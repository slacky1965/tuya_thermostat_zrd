#include "tl_common.h"
#include "zcl_include.h"

#include "app_main.h"

#ifndef ZCL_BASIC_MFG_NAME
#define ZCL_BASIC_MFG_NAME          {6,'T','E','L','I','N','K'}
#endif
#ifndef ZCL_BASIC_MODEL_ID
#define ZCL_BASIC_MODEL_ID          {8,'T','L','S','R','8','2','x','x'}
#endif
#ifndef ZCL_BASIC_SW_BUILD_ID
#define ZCL_BASIC_SW_BUILD_ID       {10,'0','1','2','2','0','5','2','0','1','7'}
#endif

#define R               ACCESS_CONTROL_READ
#define RW              ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE
#define RR              ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE
#define RWR             ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE | ACCESS_CONTROL_REPORTABLE

#define ZCL_UINT8       ZCL_DATA_TYPE_UINT8
#define ZCL_INT8        ZCL_DATA_TYPE_INT8
#define ZCL_UINT16      ZCL_DATA_TYPE_UINT16
#define ZCL_INT16       ZCL_DATA_TYPE_INT16
#define ZCL_UINT32      ZCL_DATA_TYPE_UINT32
#define ZCL_ENUM8       ZCL_DATA_TYPE_ENUM8
#define ZCL_BOOLEAN     ZCL_DATA_TYPE_BOOLEAN
#define ZCL_BITMAP8     ZCL_DATA_TYPE_BITMAP8
#define ZCL_BITMAP16    ZCL_DATA_TYPE_BITMAP16
#define ZCL_CHAR_STR    ZCL_DATA_TYPE_CHAR_STR
#define ZCL_UTC         ZCL_DATA_TYPE_UTC

/**
 *  @brief Definition for Incoming cluster / Sever Cluster
 */
const uint16_t app_ep1_inClusterList[] = {
    ZCL_CLUSTER_GEN_BASIC,
    ZCL_CLUSTER_GEN_IDENTIFY,
#ifdef ZCL_GROUP
    ZCL_CLUSTER_GEN_GROUPS,
#endif
#ifdef ZCL_SCENE
    ZCL_CLUSTER_GEN_SCENES,
#endif
#ifdef ZCL_ON_OFF
    ZCL_CLUSTER_GEN_ON_OFF,
#endif
#ifdef ZCL_ZLL_COMMISSIONING
    ZCL_CLUSTER_TOUCHLINK_COMMISSIONING,
#endif
#ifdef ZCL_LEVEL_CTRL
    ZCL_CLUSTER_GEN_LEVEL_CONTROL,
#endif
#ifdef ZCL_THERMOSTAT
    ZCL_CLUSTER_HAVC_THERMOSTAT,
    ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG,
#endif
#ifdef ZCL_FANCONTROL
    ZCL_CLUSTER_HAVC_FAN_CONTROL,
#endif
    ZCL_CLUSTER_MS_RELATIVE_HUMIDITY,
};

/**
 *  @brief Definition for Outgoing cluster / Client Cluster
 */
const uint16_t app_ep1_outClusterList[] = {
#ifdef ZCL_OTA
    ZCL_CLUSTER_OTA,
    ZCL_CLUSTER_GEN_TIME,
#endif
};

/**
 *  @brief Definition for Server cluster number and Client cluster number
 */
#define APP_EP1_IN_CLUSTER_NUM   (sizeof(app_ep1_inClusterList)/sizeof(app_ep1_inClusterList[0]))
#define APP_EP1_OUT_CLUSTER_NUM  (sizeof(app_ep1_outClusterList)/sizeof(app_ep1_outClusterList[0]))

const uint16_t app_ep2_inClusterList[] = {
#ifdef ZCL_LEVEL_CTRL
    ZCL_CLUSTER_GEN_LEVEL_CONTROL,
#endif
};

const uint16_t app_ep2_outClusterList[] = {
};

#define APP_EP2_IN_CLUSTER_NUM   (sizeof(app_ep2_inClusterList)/sizeof(app_ep2_inClusterList[0]))
#define APP_EP2_OUT_CLUSTER_NUM  (sizeof(app_ep2_outClusterList)/sizeof(app_ep2_outClusterList[0]))

/**
 *  @brief Definition for simple description for HA profile
 */
const af_simple_descriptor_t app_ep1Desc = {
    HA_PROFILE_ID,                          /* Application profile identifier */
    HA_DEV_THERMOSTAT,                      /* Application device identifier */
    APP_ENDPOINT1,                          /* Endpoint */
    2,                                      /* Application device version */
    0,                                      /* Reserved */
    APP_EP1_IN_CLUSTER_NUM,                 /* Application input cluster count */
    APP_EP1_OUT_CLUSTER_NUM,                /* Application output cluster count */
    (uint16_t *)app_ep1_inClusterList,      /* Application input cluster list */
    (uint16_t *)app_ep1_outClusterList,     /* Application output cluster list */
};


const af_simple_descriptor_t app_ep2Desc = {
    HA_PROFILE_ID,                          /* Application profile identifier */
    HA_DEV_THERMOSTAT,                      /* Application device identifier */
    APP_ENDPOINT2,                          /* Endpoint */
    2,                                      /* Application device version */
    0,                                      /* Reserved */
    APP_EP2_IN_CLUSTER_NUM,                 /* Application input cluster count */
    APP_EP2_OUT_CLUSTER_NUM,                /* Application output cluster count */
    (uint16_t *)app_ep2_inClusterList,      /* Application input cluster list */
    (uint16_t *)app_ep2_outClusterList,     /* Application output cluster list */
};


/* Basic */
zcl_basicAttr_t g_zcl_basicAttrs =
{
    .zclVersion     = 0x03,
    .appVersion     = APP_RELEASE,
    .stackVersion   = (STACK_RELEASE|STACK_BUILD),
    .hwVersion      = HW_VERSION,
    .manuName       = ZCL_BASIC_MFG_NAME,
    .modelId        = ZCL_BASIC_MODEL_ID,
    .dateCode       = ZCL_BASIC_DATE_CODE,
    .powerSource    = POWER_SOURCE_MAINS_1_PHASE,
    .swBuildId      = ZCL_BASIC_SW_BUILD_ID,
    .deviceEnable   = TRUE,
};

