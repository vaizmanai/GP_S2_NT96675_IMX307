
#include "UIFramework.h"
#include "UIFrameworkExt.h"
#include "UIFlow.h"
#include "JpgEnc.h"
#include "Exif.h"
#include "Utility.h"
#include "Audio.h"
#include "rtc.h"
//#include "PhotoTsk.h"

static CHAR    g_RecMaxTimeStr[20] = {0};
static UINT32  g_RecMaxTime=0;
static CHAR    g_RecCurrTimeStr[20] = {0};
static UINT32  g_RecCurrTime=0;
static CHAR    date_str[20] = {0};
static CHAR    time_str[20] = {0};

//MOVIE_SIZE_TAG
static CHAR    wifiresolution_Buf[MOVIE_SIZE_ID_MAX][30]=
{
   "UHD P24", 
   "QHD P30",
   "MHD P30",
   "FHD P96",
   "FHD P60",
   "FHD P30",
   "HD P120",
   "HD P60",
   "HD P30",
   "WVGA P30"
};
/*static  CHAR wifiphotoresolution_Buf[PHOTO_SIZE_ID_MAX][20] =
{
    "12M",
    "10M",
    "8M",
    "5M",
    "3M",
    "VGA",
    //"2MHD",
    //"1.3M",
};*/


void FlowMovieWifi_IconDrawCamera(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, TRUE);
}


void FlowMovieWifi_IconHideCamera(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}


void FlowMovieWifi_IconDrawDSCMode(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, TRUE);
}


void FlowMovieWifi_IconHideDSCMode(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}


void FlowMovieWifi_IconDrawPlayMode(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, TRUE);
}


void FlowMovieWifi_IconHidePlayMode(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}


void FlowWiFiMovie_IconDrawWiFiLinkStatus(VControl *pCtrl)
{
	 /* Update status item data */
	if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
	{
		  UxState_SetData(pCtrl,STATE_CURITEM,UIMenuWndWiFiMobileLinkOK_StatusWIFILink_ICON_WIFI_CONNECTED);	
	}
	else
	{
		UxState_SetData(pCtrl,STATE_CURITEM,UIMenuWndWiFiMobileLinkOK_StatusWIFILink_ICON_WIFI_DOT_CONNECTING_OFF);	
	}
      UxCtrl_SetShow(pCtrl, TRUE);
}



void FlowMovieWifi_IconDrawMaxRecTime(VControl *pCtrl)
{
    memset((void *)g_RecMaxTimeStr, 0, sizeof(g_RecMaxTimeStr));
    g_RecMaxTime = MovieExe_GetMaxRecSec();

    if (g_RecMaxTime <= 2)
    {
        FlowMovie_SetRecMaxTime(0);
    }
    else if (g_RecMaxTime > 86399)
    {   ///23:59:59
        FlowMovie_SetRecMaxTime(86399);
    }
    else
    {
        FlowMovie_SetRecMaxTime(g_RecMaxTime);
    }

    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED)
    {
        sprintf(g_RecMaxTimeStr,"%02d:%02d:%02d", 0, 0, 0);
    }
    else
    {
        sprintf(g_RecMaxTimeStr,"%02d:%02d:%02d", g_RecMaxTime/3600,(g_RecMaxTime%3600)/60, (g_RecMaxTime%3600)%60);
    }

    UxStatic_SetData(pCtrl,STATIC_VALUE,Txt_Pointer(g_RecMaxTimeStr));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovieWifi_IconHideMaxRecTime(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}


void FlowMovieWifi_IconHideRecTime(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}


