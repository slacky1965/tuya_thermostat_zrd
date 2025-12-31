#include "tl_common.h"

#include "app_main.h"

#define NOT_NEED_CONFIRM    false
#define NEED_CONFIRM        true

static uint8_t      pkt_buff[DATA_MAX_LEN*2];
static uint8_t      answer_count = 0;
static uint32_t     answer_period = 0;
static uint16_t     seq_num = 0;
static status_net_t status_net = STATUS_NET_UNKNOWN;
static uint8_t      no_answer = false;
static uint32_t     uart_timeout = TIMEOUT_10SEC;

static schedule_args_model2_t schedule_args;

static ev_timer_event_t *check_answerTimerEvt = NULL;
static ev_timer_event_t *check_answerMcuTimerEvt = NULL;

static cmd_queue_cell_t ring_cmd_buff[RING_CMD_QUEUE_CELL_SIZE];
static uint16_t         ring_cmd_head, ring_cmd_tail;

bool                    first_start = true;
char8_t                 signature[9] = {0};
temp_schedule_model8_t  temp_schedule;


uint8_t checksum(uint8_t *data, uint16_t length) {

    uint8_t crc8 = 0;

    for(uint8_t i = 0; i < length; i++) {
        crc8 += data[i];
    }

    return crc8;
}

static uint16_t get_len_ring_cmd() {
    return (ring_cmd_head - ring_cmd_tail) & (RING_CMD_QUEUE_CELL_MASK);
}

static uint16_t get_freespace_ring_cmd() {
    return (sizeof(ring_cmd_buff)/sizeof(ring_cmd_buff[0]) - get_len_ring_cmd());
}

static void flush_ring_cmd() {
    ring_cmd_head = ring_cmd_tail = 0;
}

static cmd_queue_cell_t *read_from_ring_cmd() {

    if (get_len_ring_cmd()) {
        cmd_queue_cell_t *cmd_queue = &ring_cmd_buff[ring_cmd_tail];
        return cmd_queue;
    }
    return NULL;
}

static void move_queue_ring_cmd(cmd_queue_cell_t *current_queue) {

    if (current_queue) {
        if (current_queue->confirm_rec) {
            ring_cmd_tail++;
            ring_cmd_tail &= RING_CMD_QUEUE_CELL_MASK;
        }
    }
}

bool add_to_ring_cmd(pkt_tuya_t *pkt, uint8_t confirm_need) {

    uint16_t free_space = get_freespace_ring_cmd();
    bool st = false;

    if (free_space) {
        ring_cmd_buff[ring_cmd_head].confirm_need = confirm_need;
        ring_cmd_buff[ring_cmd_head].confirm_rec = 0;
        memcpy(&(ring_cmd_buff[ring_cmd_head].pkt), pkt, sizeof(pkt_tuya_t));
//        printf("confirm_need:  %d\r\n", ring_cmd_buff[ring_cmd_head].confirm_need);
//        printf("confirm_rec:   %d\r\n", ring_cmd_buff[ring_cmd_head].confirm_rec);
//        printf("pkt:           0x");
//        uint8_t ch;
//
//        uint8_t *data = (uint8_t*)&(ring_cmd_buff[ring_cmd_head].pkt);
//
//        for (int i = 0; i < ring_cmd_buff[ring_cmd_head].pkt.pkt_len; i++) {
//            ch = data[i];
//            if (ch < 0x10) {
//                printf("0%x", ch);
//            } else {
//                printf("%x", ch);
//            }
//        }
//
//        printf("\r\n");

        ring_cmd_head++;
        ring_cmd_head &= RING_CMD_QUEUE_CELL_MASK;
//        printf("free_space:    %d\r\n", free_space);
//        printf("ring_cmd_head: %d\r\n", ring_cmd_head);
//        printf("ring_cmd_tail: %d\r\n", ring_cmd_tail);
        st = true;
    }

//    printf("st %s\r\n", st?"true":"false");
    return st;
}


static uartTx_err send_command(pkt_tuya_t *pkt) {

    uartTx_err ret = UART_TX_FAILED;

    for(uint8_t i = 0; i < 100; i++) {
        ret = app_uart_txMsg((uint8_t*)pkt, pkt->pkt_len);
        if (ret == UART_TX_SUCCESS) break;
        sleep_ms(5);
    }

    return ret;
}

uint16_t get_seq_num() {

    return seq_num;
}

void set_seq_num(uint16_t f_seq_num) {

    seq_num = f_seq_num;
}

void set_header_pkt(uint8_t *f_pkt_buff, uint8_t len, uint16_t f_seq_num, uint8_t command) {

    memset(f_pkt_buff, 0, len);
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)f_pkt_buff;
    out_pkt->pkt_len = 0;
    out_pkt->f_start1 = FLAG_START1;
    out_pkt->pkt_len++;
    out_pkt->f_start2 = FLAG_START2;
    out_pkt->pkt_len++;
    out_pkt->pkt_vesion = SP_VERSION;
    out_pkt->pkt_len++;
    out_pkt->seq_num = reverse16(f_seq_num);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    out_pkt->command = command;
    out_pkt->pkt_len++;
}