const zclAttrInfo_t basic_attrTbl[] =
{
    { ZCL_ATTRID_BASIC_ZCL_VER,             ZCL_UINT8,      R,  (uint8_t*)&g_zcl_basicAttrs.zclVersion  },
    { ZCL_ATTRID_BASIC_APP_VER,             ZCL_UINT8,      R,  (uint8_t*)&g_zcl_basicAttrs.appVersion  },
    { ZCL_ATTRID_BASIC_STACK_VER,           ZCL_UINT8,      R,  (uint8_t*)&g_zcl_basicAttrs.stackVersion},
    { ZCL_ATTRID_BASIC_HW_VER,              ZCL_UINT8,      R,  (uint8_t*)&g_zcl_basicAttrs.hwVersion   },
    { ZCL_ATTRID_BASIC_MFR_NAME,            ZCL_CHAR_STR,   R,  (uint8_t*)g_zcl_basicAttrs.manuName     },
    { ZCL_ATTRID_BASIC_MODEL_ID,            ZCL_CHAR_STR,   R,  (uint8_t*)g_zcl_basicAttrs.modelId      },
    { ZCL_ATTRID_BASIC_DATE_CODE,           ZCL_CHAR_STR,   R,  (uint8_t*)g_zcl_basicAttrs.dateCode     },
    { ZCL_ATTRID_BASIC_POWER_SOURCE,        ZCL_ENUM8,      R,  (uint8_t*)&g_zcl_basicAttrs.powerSource },
    { ZCL_ATTRID_BASIC_DEV_ENABLED,         ZCL_BOOLEAN,    RW, (uint8_t*)&g_zcl_basicAttrs.deviceEnable},
    { ZCL_ATTRID_BASIC_SW_BUILD_ID,         ZCL_CHAR_STR,   R,  (uint8_t*)&g_zcl_basicAttrs.swBuildId   },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (uint8_t*)&zcl_attr_global_clusterRevision},

};

#define ZCL_BASIC_ATTR_NUM       sizeof(basic_attrTbl) / sizeof(zclAttrInfo_t)


/* Identify */
zcl_identifyAttr_t g_zcl_identifyAttrs =
{
    .identifyTime   = 0x0000,
};

const zclAttrInfo_t identify_attrTbl[] =
{
    { ZCL_ATTRID_IDENTIFY_TIME,             ZCL_UINT16,     RW, (uint8_t*)&g_zcl_identifyAttrs.identifyTime},

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (uint8_t*)&zcl_attr_global_clusterRevision},
};

#define ZCL_IDENTIFY_ATTR_NUM           sizeof(identify_attrTbl) / sizeof(zclAttrInfo_t)

#ifdef ZCL_GROUP
/* Group */
zcl_groupAttr_t g_zcl_group1Attrs =
{
    .nameSupport    = 0,
};

const zclAttrInfo_t group_attr1Tbl[] =
{
    { ZCL_ATTRID_GROUP_NAME_SUPPORT,        ZCL_BITMAP8,    R,  (uint8_t*)&g_zcl_group1Attrs.nameSupport},

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (uint8_t*)&zcl_attr_global_clusterRevision},
};

#define ZCL_GROUP_1ATTR_NUM    sizeof(group_attr1Tbl) / sizeof(zclAttrInfo_t)

#endif

#ifdef ZCL_SCENE
/* Scene */
zcl_sceneAttr_t g_zcl_scene1Attrs = {
    .sceneCount     = 0,
    .currentScene   = 0,
    .currentGroup   = 0x0000,
    .sceneValid     = FALSE,
    .nameSupport    = 0,
};

const zclAttrInfo_t scene_attr1Tbl[] = {
    { ZCL_ATTRID_SCENE_SCENE_COUNT,         ZCL_UINT8,      R,  (uint8_t*)&g_zcl_scene1Attrs.sceneCount   },
    { ZCL_ATTRID_SCENE_CURRENT_SCENE,       ZCL_UINT8,      R,  (uint8_t*)&g_zcl_scene1Attrs.currentScene },
    { ZCL_ATTRID_SCENE_CURRENT_GROUP,       ZCL_UINT16,     R,  (uint8_t*)&g_zcl_scene1Attrs.currentGroup },
    { ZCL_ATTRID_SCENE_SCENE_VALID,         ZCL_BOOLEAN,    R,  (uint8_t*)&g_zcl_scene1Attrs.sceneValid   },
    { ZCL_ATTRID_SCENE_NAME_SUPPORT,        ZCL_BITMAP8,    R,  (uint8_t*)&g_zcl_scene1Attrs.nameSupport  },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (uint8_t*)&zcl_attr_global_clusterRevision},
};

#define ZCL_SCENE_1ATTR_NUM   sizeof(scene_attr1Tbl) / sizeof(zclAttrInfo_t)

#endif

#ifdef ZCL_LEVEL_CTRL
/* Level */
zcl_levelAttr_t g_zcl_levelAttrs = {
    .currentLevelA = 6,
    .currentLevelB = 6,
    .minLevelA = 0,
    .maxLevelA = 8,
    .minLevelB = 0,
    .maxLevelB = 8,
    .optionsA  = 1,
    .optionsB  = 1,
};

const zclAttrInfo_t levelA_attrTbl[] =
{
    { ZCL_ATTRID_LEVEL_CURRENT_LEVEL,       ZCL_UINT8,      RR, (uint8_t*)&g_zcl_levelAttrs.currentLevelA },
    { ZCL_ATTRID_LEVEL_MIN_LEVEL,           ZCL_UINT8,      R,  (uint8_t*)&g_zcl_levelAttrs.minLevelA     },
    { ZCL_ATTRID_LEVEL_MAX_LEVEL,           ZCL_UINT8,      R,  (uint8_t*)&g_zcl_levelAttrs.maxLevelA     },
    { ZCL_ATTRID_LEVEL_OPTIONS,             ZCL_BITMAP8,    RW, (uint8_t*)&g_zcl_levelAttrs.optionsA      },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (u8*)&zcl_attr_global_clusterRevision     },
};

#define ZCL_LEVEL_A_ATTR_NUM   sizeof(levelA_attrTbl) / sizeof(zclAttrInfo_t)

const zclAttrInfo_t levelB_attrTbl[] =
{
    { ZCL_ATTRID_LEVEL_CURRENT_LEVEL,       ZCL_UINT8,      RR, (uint8_t*)&g_zcl_levelAttrs.currentLevelB },
    { ZCL_ATTRID_LEVEL_MIN_LEVEL,           ZCL_UINT8,      R,  (uint8_t*)&g_zcl_levelAttrs.minLevelB     },
    { ZCL_ATTRID_LEVEL_MAX_LEVEL,           ZCL_UINT8,      R,  (uint8_t*)&g_zcl_levelAttrs.maxLevelB     },
    { ZCL_ATTRID_LEVEL_OPTIONS,             ZCL_BITMAP8,    RW, (uint8_t*)&g_zcl_levelAttrs.optionsB      },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (u8*)&zcl_attr_global_clusterRevision     },
};

