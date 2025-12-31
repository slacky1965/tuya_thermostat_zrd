#ifndef SRC_INCLUDE_APP_TUYA_DATAPOINT_H_
#define SRC_INCLUDE_APP_TUYA_DATAPOINT_H_

/* data point for manufacturer id -
 * "u9bfwha0"
 * "aoclfnxz"
 *
 * type1 (model1)
*/
typedef enum {
    DP_TYPE1_ID_00    = 0x00,     // 0 - not support
    DP_TYPE1_ID_01    = 0x01,     // on off
    DP_TYPE1_ID_02    = 0x02,     // manual / programming
    DP_TYPE1_ID_03    = 0x03,     // unknown
    DP_TYPE1_ID_10    = 0x10,     // heat setpoint
    DP_TYPE1_ID_13    = 0x13,     // max (protection max temperature (+45°C ... +70°C))
    DP_TYPE1_ID_18    = 0x18,     // local temperature
    DP_TYPE1_ID_1A    = 0x1A,     // hysteresis (1°C ... 5°C)
    DP_TYPE1_ID_1B    = 0x1B,     // calibration
    DP_TYPE1_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE1_ID_28    = 0x28,     // lock / unlock keys
    DP_TYPE1_ID_2B    = 0x2B,     // Sensor IN - 0 / AL - 1 / OU - 2
    DP_TYPE1_ID_65    = 0x65,     // schedule
} data_point_id_type1_t;


/* data point for manufacturer id -
 * "edl8pz1k"
 *
 * type2 (model2)
 */
typedef enum {
    DP_TYPE2_ID_00    = 0x00,     // 0 - not support
    DP_TYPE2_ID_01    = 0x01,     // on off
    DP_TYPE2_ID_02    = 0x02,     // manual / programming
    DP_TYPE2_ID_10    = 0x10,     // heat setpoint
    DP_TYPE2_ID_13    = 0x13,     // max heat (+35°C ... +45°C step 1°C)
    DP_TYPE2_ID_18    = 0x18,     // local temperature
    DP_TYPE2_ID_1A    = 0x1A,     // min heat (+5°C ... +15°C step 1°C)
    DP_TYPE2_ID_1B    = 0x1B,     // calibration
    DP_TYPE2_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE2_ID_28    = 0x28,     // lock / unlock keys
    DP_TYPE2_ID_2B    = 0x2B,     // Sensor IN/AL/OU
    DP_TYPE2_ID_67    = 0x67,     // hysteresis (0°C ... 5°C step 1°C)
    DP_TYPE2_ID_68    = 0x68,     // protection max temperature (+25°C ... +70°C step 1°C)
    DP_TYPE2_ID_6F    = 0x6F,     // protection min temperature (0°C ... +10°C step 1°C)
    DP_TYPE2_ID_65    = 0x65,     // schedule sun
    DP_TYPE2_ID_66    = 0x66,     // temperature of outer sensor (if AL or OU)
    DP_TYPE2_ID_69    = 0x69,     // schedule sat
    DP_TYPE2_ID_6A    = 0x6A,     // schedule fri
    DP_TYPE2_ID_6B    = 0x6B,     // schedule thu
    DP_TYPE2_ID_6C    = 0x6C,     // schedule wed
    DP_TYPE2_ID_6D    = 0x6D,     // schedule tue
    DP_TYPE2_ID_6E    = 0x6E,     // schedule mon
} data_point_id_type2_t;


