#include "app_main.h"

/* data point for manufacturer id -
 * "_TZE204_lpedvtvr"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */

#define R0D_ABS_HEAT_MIN      500 // * 100
#define R0D_ABS_HEAT_MAX      4500 // * 100
#define R0D_ECO_HEAT_MIN      1000 // * 100
#define R0D_ECO_HEAT_MAX      3000 // * 100
#define R0D_HEAT_MIN_MIN      500 // * 100
#define R0D_HEAT_MIN_MAX      1500 // * 100
#define R0D_HEAT_MAX_MIN      3500 // * 100
#define R0D_HEAT_MAX_MAX      4500 // * 100
#define R0D_FROST_PROTECT_MIN 0
#define R0D_FROST_PROTECT_MAX 1000
#define R0D_HEAT_PROTECT_MIN  2500 // * 100
#define R0D_HEAT_PROTECT_MAX  7000 // * 100
#define R0D_DEADZONE_MIN      5 // * 10
#define R0D_DEADZONE_MAX      50 // * 10
#define R0D_CALIBRATION_MIN   -100 // * 10
#define R0D_CALIBRATION_MAX   100 // * 10

#define BRIGHTNESS_LEVELS 4
static const uint8_t brightness_levels[BRIGHTNESS_LEVELS] =
    {0, 5, 25, 100}; // Off, Low, Medium, High