#define ZCL_LEVEL_B_ATTR_NUM   sizeof(levelB_attrTbl) / sizeof(zclAttrInfo_t)

#endif

zcl_timeAttr_t g_zcl_timeAttrs = {
    .time_utc   = 0xffffffff,
    .time_local = 0xffffffff,
};

const zclAttrInfo_t time_attrTbl[] =
{
    { ZCL_ATTRID_TIME,                      ZCL_UTC,    RW, (uint8_t*)&g_zcl_timeAttrs.time_utc         },
    { ZCL_ATTRID_LOCAL_TIME,                ZCL_UINT32, R,  (uint8_t*)&g_zcl_timeAttrs.time_local       },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16, R,  (uint8_t*)&zcl_attr_global_clusterRevision  },
};

#define ZCL_TIME_ATTR_NUM    sizeof(time_attrTbl) / sizeof(zclAttrInfo_t)

zcl_humidityAttr_t g_zcl_humidityAttrs = {
        .value = 0xffff,    /* humidity unknown  */
        .minValue = 0x0000,
        .maxValue = 0x2710, /* 100.00              */
        .humidity_offset = 0,
};


const zclAttrInfo_t humidity_attrTbl[] = {
        { ZCL_RELATIVE_HUMIDITY_MEASUREMENT_ATTRID_MEASUREDVALUE,       ZCL_UINT16,     RR,     (uint8_t*)&g_zcl_humidityAttrs.value            },
        { ZCL_RELATIVE_HUMIDITY_MEASUREMENT_ATTRID_MINMEASUREDVALUE,    ZCL_UINT16,     R,      (uint8_t*)&g_zcl_humidityAttrs.minValue         },
        { ZCL_RELATIVE_HUMIDITY_MEASUREMENT_ATTRID_MAXMEASUREDVALUE,    ZCL_UINT16,     R,      (uint8_t*)&g_zcl_humidityAttrs.maxValue         },
        { ZCL_RELATIVE_HUMIDITY_MEASUREMENT_ATTRID_CUSTOM_HUMIDITY_OFFSET, ZCL_INT16,   RWR,    (uint8_t*)&g_zcl_humidityAttrs.humidity_offset  },

        { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,                           ZCL_UINT16,     R,      (uint8_t*)&zcl_attr_global_clusterRevision      },
};

#define ZCL_HUMIDITY_ATTR_NUM   sizeof(humidity_attrTbl) / sizeof(zclAttrInfo_t)


#ifdef ZCL_THERMOSTAT

zcl_thermostatAttr_t g_zcl_thermostatAttrs = {
    .localTemperature = 2200,               // 22°C * 100
    .outDoorTemperature = 2400,             // 24°C * 100
    .absMinHeatSetpointLimit = 500,         // min  5°C * 100 ( +5°C ... +15°C)
    .absMaxHeatSetpointLimit = 4500,        // max 45°C * 100 (+15°C ... +45°C)
    .minHeatSetpointLimit = 500,            // min  5°C * 100 ( +5°C ... +15°C)
    .maxHeatSetpointLimit = 4500,           // max 45°C * 100 (+15°C ... +45°C)
    .localTemperatureCalibration = 0,       // in device -9°C...+9°C
    .occupiedHeatingSetpoint = 2200,        // set 22°C * 100
    .controlSequenceOfOperation = 0x02,     // 0x02 Heating
    .systemMode = SYS_MODE_OFF,             // see /src/zcl/zcl_app_thermostat.h
    .runningState = 0x0000,                 // 0x0000 - off, 0x0001 - heat
    .manual_progMode = 0x00,                // 0x00 - manual mode, 0x01 - programming mode
    .sensor_used = SENSOR_IN,               // IN, ALL, OU
    .frostProtect = 0,
    .heatProtect = 4500,
    .dead_band = HYSTERESIS_MIN,            // 1 ... 5 °C
    .temperatureDisplayMode = 0x00,         // 0x00 - °C, 0x01 - °F (Not support)
    .keypadLockout = 0x00,                  // on off
    .modeKeyLock = 0x01,
    .startOfWeek = DAY_MON,                 // 1 - Monday
    .weeklyTransNum = 3,                    // 1 - Mon-Fri, 2 - Sat, 3 - Sun
    .dailyTransNum = 4,
    .ecoMode = 0,                           // 0 - off, 1 - on
    .ecoModeHeatTemperature = 2000,         // 20°C * 100
    .ecoModeCoolTemperature = 2000,         // 20°C * 100
    .sound = 1,
    .schedule_mode = 1,
    .frost_protect_onoff = 0,
    .level = 3,
    .settings_reset = 0,
    .extTemperatureCalibration = 0,
    .manuf_name = 0,
};