/* data point for manufacturer id -
 * "tagezcph"
 *
 * type3 (model3)
*/
typedef enum {
    DP_TYPE3_ID_00    = 0x00,     // 0 - not support
    DP_TYPE3_ID_01    = 0x01,     // on off
    DP_TYPE3_ID_02    = 0x02,     // manual / programming
    DP_TYPE3_ID_10    = 0x10,     // heat setpoint
    DP_TYPE3_ID_13    = 0x13,     // max heat
    DP_TYPE3_ID_18    = 0x18,     // local temperature
    DP_TYPE3_ID_1A    = 0x1A,     // min heat
    DP_TYPE3_ID_1B    = 0x1B,     // calibration
    DP_TYPE3_ID_1C    = 0x1C,     // default setting
    DP_TYPE3_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE3_ID_27    = 0x27,     // lock / unlock keys
    DP_TYPE3_ID_28    = 0x28,     // eco mode
    DP_TYPE3_ID_2B    = 0x2B,     // Sensor IN/AL/OU
    DP_TYPE3_ID_67    = 0x67,     // hysteresis
    DP_TYPE3_ID_68    = 0x68,     // protection max temperature
    DP_TYPE3_ID_6F    = 0x6F,     // protection min temperature
    DP_TYPE3_ID_65    = 0x65,     // schedule sun
    DP_TYPE3_ID_66    = 0x66,     // temperature of outer sensor (if AL or OU)
    DP_TYPE3_ID_69    = 0x69,     // schedule sat
    DP_TYPE3_ID_6A    = 0x6A,     // schedule fri
    DP_TYPE3_ID_6B    = 0x6B,     // schedule thu
    DP_TYPE3_ID_6C    = 0x6C,     // schedule wed
    DP_TYPE3_ID_6D    = 0x6D,     // schedule tue
    DP_TYPE3_ID_6E    = 0x6E,     // schedule mon
    DP_TYPE3_ID_70    = 0x70,     // eco mode's temperature
    DP_TYPE3_ID_71    = 0x71,     // level brightness 06:00-22:00
    DP_TYPE3_ID_72    = 0x72,     // level brightness 22:00-06:00
} data_point_id_type3_t;

/* data point for manufacturer id -
 * "xyugziqv"
 *
 * type4 (model4)
*/
typedef enum {
    DP_TYPE4_ID_00    = 0x00,     // 0 - not support
    DP_TYPE4_ID_01    = 0x01,     // on off
    DP_TYPE4_ID_02    = 0x02,     // manual / programming
    DP_TYPE4_ID_04    = 0x04,     // eco mode
    DP_TYPE4_ID_10    = 0x10,     // heat setpoint
    DP_TYPE4_ID_13    = 0x13,     // max heat
    DP_TYPE4_ID_18    = 0x18,     // local temperature
    DP_TYPE4_ID_1A    = 0x1A,     // min heat
    DP_TYPE4_ID_1B    = 0x1B,     // calibration
    DP_TYPE4_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE4_ID_28    = 0x28,     // lock / unlock keys
    DP_TYPE4_ID_66    = 0x66,     // Sensor IN/AL/OU
    DP_TYPE4_ID_67    = 0x67,     // hysteresis
    DP_TYPE4_ID_69    = 0x69,     // eco mode's temperature
    DP_TYPE4_ID_6A    = 0x6A,     // schedule sun
    DP_TYPE4_ID_6B    = 0x6B,     // schedule sat
    DP_TYPE4_ID_6C    = 0x6C,     // schedule fri
    DP_TYPE4_ID_6D    = 0x6D,     // schedule thu
    DP_TYPE4_ID_6E    = 0x6E,     // schedule wed
    DP_TYPE4_ID_6F    = 0x6F,     // schedule tue
    DP_TYPE4_ID_70    = 0x70,     // schedule mon
    DP_TYPE4_ID_71    = 0x71,     // temperature of outer sensor (if AL or OU)
    DP_TYPE4_ID_73    = 0x73,     // level brightness of screen
    DP_TYPE4_ID_74    = 0x74,     // protection max temperature
    DP_TYPE4_ID_75    = 0x75,     // protection min temperature
} data_point_id_type4_t;

/* data point for manufacturer id -
 * "5toc8efa"
 *
 * type5 (model5)
 */
