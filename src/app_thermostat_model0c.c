#include "app_main.h"

/* data point for manufacturer id -
 * "szbxmorb"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */

#define R0C_ABS_HEAT_MIN            500
#define R0C_ABS_HEAT_MAX            4500
#define R0C_HEAT_MIN_MIN            500         // * 100
#define R0C_HEAT_MIN_MAX            1500        // * 100
#define R0C_HEAT_MAX_MIN            1500        // * 100
#define R0C_HEAT_MAX_MAX            4500        // * 100
#define R0C_FROST_PROTECT_MIN       0
#define R0C_FROST_PROTECT_MAX       1000
#define R0C_HEAT_PROTECT_MIN        2500        // * 100
#define R0C_HEAT_PROTECT_MAX        7000        // * 100
#define R0C_DEADZONE_MIN            1
#define R0C_DEADZONE_MAX            5
#define R0C_CALIBRATION_MIN        -120         // * 10
#define R0C_CALIBRATION_MAX         120         // * 10
#define R0C_HUMIDITY_MIN            0           // * 100
#define R0C_HUMIDITY_MAX            10000       // * 100
#define R0C_HUMIDITY_OFFSET_MIN    -9500        // * 100
#define R0C_HUMIDITY_OFFSET_MAX     9500        // * 100

//data_point_st_t data_point_model4[DP_IDX_MAXNUM];

