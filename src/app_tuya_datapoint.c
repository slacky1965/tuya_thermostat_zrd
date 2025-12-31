#include "tl_common.h"

#include "app_main.h"

static const char8_t *tuya_manuf_name1[] = {
                                           "u9bfwha0",
                                           "aoclfnxz",
                                            NULL};

static const char8_t *tuya_manuf_name2[] = {
                                           "edl8pz1k",
                                            NULL};

static const char8_t *tuya_manuf_name3[] = {
                                           "tagezcph",
                                            NULL};

static const char8_t *tuya_manuf_name4[] = {
                                           "xyugziqv",
                                            NULL};

static const char8_t *tuya_manuf_name5[] = {
                                           "5toc8efa",
                                            NULL};

static const char8_t *tuya_manuf_name6[] = {
                                           "lzriup1j",
                                           "oh8y8pv8",
                                           "gops3slb",
                                           "cvub6xbb",
                                            NULL};

static const char8_t *tuya_manuf_name7[] = {
                                           "mpbki2zm",
                                            NULL};

static const char8_t *tuya_manuf_name8[] = {
                                           "7rghpoxo",
                                            NULL};

static const char8_t *tuya_manuf_name9[] = {
                                           "6a4vxfnv",
                                            NULL};

static const char8_t *tuya_manuf_name0A[] = {
                                           "xalsoe3m",
                                            NULL};

static const char8_t *tuya_manuf_name0B[] = {
                                           "8byfmxdv",
                                            NULL};

static const char8_t *tuya_manuf_name0C[] = {
                                           "szbxmorb",
                                            NULL};

const char8_t **tuya_manuf_names[] = {
                                      tuya_manuf_name1,
                                      tuya_manuf_name2,
                                      tuya_manuf_name3,
                                      tuya_manuf_name4,
                                      tuya_manuf_name5,
                                      tuya_manuf_name6,
                                      tuya_manuf_name7,
                                      tuya_manuf_name8,
                                      tuya_manuf_name9,
                                      tuya_manuf_name0A,
                                      tuya_manuf_name0B,
                                      tuya_manuf_name0C
};

uint8_t manuf_name = MANUF_NAME_1;

//data_point_st_t *data_point_model_arr[DP_IDX_MAXNUM] = {
//                                                        data_point_model1,
//                                                        data_point_model2,
//                                                        data_point_model3,
//                                                        data_point_model4,
//                                                        data_point_model5,
//                                                        data_point_model6,
//                                                        data_point_model7,
//                                                        data_point_model8,
//                                                        data_point_model9,
//                                                        data_point_model0A,
//                                                        data_point_model0B
//};

// Not worked in gcc 4.5.1
//data_point_st_t *data_point_model = data_point_model_arr[MANUF_NAME_1];
data_point_st_t *data_point_model = NULL; //data_point_model1;

schedule_model8_t schedule_model8[3];

//void data_point_model_init() {
//
//    data_point_model = data_point_model_arr[MANUF_NAME_1];
//
////    for(uint16_t i = 0; i < DP_IDX_MAXNUM; i++) {
////        printf("i: %d, id: 0x%x, type: %d, len: %d, divisor: %d\r\n",
////                i, data_point_model[i].id, data_point_model[i].type, data_point_model[i].len, data_point_model[i].divisor);
////    }
//}