const zclAttrInfo_t thermostat_attrTbl[] = {
        { ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMPERATURE,             ZCL_INT16,      RR,     (uint8_t*)&g_zcl_thermostatAttrs.localTemperature           },
        { ZCL_ATTRID_HVAC_THERMOSTAT_OUTDOOR_TEMPERATURE,           ZCL_INT16,      RR,     (uint8_t*)&g_zcl_thermostatAttrs.outDoorTemperature         },
        { ZCL_ATTRID_HVAC_THERMOSTAT_ABS_MIN_HEAT_SETPOINT_LIMIT,   ZCL_INT16,      R,      (uint8_t*)&g_zcl_thermostatAttrs.absMinHeatSetpointLimit    },
        { ZCL_ATTRID_HVAC_THERMOSTAT_ABS_MAX_HEAT_SETPOINT_LIMIT,   ZCL_INT16,      R,      (uint8_t*)&g_zcl_thermostatAttrs.absMaxHeatSetpointLimit    },
        { ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT,       ZCL_INT16,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.minHeatSetpointLimit       },
        { ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT,       ZCL_INT16,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.maxHeatSetpointLimit       },
        { ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION,        ZCL_INT8,       RWR,    (uint8_t*)&g_zcl_thermostatAttrs.localTemperatureCalibration},
        { ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT,     ZCL_INT16,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.occupiedHeatingSetpoint    },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CTRL_SEQUENCE_OF_OPERATION,    ZCL_ENUM8,      R,      (uint8_t*)&g_zcl_thermostatAttrs.controlSequenceOfOperation },
        { ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,                      ZCL_ENUM8,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.systemMode                 },
        { ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE,    ZCL_BITMAP8,    RWR,    (uint8_t*)&g_zcl_thermostatAttrs.manual_progMode            },
        { ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE,                 ZCL_BITMAP16,   RR,     (uint8_t*)&g_zcl_thermostatAttrs.runningState               },
        { ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND,        ZCL_INT8,       RWR,    (uint8_t*)&g_zcl_thermostatAttrs.dead_band                  },
        { ZCL_ATTRID_HVAC_THERMOSTAT_START_OF_WEEK,                 ZCL_ENUM8,      R,      (uint8_t*)&g_zcl_thermostatAttrs.startOfWeek                },
        { ZCL_ATTRID_HVAC_THERMOSTAT_NUM_OF_WEEKLY_TRANSITIONS,     ZCL_INT8,       R,      (uint8_t*)&g_zcl_thermostatAttrs.weeklyTransNum             },
        { ZCL_ATTRID_HVAC_THERMOSTAT_NUM_OF_DAILY_TRANSITIONS,      ZCL_INT8,       R,      (uint8_t*)&g_zcl_thermostatAttrs.dailyTransNum              },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED,            ZCL_ENUM8,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.sensor_used                },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT,          ZCL_INT16,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.frostProtect               },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_HEAT_PROTECT,           ZCL_INT16,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.heatProtect                },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE,               ZCL_ENUM8,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.ecoMode                    },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE_HEAT_TEMPERATURE,  ZCL_INT16,  RWR,    (uint8_t*)&g_zcl_thermostatAttrs.ecoModeHeatTemperature     },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE_COOL_TEMPERATURE,  ZCL_INT16,  RWR,    (uint8_t*)&g_zcl_thermostatAttrs.ecoModeCoolTemperature     },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT_ONOFF,    ZCL_BOOLEAN,    RWR,    (uint8_t*)&g_zcl_thermostatAttrs.frost_protect_onoff        },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SETTINGS_RESET,         ZCL_BOOLEAN,    RWR,    (uint8_t*)&g_zcl_thermostatAttrs.settings_reset             },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SOUND,                  ZCL_BOOLEAN,    RWR,    (uint8_t*)&g_zcl_thermostatAttrs.sound                      },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_INVERSION,              ZCL_BOOLEAN,    RWR,    (uint8_t*)&g_zcl_thermostatAttrs.inversion                  },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SCHEDULE_MODE,          ZCL_ENUM8,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.schedule_mode              },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_LEVEL,                  ZCL_ENUM8,      RWR,    (uint8_t*)&g_zcl_thermostatAttrs.level                      },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_EXT_TEMP_CALIBRATION,   ZCL_INT8,       RWR,    (uint8_t*)&g_zcl_thermostatAttrs.extTemperatureCalibration  },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_MODE_KEYLOCK,           ZCL_BOOLEAN,    RWR,    (uint8_t*)&g_zcl_thermostatAttrs.modeKeyLock                },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_MANUF_NAME,             ZCL_ENUM8,      RW,     (uint8_t*)&g_zcl_thermostatAttrs.manuf_name                 },

        { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,                       ZCL_UINT16,     R,      (uint8_t*)&zcl_attr_global_clusterRevision                  },
};

#define ZCL_THERMOSTAT_ATTR_NUM   sizeof(thermostat_attrTbl) / sizeof(zclAttrInfo_t)

const zclAttrInfo_t thermostat_ui_cfg_attrTbl[] = {
        { ZCL_ATTRID_HVAC_TEMPERATURE_DISPLAY_MODE, ZCL_ENUM8,  RWR,    (uint8_t*)&g_zcl_thermostatAttrs.temperatureDisplayMode },
        { ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT,           ZCL_ENUM8,  RWR,    (uint8_t*)&g_zcl_thermostatAttrs.keypadLockout          },

        { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,       ZCL_UINT16, R,      (uint8_t*)&zcl_attr_global_clusterRevision              },
};

#define ZCL_THERMOSTAT_UIC_ATTR_NUM   sizeof(thermostat_ui_cfg_attrTbl) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_FANCONTROL

zcl_fancontrolAttr_t g_zcl_fancontrolAttrs = {
        .fanMode = 0,
        .fanModeSequence = FANMODESEQ_LOW_MED_HIGH_AUTO,
        .fanControl = 0,
};

const zclAttrInfo_t fancontrol_attrTbl[] = {
        { ZCL_ATTRID_HVAC_FANCONTROL_FANMODE,           ZCL_ENUM8,      RWR,    (uint8_t*)&g_zcl_fancontrolAttrs.fanMode         },
        { ZCL_ATTRID_HVAC_FANCONTROL_FANMODESEQ,        ZCL_ENUM8,      RW,     (uint8_t*)&g_zcl_fancontrolAttrs.fanModeSequence },
        { ZCL_ATTRID_HVAC_FANCONTROL_CUSTOM_CONTROL,    ZCL_BOOLEAN,    RWR,    (uint8_t*)&g_zcl_fancontrolAttrs.fanControl      },

        { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,       ZCL_UINT16, R,      (uint8_t*)&zcl_attr_global_clusterRevision       },
};

#define ZCL_FANCONTROL_ATTR_NUM   sizeof(fancontrol_attrTbl) / sizeof(zclAttrInfo_t)

#endif

/**
 *  @brief Definition for simple switch ZCL specific cluster
 */