void FlowMovieWifi_IconHideLock(VControl *pCtrl)
{
	UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovieWifi_IconDrawRecTime(VControl *pCtrl)
{
	switch (WiFiCmd_GetStatus())
      {
        case WIFI_MOV_ST_RECORD:
        g_RecCurrTime = FlowMovie_GetRecCurrTime();
        memset((void *)g_RecCurrTimeStr, 0, sizeof(g_RecCurrTimeStr));
        sprintf(g_RecCurrTimeStr,"%02d:%02d:%02d", g_RecCurrTime/3600,(g_RecCurrTime%3600)/60, (g_RecCurrTime%3600)%60);
        UxStatic_SetData(pCtrl,STATIC_VALUE,Txt_Pointer(g_RecCurrTimeStr));
        UxCtrl_SetShow(pCtrl, TRUE);
        break;
    }
}

void FlowMovieWifi_IconDrawDateTime(void)
{
 RTC_DATE    Date;
 RTC_TIME    Time;

    // display Date/Time string in movie mode
    Date = rtc_getDate();
    Time = rtc_getTime();
    sprintf(date_str,"%04d/%02d/%02d",Date.s.year,Date.s.month,Date.s.day);
    sprintf(time_str,"%02d:%02d:%02d",Time.s.hour,Time.s.minute,Time.s.second);
    UxStatic_SetData(&UIMenuWndWiFiMobileLinkOK_YMD_StaticCtrl,STATIC_VALUE,Txt_Pointer(date_str));
    UxStatic_SetData(&UIMenuWndWiFiMobileLinkOK_HMS_StaticCtrl,STATIC_VALUE,Txt_Pointer(time_str));
    UxCtrl_SetShow(&UIMenuWndWiFiMobileLinkOK_YMD_StaticCtrl,TRUE);
    UxCtrl_SetShow(&UIMenuWndWiFiMobileLinkOK_HMS_StaticCtrl,TRUE);
}

void FlowMovieWifi_IconHideDateTime(void)
{
    UxCtrl_SetShow(&UIMenuWndWiFiMobileLinkOK_YMD_StaticCtrl,FALSE);
    UxCtrl_SetShow(&UIMenuWndWiFiMobileLinkOK_HMS_StaticCtrl,FALSE);
}

void FlowMovieWifi_IconDrawRec(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,TRUE);
}

void FlowMovieWifi_IconHideRec(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,FALSE);
}

void FlowMovieWifi_IconDrawSize(VControl *pCtrl)
{

	UxCtrl_SetShow(pCtrl, FALSE);
	//debug_msg("<------------------System_GetState(SYS_STATE_CURRMODE):%d-----SysGetFlag(FL_PHOTO_SIZE) is %d--------->\r\n",System_GetState(SYS_STATE_CURRMODE),SysGetFlag(FL_PHOTO_SIZE));

	// if(System_GetState(SYS_STATE_CURRMODE)==1)
	// 	UxStatic_SetData(pCtrl,STATIC_VALUE,Txt_Pointer(wifiphotoresolution_Buf[SysGetFlag(FL_PHOTO_SIZE)]));
	// else if(System_GetState(SYS_STATE_CURRMODE)==2)
	    UxStatic_SetData(pCtrl,STATIC_VALUE,Txt_Pointer(wifiresolution_Buf[SysGetFlag(FL_MOVIE_SIZE)]));
	// else 
	// 	return;
	 	
	//debug_msg("<------------------DrawSize:%d-------------->\r\n",SysGetFlag(FL_MOVIE_SIZE));
	//debug_msg("<------------------DrawSize:%s-------------->\r\n",wifiresolution_Buf[SysGetFlag(FL_MOVIE_SIZE)]);
	UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovieWifi_IconHideSize(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovieWifi_IconDrawEV(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_EV));
    UxCtrl_SetShow(pCtrl,TRUE);
}

void FlowMovieWifi_IconHideEV(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,FALSE);
}

