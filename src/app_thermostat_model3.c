#include "app_main.h"

/* data point for manufacturer id -
 * "tagezcph"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */

#define R03_ABS_HEAT_MIN            500
#define R03_ABS_HEAT_MAX            4500
#define R03_HEAT_MIN_MIN            500         // * 100
#define R03_HEAT_MIN_MAX            1500        // * 100
#define R03_HEAT_MAX_MIN            1500        // * 100
#define R03_HEAT_MAX_MAX            4500        // * 100
#define R03_FROST_PROTECT_MIN       0
#define R03_FROST_PROTECT_MAX       1000
#define R03_HEAT_PROTECT_MIN        2500        // * 100
#define R03_HEAT_PROTECT_MAX        7000        // * 100
#define R03_DEADZONE_MIN            1
#define R03_DEADZONE_MAX            5
#define R03_CALIBRATION_MIN        -90          // * 10
#define R03_CALIBRATION_MAX         90          // * 10

data_point_st_t data_point_model3[DP_IDX_MAXNUM];

data_point_st_t *init_datapoint_model3() {

    memset(data_point_model_common, 0, sizeof(data_point_model_common));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = R03_ABS_HEAT_MIN;       // min +5°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = R03_ABS_HEAT_MAX;       // max +45°C

    data_point_model_common[DP_IDX_ONOFF].id = DP_TYPE3_ID_01;
    data_point_model_common[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model_common[DP_IDX_ONOFF].len = 1;
    data_point_model_common[DP_IDX_ONOFF].divisor = 1;
    data_point_model_common[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_3;
    data_point_model_common[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_3;

    data_point_model_common[DP_IDX_TEMP].id = DP_TYPE3_ID_18;
    data_point_model_common[DP_IDX_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP].len = 4;
    data_point_model_common[DP_IDX_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_3;

    data_point_model_common[DP_IDX_SETPOINT].id = DP_TYPE3_ID_10;
    data_point_model_common[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model_common[DP_IDX_SETPOINT].len = 4;
    data_point_model_common[DP_IDX_SETPOINT].divisor = 10;
    data_point_model_common[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_3;
    data_point_model_common[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_3;

    data_point_model_common[DP_IDX_MIN].id = DP_TYPE3_ID_1A;
    data_point_model_common[DP_IDX_MIN].type = DP_VAL;
    data_point_model_common[DP_IDX_MIN].len = 4;
    data_point_model_common[DP_IDX_MIN].divisor = 10;
    data_point_model_common[DP_IDX_MIN].remote_cmd = remote_cmd_min_setpoint_3;
    data_point_model_common[DP_IDX_MIN].local_cmd = local_cmd_min_setpoint_3;
    data_point_model_common[DP_IDX_MIN].arg1 = R03_HEAT_MIN_MIN;
    data_point_model_common[DP_IDX_MIN].arg2 = R03_HEAT_MIN_MAX;

    data_point_model_common[DP_IDX_MAX].id = DP_TYPE3_ID_13;
    data_point_model_common[DP_IDX_MAX].type = DP_VAL;
    data_point_model_common[DP_IDX_MAX].len = 4;
    data_point_model_common[DP_IDX_MAX].divisor = 10;
    data_point_model_common[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_3;
    data_point_model_common[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_3;
    data_point_model_common[DP_IDX_MAX].arg1 = R03_HEAT_MAX_MIN;
    data_point_model_common[DP_IDX_MAX].arg2 = R03_HEAT_MAX_MAX;

    data_point_model_common[DP_IDX_DEADZONE].id = DP_TYPE3_ID_67;
    data_point_model_common[DP_IDX_DEADZONE].type = DP_VAL;
    data_point_model_common[DP_IDX_DEADZONE].len = 4;
    data_point_model_common[DP_IDX_DEADZONE].divisor = 1;
    data_point_model_common[DP_IDX_DEADZONE].remote_cmd = remote_cmd_deadband_3;
    data_point_model_common[DP_IDX_DEADZONE].local_cmd = local_cmd_deadband_3;
    data_point_model_common[DP_IDX_DEADZONE].arg1 = R03_DEADZONE_MIN;
    data_point_model_common[DP_IDX_DEADZONE].arg2 = R03_DEADZONE_MAX;

    data_point_model_common[DP_IDX_CALIBRATION].id = DP_TYPE3_ID_1B;
    data_point_model_common[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model_common[DP_IDX_CALIBRATION].len = 4;
    data_point_model_common[DP_IDX_CALIBRATION].divisor = -10;
    data_point_model_common[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_3;
    data_point_model_common[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_3;
    data_point_model_common[DP_IDX_CALIBRATION].arg1 = R03_CALIBRATION_MIN;
    data_point_model_common[DP_IDX_CALIBRATION].arg2 = R03_CALIBRATION_MAX;

    data_point_model_common[DP_IDX_RUNSTATE].id = DP_TYPE3_ID_24;
    data_point_model_common[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model_common[DP_IDX_RUNSTATE].len = 1;
    data_point_model_common[DP_IDX_RUNSTATE].divisor = 1;
    data_point_model_common[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_3;

    data_point_model_common[DP_IDX_SENSOR].id = DP_TYPE3_ID_2B;
    data_point_model_common[DP_IDX_SENSOR].type = DP_ENUM;
    data_point_model_common[DP_IDX_SENSOR].len = 1;
    data_point_model_common[DP_IDX_SENSOR].divisor = 1;
    data_point_model_common[DP_IDX_SENSOR].remote_cmd = remote_cmd_sensor_used_3;
    data_point_model_common[DP_IDX_SENSOR].local_cmd = local_cmd_sensor_used_3;

    data_point_model_common[DP_IDX_PROG].id = DP_TYPE3_ID_02;
    data_point_model_common[DP_IDX_PROG].type = DP_ENUM;
    data_point_model_common[DP_IDX_PROG].len = 1;
    data_point_model_common[DP_IDX_PROG].divisor = 1;
    data_point_model_common[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_3;
    data_point_model_common[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_3;

    data_point_model_common[DP_IDX_LOCKUNLOCK].id = DP_TYPE3_ID_27;
    data_point_model_common[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model_common[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].divisor = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_3;
    data_point_model_common[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_3;

    data_point_model_common[DP_IDX_SCHEDULE].id = DP_TYPE3_ID_00;
    data_point_model_common[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_3;

    data_point_model_common[DP_IDX_TEMP_OUT].id = DP_TYPE3_ID_66;
    data_point_model_common[DP_IDX_TEMP_OUT].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP_OUT].len = 4;
    data_point_model_common[DP_IDX_TEMP_OUT].divisor = 10;
    data_point_model_common[DP_IDX_TEMP_OUT].local_cmd = local_cmd_outdoor_sensor_3;

    data_point_model_common[DP_IDX_FROST_PROTECT].id = DP_TYPE3_ID_6F;
    data_point_model_common[DP_IDX_FROST_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_FROST_PROTECT].len = 4;
    data_point_model_common[DP_IDX_FROST_PROTECT].divisor = 10;
    data_point_model_common[DP_IDX_FROST_PROTECT].remote_cmd = remote_cmd_frost_protect_3;
    data_point_model_common[DP_IDX_FROST_PROTECT].local_cmd = local_cmd_frost_protect_3;
    data_point_model_common[DP_IDX_FROST_PROTECT].arg1 = R03_FROST_PROTECT_MIN;
    data_point_model_common[DP_IDX_FROST_PROTECT].arg2 = R03_FROST_PROTECT_MAX;

    data_point_model_common[DP_IDX_HEAT_PROTECT].id = DP_TYPE3_ID_68;
    data_point_model_common[DP_IDX_HEAT_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_HEAT_PROTECT].len = 4;
    data_point_model_common[DP_IDX_HEAT_PROTECT].divisor = 10;
    data_point_model_common[DP_IDX_HEAT_PROTECT].remote_cmd = remote_cmd_heat_protect_3;
    data_point_model_common[DP_IDX_HEAT_PROTECT].local_cmd = local_cmd_heat_protect_3;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg1 = R03_HEAT_PROTECT_MIN;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg2 = R03_HEAT_PROTECT_MAX;

    data_point_model_common[DP_IDX_SCHEDULE_MON].id = DP_TYPE3_ID_6E;
    data_point_model_common[DP_IDX_SCHEDULE_MON].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_MON].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_MON].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_MON].local_cmd = local_cmd_set_schedule_3;

    data_point_model_common[DP_IDX_SCHEDULE_TUE].id = DP_TYPE3_ID_6D;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].local_cmd = local_cmd_set_schedule_3;

    data_point_model_common[DP_IDX_SCHEDULE_WED].id = DP_TYPE3_ID_6C;
    data_point_model_common[DP_IDX_SCHEDULE_WED].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_WED].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_WED].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_WED].local_cmd = local_cmd_set_schedule_3;

    data_point_model_common[DP_IDX_SCHEDULE_THU].id = DP_TYPE3_ID_6B;
    data_point_model_common[DP_IDX_SCHEDULE_THU].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_THU].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_THU].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_THU].local_cmd = local_cmd_set_schedule_3;

    data_point_model_common[DP_IDX_SCHEDULE_FRI].id = DP_TYPE3_ID_6A;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].local_cmd = local_cmd_set_schedule_3;

    data_point_model_common[DP_IDX_SCHEDULE_SAT].id = DP_TYPE3_ID_69;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].local_cmd = local_cmd_set_schedule_3;

    data_point_model_common[DP_IDX_SCHEDULE_SUN].id = DP_TYPE3_ID_65;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].local_cmd = local_cmd_set_schedule_3;

    data_point_model_common[DP_IDX_LEVEL_A].id = DP_TYPE3_ID_71;
    data_point_model_common[DP_IDX_LEVEL_A].type = DP_VAL;
    data_point_model_common[DP_IDX_LEVEL_A].len = 4;
    data_point_model_common[DP_IDX_LEVEL_A].remote_cmd = remote_cmd_level_day_3;
    data_point_model_common[DP_IDX_LEVEL_A].local_cmd = local_cmd_level_day_3;

    data_point_model_common[DP_IDX_LEVEL_B].id = DP_TYPE3_ID_72;
    data_point_model_common[DP_IDX_LEVEL_B].type = DP_VAL;
    data_point_model_common[DP_IDX_LEVEL_B].len = 4;
    data_point_model_common[DP_IDX_LEVEL_B].remote_cmd = remote_cmd_level_night_3;
    data_point_model_common[DP_IDX_LEVEL_B].local_cmd = local_cmd_level_night_3;

    data_point_model_common[DP_IDX_ECO_MODE].id = DP_TYPE3_ID_28;
    data_point_model_common[DP_IDX_ECO_MODE].type = DP_BOOL;
    data_point_model_common[DP_IDX_ECO_MODE].len = 1;
    data_point_model_common[DP_IDX_ECO_MODE].remote_cmd = remote_cmd_eco_mode_3;
    data_point_model_common[DP_IDX_ECO_MODE].local_cmd = local_cmd_eco_mode_3;

    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].id = DP_TYPE3_ID_70;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].len = 4;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].remote_cmd = remote_cmd_eco_mode_temp_3;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].local_cmd = local_cmd_eco_mode_temp_3;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].arg1 = R03_ABS_HEAT_MIN;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].arg2 = R03_ABS_HEAT_MAX;

    return data_point_model_common;
}