static void set_command(command_t command, uint16_t f_seq_num, bool inc_seq_num) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t len;
    uint32_t utc_time, local_time;

    if (inc_seq_num) {
        f_seq_num++;
        if (f_seq_num > 0xFFF0) f_seq_num = 0;
        seq_num = f_seq_num;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), f_seq_num, command);

    switch(command) {
        case COMMAND00:
            break;
        case COMMAND01:
            out_pkt->len = 0;
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_to_ring_cmd(out_pkt, true);
            break;
        case COMMAND02:
            out_pkt->len = reverse16(1);
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = status_net;
            out_pkt->pkt_len++;
            out_pkt->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_to_ring_cmd(out_pkt, true);
            break;
        case COMMAND03:
            out_pkt->len = 0;
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_to_ring_cmd(out_pkt, false);
            break;
        case COMMAND04:
        case COMMAND05:
        case COMMAND06:
            break;
        case COMMAND20:
            printf("f_seq_num: %d\r\n", f_seq_num);
            out_pkt->len = reverse16(1);
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = status_net;
            out_pkt->pkt_len++;
            out_pkt->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_to_ring_cmd(out_pkt, false);
            break;
        case COMMAND24:
            out_pkt->len = reverse16(8);
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;

            zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_TIME, &len, (uint8_t*)&utc_time);
            zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_LOCAL_TIME, &len, (uint8_t*)&local_time);

            utc_time   += UNIX_TIME_CONST;
            local_time += UNIX_TIME_CONST;

            out_pkt->data[0] = (utc_time >> 24) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[1] = (utc_time >> 16) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[2] = (utc_time >> 8) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[3] = utc_time & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[4] = (local_time >> 24) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[5] = (local_time >> 16) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[6] = (local_time >> 8) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[7] = local_time & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[8] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_to_ring_cmd(out_pkt, false);

            break;
        case COMMAND28:
            out_pkt->len = 0;
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_to_ring_cmd(out_pkt, false);
            break;
        case COMMANDXX:
            printf("COMMMANDXX\r\n");
            out_pkt->command = 0x28;
            out_pkt->len = reverse16(1);
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = 0x17;
            out_pkt->pkt_len++;
//            out_pkt->data[1] = 0x04;
//            out_pkt->pkt_len++;
//            out_pkt->data[2] = 0x00;
//            out_pkt->pkt_len++;
//            out_pkt->data[3] = 0x01;
//            out_pkt->pkt_len++;
//            out_pkt->data[4] = 0x01;
//            out_pkt->pkt_len++;
            out_pkt->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_to_ring_cmd(out_pkt, true);
            break;
        default:
            break;
    }
}

static void set_default_answer(command_t command, uint16_t f_seq_num) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    set_header_pkt(pkt_buff, sizeof(pkt_buff), f_seq_num, command);
    out_pkt->len = reverse16(1);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    out_pkt->data[0] = 0x01;
    out_pkt->pkt_len++;
    out_pkt->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, false);

}

static int32_t check_answerCb(void *arg) {

    if (no_answer) {
#if UART_PRINTF_MODE
        printf("no answer, uart reinit\r\n");
#endif
        app_uart_reinit();
        no_answer = false;

    }

    check_answerTimerEvt = NULL;
    return -1;
}

static int32_t check_answerMcuCb(void *arg) {

#if UART_PRINTF_MODE
    printf("no answer from MCU, uart reinit\r\n");
#endif

    app_uart_reinit();

    return 0;
}

static int32_t net_steer_start_offCb(void *args) {

    g_appCtx.net_steer_start = false;

    return -1;
}