const zcl_specClusterInfo_t g_appEp1ClusterList[] = {
    {ZCL_CLUSTER_GEN_BASIC,     MANUFACTURER_CODE_NONE, ZCL_BASIC_ATTR_NUM,     basic_attrTbl,      zcl_basic_register,     app_basicCb},
    {ZCL_CLUSTER_GEN_IDENTIFY,  MANUFACTURER_CODE_NONE, ZCL_IDENTIFY_ATTR_NUM,  identify_attrTbl,   zcl_identify_register,  app_identifyCb},
#ifdef ZCL_GROUP
    {ZCL_CLUSTER_GEN_GROUPS,    MANUFACTURER_CODE_NONE, ZCL_GROUP_1ATTR_NUM,    group_attr1Tbl,     zcl_group_register,     NULL},
#endif
#ifdef ZCL_SCENE
    {ZCL_CLUSTER_GEN_SCENES,    MANUFACTURER_CODE_NONE, ZCL_SCENE_1ATTR_NUM,    scene_attr1Tbl,     zcl_scene_register,     app_sceneCb},
#endif
#ifdef ZCL_LEVEL_CTRL
    {ZCL_CLUSTER_GEN_LEVEL_CONTROL, MANUFACTURER_CODE_NONE, ZCL_LEVEL_A_ATTR_NUM, levelA_attrTbl,      zcl_level_register,     app_displayLevelCb},
#endif
    {ZCL_CLUSTER_GEN_TIME,      MANUFACTURER_CODE_NONE, ZCL_TIME_ATTR_NUM,      time_attrTbl,       zcl_time_register,      app_timeCb},
#ifdef ZCL_THERMOSTAT
    {ZCL_CLUSTER_HAVC_THERMOSTAT, MANUFACTURER_CODE_NONE, ZCL_THERMOSTAT_ATTR_NUM, thermostat_attrTbl, zcl_thermostat_register, app_thermostatCb},
    {ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG, MANUFACTURER_CODE_NONE, ZCL_THERMOSTAT_UIC_ATTR_NUM, thermostat_ui_cfg_attrTbl, zcl_thermostat_ui_cfg_register, app_thermostat_uicCb},
#endif
#ifdef ZCL_FANCONTROL
    {ZCL_CLUSTER_HAVC_FAN_CONTROL, MANUFACTURER_CODE_NONE, ZCL_FANCONTROL_ATTR_NUM, fancontrol_attrTbl, zcl_fancontrol_register, app_fancontrolCb},
#endif
    {ZCL_CLUSTER_MS_RELATIVE_HUMIDITY,  MANUFACTURER_CODE_NONE, ZCL_HUMIDITY_ATTR_NUM,  humidity_attrTbl,   zcl_humidity_measurement_register,  app_humidityCb},
};

uint8_t APP_EP1_CB_CLUSTER_NUM = (sizeof(g_appEp1ClusterList)/sizeof(g_appEp1ClusterList[0]));

const zcl_specClusterInfo_t g_appEp2ClusterList[] = {
#ifdef ZCL_LEVEL_CTRL
    {ZCL_CLUSTER_GEN_LEVEL_CONTROL, MANUFACTURER_CODE_NONE, ZCL_LEVEL_B_ATTR_NUM, levelB_attrTbl,      zcl_level_register,     app_displayLevelCb},
#endif
};

uint8_t APP_EP2_CB_CLUSTER_NUM = (sizeof(g_appEp2ClusterList)/sizeof(g_appEp2ClusterList[0]));


static void print_setting_sr(nv_sts_t st, thermostat_settings_t *thermostat_settings, bool save) {

#if UART_PRINTF_MODE && DEBUG_SAVE

    printf("Settings %s. Return: %s\r\n", save?"saved":"restored", st==NV_SUCC?"Ok":"Error");

#if DEBUG_SCHEDULE

    uint8_t i;

    if (first_start) {

        for(i = 0; i < 6; i++) {
            printf("schedule_mon[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                    thermostat_settings->schedule_data.schedule_mon[i].transTime,
                    thermostat_settings->schedule_data.schedule_mon[i].heatSetpoint);
        }
        for(i = 0; i < 6; i++) {
            printf("schedule_tue[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                    thermostat_settings->schedule_data.schedule_tue[i].transTime,
                    thermostat_settings->schedule_data.schedule_tue[i].heatSetpoint);
        }
        for(i = 0; i < 6; i++) {
            printf("schedule_wed[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                    thermostat_settings->schedule_data.schedule_wed[i].transTime,
                    thermostat_settings->schedule_data.schedule_wed[i].heatSetpoint);
        }
        for(i = 0; i < 6; i++) {
            printf("schedule_thu[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                    thermostat_settings->schedule_data.schedule_thu[i].transTime,
                    thermostat_settings->schedule_data.schedule_thu[i].heatSetpoint);
        }
        for(i = 0; i < 6; i++) {
            printf("schedule_fri[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                    thermostat_settings->schedule_data.schedule_fri[i].transTime,
                    thermostat_settings->schedule_data.schedule_fri[i].heatSetpoint);
        }
        for(i = 0; i < 6; i++) {
            printf("schedule_sat[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                    thermostat_settings->schedule_data.schedule_sat[i].transTime,
                    thermostat_settings->schedule_data.schedule_sat[i].heatSetpoint);
        }
        for(i = 0; i < 6; i++) {
            printf("schedule_sun[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                    thermostat_settings->schedule_data.schedule_sun[i].transTime,
                    thermostat_settings->schedule_data.schedule_sun[i].heatSetpoint);
        }

    } else {

        switch(manuf_name) {
            case MANUF_NAME_1:
                for(i = 0; i < 4; i++) {
                    printf("schedule_mon[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_mon[i].transTime,
                            thermostat_settings->schedule_data.schedule_mon[i].heatSetpoint);
                }
                for(i = 0; i < 4; i++) {
                    printf("schedule_sat[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_sat[i].transTime,
                            thermostat_settings->schedule_data.schedule_sat[i].heatSetpoint);
                }
                for(i = 0; i < 4; i++) {
                    printf("schedule_sun[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_sun[i].transTime,
                            thermostat_settings->schedule_data.schedule_sun[i].heatSetpoint);
                }
                break;
            case MANUF_NAME_2:
            case MANUF_NAME_3:
            case MANUF_NAME_4:
            case MANUF_NAME_5:
            case MANUF_NAME_7:
            case MANUF_NAME_9:
            case MANUF_NAME_0C:
                for(i = 0; i < 4; i++) {
                    printf("schedule_mon[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_mon[i].transTime,
                            thermostat_settings->schedule_data.schedule_mon[i].heatSetpoint);
                }
                for(i = 0; i < 4; i++) {
                    printf("schedule_tue[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_tue[i].transTime,
                            thermostat_settings->schedule_data.schedule_tue[i].heatSetpoint);
                }
                for(i = 0; i < 4; i++) {
                    printf("schedule_wed[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_wed[i].transTime,
                            thermostat_settings->schedule_data.schedule_wed[i].heatSetpoint);
                }
                for(i = 0; i < 4; i++) {
                    printf("schedule_thu[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_thu[i].transTime,
                            thermostat_settings->schedule_data.schedule_thu[i].heatSetpoint);
                }
                for(i = 0; i < 4; i++) {
                    printf("schedule_fri[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_fri[i].transTime,
                            thermostat_settings->schedule_data.schedule_fri[i].heatSetpoint);
                }
                for(i = 0; i < 4; i++) {
                    printf("schedule_sat[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_sat[i].transTime,
                            thermostat_settings->schedule_data.schedule_sat[i].heatSetpoint);
                }
                for(i = 0; i < 4; i++) {
                    printf("schedule_sun[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_sun[i].transTime,
                            thermostat_settings->schedule_data.schedule_sun[i].heatSetpoint);
                }
                break;
            case MANUF_NAME_6:
                for(i = 0; i < 6; i++) {
                    printf("schedule_mon[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_mon[i].transTime,
                            thermostat_settings->schedule_data.schedule_mon[i].heatSetpoint);
                }
                for(i = 0; i < 2; i++) {
                    printf("schedule_sun[%d]. transTime: 0x%x, heatSetpoint: 0x%x\r\n", i,
                            thermostat_settings->schedule_data.schedule_sun[i].transTime,
                            thermostat_settings->schedule_data.schedule_sun[i].heatSetpoint);
                }
                break;
            default:
                break;
        }
    }

#endif

    printf("localTemperature:            %d\r\n", thermostat_settings->localTemperature);
    printf("systemMode                   %d\r\n", thermostat_settings->systemMode);
    printf("occupiedHeatingSetpoint:     %d\r\n", thermostat_settings->occupiedHeatingSetpoint);
    printf("localTemperatureCalibration: %d\r\n", thermostat_settings->localTemperatureCalibration);
    printf("sensor_used:                 %d\r\n", thermostat_settings->sensor_used);
    printf("dead_band:                   %d\r\n", thermostat_settings->dead_band);
    printf("manual_progMode:             %d\r\n", thermostat_settings->manual_progMode);
    printf("minHeatSetpointLimit:        %d\r\n", thermostat_settings->minHeatSetpointLimit);
    printf("maxHeatSetpointLimit:        %d\r\n", thermostat_settings->maxHeatSetpointLimit);
    printf("frostProtect:                %d\r\n", thermostat_settings->frostProtect);
    printf("heatProtect:                 %d\r\n", thermostat_settings->heatProtect);
    printf("keypadLockout:               %d\r\n", thermostat_settings->keypadLockout);
    printf("ecoMode:                     %s\r\n", thermostat_settings->ecoMode?"On":"Off");
    printf("ecoModeHeatTemperature:      %d\r\n", thermostat_settings->ecoModeHeatTemperature);
    printf("ecoModeCoolTemperature:      %d\r\n", thermostat_settings->ecoModeCoolTemperature);
    printf("currentLevelA:               %d\r\n", thermostat_settings->currentLevelA);
    printf("currentLevelB:               %d\r\n", thermostat_settings->currentLevelB);
    printf("frost_protect_onoff:         %d\r\n", thermostat_settings->frost_protect_onoff);
    printf("inversion:                   %d\r\n", thermostat_settings->inversion);
    printf("schedule_mode:               %d\r\n", thermostat_settings->schedule_mode);
    printf("sound:                       %d\r\n", thermostat_settings->sound);
    printf("level:                       %d\r\n", thermostat_settings->level);
    printf("dev_therm_mode:              %d\r\n", thermostat_settings->dev_therm_mode);
    printf("extTemperatureCalibration:   %d\r\n", thermostat_settings->extTemperatureCalibration);
    printf("humidity_offset:             %d\r\n", thermostat_settings->humidity_offset);
#endif
}


