#include "app_main.h"

/* data point for manufacturer id -
 * "lzriup1j"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */

#define R06_ABS_HEAT_MIN            500
#define R06_ABS_HEAT_MAX            6000
#define R06_HEAT_MAX_MIN            1500        // * 100
#define R06_HEAT_MAX_MAX            6000        // * 100
#define R06_HEAT_PROTECT_MIN        3500        // * 100
#define R06_HEAT_PROTECT_MAX        6000        // * 100
#define R06_DEADZONE_MIN            5           // 0.5
#define R06_DEADZONE_MAX            100         // 10
#define R06_CALIBRATION_MIN        -99          // * 1
#define R06_CALIBRATION_MAX         99          // * 1

#define DP_IDX_SCHEDULE_MODE        DP_IDX_SCHEDULE_MON

//data_point_st_t data_point_model6[DP_IDX_MAXNUM];

data_point_st_t *init_datapoint_model6() {

    memset(data_point_model_common, 0, sizeof(data_point_model_common));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = R06_ABS_HEAT_MIN;       // min +5°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = R06_ABS_HEAT_MAX;       // max +45°C

    data_point_model_common[DP_IDX_ONOFF].id = DP_TYPE6_ID_01;
    data_point_model_common[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model_common[DP_IDX_ONOFF].len = 1;
    data_point_model_common[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_6;
    data_point_model_common[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_6;

    data_point_model_common[DP_IDX_TEMP].id = DP_TYPE6_ID_03;
    data_point_model_common[DP_IDX_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP].len = 4;
    data_point_model_common[DP_IDX_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_6;

    data_point_model_common[DP_IDX_SETPOINT].id = DP_TYPE6_ID_02;
    data_point_model_common[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model_common[DP_IDX_SETPOINT].len = 4;
    data_point_model_common[DP_IDX_SETPOINT].divisor = 10;
    data_point_model_common[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_6;
    data_point_model_common[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_6;

    data_point_model_common[DP_IDX_MAX].id = DP_TYPE6_ID_0F;
    data_point_model_common[DP_IDX_MAX].type = DP_VAL;
    data_point_model_common[DP_IDX_MAX].len = 4;
    data_point_model_common[DP_IDX_MAX].divisor = 10;
    data_point_model_common[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_6;
    data_point_model_common[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_6;
    data_point_model_common[DP_IDX_MAX].arg1 = R06_HEAT_MAX_MIN;
    data_point_model_common[DP_IDX_MAX].arg2 = R06_HEAT_MAX_MAX;

    data_point_model_common[DP_IDX_DEADZONE].id = DP_TYPE6_ID_6B;
    data_point_model_common[DP_IDX_DEADZONE].type = DP_VAL;
    data_point_model_common[DP_IDX_DEADZONE].len = 4;
    data_point_model_common[DP_IDX_DEADZONE].divisor = 1;
    data_point_model_common[DP_IDX_DEADZONE].remote_cmd = remote_cmd_deadband_6;
    data_point_model_common[DP_IDX_DEADZONE].local_cmd = local_cmd_deadband_6;
    data_point_model_common[DP_IDX_DEADZONE].arg1 = R06_DEADZONE_MIN;
    data_point_model_common[DP_IDX_DEADZONE].arg2 = R06_DEADZONE_MAX;

    data_point_model_common[DP_IDX_CALIBRATION].id = DP_TYPE6_ID_13;
    data_point_model_common[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model_common[DP_IDX_CALIBRATION].len = 4;
    data_point_model_common[DP_IDX_CALIBRATION].divisor = 1;
    data_point_model_common[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_6;
    data_point_model_common[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_6;
    data_point_model_common[DP_IDX_CALIBRATION].arg1 = R06_CALIBRATION_MIN;
    data_point_model_common[DP_IDX_CALIBRATION].arg2 = R06_CALIBRATION_MAX;

    data_point_model_common[DP_IDX_RUNSTATE].id = DP_TYPE6_ID_65;
    data_point_model_common[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model_common[DP_IDX_RUNSTATE].len = 1;
    data_point_model_common[DP_IDX_RUNSTATE].divisor = 1;
    data_point_model_common[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_6;

    data_point_model_common[DP_IDX_SENSOR].id = DP_TYPE6_ID_6A;
    data_point_model_common[DP_IDX_SENSOR].type = DP_ENUM;
    data_point_model_common[DP_IDX_SENSOR].len = 1;
    data_point_model_common[DP_IDX_SENSOR].divisor = 1;
    data_point_model_common[DP_IDX_SENSOR].remote_cmd = remote_cmd_sensor_used_6;
    data_point_model_common[DP_IDX_SENSOR].local_cmd = local_cmd_sensor_used_6;

    data_point_model_common[DP_IDX_PROG].id = DP_TYPE6_ID_04;
    data_point_model_common[DP_IDX_PROG].type = DP_ENUM;
    data_point_model_common[DP_IDX_PROG].len = 1;
    data_point_model_common[DP_IDX_PROG].divisor = 1;
    data_point_model_common[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_6;
    data_point_model_common[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_6;

    data_point_model_common[DP_IDX_LOCKUNLOCK].id = DP_TYPE6_ID_09;
    data_point_model_common[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model_common[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].divisor = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_6;
    data_point_model_common[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_6;

    data_point_model_common[DP_IDX_SCHEDULE].id = DP_TYPE6_ID_6D;
    data_point_model_common[DP_IDX_SCHEDULE].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE].len = 0x20;
    data_point_model_common[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_6;
    data_point_model_common[DP_IDX_SCHEDULE].local_cmd = local_cmd_set_schedule_6;

    data_point_model_common[DP_IDX_FROST_PROTECT].id = DP_TYPE6_ID_66;
    data_point_model_common[DP_IDX_FROST_PROTECT].type = DP_BOOL;
    data_point_model_common[DP_IDX_FROST_PROTECT].len = 1;
    data_point_model_common[DP_IDX_FROST_PROTECT].remote_cmd = remote_cmd_frost_protect_6;
    data_point_model_common[DP_IDX_FROST_PROTECT].local_cmd = local_cmd_frost_protect_6;

    data_point_model_common[DP_IDX_HEAT_PROTECT].id = DP_TYPE6_ID_6C;
    data_point_model_common[DP_IDX_HEAT_PROTECT].type = DP_VAL;
    data_point_model_common[DP_IDX_HEAT_PROTECT].len = 4;
    data_point_model_common[DP_IDX_HEAT_PROTECT].divisor = 1;
    data_point_model_common[DP_IDX_HEAT_PROTECT].remote_cmd = remote_cmd_heat_protect_6;
    data_point_model_common[DP_IDX_HEAT_PROTECT].local_cmd = local_cmd_heat_protect_6;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg1 = R06_HEAT_PROTECT_MIN;
    data_point_model_common[DP_IDX_HEAT_PROTECT].arg2 = R06_HEAT_PROTECT_MAX;

    data_point_model_common[DP_IDX_SCHEDULE_MON].id = DP_TYPE6_ID_68;
    data_point_model_common[DP_IDX_SCHEDULE_MON].type = DP_ENUM;
    data_point_model_common[DP_IDX_SCHEDULE_MON].len = 1;
    data_point_model_common[DP_IDX_SCHEDULE_MON].remote_cmd = remote_cmd_schedule_mode_6;
    data_point_model_common[DP_IDX_SCHEDULE_MON].local_cmd = remote_cmd_schedule_mode_6;

    data_point_model_common[DP_IDX_LEVEL_A].id = DP_TYPE6_ID_6E;
    data_point_model_common[DP_IDX_LEVEL_A].type = DP_ENUM;
    data_point_model_common[DP_IDX_LEVEL_A].len = 1;
    data_point_model_common[DP_IDX_LEVEL_A].remote_cmd = remote_cmd_level_6;
    data_point_model_common[DP_IDX_LEVEL_A].local_cmd = local_cmd_level_6;

    data_point_model_common[DP_IDX_SOUND].id = DP_TYPE6_ID_69;
    data_point_model_common[DP_IDX_SOUND].type = DP_BOOL;
    data_point_model_common[DP_IDX_SOUND].len = 1;
    data_point_model_common[DP_IDX_SOUND].remote_cmd = remote_cmd_sound_6;
    data_point_model_common[DP_IDX_SOUND].local_cmd = local_cmd_sound_6;

    data_point_model_common[DP_IDX_SETTINGS_RESET].id = DP_TYPE6_ID_67;
    data_point_model_common[DP_IDX_SETTINGS_RESET].type = DP_BOOL;
    data_point_model_common[DP_IDX_SETTINGS_RESET].len = 1;
    data_point_model_common[DP_IDX_SETTINGS_RESET].remote_cmd = remote_cmd_setting_reset_6;
    data_point_model_common[DP_IDX_SETTINGS_RESET].local_cmd = local_cmd_setting_reset_6;

    data_point_model_common[DP_IDX_INVERSION].id = DP_TYPE6_ID_6F;
    data_point_model_common[DP_IDX_INVERSION].type = DP_BOOL;
    data_point_model_common[DP_IDX_INVERSION].len = 1;
    data_point_model_common[DP_IDX_INVERSION].remote_cmd = remote_cmd_inversion_6;
    data_point_model_common[DP_IDX_INVERSION].local_cmd = local_cmd_inversion_6;

    return data_point_model_common;
}

//data_point_st_t data_point_model6[DP_IDX_MAXNUM] = {
//        {DP_TYPE6_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_6, local_cmd_onoff_state_6},        // onoff
//        {DP_TYPE6_ID_03, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_6},                        // local temperature
//        {DP_TYPE6_ID_02, DP_VAL,  4,    10, remote_cmd_heating_set_6, local_cmd_heating_set_6},     // heat setpoint
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // min heat setpoint
//        {DP_TYPE6_ID_0F, DP_VAL,  4,    10, remote_cmd_max_setpoint_6, local_cmd_max_setpoint_6},   // max heat setpoint
//        {DP_TYPE6_ID_6B, DP_VAL,  4,    1,  remote_cmd_deadband_6, local_cmd_deadband_6},           // hysteresis
//        {DP_TYPE6_ID_13, DP_VAL,  4,    1,  remote_cmd_temp_calibration_6, local_cmd_temp_calibration_6}, // local temperature calibration
//        {DP_TYPE6_ID_65, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_6},                       // 0x00 - heat, 0x01 - idle
//        {DP_TYPE6_ID_6A, DP_ENUM, 1,    1,  remote_cmd_sensor_used_6, local_cmd_sensor_used_6},     // sensor IN/AL/OU
//        {DP_TYPE6_ID_04, DP_ENUM, 1,    1,  remote_cmd_oper_mode_6, local_cmd_oper_mode_6},         // manual (setpoint) / programming (schedule)
//        {DP_TYPE6_ID_09, DP_BOOL, 1,    1,  remote_cmd_keylock_6, local_cmd_keylock_6},             // lock / unlock keys (child lock)
//        {DP_TYPE6_ID_6D, DP_RAW,  0x20, 1,  remote_cmd_set_schedule_6, local_cmd_set_schedule_6},   // schedule
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // temperature of outer sensor
//        {DP_TYPE6_ID_66, DP_BOOL, 1,    1,  remote_cmd_frost_protect_6, local_cmd_frost_protect_6}, // frost protected
//        {DP_TYPE6_ID_6C, DP_VAL,  4,    1,  remote_cmd_heat_protect_6, local_cmd_heat_protect_6},   // heat protected
//        {DP_TYPE6_ID_68, DP_ENUM, 1,    1,  remote_cmd_schedule_mode_6, local_cmd_schedule_mode_6}, // schedule mode
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // schedule tue
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // schedule wed
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // schedule thu
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // schedule fri
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // schedule sat
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // schedule sun
//        {DP_TYPE6_ID_6E, DP_ENUM, 1,    1,  remote_cmd_level_6, local_cmd_level_6},                 // level brightness of screen
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE6_ID_69, DP_BOOL, 1,    1,  remote_cmd_sound_6, local_cmd_sound_6},                 // sound on-off
//        {DP_TYPE6_ID_67, DP_BOOL, 1,    1,  remote_cmd_setting_reset_6, local_cmd_setting_reset_6}, // settings reset
//        {DP_TYPE6_ID_6F, DP_BOOL, 1,    1,  remote_cmd_inversion_6, local_cmd_inversion_6},         // inversion of output
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//};

/*
 *
 * Local variables and functions
 *
 */

static void get_schedule(void *args) {

    if (!zb_isDeviceJoinedNwk()) return;

    args_get_schedule_t *args_get_schedule = (args_get_schedule_t*)args;

    epInfo_t dstEpInfo;
    TL_SETSTRUCTCONTENT(dstEpInfo, 0);

    dstEpInfo.profileId = HA_PROFILE_ID;
#if FIND_AND_BIND_SUPPORT
    dstEpInfo.dstAddrMode = APS_DSTADDR_EP_NOTPRESETNT;
#else
    dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
    dstEpInfo.dstEp = APP_ENDPOINT1;
    dstEpInfo.dstAddr.shortAddr = 0x0;
#endif

    zcl_thermostat_setWeeklyScheduleCmd_t cmd;
    heatMode_t *heat_mode;

    cmd.dayOfWeekForSequence = 0;

    if (args_get_schedule->day & DAY_MON) {
        //mon
        heat_mode = g_zcl_scheduleData.schedule_mon;
        cmd.dayOfWeekForSequence = DAY_MON;
        cmd.numOfTransForSequence = 6;
    } else if (args_get_schedule->day & DAY_SUN) {
        //sun
        heat_mode = g_zcl_scheduleData.schedule_sun;
        cmd.dayOfWeekForSequence = DAY_SUN;
        cmd.numOfTransForSequence = 2;
    } else {
        return;
    }

    cmd.sequenceMode.pHeatMode = heat_mode;
    cmd.modeForSequence = HEAT_SERPOINT_FIELD_PRESENT;

//        for (uint8_t i = 0; i < cmd.numOfTransForSequence; i++) {
//            printf("i: %d, time: %d, temp: %d\r\n", i, cmd.sequenceMode.pHeatMode[i].transTime, cmd.sequenceMode.pHeatMode[i].heatSetpoint);
//        }

    if (args_get_schedule->rsp) {
        zcl_thermostat_getWeeklyScheduleRspCmdSend(APP_ENDPOINT1, &dstEpInfo, 0, args_get_schedule->seqNum, &cmd);
    } else {
        zcl_thermostat_setWeeklyScheduleCmdSend(APP_ENDPOINT1, &dstEpInfo, 0, &cmd);
    }
}

/*
 *
 * Global functions
 *
 */

/*
 *
 * For models   "lzriup1j"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_sensor_used_6(void *args) {

    uint8_t *sensor_used = (uint8_t*)args;

    if (*sensor_used == SENSOR_AL) {
        *sensor_used = SENSOR_OU;
    } else if (*sensor_used == SENSOR_OU){
        *sensor_used = SENSOR_AL;
    }

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED, (uint8_t*)sensor_used);

    thermostat_settings_save();
}

//void local_cmd_temp_calibration_6(void *args) {
//
//    int8_t *temp = (int8_t*)args;
//
//    if (data_point_model[DP_IDX_CALIBRATION].divisor == 10) {
//        *temp /= 10;
//    } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 100) {
//        *temp /= 100;
//    }
//
//    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION, (uint8_t*)temp);
//
//    thermostat_settings_save();
//}

void local_cmd_frost_protect_6(void *args) {

    uint8_t *frost = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT_ONOFF, (uint8_t*)frost);

    thermostat_settings_save();
}

void local_cmd_inversion_6(void *args) {

    uint8_t *inversion = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_INVERSION, (uint8_t*)inversion);

    thermostat_settings_save();
}

void local_cmd_level_6(void *args) {

    uint8_t *level = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_LEVEL, (uint8_t*)level);

    thermostat_settings_save();
}

void local_cmd_sound_6(void *args) {

    uint8_t *sound = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SOUND, (uint8_t*)sound);

    thermostat_settings_save();
}

void local_cmd_setting_reset_6(void *args) {

    uint8_t *settings = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SETTINGS_RESET, (uint8_t*)settings);

    thermostat_settings_save();
}

void local_cmd_schedule_mode_6(void *args) {

    uint8_t *mode = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SCHEDULE_MODE, mode);

    thermostat_settings_save();
}

void local_cmd_set_schedule_6(void *args) {

    data_point_t *data_point = (data_point_t*)args;

    uint8_t *ptr = data_point->data;

    dp_schedule_model6_t *schedule = (dp_schedule_model6_t*)ptr;

    for (uint8_t i = 0; i < 6; i++) {
        g_zcl_scheduleData.schedule_mon[i].transTime = schedule->hour * 60;
        g_zcl_scheduleData.schedule_mon[i].transTime += schedule->minute;
        g_zcl_scheduleData.schedule_mon[i].heatSetpoint = reverse16(schedule->temperature)  * 10;
        schedule++;

#if UART_PRINTF_MODE && DEBUG_SCHEDULE
        printf("mon. i: %d, time: 0x%x, temp: 0x%x\r\n", i, g_zcl_scheduleData.schedule_mon[i].transTime,
                g_zcl_scheduleData.schedule_mon[i].heatSetpoint);
#endif
    }

    for (uint8_t i = 0; i < 2; i++) {
        g_zcl_scheduleData.schedule_sun[i].transTime = schedule->hour * 60;
        g_zcl_scheduleData.schedule_sun[i].transTime += schedule->minute;
        g_zcl_scheduleData.schedule_sun[i].heatSetpoint = reverse16(schedule->temperature)  * 10;
        schedule++;

#if UART_PRINTF_MODE && DEBUG_SCHEDULE
        printf("sun. i: %d, time: 0x%x, temp: 0x%x\r\n", i, g_zcl_scheduleData.schedule_sun[i].transTime,
                g_zcl_scheduleData.schedule_sun[i].heatSetpoint);
#endif
    }

    thermostat_settings_save();

    args_get_schedule_sun.day = DAY_SUN;
    args_get_schedule_sun.rsp = false;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_sun);
    args_get_schedule_mon.day = DAY_MON;
    args_get_schedule_mon.rsp = false;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_mon);
}


/*
 *
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_sensor_used_6(void *args) {

    /*
     * all
     * 0 - IN
     * 1 - ALL
     * 2 - OUT
     *
     * current
     * 0 - IN
     * 1 - OUT
     * 2 - ALL
     *
     */

    uint8_t *sensor_used = (uint8_t*)args;

    if (data_point_model[DP_IDX_SENSOR].id == 0) return;

    if (*sensor_used != SENSOR_IN && *sensor_used != SENSOR_AL && *sensor_used != SENSOR_OU) {
        return;
    }

    /* args points directly at ZCL attribute RAM. Swap into a local so we don't
     * corrupt the ZCL view of the attribute with the MCU-side encoding. */
    uint8_t mcu_sensor = *sensor_used;
    if (mcu_sensor == SENSOR_AL) {
        mcu_sensor = SENSOR_OU;
    } else if (mcu_sensor == SENSOR_OU) {
        mcu_sensor = SENSOR_AL;
    }

//    printf("sensor_used: %d\r\n", mcu_sensor);

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
    data_point->data[0] = mcu_sensor;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}


//void remote_cmd_temp_calibration_6(void *args) {
//
//    int8_t *arg = (int8_t*)args;
//    int8_t temp = *arg;
//
//    if(data_point_model[DP_IDX_CALIBRATION].id == 0) return;
//
//    if (temp < data_point_model[DP_IDX_CALIBRATION].arg1) temp = data_point_model[DP_IDX_CALIBRATION].arg1;
//    if (temp > data_point_model[DP_IDX_CALIBRATION].arg2) temp = data_point_model[DP_IDX_CALIBRATION].arg2;
//
////    if (temp < data_point_model[DP_IDX_CALIBRATION].arg1 || temp > data_point_model[DP_IDX_CALIBRATION].arg2) {
////        return;
////    }
//
//    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
//    uint16_t seq_num = get_seq_num();
//    seq_num++;
//
//    if (data_point_model[DP_IDX_CALIBRATION].divisor == 10) {
//        temp *= 10;
//    } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 100) {
//        temp *= 100;
//    }
//
//    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);
//
//    out_pkt->len = reverse16(8);
//    out_pkt->pkt_len++;
//    out_pkt->pkt_len++;
//
//    data_point_t *data_point = (data_point_t*)out_pkt->data;
//    data_point->dp_id = data_point_model[DP_IDX_CALIBRATION].id;
//    out_pkt->pkt_len++;
//    data_point->dp_type = data_point_model[DP_IDX_CALIBRATION].type;
//    out_pkt->pkt_len++;
//    data_point->dp_len = (reverse16(4));
//    out_pkt->pkt_len++;
//    out_pkt->pkt_len++;
//    int32_t dev_temp = temp;
//    data_point->data[0] = (dev_temp >> 24) & 0xFF;
//    data_point->data[1] = (dev_temp >> 16) & 0xFF;
//    data_point->data[2] = (dev_temp >> 8)  & 0xFF;
//    data_point->data[3] = dev_temp & 0xFF;
//    out_pkt->pkt_len += 4;
//    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
//    add_to_ring_cmd(out_pkt, true);
//
//    set_seq_num(seq_num);
//
//    thermostat_settings_save();
//}

void remote_cmd_deadband_6(void *args) {

    uint8_t *arg = (uint8_t*)args;
    uint32_t hysteresis = *arg;

    if (data_point_model[DP_IDX_DEADZONE].id == 0) return;

    /* 5 -> 0.5°C ... 100 -> 10°C */
    if (hysteresis < data_point_model[DP_IDX_DEADZONE].arg1) hysteresis = data_point_model[DP_IDX_DEADZONE].arg1;
    if (hysteresis > data_point_model[DP_IDX_DEADZONE].arg2) hysteresis = data_point_model[DP_IDX_DEADZONE].arg2;

//    if (hysteresis < data_point_model[DP_IDX_DEADZONE].arg1 || hysteresis > data_point_model[DP_IDX_DEADZONE].arg2) {
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

//    printf("hysteresis: %d\r\n", hysteresis);

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

void remote_cmd_max_setpoint_6(void *args) {

    uint16_t *arg = (uint16_t*)args;
    uint32_t max_temp = *arg;

    if (data_point_model[DP_IDX_MAX].id == 0) return;

    if (max_temp < data_point_model[DP_IDX_MAX].arg1) max_temp = data_point_model[DP_IDX_MAX].arg1;
    if (max_temp > data_point_model[DP_IDX_MAX].arg2) max_temp = data_point_model[DP_IDX_MAX].arg2;

//    if (max_temp < data_point_model[DP_IDX_MAX].arg1 || max_temp > data_point_model[DP_IDX_MAX].arg2) {
//        return;
//    }

//    if (max_temp < 1500 || max_temp > 9500) {
//        return;
//    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

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

//void remote_cmd_oper_mode_6(void *args) {
//
//    uint8_t *oper_mode = (uint8_t*)args;
//
//    printf("oper_mode: 0x%x\r\n", *oper_mode);
//
//    if (data_point_model[DP_IDX_PROG].id == 0) return;
//
//    if (*oper_mode > 2) return;
//
//    printf("oper_mode: 0x%x\r\n", *oper_mode);
//
//    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
//    uint16_t seq_num = get_seq_num();
//    seq_num++;
//
//    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);
//
//    out_pkt->len = reverse16(5);
//    out_pkt->pkt_len++;
//    out_pkt->pkt_len++;
//
//    data_point_t *data_point = (data_point_t*)out_pkt->data;
//    data_point->dp_id = data_point_model[DP_IDX_PROG].id;
//    out_pkt->pkt_len++;
//    data_point->dp_type = data_point_model[DP_IDX_PROG].type;
//    out_pkt->pkt_len++;
//    data_point->dp_len = (reverse16(1));
//    out_pkt->pkt_len++;
//    out_pkt->pkt_len++;
//    data_point->data[0] = *oper_mode;
//    out_pkt->pkt_len ++;
//    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
//    add_to_ring_cmd(out_pkt, true);
//
//    set_seq_num(seq_num);
//
//    thermostat_settings_save();
//}

void remote_cmd_heat_protect_6(void *args) {

    int16_t *arg = (int16_t*)args;
    uint32_t heat_protect = *arg;

    if (data_point_model[DP_IDX_HEAT_PROTECT].id == 0) return;

    if (heat_protect < data_point_model[DP_IDX_HEAT_PROTECT].arg1) heat_protect = data_point_model[DP_IDX_HEAT_PROTECT].arg1;
    if (heat_protect > data_point_model[DP_IDX_HEAT_PROTECT].arg2) heat_protect = data_point_model[DP_IDX_HEAT_PROTECT].arg2;

//    if (heat_protect < data_point_model[DP_IDX_HEAT_PROTECT].arg1 || heat_protect > data_point_model[DP_IDX_HEAT_PROTECT].arg2) {
//        return;
//    }

    heat_protect /= 100; // 3500 -> 35°C

    if (data_point_model[DP_IDX_HEAT_PROTECT].divisor == 10) {
        heat_protect *= 10;
    } else if (data_point_model[DP_IDX_HEAT_PROTECT].divisor == 100) {
        heat_protect *= 100;
    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_HEAT_PROTECT].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_HEAT_PROTECT].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (heat_protect >> 24) & 0xFF;
    data_point->data[1] = (heat_protect >> 16) & 0xFF;
    data_point->data[2] = (heat_protect >> 8)  & 0xFF;
    data_point->data[3] = heat_protect & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();

}

void remote_cmd_frost_protect_6(void *args) {


    uint8_t *frost = (uint8_t*)args;

    if (data_point_model[DP_IDX_FROST_PROTECT].id == 0) return;

    if (*frost > 1) {
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
    data_point->dp_id = data_point_model[DP_IDX_FROST_PROTECT].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_FROST_PROTECT].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *frost;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_inversion_6(void *args) {


    uint8_t *inversion = (uint8_t*)args;

    if (data_point_model[DP_IDX_INVERSION].id == 0) return;

    if (*inversion > 1) {
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
    data_point->dp_id = data_point_model[DP_IDX_INVERSION].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_INVERSION].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *inversion;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_level_6(void *args) {


    uint8_t *level = (uint8_t*)args;

    if (data_point_model[DP_IDX_LEVEL_A].id == 0) return;

    if (*level > 3) {
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
    data_point->dp_id = data_point_model[DP_IDX_LEVEL_A].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LEVEL_A].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *level;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_sound_6(void *args) {


    uint8_t *sound = (uint8_t*)args;

    if (data_point_model[DP_IDX_SOUND].id == 0) return;

    if (*sound > 1) {
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
    data_point->dp_id = data_point_model[DP_IDX_SOUND].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SOUND].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *sound;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_setting_reset_6(void *args) {


    uint8_t *settings = (uint8_t*)args;

    if (data_point_model[DP_IDX_SETTINGS_RESET].id == 0) return;

    if (*settings > 1) {
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
    data_point->dp_id = data_point_model[DP_IDX_SETTINGS_RESET].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SETTINGS_RESET].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *settings;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_schedule_mode_6(void *args) {


    uint8_t *mode = (uint8_t*)args;

    if (data_point_model[DP_IDX_SCHEDULE_MODE].id == 0) return;

    if (*mode > 3) {
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
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_MODE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_MODE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *mode;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_set_schedule_6(void *args) {

    args_get_schedule_any.day = *(uint8_t*)args;

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(data_point_model[DP_IDX_SCHEDULE].len+4);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE].len));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    uint8_t *pstrd = data_point->data;
    heatMode_t *heat_mode = g_zcl_scheduleData.schedule_mon;
    uint16_t temp;

    for (uint8_t i = 0; i < 6; i++) {
        *pstrd++ = heat_mode[i].transTime/60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime%60;
        out_pkt->pkt_len++;
        temp = heat_mode[i].heatSetpoint / 10;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    heat_mode = g_zcl_scheduleData.schedule_sun;

    for (uint8_t i = 0; i < 2; i++) {
        *pstrd++ = heat_mode[i].transTime/60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime%60;
        out_pkt->pkt_len++;
        temp = heat_mode[i].heatSetpoint / 10;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);

    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();

    if (args_get_schedule_any.day & DAY_MON) {
        //mon
        args_get_schedule_any.rsp = false;
        TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_any);
    }

    if (args_get_schedule_any.day & DAY_SUN){
        //sun
        args_get_schedule_any.rsp = false;
        TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_any);
    }

}

void remote_cmd_get_schedule_6(void *args) {

    uint8_t *seqNum = (uint8_t*)args;

    args_get_schedule_sun.day = DAY_SUN;
    args_get_schedule_sun.seqNum = *seqNum;
    args_get_schedule_sun.rsp = true;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_sun);

    args_get_schedule_mon.day = DAY_MON;
    args_get_schedule_mon.rsp = false;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_mon);
}