void uart_cmd_handler() {

    size_t load_size = 0;
    uint8_t ch, complete = false;
    uint8_t answer_buff[DATA_MAX_LEN+24];
    pkt_tuya_t *pkt  = (pkt_tuya_t*)answer_buff;
    data_point_t *data_point = (data_point_t*)pkt->data;
    cmd_queue_cell_t *current_queue = NULL;

    if (first_start) {
        flush_ring_cmd();
        set_command(COMMAND01, seq_num, true);
//        data_point_model_init();
        check_answerMcuTimerEvt = TL_ZB_TIMER_SCHEDULE(check_answerMcuCb, NULL, TIMEOUT_1MIN30SEC);

        first_start = false;

        memset(&schedule_model8, 0, sizeof(schedule_model8));

        //only for test!!!
//        set_command(COMMANDXX, seq_num, true);
    }

    current_queue = read_from_ring_cmd();

    if (current_queue) {

        /* except "aoclfnxz" and "edl8pz1k" */
        if (strcmp(signature, tuya_manuf_names[1][0]) && strcmp(signature, tuya_manuf_names[0][1])) {
            if (!clock_time_exceed(answer_period, TIMEOUT_TICK_50MS)) {
                return;
            }
        }

        if (send_command(&(current_queue->pkt)) == UART_TX_SUCCESS) {

            answer_period = clock_time();

            if (current_queue->confirm_need) {

                /* trying to read for 1 seconds */
                for(uint8_t i = 0; i < 100; i++ ) {
                    load_size = 0;
                    if (available_ring_buff() /*&& get_queue_len_ring_buff() >= 8*/) {
                        while (available_ring_buff() && load_size < (DATA_MAX_LEN + 8)) {
                            ch = read_byte_from_ring_buff();

                            if (load_size == 0) {
                                if (ch != FLAG_START1) {
                                    continue;
                                }
                            } else if (load_size == 1) {
                                if (ch != FLAG_START2) {
                                    load_size = 0;
                                    continue;
                                }
                            }

                            answer_buff[load_size++] = ch;

                            if (load_size == 2) {

                                load_size += read_bytes_from_buff(answer_buff+load_size, 6);

                                if (load_size == 8) {
                                    pkt->len = reverse16(pkt->len);
                                    load_size += read_bytes_from_buff(answer_buff+load_size, pkt->len+1);
                                    i = 100;
                                    complete = true;
                                    break;
                                } else {
                                    load_size = 0;
                                    continue;
                                }

                            }
                        }
                    }
#if (MODULE_WATCHDOG_ENABLE)
                    drv_wd_clear();
#endif
                    sleep_ms(10);
                }

                pkt_tuya_t *send_pkt = &current_queue->pkt;

                if (complete) {

                    no_answer = false;

                    pkt->pkt_len = load_size;
                    uint8_t crc = checksum((uint8_t*)pkt, pkt->pkt_len-1);

//                    printf("complete.inCRC: 0x%x, outCRC: 0x%x\r\n", crc, answer_buff[pkt->pkt_len-1]);

                    if (crc == answer_buff[pkt->pkt_len-1]) {

                        if (send_pkt->command == COMMAND04 && (pkt->command == COMMAND06 || pkt->command == COMMAND05) /*&& pkt->seq_num == send_pkt->seq_num*/) {
                            current_queue->confirm_rec = true;
                            if (manuf_name == MANUF_NAME_0C) {
                                set_default_answer(COMMAND06, reverse16(pkt->seq_num));
                            } else if (data_point->dp_id == data_point_model[DP_IDX_SETPOINT].id ||
                                data_point->dp_id == data_point_model[DP_IDX_ONOFF].id ||
                                data_point->dp_id == data_point_model[DP_IDX_FAN_MODE].id ||
                                data_point->dp_id == data_point_model[DP_IDX_FAN_CONTROL].id ||
                                data_point->dp_id == data_point_model[DP_IDX_SCHEDULE].id) {
                                if (strcmp(tuya_manuf_names[MANUF_NAME_6][1], signature) ||
                                        strcmp(tuya_manuf_names[MANUF_NAME_6][3], signature)) {
                                    set_default_answer(COMMAND05, reverse16(pkt->seq_num));
                                } else {
                                    set_default_answer(COMMAND06, reverse16(pkt->seq_num));
                                }
                            }
                        } else if (send_pkt->command == COMMAND28) {
                            current_queue->confirm_rec = true;
                        } else if (pkt->command == send_pkt->command /*&& pkt->seq_num == send_pkt->seq_num*/) {
//                            printf("command: 0%x\r\n", pkt->command);
                            switch(pkt->command) {
                                case COMMAND01:

                                    current_queue->confirm_rec = true;

                                    uint8_t *p = pkt->data;
                                    uint16_t len = pkt->len;

                                    while(*p != ':' && len != 0) {
                                        p++;
                                        len--;
                                    }
                                    p++;
                                    p++;

                                    uint8_t *ptr = p;
                                    while(*p != '"' && len != 0) {
                                        p++;
                                        len--;
                                    }

                                    *p = 0;

                                    manuf_name = MANUF_NAME_MAX;

                                    for (uint8_t ii = 0; ii < MANUF_NAME_MAX; ii++) {
                                        for (uint8_t i = 0; i < 255; i++) {
                                            if (tuya_manuf_names[ii][i] == NULL) break;
//                                            printf("tuya_manuf_names[%d][%d]: %s\r\n", ii, i, tuya_manuf_names[ii][i]);
                                            if (strcmp(tuya_manuf_names[ii][i], (char8_t*)ptr) == 0) {
                                                manuf_name = ii;
                                                ii = MANUF_NAME_MAX;
                                                break;
                                            }
                                        }
                                    }

                                    if (manuf_name == MANUF_NAME_MAX) {
#if UART_PRINTF_MODE
                                        printf("Unknown Tuya signature: \"%s\". Use default\r\n", ptr);
#endif
                                        manuf_name = MANUF_NAME_1;
                                        strcpy(signature, tuya_manuf_names[0][0]);

                                    } else {
#if UART_PRINTF_MODE
                                        printf("Tuya signature found: \"%s\"\r\n", ptr);
#endif
                                        strcpy(signature, (char8_t*)ptr);
                                    }

                                    if (g_zcl_thermostatAttrs.manuf_name && g_zcl_thermostatAttrs.manuf_name <= MANUF_NAME_MAX) {
                                        manuf_name = g_zcl_thermostatAttrs.manuf_name - 1;
                                        strcpy(signature, tuya_manuf_names[manuf_name][0]);
#if UART_PRINTF_MODE
                                        printf("Manual set signature: \"%s\".\r\n", signature);
#endif
                                    }

#if 0
                                    /* Only for test */
//                                    manuf_name = MANUF_NAME_1;
//                                    manuf_name = MANUF_NAME_2;
//                                    manuf_name = MANUF_NAME_3;
//                                    manuf_name = MANUF_NAME_4;
//                                    manuf_name = MANUF_NAME_5;

#endif

//                                    init_datapoint_model(manuf_name);
//                                    data_point_model = data_point_model_arr[manuf_name];

                                    if (check_answerMcuTimerEvt) {
                                        TL_ZB_TIMER_CANCEL(&check_answerMcuTimerEvt);
                                    }

                                    switch(manuf_name) {
                                        case MANUF_NAME_1:
                                            data_point_model = init_datapoint_model1();
                                            uart_timeout = TIMEOUT_1MIN30SEC;
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '1';
                                            break;
                                        case MANUF_NAME_2:
                                            uart_timeout = TIMEOUT_8SEC;
                                            data_point_model = init_datapoint_model2();
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '2';
                                            break;
                                        case MANUF_NAME_3:
                                            data_point_model = init_datapoint_model3();
                                            uart_timeout = TIMEOUT_15SEC;
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '3';
                                            break;
                                        case MANUF_NAME_4:
                                            data_point_model = init_datapoint_model4();
                                            uart_timeout = TIMEOUT_15SEC;
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '4';
                                            break;
                                        case MANUF_NAME_5:
                                            data_point_model = init_datapoint_model5();
                                            uart_timeout = TIMEOUT_1MIN30SEC;
                                            set_command(COMMAND28, seq_num, true);
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '5';
                                            break;
                                        case MANUF_NAME_6:
                                            data_point_model = init_datapoint_model6();
                                            uart_timeout = TIMEOUT_30SEC;
                                            set_command(COMMAND28, seq_num, true);
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '6';
                                            break;
                                        case MANUF_NAME_7:
                                            data_point_model = init_datapoint_model7();
                                            uart_timeout = TIMEOUT_25SEC;
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '7';
                                            break;
                                        case MANUF_NAME_8:
                                            data_point_model = init_datapoint_model8();
                                            uart_timeout = TIMEOUT_15SEC;
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '8';
                                            break;
                                        case MANUF_NAME_9:
                                            data_point_model = init_datapoint_model9();
                                            uart_timeout = TIMEOUT_2MIN30SEC;
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = '9';
                                            break;
                                        case MANUF_NAME_0A:
                                            data_point_model = init_datapoint_model0A();
                                            uart_timeout = TIMEOUT_1MIN30SEC;
                                            set_command(COMMAND28, seq_num, true);
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = 'A';
                                            break;
                                        case MANUF_NAME_0B:
                                            data_point_model = init_datapoint_model0B();
                                            uart_timeout = TIMEOUT_15SEC;
                                            set_command(COMMAND28, seq_num, true);
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = 'B';
                                            break;
                                        case MANUF_NAME_0C:
                                            data_point_model = init_datapoint_model0C();
                                            uart_timeout = TIMEOUT_20SEC;
                                            set_command(COMMAND28, seq_num, true);
                                            zb_modelId[18] = '0';
                                            zb_modelId[19] = 'C';
                                            break;
                                        default:
                                            manuf_name = MANUF_NAME_1;
                                            strcpy(signature, tuya_manuf_names[0][0]);
                                            data_point_model = init_datapoint_model1();
                                            uart_timeout = TIMEOUT_1MIN30SEC;
                                            break;
                                    }

                                    check_answerMcuTimerEvt = TL_ZB_TIMER_SCHEDULE(check_answerMcuCb, NULL, uart_timeout);

#if UART_PRINTF_MODE
                                    printf("Use modelId: %s\r\n", zb_modelId+1);
#endif

                                    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_BASIC, ZCL_ATTRID_BASIC_MODEL_ID, zb_modelId);

                                    break;
                                case COMMAND02:
                                    current_queue->confirm_rec = true;
                                    break;
                                case COMMAND00:
                                case COMMAND03:
                                case COMMAND04:
                                case COMMAND05:
                                case COMMAND06:
                                    break;
                                case COMMAND28:
                                    current_queue->confirm_rec = true;
                                    break;
                                default:
                                    break;
                            }
                        }

                    } else {
#if UART_PRINTF_MODE
                        printf("Error CRC. inCRC: 0x%x, outCRC: 0x%x\r\n", crc, answer_buff[pkt->pkt_len-1]);
#endif
                    }

                } else {
#if UART_PRINTF_MODE
                    printf("no complete\r\n");
#endif
                    current_queue->confirm_rec = false;
                    if (answer_count++ == 5) {
                        answer_count = 0;
                        current_queue->confirm_rec = true;
                    }

                    if (!no_answer) {
                        no_answer = true;

                        if (check_answerTimerEvt) {
                            TL_ZB_TIMER_CANCEL(&check_answerTimerEvt);
                        }
                        check_answerTimerEvt = TL_ZB_TIMER_SCHEDULE(check_answerCb, NULL, TIMEOUT_15SEC);
                    }


                    if (send_pkt->command == COMMAND01) {
                        uint32_t baudrate = get_uart_baudrate();
                        if (baudrate == UART_BAUDRATE_9600) {
                            set_uart_baudrate(UART_BAUDRATE_115200);
                        } else {
                            set_uart_baudrate(UART_BAUDRATE_9600);
                        }
                        app_uart_reinit();
                    }
                }
            } else {
                current_queue->confirm_rec = true;
            }

        }
    }

    move_queue_ring_cmd(current_queue);


