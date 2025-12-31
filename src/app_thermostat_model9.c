#include "app_main.h"

/* data point for manufacturer id -
 * "6a4vxfnv"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */

#define R09_ABS_HEAT_MIN            500
#define R09_ABS_HEAT_MAX            6000
#define R09_HEAT_MIN_MIN            500         // * 100
#define R09_HEAT_MIN_MAX            1500        // * 100
#define R09_HEAT_MAX_MIN            3000        // * 100
#define R09_HEAT_MAX_MAX            6000        // * 100
#define R09_FROST_PROTECT_MIN       0
#define R09_FROST_PROTECT_MAX       1000
#define R09_HEAT_PROTECT_MIN        2000        // * 100
#define R09_HEAT_PROTECT_MAX        7000        // * 100
#define R09_DEADZONE_MIN            10
#define R09_DEADZONE_MAX            50
#define R09_CALIBRATION_MIN        -90          // * 10
#define R09_CALIBRATION_MAX         90          // * 10
#define R07_ECO_HEAT_TEMP_MIN       0
#define R07_ECO_HEAT_TEMP_MAX       3000


//data_point_st_t data_point_model9[DP_IDX_MAXNUM];

data_point_st_t *init_datapoint_model9() {

    memset(data_point_model_common, 0, sizeof(data_point_model_common));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = R09_ABS_HEAT_MIN;       // min +5°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = R09_ABS_HEAT_MAX;       // max +60°C

    data_point_model_common[DP_IDX_ONOFF].id = DP_TYPE9_ID_01;
    data_point_model_common[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model_common[DP_IDX_ONOFF].len = 1;
    data_point_model_common[DP_IDX_ONOFF].divisor = 1;
    data_point_model_common[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_9;
    data_point_model_common[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_9;

    data_point_model_common[DP_IDX_TEMP].id = DP_TYPE9_ID_18;
    data_point_model_common[DP_IDX_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP].len = 4;
    data_point_model_common[DP_IDX_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_9;

    data_point_model_common[DP_IDX_SETPOINT].id = DP_TYPE9_ID_10;
    data_point_model_common[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model_common[DP_IDX_SETPOINT].len = 4;
    data_point_model_common[DP_IDX_SETPOINT].divisor = 10;
    data_point_model_common[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_9;
    data_point_model_common[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_9;

    data_point_model_common[DP_IDX_MIN].id = DP_TYPE9_ID_1A;
    data_point_model_common[DP_IDX_MIN].type = DP_VAL;
    data_point_model_common[DP_IDX_MIN].len = 4;
    data_point_model_common[DP_IDX_MIN].divisor = 10;
    data_point_model_common[DP_IDX_MIN].remote_cmd = remote_cmd_min_setpoint_9;
    data_point_model_common[DP_IDX_MIN].local_cmd = local_cmd_min_setpoint_9;
    data_point_model_common[DP_IDX_MIN].arg1 = R09_HEAT_MIN_MIN;
    data_point_model_common[DP_IDX_MIN].arg2 = R09_HEAT_MIN_MAX;

    data_point_model_common[DP_IDX_MAX].id = DP_TYPE9_ID_13;
    data_point_model_common[DP_IDX_MAX].type = DP_VAL;
    data_point_model_common[DP_IDX_MAX].len = 4;
    data_point_model_common[DP_IDX_MAX].divisor = 10;
    data_point_model_common[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_9;
    data_point_model_common[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_9;
    data_point_model_common[DP_IDX_MAX].arg1 = R09_HEAT_MAX_MIN;
    data_point_model_common[DP_IDX_MAX].arg2 = R09_HEAT_MAX_MAX;

    data_point_model_common[DP_IDX_DEADZONE].id = DP_TYPE9_ID_67;
    data_point_model_common[DP_IDX_DEADZONE].type = DP_VAL;
    data_point_model_common[DP_IDX_DEADZONE].len = 4;
    data_point_model_common[DP_IDX_DEADZONE].divisor = 1;
    data_point_model_common[DP_IDX_DEADZONE].remote_cmd = remote_cmd_deadband_9;
    data_point_model_common[DP_IDX_DEADZONE].local_cmd = local_cmd_deadband_9;
    data_point_model_common[DP_IDX_DEADZONE].arg1 = R09_DEADZONE_MIN;
    data_point_model_common[DP_IDX_DEADZONE].arg2 = R09_DEADZONE_MAX;

    data_point_model_common[DP_IDX_CALIBRATION].id = DP_TYPE9_ID_1B;
    data_point_model_common[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model_common[DP_IDX_CALIBRATION].len = 4;
    data_point_model_common[DP_IDX_CALIBRATION].divisor = -10;
    data_point_model_common[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_9;
    data_point_model_common[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_9;
    data_point_model_common[DP_IDX_CALIBRATION].arg1 = R09_CALIBRATION_MIN;
    data_point_model_common[DP_IDX_CALIBRATION].arg2 = R09_CALIBRATION_MAX;

    data_point_model_common[DP_IDX_RUNSTATE].id = DP_TYPE9_ID_24;
    data_point_model_common[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model_common[DP_IDX_RUNSTATE].len = 1;
    data_point_model_common[DP_IDX_RUNSTATE].divisor = 1;
    data_point_model_common[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_9;

    data_point_model_common[DP_IDX_SENSOR].id = DP_TYPE9_ID_2B;
    data_point_model_common[DP_IDX_SENSOR].type = DP_ENUM;
    data_point_model_common[DP_IDX_SENSOR].len = 1;
    data_point_model_common[DP_IDX_SENSOR].divisor = 1;
    data_point_model_common[DP_IDX_SENSOR].remote_cmd = remote_cmd_sensor_used_9;
    data_point_model_common[DP_IDX_SENSOR].local_cmd = local_cmd_sensor_used_9;

    data_point_model_common[DP_IDX_PROG].id = DP_TYPE9_ID_02;
    data_point_model_common[DP_IDX_PROG].type = DP_ENUM;
    data_point_model_common[DP_IDX_PROG].len = 1;
    data_point_model_common[DP_IDX_PROG].divisor = 1;
    data_point_model_common[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_9;
    data_point_model_common[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_9;

    data_point_model_common[DP_IDX_LOCKUNLOCK].id = DP_TYPE9_ID_27;
    data_point_model_common[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model_common[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].divisor = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_9;
    data_point_model_common[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_9;

    data_point_model_common[DP_IDX_SCHEDULE].id = DP_TYPE9_ID_00;
    data_point_model_common[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_9;

    data_point_model_common[DP_IDX_TEMP_OUT].id = DP_TYPE9_ID_66;
    data_point_model_common[DP_IDX_TEMP_OUT].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP_OUT].len = 4;
    data_point_model_common[DP_IDX_TEMP_OUT].divisor = 10;
    data_point_model_common[DP_IDX_TEMP_OUT].local_cmd = local_cmd_outdoor_sensor_9;

    data_point_model_common[DP_IDX_FROST_PROTECT].id = DP_TYPE9_ID_6F;
    data_point_model_common[DP_IDX_FROST_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_FROST_PROTECT].len = 4;
    data_point_model_common[DP_IDX_FROST_PROTECT].divisor = 10;
    data_point_model_common[DP_IDX_FROST_PROTECT].remote_cmd = remote_cmd_frost_protect_9;
    data_point_model_common[DP_IDX_FROST_PROTECT].local_cmd = local_cmd_frost_protect_9;
    data_point_model_common[DP_IDX_FROST_PROTECT].arg1 = R09_FROST_PROTECT_MIN;
    data_point_model_common[DP_IDX_FROST_PROTECT].arg2 = R09_FROST_PROTECT_MAX;

    data_point_model_common[DP_IDX_HEAT_PROTECT].id = DP_TYPE9_ID_68;
    data_point_model_common[DP_IDX_HEAT_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_HEAT_PROTECT].len = 4;
    data_point_model_common[DP_IDX_HEAT_PROTECT].divisor = 10;
    data_point_model_common[DP_IDX_HEAT_PROTECT].remote_cmd = remote_cmd_heat_protect_9;
    data_point_model_common[DP_IDX_HEAT_PROTECT].local_cmd = local_cmd_heat_protect_9;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg1 = R09_HEAT_PROTECT_MIN;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg2 = R09_HEAT_PROTECT_MAX;

    data_point_model_common[DP_IDX_SCHEDULE_MON].id = DP_TYPE9_ID_6E;
    data_point_model_common[DP_IDX_SCHEDULE_MON].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_MON].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_MON].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_MON].local_cmd = local_cmd_set_schedule_9;

    data_point_model_common[DP_IDX_SCHEDULE_TUE].id = DP_TYPE9_ID_6D;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_TUE].local_cmd = local_cmd_set_schedule_9;

    data_point_model_common[DP_IDX_SCHEDULE_WED].id = DP_TYPE9_ID_6C;
    data_point_model_common[DP_IDX_SCHEDULE_WED].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_WED].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_WED].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_WED].local_cmd = local_cmd_set_schedule_9;

    data_point_model_common[DP_IDX_SCHEDULE_THU].id = DP_TYPE9_ID_6B;
    data_point_model_common[DP_IDX_SCHEDULE_THU].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_THU].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_THU].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_THU].local_cmd = local_cmd_set_schedule_9;

    data_point_model_common[DP_IDX_SCHEDULE_FRI].id = DP_TYPE9_ID_6A;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_FRI].local_cmd = local_cmd_set_schedule_9;

    data_point_model_common[DP_IDX_SCHEDULE_SAT].id = DP_TYPE9_ID_69;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SAT].local_cmd = local_cmd_set_schedule_9;

    data_point_model_common[DP_IDX_SCHEDULE_SUN].id = DP_TYPE9_ID_65;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].len = 0x11;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].divisor = 10;
    data_point_model_common[DP_IDX_SCHEDULE_SUN].local_cmd = local_cmd_set_schedule_9;

    data_point_model_common[DP_IDX_LEVEL_A].id = DP_TYPE9_ID_71;
    data_point_model_common[DP_IDX_LEVEL_A].type = DP_VAL;
    data_point_model_common[DP_IDX_LEVEL_A].len = 4;
    data_point_model_common[DP_IDX_LEVEL_A].divisor = 1;
    data_point_model_common[DP_IDX_LEVEL_A].remote_cmd = remote_cmd_level_day_9;
    data_point_model_common[DP_IDX_LEVEL_A].local_cmd = local_cmd_level_day_9;

    data_point_model_common[DP_IDX_LEVEL_B].id = DP_TYPE9_ID_72;
    data_point_model_common[DP_IDX_LEVEL_B].type = DP_VAL;
    data_point_model_common[DP_IDX_LEVEL_B].len = 4;
    data_point_model_common[DP_IDX_LEVEL_B].divisor = 1;
    data_point_model_common[DP_IDX_LEVEL_B].remote_cmd = remote_cmd_level_night_9;
    data_point_model_common[DP_IDX_LEVEL_B].local_cmd = local_cmd_level_night_9;

    data_point_model_common[DP_IDX_ECO_MODE].id = DP_TYPE9_ID_28;
    data_point_model_common[DP_IDX_ECO_MODE].type = DP_BOOL;
    data_point_model_common[DP_IDX_ECO_MODE].len = 1;
    data_point_model_common[DP_IDX_ECO_MODE].remote_cmd = remote_cmd_eco_mode_9;
    data_point_model_common[DP_IDX_ECO_MODE].local_cmd = local_cmd_eco_mode_9;

    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].id = DP_TYPE9_ID_70;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].len = 4;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].remote_cmd = remote_cmd_eco_mode_temp_9;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].local_cmd = local_cmd_eco_mode_temp_9;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].arg1 = R07_ECO_HEAT_TEMP_MIN;
    data_point_model_common[DP_IDX_ECO_HEAT_TEMP].arg2 = R07_ECO_HEAT_TEMP_MAX;

    data_point_model_common[DP_IDX_SETTINGS_RESET].id = DP_TYPE9_ID_1C;
    data_point_model_common[DP_IDX_SETTINGS_RESET].type = DP_BOOL;
    data_point_model_common[DP_IDX_SETTINGS_RESET].len = 1;
    data_point_model_common[DP_IDX_SETTINGS_RESET].remote_cmd = remote_cmd_setting_reset_9;
    data_point_model_common[DP_IDX_SETTINGS_RESET].local_cmd = local_cmd_setting_reset_9;

    data_point_model_common[DP_IDX_INVERSION].id = DP_TYPE9_ID_74;
    data_point_model_common[DP_IDX_INVERSION].type = DP_ENUM;
    data_point_model_common[DP_IDX_INVERSION].len = 1;
    data_point_model_common[DP_IDX_INVERSION].remote_cmd = remote_cmd_inversion_9;
    data_point_model_common[DP_IDX_INVERSION].local_cmd = local_cmd_inversion_9;

    data_point_model_common[DP_IDX_EXT_CALIBRATION].id = DP_TYPE9_ID_73;
    data_point_model_common[DP_IDX_EXT_CALIBRATION].type = DP_VAL;
    data_point_model_common[DP_IDX_EXT_CALIBRATION].len = 4;
    data_point_model_common[DP_IDX_EXT_CALIBRATION].divisor = -10;
    data_point_model_common[DP_IDX_EXT_CALIBRATION].remote_cmd = remote_cmd_ext_temp_calibration_9;
    data_point_model_common[DP_IDX_EXT_CALIBRATION].local_cmd = local_cmd_ext_temp_calibration_9;
    data_point_model_common[DP_IDX_EXT_CALIBRATION].arg1 = R09_CALIBRATION_MIN;
    data_point_model_common[DP_IDX_EXT_CALIBRATION].arg2 = R09_CALIBRATION_MAX;

    data_point_model_common[DP_IDX_MODE_LOCK].id = DP_TYPE9_ID_75;
    data_point_model_common[DP_IDX_MODE_LOCK].type = DP_ENUM;
    data_point_model_common[DP_IDX_MODE_LOCK].len = 1;
    data_point_model_common[DP_IDX_MODE_LOCK].remote_cmd = remote_cmd_mode_keylock_9;
    data_point_model_common[DP_IDX_MODE_LOCK].local_cmd = local_cmd_mode_keylock_9;

    return data_point_model_common;
}