#define DP_TYPE5_ID_00 DP_TYPE2_ID_00
#define DP_TYPE5_ID_01 DP_TYPE2_ID_01
#define DP_TYPE5_ID_02 DP_TYPE2_ID_02
#define DP_TYPE5_ID_10 DP_TYPE2_ID_10
#define DP_TYPE5_ID_13 DP_TYPE2_ID_13
#define DP_TYPE5_ID_18 DP_TYPE2_ID_18
#define DP_TYPE5_ID_1A DP_TYPE2_ID_1A
#define DP_TYPE5_ID_1B DP_TYPE2_ID_1B
#define DP_TYPE5_ID_24 DP_TYPE2_ID_24
#define DP_TYPE5_ID_28 DP_TYPE2_ID_28
#define DP_TYPE5_ID_2B DP_TYPE2_ID_2B
#define DP_TYPE5_ID_67 DP_TYPE2_ID_67
#define DP_TYPE5_ID_68 DP_TYPE2_ID_68
#define DP_TYPE5_ID_65 DP_TYPE2_ID_65
#define DP_TYPE5_ID_66 DP_TYPE2_ID_66
#define DP_TYPE5_ID_69 DP_TYPE2_ID_69
#define DP_TYPE5_ID_6A DP_TYPE2_ID_6A
#define DP_TYPE5_ID_6B DP_TYPE2_ID_6B
#define DP_TYPE5_ID_6C DP_TYPE2_ID_6C
#define DP_TYPE5_ID_6D DP_TYPE2_ID_6D
#define DP_TYPE5_ID_6E DP_TYPE2_ID_6E

typedef data_point_id_type2_t data_point_id_type5_t;

/* data point for manufacturer id -
 * "lzriup1j"
 * "oh8y8pv8",
 * "gops3slb",
 * "cvub6xbb",
 *
 * type6 (model6)
*/
typedef enum {
    DP_TYPE6_ID_00    = 0x00,     // 0 - not support
    DP_TYPE6_ID_01    = 0x01,     // on off
    DP_TYPE6_ID_02    = 0x02,     // heat setpoint
    DP_TYPE6_ID_03    = 0x03,     // local temperature
    DP_TYPE6_ID_04    = 0x04,     // manual / programming / temporary
    DP_TYPE6_ID_09    = 0x09,     // lock / unlock keys
    DP_TYPE6_ID_0F    = 0x0F,     // max heat
    DP_TYPE6_ID_13    = 0x13,     // calibration
    DP_TYPE6_ID_65    = 0x65,     // 0x00 - heat, 0x01 - idle
    DP_TYPE6_ID_66    = 0x66,     // frost protection (on-off)
    DP_TYPE6_ID_67    = 0x67,     // factory reset thermostat (not zigbee)
    DP_TYPE6_ID_68    = 0x68,     // schedule off, 5+2, 6+1, 7
    DP_TYPE6_ID_69    = 0x69,     // sound on-off
    DP_TYPE6_ID_6A    = 0x6A,     // Sensor IN/AL/OU
    DP_TYPE6_ID_6B    = 0x6B,     // hysteresis
    DP_TYPE6_ID_6C    = 0x6C,     // protection max temperature
    DP_TYPE6_ID_6D    = 0x6D,     // schedule
    DP_TYPE6_ID_6E    = 0x6E,     // level brightness of screen (off, low, medium, high)
    DP_TYPE6_ID_6F    = 0x6F,     // inversion of output
} data_point_id_type6_t;

/* data point for manufacturer id -
 * "mpbki2zm"
 *
 * type7 (model7)
*/
typedef enum {
    DP_TYPE7_ID_00    = 0x00,     // 0 - not support
    DP_TYPE7_ID_01    = 0x01,     // on off
    DP_TYPE7_ID_02    = 0x02,     // thermostat local mode (cold, heat, fan)
    DP_TYPE7_ID_04    = 0x04,     // eco mode
    DP_TYPE7_ID_10    = 0x10,     // heat setpoint
    DP_TYPE7_ID_13    = 0x13,     // max heat (+15°C ... +35°C stepe 1°C)
    DP_TYPE7_ID_18    = 0x18,     // local temperature
    DP_TYPE7_ID_1A    = 0x1A,     // min heat (+5°C ... +15°C step 1°C)
    DP_TYPE7_ID_1B    = 0x1B,     // calibration
    DP_TYPE7_ID_1C    = 0x1C,     // fan mode 0x00 - low, 0x01 - mid, 0x02 - high, 0x03 - auto
    DP_TYPE7_ID_24    = 0x24,     // 0x00 - valve open, 0x01 - valve close
    DP_TYPE7_ID_28    = 0x28,     // lock / unlock keys
    DP_TYPE7_ID_65    = 0x65,     // manual / programming
    DP_TYPE7_ID_66    = 0x66,     // fan control 0x00 - off, 0x01 - on
    DP_TYPE7_ID_67    = 0x67,     // hysteresis
    DP_TYPE7_ID_68    = 0x68,     // eco mode's cool temperature (+10°C ... +30°C step 1°C)
    DP_TYPE7_ID_69    = 0x69,     // eco mode's heat temperature (+10°C ... +30°C step 1°C)
    DP_TYPE7_ID_6A    = 0x6A,     // schedule sun
    DP_TYPE7_ID_6B    = 0x6B,     // schedule sat
    DP_TYPE7_ID_6C    = 0x6C,     // schedule fri
    DP_TYPE7_ID_6D    = 0x6D,     // schedule thu
    DP_TYPE7_ID_6E    = 0x6E,     // schedule wed
    DP_TYPE7_ID_6F    = 0x6F,     // schedule tue
    DP_TYPE7_ID_70    = 0x70,     // schedule mon
} data_point_id_type7_t;