#if (MODULE_WATCHDOG_ENABLE)
    drv_wd_clear();
#endif

    if (available_ring_buff() /* && get_queue_len_ring_buff() >= 8*/) {
        load_size = 0;
        while (available_ring_buff() && load_size < (DATA_MAX_LEN + 8)) {
            ch = read_byte_from_ring_buff();

            if (load_size == 0) {
                if (ch != FLAG_START1) {
                    continue;
                }
            } else if (load_size == 1) {
                if (ch != FLAG_START2) {
                    load_size = 0;
                    continue;
                }
            }

            answer_buff[load_size++] = ch;

            if (load_size == 2) {

                load_size += read_bytes_from_buff(answer_buff+load_size, 6);

                if (load_size == 8) {
                    pkt->len = reverse16(pkt->len);
                    load_size += read_bytes_from_buff(answer_buff+load_size, pkt->len+1);
                    break;
                } else {
                    load_size = 0;
                    continue;
                }

            }
        }

        if (load_size == pkt->len + 9) {

            if (check_answerMcuTimerEvt) {
                TL_ZB_TIMER_CANCEL(&check_answerMcuTimerEvt);
            }
            check_answerMcuTimerEvt = TL_ZB_TIMER_SCHEDULE(check_answerMcuCb, NULL, uart_timeout);

            pkt->pkt_len = load_size;
            uint8_t crc = checksum((uint8_t*)pkt, pkt->pkt_len-1);
            if (crc == answer_buff[pkt->pkt_len-1]) {
                pkt->seq_num = reverse16(pkt->seq_num);

                if (pkt->command == COMMAND03) {
                    if (pkt->data[0] == 0x01) {
                        /* Reset Factory */
#if UART_PRINTF_MODE && DEBUG_CMD
                        printf("command 0x03. Factory Reset. net_steer_start: %d\r\n", g_appCtx.net_steer_start);
#endif
                        if (!g_appCtx.net_steer_start) {

                            set_status_net(STATUS_NET_FREE);

                            zb_factoryReset();

                            g_appCtx.net_steer_start = true;

                            if (g_appCtx.factory_resetTimerEvt) {
                                TL_ZB_TIMER_CANCEL(&g_appCtx.factory_resetTimerEvt);
                            }
                            g_appCtx.factory_resetTimerEvt = TL_ZB_TIMER_SCHEDULE(net_steer_start_offCb, NULL, TIMEOUT_1MIN30SEC);

                        }

                        set_command(pkt->command, pkt->seq_num, false);

                    } else {
#if UART_PRINTF_MODE && DEBUG_CMD
                        printf("command 0x03. Reset ZTU. Not support\r\n");
#endif
                    }
//                } else if (pkt->command == COMMAND02) {
//                    printf("input COMMAND02\r\n");
                } else if (pkt->command == COMMAND20) {
                    printf("pkt->seq_num: %d\r\n", pkt->seq_num);
                    set_command(pkt->command, pkt->seq_num, false);
                } else if (pkt->command == COMMAND24) {
#if UART_PRINTF_MODE
                    printf("command 0x24. Sync Time\r\n");
#endif
                    if (get_time_sent()) {
                        set_command(pkt->command, pkt->seq_num, false);
                    } else {
                        if (strcmp(tuya_manuf_names[MANUF_NAME_6][1], signature)) {
                            set_default_answer(COMMAND05, reverse16(pkt->seq_num));
                        } else {
                            set_default_answer(COMMAND06, reverse16(pkt->seq_num));
                        }
                    }

                } else if (pkt->command == COMMAND06 || pkt->command == COMMAND05) {
#if UART_PRINTF_MODE && DEBUG_CMD
                    printf("command 0x06. Report DP data\r\n");
#endif
                    if (pkt->len >= 5) {
                        /* data point used */
                        data_point->dp_len = reverse16(data_point->dp_len);

#if UART_PRINTF_MODE && DEBUG_DP
                        printf("data point id: 0x%x\r\n", data_point->dp_id);
#endif

                        set_default_answer(pkt->command, pkt->seq_num);

                        if (data_point->dp_id == data_point_model[DP_IDX_ONOFF].id &&
                                data_point->dp_type == data_point_model[DP_IDX_ONOFF].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP OnOff\r\n");
#endif

                            uint8_t onoff = data_point->data[0];
                            if (data_point_model[DP_IDX_ONOFF].local_cmd)
                                data_point_model[DP_IDX_ONOFF].local_cmd(&onoff);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_PROG].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_PROG].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP ProgMode\r\n");
#endif
                            uint8_t mode = data_point->data[0];
                            if (data_point_model[DP_IDX_PROG].local_cmd) data_point_model[DP_IDX_PROG].local_cmd(&mode);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_FAN_MODE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_FAN_MODE].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP FanMode\r\n");
#endif
                            uint8_t mode = data_point->data[0];
                            if (data_point_model[DP_IDX_FAN_MODE].local_cmd)
                                data_point_model[DP_IDX_FAN_MODE].local_cmd(&mode);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_FAN_CONTROL].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_FAN_CONTROL].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP FanControl\r\n");
#endif
                            uint8_t fan_control = data_point->data[0];
                            if (data_point_model[DP_IDX_FAN_CONTROL].local_cmd)
                                data_point_model[DP_IDX_FAN_CONTROL].local_cmd(&fan_control);

//                        } else if (data_point->dp_id == data_point_model[DP_IDX_UNKNOWN].id &&
//                                   data_point->dp_type == data_point_model[DP_IDX_UNKNOWN].type) {
//
                        } else if (data_point->dp_id == data_point_model[DP_IDX_SETPOINT].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SETPOINT].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP HeatSetPoint\r\n");
