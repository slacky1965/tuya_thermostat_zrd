#include "app_main.h"

uint8_t zb_modelId[ZB_MODELID_FULL_SIZE] =
        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','x','x',0};
//                                                                                             18, 19
//uint8_t zb_modelId_arr[ZB_MODELID_ARR_NUM][ZB_MODELID_FULL_SIZE] = {
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','1',0},   // model1
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','2',0},   // model2
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','3',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','4',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','5',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','6',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','7',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','8',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','9',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','A',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','B',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','C',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','D',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','E',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','0','F',0},
//        {ZB_MODELID_SIZE, 'T','u','y','a','_','T','h','e','r','m','o','s','t','a','t','_','r','1','0',0},  // etc
//};

data_point_st_t data_point_model_common[DP_IDX_MAXNUM];

uint8_t remote_cmd_pkt_buff[DATA_MAX_LEN+12];
uint8_t dev_therm_mode = DEV_THERM_MODE_COLD;

//uint8_t w_mon = DAY_MON;
//uint8_t w_tue = DAY_TUE;
//uint8_t w_wed = DAY_WED;
//uint8_t w_thu = DAY_THU;
//uint8_t w_fri = DAY_FRI;
//uint8_t w_sat = DAY_SAT;
//uint8_t w_sun = DAY_SUN;
//uint8_t w_day;

args_get_schedule_t args_get_schedule_mon;
args_get_schedule_t args_get_schedule_tue;
args_get_schedule_t args_get_schedule_wed;
args_get_schedule_t args_get_schedule_thu;
args_get_schedule_t args_get_schedule_fri;
args_get_schedule_t args_get_schedule_sat;
args_get_schedule_t args_get_schedule_sun;
args_get_schedule_t args_get_schedule_any;

void (*answer_weekly_schedule[MANUF_NAME_MAX])(void *args) = {
   remote_cmd_get_schedule_1,
   remote_cmd_get_schedule_2,
   remote_cmd_get_schedule_3,
   remote_cmd_get_schedule_4,
   remote_cmd_get_schedule_5,
   remote_cmd_get_schedule_6,
   remote_cmd_get_schedule_7,
   remote_cmd_get_schedule_8,
   remote_cmd_get_schedule_9,
   remote_cmd_get_schedule_0A,
   remote_cmd_get_schedule_0B,
   remote_cmd_get_schedule_0C,
};

/*
 *
 *  common remote_cmd functions
 *
 */

//data_point_st_t* init_datapoint_model(manuf_name_t manuf_name) {
//
//    data_point_st_t *dp_model = NULL;
//
//    switch(manuf_name) {
//        case MANUF_NAME_1:
//            dp_model = init_datapoint_model1();
//            break;
//        case MANUF_NAME_2:
//            break;
//        case MANUF_NAME_3:
//            break;
//        case MANUF_NAME_4:
//            break;
//        case MANUF_NAME_5:
//            break;
//        case MANUF_NAME_6:
//            break;
//        case MANUF_NAME_7:
//            break;
//        case MANUF_NAME_8:
//            break;
//        case MANUF_NAME_9:
//            break;
//        case MANUF_NAME_0A:
//            dp_model = init_datapoint_model0A();
//            break;
//        case MANUF_NAME_0B:
//            dp_model = init_datapoint_model0B();
//            break;
//        default:
//            break;
//    }
//
//    return dp_model;
//}

void remote_cmd_sys_mode(void *args) {

    uint8_t *mode = (uint8_t*)args;

    if (*mode != SYS_MODE_OFF && *mode != SYS_MODE_HEAT) {
        return;
    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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

    if (*mode == SYS_MODE_OFF) {
        data_point->data[0] = 0x00;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_to_ring_cmd(out_pkt, true);
        set_seq_num(seq_num);
    } else if (*mode == SYS_MODE_HEAT) {
        data_point->data[0] = 0x01;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_to_ring_cmd(out_pkt, true);
        set_seq_num(seq_num);
    }

    thermostat_settings_save();
}

void remote_cmd_heating_set(void *args) {

    int16_t *arg = (int16_t*)args;
    int32_t temp = *arg;

    uint16_t len;
    int16_t  minHeatSet;
    int16_t  maxHeatSet;

    if(data_point_model[DP_IDX_SETPOINT].id == 0) return;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&minHeatSet);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&maxHeatSet);