//data_point_st_t data_point_model9[DP_IDX_MAXNUM] = {
///*00*/  {DP_TYPE9_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_9, local_cmd_onoff_state_9},                // onoff
///*01*/  {DP_TYPE9_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_9},                                // local temperature
///*02*/  {DP_TYPE9_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_9, local_cmd_heating_set_9},             // heat setpoint
///*03*/  {DP_TYPE9_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_9, local_cmd_min_setpoint_9},           // min heat setpoint
///*04*/  {DP_TYPE9_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_9, local_cmd_max_setpoint_9},           // max heat setpoint
///*05*/  {DP_TYPE9_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_9, local_cmd_deadband_9},                   // hysteresis
///*06*/  {DP_TYPE9_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_9, local_cmd_temp_calibration_9},   // local temperature calibration
///*07*/  {DP_TYPE9_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_9},                       // 0x00 - heat, 0x01 - idle
///*08*/  {DP_TYPE9_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_9, local_cmd_sensor_used_9},     // sensor IN/AL/OU
///*09*/  {DP_TYPE9_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_9, local_cmd_oper_mode_9},         // manual (setpoint) / programming (schedule)
///*10*/  {DP_TYPE9_ID_27, DP_BOOL, 1,    1,  remote_cmd_keylock_9, local_cmd_keylock_9},             // lock / unlock keys (child lock)
///*11*/  {DP_TYPE9_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_9, NULL},                       // schedule
///*12*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
///*13*/  {DP_TYPE9_ID_66, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_9},                      // temperature of outer sensor
///*14*/  {DP_TYPE9_ID_6F, DP_VAL,  4,    10, remote_cmd_frost_protect_9, local_cmd_frost_protect_9}, // frost protected
///*15*/  {DP_TYPE9_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_9, local_cmd_heat_protect_9},   // heat protected
///*16*/  {DP_TYPE9_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule mon
///*17*/  {DP_TYPE9_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule tue
///*18*/  {DP_TYPE9_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule wed
///*19*/  {DP_TYPE9_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule thu
///*20*/  {DP_TYPE9_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule fri
///*21*/  {DP_TYPE9_ID_69, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule sat
///*22*/  {DP_TYPE9_ID_65, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule sun
///*23*/  {DP_TYPE9_ID_71, DP_VAL,  4,    1,  remote_cmd_level_day_9, local_cmd_level_day_9},         // level brightness 06:00-22:00
///*24*/  {DP_TYPE9_ID_72, DP_VAL,  4,    1,  remote_cmd_level_night_9, local_cmd_level_night_9},     // level brightness 22:00-06:00
///*25*/  {DP_TYPE9_ID_28, DP_BOOL, 1,    1,  remote_cmd_eco_mode_9, local_cmd_eco_mode_9},           // eco mode
///*26*/  {DP_TYPE9_ID_70, DP_VAL,  4,    10, remote_cmd_eco_mode_temp_9, local_cmd_eco_mode_temp_9}, // eco mode's temperature
///*27*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
///*28*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
///*29*/  {DP_TYPE9_ID_1C, DP_BOOL, 1,    1,  remote_cmd_setting_reset_9, local_cmd_setting_reset_9}, // default setting
///*30*/  {DP_TYPE9_ID_74, DP_ENUM, 4,    1,  remote_cmd_inversion_9, local_cmd_inversion_9},         // type relay NC or NO (inversion)
///*31*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
///*32*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
///*33*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
///*34*/  {DP_TYPE9_ID_73, DP_VAL,  4,    1,  remote_cmd_ext_temp_calibration_9, local_cmd_ext_temp_calibration_9}, // external sensor calibration
///*35*/  {DP_TYPE9_ID_75, DP_ENUM, 1,    1,  remote_cmd_mode_keylock_9, local_cmd_mode_keylock_9},   // mode key lock
//};