#endif
                            uint16_t temp = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_SETPOINT].local_cmd)
                                data_point_model[DP_IDX_SETPOINT].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_MIN].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_MIN].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP MinHeatSet\r\n");
#endif
                            int16_t temp = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_MIN].local_cmd)
                                data_point_model[DP_IDX_MIN].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_MAX].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_MAX].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP MaxHeatSet\r\n");
#endif
                            int16_t temp = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_MAX].local_cmd)
                                data_point_model[DP_IDX_MAX].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_FROST_PROTECT].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_FROST_PROTECT].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP FrostProtect\r\n");
#endif
                            if (manuf_name == MANUF_NAME_6) {
                                uint8_t frost = data_point->data[0];

                                if (data_point_model[DP_IDX_FROST_PROTECT].local_cmd)
                                    data_point_model[DP_IDX_FROST_PROTECT].local_cmd(&frost);
                            } else {
                                uint32_t temp = int32_from_str(data_point->data) & 0xffff;

                                if (data_point_model[DP_IDX_FROST_PROTECT].local_cmd)
                                    data_point_model[DP_IDX_FROST_PROTECT].local_cmd(&temp);
                            }

                        } else if (data_point->dp_id == data_point_model[DP_IDX_HEAT_PROTECT].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_HEAT_PROTECT].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP HeatProtect\r\n");