//    printf("1.temp: %d, minHeatSet: %d, maxHeatSet: %d\r\n", temp, minHeatSet, maxHeatSet);

    if (temp < minHeatSet) temp = minHeatSet;
    if (temp > maxHeatSet) temp = maxHeatSet;

//    if (temp < minHeatSet || temp > maxHeatSet) {
//        return;
//    }

//    printf("2. temp: %d, minHeatSet: %d, maxHeatSet: %d\r\n", temp, minHeatSet, maxHeatSet);


    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    if (data_point_model[DP_IDX_SETPOINT].divisor == 1) {
        temp /= 100;
    } else if (data_point_model[DP_IDX_SETPOINT].divisor == 10) {
        temp /= 10;
    }

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_temp_calibration(void *args) {

    int8_t *arg = (int8_t*)args;
    int8_t temp = *arg;

    if(data_point_model[DP_IDX_CALIBRATION].id == 0) return;

    if (temp < data_point_model[DP_IDX_CALIBRATION].arg1) temp = data_point_model[DP_IDX_CALIBRATION].arg1;
    if (temp > data_point_model[DP_IDX_CALIBRATION].arg2) temp = data_point_model[DP_IDX_CALIBRATION].arg2;

//    if (temp < data_point_model[DP_IDX_CALIBRATION].arg1 || temp > data_point_model[DP_IDX_CALIBRATION].arg2) {
//        return;
//    }

//    if (temp < CLIENT_TEMP_CALIBRATION_MIN || temp > CLIENT_TEMP_CALIBRATION_MAX) {
//        return;
//    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    if (data_point_model[DP_IDX_CALIBRATION].divisor == -10) {
        temp /= 10;
    } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 10) {
        temp *= 10;
    }