/* data point for manufacturer id -
 * "7rghpoxo"
 *
 * type8 (model8)
*/
typedef enum {
    DP_TYPE8_ID_00    = 0x00,     // 0 - not support
    DP_TYPE8_ID_01    = 0x01,     // on off
    DP_TYPE8_ID_02    = 0x02,     // heat setpoint
    DP_TYPE8_ID_03    = 0x03,     // local temperature
    DP_TYPE8_ID_09    = 0x09,     // lock / unlock keys
    DP_TYPE8_ID_0B    = 0x0B,     // ???
    DP_TYPE8_ID_0F    = 0x0F,     // max heat
    DP_TYPE8_ID_10    = 0x10,     // min heat
    DP_TYPE8_ID_13    = 0x13,     // calibration
    DP_TYPE8_ID_65    = 0x65,     // calibration of external senor
    DP_TYPE8_ID_66    = 0x66,     // 0x00 - heat, 0x01 - idle
    DP_TYPE8_ID_67    = 0x67,     // sleep mode
    DP_TYPE8_ID_68    = 0x68,     // manual 0 / programming 1
    DP_TYPE8_ID_69    = 0x69,     // schedule workweek, sat, sun
    DP_TYPE8_ID_6A    = 0x6A,     // set hour of schedule
    DP_TYPE8_ID_6B    = 0x6B,     // set minutes of schedule
    DP_TYPE8_ID_6C    = 0x6C,     // set temperature of schedule
    DP_TYPE8_ID_6D    = 0x6D,     // time period of schedule (in quantity 6)
} data_point_id_type8_t;

/* data point for manufacturer id -
 * "6a4vxfnv"
 *
 * type9 (model9)
 */
typedef enum {
    DP_TYPE9_ID_00    = 0x00,     // 0 - not support
    DP_TYPE9_ID_01    = 0x01,     // on off
    DP_TYPE9_ID_02    = 0x02,     // manual - 0x00 / programming - 0x01 / temporary - 0x02
    DP_TYPE9_ID_10    = 0x10,     // heat setpoint (step 0.5 *10)
    DP_TYPE9_ID_13    = 0x13,     // max heat (+30°C ... +90°C, step 1°C *10)
    DP_TYPE9_ID_18    = 0x18,     // local temperature
    DP_TYPE9_ID_1A    = 0x1A,     // min heat (+5°C ... +15°C, step 1°C *10)
    DP_TYPE9_ID_1B    = 0x1B,     // calibration
    DP_TYPE9_ID_1C    = 0x1C,     // default setting
    DP_TYPE9_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE9_ID_27    = 0x27,     // lock / unlock keys
    DP_TYPE9_ID_28    = 0x28,     // eco mode
    DP_TYPE9_ID_2B    = 0x2B,     // Sensor IN - 0x00 / AL - 0x01 / OUT - 0x02
    DP_TYPE9_ID_67    = 0x67,     // hysteresis
    DP_TYPE9_ID_68    = 0x68,     // protection max temperature (+25°C ... +90°C step 1°C *10)
    DP_TYPE9_ID_6F    = 0x6F,     // protection min temperature (0°C ... +10°C step 1°C *10)
    DP_TYPE9_ID_65    = 0x65,     // schedule sun
    DP_TYPE9_ID_66    = 0x66,     // temperature of outer sensor (if AL or OU)
    DP_TYPE9_ID_69    = 0x69,     // schedule sat
    DP_TYPE9_ID_6A    = 0x6A,     // schedule fri
    DP_TYPE9_ID_6B    = 0x6B,     // schedule thu
    DP_TYPE9_ID_6C    = 0x6C,     // schedule wed
    DP_TYPE9_ID_6D    = 0x6D,     // schedule tue
    DP_TYPE9_ID_6E    = 0x6E,     // schedule mon
    DP_TYPE9_ID_70    = 0x70,     // eco mode's temperature (0°C ... +30°C step 1°C *10)
    DP_TYPE9_ID_71    = 0x71,     // level brightness 06:00-22:00 (0 ... 8 step 1)
    DP_TYPE9_ID_72    = 0x72,     // level brightness 22:00-06:00
    DP_TYPE9_ID_73    = 0x73,     // external sensor calibration (-9°C ... +9°C step 1°C)
    DP_TYPE9_ID_74    = 0x74,     // type relay NC - 0x00, NO - 0x01 (inversion)
    DP_TYPE9_ID_75    = 0x75,     // mode lock / unlock keys (all - 0x01, partial - 0x00)
} data_point_id_type9_t;