//data_point_st_t data_point_model3[DP_IDX_MAXNUM] = {
//        {DP_TYPE3_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_3, local_cmd_onoff_state_3},                // onoff
//        {DP_TYPE3_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_3},                                // local temperature
//        {DP_TYPE3_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_3, local_cmd_heating_set_3},             // heat setpoint
//        {DP_TYPE3_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_3, local_cmd_min_setpoint_3},           // min heat setpoint
//        {DP_TYPE3_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_3, local_cmd_max_setpoint_3},           // max heat setpoint
//        {DP_TYPE3_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_3, local_cmd_deadband_3},                   // hysteresis
//        {DP_TYPE3_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_3, local_cmd_temp_calibration_3},   // local temperature calibration
//        {DP_TYPE3_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_3},                       // 0x00 - heat, 0x01 - idle
//        {DP_TYPE3_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_3, local_cmd_sensor_used_3},     // sensor IN/AL/OU
//        {DP_TYPE3_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_3, local_cmd_oper_mode_3},         // manual (setpoint) / programming (schedule)
//        {DP_TYPE3_ID_27, DP_BOOL, 1,    1,  remote_cmd_keylock_3, local_cmd_keylock_3},             // lock / unlock keys (child lock)
//        {DP_TYPE3_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_3, NULL},                       // schedule
//        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
//        {DP_TYPE3_ID_66, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_3},                      // temperature of outer sensor
//        {DP_TYPE3_ID_6F, DP_VAL,  4,    10, remote_cmd_frost_protect_3, local_cmd_frost_protect_3}, // frost protected
//        {DP_TYPE3_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_3, local_cmd_heat_protect_3},   // heat protected
//        {DP_TYPE3_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule mon
//        {DP_TYPE3_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule tue
//        {DP_TYPE3_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule wed
//        {DP_TYPE3_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule thu
//        {DP_TYPE3_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule fri
//        {DP_TYPE3_ID_69, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule sat
//        {DP_TYPE3_ID_65, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule sun
//        {DP_TYPE3_ID_71, DP_VAL,  4,    1,  remote_cmd_level_day_3, local_cmd_level_day_3},         // level brightness 06:00-22:00
//        {DP_TYPE3_ID_72, DP_VAL,  4,    1,  remote_cmd_level_night_3, local_cmd_level_night_3},     // level brightness 22:00-06:00
//        {DP_TYPE3_ID_28, DP_BOOL, 1,    1,  remote_cmd_eco_mode_3, local_cmd_eco_mode_3},           // eco mode
//        {DP_TYPE3_ID_70, DP_VAL,  4,    10, remote_cmd_eco_mode_temp_3, local_cmd_eco_mode_temp_3}, // eco mode's temperature
//        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//};