void FlowMovieWifi_IconDrawStorage(VControl *pCtrl)
{
    /* Update status item data */
    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED)
    {
        UxState_SetData(pCtrl,STATE_CURITEM,UIMenuWndWiFiMobileLinkOK_Status_Storage_ICON_INTERNAL_FLASH);
    } else if (System_GetState(SYS_STATE_CARD) == CARD_LOCKED) {
        UxState_SetData(pCtrl,STATE_CURITEM,UIMenuWndWiFiMobileLinkOK_Status_Storage_ICON_SD_LOCK);
    } else {
        UxState_SetData(pCtrl,STATE_CURITEM,UIMenuWndWiFiMobileLinkOK_Status_Storage_ICON_SD_CARD);
    }

    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovieWifi_IconHideStorage(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovieWifi_IconDrawCyclicRec(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_MOVIE_CYCLIC_REC));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovieWifi_IconHideCyclicRec(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovieWifi_IconDrawHDR(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_MOVIE_HDR));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovieWifi_IconHideHDR(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}

void FlowMovieWifi_IconDrawWDR(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_MOVIE_WDR));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowMovieWifi_IconHideWDR(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}


void FlowMovieWifi_IconDrawBattery(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,GetBatteryLevel());
    UxCtrl_SetShow(pCtrl,TRUE);
}

void FlowMovieWifi_IconHideBattery(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl,FALSE);
}

void FlowPhotoWifi_IconDrawSize(VControl *pCtrl)
{
    //debug_msg("in FlowPhotoWifi_IconDrawSize,Get_SizeString(SysGetFlag(FL_PHOTO_SIZE)) = %s  \r\n",Get_SizeString(SysGetFlag(FL_PHOTO_SIZE)));
    UxStatic_SetData(pCtrl,STATIC_VALUE,Txt_Pointer(Get_SizeString(SysGetFlag(FL_PHOTO_SIZE))));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowPhotoWifi_IconHideSize(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}


static UINT32  g_uiFreePicNum=0;

void FlowPhotoWifi_IconDrawFreePicNumber(VControl *pCtrl)
{
    UIStorageCheck(STORAGE_CHECK_FULL, &g_uiFreePicNum);
    UxStatic_SetData(pCtrl,STATIC_VALUE,Txt_Pointer(Get_FreePicNumString(g_uiFreePicNum)));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowPhotoWifi_IconHideFreePicNumber(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}



void FlowPhotoWifi_IconDrawQuality(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_QUALITY));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowPhotoWifi_IconHideQuality(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}



void FlowPhotoWifi_IconDrawWB(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_WB));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowPhotoWifi_IconHideWB(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}


void FlowPhotoWifi_IconDrawISO(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_ISO));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowPhotoWifi_IconHideISO(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}



void FlowPhotoWifi_IconDrawSelftimer(VControl *pCtrl)
{
    UxState_SetData(pCtrl,STATE_CURITEM,SysGetFlag(FL_SELFTIMER));
    UxCtrl_SetShow(pCtrl, TRUE);
}

void FlowPhotoWifi_IconHideSelftimer(VControl *pCtrl)
{
    UxCtrl_SetShow(pCtrl, FALSE);
}