/* data point for manufacturer id -
 * "_TZE284_xalsoe3m"
 *
 * typeA (modelA)
*/
typedef enum {
    DP_TYPE0A_ID_00     = 0x00,     // not support
    DP_TYPE0A_ID_01     = 0x01,     // on off
    DP_TYPE0A_ID_02     = 0x02,     // manual - 1 / programming - 0
    DP_TYPE0A_ID_10     = 0x10,     // local temperature
    DP_TYPE0A_ID_12     = 0x12,     // min heat (0°C ... +20°C, step 1°C)
    DP_TYPE0A_ID_13     = 0x13,     // calibration (-9°C ... +9°C step 1°C)
    DP_TYPE0A_ID_17     = 0x17,     // ???? not used. temperature of outer sensor (if AL or OU)
    DP_TYPE0A_ID_20     = 0x20,     // Sensor IN - 0/OUT - 1/ALL - 2
    DP_TYPE0A_ID_22     = 0x22,     // max heat (+20°C ... 50°C, step 1°С)
    DP_TYPE0A_ID_27     = 0x27,     // lock - 1 / unlock keys - 0
    DP_TYPE0A_ID_28     = 0x28,     // eco mode
    DP_TYPE0A_ID_2F     = 0x2F,     // 0x00 - heat, 0x01 - idle
    DP_TYPE0A_ID_32     = 0x32,     // heat setpoint
    DP_TYPE0A_ID_44     = 0x44,     // schedule
    DP_TYPE0A_ID_65     = 0x65,     // protection max temperature (+25°C ... +70°C step 1°C)
    DP_TYPE0A_ID_66     = 0x66,     // hysteresis (1°C ... 5°C step 1°C)
} data_point_id_type0A_t;

/* data point for manufacturer id -
 * "_TZE204_8byfmxdv"
 *
 * type6 (model0B)
*/
typedef enum {
    DP_TYPE0B_ID_00    = 0x00,     // 0 - not support
    DP_TYPE0B_ID_01    = 0x01,     // on off
    DP_TYPE0B_ID_02    = 0x02,     // programming - 0 / manual - 1
    DP_TYPE0B_ID_10    = 0x10,     // heat setpoint *10
    DP_TYPE0B_ID_13    = 0x13,     // max heat +35°C ... +50°C step 0.5, *10
    DP_TYPE0B_ID_18    = 0x18,     // local temperature (0x011D - 285 / 10 = 28.5°C)
    DP_TYPE0B_ID_1A    = 0x1A,     // min heat 1°C ... +5°C, step 0.5 * 10
    DP_TYPE0B_ID_1B    = 0x1B,     // calibration -9°C ... +9°C step 1
    DP_TYPE0B_ID_2B    = 0x2B,     // Sensor IN - 0 / OUT - 1
    DP_TYPE0B_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE0B_ID_28    = 0x28,     // keys lock - 1 / unlock  - 0
    DP_TYPE0A_ID_30    = 0x30,     // schedule len 48
    DP_TYPE0B_ID_34    = 0x34,     // level brightness of screen (off, 50%, 100%)
    DP_TYPE0B_ID_65    = 0x65,     // hysteresis 0.5° ... 5°C step 0.5 *10
} data_point_id_type0B_t;

