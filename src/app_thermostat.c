#include "app_main.h"

uint8_t thermostat_mode = DEV_THERM_MODE_MANUAL;

void remote_smd_sys_mode(uint8_t mode) {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_ONOFF].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_ONOFF].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    if (mode == SYS_MODE_OFF) {
        data_point->data[0] = 0x00;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
    } else if (mode == SYS_MODE_HEAT) {
        data_point->data[0] = 0x01;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
    }
}

void remote_smd_heating_set(int32_t temp) {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    if (data_point_model[DP_IDX_SETPOINT].divisor == 1) {
        temp /= 100;
    } else if (data_point_model[DP_IDX_SETPOINT].divisor == 10) {
        temp /= 10;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SETPOINT].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SETPOINT].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (temp >> 24) & 0xFF;
    data_point->data[1] = (temp >> 16) & 0xFF;
    data_point->data[2] = (temp >> 8)  & 0xFF;
    data_point->data[3] = temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);
}

void remote_smd_temp_calibration(int8_t temp) {

    if(data_point_model[DP_IDX_CALIBRATION].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    temp /= 10; // 90 -> 9, -90 -> -9
    if (data_point_model[DP_IDX_CALIBRATION].divisor == 10) {
        temp *= 10;
    } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 100) {
        temp *= 100;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_CALIBRATION].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_CALIBRATION].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    int32_t dev_temp = temp;
    data_point->data[0] = (dev_temp >> 24) & 0xFF;
    data_point->data[1] = (dev_temp >> 16) & 0xFF;
    data_point->data[2] = (dev_temp >> 8)  & 0xFF;
    data_point->data[3] = dev_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);
}

void remote_smd_display_mode(uint8_t mode) {

//    pkt_output_t *pkt = (pkt_output_t*)cmdTx[CMD_DISPLAY];
//    pkt->cnt++;
//
//    if (mode == ZCL_DISPLAY_MODE_CELSIUS) {
//        pkt->cmd_value = DEV_DISPLAY_MODE_CELSIUS;
//        add_cmd_queue(CMD_DISPLAY, true, cmdTx[CMD_DISPLAY]);
//    } else if (mode == ZCL_DISPLAY_MODE_FAHRENHEIT) {
//        pkt->cmd_value = DEV_DISPLAY_MODE_FAHRENHEIT;
//        add_cmd_queue(CMD_DISPLAY, true, cmdTx[CMD_DISPLAY]);
//    }
}

void remote_smd_keylock(uint8_t keylock) {

    if(data_point_model[DP_IDX_LOCKUNLOCK].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LOCKUNLOCK].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LOCKUNLOCK].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = keylock;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);
}

void remote_cmd_sensor_used(uint8_t sensor_used) {

    if (data_point_model[DP_IDX_SENSOR].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SENSOR].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SENSOR].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = sensor_used;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);
}

