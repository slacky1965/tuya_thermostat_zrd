#include "app_main.h"

/* data point for manufacturer id -
 * "5toc8efa"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */

#define R05_ABS_HEAT_MIN            500
#define R05_ABS_HEAT_MAX            4500
#define R05_HEAT_MIN_MIN            500         // * 100
#define R05_HEAT_MIN_MAX            1500        // * 100
#define R05_HEAT_MAX_MIN            1500        //3500        // * 100
#define R05_HEAT_MAX_MAX            4500        // * 100
#define R05_HEAT_PROTECT_MIN        2500        // * 100
#define R05_HEAT_PROTECT_MAX        7000        // * 100
#define R05_DEADZONE_MIN            1
#define R05_DEADZONE_MAX            5
#define R05_CALIBRATION_MIN        -90          // * 10
#define R05_CALIBRATION_MAX         90          // * 10

//data_point_st_t data_point_model5[DP_IDX_MAXNUM];

data_point_st_t *init_datapoint_model5() {

    memset(data_point_model_common, 0, sizeof(data_point_model_common));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = R05_ABS_HEAT_MIN;       // min +5°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = R05_ABS_HEAT_MAX;       // max +45°C

    data_point_model_common[DP_IDX_ONOFF].id = DP_TYPE5_ID_01;
    data_point_model_common[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model_common[DP_IDX_ONOFF].len = 1;
    data_point_model_common[DP_IDX_ONOFF].divisor = 1;
    data_point_model_common[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_5;
    data_point_model_common[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_5;

    data_point_model_common[DP_IDX_TEMP].id = DP_TYPE5_ID_18;
    data_point_model_common[DP_IDX_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP].len = 4;
    data_point_model_common[DP_IDX_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_5;

    data_point_model_common[DP_IDX_SETPOINT].id = DP_TYPE5_ID_10;
    data_point_model_common[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model_common[DP_IDX_SETPOINT].len = 4;
    data_point_model_common[DP_IDX_SETPOINT].divisor = 10;
    data_point_model_common[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_5;
    data_point_model_common[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_5;

    data_point_model_common[DP_IDX_MIN].id = DP_TYPE5_ID_1A;
    data_point_model_common[DP_IDX_MIN].type = DP_VAL;
    data_point_model_common[DP_IDX_MIN].len = 4;
    data_point_model_common[DP_IDX_MIN].divisor = 10;
    data_point_model_common[DP_IDX_MIN].remote_cmd = remote_cmd_min_setpoint_5;
    data_point_model_common[DP_IDX_MIN].local_cmd = local_cmd_min_setpoint_5;
    data_point_model_common[DP_IDX_MIN].arg1 = R05_HEAT_MIN_MIN;
    data_point_model_common[DP_IDX_MIN].arg2 = R05_HEAT_MIN_MAX;

    data_point_model_common[DP_IDX_MAX].id = DP_TYPE5_ID_13;
    data_point_model_common[DP_IDX_MAX].type = DP_VAL;
    data_point_model_common[DP_IDX_MAX].len = 4;
    data_point_model_common[DP_IDX_MAX].divisor = 10;
    data_point_model_common[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_5;
    data_point_model_common[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_5;
    data_point_model_common[DP_IDX_MAX].arg1 = R05_HEAT_MAX_MIN;
    data_point_model_common[DP_IDX_MAX].arg2 = R05_HEAT_MAX_MAX;

    data_point_model_common[DP_IDX_DEADZONE].id = DP_TYPE5_ID_67;
    data_point_model_common[DP_IDX_DEADZONE].type = DP_VAL;
    data_point_model_common[DP_IDX_DEADZONE].len = 4;
    data_point_model_common[DP_IDX_DEADZONE].divisor = 1;
    data_point_model_common[DP_IDX_DEADZONE].remote_cmd = remote_cmd_deadband_5;
    data_point_model_common[DP_IDX_DEADZONE].local_cmd = local_cmd_deadband_5;
    data_point_model_common[DP_IDX_DEADZONE].arg1 = R05_DEADZONE_MIN;
    data_point_model_common[DP_IDX_DEADZONE].arg2 = R05_DEADZONE_MAX;

    data_point_model_common[DP_IDX_CALIBRATION].id = DP_TYPE5_ID_1B;
    data_point_model_common[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model_common[DP_IDX_CALIBRATION].len = 4;
    data_point_model_common[DP_IDX_CALIBRATION].divisor = -10;
    data_point_model_common[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_5;
    data_point_model_common[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_5;
    data_point_model_common[DP_IDX_CALIBRATION].arg1 = R05_CALIBRATION_MIN;
    data_point_model_common[DP_IDX_CALIBRATION].arg2 = R05_CALIBRATION_MAX;

    data_point_model_common[DP_IDX_RUNSTATE].id = DP_TYPE5_ID_24;
    data_point_model_common[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model_common[DP_IDX_RUNSTATE].len = 1;
    data_point_model_common[DP_IDX_RUNSTATE].divisor = 1;
    data_point_model_common[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_5;

    data_point_model_common[DP_IDX_SENSOR].id = DP_TYPE5_ID_2B;
    data_point_model_common[DP_IDX_SENSOR].type = DP_ENUM;
    data_point_model_common[DP_IDX_SENSOR].len = 1;
    data_point_model_common[DP_IDX_SENSOR].divisor = 1;
    data_point_model_common[DP_IDX_SENSOR].remote_cmd = remote_cmd_sensor_used_5;
    data_point_model_common[DP_IDX_SENSOR].local_cmd = local_cmd_sensor_used_5;

    data_point_model_common[DP_IDX_PROG].id = DP_TYPE5_ID_02;
    data_point_model_common[DP_IDX_PROG].type = DP_ENUM;
    data_point_model_common[DP_IDX_PROG].len = 1;
    data_point_model_common[DP_IDX_PROG].divisor = 1;
    data_point_model_common[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_5;
    data_point_model_common[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_5;

    data_point_model_common[DP_IDX_LOCKUNLOCK].id = DP_TYPE5_ID_28;
    data_point_model_common[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model_common[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].divisor = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_5;
    data_point_model_common[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_5;

    data_point_model_common[DP_IDX_SCHEDULE].id = DP_TYPE5_ID_00;
    data_point_model_common[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_5;

    data_point_model_common[DP_IDX_TEMP_OUT].id = DP_TYPE5_ID_66;
    data_point_model_common[DP_IDX_TEMP_OUT].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP_OUT].len = 4;
    data_point_model_common[DP_IDX_TEMP_OUT].divisor = 10;
    data_point_model_common[DP_IDX_TEMP_OUT].local_cmd = local_cmd_outdoor_sensor_5;

    data_point_model_common[DP_IDX_HEAT_PROTECT].id = DP_TYPE5_ID_68;
    data_point_model_common[DP_IDX_HEAT_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_HEAT_PROTECT].len = 4;
    data_point_model_common[DP_IDX_HEAT_PROTECT].divisor = 10;
    data_point_model_common[DP_IDX_HEAT_PROTECT].remote_cmd = remote_cmd_heat_protect_5;
    data_point_model_common[DP_IDX_HEAT_PROTECT].local_cmd = local_cmd_heat_protect_5;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg1 = R05_HEAT_PROTECT_MIN;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg2 = R05_HEAT_PROTECT_MAX;

    data_point_model_common[DP_IDX_SCHEDULE_MON].id = DP_TYPE5_ID_6E;
    data_point_model_common[DP_IDX_SCHEDULE_MON].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_MON].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_MON].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_MON].local_cmd = local_cmd_set_schedule_5;

    data_point_model_common[DP_IDX_SCHEDULE_TUE].id = DP_TYPE5_ID_6D;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].local_cmd = local_cmd_set_schedule_5;

    data_point_model_common[DP_IDX_SCHEDULE_WED].id = DP_TYPE5_ID_6C;
    data_point_model_common[DP_IDX_SCHEDULE_WED].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_WED].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_WED].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_WED].local_cmd = local_cmd_set_schedule_5;

    data_point_model_common[DP_IDX_SCHEDULE_THU].id = DP_TYPE5_ID_6B;
    data_point_model_common[DP_IDX_SCHEDULE_THU].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_THU].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_THU].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_THU].local_cmd = local_cmd_set_schedule_5;

    data_point_model_common[DP_IDX_SCHEDULE_FRI].id = DP_TYPE5_ID_6A;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].local_cmd = local_cmd_set_schedule_5;

    data_point_model_common[DP_IDX_SCHEDULE_SAT].id = DP_TYPE5_ID_69;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].local_cmd = local_cmd_set_schedule_5;

    data_point_model_common[DP_IDX_SCHEDULE_SUN].id = DP_TYPE5_ID_65;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].local_cmd = local_cmd_set_schedule_5;

    return data_point_model_common;
}


//data_point_st_t data_point_model5[DP_IDX_MAXNUM] = {
//        {DP_TYPE5_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_5, local_cmd_onoff_state_5},                // onoff
//        {DP_TYPE5_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_5},                                // local temperature
//        {DP_TYPE5_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_5, local_cmd_heating_set_5},             // heat setpoint
//        {DP_TYPE5_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_5, local_cmd_min_setpoint_5},           // min heat setpoint
//        {DP_TYPE5_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_5, local_cmd_max_setpoint_5},           // max heat setpoint
//        {DP_TYPE5_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_5, local_cmd_deadband_5},                   // hysteresis
//        {DP_TYPE5_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_5, local_cmd_temp_calibration_5},   // local temperature calibration
//        {DP_TYPE5_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_5},                       // 0x00 - heat, 0x01 - idle
//        {DP_TYPE5_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_5, local_cmd_sensor_used_5},     // sensor IN/AL/OU
//        {DP_TYPE5_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_5, local_cmd_oper_mode_5},         // manual (setpoint) / programming (schedule)
//        {DP_TYPE5_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_5, local_cmd_keylock_5},             // lock / unlock keys (child lock)
//        {DP_TYPE5_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_5, NULL},                       // schedule
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
//        {DP_TYPE5_ID_66, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_5},                      // temperature of outer sensor
//        {DP_TYPE5_ID_00, DP_RAW,  4,    0,  NULL, NULL},                                            // frost protected
//        {DP_TYPE5_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_5, local_cmd_heat_protect_5},   // heat protected
//        {DP_TYPE5_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule mon
//        {DP_TYPE5_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule tue
//        {DP_TYPE5_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule wed
//        {DP_TYPE5_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule thu
//        {DP_TYPE5_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule fri
//        {DP_TYPE5_ID_69, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule sat
//        {DP_TYPE5_ID_65, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule sun
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
//};