/* data point for manufacturer id -
 * "szbxmorb"
 *
 * type0C (model0C)
*/
typedef enum {
    DP_TYPE0C_ID_00    = 0x00,     // 0 - not support
    DP_TYPE0C_ID_01    = 0x01,     // on off
    DP_TYPE0C_ID_02    = 0x02,     // manual / programming
    DP_TYPE0C_ID_04    = 0x04,     // eco mode
    DP_TYPE0C_ID_10    = 0x10,     // heat setpoint
    DP_TYPE0C_ID_13    = 0x13,     // max heat 20°C ... 45°C step 1
    DP_TYPE0C_ID_18    = 0x18,     // local temperature
    DP_TYPE0C_ID_1A    = 0x1A,     // min heat 5°C ... 20°C step 1
    DP_TYPE0C_ID_1B    = 0x1B,     // calibration -12°C ... +12°C step 1
    DP_TYPE0C_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE0C_ID_28    = 0x28,     // lock / unlock keys
    DP_TYPE0C_ID_65    = 0x65,     // humidity offset -95 ... 95 step 5
    DP_TYPE0C_ID_66    = 0x66,     // Sensor IN - 0/AL - 1/OU - 2
    DP_TYPE0C_ID_67    = 0x67,     // hysteresis 1°C ... 5°C step 1
    DP_TYPE0C_ID_68    = 0x68,     // humidity
    DP_TYPE0C_ID_69    = 0x69,     // eco mode's set temperature 0 ... 30°C step 1
    DP_TYPE0C_ID_6A    = 0x6A,     // schedule sun
    DP_TYPE0C_ID_6B    = 0x6B,     // schedule sat
    DP_TYPE0C_ID_6C    = 0x6C,     // schedule fri
    DP_TYPE0C_ID_6D    = 0x6D,     // schedule thu
    DP_TYPE0C_ID_6E    = 0x6E,     // schedule wed
    DP_TYPE0C_ID_6F    = 0x6F,     // schedule tue
    DP_TYPE0C_ID_70    = 0x70,     // schedule mon
    DP_TYPE0C_ID_71    = 0x71,     // temperature of outer sensor (if AL or OU)
    DP_TYPE0C_ID_73    = 0x73,     // level brightness of screen 0 ... 9 step 1
    DP_TYPE0C_ID_74    = 0x74,     // protection max temperature +20°C ... +70°C step 1
    DP_TYPE0C_ID_75    = 0x75,     // protection min temperature 0°C ... +10°C step 1
} data_point_id_type0C_t;

typedef enum {
    SCHEDULE8_MON = 0,
    SCHEDULE8_SAT,
    SCHEDULE8_SUN,
} schedule8_day_t;

typedef enum {
    MANUF_NAME_1 = 0,
    MANUF_NAME_2,
    MANUF_NAME_3,
    MANUF_NAME_4,
    MANUF_NAME_5,
    MANUF_NAME_6,
    MANUF_NAME_7,
    MANUF_NAME_8,
    MANUF_NAME_9,
    MANUF_NAME_0A,
    MANUF_NAME_0B,
    MANUF_NAME_0C,
    MANUF_NAME_MAX
} manuf_name_t;