nv_sts_t thermostat_settings_save() {
    nv_sts_t st = NV_SUCC;

#ifdef ZCL_THERMOSTAT
#if NV_ENABLE

    thermostat_settings_t thermostat_settings;
    uint8_t     crc;
    bool        save = false;

    st = nv_flashReadNew(1, NV_MODULE_APP, NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);

    crc = thermostat_settings.crc;

    if(st == NV_SUCC && crc == checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1)) {

        if (memcmp(&thermostat_settings.schedule_data, &g_zcl_scheduleData, sizeof(zcl_scheduleData_t)) != 0) {
            memcpy(&thermostat_settings.schedule_data, &g_zcl_scheduleData, sizeof(zcl_scheduleData_t));
            save = true;
        }

        if (thermostat_settings.systemMode != g_zcl_thermostatAttrs.systemMode) {
            thermostat_settings.systemMode = g_zcl_thermostatAttrs.systemMode;
            save = true;
//            printf("systemMode changed\r\n");
        }

        if (thermostat_settings.minHeatSetpointLimit != g_zcl_thermostatAttrs.minHeatSetpointLimit) {
            thermostat_settings.minHeatSetpointLimit = g_zcl_thermostatAttrs.minHeatSetpointLimit;
            save = true;
//            printf("minHeatSetpointLimit changed\r\n");
        }

        if (thermostat_settings.maxHeatSetpointLimit != g_zcl_thermostatAttrs.maxHeatSetpointLimit) {
            thermostat_settings.maxHeatSetpointLimit = g_zcl_thermostatAttrs.maxHeatSetpointLimit;
            save = true;
//            printf("maxHeatSetpointLimit changed\r\n");
        }

        if (thermostat_settings.localTemperatureCalibration != g_zcl_thermostatAttrs.localTemperatureCalibration) {
            thermostat_settings.localTemperatureCalibration = g_zcl_thermostatAttrs.localTemperatureCalibration;
            save = true;
//            printf("localTemperatureCalibration changed\r\n");
        }

        if (thermostat_settings.occupiedHeatingSetpoint != g_zcl_thermostatAttrs.occupiedHeatingSetpoint) {
            thermostat_settings.occupiedHeatingSetpoint = g_zcl_thermostatAttrs.occupiedHeatingSetpoint;
            save = true;
//            printf("occupiedHeatingSetpoint changed\r\n");
        }

        if (thermostat_settings.manual_progMode != g_zcl_thermostatAttrs.manual_progMode) {
            thermostat_settings.manual_progMode = g_zcl_thermostatAttrs.manual_progMode;
            save = true;
//            printf("manual_progMode changed\r\n");
        }

        if (thermostat_settings.sensor_used != g_zcl_thermostatAttrs.sensor_used) {
            thermostat_settings.sensor_used = g_zcl_thermostatAttrs.sensor_used;
            save = true;
//            printf("sensor_used changed\r\n");
        }

        if (thermostat_settings.dead_band != g_zcl_thermostatAttrs.dead_band) {
            thermostat_settings.dead_band = g_zcl_thermostatAttrs.dead_band;
            save = true;
//            printf("dead_band changed\r\n");
        }

        if (thermostat_settings.frostProtect != g_zcl_thermostatAttrs.frostProtect) {
            thermostat_settings.frostProtect = g_zcl_thermostatAttrs.frostProtect;
            save = true;
//            printf("frostProtect changed\r\n");
        }

        if (thermostat_settings.heatProtect != g_zcl_thermostatAttrs.heatProtect) {
            thermostat_settings.heatProtect = g_zcl_thermostatAttrs.heatProtect;
            save = true;
//            printf("heatProtect changed\r\n");
        }

        if (thermostat_settings.keypadLockout != g_zcl_thermostatAttrs.keypadLockout) {
            thermostat_settings.keypadLockout = g_zcl_thermostatAttrs.keypadLockout;
            save = true;
//            printf("keypadLockout changed\r\n");
        }

        if (thermostat_settings.modeKeyLock != g_zcl_thermostatAttrs.modeKeyLock) {
            thermostat_settings.modeKeyLock = g_zcl_thermostatAttrs.modeKeyLock;
            save = true;
//            printf("modeKeyLock changed\r\n");
        }

        if (thermostat_settings.ecoMode != g_zcl_thermostatAttrs.ecoMode) {
            thermostat_settings.ecoMode = g_zcl_thermostatAttrs.ecoMode;
            save = true;
//            printf("ecoMode changed\r\n");
        }

        if (thermostat_settings.ecoModeHeatTemperature != g_zcl_thermostatAttrs.ecoModeHeatTemperature) {
            thermostat_settings.ecoModeHeatTemperature = g_zcl_thermostatAttrs.ecoModeHeatTemperature;
            save = true;
//            printf("ecoModeHeatTemperature changed\r\n");
        }

        if (thermostat_settings.ecoModeCoolTemperature != g_zcl_thermostatAttrs.ecoModeCoolTemperature) {
            thermostat_settings.ecoModeCoolTemperature = g_zcl_thermostatAttrs.ecoModeCoolTemperature;
            save = true;
//            printf("ecoModeCoolTemperature changed\r\n");
        }

        if (thermostat_settings.currentLevelA != g_zcl_levelAttrs.currentLevelA) {
            thermostat_settings.currentLevelA = g_zcl_levelAttrs.currentLevelA;
            save = true;
//            printf("currentLevelA changed\r\n");
        }

        if (thermostat_settings.currentLevelB != g_zcl_levelAttrs.currentLevelB) {
            thermostat_settings.currentLevelB = g_zcl_levelAttrs.currentLevelB;
            save = true;
//            printf("currentLevelB changed\r\n");
        }

        if (thermostat_settings.frost_protect_onoff != g_zcl_thermostatAttrs.frost_protect_onoff) {
            thermostat_settings.frost_protect_onoff = g_zcl_thermostatAttrs.frost_protect_onoff;
            save = true;
//            printf("frost_protect_onoff changed\r\n");
        }

        if (thermostat_settings.inversion != g_zcl_thermostatAttrs.inversion) {
            thermostat_settings.inversion = g_zcl_thermostatAttrs.inversion;
            save = true;
//            printf("inversion changed\r\n");
        }

        if (thermostat_settings.level != g_zcl_thermostatAttrs.level) {
            thermostat_settings.level = g_zcl_thermostatAttrs.level;
            save = true;
//            printf("level changed\r\n");
        }

        if (thermostat_settings.schedule_mode != g_zcl_thermostatAttrs.schedule_mode) {
            thermostat_settings.schedule_mode = g_zcl_thermostatAttrs.schedule_mode;
            save = true;
//            printf("schedule_mode changed\r\n");
        }

        if (thermostat_settings.sound != g_zcl_thermostatAttrs.sound) {
            thermostat_settings.sound = g_zcl_thermostatAttrs.sound;
            save = true;
//            printf("sound changed\r\n");
        }

        if (thermostat_settings.extTemperatureCalibration != g_zcl_thermostatAttrs.extTemperatureCalibration) {
            thermostat_settings.extTemperatureCalibration = g_zcl_thermostatAttrs.extTemperatureCalibration;
            save = true;
//            printf("extTemperatureCalibration changed: 0x%x\r\n", thermostat_settings.extTemperatureCalibration);
        }

        if (thermostat_settings.manuf_name != g_zcl_thermostatAttrs.manuf_name) {
            thermostat_settings.manuf_name = g_zcl_thermostatAttrs.manuf_name;
            save = true;
//            printf("manuf_name changed: 0x%02x\r\n", thermostat_settings.manuf_name);
        }

        if (thermostat_settings.dev_therm_mode != dev_therm_mode) {
            thermostat_settings.dev_therm_mode = dev_therm_mode;
            save = true;
//            printf("dev_therm_mode changed: 0x%x\r\n", dev_therm_mode);
        }

        if (thermostat_settings.fanMode != g_zcl_fancontrolAttrs.fanMode) {
            thermostat_settings.fanMode = g_zcl_fancontrolAttrs.fanMode;
            save = true;
//            printf("fanMode changed: 0x%x\r\n", thermostat_settings.fanMode);
        }

        if (thermostat_settings.fanControl != g_zcl_fancontrolAttrs.fanControl) {
            thermostat_settings.fanControl = g_zcl_fancontrolAttrs.fanControl;
            save = true;
//            printf("fanControl changed: 0x%x\r\n", thermostat_settings.fanControl);
        }

        if (thermostat_settings.humidity_offset != g_zcl_humidityAttrs.humidity_offset) {
            thermostat_settings.humidity_offset = g_zcl_humidityAttrs.humidity_offset;
            save = true;
//            printf("humidity_offset changed: 0x%x\r\n", thermostat_settings.humidity_offset);
        }

        if (save) {

#if UART_PRINTF_MODE
            printf("Saved settings\r\n");
#endif

            thermostat_settings.localTemperature = g_zcl_thermostatAttrs.localTemperature;

            thermostat_settings.crc = checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1);
            st = nv_flashWriteNew(1, NV_MODULE_APP,  NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);

            print_setting_sr(st, &thermostat_settings, true);

        }
    } else if (st == NV_ITEM_NOT_FOUND ||
            (st == NV_SUCC && crc != checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1))) {

        memcpy(&thermostat_settings.schedule_data, &g_zcl_scheduleData, sizeof(zcl_scheduleData_t));
        thermostat_settings.localTemperature = g_zcl_thermostatAttrs.localTemperature;
        thermostat_settings.systemMode = g_zcl_thermostatAttrs.systemMode;
        thermostat_settings.minHeatSetpointLimit = g_zcl_thermostatAttrs.minHeatSetpointLimit;
        thermostat_settings.maxHeatSetpointLimit = g_zcl_thermostatAttrs.maxHeatSetpointLimit;
        thermostat_settings.localTemperatureCalibration = g_zcl_thermostatAttrs.localTemperatureCalibration;
        thermostat_settings.occupiedHeatingSetpoint = g_zcl_thermostatAttrs.occupiedHeatingSetpoint;
        thermostat_settings.manual_progMode = g_zcl_thermostatAttrs.manual_progMode;
        thermostat_settings.sensor_used = g_zcl_thermostatAttrs.sensor_used;
        thermostat_settings.dead_band = g_zcl_thermostatAttrs.dead_band;
        thermostat_settings.frostProtect = g_zcl_thermostatAttrs.frostProtect;
        thermostat_settings.heatProtect = g_zcl_thermostatAttrs.heatProtect;
        thermostat_settings.keypadLockout = g_zcl_thermostatAttrs.keypadLockout;
        thermostat_settings.modeKeyLock = g_zcl_thermostatAttrs.modeKeyLock;
        thermostat_settings.ecoMode = g_zcl_thermostatAttrs.ecoMode;
        thermostat_settings.ecoModeHeatTemperature = g_zcl_thermostatAttrs.ecoModeHeatTemperature;
        thermostat_settings.ecoModeCoolTemperature = g_zcl_thermostatAttrs.ecoModeCoolTemperature;
        thermostat_settings.currentLevelA = g_zcl_levelAttrs.currentLevelA;
        thermostat_settings.currentLevelB = g_zcl_levelAttrs.currentLevelB;
        thermostat_settings.frost_protect_onoff = g_zcl_thermostatAttrs.frost_protect_onoff;
        thermostat_settings.inversion = g_zcl_thermostatAttrs.inversion;
        thermostat_settings.level = g_zcl_thermostatAttrs.level;
        thermostat_settings.schedule_mode = g_zcl_thermostatAttrs.schedule_mode;
        thermostat_settings.sound = g_zcl_thermostatAttrs.sound;
        thermostat_settings.extTemperatureCalibration = g_zcl_thermostatAttrs.extTemperatureCalibration;
        thermostat_settings.manuf_name = g_zcl_thermostatAttrs.manuf_name;
        thermostat_settings.dev_therm_mode = dev_therm_mode;
        thermostat_settings.fanMode = g_zcl_fancontrolAttrs.fanMode;
        thermostat_settings.fanControl = g_zcl_fancontrolAttrs.fanControl;
        thermostat_settings.humidity_offset = g_zcl_humidityAttrs.humidity_offset;
        thermostat_settings.crc = checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1);

        st = nv_flashWriteNew(1, NV_MODULE_APP,  NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);

        print_setting_sr(st, &thermostat_settings, true);

    }