void remote_cmd_hysteresis(uint32_t hysteresis) {

    if (data_point_model[DP_IDX_DEADZONE].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;


    if (data_point_model[DP_IDX_DEADZONE].divisor == 10) {
        hysteresis *= 10;
    } else if (data_point_model[DP_IDX_DEADZONE].divisor == 100) {
        hysteresis *= 100;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_DEADZONE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_DEADZONE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (hysteresis >> 24) & 0xFF;
    data_point->data[1] = (hysteresis >> 16) & 0xFF;
    data_point->data[2] = (hysteresis >> 8)  & 0xFF;
    data_point->data[3] = hysteresis & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);
}

void remote_cmd_min_setpoint(uint32_t min_temp) {
    printf("min_temp: %d\r\n", min_temp);

    if (data_point_model[DP_IDX_MIN].id == 0) return;

//    min_temp /= 10;
//    uint8_t pkt_buff[DATA_MAX_LEN+12];
//    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
//    uint16_t seq_num = get_seq_num();
//    seq_num++;
//
//    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);
//
//    out_pkt->len = reverse16(8);
//    out_pkt->pkt_len++;
//    out_pkt->pkt_len++;
//
//    data_point_t *data_point = (data_point_t*)out_pkt->data;
//    data_point->dp_id = DP_ID_1A;
//    out_pkt->pkt_len++;
//    data_point->dp_type = DP_VAL;
//    out_pkt->pkt_len++;
//    data_point->dp_len = (reverse16(4));
//    out_pkt->pkt_len++;
//    out_pkt->pkt_len++;
//    data_point->data[0] = (min_temp >> 24) & 0xFF;
//    data_point->data[1] = (min_temp >> 16) & 0xFF;
//    data_point->data[2] = (min_temp >> 8)  & 0xFF;
//    data_point->data[3] = min_temp & 0xFF;
//    out_pkt->pkt_len += 4;
//    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
//    add_cmd_queue(out_pkt, true);
//
//    set_seq_num(seq_num);
}

void remote_cmd_max_setpoint(uint32_t max_temp) {

    if (data_point_model[DP_IDX_MAX].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    max_temp /= 100; // 4400 -> 44°C

    if (data_point_model[DP_IDX_MAX].divisor == 10) {
        max_temp *= 10;
    } else if (data_point_model[DP_IDX_MAX].divisor == 100) {
        max_temp *= 100;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_MAX].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_MAX].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (max_temp >> 24) & 0xFF;
    data_point->data[1] = (max_temp >> 16) & 0xFF;
    data_point->data[2] = (max_temp >> 8)  & 0xFF;
    data_point->data[3] = max_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);
}

void remote_cmd_oper_mode(uint8_t oper_mode) {

    if (data_point_model[DP_IDX_PROG].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_PROG].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_PROG].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = oper_mode;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);
}

void set_run_state_bit(uint8_t bit_num, bool set) {

    uint16_t runState;
    uint16_t len;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE, &len, (uint8_t*)&runState);

    if (set) {
        runState |= (1 << bit_num);
    } else {
        runState &= ~( 1 << bit_num);
    }

    zcl_setAttrVal(APP_ENDPOINT1,
                   ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE,
                   (uint8_t*)&runState);

}

void thermostat_onoff_state(int8_t onoff) {

    uint8_t sys_mode;

    if (onoff == DEV_POWER_OFF) {
#if UART_PRINTF_MODE && DEBUG_CMD
        printf("Power OFF\r\n");
#endif
        sys_mode = SYS_MODE_OFF;
        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);
        set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
    } else {
#if UART_PRINTF_MODE && DEBUG_CMD
        printf("Power ON\r\n");
#endif
        sys_mode = SYS_MODE_HEAT;
        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);

//        zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMPERATURE, &len, (uint8_t*)&localTemp);
//        zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT, &len, (uint8_t*)&ocHeatSetpoint);
//        zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE, &len, (uint8_t*)&man_prog_mode);
    }

}

//void thermostat_heatset_state(int32_t tempF) {
//
//    zcl_thermostatAttr_t *tempAttrs = zcl_thermostatAttrGet();
//
//    int16_t tempC = zcl_convert_temperature_fromFtoC(tempF/10);
//
//#if UART_PRINTF_MODE && DEBUG_CMD
//    printf("Heat set temperature: %d F, %d C, localTemperature: %d C\r\n", tempF, tempC, tempAttrs->localTemperature);
//#endif
//    tempAttrs->occupiedHeatingSetpoint = tempC;
//    if (tempAttrs->systemMode == SYS_MODE_HEAT && thermostat_mode == DEV_THERM_MODE_MANUAL) {
//        if (tempAttrs->occupiedHeatingSetpoint > tempAttrs->localTemperature) {
//            set_run_state_bit(RUN_STATE_HEAT_BIT, ON);
//        } else {
//            set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
//        }
//    } else if (tempAttrs->systemMode == SYS_MODE_OFF) {
//        set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
//    }
//
//}