typedef enum {
    DP_IDX_ONOFF    = 0,        // 00
    DP_IDX_TEMP,                // 01
    DP_IDX_SETPOINT,            // 02
    DP_IDX_MIN,                 // 03
    DP_IDX_MAX,                 // 04
    DP_IDX_DEADZONE,            // 05
    DP_IDX_CALIBRATION,         // 06
    DP_IDX_RUNSTATE,            // 07
    DP_IDX_SENSOR,              // 08
    DP_IDX_PROG,                // 09
    DP_IDX_LOCKUNLOCK,          // 10
    DP_IDX_SCHEDULE,            // 11
    DP_IDX_UNKNOWN,             // 12
    DP_IDX_TEMP_OUT,            // 13
    DP_IDX_FROST_PROTECT,       // 14
    DP_IDX_HEAT_PROTECT,        // 15
    DP_IDX_SCHEDULE_MON,        // 16
    DP_IDX_SCHEDULE_TUE,        // 17
    DP_IDX_SCHEDULE_WED,        // 18
    DP_IDX_SCHEDULE_THU,        // 19
    DP_IDX_SCHEDULE_FRI,        // 20
    DP_IDX_SCHEDULE_SAT,        // 21
    DP_IDX_SCHEDULE_SUN,        // 22
    DP_IDX_LEVEL_A,             // 23
    DP_IDX_LEVEL_B,             // 24
    DP_IDX_ECO_MODE,            // 25
    DP_IDX_ECO_HEAT_TEMP,       // 26
    DP_IDX_ECO_COOL_TEMP,       // 27
    DP_IDX_SOUND,               // 28
    DP_IDX_SETTINGS_RESET,      // 29
    DP_IDX_INVERSION,           // 30
    DP_IDX_THERM_MODE,          // 31
    DP_IDX_FAN_MODE,            // 32
    DP_IDX_FAN_CONTROL,         // 33
    DP_IDX_EXT_CALIBRATION,     // 34
    DP_IDX_MODE_LOCK,           // 35
    DP_IDX_HUMIDITY,            // 36
    DP_IDX_HUMIDITY_OFFSET,     // 37
    DP_IDX_MAXNUM               // 38
} data_point_idx_t;

/* Data Point
 *  Type    Data type   Data length     Description
    0x00    Raw         Custom          Raw data type in hex format, with customizable bytes.
    0x01    Boolean     1               Boolean data type. Valid values include 0x00 and 0x01.
    0x02    Value       4               Value data type, for example, 1, 23, and 104.
    0x03    String      Custom          Custom string.
    0x04    Enum        1               Enum data type, ranging from 0 to 255.
    0x05    Bitmap      1/2/4           Bitmap data type, used to report error codes.
 */

typedef enum {
    DP_RAW = 0,
    DP_BOOL,
    DP_VAL,
    DP_STR,
    DP_ENUM,
    DP_BITMAP
} dp_type_t;

typedef struct __attribute__((packed)) {
    uint8_t  dp_id;
    uint8_t  dp_type;
    uint16_t dp_len;
    uint8_t  data[DATA_MAX_LEN-8];
} data_point_t;

typedef void (*remote_cmd_t)(void *args);
typedef void (*local_cmd_t)(void *args);

typedef struct {
    uint8_t         id;             // datapoint id
    uint8_t         type;           // dp_type_t
    uint16_t        len;            // length of datapoint
    int16_t         divisor;        // divisor: -100 => /100; -10 => /10; 1 = > *1; 10 => *10; 100 => *100
    remote_cmd_t    remote_cmd;     // remote function of command
    local_cmd_t     local_cmd;      // local function of command
    int32_t         arg1;           // argument1, e.g. - MIN setpoint. If not used must be -1
    int32_t         arg2;           // argument2, e.g. - MAX setpoint. If not used must be -1
} data_point_st_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t temperature;
} dp_schedule_model1_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint16_t temperature;
} dp_schedule_model2_t;

typedef dp_schedule_model2_t dp_schedule_model6_t;

enum {
    SCHEDULE_BIT_MON = 0,
    SCHEDULE_BIT_SAT,
    SCHEDULE_BIT_SUN,
};

enum {
    SCHEDULE_BIT_T1 = 0,
    SCHEDULE_BIT_T2,
    SCHEDULE_BIT_T3,
    SCHEDULE_BIT_T4,
    SCHEDULE_BIT_T5,
    SCHEDULE_BIT_T6,
    SCHEDULE_BIT_REQ,
};

typedef struct {
    dp_schedule_model2_t schedule[6];
} schedule_model8_t;

typedef struct {
    uint8_t     week_day;
    uint8_t     time_period;
    uint32_t    hour;
    uint32_t    minute;
    uint32_t    temperature;
} temp_schedule_model8_t;

extern schedule_model8_t schedule_model8[3];

extern uint8_t manuf_name;
extern data_point_st_t *data_point_model;
extern const char8_t **tuya_manuf_names[];

//void data_point_model_init();
//data_point_st_t *data_point_model_arr[DP_IDX_MAXNUM];

#endif /* SRC_INCLUDE_APP_TUYA_DATAPOINT_H_ */