#endif
                            int16_t temp = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_HEAT_PROTECT].local_cmd)
                                data_point_model[DP_IDX_HEAT_PROTECT].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_TEMP_OUT].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_TEMP_OUT].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP OutTemp\r\n");
#endif
                            int16_t temp = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_TEMP_OUT].local_cmd)
                                data_point_model[DP_IDX_TEMP_OUT].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_TEMP].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_TEMP].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP LocalTemp\r\n");
#endif
                            int16_t temp = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_TEMP].local_cmd)
                                data_point_model[DP_IDX_TEMP].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_DEADZONE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_DEADZONE].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP DeadZone\r\n");
#endif
                            int16_t temp = int32_from_str(data_point->data) & 0xFFFF;

                            if (data_point_model[DP_IDX_DEADZONE].local_cmd)
                                data_point_model[DP_IDX_DEADZONE].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_CALIBRATION].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_CALIBRATION].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Calibration\r\n");
#endif
                            int8_t temp = int32_from_str(data_point->data) &0xff;

                            if (data_point_model[DP_IDX_CALIBRATION].local_cmd)
                                data_point_model[DP_IDX_CALIBRATION].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_RUNSTATE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_RUNSTATE].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP RunState: %d\r\n", data_point->data[0]);
#endif
                            run_state_bit_t run_state_bit;
                            run_state_bit.bit_num = RUN_STATE_HEAT_BIT;
                            if (data_point->data[0]) {
                                if (manuf_name == MANUF_NAME_6 || manuf_name == MANUF_NAME_0A) {
                                    run_state_bit.set = ON;
                                } else {
                                    run_state_bit.set = OFF;
                                }
                            } else {
                                if (manuf_name == MANUF_NAME_6 || manuf_name == MANUF_NAME_0A) {
                                    run_state_bit.set = OFF;
                                } else {
                                    run_state_bit.set = ON;
                                }
                            }

//                            printf("DP RunState: %d\r\n",  run_state_bit.set);
                            if (data_point_model[DP_IDX_RUNSTATE].local_cmd)
                                data_point_model[DP_IDX_RUNSTATE].local_cmd(&run_state_bit);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_LOCKUNLOCK].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_LOCKUNLOCK].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP KeyLock\r\n");
#endif
                            uint8_t lock = data_point->data[0];

                            if (data_point_model[DP_IDX_LOCKUNLOCK].local_cmd)
                                data_point_model[DP_IDX_LOCKUNLOCK].local_cmd(&lock);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_MODE_LOCK].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_MODE_LOCK].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP KeyLockMode\r\n");
#endif
                            uint8_t mode = data_point->data[0];
                            if (data_point_model[DP_IDX_MODE_LOCK].local_cmd)
                                data_point_model[DP_IDX_MODE_LOCK].local_cmd(&mode);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SENSOR].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SENSOR].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP SensorUsed\r\n");