data_point_st_t *init_datapoint_model0C() {

    memset(data_point_model_common, 0, sizeof(data_point_model_common));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = R0C_ABS_HEAT_MIN;       // min +5°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = R0C_ABS_HEAT_MAX;       // max +45°C

    data_point_model_common[DP_IDX_ONOFF].id = DP_TYPE0C_ID_01;
    data_point_model_common[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model_common[DP_IDX_ONOFF].len = 1;
    data_point_model_common[DP_IDX_ONOFF].divisor = 1;
    data_point_model_common[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_0C;
    data_point_model_common[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_0C;

    data_point_model_common[DP_IDX_TEMP].id = DP_TYPE0C_ID_18;
    data_point_model_common[DP_IDX_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP].len = 4;
    data_point_model_common[DP_IDX_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_0C;

    data_point_model_common[DP_IDX_SETPOINT].id = DP_TYPE0C_ID_10;
    data_point_model_common[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model_common[DP_IDX_SETPOINT].len = 4;
    data_point_model_common[DP_IDX_SETPOINT].divisor = 10;
    data_point_model_common[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_0C;
    data_point_model_common[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_0C;

    data_point_model_common[DP_IDX_MIN].id = DP_TYPE0C_ID_1A;
    data_point_model_common[DP_IDX_MIN].type = DP_VAL;
    data_point_model_common[DP_IDX_MIN].len = 4;
    data_point_model_common[DP_IDX_MIN].divisor = 10;
    data_point_model_common[DP_IDX_MIN].remote_cmd = remote_cmd_min_setpoint_0C;
    data_point_model_common[DP_IDX_MIN].local_cmd = local_cmd_min_setpoint_0C;
    data_point_model_common[DP_IDX_MIN].arg1 = R0C_HEAT_MIN_MIN;
    data_point_model_common[DP_IDX_MIN].arg2 = R0C_HEAT_MIN_MAX;

    data_point_model_common[DP_IDX_MAX].id = DP_TYPE0C_ID_13;
    data_point_model_common[DP_IDX_MAX].type = DP_VAL;
    data_point_model_common[DP_IDX_MAX].len = 4;
    data_point_model_common[DP_IDX_MAX].divisor = 10;
    data_point_model_common[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_0C;
    data_point_model_common[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_0C;
    data_point_model_common[DP_IDX_MAX].arg1 = R0C_HEAT_MAX_MIN;
    data_point_model_common[DP_IDX_MAX].arg2 = R0C_HEAT_MAX_MAX;

    data_point_model_common[DP_IDX_DEADZONE].id = DP_TYPE0C_ID_67;
    data_point_model_common[DP_IDX_DEADZONE].type = DP_VAL;
    data_point_model_common[DP_IDX_DEADZONE].len = 4;
    data_point_model_common[DP_IDX_DEADZONE].divisor = 1;
    data_point_model_common[DP_IDX_DEADZONE].remote_cmd = remote_cmd_deadband_0C;
    data_point_model_common[DP_IDX_DEADZONE].local_cmd = local_cmd_deadband_0C;
    data_point_model_common[DP_IDX_DEADZONE].arg1 = R0C_DEADZONE_MIN;
    data_point_model_common[DP_IDX_DEADZONE].arg2 = R0C_DEADZONE_MAX;

    data_point_model_common[DP_IDX_CALIBRATION].id = DP_TYPE0C_ID_1B;
    data_point_model_common[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model_common[DP_IDX_CALIBRATION].len = 4;
    data_point_model_common[DP_IDX_CALIBRATION].divisor = -10;
    data_point_model_common[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_0C;
    data_point_model_common[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_0C;
    data_point_model_common[DP_IDX_CALIBRATION].arg1 = R0C_CALIBRATION_MIN;
    data_point_model_common[DP_IDX_CALIBRATION].arg2 = R0C_CALIBRATION_MAX;

    data_point_model_common[DP_IDX_RUNSTATE].id = DP_TYPE0C_ID_24;
    data_point_model_common[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model_common[DP_IDX_RUNSTATE].len = 1;
    data_point_model_common[DP_IDX_RUNSTATE].divisor = 1;
    data_point_model_common[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_0C;

    data_point_model_common[DP_IDX_SENSOR].id = DP_TYPE0C_ID_66;
    data_point_model_common[DP_IDX_SENSOR].type = DP_ENUM;
    data_point_model_common[DP_IDX_SENSOR].len = 1;
    data_point_model_common[DP_IDX_SENSOR].divisor = 1;
    data_point_model_common[DP_IDX_SENSOR].remote_cmd = remote_cmd_sensor_used_0C;
    data_point_model_common[DP_IDX_SENSOR].local_cmd = local_cmd_sensor_used_0C;

    data_point_model_common[DP_IDX_PROG].id = DP_TYPE0C_ID_02;
    data_point_model_common[DP_IDX_PROG].type = DP_ENUM;
    data_point_model_common[DP_IDX_PROG].len = 1;
    data_point_model_common[DP_IDX_PROG].divisor = 1;
    data_point_model_common[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_0C;
    data_point_model_common[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_0C;

    data_point_model_common[DP_IDX_LOCKUNLOCK].id = DP_TYPE0C_ID_28;
    data_point_model_common[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model_common[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].divisor = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_0C;
    data_point_model_common[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_0C;

    data_point_model_common[DP_IDX_SCHEDULE].id = DP_TYPE0C_ID_00;
    data_point_model_common[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_0C;

    data_point_model_common[DP_IDX_TEMP_OUT].id = DP_TYPE0C_ID_71;
    data_point_model_common[DP_IDX_TEMP_OUT].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP_OUT].len = 4;
    data_point_model_common[DP_IDX_TEMP_OUT].divisor = 10;
    data_point_model_common[DP_IDX_TEMP_OUT].local_cmd = local_cmd_outdoor_sensor_0C;

    data_point_model_common[DP_IDX_FROST_PROTECT].id = DP_TYPE0C_ID_75;
    data_point_model_common[DP_IDX_FROST_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_FROST_PROTECT].len = 4;
    data_point_model_common[DP_IDX_FROST_PROTECT].divisor = 1;
    data_point_model_common[DP_IDX_FROST_PROTECT].remote_cmd = remote_cmd_frost_protect_0C;
    data_point_model_common[DP_IDX_FROST_PROTECT].local_cmd = local_cmd_frost_protect_0C;
    data_point_model_common[DP_IDX_FROST_PROTECT].arg1 = R0C_FROST_PROTECT_MIN;
    data_point_model_common[DP_IDX_FROST_PROTECT].arg2 = R0C_FROST_PROTECT_MAX;

    data_point_model_common[DP_IDX_HEAT_PROTECT].id = DP_TYPE0C_ID_74;
    data_point_model_common[DP_IDX_HEAT_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_HEAT_PROTECT].len = 4;
    data_point_model_common[DP_IDX_HEAT_PROTECT].divisor = 1;
    data_point_model_common[DP_IDX_HEAT_PROTECT].remote_cmd = remote_cmd_heat_protect_0C;
    data_point_model_common[DP_IDX_HEAT_PROTECT].local_cmd = local_cmd_heat_protect_0C;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg1 = R0C_HEAT_PROTECT_MIN;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg2 = R0C_HEAT_PROTECT_MAX;

    data_point_model_common[DP_IDX_SCHEDULE_MON].id = DP_TYPE0C_ID_70;
    data_point_model_common[DP_IDX_SCHEDULE_MON].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_MON].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_MON].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_MON].local_cmd = local_cmd_set_schedule_0C;

    data_point_model_common[DP_IDX_SCHEDULE_TUE].id = DP_TYPE0C_ID_6F;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].local_cmd = local_cmd_set_schedule_0C;

    data_point_model_common[DP_IDX_SCHEDULE_WED].id = DP_TYPE0C_ID_6E;
    data_point_model_common[DP_IDX_SCHEDULE_WED].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_WED].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_WED].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_WED].local_cmd = local_cmd_set_schedule_0C;

    data_point_model_common[DP_IDX_SCHEDULE_THU].id = DP_TYPE0C_ID_6D;
    data_point_model_common[DP_IDX_SCHEDULE_THU].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_THU].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_THU].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_THU].local_cmd = local_cmd_set_schedule_0C;

    data_point_model_common[DP_IDX_SCHEDULE_FRI].id = DP_TYPE0C_ID_6C;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].local_cmd = local_cmd_set_schedule_0C;

    data_point_model_common[DP_IDX_SCHEDULE_SAT].id = DP_TYPE0C_ID_6B;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].local_cmd = local_cmd_set_schedule_0C;

    data_point_model_common[DP_IDX_SCHEDULE_SUN].id = DP_TYPE0C_ID_6A;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].local_cmd = local_cmd_set_schedule_0C;

    data_point_model_common[DP_IDX_LEVEL_A].id = DP_TYPE0C_ID_73;
    data_point_model_common[DP_IDX_LEVEL_A].type = DP_VAL;
    data_point_model_common[DP_IDX_LEVEL_A].len = 4;
    data_point_model_common[DP_IDX_LEVEL_A].remote_cmd = remote_cmd_level_0C;
    data_point_model_common[DP_IDX_LEVEL_A].local_cmd = local_cmd_level_0C;

    data_point_model_common[DP_IDX_ECO_MODE].id = DP_TYPE0C_ID_04;
    data_point_model_common[DP_IDX_ECO_MODE].type = DP_BOOL;
    data_point_model_common[DP_IDX_ECO_MODE].len = 1;
    data_point_model_common[DP_IDX_ECO_MODE].remote_cmd = remote_cmd_eco_mode_0C;
    data_point_model_common[DP_IDX_ECO_MODE].local_cmd = local_cmd_eco_mode_0C;

    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].id = DP_TYPE0C_ID_69;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].len = 4;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].remote_cmd = remote_cmd_eco_mode_temp_0C;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].local_cmd = local_cmd_eco_mode_temp_0C;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].arg1 = R0C_ABS_HEAT_MIN;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].arg2 = R0C_ABS_HEAT_MAX;

    data_point_model_common[DP_IDX_HUMIDITY].id = DP_TYPE0C_ID_68;
    data_point_model_common[DP_IDX_HUMIDITY].type = DP_VAL;
    data_point_model_common[DP_IDX_HUMIDITY].len = 4;
    data_point_model_common[DP_IDX_HUMIDITY].divisor = 1;
    data_point_model_common[DP_IDX_HUMIDITY].local_cmd = local_cmd_humidity_0C;
    data_point_model_common[DP_IDX_HUMIDITY].arg1 = R0C_HUMIDITY_MIN;
    data_point_model_common[DP_IDX_HUMIDITY].arg2 = R0C_HUMIDITY_MAX;

    data_point_model_common[DP_IDX_HUMIDITY_OFFSET].id = DP_TYPE0C_ID_65;
    data_point_model_common[DP_IDX_HUMIDITY_OFFSET].type = DP_VAL;
    data_point_model_common[DP_IDX_HUMIDITY_OFFSET].len = 4;
    data_point_model_common[DP_IDX_HUMIDITY_OFFSET].divisor = 1;
    data_point_model_common[DP_IDX_HUMIDITY_OFFSET].remote_cmd = remote_cmd_humidity_offset_0C;
    data_point_model_common[DP_IDX_HUMIDITY_OFFSET].local_cmd = local_cmd_humidity_offset_0C;
    data_point_model_common[DP_IDX_HUMIDITY_OFFSET].arg1 = R0C_HUMIDITY_OFFSET_MIN;
    data_point_model_common[DP_IDX_HUMIDITY_OFFSET].arg2 = R0C_HUMIDITY_OFFSET_MAX;

    return data_point_model_common;
}