//    temp /= 10; // 90 -> 9, -90 -> -9

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_keylock(void *args) {

    uint8_t *keylock = (uint8_t*)args;

    if(data_point_model[DP_IDX_LOCKUNLOCK].id == 0) return;

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    data_point->data[0] = *keylock;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_sensor_used(void *args) {

    uint8_t *sensor_used = (uint8_t*)args;

    if (data_point_model[DP_IDX_SENSOR].id == 0) return;

    if (*sensor_used != SENSOR_IN && *sensor_used != SENSOR_AL && *sensor_used != SENSOR_OU) {
        return;
    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    data_point->data[0] = *sensor_used;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_deadband(void *args) {

    uint8_t *arg = (uint8_t*)args;
    uint32_t hysteresis = *arg;

    if (data_point_model[DP_IDX_DEADZONE].id == 0) return;

    if (hysteresis < data_point_model[DP_IDX_DEADZONE].arg1) hysteresis = data_point_model[DP_IDX_DEADZONE].arg1;
    if (hysteresis > data_point_model[DP_IDX_DEADZONE].arg2) hysteresis = data_point_model[DP_IDX_DEADZONE].arg2;

//    if (hysteresis < data_point_model[DP_IDX_DEADZONE].arg1 || hysteresis > data_point_model[DP_IDX_DEADZONE].arg2) {
//        return;
//    }

//    if (hysteresis < HYSTERESIS_MIN || hysteresis > HYSTERESIS_MAX) {
//        return;
//    }

//    printf("hysteresis: %d\r\n", hysteresis);

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;


    if (data_point_model[DP_IDX_DEADZONE].divisor == 10) {
        hysteresis *= 10;
    } else if (data_point_model[DP_IDX_DEADZONE].divisor == 100) {
        hysteresis *= 100;
    }

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_min_setpoint(void *args) {

    uint16_t *arg = (uint16_t*)args;
    uint32_t min_temp = *arg;

//    printf("min_temp: %d\r\n", min_temp);

    if (data_point_model[DP_IDX_MIN].id == 0) return;

    if (min_temp < data_point_model[DP_IDX_MIN].arg1) min_temp = data_point_model[DP_IDX_MIN].arg1;
    if (min_temp > data_point_model[DP_IDX_MIN].arg2) min_temp = data_point_model[DP_IDX_MIN].arg2;

//    if (min_temp < data_point_model[DP_IDX_MIN].arg1 || min_temp > data_point_model[DP_IDX_MIN].arg2) {
//        return;
//    }

//    if (min_temp < SET_POINT_MIN_MIN * 100 || min_temp > SET_POINT_MIN_MAX * 100) {
//        return;
//    }

    min_temp /= 100; // 1500 -> 15°C

    if (data_point_model[DP_IDX_MAX].divisor == 10) {
        min_temp *= 10;
    } else if (data_point_model[DP_IDX_MAX].divisor == 100) {
        min_temp *= 100;
    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_MIN].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_MIN].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (min_temp >> 24) & 0xFF;
    data_point->data[1] = (min_temp >> 16) & 0xFF;
    data_point->data[2] = (min_temp >> 8)  & 0xFF;
    data_point->data[3] = min_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_max_setpoint(void *args) {

    uint16_t *arg = (uint16_t*)args;
    uint32_t max_temp = *arg;

//    printf("max_temp: %d\r\n", max_temp);

    if (data_point_model[DP_IDX_MAX].id == 0) return;

    if (max_temp < data_point_model[DP_IDX_MAX].arg1) max_temp = data_point_model[DP_IDX_MAX].arg1;
    if (max_temp > data_point_model[DP_IDX_MAX].arg2) max_temp = data_point_model[DP_IDX_MAX].arg2;

//    if (max_temp < data_point_model[DP_IDX_MAX].arg1 || max_temp > data_point_model[DP_IDX_MAX].arg2) {
//        return;
//    }

//    if (max_temp < SET_POINT_MAX_MIN * 100 || max_temp > SET_POINT_MAX_MAX * 100) {
//        return;
//    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    max_temp /= 100; // 4400 -> 44°C

    if (data_point_model[DP_IDX_MAX].divisor == 10) {
        max_temp *= 10;
    } else if (data_point_model[DP_IDX_MAX].divisor == 100) {
        max_temp *= 100;
    }

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

/*
 *
 *  common local_cmd functions
 *
 */

void local_cmd_inner_sensor(void *args) {

    int16_t *temp = (int16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_TEMP].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_TEMP].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMPERATURE, (uint8_t*)temp);

#if UART_PRINTF_MODE && DEBUG_CMD
            printf("Local Temperature: %d\r\n", *temp);
#endif

}

void local_cmd_heating_set(void *args) {

    uint16_t *temp = (uint16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_SETPOINT].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_SETPOINT].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT, (uint8_t*)temp);

    thermostat_settings_save();
}

void local_cmd_min_setpoint(void *args) {

    int16_t *temp = (int16_t*)args;

    uint16_t divisor = 1;
    int16_t  old_min;
    uint16_t len;

    if (data_point_model[DP_IDX_MIN].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_MIN].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&old_min);

//                            printf("temp: %d, old_min: %d", temp, old_min);

    if (old_min != *temp) {

        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, (uint8_t*)temp);

        thermostat_settings_save();
    }
}

void local_cmd_max_setpoint(void *args) {

    int16_t *temp = (int16_t*)args;

    uint16_t divisor = 1;
    int16_t  absMinHeatSet;
    int16_t  absMaxHeatSet;
    int16_t  old_max;
    uint16_t len;
    bool set_attr = false;

    if (data_point_model[DP_IDX_MAX].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_MAX].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_ABS_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&absMinHeatSet);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_ABS_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&absMaxHeatSet);

