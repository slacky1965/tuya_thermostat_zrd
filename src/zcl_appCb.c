/********************************************************************************************************
 * @file    zcl_appCb.c
 *
 * @brief   This is the source file for zcl_appCb
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *			All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zcl_include.h"

#include "app_main.h"


/**********************************************************************
 * LOCAL CONSTANTS
 */


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * LOCAL FUNCTIONS
 */
#ifdef ZCL_READ
static void app_zclReadRspCmd(uint16_t clusterId, zclReadRspCmd_t *pReadRspCmd);
#endif
#ifdef ZCL_WRITE
static void app_zclWriteRspCmd(uint16_t clusterId, zclWriteRspCmd_t *pWriteRspCmd);
static void app_zclWriteReqCmd(uint8_t endPoint, uint16_t clusterId, zclWriteCmd_t *pWriteReqCmd);
#endif
#ifdef ZCL_REPORT
static void app_zclCfgReportCmd(uint8_t endPoint, uint16_t clusterId, zclCfgReportCmd_t *pCfgReportCmd);
static void app_zclCfgReportRspCmd(uint16_t clusterId, zclCfgReportRspCmd_t *pCfgReportRspCmd);
static void app_zclReportCmd(uint16_t clusterId, zclReportCmd_t *pReportCmd);
#endif
static void app_zclDfltRspCmd(uint16_t clusterId, zclDefaultRspCmd_t *pDftRspCmd);


/**********************************************************************
 * GLOBAL VARIABLES
 */


/**********************************************************************
 * LOCAL VARIABLES
 */
#ifdef ZCL_IDENTIFY
static ev_timer_event_t *identifyTimerEvt = NULL;
#endif

/**********************************************************************
 * FUNCTIONS
 */

/*********************************************************************
 * @fn      app_zclProcessIncomingMsg
 *
 * @brief   Process ZCL Foundation incoming message.
 *
 * @param   pInMsg - pointer to the received message
 *
 * @return  None
 */