void UIMenuWndWiFiMobileLinkOK_UpdateMoiveIcons(BOOL bShow,BOOL ModeCtrl)
{
    if (bShow)
    {
    		if(ModeCtrl == TRUE)
    		{
    			FlowMovieWifi_IconDrawCamera(&UIMenuWndWiFiMobileLinkOK_Static_cameraCtrl);
    			FlowWiFiMovie_IconDrawWiFiLinkStatus(&UIMenuWndWiFiMobileLinkOK_StatusWIFILinkCtrl);
			FlowMovieWifi_IconHideRec(&UIMenuWndWiFiMobileLinkOK_PanelCtrl);
			FlowMovieWifi_IconDrawStorage(&UIMenuWndWiFiMobileLinkOK_Status_StorageCtrl);
			FlowMovieWifi_IconDrawSize(&UIMenuWndWiFiMobileLinkOK_Static_resolutionCtrl);
			FlowMovieWifi_IconDrawCyclicRec(&UIMenuWndWiFiMobileLinkOK_Status_CyclicRecCtrl);
			FlowMovieWifi_IconDrawBattery(&UIMenuWndWiFiMobileLinkOK_Status_batteryCtrl);
		       FlowMovieWifi_IconDrawEV(&UIMenuWndWiFiMobileLinkOK_StatusICN_EVCtrl);
			FlowMovieWifi_IconHideMaxRecTime(&UIMenuWndWiFiMobileLinkOK_Static_maxtimeCtrl);  
			FlowMovieWifi_IconHideRecTime(&UIMenuWndWiFiMobileLinkOK_Static_timeCtrl);  
			FlowMovieWifi_IconHideLock(&UIMenuWndWiFiMobileLinkOK__StaticICN_ProtectCtrl);  
			FlowMovieWifi_IconHidePlayMode(&UIMenuWndWiFiMobileLinkOK_StaticI_PlayModeCtrl);
		      FlowMovieWifi_IconDrawDateTime();
    		}
		else if(ModeCtrl == FALSE)
		{
			FlowWiFiMovie_IconDrawWiFiLinkStatus(&UIMenuWndWiFiMobileLinkOK_StatusWIFILinkCtrl);
			FlowMovieWifi_IconDrawStorage(&UIMenuWndWiFiMobileLinkOK_Status_StorageCtrl);
			FlowMovieWifi_IconDrawSize(&UIMenuWndWiFiMobileLinkOK_Static_resolutionCtrl);
			FlowMovieWifi_IconDrawCyclicRec(&UIMenuWndWiFiMobileLinkOK_Status_CyclicRecCtrl);
			FlowMovieWifi_IconDrawBattery(&UIMenuWndWiFiMobileLinkOK_Status_batteryCtrl);
		      FlowMovieWifi_IconDrawEV(&UIMenuWndWiFiMobileLinkOK_StatusICN_EVCtrl);
		}
		
	      //FlowWiFiMovie_IconDrawDscMode(&UIMenuWndWiFiMobileLinkOK_Statas_ModeCtrl);
            //FlowMovieWifi_IconDrawMaxRecTime(&UIMenuWndWiFiMobileLinkOK_Static_maxtimeCtrl);
            //FlowMovie_IconDrawHDR(&UIMenuWndWiFiMobileLinkOK_Status_HDRCtrl);
            // FlowMovieWifi_IconDrawMotionDet(&UIMenuWndWiFiMobileLinkOK_Status_MotionDetCtrl);


           //FlowMovieWifi_DrawPIM(FALSE);
	    //	FlowMovieWifi_IconDrawAudioOnOff();
    }
    else
    {
    	  FlowMovieWifi_IconHideCamera(&UIMenuWndWiFiMobileLinkOK_Static_cameraCtrl);
    	  FlowWiFiMovie_IconDrawWiFiLinkStatus(&UIMenuWndWiFiMobileLinkOK_StatusWIFILinkCtrl);
	  //FlowWiFiMovie_IconHideDscMode(&UIMenuWndWiFiMobileLinkOK_Statas_ModeCtrl);
        //FlowMovieWifi_IconDrawMaxRecTime(&UIMenuWndWiFiMobileLinkOK_Static_maxtimeCtrl);
        FlowMovieWifi_IconHideRec(&UIMenuWndWiFiMobileLinkOK_PanelCtrl);
        FlowMovieWifi_IconDrawStorage(&UIMenuWndWiFiMobileLinkOK_Status_StorageCtrl);
	  FlowMovieWifi_IconHideSize(&UIMenuWndWiFiMobileLinkOK_Static_resolutionCtrl);
	  FlowMovieWifi_IconHideLock(&UIMenuWndWiFiMobileLinkOK__StaticICN_ProtectCtrl);  
        FlowMovieWifi_IconHideCyclicRec(&UIMenuWndWiFiMobileLinkOK_Status_CyclicRecCtrl);
        //FlowMovie_IconDrawHDR(&UIMenuWndWiFiMobileLinkOK_Status_HDRCtrl);
        //FlowMovieWifi_IconHideMotionDet(&UIMenuWndWiFiMobileLinkOK_Status_MotionDetCtrl);
        FlowMovieWifi_IconDrawBattery(&UIMenuWndWiFiMobileLinkOK_Status_batteryCtrl);
        FlowMovieWifi_IconDrawEV(&UIMenuWndWiFiMobileLinkOK_StatusICN_EVCtrl);
	  FlowMovieWifi_IconHideMaxRecTime(&UIMenuWndWiFiMobileLinkOK_Static_maxtimeCtrl);  
        FlowMovieWifi_IconHideDateTime();
       // FlowMovieWifi_DrawPIM(FALSE);
	//	FlowMovieWifi_IconDrawAudioOnOff();
    }
}