data_point_st_t* init_datapoint_model0D() {
    memset(data_point_model_common, 0, sizeof(data_point_model_common));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = R0D_ABS_HEAT_MIN; // min +5°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = R0D_ABS_HEAT_MAX; // max +45°C

    data_point_model_common[DP_IDX_ONOFF].id = DP_TYPE0D_ID_01;
    data_point_model_common[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model_common[DP_IDX_ONOFF].len = 1;
    data_point_model_common[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_0D;
    data_point_model_common[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_0D;

    data_point_model_common[DP_IDX_TEMP].id = DP_TYPE0D_ID_10;
    data_point_model_common[DP_IDX_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP].len = 4;
    data_point_model_common[DP_IDX_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_0D;

    data_point_model_common[DP_IDX_TEMP_OUT].id = DP_TYPE0D_ID_6D;
    data_point_model_common[DP_IDX_TEMP_OUT].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP_OUT].len = 4;
    data_point_model_common[DP_IDX_TEMP_OUT].divisor = 10;
    data_point_model_common[DP_IDX_TEMP_OUT].local_cmd = local_cmd_outdoor_sensor_0D;

    data_point_model_common[DP_IDX_SETPOINT].id = DP_TYPE0D_ID_32;
    data_point_model_common[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model_common[DP_IDX_SETPOINT].len = 4;
    data_point_model_common[DP_IDX_SETPOINT].divisor = 10;
    data_point_model_common[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_0D;
    data_point_model_common[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_0D;

    data_point_model_common[DP_IDX_MIN].id = DP_TYPE0D_ID_12;
    data_point_model_common[DP_IDX_MIN].type = DP_VAL;
    data_point_model_common[DP_IDX_MIN].len = 4;
    data_point_model_common[DP_IDX_MIN].divisor = 10;
    data_point_model_common[DP_IDX_MIN].remote_cmd = remote_cmd_min_setpoint_0D;
    data_point_model_common[DP_IDX_MIN].local_cmd = local_cmd_min_setpoint_0D;
    data_point_model_common[DP_IDX_MIN].arg1 = R0D_HEAT_MIN_MIN;
    data_point_model_common[DP_IDX_MIN].arg2 = R0D_HEAT_MIN_MAX;

    data_point_model_common[DP_IDX_MAX].id = DP_TYPE0D_ID_22;
    data_point_model_common[DP_IDX_MAX].type = DP_VAL;
    data_point_model_common[DP_IDX_MAX].len = 4;
    data_point_model_common[DP_IDX_MAX].divisor = 10;
    data_point_model_common[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_0D;
    data_point_model_common[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_0D;
    data_point_model_common[DP_IDX_MAX].arg1 = R0D_HEAT_MAX_MIN;
    data_point_model_common[DP_IDX_MAX].arg2 = R0D_HEAT_MAX_MAX;

    data_point_model_common[DP_IDX_DEADZONE].id = DP_TYPE0D_ID_6E;
    data_point_model_common[DP_IDX_DEADZONE].type = DP_VAL;
    data_point_model_common[DP_IDX_DEADZONE].len = 4;
    data_point_model_common[DP_IDX_DEADZONE].divisor = 1;
    data_point_model_common[DP_IDX_DEADZONE].remote_cmd = remote_cmd_deadband_0D;
    data_point_model_common[DP_IDX_DEADZONE].local_cmd = local_cmd_deadband_0D;
    data_point_model_common[DP_IDX_DEADZONE].arg1 = R0D_DEADZONE_MIN;
    data_point_model_common[DP_IDX_DEADZONE].arg2 = R0D_DEADZONE_MAX;

    data_point_model_common[DP_IDX_CALIBRATION].id = DP_TYPE0D_ID_65;
    data_point_model_common[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model_common[DP_IDX_CALIBRATION].len = 4;
    data_point_model_common[DP_IDX_CALIBRATION].divisor = -10;
    data_point_model_common[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_0D;
    data_point_model_common[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_0D;
    data_point_model_common[DP_IDX_CALIBRATION].arg1 = R0D_CALIBRATION_MIN;
    data_point_model_common[DP_IDX_CALIBRATION].arg2 = R0D_CALIBRATION_MAX;

    data_point_model_common[DP_IDX_RUNSTATE].id = DP_TYPE0D_ID_2F;
    data_point_model_common[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model_common[DP_IDX_RUNSTATE].len = 1;
    data_point_model_common[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_0D;

    data_point_model_common[DP_IDX_SENSOR].id = DP_TYPE0D_ID_20;
    data_point_model_common[DP_IDX_SENSOR].type = DP_ENUM;
    data_point_model_common[DP_IDX_SENSOR].len = 1;
    data_point_model_common[DP_IDX_SENSOR].remote_cmd = remote_cmd_sensor_used_0D;
    data_point_model_common[DP_IDX_SENSOR].local_cmd = local_cmd_sensor_used_0D;

    data_point_model_common[DP_IDX_PROG].id = DP_TYPE0D_ID_02;
    data_point_model_common[DP_IDX_PROG].type = DP_ENUM;
    data_point_model_common[DP_IDX_PROG].len = 1;
    data_point_model_common[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_0D;
    data_point_model_common[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_0D;

    data_point_model_common[DP_IDX_LOCKUNLOCK].id = DP_TYPE0D_ID_27;
    data_point_model_common[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model_common[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_0D;
    data_point_model_common[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_0D;

    data_point_model_common[DP_IDX_LEVEL_A].id = DP_TYPE0D_ID_30;
    data_point_model_common[DP_IDX_LEVEL_A].type = DP_VAL;
    data_point_model_common[DP_IDX_LEVEL_A].len = 4;
    data_point_model_common[DP_IDX_LEVEL_A].divisor = 1;
    data_point_model_common[DP_IDX_LEVEL_A].remote_cmd = remote_cmd_level_0D;
    data_point_model_common[DP_IDX_LEVEL_A].local_cmd = local_cmd_level_0D;

    data_point_model_common[DP_IDX_SCREEN_TIME].id = DP_TYPE0D_ID_72;
    data_point_model_common[DP_IDX_SCREEN_TIME].type = DP_ENUM;
    data_point_model_common[DP_IDX_SCREEN_TIME].len = 1;
    data_point_model_common[DP_IDX_SCREEN_TIME].remote_cmd = remote_cmd_screen_off_time_0D;
    data_point_model_common[DP_IDX_SCREEN_TIME].local_cmd = local_cmd_screen_off_time_0D;

    data_point_model_common[DP_IDX_LED_INDICATOR].id = DP_TYPE0D_ID_73;
    data_point_model_common[DP_IDX_LED_INDICATOR].type = DP_BOOL;
    data_point_model_common[DP_IDX_LED_INDICATOR].len = 1;
    data_point_model_common[DP_IDX_LED_INDICATOR].remote_cmd = remote_cmd_led_indicator_0D;
    data_point_model_common[DP_IDX_LED_INDICATOR].local_cmd = local_cmd_led_indicator_0D;

    data_point_model_common[DP_IDX_FROST_PROTECT].id = DP_TYPE0D_ID_70;
    data_point_model_common[DP_IDX_FROST_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_FROST_PROTECT].len = 4;
    data_point_model_common[DP_IDX_FROST_PROTECT].divisor = 10;
    data_point_model_common[DP_IDX_FROST_PROTECT].remote_cmd = remote_cmd_frost_protect_0C;
    data_point_model_common[DP_IDX_FROST_PROTECT].local_cmd = local_cmd_frost_protect_0C;
    data_point_model_common[DP_IDX_FROST_PROTECT].arg1 = R0D_FROST_PROTECT_MIN;
    data_point_model_common[DP_IDX_FROST_PROTECT].arg2 = R0D_FROST_PROTECT_MAX;

    data_point_model_common[DP_IDX_HEAT_PROTECT].id = DP_TYPE0D_ID_6F;
    data_point_model_common[DP_IDX_HEAT_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_HEAT_PROTECT].len = 4;
    data_point_model_common[DP_IDX_HEAT_PROTECT].divisor = 10;
    data_point_model_common[DP_IDX_HEAT_PROTECT].remote_cmd = remote_cmd_heat_protect_0D;
    data_point_model_common[DP_IDX_HEAT_PROTECT].local_cmd = local_cmd_heat_protect_0D;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg1 = R0D_HEAT_PROTECT_MIN;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg2 = R0D_HEAT_PROTECT_MAX;

    data_point_model_common[DP_IDX_ECO_COOL_TEMP].id = DP_TYPE0D_ID_71;
    data_point_model_common[DP_IDX_ECO_COOL_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_ECO_COOL_TEMP].len = 4;
    data_point_model_common[DP_IDX_ECO_COOL_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_ECO_COOL_TEMP].remote_cmd = remote_cmd_eco_mode_temp_0D;
    data_point_model_common[DP_IDX_ECO_COOL_TEMP].local_cmd = local_cmd_eco_mode_temp_0D;
    data_point_model_common[DP_IDX_ECO_COOL_TEMP].arg1 = R0D_ECO_HEAT_MIN;
    data_point_model_common[DP_IDX_ECO_COOL_TEMP].arg2 = R0D_ECO_HEAT_MAX;

    data_point_model_common[DP_IDX_SETTINGS_RESET].id = DP_TYPE0D_ID_1C;
    data_point_model_common[DP_IDX_SETTINGS_RESET].type = DP_BOOL;
    data_point_model_common[DP_IDX_SETTINGS_RESET].len = 1;
    data_point_model_common[DP_IDX_SETTINGS_RESET].remote_cmd = remote_cmd_setting_reset_0D;
    data_point_model_common[DP_IDX_SETTINGS_RESET].local_cmd = local_cmd_setting_reset_0D;

    data_point_model_common[DP_IDX_SCHEDULE].id = DP_TYPE0D_ID_00;
    data_point_model_common[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_0D;

    data_point_model_common[DP_IDX_SCHEDULE_MON].id = DP_TYPE0D_ID_66;
    data_point_model_common[DP_IDX_SCHEDULE_MON].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_MON].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_MON].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_MON].local_cmd = local_cmd_set_schedule_0D;

    data_point_model_common[DP_IDX_SCHEDULE_TUE].id = DP_TYPE0D_ID_67;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].local_cmd = local_cmd_set_schedule_0D;

    data_point_model_common[DP_IDX_SCHEDULE_WED].id = DP_TYPE0D_ID_68;
    data_point_model_common[DP_IDX_SCHEDULE_WED].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_WED].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_WED].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_WED].local_cmd = local_cmd_set_schedule_0D;

    data_point_model_common[DP_IDX_SCHEDULE_THU].id = DP_TYPE0D_ID_69;
    data_point_model_common[DP_IDX_SCHEDULE_THU].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_THU].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_THU].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_THU].local_cmd = local_cmd_set_schedule_0D;

    data_point_model_common[DP_IDX_SCHEDULE_FRI].id = DP_TYPE0D_ID_6A;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].local_cmd = local_cmd_set_schedule_0D;

    data_point_model_common[DP_IDX_SCHEDULE_SAT].id = DP_TYPE0D_ID_6B;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].local_cmd = local_cmd_set_schedule_0D;

    data_point_model_common[DP_IDX_SCHEDULE_SUN].id = DP_TYPE0D_ID_6C;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].local_cmd = local_cmd_set_schedule_0D;

    return data_point_model_common;
}

/*
 *
 * Local variables and functions
 *
 */

void remote_cmd_oper_mode_0D(void* args) {
    uint8_t* mode = (uint8_t*)args;

    if(data_point_model[DP_IDX_PROG].id == 0) return;

    switch(*mode) {
    case 0: // setpoint (0) -> 0
        break;
    case 3: // schedule_with_preheat (3) -> 1
        *mode = 1;
        break;
    case 1: // schedule (1) -> 2
        *mode = 2;
        break;
    case 4: // eco (4) -> 3
        *mode = 3;
        break;
    default:
        return;
    }

    pkt_tuya_t* out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t* data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_PROG].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_PROG].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *mode;
    out_pkt->pkt_len++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void local_cmd_oper_mode_0D(void* args) {
    uint8_t* mode = (uint8_t*)args;

    switch(*mode) {
    case 0: // 0 -> setpoint (0)
        break;
    case 1: // 1 -> schedule_with_preheat (3)
        *mode = 3;
        break;
    case 2: // 2 -> schedule (1)
        *mode = 1;
        break;
    case 3: // 3 -> eco (4)
        *mode = 4;
        break;
    default:
        return;
    }

    zcl_setAttrVal(
        APP_ENDPOINT1,
        ZCL_CLUSTER_HAVC_THERMOSTAT,
        ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE,
        mode);

    thermostat_settings_save();
}

void remote_cmd_level_0D(void* args) {
    uint8_t* level = (uint8_t*)args;

    if(*level < 0 || *level >= BRIGHTNESS_LEVELS) return;
    uint8_t level_id = *level;
    *level = brightness_levels[level_id];

#if UART_PRINTF_MODE && DEBUG_CMD
    printf("Brightness remote: %d -> %d\r\n", level_id, *level);
#endif

    zcl_setAttrVal(
        APP_ENDPOINT1,
        ZCL_CLUSTER_HAVC_THERMOSTAT,
        ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_LEVEL,
        (uint8_t*)level);

    pkt_tuya_t* out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t* data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LEVEL_A].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LEVEL_A].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (*level >> 24) & 0xFF;
    data_point->data[1] = (*level >> 16) & 0xFF;
    data_point->data[2] = (*level >> 8) & 0xFF;
    data_point->data[3] = *level & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void local_cmd_level_0D(void* args) {
    uint16_t* level = (uint16_t*)args;

    uint8_t level_id = 0;
    for(uint8_t i = 0; i < BRIGHTNESS_LEVELS; i++) {
        if(*level <= brightness_levels[i]) {
            level_id = i;
            break;
        }
    }

#if UART_PRINTF_MODE && DEBUG_CMD
    printf("Brightness local: %d -> %d\r\n", *level, level_id);
#endif

    *level = level_id;

    zcl_setAttrVal(
        APP_ENDPOINT1,
        ZCL_CLUSTER_HAVC_THERMOSTAT,
        ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_LEVEL,
        (uint8_t*)level);

    thermostat_settings_save();
}

void remote_cmd_screen_off_time_0D(void* args) {
    uint8_t* mode = (uint8_t*)args;

#if UART_PRINTF_MODE && DEBUG_CMD
    printf("Screen off time remote: %d\r\n", *mode);
#endif

    zcl_setAttrVal(
        APP_ENDPOINT1,
        ZCL_CLUSTER_HAVC_THERMOSTAT,
        ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SCREEN_OFF_TIME,
        (uint8_t*)mode);

    pkt_tuya_t* out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t* data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCREEN_TIME].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCREEN_TIME].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *mode & 0xFF;
    out_pkt->pkt_len += 1;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void local_cmd_screen_off_time_0D(void* args) {
    uint16_t* mode = (uint16_t*)args;

#if UART_PRINTF_MODE && DEBUG_CMD
    printf("Screen off time local: %d\r\n", *mode);
#endif

    zcl_setAttrVal(
        APP_ENDPOINT1,
        ZCL_CLUSTER_HAVC_THERMOSTAT,
        ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SCREEN_OFF_TIME,
        (uint8_t*)mode);

    thermostat_settings_save();
}

void remote_cmd_led_indicator_0D(void* args) {
    uint8_t* mode = (uint8_t*)args;

    if(*mode > 1) return;

#if UART_PRINTF_MODE && DEBUG_CMD
    printf("LED indicator remote: %d\r\n", *mode);
#endif

    zcl_setAttrVal(
        APP_ENDPOINT1,
        ZCL_CLUSTER_HAVC_THERMOSTAT,
        ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_LED_INDICATOR,
        (uint8_t*)mode);

    pkt_tuya_t* out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t* data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LED_INDICATOR].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LED_INDICATOR].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *mode & 0xFF;
    out_pkt->pkt_len += 1;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void local_cmd_led_indicator_0D(void* args) {
    uint16_t* mode = (uint16_t*)args;

#if UART_PRINTF_MODE && DEBUG_CMD
    printf("LED indicator local: %d\r\n", *mode);
#endif

    zcl_setAttrVal(
        APP_ENDPOINT1,
        ZCL_CLUSTER_HAVC_THERMOSTAT,
        ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_LED_INDICATOR,
        (uint8_t*)mode);

    thermostat_settings_save();
}