#else
    st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

    return st;
}

nv_sts_t thermostat_settings_restore() {
    nv_sts_t st = NV_SUCC;

    #ifdef ZCL_THERMOSTAT
#if NV_ENABLE

    thermostat_settings_t thermostat_settings;

    st = nv_flashReadNew(1, NV_MODULE_APP,  NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);

    if (st == NV_SUCC && thermostat_settings.crc == checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1)) {

#if UART_PRINTF_MODE
        printf("Restored settings\r\n");
#endif

        memcpy(&g_zcl_scheduleData, &thermostat_settings.schedule_data, sizeof(zcl_scheduleData_t));

        g_zcl_thermostatAttrs.localTemperature = thermostat_settings.localTemperature;
        g_zcl_thermostatAttrs.systemMode = thermostat_settings.systemMode;
        g_zcl_thermostatAttrs.minHeatSetpointLimit = thermostat_settings.minHeatSetpointLimit;
        g_zcl_thermostatAttrs.maxHeatSetpointLimit = thermostat_settings.maxHeatSetpointLimit;
        g_zcl_thermostatAttrs.localTemperatureCalibration = thermostat_settings.localTemperatureCalibration;
        g_zcl_thermostatAttrs.occupiedHeatingSetpoint = thermostat_settings.occupiedHeatingSetpoint;
        g_zcl_thermostatAttrs.manual_progMode = thermostat_settings.manual_progMode;
        g_zcl_thermostatAttrs.sensor_used = thermostat_settings.sensor_used;
        g_zcl_thermostatAttrs.frostProtect = thermostat_settings.frostProtect;
        g_zcl_thermostatAttrs.heatProtect = thermostat_settings.heatProtect;
        g_zcl_thermostatAttrs.dead_band = thermostat_settings.dead_band;
        g_zcl_thermostatAttrs.ecoMode = thermostat_settings.ecoMode;
        g_zcl_thermostatAttrs.ecoModeHeatTemperature = thermostat_settings.ecoModeHeatTemperature;
        g_zcl_thermostatAttrs.ecoModeCoolTemperature = thermostat_settings.ecoModeCoolTemperature;
        g_zcl_thermostatAttrs.keypadLockout = thermostat_settings.keypadLockout;
        g_zcl_thermostatAttrs.modeKeyLock = thermostat_settings.modeKeyLock;
        g_zcl_thermostatAttrs.frost_protect_onoff = thermostat_settings.frostProtect;
        g_zcl_thermostatAttrs.inversion = thermostat_settings.inversion;
        g_zcl_thermostatAttrs.level = thermostat_settings.level;
        g_zcl_thermostatAttrs.schedule_mode = thermostat_settings.schedule_mode;
        g_zcl_thermostatAttrs.sound = thermostat_settings.sound;
        g_zcl_thermostatAttrs.extTemperatureCalibration = thermostat_settings.extTemperatureCalibration;
        g_zcl_thermostatAttrs.manuf_name = thermostat_settings.manuf_name;
        dev_therm_mode = thermostat_settings.dev_therm_mode;
        g_zcl_fancontrolAttrs.fanControl = thermostat_settings.fanControl;
        g_zcl_fancontrolAttrs.fanMode = thermostat_settings.fanMode;

        g_zcl_levelAttrs.currentLevelA = thermostat_settings.currentLevelA;
        g_zcl_levelAttrs.currentLevelB = thermostat_settings.currentLevelB;

        g_zcl_humidityAttrs.humidity_offset = thermostat_settings.humidity_offset;

#if UART_PRINTF_MODE && DEBUG_SAVE
        print_setting_sr(st, &thermostat_settings, false);
#endif
    }

#else
    st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

    return st;
}