#if 1
void UIMenuWndWiFiMobileLinkOK_UpdatePhotoIcons(BOOL bShow)
{
    if (bShow)
    {
    		FlowMovieWifi_IconDrawDSCMode(&UIMenuWndWiFiMobileLinkOK_StaticICN_DSCModeCtrl);
    	  	FlowWiFiMovie_IconDrawWiFiLinkStatus(&UIMenuWndWiFiMobileLinkOK_StatusWIFILinkCtrl);
   		FlowPhotoWifi_IconDrawSize(&UIMenuWndWiFiMobileLinkOK_StaticTXT_SizeCtrl);
    		FlowPhotoWifi_IconDrawQuality(&UIMenuWndWiFiMobileLinkOK_StatusICN_QualityCtrl);
    		FlowPhotoWifi_IconDrawFreePicNumber(&UIMenuWndWiFiMobileLinkOK_StaticTXT_FreePicCtrl);
		FlowPhotoWifi_IconDrawISO(&UIMenuWndWiFiMobileLinkOK_StatusICN_ISOCtrl);
		FlowPhotoWifi_IconDrawWB(&UIMenuWndWiFiMobileLinkOK__StatusICN_WBCtrl);
		FlowPhotoWifi_IconDrawSelftimer(&UIMenuWndWiFiMobileLinkOK_StatusICN_SelftimerCtrl);
	 	FlowMovieWifi_IconDrawStorage(&UIMenuWndWiFiMobileLinkOK_Status_StorageCtrl);
	  	FlowMovieWifi_IconDrawBattery(&UIMenuWndWiFiMobileLinkOK_Status_batteryCtrl);
        	FlowMovieWifi_IconDrawEV(&UIMenuWndWiFiMobileLinkOK_StatusICN_EVCtrl);
        	//FlowMovieWifi_IconDrawDateTime();
        	FlowMovieWifi_IconHidePlayMode(&UIMenuWndWiFiMobileLinkOK_StaticI_PlayModeCtrl);
		
    }
    else
    {
        	FlowMovieWifi_IconHideDSCMode(&UIMenuWndWiFiMobileLinkOK_StaticICN_DSCModeCtrl);
	 	FlowPhotoWifi_IconHideSize(&UIMenuWndWiFiMobileLinkOK_StaticTXT_SizeCtrl);
     	 	FlowPhotoWifi_IconHideQuality(&UIMenuWndWiFiMobileLinkOK_StatusICN_QualityCtrl);
    	 	FlowPhotoWifi_IconHideFreePicNumber(&UIMenuWndWiFiMobileLinkOK_StaticTXT_FreePicCtrl);
	 	FlowPhotoWifi_IconHideISO(&UIMenuWndWiFiMobileLinkOK_StatusICN_ISOCtrl);
	 	FlowPhotoWifi_IconHideWB(&UIMenuWndWiFiMobileLinkOK__StatusICN_WBCtrl);
		FlowPhotoWifi_IconHideSelftimer(&UIMenuWndWiFiMobileLinkOK_StatusICN_SelftimerCtrl);
    }
}
#endif