void app_zclProcessIncomingMsg(zclIncoming_t *pInHdlrMsg)
{
//    printf("app_zclProcessIncomingMsg\r\n");

	uint16_t cluster = pInHdlrMsg->msg->indInfo.cluster_id;
	uint8_t endPoint = pInHdlrMsg->msg->indInfo.dst_ep;
	switch(pInHdlrMsg->hdr.cmd)
	{
#ifdef ZCL_READ
		case ZCL_CMD_READ_RSP:
			app_zclReadRspCmd(cluster, pInHdlrMsg->attrCmd);
			break;
#endif
#ifdef ZCL_WRITE
		case ZCL_CMD_WRITE_RSP:
			app_zclWriteRspCmd(cluster, pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_WRITE:
		    app_zclWriteReqCmd(endPoint, cluster, pInHdlrMsg->attrCmd);
			break;
#endif
#ifdef ZCL_REPORT
		case ZCL_CMD_CONFIG_REPORT:
			app_zclCfgReportCmd(endPoint, cluster, pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_CONFIG_REPORT_RSP:
			app_zclCfgReportRspCmd(cluster, pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_REPORT:
			app_zclReportCmd(cluster, pInHdlrMsg->attrCmd);
			break;
#endif
		case ZCL_CMD_DEFAULT_RSP:
			app_zclDfltRspCmd(cluster, pInHdlrMsg->attrCmd);
			break;
		default:
			break;
	}
}

#ifdef ZCL_READ
/*********************************************************************
 * @fn      app_zclReadRspCmd
 *
 * @brief   Handler for ZCL Read Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void app_zclReadRspCmd(uint16_t clusterId, zclReadRspCmd_t *pReadRspCmd)
{
    //printf("app_zclReadRspCmd\n");
    uint8_t numAttr = pReadRspCmd->numAttr;
    zclReadRspStatus_t *attrList = pReadRspCmd->attrList;

    uint32_t utc;
    uint32_t time_local;
    bool time_sent = false;

    for (uint8_t i = 0; i < numAttr; i++) {
        if (attrList[i].attrID == ZCL_ATTRID_TIME && attrList[i].status == ZCL_STA_SUCCESS) {
            utc = attrList[i].data[0] & 0xff;
            utc |= (attrList[i].data[1] << 8)  & 0x0000ffff;
            utc |= (attrList[i].data[2] << 16) & 0x00ffffff;
            utc |= (attrList[i].data[3] << 24) & 0xffffffff;
            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_TIME, (uint8_t*)&utc);
            time_sent = true;
#if UART_PRINTF_MODE && DEBUG_TIME
            printf("Sync UTC:        %d\r\n", utc+UNIX_TIME_CONST);
#endif
        } else if (attrList[i].attrID == ZCL_ATTRID_LOCAL_TIME && attrList[i].status == ZCL_STA_SUCCESS) {
            time_local = attrList[i].data[0] & 0xff;
            time_local |= (attrList[i].data[1] << 8)  & 0x0000ffff;
            time_local |= (attrList[i].data[2] << 16) & 0x00ffffff;
            time_local |= (attrList[i].data[3] << 24) & 0xffffffff;
            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_LOCAL_TIME, (uint8_t*)&time_local);
            time_sent = true;
#if UART_PRINTF_MODE && DEBUG_TIME
            printf("Sync Local Time: %d\r\n", time_local+UNIX_TIME_CONST);
#endif
        }
    }

    if (time_sent) {
        set_time_sent();
    }
}
#endif	/* ZCL_READ */

#ifdef ZCL_WRITE
/*********************************************************************
 * @fn      app_zclWriteRspCmd
 *
 * @brief   Handler for ZCL Write Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void app_zclWriteRspCmd(uint16_t clusterId, zclWriteRspCmd_t *pWriteRspCmd)
{
//    printf("app_zclWriteRspCmd\r\n");

}

/*********************************************************************
 * @fn      app_zclWriteReqCmd
 *
 * @brief   Handler for ZCL Write Request command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void app_zclWriteReqCmd(uint8_t endPoint, uint16_t clusterId, zclWriteCmd_t *pWriteReqCmd) {
    uint8_t numAttr = pWriteReqCmd->numAttr;
    zclWriteRec_t *attr = pWriteReqCmd->attrList;


//    printf("app_zclWriteReqCmd\r\n");

    if (clusterId == ZCL_CLUSTER_HAVC_THERMOSTAT) {
        for (uint32_t i = 0; i < numAttr; i++) {
            if (attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE) {
                uint8_t sys_mode = attr[i].attrData[0];
                if (data_point_model[DP_IDX_ONOFF].remote_cmd)
                    data_point_model[DP_IDX_ONOFF].remote_cmd(&sys_mode);
            } else if (attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT) {
                uint16_t temp = BUILD_S16(attr[i].attrData[0], attr[i].attrData[1]);
                if (data_point_model[DP_IDX_SETPOINT].remote_cmd)
                    data_point_model[DP_IDX_SETPOINT].remote_cmd(&temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION) {
                int8_t temp = (int8_t)attr[i].attrData[0];
                if (data_point_model[DP_IDX_CALIBRATION].remote_cmd)
                    data_point_model[DP_IDX_CALIBRATION].remote_cmd(&temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED) {
                uint8_t sensor_used = attr[i].attrData[0];
                if (data_point_model[DP_IDX_SENSOR].remote_cmd)
                    data_point_model[DP_IDX_SENSOR].remote_cmd(&sensor_used);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND) {
                uint8_t dead_band = attr[i].attrData[0];
                if (data_point_model[DP_IDX_DEADZONE].remote_cmd)
                    data_point_model[DP_IDX_DEADZONE].remote_cmd(&dead_band);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT) {
                uint16_t min_temp = BUILD_S16(attr[i].attrData[0], attr[i].attrData[1]);
                if (data_point_model[DP_IDX_MIN].remote_cmd)
                    data_point_model[DP_IDX_MIN].remote_cmd(&min_temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT) {
                uint16_t max_temp = BUILD_S16(attr[i].attrData[0], attr[i].attrData[1]);
                if (data_point_model[DP_IDX_MAX].remote_cmd)
                    data_point_model[DP_IDX_MAX].remote_cmd(&max_temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE) {
                uint8_t oper_mode = attr[i].attrData[0];
                if (data_point_model[DP_IDX_PROG].remote_cmd)
                    data_point_model[DP_IDX_PROG].remote_cmd(&oper_mode);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT) {
                uint16_t temp = BUILD_S16(attr[i].attrData[0], attr[i].attrData[1]);
                if (data_point_model[DP_IDX_FROST_PROTECT].remote_cmd)
                    data_point_model[DP_IDX_FROST_PROTECT].remote_cmd(&temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_HEAT_PROTECT) {
                uint16_t temp = BUILD_S16(attr[i].attrData[0], attr[i].attrData[1]);
                if (data_point_model[DP_IDX_HEAT_PROTECT].remote_cmd)
                    data_point_model[DP_IDX_HEAT_PROTECT].remote_cmd(&temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE) {
                uint8_t eco_mode = attr[i].attrData[0];
                if (data_point_model[DP_IDX_ECO_MODE].remote_cmd)
                    data_point_model[DP_IDX_ECO_MODE].remote_cmd(&eco_mode);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE_HEAT_TEMPERATURE) {
                uint16_t temp = BUILD_S16(attr[i].attrData[0], attr[i].attrData[1]);
                if (data_point_model[DP_IDX_ECO_HEAT_TEMP].remote_cmd)
                    data_point_model[DP_IDX_ECO_HEAT_TEMP].remote_cmd(&temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE_COOL_TEMPERATURE) {
                uint16_t temp = BUILD_S16(attr[i].attrData[0], attr[i].attrData[1]);
                if (data_point_model[DP_IDX_ECO_COOL_TEMP].remote_cmd)
                    data_point_model[DP_IDX_ECO_COOL_TEMP].remote_cmd(&temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT_ONOFF) {
                uint8_t frost = attr[i].attrData[0];
                if (data_point_model[DP_IDX_FROST_PROTECT].remote_cmd)
                    data_point_model[DP_IDX_FROST_PROTECT].remote_cmd(&frost);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SOUND) {
                uint8_t sound = attr[i].attrData[0];
                if (data_point_model[DP_IDX_SOUND].remote_cmd)
                    data_point_model[DP_IDX_SOUND].remote_cmd(&sound);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_LEVEL) {
                uint8_t level = attr[i].attrData[0];
                if (data_point_model[DP_IDX_LEVEL_A].remote_cmd)
                    data_point_model[DP_IDX_LEVEL_A].remote_cmd(&level);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SCHEDULE_MODE) {
                uint8_t mode = attr[i].attrData[0];
                if (data_point_model[DP_IDX_SCHEDULE_MON].remote_cmd)
                    data_point_model[DP_IDX_SCHEDULE_MON].remote_cmd(&mode);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_INVERSION) {
                uint8_t inversion = attr[i].attrData[0];
                if (data_point_model[DP_IDX_INVERSION].remote_cmd)
                    data_point_model[DP_IDX_INVERSION].remote_cmd(&inversion);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SETTINGS_RESET) {
                uint8_t sreset = attr[i].attrData[0];
                if (data_point_model[DP_IDX_SETTINGS_RESET].remote_cmd)
                    data_point_model[DP_IDX_SETTINGS_RESET].remote_cmd(&sreset);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_EXT_TEMP_CALIBRATION) {
                int8_t temp = (int8_t)attr[i].attrData[0];
                if (data_point_model[DP_IDX_EXT_CALIBRATION].remote_cmd)
                    data_point_model[DP_IDX_EXT_CALIBRATION].remote_cmd(&temp);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_MODE_KEYLOCK) {
                uint8_t mode = attr[i].attrData[0];
                if (data_point_model[DP_IDX_MODE_LOCK].remote_cmd)
                    data_point_model[DP_IDX_MODE_LOCK].remote_cmd(&mode);
            } else if(attr[i].attrID == ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_MANUF_NAME) {
                uint8_t m_name = attr[i].attrData[0];
                printf("Manual set namufacturer name: %d\r\n", m_name);
                thermostat_settings_save();
                TL_ZB_TIMER_SCHEDULE(delayedMcuResetCb, NULL, TIMEOUT_2SEC);
            }
        }
    }


    if (clusterId == ZCL_CLUSTER_HAVC_FAN_CONTROL) {
        for (uint32_t i = 0; i < numAttr; i++) {
            if (attr[i].attrID == ZCL_ATTRID_HVAC_FANCONTROL_FANMODE) {
                uint8_t mode = attr[i].attrData[0];
                if (data_point_model[DP_IDX_FAN_MODE].remote_cmd)
                    data_point_model[DP_IDX_FAN_MODE].remote_cmd(&mode);
            } else if (attr[i].attrID == ZCL_ATTRID_HVAC_FANCONTROL_CUSTOM_CONTROL) {
                uint8_t control = attr[i].attrData[0];
                if (data_point_model[DP_IDX_FAN_CONTROL].remote_cmd)
                    data_point_model[DP_IDX_FAN_CONTROL].remote_cmd(&control);
            }
        }
    }

    if (clusterId == ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG) {
        for (uint32_t i = 0; i < numAttr; i++) {
            if (attr[i].attrID == ZCL_ATTRID_HVAC_TEMPERATURE_DISPLAY_MODE) {
//                uint8_t display_mode = attr[i].attrData[0];
//                remote_cmd_display_mode(display_mode);
            } else if (attr[i].attrID == ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT) {
                uint8_t keylock = attr[i].attrData[0];
                if (data_point_model[DP_IDX_LOCKUNLOCK].remote_cmd)
                    data_point_model[DP_IDX_LOCKUNLOCK].remote_cmd(&keylock);
            }
        }

    }

    if (clusterId == ZCL_CLUSTER_MS_RELATIVE_HUMIDITY) {
        for(uint8_t i = 0; i < numAttr; i++) {
            if (attr[i].attrID == ZCL_RELATIVE_HUMIDITY_MEASUREMENT_ATTRID_CUSTOM_HUMIDITY_OFFSET) {
                int16_t hum_offset = attr[i].attrData[0] & 0xff;
                hum_offset |= (attr[i].attrData[1] << 8) & 0xffff;
//                printf("Humidity offset: %d\r\n", hum_offset);
                if (data_point_model[DP_IDX_HUMIDITY_OFFSET].remote_cmd)
                    data_point_model[DP_IDX_HUMIDITY_OFFSET].remote_cmd(&hum_offset);
            }
        }
    }

#ifdef ZCL_POLL_CTRL
	if(clusterId == ZCL_CLUSTER_GEN_POLL_CONTROL){
		for(int32_t i = 0; i < numAttr; i++){
			if(attr[i].attrID == ZCL_ATTRID_CHK_IN_INTERVAL){
				app_zclCheckInStart();
				return;
			}
		}
	}
#endif
}
#endif	/* ZCL_WRITE */


/*********************************************************************
 * @fn      app_zclDfltRspCmd
 *
 * @brief   Handler for ZCL Default Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void app_zclDfltRspCmd(uint16_t clusterId, zclDefaultRspCmd_t *pDftRspCmd)
{
//    printf("app_zclDfltRspCmd\r\n");

}

#ifdef ZCL_REPORT
/*********************************************************************
 * @fn      app_zclCfgReportCmd
 *
 * @brief   Handler for ZCL Configure Report command.
 *
 * @param   pInHdlrMsg - incoming message to process
 * @param   dst_ep     - number of endPoint
 *
 * @return  None
 */
static void app_zclCfgReportCmd(uint8_t endPoint, uint16_t clusterId, zclCfgReportCmd_t *pCfgReportCmd)
{
    //printf("app_zclCfgReportCmd\r\n");
//    reportCfgInfo_t *pEntry;
//    for(uint8_t i = 0; i < pCfgReportCmd->numAttr; i++) {
//        for (uint8_t ii = 0; ii < ZCL_REPORTING_TABLE_NUM; ii++) {
//            pEntry = &reportingTab.reportCfgInfo[ii];
//            if (pEntry->used) {
//                printf("attrId: 0x%x, maxInterval: %d, minInterval: %d\r\n", pEntry->attrID, pEntry->maxInterval, pEntry->minInterval);
//
//            }
////            if (app_reporting[ii].pEntry->used) {
////                if (app_reporting[ii].pEntry->endPoint == endPoint && app_reporting[ii].pEntry->attrID == pCfgReportCmd->attrList[i].attrID) {
////                    if (app_reporting[ii].timerReportMinEvt) {
////                        TL_ZB_TIMER_CANCEL(&app_reporting[ii].timerReportMinEvt);
////                    }
////                    if (app_reporting[ii].timerReportMaxEvt) {
////                        TL_ZB_TIMER_CANCEL(&app_reporting[ii].timerReportMaxEvt);
////                    }
////                    return;
////                }
////            }
//        }
//    }
}

/*********************************************************************
 * @fn      app_zclCfgReportRspCmd
 *
 * @brief   Handler for ZCL Configure Report Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void app_zclCfgReportRspCmd(uint16_t clusterId, zclCfgReportRspCmd_t *pCfgReportRspCmd)
{
    //printf("app_zclCfgReportRspCmd\r\n");

}

/*********************************************************************
 * @fn      app_zclReportCmd
 *
 * @brief   Handler for ZCL Report command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void app_zclReportCmd(uint16_t clusterId, zclReportCmd_t *pReportCmd)
{
    //printf("app_zclReportCmd\n");

}
#endif	/* ZCL_REPORT */

#ifdef ZCL_BASIC
/*********************************************************************
 * @fn      app_zclBasicResetCmdHandler
 *
 * @brief   Handler for ZCL Basic Reset command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t app_basicCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload)
{
	if(cmdId == ZCL_CMD_BASIC_RESET_FAC_DEFAULT){
		//Reset all the attributes of all its clusters to factory defaults
		//zcl_nv_attr_reset();
	}

	return ZCL_STA_SUCCESS;
}
#endif	/* ZCL_BASIC */

#ifdef ZCL_IDENTIFY
int32_t app_zclIdentifyTimerCb(void *arg)
{
	if(g_zcl_identifyAttrs.identifyTime <= 0){
		identifyTimerEvt = NULL;
		return -1;
	}
	g_zcl_identifyAttrs.identifyTime--;
	return 0;
}

void app_zclIdentifyTimerStop(void)
{
	if(identifyTimerEvt){
		TL_ZB_TIMER_CANCEL(&identifyTimerEvt);
	}
}

/*********************************************************************
 * @fn      app_zclIdentifyCmdHandler
 *
 * @brief   Handler for ZCL Identify command. This function will set blink LED.
 *
 * @param   endpoint
 * @param   srcAddr
 * @param   identifyTime - identify time
 *
 * @return  None
 */
void app_zclIdentifyCmdHandler(uint8_t endpoint, uint16_t srcAddr, uint16_t identifyTime)
{
	g_zcl_identifyAttrs.identifyTime = identifyTime;

	if(identifyTime == 0){
		app_zclIdentifyTimerStop();
//		light_blink_stop();
	}else{
		if(!identifyTimerEvt){
//			light_blink_start(identifyTime, 500, 500);
			identifyTimerEvt = TL_ZB_TIMER_SCHEDULE(app_zclIdentifyTimerCb, NULL, 1000);
		}
	}
}

/*********************************************************************
 * @fn      app_zcltriggerCmdHandler
 *
 * @brief   Handler for ZCL trigger command.
 *
 * @param   pTriggerEffect
 *
 * @return  None
 */
static void app_zcltriggerCmdHandler(zcl_triggerEffect_t *pTriggerEffect)
{
	uint8_t effectId = pTriggerEffect->effectId;
	//uint8_t effectVariant = pTriggerEffect->effectVariant;

	switch(effectId){
		case IDENTIFY_EFFECT_BLINK:
//			light_blink_start(1, 500, 500);
			break;
		case IDENTIFY_EFFECT_BREATHE:
//			light_blink_start(15, 300, 700);
			break;
		case IDENTIFY_EFFECT_OKAY:
//			light_blink_start(2, 250, 250);
			break;
		case IDENTIFY_EFFECT_CHANNEL_CHANGE:
//			light_blink_start(1, 500, 7500);
			break;
		case IDENTIFY_EFFECT_FINISH_EFFECT:
//			light_blink_start(1, 300, 700);
			break;
		case IDENTIFY_EFFECT_STOP_EFFECT:
//			light_blink_stop();
			break;
		default:
			break;
	}
}

/*********************************************************************
 * @fn      app_zclIdentifyQueryRspCmdHandler
 *
 * @brief   Handler for ZCL Identify Query response command.
 *
 * @param   endpoint
 * @param   srcAddr
 * @param   identifyRsp
 *
 * @return  None
 */
static void app_zclIdentifyQueryRspCmdHandler(uint8_t endpoint, uint16_t srcAddr, zcl_identifyRspCmd_t *identifyRsp)
{
#if FIND_AND_BIND_SUPPORT
	if(identifyRsp->timeout){
		findBindDst_t dstInfo;
		dstInfo.addr = srcAddr;
		dstInfo.endpoint = endpoint;

		bdb_addIdentifyActiveEpForFB(dstInfo);
	}
#endif
}

/*********************************************************************
 * @fn      app_identifyCb
 *
 * @brief   Handler for ZCL Identify command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t app_identifyCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload)
{

//    printf("app_identifyCb()\r\n");

	if(pAddrInfo->dstEp == APP_ENDPOINT1){
		if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
			switch(cmdId){
				case ZCL_CMD_IDENTIFY:
					app_zclIdentifyCmdHandler(pAddrInfo->dstEp, pAddrInfo->srcAddr, ((zcl_identifyCmd_t *)cmdPayload)->identifyTime);
					break;
				case ZCL_CMD_TRIGGER_EFFECT:
					app_zcltriggerCmdHandler((zcl_triggerEffect_t *)cmdPayload);
					break;
				default:
					break;
			}
		}else{
			if(cmdId == ZCL_CMD_IDENTIFY_QUERY_RSP){
				app_zclIdentifyQueryRspCmdHandler(pAddrInfo->dstEp, pAddrInfo->srcAddr, (zcl_identifyRspCmd_t *)cmdPayload);
			}
		}
	}

	return ZCL_STA_SUCCESS;
}
#endif	/* ZCL_IDENTIFY */

#ifdef ZCL_IAS_ZONE
/*********************************************************************
 * @fn      leak_zclIasZoneEnrollRspCmdHandler
 *
 * @brief   Handler for ZCL IAS ZONE Enroll response command.
 *
 * @param   pZoneEnrollRsp
 *
 * @return  None
 */
static void leak_zclIasZoneEnrollRspCmdHandler(zoneEnrollRsp_t *pZoneEnrollRsp, uint8_t endpoint) {

    //printf("zclIasZoneEnrollRspCmdHandler endpoint: %d, code: %d zone_id: %d\r\n", endpoint, pZoneEnrollRsp->code, pZoneEnrollRsp->zoneId);
    if (pZoneEnrollRsp->zoneId != ZCL_ZONE_ID_INVALID) {
        u8 zoneState;
        zoneState = ZONE_STATE_ENROLLED;
        zcl_setAttrVal(endpoint, ZCL_CLUSTER_SS_IAS_ZONE, ZCL_ATTRID_ZONE_ID, &(pZoneEnrollRsp->zoneId));
        zcl_setAttrVal(endpoint, ZCL_CLUSTER_SS_IAS_ZONE, ZCL_ATTRID_ZONE_STATE, &zoneState);
    }

}

/*********************************************************************
 * @fn      leak_zclIasZoneInitNormalOperationModeCmdHandler
 *
 * @brief   Handler for ZCL IAS ZONE normal operation mode command.
 *
 * @param
 *
 * @return  status
 */
static status_t leak_zclIasZoneInitNormalOperationModeCmdHandler(void) {

    //printf("zclIasZoneInitNormalOperationModeCmdHandler\r\n");
    u8 status = ZCL_STA_FAILURE;

    return status;
}

/*********************************************************************
 * @fn      leak_zclIasZoneInitTestModeCmdHandler
 *
 * @brief   Handler for ZCL IAS ZONE test mode command.
 *
 * @param   pZoneInitTestMode
 *
 * @return  status
 */
static status_t leak_zclIasZoneInitTestModeCmdHandler(zoneInitTestMode_t *pZoneInitTestMode) {

    //printf("zclIasZoneInitNormalOperationModeCmdHandler\r\n");
    u8 status = ZCL_STA_FAILURE;

    return status;
}

/*********************************************************************
 * @fn      leak_iasZoneCb
 *
 * @brief   Handler for ZCL IAS Zone command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t leak_iasZoneCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
    status_t status = ZCL_STA_SUCCESS;

    if(pAddrInfo->dstEp == APP_ENDPOINT4 || pAddrInfo->dstEp == APP_ENDPOINT5){
        if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
            switch(cmdId){
                case ZCL_CMD_ZONE_ENROLL_RSP:
                    leak_zclIasZoneEnrollRspCmdHandler((zoneEnrollRsp_t *)cmdPayload, pAddrInfo->dstEp);
                    break;
                case ZCL_CMD_INIT_NORMAL_OPERATION_MODE:
                    leak_zclIasZoneInitNormalOperationModeCmdHandler();
                    break;
                case ZCL_CMD_INIT_TEST_MODE:
                    leak_zclIasZoneInitTestModeCmdHandler((zoneInitTestMode_t *)cmdPayload);
                    break;
                default:
                    break;
            }
        }
    }

    return status;
}
#endif  /* ZCL_IAS_ZONE */


/*********************************************************************
 * @fn      app_powerCfgCb
 *
 * @brief   Handler for ZCL Identify command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t app_powerCfgCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload)
{

    return ZCL_STA_SUCCESS;
}


#ifdef ZCL_GROUP
/*********************************************************************
 * @fn      app_zclAddGroupRspCmdHandler
 *
 * @brief   Handler for ZCL add group response command.
 *
 * @param   pAddGroupRsp
 *
 * @return  None
 */
static void app_zclAddGroupRspCmdHandler(uint8_t ep, zcl_addGroupRsp_t *pAddGroupRsp) {

//    printf("app_zclAddGroupRspCmdHandler. ep: %d, status: %d, gid: %d\r\n", ep, pAddGroupRsp->status, pAddGroupRsp->groupId);
}

/*********************************************************************
 * @fn      app_zclViewGroupRspCmdHandler
 *
 * @brief   Handler for ZCL view group response command.
 *
 * @param   pViewGroupRsp
 *
 * @return  None
 */
static void app_zclViewGroupRspCmdHandler(zcl_viewGroupRsp_t *pViewGroupRsp)
{

}

/*********************************************************************
 * @fn      app_zclRemoveGroupRspCmdHandler
 *
 * @brief   Handler for ZCL remove group response command.
 *
 * @param   pRemoveGroupRsp
 *
 * @return  None
 */
static void app_zclRemoveGroupRspCmdHandler(zcl_removeGroupRsp_t *pRemoveGroupRsp)
{

}

/*********************************************************************
 * @fn      app_zclGetGroupMembershipRspCmdHandler
 *
 * @brief   Handler for ZCL get group membership response command.
 *
 * @param   pGetGroupMembershipRsp
 *
 * @return  None
 */
static void app_zclGetGroupMembershipRspCmdHandler(zcl_getGroupMembershipRsp_t *pGetGroupMembershipRsp)
{

}

/*********************************************************************
 * @fn      app_groupCb
 *
 * @brief   Handler for ZCL Group command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t app_groupCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload) {

//    printf("app_groupCb. ep: %d\r\n", pAddrInfo->dstEp);

	if(pAddrInfo->dstEp == APP_ENDPOINT1 || pAddrInfo->dstEp == APP_ENDPOINT2) {
		if(pAddrInfo->dirCluster == ZCL_FRAME_SERVER_CLIENT_DIR){
			switch(cmdId){
				case ZCL_CMD_GROUP_ADD_GROUP_RSP:
					app_zclAddGroupRspCmdHandler(pAddrInfo->dstEp, (zcl_addGroupRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_GROUP_VIEW_GROUP_RSP:
					app_zclViewGroupRspCmdHandler((zcl_viewGroupRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_GROUP_REMOVE_GROUP_RSP:
					app_zclRemoveGroupRspCmdHandler((zcl_removeGroupRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_GROUP_GET_MEMBERSHIP_RSP:
					app_zclGetGroupMembershipRspCmdHandler((zcl_getGroupMembershipRsp_t *)cmdPayload);
					break;
				default:
					break;
			}
		}
	}

	return ZCL_STA_SUCCESS;
}
#endif	/* ZCL_GROUP */

#ifdef ZCL_SCENE
/*********************************************************************
 * @fn      app_zclAddSceneRspCmdHandler
 *
 * @brief   Handler for ZCL add scene response command.
 *
 * @param   cmdId
 * @param   pAddSceneRsp
 *
 * @return  None
 */
static void app_zclAddSceneRspCmdHandler(uint8_t cmdId, addSceneRsp_t *pAddSceneRsp)
{

}

/*********************************************************************
 * @fn      app_zclViewSceneRspCmdHandler
 *
 * @brief   Handler for ZCL view scene response command.
 *
 * @param   cmdId
 * @param   pViewSceneRsp
 *
 * @return  None
 */
static void app_zclViewSceneRspCmdHandler(uint8_t cmdId, viewSceneRsp_t *pViewSceneRsp)
{

}

/*********************************************************************
 * @fn      app_zclRemoveSceneRspCmdHandler
 *
 * @brief   Handler for ZCL remove scene response command.
 *
 * @param   pRemoveSceneRsp
 *
 * @return  None
 */
static void app_zclRemoveSceneRspCmdHandler(removeSceneRsp_t *pRemoveSceneRsp)
{

}

/*********************************************************************
 * @fn      app_zclRemoveAllSceneRspCmdHandler
 *
 * @brief   Handler for ZCL remove all scene response command.
 *
 * @param   pRemoveAllSceneRsp
 *
 * @return  None
 */
static void app_zclRemoveAllSceneRspCmdHandler(removeAllSceneRsp_t *pRemoveAllSceneRsp)
{

}

/*********************************************************************
 * @fn      app_zclStoreSceneRspCmdHandler
 *
 * @brief   Handler for ZCL store scene response command.
 *
 * @param   pStoreSceneRsp
 *
 * @return  None
 */
static void app_zclStoreSceneRspCmdHandler(storeSceneRsp_t *pStoreSceneRsp)
{

}

/*********************************************************************
 * @fn      app_zclGetSceneMembershipRspCmdHandler
 *
 * @brief   Handler for ZCL get scene membership response command.
 *
 * @param   pGetSceneMembershipRsp
 *
 * @return  None
 */
static void app_zclGetSceneMembershipRspCmdHandler(getSceneMemRsp_t *pGetSceneMembershipRsp)
{

}

/*********************************************************************
 * @fn      app_sceneCb
 *
 * @brief   Handler for ZCL Scene command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t app_sceneCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload)
{
	if(pAddrInfo->dstEp == APP_ENDPOINT1){
		if(pAddrInfo->dirCluster == ZCL_FRAME_SERVER_CLIENT_DIR){
			switch(cmdId){
				case ZCL_CMD_SCENE_ADD_SCENE_RSP:
				case ZCL_CMD_SCENE_ENHANCED_ADD_SCENE_RSP:
					app_zclAddSceneRspCmdHandler(cmdId, (addSceneRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_SCENE_VIEW_SCENE_RSP:
				case ZCL_CMD_SCENE_ENHANCED_VIEW_SCENE_RSP:
					app_zclViewSceneRspCmdHandler(cmdId, (viewSceneRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_SCENE_REMOVE_SCENE_RSP:
					app_zclRemoveSceneRspCmdHandler((removeSceneRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_SCENE_REMOVE_ALL_SCENE_RSP:
					app_zclRemoveAllSceneRspCmdHandler((removeAllSceneRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_SCENE_STORE_SCENE_RSP:
					app_zclStoreSceneRspCmdHandler((storeSceneRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_SCENE_GET_SCENE_MEMSHIP_RSP:
					app_zclGetSceneMembershipRspCmdHandler((getSceneMemRsp_t *)cmdPayload);
					break;
				default:
					break;
			}
		}
	}

	return ZCL_STA_SUCCESS;
}
#endif	/* ZCL_SCENE */

#ifdef ZCL_POLL_CTRL
static ev_timer_event_t *zclFastPollTimeoutTimerEvt = NULL;
static ev_timer_event_t *zclCheckInTimerEvt = NULL;
static bool isFastPollMode = FALSE;

void app_zclCheckInCmdSend(void)
{
	epInfo_t dstEpInfo;
	TL_SETSTRUCTCONTENT(dstEpInfo, 0);

	dstEpInfo.dstAddrMode = APS_DSTADDR_EP_NOTPRESETNT;
	dstEpInfo.dstEp = APP_ENDPOINT;
	dstEpInfo.profileId = HA_PROFILE_ID;

	zcl_pollCtrl_checkInCmd(APP_ENDPOINT, &dstEpInfo, TRUE);
}

int32_t app_zclCheckInTimerCb(void *arg)
{
	zcl_pollCtrlAttr_t *pPollCtrlAttr = zcl_pollCtrlAttrGet();

	if(!pPollCtrlAttr->chkInInterval){
		zclCheckInTimerEvt = NULL;
		return -1;
	}

	app_zclCheckInCmdSend();

	return 0;
}

void app_zclCheckInStart(void)
{
	if(zb_bindingTblSearched(ZCL_CLUSTER_GEN_POLL_CONTROL, APP_ENDPOINT)){
		zcl_pollCtrlAttr_t *pPollCtrlAttr = zcl_pollCtrlAttrGet();

		if(!zclCheckInTimerEvt){
			zclCheckInTimerEvt = TL_ZB_TIMER_SCHEDULE(app_zclCheckInTimerCb, NULL, pPollCtrlAttr->chkInInterval * POLL_RATE_QUARTERSECONDS);
			
			if(pPollCtrlAttr->chkInInterval){
				app_zclCheckInCmdSend();
			}
		}
	}
}

void app_zclSetFastPollMode(bool fastPollMode)
{
	zcl_pollCtrlAttr_t *pPollCtrlAttr = zcl_pollCtrlAttrGet();

	isFastPollMode = fastPollMode;
	uint32_t pollRate = fastPollMode ? pPollCtrlAttr->shortPollInterval : pPollCtrlAttr->longPollInterval;

	zb_setPollRate(pollRate  * POLL_RATE_QUARTERSECONDS);
}

int32_t app_zclFastPollTimeoutCb(void *arg)
{
	app_zclSetFastPollMode(FALSE);

	zclFastPollTimeoutTimerEvt = NULL;
	return -1;
}

static status_t app_zclPollCtrlChkInRspCmdHandler(zcl_chkInRsp_t *pCmd)
{
	zcl_pollCtrlAttr_t *pPollCtrlAttr = zcl_pollCtrlAttrGet();

	if(pCmd->startFastPolling){
		uint16_t fastPollTimeoutCnt = 0;

		if(pCmd->fastPollTimeout){
			if(pCmd->fastPollTimeout > pPollCtrlAttr->fastPollTimeoutMax){
				return ZCL_STA_INVALID_FIELD;
			}

			fastPollTimeoutCnt = pCmd->fastPollTimeout;
		}else{
			fastPollTimeoutCnt = pPollCtrlAttr->fastPollTimeout;
		}

		if(fastPollTimeoutCnt){
			app_zclSetFastPollMode(TRUE);
			
			if(zclFastPollTimeoutTimerEvt){
				TL_ZB_TIMER_CANCEL(&zclFastPollTimeoutTimerEvt);
			}
			zclFastPollTimeoutTimerEvt = TL_ZB_TIMER_SCHEDULE(app_zclFastPollTimeoutCb, NULL, fastPollTimeoutCnt * POLL_RATE_QUARTERSECONDS);
		}
	}else{
		//continue in normal operation and not required to go into fast poll mode.
	}

	return ZCL_STA_SUCCESS;
}

static status_t app_zclPollCtrlFastPollStopCmdHandler(void)
{
	if(!isFastPollMode){
		return ZCL_STA_ACTION_DENIED;
	}else{
		if(zclFastPollTimeoutTimerEvt){
			TL_ZB_TIMER_CANCEL(&zclFastPollTimeoutTimerEvt);
		}
		app_zclSetFastPollMode(FALSE);
	}

	return ZCL_STA_SUCCESS;
}

static status_t app_zclPollCtrlSetLongPollIntervalCmdHandler(zcl_setLongPollInterval_t *pCmd)
{
	zcl_pollCtrlAttr_t *pPollCtrlAttr = zcl_pollCtrlAttrGet();

	if((pCmd->newLongPollInterval >= 0x04) && (pCmd->newLongPollInterval <= 0x6E0000)
		&& (pCmd->newLongPollInterval <= pPollCtrlAttr->chkInInterval) && (pCmd->newLongPollInterval >= pPollCtrlAttr->shortPollInterval)){
		pPollCtrlAttr->longPollInterval = pCmd->newLongPollInterval;
		zb_setPollRate(pCmd->newLongPollInterval * POLL_RATE_QUARTERSECONDS);
	}else{
		return ZCL_STA_INVALID_VALUE;
	}

	return ZCL_STA_SUCCESS;
}

static status_t app_zclPollCtrlSetShortPollIntervalCmdHandler(zcl_setShortPollInterval_t *pCmd)
{
	zcl_pollCtrlAttr_t *pPollCtrlAttr = zcl_pollCtrlAttrGet();

	if((pCmd->newShortPollInterval >= 0x01) && (pCmd->newShortPollInterval <= 0xff)
		&& (pCmd->newShortPollInterval <= pPollCtrlAttr->longPollInterval)){
		pPollCtrlAttr->shortPollInterval = pCmd->newShortPollInterval;
		zb_setPollRate(pCmd->newShortPollInterval * POLL_RATE_QUARTERSECONDS);
	}else{
		return ZCL_STA_INVALID_VALUE;
	}

	return ZCL_STA_SUCCESS;
}

/*********************************************************************
 * @fn      app_pollCtrlCb
 *
 * @brief   Handler for ZCL Poll Control command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t app_pollCtrlCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload)
{
	status_t status = ZCL_STA_SUCCESS;

	if(pAddrInfo->dstEp == APP_ENDPOINT){
		if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
			switch(cmdId){
				case ZCL_CMD_CHK_IN_RSP:
					status = app_zclPollCtrlChkInRspCmdHandler((zcl_chkInRsp_t *)cmdPayload);
					break;
				case ZCL_CMD_FAST_POLL_STOP:
					status = app_zclPollCtrlFastPollStopCmdHandler();
					break;
				case ZCL_CMD_SET_LONG_POLL_INTERVAL:
					status = app_zclPollCtrlSetLongPollIntervalCmdHandler((zcl_setLongPollInterval_t *)cmdPayload);
					break;
				case ZCL_CMD_SET_SHORT_POLL_INTERVAL:
					status = app_zclPollCtrlSetShortPollIntervalCmdHandler((zcl_setShortPollInterval_t *)cmdPayload);
					break;
				default:
					break;
			}
		}
	}

	return status;
}
#endif	/* ZCL_POLL_CTRL */

#ifdef ZCL_THERMOSTAT

status_t app_thermostatCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload) {

//    printf("app_thermostatCb(). pAddrInfo->dirCluster: %0x%x, cmdId: 0x%x\r\n", pAddrInfo->dirCluster, cmdId);

    uint16_t len;
    int16_t  setpoint;

    status_t status = ZCL_STA_SUCCESS;

    if(pAddrInfo->dstEp == APP_ENDPOINT1) {
        switch(cmdId) {
            case ZCL_CMD_THERMOSTAT_SETPOINT_RAISE_LOWER: {
#if UART_PRINTF_MODE
                printf("CMD Setpoint Raise Lower\r\n");
#endif
                return status;

                zcl_thermostat_setpointRaiseLowerCmd_t *cmd = (zcl_thermostat_setpointRaiseLowerCmd_t*)cmdPayload;
                if (cmd->mode == ADJUST_HEAT_SETPOINT) {
                    int8_t raise_lower = cmd->amount / 10;
                    if (raise_lower >= -5 && raise_lower <= 5) {
                        zcl_getAttrVal(APP_ENDPOINT1,
                                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                                       ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT,
                                       &len, (uint8_t*)&setpoint);

                        setpoint += raise_lower*100;

                        data_point_model[DP_IDX_SETPOINT].remote_cmd(&setpoint);
//                        printf("raise_lower: %d, setpoint: %d\r\n", raise_lower, setpoint);
                    }
                }
                break;
            }
            case ZCL_CMD_THERMOSTAT_SET_WEEKLY_SCHEDULE: {
#if UART_PRINTF_MODE
                printf("CMD Set Weekly Schedule\r\n");
#endif
                zcl_thermostat_setWeeklyScheduleCmd_t *cmd = (zcl_thermostat_setWeeklyScheduleCmd_t*)cmdPayload;

                heatMode_t *heat_mode;
                bool save = false;

                switch(manuf_name) {
                case MANUF_NAME_1:
                case MANUF_NAME_0A:
                case MANUF_NAME_0B:
#if UART_PRINTF_MODE
                        printf("Days other than Monday, Saturday and Sunday are not supported\r\n");
#endif
                        for (uint8_t i = 0; i < cmd->numOfTransForSequence; i++) {
                            if (i == 4) {
                                break;
                            }
                            if (cmd->dayOfWeekForSequence & DAY_SUN) {
                                heat_mode =  g_zcl_scheduleData.schedule_sun;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
                                save = true;
//                                printf("i: %d, weekday: sun, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_MON) {
                                heat_mode =  g_zcl_scheduleData.schedule_mon;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
                                save = true;
//                                printf("i: %d, weekday: mon, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_SAT) {
                                heat_mode =  g_zcl_scheduleData.schedule_sat;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
                                save = true;
//                                printf("i: %d, weekday: sat, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                        }

                        if (save) {
                            if (data_point_model[DP_IDX_SCHEDULE].remote_cmd)
                                data_point_model[DP_IDX_SCHEDULE].remote_cmd(&cmd->dayOfWeekForSequence);
                        }
                        break;
                    case MANUF_NAME_2:
                    case MANUF_NAME_3:
                    case MANUF_NAME_4:
                    case MANUF_NAME_5:
                    case MANUF_NAME_7:
                    case MANUF_NAME_9:
                    case MANUF_NAME_0C:
                        for (uint8_t i = 0; i < cmd->numOfTransForSequence; i++) {
                            if (i == 4) {
                                break;
                            }
                            if (cmd->dayOfWeekForSequence & DAY_SUN) {
                                heat_mode =  g_zcl_scheduleData.schedule_sun;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
//                                printf("i: %d, weekday: sun, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_MON) {
                                heat_mode =  g_zcl_scheduleData.schedule_mon;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
//                                printf("i: %d, weekday: mon, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_TUE) {
                                heat_mode =  g_zcl_scheduleData.schedule_tue;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
//                                printf("i: %d, weekday: tue, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_WED) {
                                heat_mode =  g_zcl_scheduleData.schedule_wed;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
//                                printf("i: %d, weekday: wed, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_THU) {
                                heat_mode =  g_zcl_scheduleData.schedule_thu;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
//                                printf("i: %d, weekday: thu, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_FRI) {
                                heat_mode =  g_zcl_scheduleData.schedule_fri;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
//                                printf("i: %d, weekday: fri, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_SAT) {
                                heat_mode =  g_zcl_scheduleData.schedule_sat;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
//                                printf("i: %d, weekday: sat, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                        }

                        if (data_point_model[DP_IDX_SCHEDULE].remote_cmd)
                            data_point_model[DP_IDX_SCHEDULE].remote_cmd(&cmd->dayOfWeekForSequence);

                        break;
                    case MANUF_NAME_6:
#if UART_PRINTF_MODE
                        printf("Days other than Monday and Sunday are not supported\r\n");
#endif
                        for (uint8_t i = 0; i < cmd->numOfTransForSequence; i++) {
                            if (i == 6) {
                                break;
                            }
                            if (cmd->dayOfWeekForSequence & DAY_SUN) {
                                heat_mode =  g_zcl_scheduleData.schedule_sun;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
                                save = true;
//                                printf("i: %d, weekday: sun, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_MON) {
                                heat_mode =  g_zcl_scheduleData.schedule_mon;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
                                save = true;
//                                printf("i: %d, weekday: mon, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                        }

                        if (save) {
                            if (data_point_model[DP_IDX_SCHEDULE].remote_cmd)
                                data_point_model[DP_IDX_SCHEDULE].remote_cmd(&cmd->dayOfWeekForSequence);
                        }
                        break;
                    case MANUF_NAME_8:
#if UART_PRINTF_MODE
                        printf("Days other than Monday, Saturday and Sunday are not supported\r\n");
#endif
                        for (uint8_t i = 0; i < cmd->numOfTransForSequence; i++) {
                            if (i == 6) {
                                break;
                            }
                            if (cmd->dayOfWeekForSequence & DAY_SUN) {
                                heat_mode =  g_zcl_scheduleData.schedule_sun;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
                                save = true;
//                                printf("i: %d, weekday: sun, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_MON) {
                                heat_mode =  g_zcl_scheduleData.schedule_mon;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
                                save = true;
//                                printf("i: %d, weekday: mon, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                            if (cmd->dayOfWeekForSequence & DAY_SAT) {
                                heat_mode =  g_zcl_scheduleData.schedule_sat;
                                heat_mode[i].transTime = cmd->sequenceMode.pHeatMode[i].transTime;
                                heat_mode[i].heatSetpoint = cmd->sequenceMode.pHeatMode[i].heatSetpoint;
                                save = true;
//                                printf("i: %d, weekday: sat, time: %d, temp: %d\r\n", i, heat_mode[i].transTime, heat_mode[i].heatSetpoint);
                            }
                        }

                        if (save) {
                            if (data_point_model[DP_IDX_SCHEDULE].remote_cmd)
                                data_point_model[DP_IDX_SCHEDULE].remote_cmd(&cmd->dayOfWeekForSequence);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }
            case ZCL_CMD_THERMOSTAT_GET_WEEKLY_SCHEDULE:
#if UART_PRINTF_MODE
                printf("CMD Get Weekly Schedule\r\n");
#endif
                answer_weekly_schedule[manuf_name](&pAddrInfo->seqNum);

                break;
            case ZCL_CMD_THERMOSTAT_CLEAR_WEEKLY_SCHEDULE:
#if UART_PRINTF_MODE
                printf("CMD Clear Weekly Schedule\r\n");
#endif
                break;
            default:
                break;
        }
    }


    return status;
}

status_t app_thermostat_uicCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload) {

//    printf("app_thermostatCb(). pAddrInfo->dirCluster: %0x%x, cmdId: 0x%x\r\n", pAddrInfo->dirCluster, cmdId);

//    uint8_t *cmdData = (uint8_t*)cmdPayload;

    status_t status = ZCL_STA_SUCCESS;

//    if(pAddrInfo->dstEp == APP_ENDPOINT1) {
//        switch(cmdId) {
//            case ZCL_CMD_UP_OPEN:
//                printf("CMD Open\r\n");
//                remote_cmd_ocs(pAddrInfo->dstEp, cmdId);
//                break;
//            case ZCL_CMD_DOWN_CLOSE:
//                printf("CMD Close\r\n");
//                remote_cmd_ocs(pAddrInfo->dstEp, cmdId);
//                break;
//            case ZCL_CMD_STOP:
//                printf("CMD Stop\r\n");
//                remote_cmd_ocs(pAddrInfo->dstEp, cmdId);
//                break;
//            case ZCL_CMD_GO_TO_LIFT_PERCENTAGE:
//                printf("CMD go to lift percentage. Payload: 0x%x\r\n", *cmdData);
//                if (*cmdData <= 100) remote_cmd_goToLiftPer(pAddrInfo->dstEp, *cmdData);
//                else status = ZCL_STA_INVALID_VALUE;
//                break;
//            default:
//                break;
//        }
//    }


    return status;
}

#endif /* ZCL_THERMOSTAT */

#ifdef ZCL_FANCONTROL

status_t app_fancontrolCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload) {

//    printf("app_thermostatCb().\r\n");

    status_t status = ZCL_STA_SUCCESS;

    return status;
}

#endif /* ZCL_FANCONTROL */

/*********************************************************************
 * @fn      app_timeCb
 *
 * @brief   Handler for ZCL Time command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t app_timeCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload) {

//    printf("app_timeCb. cmd: 0x%x\r\n", cmdId);

    return ZCL_STA_SUCCESS;
}


/*********************************************************************
 * @fn      app_displayMoveToLevelProcess
 *
 * @brief
 *
 * @param   cmdId
 * @param   cmd
 *
 * @return  None
 */

static void app_displayMoveToLevelProcess(uint8_t endpoint, uint8_t cmdId, moveToLvl_t *cmd) {

    if (endpoint == APP_ENDPOINT1) {
        if (data_point_model[DP_IDX_LEVEL_A].remote_cmd)
            data_point_model[DP_IDX_LEVEL_A].remote_cmd(&cmd->level);
    } else if (endpoint == APP_ENDPOINT2) {
        if (data_point_model[DP_IDX_LEVEL_B].remote_cmd)
            data_point_model[DP_IDX_LEVEL_B].remote_cmd(&cmd->level);
    }
}


/*********************************************************************
 * @fn      app_displaylevelCb
 *
 * @brief   Handler for ZCL LEVEL command. This function will set LEVEL attribute first.
 *
 * @param   pAddrInfo
 * @param   cmd - level cluster command id
 * @param   cmdPayload
 *
 * @return  status_t
 */

status_t app_displayLevelCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload) {
    if(pAddrInfo->dstEp == APP_ENDPOINT1 || pAddrInfo->dstEp == APP_ENDPOINT2) {
        switch(cmdId){
            case ZCL_CMD_LEVEL_MOVE_TO_LEVEL:
                app_displayMoveToLevelProcess(pAddrInfo->dstEp, cmdId, (moveToLvl_t *)cmdPayload);
                break;
            default:
                break;
        }
    }

    return ZCL_STA_SUCCESS;
}

/*********************************************************************
 * @fn      app_humidityCb
 *
 * @brief   Handler for ZCL Humidity command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t app_humidityCb(zclIncomingAddrInfo_t *pAddrInfo, uint8_t cmdId, void *cmdPayload) {

//    printf("app_humidityCb. cmd: 0x%x\r\n", cmdId);

    return ZCL_STA_SUCCESS;
}