void remote_cmd_mode_keylock_9(void *args) {

    uint8_t *mode = (uint8_t*)args;

    if (*mode != 0x00 && *mode != 0x01) {
        return;
    }

    printf("remote_cmd_mode_keylock_9: %d\r\n", *mode);

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_MODE_LOCK].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_MODE_LOCK].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    if (*mode == 0x00) {
        data_point->data[0] = 0x00;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_to_ring_cmd(out_pkt, true);
        set_seq_num(seq_num);
    } else if (*mode == 0x01) {
        data_point->data[0] = 0x01;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_to_ring_cmd(out_pkt, true);
        set_seq_num(seq_num);
    }

    thermostat_settings_save();
}

void remote_cmd_deadband_9(void *args) {

    uint8_t *arg = (uint8_t*)args;
    uint32_t hysteresis = *arg;

    if (data_point_model[DP_IDX_DEADZONE].id == 0) return;

    /* 5 -> 0.5°C ... 50 -> 5°C */
    if (hysteresis < data_point_model[DP_IDX_DEADZONE].arg1) hysteresis = data_point_model[DP_IDX_DEADZONE].arg1;
    if (hysteresis > data_point_model[DP_IDX_DEADZONE].arg2) hysteresis = data_point_model[DP_IDX_DEADZONE].arg2;

//    if (hysteresis > data_point_model[DP_IDX_EXT_CALIBRATION].arg2 || hysteresis > data_point_model[DP_IDX_DEADZONE].arg2) {
//        return;
//    }

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


void local_cmd_mode_keylock_9(void *args) {

    uint8_t *mode = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_MODE_KEYLOCK, (uint8_t*)mode);

    thermostat_settings_save();
}