//    printf("temp: %d, absMinHeatSet: %d, absMaxHeatSet: %d\r\n", *temp, absMinHeatSet, absMaxHeatSet);

    if (*temp > absMaxHeatSet) {
        *temp = absMaxHeatSet;
        set_attr = true;
    }
    if (*temp < absMinHeatSet) {
        *temp = absMinHeatSet;
        set_attr = true;
    }

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&old_max);

    printf("old_max: %d, temp: %d\r\n", old_max, *temp);

    if (old_max != *temp) {
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, (uint8_t*)temp);

        thermostat_settings_save();
    }

    if (set_attr) {
        data_point_model[DP_IDX_MAX].remote_cmd(temp);
    }
}

void local_cmd_deadband(void *args) {

    int16_t *temp = (int16_t*)args;

    if (data_point_model[DP_IDX_DEADZONE].divisor == 10) {
        *temp /= 10;
    } else if (data_point_model[DP_IDX_DEADZONE].divisor == 100) {
        *temp /= 100;
    }

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND, (uint8_t*)temp);

    thermostat_settings_save();
}

void local_cmd_temp_calibration(void *args) {

    int8_t *temp = (int8_t*)args;

    if (data_point_model[DP_IDX_CALIBRATION].divisor == -10) {
        *temp *= 10;
    } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 10) {
        *temp /= 10;
    }

//    if (data_point_model[DP_IDX_CALIBRATION].divisor == 1) {
//        *temp *= 10;
//    } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 100) {
//        *temp /= 10;
//    }

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION, (uint8_t*)temp);

    thermostat_settings_save();
}

void local_cmd_keylock(void *args) {

    uint8_t *lock = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG, ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT, (uint8_t*)lock);

    thermostat_settings_save();
}

void local_cmd_sensor_used(void *args) {

    uint8_t *sensor_used = (uint8_t*)args;

//    if (sensor_used == SENSOR_IN) {
////                                printf("sensor IN\r\n");
//    } else if (sensor_used == SENSOR_AL) {
////                                printf("sensor AL\r\n");
//    } else {
////                                printf("sensor OU\r\n");
//    }

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED, (uint8_t*)sensor_used);

    thermostat_settings_save();
}

void local_cmd_set_run_state(void *args) {

    run_state_bit_t *run_state_bit = (run_state_bit_t*)args;

    uint16_t runState;
    uint16_t len;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE, &len, (uint8_t*)&runState);

    if (run_state_bit->set) {
        runState |= (1 << run_state_bit->bit_num);
    } else {
        runState &= ~( 1 << run_state_bit->bit_num);
    }

    zcl_setAttrVal(APP_ENDPOINT1,
                   ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE,
                   (uint8_t*)&runState);

}

void local_cmd_onoff_state(void *args) {

    uint8_t *onoff = (uint8_t*)args;
    run_state_bit_t run_state_bit;
    uint8_t sys_mode;

    if (*onoff == DEV_POWER_OFF) {
#if UART_PRINTF_MODE /* && DEBUG_CMD*/
        printf("Power OFF\r\n");
#endif
        sys_mode = SYS_MODE_OFF;
        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);
        run_state_bit.bit_num = RUN_STATE_HEAT_BIT;
        run_state_bit.set = OFF;
        local_cmd_set_run_state(&run_state_bit);
    } else {
#if UART_PRINTF_MODE /*&& DEBUG_CMD*/
        printf("Power ON\r\n");
#endif
        sys_mode = SYS_MODE_HEAT;
        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);
    }

    thermostat_settings_save();
}


/*****************************************************************************************************/

//void set_zcl_modelId(uint8_t *signature) {
//    uint8_t modelId[ZCL_BASIC_MAX_LENGTH] = {0};
//    uint8_t name[ZCL_BASIC_MAX_LENGTH-1] = {0};
//
//    strncpy((char*)name, STR_MODEL_ID_BEGIN, STR_MODEL_ID_BEGIN_LEN);
//    strncpy((char*)name+STR_MODEL_ID_BEGIN_LEN, (char*)signature, 8);
//
//    set_zcl_str(name, modelId, ZCL_BASIC_MAX_LENGTH);
//
//    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_BASIC, ZCL_ATTRID_BASIC_MODEL_ID, modelId);
//}

/*****************************************************************************************************/