//data_point_st_t data_point_model4[DP_IDX_MAXNUM] = {
//        {DP_TYPE0C_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_4, local_cmd_onoff_state_4},                // onoff
//        {DP_TYPE0C_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_4},                                // local temperature
//        {DP_TYPE0C_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_4, local_cmd_heating_set_4},             // heat setpoint
//        {DP_TYPE0C_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_4, local_cmd_min_setpoint_4},           // min heat setpoint
//        {DP_TYPE0C_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_4, local_cmd_max_setpoint_4},           // max heat setpoint
//        {DP_TYPE0C_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_4, local_cmd_deadband_4},                   // hysteresis
//        {DP_TYPE0C_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_4, local_cmd_temp_calibration_4},   // local temperature calibration
//        {DP_TYPE0C_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_4},                       // 0x00 - heat, 0x01 - idle
//        {DP_TYPE0C_ID_66, DP_ENUM, 1,    1,  remote_cmd_sensor_used_4, local_cmd_sensor_used_4},     // sensor IN/AL/OU
//        {DP_TYPE0C_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_4, local_cmd_oper_mode_4},         // manual (setpoint) / programming (schedule)
//        {DP_TYPE0C_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_4, local_cmd_keylock_4},             // lock / unlock keys (child lock)
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_4, NULL},                       // schedule
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
//        {DP_TYPE0C_ID_71, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_4},                      // temperature of outer sensor
//        {DP_TYPE0C_ID_75, DP_VAL,  4,    10, remote_cmd_frost_protect_4, local_cmd_frost_protect_4}, // frost protected
//        {DP_TYPE0C_ID_74, DP_VAL,  4,    10, remote_cmd_heat_protect_4, local_cmd_heat_protect_4},   // heat protected
//        {DP_TYPE0C_ID_70, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule mon
//        {DP_TYPE0C_ID_6F, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule tue
//        {DP_TYPE0C_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule wed
//        {DP_TYPE0C_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule thu
//        {DP_TYPE0C_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule fri
//        {DP_TYPE0C_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule sat
//        {DP_TYPE0C_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule sun
//        {DP_TYPE0C_ID_73, DP_VAL,  4,    1,  remote_cmd_level_4, local_cmd_level_4},                 // level brightness of screen
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE0C_ID_04, DP_BOOL, 1,    1,  remote_cmd_eco_mode_4, local_cmd_eco_mode_4},           // eco mode
//        {DP_TYPE0C_ID_69, DP_VAL,  4,    10, remote_cmd_eco_mode_temp_4, local_cmd_eco_mode_temp_4}, // eco mode's temperature
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE0C_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//};