#endif
                            uint8_t sensor_used = data_point->data[0];

                            if (data_point_model[DP_IDX_SENSOR].local_cmd)
                                data_point_model[DP_IDX_SENSOR].local_cmd(&sensor_used);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_ECO_MODE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_ECO_MODE].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP EcoMode\r\n");
#endif
                            uint8_t eco_mode = data_point->data[0];

                            if (data_point_model[DP_IDX_ECO_MODE].local_cmd)
                                data_point_model[DP_IDX_ECO_MODE].local_cmd(&eco_mode);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_ECO_HEAT_TEMP].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_ECO_HEAT_TEMP].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP EcoModeHeatTemp\r\n");
#endif
                            int16_t temp = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_ECO_HEAT_TEMP].local_cmd)
                                data_point_model[DP_IDX_ECO_HEAT_TEMP].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_ECO_COOL_TEMP].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_ECO_COOL_TEMP].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP EcoModeCoolTemp\r\n");
#endif
                            int16_t temp = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_ECO_COOL_TEMP].local_cmd)
                                data_point_model[DP_IDX_ECO_COOL_TEMP].local_cmd(&temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_THERM_MODE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_THERM_MODE].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP ThermostatMode\r\n");
#endif

                            uint8_t therm_mode = data_point->data[0];

                            if (data_point_model[DP_IDX_THERM_MODE].local_cmd)
                                data_point_model[DP_IDX_THERM_MODE].local_cmd(&therm_mode);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_LEVEL_A].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_LEVEL_A].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP LevelA\r\n");
#endif
                            uint8_t level = 0;

                            if (manuf_name == MANUF_NAME_6) {
                                level = data_point->data[0];
                            } else {
                                level = int32_from_str(data_point->data) & 0xff;
                            }

                            if (data_point_model[DP_IDX_LEVEL_A].local_cmd)
                                data_point_model[DP_IDX_LEVEL_A].local_cmd(&level);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_LEVEL_B].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_LEVEL_B].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP LevelB\r\n");
#endif
                            uint8_t level = int32_from_str(data_point->data) & 0xff;

                            if (data_point_model[DP_IDX_LEVEL_B].local_cmd)
                                data_point_model[DP_IDX_LEVEL_B].local_cmd(&level);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SOUND].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SOUND].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Sound\r\n");
#endif
                            uint8_t sound = data_point->data[0];

                            if (data_point_model[DP_IDX_SOUND].local_cmd)
                                data_point_model[DP_IDX_SOUND].local_cmd(&sound);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SETTINGS_RESET].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SETTINGS_RESET].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Settings Reset\r\n");
#endif
                            uint8_t sreset = data_point->data[0];

                            if (data_point_model[DP_IDX_SETTINGS_RESET].local_cmd)
                                data_point_model[DP_IDX_SETTINGS_RESET].local_cmd(&sreset);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_INVERSION].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_INVERSION].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Inversion\r\n");
#endif
                            uint8_t inversion = data_point->data[0];

                            if (data_point_model[DP_IDX_INVERSION].local_cmd)
                                data_point_model[DP_IDX_INVERSION].local_cmd(&inversion);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_HUMIDITY].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_HUMIDITY].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Humidity\r\n");
#endif
                            uint16_t hum = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_HUMIDITY].local_cmd)
                                data_point_model[DP_IDX_HUMIDITY].local_cmd(&hum);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_HUMIDITY_OFFSET].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_HUMIDITY_OFFSET].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Humidity offset\r\n");
#endif
                            uint16_t hum_offset = int32_from_str(data_point->data) & 0xffff;

                            if (data_point_model[DP_IDX_HUMIDITY_OFFSET].local_cmd)
                                data_point_model[DP_IDX_HUMIDITY_OFFSET].local_cmd(&hum_offset);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Schedule\r\n");
#endif
                            if (data_point_model[DP_IDX_SCHEDULE].local_cmd)
                                data_point_model[DP_IDX_SCHEDULE].local_cmd(data_point);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE_MON].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE_MON].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Schedule Mon\r\n");
#endif
                            uint8_t mode;
                            if (manuf_name == MANUF_NAME_6) {
                                /* schedule mode */
                                mode = data_point->data[0];
                                if (data_point_model[DP_IDX_SCHEDULE_MON].local_cmd)
                                    data_point_model[DP_IDX_SCHEDULE_MON].local_cmd(&mode);
                            } else if (manuf_name == MANUF_NAME_8) {
                                /* schedule mode */
                                mode = data_point->data[0];
                                memset(&temp_schedule, 0, sizeof(temp_schedule));
                                temp_schedule.week_day = mode;
//                                printf("DP_IDX_SCHEDULE_MON. week day: %d\r\n", mode);
                            } else {
                                schedule_args.data_point = data_point;
                                schedule_args.idx = DP_IDX_SCHEDULE_MON;
                                schedule_args.heatMode = g_zcl_scheduleData.schedule_mon,
                                schedule_args.w_day = DAY_MON;

                                if (data_point_model[DP_IDX_SCHEDULE_MON].local_cmd)
                                    data_point_model[DP_IDX_SCHEDULE_MON].local_cmd(&schedule_args);
                            }

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE_TUE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE_TUE].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Schedule Tue\r\n");
#endif
                            if (manuf_name == MANUF_NAME_8) {
                                temp_schedule.hour = int32_from_str(data_point->data);
//                                printf("DP_IDX_SCHEDULE_TUE. hour: %d\r\n", temp_schedule.hour);
                            } else {
                                schedule_args.data_point = data_point;
                                schedule_args.idx = DP_IDX_SCHEDULE_TUE;
                                schedule_args.heatMode = g_zcl_scheduleData.schedule_tue,
                                schedule_args.w_day = DAY_TUE;

                                if (data_point_model[DP_IDX_SCHEDULE_TUE].local_cmd)
                                    data_point_model[DP_IDX_SCHEDULE_TUE].local_cmd(&schedule_args);
                            }
                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE_WED].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE_WED].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Schedule Wed\r\n");
