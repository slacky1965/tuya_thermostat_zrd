#ifndef SRC_INCLUDE_APP_MAIN_H_
#define SRC_INCLUDE_APP_MAIN_H_

#include "tl_common.h"
#include "zcl_include.h"
#include "bdb.h"
#include "ota.h"
#include "gp.h"

#include "zcl_relative_humidity_measurement.h"
#include "zcl_app_thermostat.h"
#include "zcl_thermostat_ui_cfg.h"
#include "zcl_app_fancontrol.h"

#include "app_utility.h"
#include "app_uart_tuya.h"
#include "app_tuya_datapoint.h"
#include "app_endpoint_cfg.h"
#include "app_uart.h"
#include "app_thermostat.h"
#include "app_time.h"
#include "app_bootloader.h"


typedef struct {
    uint8_t keyType; /* CERTIFICATION_KEY or MASTER_KEY key for touch-link or distribute network
                        SS_UNIQUE_LINK_KEY or SS_GLOBAL_LINK_KEY for distribute network */
    uint8_t key[16]; /* the key used */
} app_linkKey_info_t;

typedef struct {
    ev_timer_event_t *bdbFBTimerEvt;
    ev_timer_event_t *factory_resetTimerEvt;

//    uint32_t timeout;

//    u32 keyPressedTime;
//    u8  keyPressed;

    bool net_steer_start;

    app_linkKey_info_t tcLinkKey;
} app_ctx_t;

extern app_ctx_t g_appCtx;

extern bdb_appCb_t g_zbBdbCb;

extern bdb_commissionSetting_t g_bdbCommissionSetting;

extern const zcl_specClusterInfo_t g_appEp1ClusterList[];
extern const zcl_specClusterInfo_t g_appEp2ClusterList[];
extern const af_simple_descriptor_t app_ep1Desc;
extern const af_simple_descriptor_t app_ep2Desc;

void app_zclProcessIncomingMsg(zclIncoming_t *pInHdlrMsg);

status_t app_basicCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_identifyCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_powerCfgCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_groupCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_sceneCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_pollCtrlCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_thermostatCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_thermostat_uicCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_fancontrolCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_timeCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);
status_t app_displayLevelCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload);
status_t app_humidityCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload);

#define zcl_scene1AttrGet()         &g_zcl_scene1Attrs
#define zcl_scene2AttrGet()         &g_zcl_scene2Attrs
#define zcl_onoff1AttrGet()         &g_zcl_onOff1Attrs
#define zcl_onoff2AttrGet()         &g_zcl_onOff2Attrs
#define zcl_levelAttrGet()          &g_zcl_levelAttrs
#define zcl_colorAttrGet()          &g_zcl_colorCtrlAttrs
#define zcl_thermostatAttrGet()     &g_zcl_thermostatAttrs
#define zcl_fancontrolAttrGet()     &g_zcl_fancontrolAttrs

void app_leaveCnfHandler(nlme_leave_cnf_t *pLeaveCnf);
void app_leaveIndHandler(nlme_leave_ind_t *pLeaveInd);
void app_otaProcessMsgHandler(uint8_t evt, uint8_t status);
bool app_nwkUpdateIndicateHandler(nwkCmd_nwkUpdate_t *pNwkUpdate);
void app_wakeupPinLevelChange();


#endif /* SRC_INCLUDE_APP_MAIN_H_ */