/*
 *
 * For models   "szbxmorb"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_humidity_0C(void *args) {

    uint16_t *hum = (uint16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_HUMIDITY].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_HUMIDITY].divisor == 10) {
        divisor = 10;
    }

    *hum *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_MS_RELATIVE_HUMIDITY, ZCL_RELATIVE_HUMIDITY_MEASUREMENT_ATTRID_MEASUREDVALUE, (uint8_t*)hum);

#if UART_PRINTF_MODE && DEBUG_CMD
            printf("Local Humidity: %d\r\n", *hum);
#endif

}

void local_cmd_humidity_offset_0C(void *args) {

    uint16_t *hum_offset = (uint16_t*)args;

    if (data_point_model[DP_IDX_HUMIDITY_OFFSET].divisor == -10) {
        *hum_offset *= 10;
    } else if (data_point_model[DP_IDX_HUMIDITY_OFFSET].divisor == 10) {
        *hum_offset /= 10;
    }

    *hum_offset *= 100;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_MS_RELATIVE_HUMIDITY,
                   ZCL_RELATIVE_HUMIDITY_MEASUREMENT_ATTRID_CUSTOM_HUMIDITY_OFFSET, (uint8_t*)hum_offset);

    thermostat_settings_save();
}

/*
 *
 * For models   "szbxmorb"
 *
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_humidity_offset_0C(void *args) {

    int16_t *arg = (int16_t*)args;
    int16_t hum_offset = *arg;

    if(data_point_model[DP_IDX_HUMIDITY_OFFSET].id == 0) return;

    if (hum_offset < data_point_model[DP_IDX_HUMIDITY_OFFSET].arg1) hum_offset = data_point_model[DP_IDX_HUMIDITY_OFFSET].arg1;
    if (hum_offset > data_point_model[DP_IDX_HUMIDITY_OFFSET].arg2) hum_offset = data_point_model[DP_IDX_HUMIDITY_OFFSET].arg2;

    hum_offset /= 100;

//    printf("humidity_offset: %d\r\n", hum_offset);

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    if (data_point_model[DP_IDX_HUMIDITY_OFFSET].divisor == -10) {
        hum_offset /= 10;
    } else if (data_point_model[DP_IDX_HUMIDITY_OFFSET].divisor == 10) {
        hum_offset *= 10;
    }

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_HUMIDITY_OFFSET].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_HUMIDITY_OFFSET].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    int32_t dev_hum_offset = hum_offset;
    data_point->data[0] = (dev_hum_offset >> 24) & 0xFF;
    data_point->data[1] = (dev_hum_offset >> 16) & 0xFF;
    data_point->data[2] = (dev_hum_offset >> 8)  & 0xFF;
    data_point->data[3] = dev_hum_offset & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}