#endif
                            if (manuf_name == MANUF_NAME_8) {
                                temp_schedule.minute = int32_from_str(data_point->data);
//                                printf("DP_IDX_SCHEDULE_WED. minute: %d\r\n", temp_schedule.minute);
                            } else {
                                schedule_args.data_point = data_point;
                                schedule_args.idx = DP_IDX_SCHEDULE_WED;
                                schedule_args.heatMode = g_zcl_scheduleData.schedule_wed,
                                schedule_args.w_day = DAY_WED;

                                if (data_point_model[DP_IDX_SCHEDULE_WED].local_cmd)
                                    data_point_model[DP_IDX_SCHEDULE_WED].local_cmd(&schedule_args);
                            }

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE_THU].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE_THU].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Schedule Thu\r\n");
#endif
                            if (manuf_name == MANUF_NAME_8) {
                                temp_schedule.temperature = int32_from_str(data_point->data);
//                                printf("DP_IDX_SCHEDULE_THU. temperature: %d\r\n", temp_schedule.temperature);
                            } else {
                                schedule_args.data_point = data_point;
                                schedule_args.idx = DP_IDX_SCHEDULE_THU;
                                schedule_args.heatMode = g_zcl_scheduleData.schedule_thu,
                                schedule_args.w_day = DAY_THU;

                                if (data_point_model[DP_IDX_SCHEDULE_THU].local_cmd)
                                    data_point_model[DP_IDX_SCHEDULE_THU].local_cmd(&schedule_args);
                            }

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE_FRI].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE_FRI].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Schedule Fri\r\n");
#endif
                            if (manuf_name == MANUF_NAME_8) {
                                temp_schedule.time_period = data_point->data[0];
//                                printf("DP_IDX_SCHEDULE_FRI. time_period: %d\r\n", temp_schedule.time_period);
                                if (data_point_model[DP_IDX_SCHEDULE_FRI].local_cmd)
                                    data_point_model[DP_IDX_SCHEDULE_FRI].local_cmd(&temp_schedule);
                            } else {
                                schedule_args.data_point = data_point;
                                schedule_args.idx = DP_IDX_SCHEDULE_FRI;
                                schedule_args.heatMode = g_zcl_scheduleData.schedule_fri,
                                schedule_args.w_day = DAY_FRI;

                                if (data_point_model[DP_IDX_SCHEDULE_FRI].local_cmd)
                                    data_point_model[DP_IDX_SCHEDULE_FRI].local_cmd(&schedule_args);
                            }

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE_SAT].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE_SAT].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Schedule Sat\r\n");
#endif
                            schedule_args.data_point = data_point;
                            schedule_args.idx = DP_IDX_SCHEDULE_SAT;
                            schedule_args.heatMode = g_zcl_scheduleData.schedule_sat,
                            schedule_args.w_day = DAY_SAT;

                            if (data_point_model[DP_IDX_SCHEDULE_SAT].local_cmd)
                                data_point_model[DP_IDX_SCHEDULE_SAT].local_cmd(&schedule_args);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE_SUN].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE_SUN].type) {

#if UART_PRINTF_MODE && DEBUG_DP
                            printf("DP Schedule Sun\r\n");
#endif
                            schedule_args.data_point = data_point;
                            schedule_args.idx = DP_IDX_SCHEDULE_SUN;
                            schedule_args.heatMode = g_zcl_scheduleData.schedule_sun,
                            schedule_args.w_day = DAY_SUN;

                            if (data_point_model[DP_IDX_SCHEDULE_SUN].local_cmd)
                                data_point_model[DP_IDX_SCHEDULE_SUN].local_cmd(&schedule_args);

                        }
                    }
                }
            }
        }
    }

}

void set_status_net(status_net_t new_status) {

    if (new_status != status_net) {
        status_net = new_status;
        set_command(COMMAND02, seq_num, true);
    }

    if (status_net == STATUS_NET_CONNECTED) {
        g_appCtx.net_steer_start = false;
        if (g_appCtx.factory_resetTimerEvt) {
            TL_ZB_TIMER_CANCEL(&g_appCtx.factory_resetTimerEvt);
        }

//        factory_reset_cnt = 0;
//        factory_reset_status = 0;
    }

}