/*
 *
 * For models   "tagezcph"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_eco_mode_3(void *args) {

    uint8_t *eco_mode = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE, (uint8_t*)eco_mode);

    thermostat_settings_save();
}

void local_cmd_eco_mode_temp_3(void *args) {

    uint16_t *eco_temp = (uint16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_ECO_HEAT_TEMP].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_ECO_HEAT_TEMP].divisor == 10) {
        divisor = 10;
    }

    *eco_temp *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE_HEAT_TEMPERATURE, (uint8_t*)eco_temp);

    thermostat_settings_save();
}

void local_cmd_level_day_3(void *args) {

    uint16_t *level = (uint16_t*)args;

//    printf("local_cmd_level_day_3(). level: %d\r\n", *level);

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL, (uint8_t*)level);

    thermostat_settings_save();
}

void local_cmd_level_night_3(void *args) {

    uint16_t *level = (uint16_t*)args;

//    printf("local_cmd_level_night_3(). level: %d\r\n", *level);

    zcl_setAttrVal(APP_ENDPOINT2, ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL, (uint8_t*)level);

    thermostat_settings_save();
}

/*
 *
 * For models   "tagezcph"
 *
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_eco_mode_3(void *args) {

    uint8_t *eco_mode = (uint8_t*)args;

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_ECO_MODE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_ECO_MODE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *eco_mode;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_eco_mode_temp_3(void *args) {

    int16_t *arg = (int16_t*)args;
    uint32_t eco_temp = *arg;
//    uint16_t len;
//    int16_t min_temp, max_temp;

//    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&min_temp);
//    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&max_temp);

    if (eco_temp < data_point_model[DP_IDX_ECO_HEAT_TEMP].arg1) eco_temp = data_point_model[DP_IDX_ECO_HEAT_TEMP].arg1;
    if (eco_temp > data_point_model[DP_IDX_ECO_HEAT_TEMP].arg2) eco_temp = data_point_model[DP_IDX_ECO_HEAT_TEMP].arg2;

    if (data_point_model[DP_IDX_ECO_HEAT_TEMP].divisor == 1) {
        eco_temp /= 100;
    } else if (data_point_model[DP_IDX_ECO_HEAT_TEMP].divisor == 10) {
        eco_temp /= 10;
    }


    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_ECO_HEAT_TEMP].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_ECO_HEAT_TEMP].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (eco_temp >> 24) & 0xFF;
    data_point->data[1] = (eco_temp >> 16) & 0xFF;
    data_point->data[2] = (eco_temp >> 8)  & 0xFF;
    data_point->data[3] = eco_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_level_day_3(void *args) {

    uint8_t *level = (uint8_t*)args;

//    printf("remote_cmd_level_day_3(). level: %d\r\n", *level);

    if (*level < 0 || *level > 8) return;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL, (uint8_t*)level);


    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LEVEL_A].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LEVEL_A].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (*level >> 24) & 0xFF;
    data_point->data[1] = (*level >> 16) & 0xFF;
    data_point->data[2] = (*level >> 8)  & 0xFF;
    data_point->data[3] = *level & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_level_night_3(void *args) {

    uint8_t *level = (uint8_t*)args;

//    printf("remote_cmd_level_night_3(). level: %d\r\n", *level);

    if (*level < 0 || *level > 8) return;

    zcl_setAttrVal(APP_ENDPOINT2, ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL, (uint8_t*)level);

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LEVEL_B].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LEVEL_B].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (*level >> 24) & 0xFF;
    data_point->data[1] = (*level >> 16) & 0xFF;
    data_point->data[2] = (*level >> 8)  & 0xFF;
    data_point->data[3] = *level & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

