/*
    System Input Callback

    System Callback for Input Module.

    @file       SysInput_Exe.c
    @ingroup    mIPRJSYS

    @note

    Copyright   Novatek Microelectronics Corp. 2010.  All rights reserved.
*/

////////////////////////////////////////////////////////////////////////////////
#include "SysCommon.h"
#include "AppCommon.h"
////////////////////////////////////////////////////////////////////////////////
#include "UIFrameworkExt.h"
#include "UICommon.h"
#include "AppLib.h"
#include "GxInput.h"
#include "GxPower.h"
#include "UIFlowMovieFuncs.h"
#include "ImageUnit_AudIn.h"
#include "gpio.h"
#include "SDMMC.h"

#if (IPCAM_FUNC != ENABLE)
#include "SoundData.h"
#endif
#if (GSENSOR_FUNCTION == ENABLE)
#include "GSensor.h"
#endif
//global debug level: PRJ_DBG_LVL
#include "PrjCfg.h"
//local debug level: THIS_DBGLVL
#define THIS_DBGLVL         2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          SysInputExe
#define __DBGLVL__          ((THIS_DBGLVL>=PRJ_DBG_LVL)?THIS_DBGLVL:PRJ_DBG_LVL)
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include "DebugModule.h"
///////////////////////////////////////////////////////////////////////////////

#include "SysInput_API.h"

#include "CommunicateToMCU.h"

//#NT#Refine code for continue key
#define    BURSTKEY_DEBOUNCE     800//ms
#define    BURSTKEY_INTERVAL     200//ms
#define TOUCH_TIMER_CNT            1//20ms
#define    DOUBLECLICK_INTERVAL     500//ms

BOOL RecvCMD_WIFI_OFF=FALSE;
BOOL FormatByMCU = TRUE;
BOOL MCUSendAT_SOS = FALSE;
BOOL SetCrash_Flag = FALSE;
BOOL WIFI_LinkOK_Flag = FALSE;
BOOL Wifi_ON_OFF_Flag = FALSE;
BOOL RecMIC_ChangeCMD = FALSE;
BOOL RecRate_ChangeCMD = FALSE;
BOOL CurrentRateBeforWIFI_onFlag = FALSE;
static BOOL MCUSendPoweroff = FALSE;
int SX_TIMER_DET_KEY_ID = -1;
int SX_TIMER_DET_TOUCH_ID = -1;
int SX_TIMER_DET_PWR_ID = -1;
int SX_TIMER_DET_MODE_ID = -1;
int SX_TIMER_AUTO_INPUT_ID = -1;
int SX_TIMER_DET_GSENSOR_ID = -1;

int SX_TIMER_DET_MCUCMD_ID=-1;

int SX_TIMER_OneSecond_ID=-1;

void UI_DetPwrKey(void);
void UI_DetNormalKey(void);
void UI_DetStatusKey(void);
void UI_DetCustom1Key(void);
void UI_OneSecond(void);

void UI_DetMCUCMD(void);

extern MOV_TASK_DATA   gMovData;

extern BOOL UIFlowWndMovie_OnStorageSlow_evenFlag;

extern void ModeMovie_Open(void);
extern void ModeMovie_Close(void);

extern UINT32          g_TVEnable; //not yet enable
extern void DrvTV_TurnOn(void);
extern void DrvTV_TurnOff(void);

#if (POWERKEY_FUNCTION == ENABLE)
SX_TIMER_ITEM(Input_DetPKey, UI_DetPwrKey, 5, FALSE)
#endif
#if (NORMALKEY_FUNCTION == ENABLE)
SX_TIMER_ITEM(Input_DetNKey, UI_DetNormalKey, 1, FALSE)
#endif
#if (STATUSKEY_FUNCTION == ENABLE)
SX_TIMER_ITEM(Input_DetSKey, UI_DetStatusKey, 7, FALSE)
#endif
#if (GSENSOR_FUNCTION == ENABLE)
SX_TIMER_ITEM(Input_DetC1Key, UI_DetCustom1Key, 3, FALSE)
#endif
#if defined(_TOUCH_ON_)
SX_TIMER_ITEM(Input_DetTP, GxTouch_DetTP, TOUCH_TIMER_CNT, FALSE)
#endif

SX_TIMER_ITEM(Input_DetMCUCMD, UI_DetMCUCMD, 1, FALSE)

SX_TIMER_ITEM(Input_OneSecond, UI_OneSecond, 25, FALSE)

static BOOL         m_uiAnyKeyUnlockEn        = FALSE;


#if defined(_TOUCH_ON_)
static TOUCH_OBJ g_TouchTable[] = {
	{TP_GESTURE_PRESS,         NVTEVT_PRESS,        DEMOSOUND_SOUND_KEY_TONE},
	{TP_GESTURE_MOVE,          NVTEVT_MOVE,         0},
	{TP_GESTURE_HOLD,          NVTEVT_HOLD,         0},
	{TP_GESTURE_RELEASE,       NVTEVT_RELEASE,      DEMOSOUND_SOUND_KEY_TONE},
	{TP_GESTURE_CLICK,         NVTEVT_CLICK,        0},
	{TP_GESTURE_SLIDE_LEFT,    NVTEVT_SLIDE_LEFT,   0},
	{TP_GESTURE_SLIDE_RIGHT,   NVTEVT_SLIDE_RIGHT,  0},
	{TP_GESTURE_SLIDE_UP,      NVTEVT_SLIDE_UP,     0},
	{TP_GESTURE_SLIDE_DOWN,    NVTEVT_SLIDE_DOWN,   0}
};
#endif

#if defined(_KEY_METHOD_4KEY_)
static KEY_OBJ g_KeyTable[] = {
#if defined(_UI_STYLE_CARDV_)
	//POWER KEY
	{FLGKEY_KEY_POWER,    KEY_PRESS,       NVTEVT_KEY_POWER_REL,    0,                      0},
	//NORMAL KEY
	{FLGKEY_MENU,         KEY_PRESS,       NVTEVT_KEY_MENU,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_MODE,         KEY_RELEASE,     NVTEVT_KEY_MODE,         NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_UP,           KEY_PRESS,       NVTEVT_KEY_UP,           NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_UP,           KEY_CONTINUE,    NVTEVT_KEY_UP,           NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_UP,           KEY_RELEASE,     NVTEVT_KEY_UP,           NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_DOWN,         KEY_PRESS,       NVTEVT_KEY_DOWN,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_DOWN,         KEY_CONTINUE,    NVTEVT_KEY_DOWN,         NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_DOWN,         KEY_RELEASE,     NVTEVT_KEY_DOWN,         NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_SHUTTER2,     KEY_PRESS,       NVTEVT_KEY_SHUTTER2,     NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_SHUTTER2,     KEY_RELEASE,     NVTEVT_KEY_SHUTTER2,     NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_ENTER,        KEY_PRESS,       NVTEVT_KEY_ENTER,        NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_ENTER,        KEY_RELEASE,     NVTEVT_KEY_ENTER,        NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_CUSTOM1,      KEY_PRESS,       NVTEVT_KEY_CUSTOM1,      NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_NONE},
	{FLGKEY_CUSTOM1,      KEY_RELEASE,     NVTEVT_KEY_CUSTOM1,      NVTEVT_KEY_RELEASE,     0},
#else// _UI_STYLE_SPORTCAM_
	//POWER KEY
	#if (POWER_KEY_LONG_PRESS == ENABLE)
	{FLGKEY_KEY_POWER,    KEY_PRESS,       NVTEVT_KEY_POWER,        0,                      0},
	{FLGKEY_KEY_POWER,    KEY_CONTINUE,    NVTEVT_KEY_POWER_CONT,   0,                      0},
	#endif
	{FLGKEY_KEY_POWER,    KEY_RELEASE,     NVTEVT_KEY_POWER_REL,    0,                      0},
	//NORMAL KEY
	{FLGKEY_UP,           KEY_PRESS,       NVTEVT_KEY_PREV,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_UP,           KEY_CONTINUE,    NVTEVT_KEY_PREV,         NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_UP,           KEY_RELEASE,     NVTEVT_KEY_PREV,         NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_DOWN,         KEY_PRESS,       NVTEVT_KEY_NEXT,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_DOWN,         KEY_CONTINUE,    NVTEVT_KEY_NEXT,         NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_DOWN,         KEY_RELEASE,     NVTEVT_KEY_NEXT,         NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_LEFT,         KEY_PRESS,       NVTEVT_KEY_MOVIE,        NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	//{FLGKEY_LEFT,         KEY_CONTINUE,    NVTEVT_KEY_PREV,         NVTEVT_KEY_CONTINUE,    0},
	//{FLGKEY_LEFT,         KEY_RELEASE,     NVTEVT_KEY_PREV,         NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_SHUTTER2,     KEY_PRESS,       NVTEVT_KEY_SHUTTER2,     NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_SHUTTER2,     KEY_RELEASE,     NVTEVT_KEY_SHUTTER2,     NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_RIGHT,        KEY_PRESS,       NVTEVT_KEY_SELECT,       NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_RIGHT,        KEY_CONTINUE,    NVTEVT_KEY_SELECT,       NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_RIGHT,        KEY_RELEASE,     NVTEVT_KEY_SELECT,       NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_CUSTOM1,      KEY_PRESS,       NVTEVT_KEY_CUSTOM1,      NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_NONE},
	{FLGKEY_CUSTOM1,      KEY_RELEASE,     NVTEVT_KEY_CUSTOM1,      NVTEVT_KEY_RELEASE,     0},

#endif
};
#else
//_KEY_METHOD_2KEY_ (for SPORTCAM only)
static KEY_OBJ g_KeyTable[] = {
	//POWER KEY
	{FLGKEY_KEY_POWER,    KEY_RELEASE,     NVTEVT_KEY_POWER_REL,    0,                      0},
	//NORMAL KEY
	{FLGKEY_ENTER,        KEY_PRESS,       NVTEVT_KEY_ENTER,        NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_MENU,         KEY_PRESS,       NVTEVT_KEY_MENU,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_MODE,         KEY_PRESS,       NVTEVT_KEY_MODE,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_PLAYBACK,     KEY_PRESS,       NVTEVT_KEY_PLAYBACK,     NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_UP,           KEY_PRESS,       NVTEVT_KEY_UP,           NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_UP,           KEY_CONTINUE,    NVTEVT_KEY_UP,           NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_UP,           KEY_RELEASE,     NVTEVT_KEY_UP,           NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_DOWN,         KEY_PRESS,       NVTEVT_KEY_DOWN,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_DOWN,         KEY_CONTINUE,    NVTEVT_KEY_DOWN,         NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_DOWN,         KEY_RELEASE,     NVTEVT_KEY_DOWN,         NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_LEFT,         KEY_PRESS,       NVTEVT_KEY_SELECT,       NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_LEFT,         KEY_CONTINUE,    NVTEVT_KEY_SELECT,       NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_LEFT,         KEY_RELEASE,     NVTEVT_KEY_SELECT,       NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_RIGHT,        KEY_PRESS,       NVTEVT_KEY_NEXT,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_RIGHT,        KEY_CONTINUE,    NVTEVT_KEY_NEXT,         NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_RIGHT,        KEY_RELEASE,     NVTEVT_KEY_NEXT,         NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_DOWN,         KEY_PRESS,       NVTEVT_KEY_DOWN,         NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_DOWN,         KEY_CONTINUE,    NVTEVT_KEY_DOWN,         NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_DOWN,         KEY_RELEASE,     NVTEVT_KEY_DOWN,         NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_ZOOMIN,       KEY_PRESS,       NVTEVT_KEY_ZOOMIN,       NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_ZOOMIN,       KEY_CONTINUE,    NVTEVT_KEY_ZOOMIN,       NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_ZOOMIN,       KEY_RELEASE,     NVTEVT_KEY_ZOOMIN,       NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_ZOOMOUT,      KEY_PRESS,       NVTEVT_KEY_ZOOMOUT,      NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_ZOOMOUT,      KEY_CONTINUE,    NVTEVT_KEY_ZOOMOUT,      NVTEVT_KEY_CONTINUE,    0},
	{FLGKEY_ZOOMOUT,      KEY_RELEASE,     NVTEVT_KEY_ZOOMOUT,      NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_SHUTTER2,     KEY_PRESS,       NVTEVT_KEY_SHUTTER2,     NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_SHUTTER2,     KEY_RELEASE,     NVTEVT_KEY_SHUTTER2,     NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_SHUTTER1,     KEY_PRESS,       NVTEVT_KEY_SHUTTER1,     NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_KEY_TONE},
	{FLGKEY_SHUTTER1,     KEY_RELEASE,     NVTEVT_KEY_SHUTTER1,     NVTEVT_KEY_RELEASE,     0},
	{FLGKEY_CUSTOM1,      KEY_PRESS,       NVTEVT_KEY_CUSTOM1,      NVTEVT_KEY_PRESS,       DEMOSOUND_SOUND_NONE},
	{FLGKEY_CUSTOM1,      KEY_RELEASE,     NVTEVT_KEY_CUSTOM1,      NVTEVT_KEY_RELEASE,     0},
};
#endif
void KeySoundCB(UINT32 uiSoundID)
{
	if (uiSoundID) {
#if(UI_FUNC==ENABLE)
		UISound_Play(uiSoundID);
#endif
	}
}

UINT32 Input_GroupStatus2Event(UINT32 status)
{
	UINT32 i = 0;
	for (i = 0; i < sizeof(g_KeyTable) / sizeof(KEY_OBJ); i++) {
		if ((g_KeyTable[i].uiKeyFlag == STATUS_KEY_GROUP1) && (g_KeyTable[i].status == status)) {
			return g_KeyTable[i].uiKeyEvent;
		}
	}
	return 0;
}

/**
  convert GPIO key to UI key event
  [InputCB internal API]

  @param UINT32 keys: Input key code detected from GPIO mapping
  @return UINT32: NVTEVT
**/
#if 0
static UINT32 Input_Key2Evt(UINT32 keys)
{
	if (keys & FLGKEY_MOVIE) {
		return NVTEVT_KEY_MOVIE;
	}
	if (keys & FLGKEY_I) {
		return NVTEVT_KEY_I;
	}
	if (keys & FLGKEY_MODE) {
		return NVTEVT_KEY_MODE;
	}
	if (keys & FLGKEY_PLAYBACK) {
		return NVTEVT_KEY_PLAYBACK;
	}
	if (keys & FLGKEY_MENU) {
		return NVTEVT_KEY_MENU;
	}
	if (keys & FLGKEY_FACEDETECT) {
		return NVTEVT_KEY_FACEDETECT;
	}
	if (keys & FLGKEY_DEL) {
		return NVTEVT_KEY_DEL;
	}
	if (keys & FLGKEY_LEFT) {
		return NVTEVT_KEY_LEFT;
	}
	if (keys & FLGKEY_RIGHT) {
		return NVTEVT_KEY_RIGHT;
	}
	if (keys & FLGKEY_ENTER) {
		return NVTEVT_KEY_ENTER;
	}
	if (keys & FLGKEY_SHUTTER1) {
		return NVTEVT_KEY_SHUTTER1;
	}
	if (keys & FLGKEY_SHUTTER2) {
		return NVTEVT_KEY_SHUTTER2;
	}
	if (keys & FLGKEY_ZOOMOUT) {
		return NVTEVT_KEY_ZOOMOUT;
	}
	if (keys & FLGKEY_ZOOMIN) {
		return NVTEVT_KEY_ZOOMIN;
	}
	if (keys & FLGKEY_UP) {
		return NVTEVT_KEY_UP;
	}
	if (keys & FLGKEY_DOWN) {
		return NVTEVT_KEY_DOWN;
	} else {
		return NVTEVT_NULL;
	}
}
#endif
//just for backward compatible
void Input_SetKeyMask(KEY_STATUS uiMode, UINT32 uiMask)
{
	SysMan_SetKeyMask(uiMode, uiMask);
}
UINT32 Input_GetKeyMask(KEY_STATUS uiMode)
{
	return SysMan_GetKeyMask(uiMode);
}
void Input_SetKeySoundMask(KEY_STATUS uiMode, UINT32 uiMask)
{
	SysMan_SetKeySoundMask(uiMode, uiMask);
}
UINT32 Input_GetKeySoundMask(KEY_STATUS uiMode)
{
	return SysMan_GetKeySoundMask(uiMode);
}

/**
    reset all mask,usually in new winodw onOpen
*/
void Input_ResetMask(void)
{
	// Set key mask as default
	SysMan_SetKeyMask(KEY_PRESS, FLGKEY_KEY_MASK_DEFAULT);
	SysMan_SetKeyMask(KEY_RELEASE, FLGKEY_KEY_MASK_DEFAULT);
	SysMan_SetKeyMask(KEY_CONTINUE, FLGKEY_KEY_MASK_NULL);
#if defined(_TOUCH_ON_)
	SysMan_SetTouchMask(TOUCH_MASK_DEFAULT);
#endif
	SysMan_SetKeySoundMask(KEY_PRESS, FLGKEY_SOUND_MASK_DEFAULT);
	SysMan_SetKeySoundMask(KEY_RELEASE, FLGKEY_KEY_MASK_NULL);
	SysMan_SetKeySoundMask(KEY_CONTINUE, FLGKEY_SOUND_MASK_DEFAULT);
}
/**
    for some case,press any key unlock all,and post NVTEVT_KEY_PRESS
    ex:Timelapse or smile detect
*/
void Input_SetAnyKeyUnlock(BOOL en)
{
	m_uiAnyKeyUnlockEn = en;
}


UINT32 Input_Key2Mode(UINT32 keys)
{
#if (STATUSKEY_FUNCTION == ENABLE)
	switch (keys) {
	case NVTEVT_KEY_STATUS1:
		return DSC_MODE_MOVIE;
	case NVTEVT_KEY_STATUS2:
		return DSC_MODE_PHOTO_MANUAL;
	case NVTEVT_KEY_STATUS3:
		return DSC_MODE_PHOTO_MANUAL;
	case NVTEVT_KEY_STATUS4:
		return DSC_MODE_PHOTO_MANUAL;
	case NVTEVT_KEY_STATUS5:
		return DSC_MODE_PHOTO_MANUAL;
	case NVTEVT_KEY_STATUS6:
		return DSC_MODE_PHOTO_SCENE;
	case NVTEVT_KEY_STATUS7:
		return DSC_MODE_PHOTO_MANUAL;
	case NVTEVT_KEY_STATUS8:
		return DSC_MODE_PHOTO_MANUAL;
	case NVTEVT_KEY_STATUS9:
		return DSC_MODE_PHOTO_MANUAL;
	case NVTEVT_KEY_STATUS10:
		return DSC_MODE_PHOTO_MANUAL;
	default:
		return DSC_MODE_PHOTO_AUTO;
	}
#else
	return 0;
#endif
}
extern SX_CMD_ENTRY key[];
void System_OnInputInit(void)
{
	//PHASE-1 : Init & Open Drv or DrvExt
	{
		GxKey_RegCB(Key_CB);         //Register CB function of GxInput
#if defined(_TOUCH_ON_)
		GxTouch_RegCB(Touch_CB);     //Register CB function of GxInput
#endif
		GxKey_Init();
		SxCmd_AddTable(key);
	}
	//PHASE-2 : Init & Open Lib or LibExt
	{
		//1.³]©winit­È
		//2.³]©wCB­È,
		GxKey_SetContDebounce(BURSTKEY_DEBOUNCE / SxTimer_GetData(SXTIMER_TIMER_BASE));
		GxKey_SetRepeatInterval(BURSTKEY_INTERVAL / SxTimer_GetData(SXTIMER_TIMER_BASE));
		SysMan_RegKeySoundCB(KeySoundCB);
		SysMan_RegKeyTable(g_KeyTable, sizeof(g_KeyTable) / sizeof(KEY_OBJ));
		//3.µù¥USxJobªA°È ---------> System Job
		//4.µù¥USxTimerªA°È ---------> Detect Job

#if (POWERKEY_FUNCTION == ENABLE)
		SX_TIMER_DET_PWR_ID = SxTimer_AddItem(&Timer_Input_DetPKey);
#endif
#if (NORMALKEY_FUNCTION == ENABLE)
		SX_TIMER_DET_KEY_ID = SxTimer_AddItem(&Timer_Input_DetNKey);
#endif
#if (STATUSKEY_FUNCTION == ENABLE)
		SX_TIMER_DET_MODE_ID = SxTimer_AddItem(&Timer_Input_DetSKey);
#endif
#if (GSENSOR_FUNCTION == ENABLE)
		SX_TIMER_DET_GSENSOR_ID = SxTimer_AddItem(&Timer_Input_DetC1Key);
#endif
#if defined(_TOUCH_ON_)
		SX_TIMER_DET_TOUCH_ID = SxTimer_AddItem(&Timer_Input_DetTP);
#endif

		SX_TIMER_DET_MCUCMD_ID = SxTimer_AddItem(&Timer_Input_DetMCUCMD);

		SX_TIMER_OneSecond_ID = SxTimer_AddItem(&Timer_Input_OneSecond);

#if (STATUSKEY_FUNCTION == ENABLE)
		GxKey_DetStatusKey();
#endif

#if (POWERKEY_FUNCTION == ENABLE)
		SxTimer_SetFuncActive(SX_TIMER_DET_PWR_ID, TRUE);
#endif
#if (NORMALKEY_FUNCTION == ENABLE)
		SxTimer_SetFuncActive(SX_TIMER_DET_KEY_ID, TRUE);
#endif
#if (STATUSKEY_FUNCTION == ENABLE)
		SxTimer_SetFuncActive(SX_TIMER_DET_MODE_ID, TRUE);
#endif
#if (GSENSOR_FUNCTION == ENABLE)
		SxTimer_SetFuncActive(SX_TIMER_DET_GSENSOR_ID, TRUE);
#endif

            SxTimer_SetFuncActive(SX_TIMER_DET_MCUCMD_ID, TRUE);
	     SxTimer_SetFuncActive(SX_TIMER_OneSecond_ID, TRUE);
#if defined(_TOUCH_ON_)
		GxTouch_Init();
		GxTouch_SetCtrl(GXTCH_DOUBLE_CLICK_INTERVAL,
						DOUBLECLICK_INTERVAL / TOUCH_TIMER_CNT / SxTimer_GetData(SXTIMER_TIMER_BASE));
		SysMan_RegTouchSoundCB(KeySoundCB);
		SysMan_RegTouchTable(g_TouchTable, sizeof(g_TouchTable) / sizeof(TOUCH_OBJ));
		SxTimer_SetFuncActive(SX_TIMER_DET_TOUCH_ID, TRUE);
#endif
	}
}

void System_OnInputExit(void)
{
	//PHASE-2 : Close Lib or LibExt
	{
	}
	//PHASE-1 : Close Drv or DrvExt
	{
	}
}

/////////////////////////////////////////////////////////////////////////////

void UI_DetPwrKey(void)
{
	if (!UI_IsForceLock()) {
		GxKey_DetPwrKey();
	}
}

void UI_DetNormalKey(void)
{
	static UINT32 keyDetectCount = 0;
	if (!UI_IsForceLock()) {
		GxKey_DetNormalKey();

		if (keyDetectCount < 4) {
			keyDetectCount++;
		}

		if (keyDetectCount == 2) {
			//recover the key detection after system boot up
			GxKey_SetFirstKeyInvalid(KEY_PRESS, 0);
		}
	}
}

void UI_DetStatusKey(void)
{
//check mode key
	if ((!UI_IsForceLock()) && (!UI_IsForceLockStatus())) {
		GxKey_DetStatusKey();
	}
}


void UI_OneSecond(void)//0.5s
{
	static UINT32 secondCount=0,wifi_off_count=0;
	//debug_msg("One Second\r\n");
	if(secondCount > 4)
	{
		if((gpio_getPin(P_GPIO_25) ==0) && (g_TVEnable == FALSE)&&(MCUSendPoweroff == FALSE))
		{
			debug_msg("---------------------TV ON---------------\r\n");
			g_TVEnable = TRUE;
			DrvTV_TurnOn();
		}
		if(gpio_getPin(P_GPIO_25) ==1 && g_TVEnable == TRUE)
		{
		      debug_msg("---------------------TV OFF---------------\r\n");
			g_TVEnable = FALSE;
			DrvTV_TurnOff();		
		}
	}
	if(((System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE) && (gMovData.State == MOV_ST_REC))|| 
		((UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK) && (WIFI_MOV_ST_RECORD == WiFiCmd_GetStatus()))||
		//(System_GetState(SYS_STATE_CARD)  == CARD_REMOVED)||
		(Wifi_ON_OFF_Flag == TRUE))
	{
		if(gpio_getPin(D_GPIO_1) == 0)
		{
			gpio_setPin(D_GPIO_1);
		}
		else
		{
			gpio_clearPin(D_GPIO_1);
		}	
	}
	else
	{
		gpio_clearPin(D_GPIO_1);
	}

	if(Wifi_ON_OFF_Flag == TRUE)
	{
		wifi_off_count ++;
		if(wifi_off_count>5)
		{
			Wifi_ON_OFF_Flag = FALSE;
			wifi_off_count = 0;
		}
	}
	
	if(secondCount < 20)
 	secondCount ++;


 	if(secondCount > 2 && secondCount < 5)
 	{
 		uart2_putString("AT+START\r\n");
 	}
}
 //PSDMMC_CSD_STRUCT pSDCardInfo;
void UI_DetMCUCMD(void)
{
      //static UINT64 stg_fat_free, stg_fat_total;
	 static UINT32  ReceiveMovRecMaxTime = 0,TimeWait_Count=0;   

	  INT32 DeleteFile_return;
	  UINT32  uiClusterSize;
	if(RecvieFromMCU_Flag == TRUE)
	{
		RecvieFromMCU_Flag = FALSE;
		switch(RecvieCMD_FromMCU)
		{
			case Receive_AT:
				debug_msg("Return_AT\r\n");
				uart2_putString(Return_AT);
				break;
			case Receive_AT_WIFION:
				debug_msg("Return_WIFION\r\n");
				uart2_putString(Return_WIFION);
				//¹Ø±ÕÂ¼Ïñ¡¢²¥·ÅµÈ
				
				if ((System_GetState(SYS_STATE_CARD) == CARD_REMOVED) || (FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE) == 0x0000))
				{
					//
					if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_NG)
			             {
			                    if(CheckWiFiMapTbl()!=E_OK)
			                    {
			                        UI_SetData(FL_WIFI_LINK,WIFI_LINK_NG);
			                        break;
			                    }
			                    UI_SetData(FL_WIFI_LINK,WIFI_LINK_LINKING);
			                    #if(WIFI_UI_FLOW_VER == WIFI_UI_VER_1_0)
			                    Ux_OpenWindow(&UIMenuWndWiFiWaitCtrl, 0);
			                    #endif
			                    BKG_PostEvent(NVTEVT_BKW_WIFI_ON);
			             }
				}
				else
				{
					if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE && (gMovData.State != MOV_ST_VIEW))
					{
						//ÇÐ»»µ½Ô¤ÀÀ
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);

                            	      //Delay_DelayMs(1000);
		                          TimeWait_Count = 0;
						while(gMovData.State != MOV_ST_VIEW)
						{
							Delay_DelayMs(20);
							TimeWait_Count ++;
							if(TimeWait_Count > 100)
							{
								DBG_ERR("Wait RecStop Timeout\r\n");
								break;
							}
						}
					}
						CHKPNT;
					      Delay_DelayMs(200);
                                      if(UI_GetData(FL_MOVIE_RATE) == MOVIE_RATE_HIGH)
                                      	{
                                      	      CurrentRateBeforWIFI_onFlag = TRUE;
                                      		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_NORMAL);
                                      	}
						  
						if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_NG)
			         	      {
			                   		 if(CheckWiFiMapTbl()!=E_OK)
			                  		  {
			                   		     UI_SetData(FL_WIFI_LINK,WIFI_LINK_NG);
			                   		     break;
			                 		   }

			                		   UI_SetData(FL_WIFI_LINK,WIFI_LINK_LINKING);
			                    	#if(WIFI_UI_FLOW_VER == WIFI_UI_VER_1_0)
			                   		 Ux_OpenWindow(&UIMenuWndWiFiWaitCtrl, 0);
			                   		 #endif
			                	    BKG_PostEvent(NVTEVT_BKW_WIFI_ON);
					     }
				}
				break;
			case Receive_AT_WIFIOFF:
				debug_msg("Return_WIFIOFF\r\n");
				Wifi_ON_OFF_Flag = TRUE;
				uart2_putString(Return_WIFIOFF);
				//if((gMovData.State == MOV_ST_VIEW)||(gPhotoData.State == PHOTO_ST_VIEW)||(g_PlbData.State == PLB_ST_FULL))
				//{
				     if(CurrentRateBeforWIFI_onFlag == TRUE)
				     	{
				     		CurrentRateBeforWIFI_onFlag = FALSE;
				     		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_HIGH);
				     	}
					 Delay_DelayMs(100);
				      Save_MenuInfo();
					if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
			            {
			                   /* UI_SetData(FL_WIFI_LINK,WIFI_LINK_DISCONNECTING);
			                    Ux_SendEvent(0,NVTEVT_EXE_WIFI_STOP,0);
			                    Ux_SendEvent(0,NVTEVT_KEY_SELECT,0);
						 Delay_DelayMs(2000);
						 //mode change
						 Ux_OpenWindow(&UIFlowWndMovieCtrl,0);
			    			 Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);//,SYS_SUBMODE_NORMAL);
						 RecvieFromMCU_Flag = FALSE;*/
						RecvCMD_WIFI_OFF = TRUE;
					 	Ux_PostEvent(NVTEVT_KEY_SELECT, 1, NVTEVT_KEY_PRESS);
						RecvieFromMCU_Flag = FALSE;

			             } 
					else
					{CHKPNT;
						//Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);	
						Ux_OpenWindow(&UIFlowWndMovieCtrl,0);
			    			Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);//,SYS_SUBMODE_NORMAL);
					}
				//}
				break;
			case Receive_AT_SD:
				if(System_GetState(SYS_STATE_CARD)  == CARD_REMOVED)
				{
					debug_msg("Return_SD_FAIL\r\n");
					uart2_putString(Return_SD_FAIL);
					break;
				}
				uiClusterSize = FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE);
				if(uiClusterSize == 0x0000)
				{
					debug_msg("SD Card Not Fat32 Format\r\n");
					uart2_putString(Return_SD_NOFILESYSTEM);
					break;
				}
				if(UIStorageCheck(STORAGE_CHECK_ERROR, NULL) == TRUE)
			      {
			      		debug_msg("Return_SD_ERROR\r\n");
					uart2_putString(Return_SD_ERROR);
					break;
			      }
				if(UIFlowWndMovie_OnStorageSlow_evenFlag == TRUE)
				{
					debug_msg("Return_SD_SLOW\r\n");
					uart2_putString(Return_SD_SLOW);
					break;
				}
 				ReceiveMovRecMaxTime = MovieExe_GetMaxRecSec();
				if (ReceiveMovRecMaxTime <= 1)
      				{
        			       ReceiveMovRecMaxTime = 0;
					debug_msg("Return_SD_FULL\r\n");
					uart2_putString(Return_SD_FULL);
					break;
				}
				uart2_putString(Return_SD_OK);
				break;
			case Receive_AT_SOS:
				uart2_putString(Return_SOSING);
				//if(MCUSendAT_SOS == FALSE)
				{
					MCUSendAT_SOS = TRUE;
					CHKPNT;
					SetCrash_Flag = TRUE;
					Ux_PostEvent(NVTEVT_KEY_CUSTOM1, 1, NVTEVT_KEY_PRESS);
					Delay_DelayMs(500);
					RecvieFromMCU_Flag = FALSE;
					uart2_putString(Return_SOSFINISH);
				}
				debug_msg("Return_SOSFINISH\r\n");
				break;
			case Receive_AT_RESET:
				uart2_putString(Return_RESETOK);
				debug_msg("Return_RESETOK\r\n");
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					if(WIFI_MOV_ST_RECORD == WiFiCmd_GetStatus())
					{
						RecMIC_ChangeCMD = TRUE;
						Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 0);//Stop record movie
						Delay_DelayMs(1000);
						Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_SYSRESET, 0);
						Delay_DelayMs(1000);
						Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
					}
					else
					{
				      		Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_SYSRESET, 0);
						Delay_DelayMs(1000);
						Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
					}
				}
				else
				{
					if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE && (gMovData.State != MOV_ST_VIEW))
					{
						//ÇÐ»»µ½Ô¤ÀÀ
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
	                                Delay_DelayMs(1500);
						if(gMovData.State == MOV_ST_VIEW)
						{
							Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_SYSRESET, 0);
							Delay_DelayMs(1000);
							Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
						}
					}
					else
					{
						Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_SYSRESET, 0);
						Delay_DelayMs(1000);
						Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
					}
				}
				break;
			case Receive_AT_50HZ:
				debug_msg("Return_50HZ\r\n");
				Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_FREQ, 1, FREQUENCY_50HZ);
				uart2_putString(Return_50HZ);
				break;
			case Receive_AT_60HZ:
				debug_msg("Return_60HZ\r\n");
				Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_FREQ, 1, FREQUENCY_60HZ);
				uart2_putString(Return_60HZ);
				break;
			case Receive_AT_FORMAT:
			      if(System_GetState(SYS_STATE_CARD)  == CARD_REMOVED)
			      	{
			      		uart2_putString(Return_SD_FAIL);
					break;
			      	}
				debug_msg("Return_FORMATING\r\n");
				uart2_putString(Return_FORMATING);
				 if(FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE) == 0x0000)
				{
					BKG_PostEvent(NVTEVT_BKW_FORMAT_CARD);
					FormatByMCU = TRUE;
					Delay_DelayMs(2000);
					debug_msg("Return_FORMAT_OK\r\n");
					uart2_putString(Return_FORMAT_OK);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
					break;
				}
				else
				{
					if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
					{
						//if(WIFI_MOV_ST_RECORD == UIFlowWndWiFiMovie_GetStatus())
						if(WIFI_MOV_ST_RECORD == WiFiCmd_GetStatus())
						{
							RecMIC_ChangeCMD = TRUE;
							Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 0);//Stop record movie
							Delay_DelayMs(1000);
						}
						BKG_PostEvent(NVTEVT_BKW_FORMAT_CARD);
						FormatByMCU = TRUE;
						Delay_DelayMs(2000);
						uart2_putString(Return_FORMAT_OK);
						Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
					}
					else
					{
						if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE && (gMovData.State != MOV_ST_VIEW))
						{
							//ÇÐ»»µ½Ô¤ÀÀ
							Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
		                                Delay_DelayMs(1500);
						}
						BKG_PostEvent(NVTEVT_BKW_FORMAT_CARD);
						FormatByMCU = TRUE;
						Delay_DelayMs(2000);
						debug_msg("Return_FORMAT_OK\r\n");
						uart2_putString(Return_FORMAT_OK);
						Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
					}
				 }
				break;
			case Receive_AT_MICR://ÄÚÖÃ
				debug_msg("Return_MICR_OK_INTER_MIC\r\n");
				uart2_putString(Return_MICR_OK);
				if(UI_GetData(FL_MOVIE_AUDIO) != MOVIE_AUDIO_OFF)
				{
					UI_SetData(FL_MOVIE_AUDIO_LAST, UI_GetData(FL_MOVIE_AUDIO));
				}
				
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					if(WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)
					{
						RecMIC_ChangeCMD = TRUE;
						Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 0);//Stop record movie
						Delay_DelayMs(1000);	
					}
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIO, 1, MOVIE_INTER_MIC);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);	
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIO, 1, MOVIE_INTER_MIC);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);	
				}
				break;
			case Receive_AT_MICL:
				debug_msg("Return_MICL_OK_EXTERN_MIC\r\n");
				uart2_putString(Return_MICL_OK);
				if(UI_GetData(FL_MOVIE_AUDIO) != MOVIE_AUDIO_OFF)
				{
					UI_SetData(FL_MOVIE_AUDIO_LAST, UI_GetData(FL_MOVIE_AUDIO));
				}
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					if(WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)
					{
						RecMIC_ChangeCMD = TRUE;
						Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 0);//Stop record movie
						Delay_DelayMs(1000);
					}
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIO, 1,MOVIE_EXTERN_MIC);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIO, 1,MOVIE_EXTERN_MIC);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				break;
			case Receive_AT_MICOFF:
				debug_msg("Return_MICOFF_OK\r\n");
				uart2_putString(Return_MICOFF_OK);
				if(UI_GetData(FL_MOVIE_AUDIO) != MOVIE_AUDIO_OFF)
				{
					UI_SetData(FL_MOVIE_AUDIO_LAST, UI_GetData(FL_MOVIE_AUDIO));
				}
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					if(WIFI_MOV_ST_RECORD == WiFiCmd_GetStatus())
					{
						RecMIC_ChangeCMD = TRUE;
						Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 0);//Stop record movie
						Delay_DelayMs(1000);
					}
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIO, 1,MOVIE_AUDIO_OFF);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_AUDIO, 1,MOVIE_AUDIO_OFF);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				break;
			case Receive_AT_PHOTO://
				debug_msg("Return_PHOTO_OK\r\n");
				uart2_putString(Return_PHOTO_OK);
				debug_msg("Current mode= %d \r\n",System_GetState(SYS_STATE_CURRMODE));
				if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE)
				{
					if(gMovData.State == MOV_ST_MENU)
					{
						Ux_PostEvent(NVTEVT_KEY_ENTER, 1, NVTEVT_KEY_PRESS);
					}
					else if((gMovData.State == MOV_ST_REC) || (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK&&WIFI_MOV_ST_RECORD == WiFiCmd_GetStatus()))
					{
						//Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
						//Â¼ÏñÖÐÅÄÕÕ
						CHKPNT;
						Ux_PostEvent(NVTEVT_KEY_RIGHT, 1, NVTEVT_KEY_PRESS);
					}
				}
				else if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_PHOTO)
				{
					if(gPhotoData.State == PHOTO_ST_VIEW)
					{
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
					}
					else if(gPhotoData.State == PHOTO_ST_MENU)
					{
						Ux_PostEvent(NVTEVT_KEY_ENTER, 1, NVTEVT_KEY_PRESS);
					}
				}
				else if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_PLAYBACK)
				{
					if( g_PlbData.State == PLB_ST_FULL)
					{
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
					}
					else if(g_PlbData.State == PLB_ST_MENU)
					{
						Ux_PostEvent(NVTEVT_KEY_ENTER, 1, NVTEVT_KEY_PRESS);
					}
				}
				break;
			case Receive_AT_MENU:
				uart2_putString(Return_MENU);

				if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_PLAYBACK)
				{
					 if(System_GetState(SYS_STATE_CARD)  == CARD_REMOVED)
					{
						debug_msg("CARD_REMOVED  \r\n");
						break;
					}
					if(FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE) == 0x0000)
					{
						debug_msg("SD Card Not Fat32 Format\r\n");
						break;
					}
					if(UIStorageCheck(STORAGE_CHECK_ERROR, NULL) == TRUE)
				      {
				      		debug_msg(" SDCard ERROR\r\n");
						break;
				      }
				}
				Ux_PostEvent(NVTEVT_KEY_MENU, 1, NVTEVT_KEY_PRESS);
				debug_msg("Return_MENU\r\n");
				break;
			case Receive_AT_MODE:
				uart2_putString(Return_MODE);

				if(System_GetState(SYS_STATE_CARD)  == CARD_REMOVED ||
					FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE) == 0x0000||
					UIStorageCheck(STORAGE_CHECK_ERROR, NULL) == TRUE)
				{
					if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE)
					{CHKPNT;
						Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_PHOTO);
					}
					else if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_PHOTO)
					{CHKPNT;
					    Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);
					}
					else
					{
						Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_MOVIE);
					}
					Delay_DelayMs(1000);
					RecvieFromMCU_Flag = FALSE;
					break;
				}
				else
				{				
					if((gMovData.State == MOV_ST_VIEW)||(gPhotoData.State == PHOTO_ST_VIEW)||(g_PlbData.State == PLB_ST_FULL))
					{
						Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_NEXT);
						Delay_DelayMs(1000);
						RecvieFromMCU_Flag = FALSE;
					}
				}
				debug_msg("Return_MODE\r\n");
				break;
			case Receive_AT_UP:
				debug_msg("Return_UP\r\n");
				Ux_PostEvent(NVTEVT_KEY_UP, 1, NVTEVT_KEY_PRESS);
				uart2_putString(Return_UP);
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					Ux_PostEvent(NVTEVT_KEY_NEXT, 1, NVTEVT_KEY_PRESS);
				}
				break;
			case Receive_AT_DOWN:
				debug_msg("Return_DOWN\r\n");
				Ux_PostEvent(NVTEVT_KEY_DOWN, 1, NVTEVT_KEY_PRESS);
				uart2_putString(Return_DOWN);
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					Ux_PostEvent(NVTEVT_KEY_NEXT, 1, NVTEVT_KEY_PRESS);
				}
				break;
			case Receive_AT_ENTER:
				uart2_putString(Return_ENTER);
				debug_msg("Return_ENTER %d\r\n",System_GetState(SYS_STATE_CURRMODE)  );
				/*if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_MOVIE)
				{
				      debug_msg("gMovData.State = %d\r\n",gMovData.State);
					if(gMovData.State == MOV_ST_MENU || gMovData.State == MOV_ST_WARNING_MENU)
					{
						Ux_PostEvent(NVTEVT_KEY_ENTER, 1, NVTEVT_KEY_PRESS);
					}
					else
					{
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
					}
				}
				else if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_PHOTO)
				{
					debug_msg("gPhotoData.State = %d\r\n",gPhotoData.State);
					if(gPhotoData.State == PHOTO_ST_VIEW)
					{
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
					}
					else if(gPhotoData.State == PHOTO_ST_MENU || gPhotoData.State ==PHOTO_ST_WARNING_MENU)
					{
						Ux_PostEvent(NVTEVT_KEY_ENTER, 1, NVTEVT_KEY_PRESS);
					}
				}
				else if(System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_PLAYBACK)
				{
					debug_msg("g_PlbData.State = %d\r\n",g_PlbData.State);
					if( g_PlbData.State == PLB_ST_MENU)
					{
						Ux_PostEvent(NVTEVT_KEY_ENTER, 1, NVTEVT_KEY_PRESS);
					}
					else// if(g_PlbData.State == PLB_ST_MENU)
					{
						Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
					}
				}*/
				//WIFI
				Ux_PostEvent(NVTEVT_KEY_SHUTTER2, 1, NVTEVT_KEY_PRESS);
				 if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK && g_TVEnable == TRUE)
				 {
				 	Ux_PostEvent(NVTEVT_KEY_SELECT, 1, NVTEVT_KEY_PRESS);
				 }
				break;
			case Receive_AT_DELBIN:
				debug_msg("Receive_AT_DELBIN\r\n");
				uart2_putString(Return_AT_DELBIN_OK);
				DeleteFile_return = FileSys_DeleteFile("A:\\GPS2.bin");
				if(DeleteFile_return == FST_STA_OK)
				{
					debug_msg("Delete bin File OK\r\n");
				}
				else if(DeleteFile_return == FST_STA_NO_FILE)
				{
					debug_msg("Delete bin fail :no file\r\n");
				}
				else if(DeleteFile_return == FST_STA_ERROR)
				{
					debug_msg("Delete bin fail \r\n");
				}
				break;
			case Receive_AT_RATE:
				debug_msg("Receive_AT_RATE\r\n");
				if(UI_GetData(FL_MOVIE_RATE) == MOVIE_RATE_NORMAL)
				{
					uart2_putString(Return_AT_RATEM_OK);
				}
				else if(UI_GetData(FL_MOVIE_RATE) == MOVIE_RATE_HIGH)
				{
					uart2_putString(Return_AT_RATEH_OK);
				}
				else if(UI_GetData(FL_MOVIE_RATE) == MOVIE_RATE_LOW)
				{
					uart2_putString(Return_AT_RATEL_OK);
				}
				break;	
			case Receive_AT_RATEH:
				debug_msg("Receive_AT_RATEH\r\n");
				uart2_putString(Return_AT_RATEH_OK);
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					CurrentRateBeforWIFI_onFlag = TRUE;
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_HIGH);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				/*if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					if(WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)
					{
						RecRate_ChangeCMD = TRUE;
						Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 0);//Stop record movie
						Delay_DelayMs(1000);
					}
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, 1);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, 1);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}*/
				break;
			case Receive_AT_RATEM:
				debug_msg("Receive_AT_RATEM\r\n");
				uart2_putString(Return_AT_RATEM_OK);
				/*if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					CurrentRateBeforWIFI_onFlag = FALSE;
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_NORMAL);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}*/
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					CurrentRateBeforWIFI_onFlag = FALSE;
					if(WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)
					{
						RecRate_ChangeCMD = TRUE;
						Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 0);//Stop record movie
						Delay_DelayMs(1000);
					}
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_NORMAL);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_NORMAL);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				break;
			case Receive_AT_RATEL:
				debug_msg("Receive_AT_RATEL\r\n");
				uart2_putString(Return_AT_RATEL_OK);
                        /* if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					CurrentRateBeforWIFI_onFlag = FALSE;
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_LOW);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}*/
				if(UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					CurrentRateBeforWIFI_onFlag = FALSE;
					if(WiFiCmd_GetStatus() == WIFI_MOV_ST_RECORD)
					{
						RecRate_ChangeCMD = TRUE;
						Ux_PostEvent(NVTEVT_WIFI_EXE_MOVIE_REC, 1, 0);//Stop record movie
						Delay_DelayMs(1000);
					}
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_LOW);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				else
				{
					Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_LOW);
					Delay_DelayMs(500);
					Ux_SendEvent(&UISetupObjCtrl,NVTEVT_EXE_CHANGEDSCMODE,1,DSCMODE_CHGTO_CURR);
				}
				break;
			case Receive_AT_CCDMODE:
				debug_msg("Receive_AT_CCDMODE\r\n");
				uart2_putString(Return_AT_CCDMODE_OK);
				Ux_SendEvent(0, NVTEVT_SYSTEM_MODE, 1, PRIMARY_MODE_USBPCC);//
				break;
			case Receive_AT_PWROFF:
				debug_msg("Receive_AT_PWROFF\r\n");
				uart2_putString(Return_AT_POWOFF_OK);
				if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
				{
					if(CurrentRateBeforWIFI_onFlag == TRUE)
					{
						CurrentRateBeforWIFI_onFlag = FALSE;
				     		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_HIGH);
				     	}
				      Delay_DelayMs(100);
				}
				
				if(MCUSendPoweroff == FALSE)
				{
					MCUSendPoweroff = TRUE;
					Ux_PostEvent(NVTEVT_SYSTEM_SHUTDOWN, 1, 0);
				}
				break;
			default:
				break;
		}
	}
}


BOOL CurrentFileLockFlag = FALSE;
#if (GSENSOR_FUNCTION == ENABLE)
void UI_DetCustom1Key(void)
{
	BOOL   bGSensorStatus = FALSE;
	Gsensor_Data GS_Data = {0};
	bGSensorStatus = GSensor_GetStatus(&GS_Data);
	if (bGSensorStatus == TRUE) {
		if(CurrentFileLockFlag == FALSE)
		{
			CurrentFileLockFlag = TRUE;
			SetCrash_Flag = TRUE;
			Ux_PostEvent(NVTEVT_KEY_CUSTOM1, 1, NVTEVT_KEY_PRESS);
			uart2_putString(Return_AT_SOS);
		}
	}
	//DBGD(bGSensorStatus);
}
#endif

/////////////////////////////////////////////////////////////////////////////
extern void System_ResetDetCloseLenCount(void);
extern void System_ResetPowerSaveCount(void);
BOOL g_bConsumeStatus = FALSE;

INT32 System_UserKeyFilter(NVTEVT evt, UINT32 paramNum, UINT32 *paramArray)
{
	UINT32 key = evt;
	#if (POWER_KEY_LONG_PRESS == ENABLE)
	static UINT32 power_key_press_count = 0;
	#endif

	if (IN_RANGE_EVENT(key, NVTEVT_KEY_STATUS_START, NVTEVT_KEY_STATUS_END)) { //Status class
		System_ResetDetCloseLenCount();
		System_ResetPowerSaveCount();
#if (STATUSKEY_FUNCTION == ENABLE)
		DBG_IND("^Bgroup key event=0x%x\r\n", key);

		if (g_bConsumeStatus) {
			g_bConsumeStatus = 0;
		} else {
			UINT32 uiDscMode = Input_Key2Mode(key);
			DBG_IND("^YDscMode=0x%x\r\n", uiDscMode);
			//FlowMode_OnKeyMode(uiDscMode);
			UI_Switch_DscMode(uiDscMode, DSCMODE_SWITCH_FORCE, DSCMODE_SWITCHDIR_DONT_CARE);
		}
#endif
		return NVTEVT_CONSUME;
	} else if (IN_RANGE_EVENT(key, NVTEVT_KEY_BUTTON_START, NVTEVT_KEY_BUTTON_END)) { //Button class
		if (IN_RANGE_EVENT(key, NVTEVT_KEY_PRESS_START, NVTEVT_KEY_PRESS_END)) { //Press key
			if (key == NVTEVT_KEY_POWER) {
				return NVTEVT_CONSUME;
			}

			System_ResetDetCloseLenCount();
			if (GxPower_GetControl(GXPWR_CTRL_SLEEP_LEVEL) > 1) { // drop key if sleep level > 1
				//NOTE! do not set GXPWR_CTRL_SLEEP_RESET before get GXPWR_CTRL_SLEEP_LEVEL,
				//  because GXPWR_CTRL_SLEEP_LEVEL status maybe alter by sleep wakeup flow~
				System_ResetPowerSaveCount();
				return NVTEVT_CONSUME;
			} else {
				System_ResetPowerSaveCount();
				if (m_uiAnyKeyUnlockEn) {
					Ux_PostEvent(NVTEVT_KEY_PRESS_START, 1, key);
					return NVTEVT_CONSUME;
				}
				return NVTEVT_PASS;
			}
		} else if (IN_RANGE_EVENT(key, NVTEVT_KEY_CONTINUE_START, NVTEVT_KEY_CONTINUE_END)) { //Contine key
			if (key == NVTEVT_KEY_POWER_CONT) {
				#if (POWER_KEY_LONG_PRESS == ENABLE)
				power_key_press_count++;
				if (power_key_press_count > 10) { // about 1.2 sec
					System_PowerOff(SYS_POWEROFF_NORMAL);
				}
				#endif
				return NVTEVT_CONSUME;
			}

			System_ResetDetCloseLenCount();
			System_ResetPowerSaveCount();
			return NVTEVT_PASS;
		} else if (IN_RANGE_EVENT(key, NVTEVT_KEY_RELEASE_START, NVTEVT_KEY_RELEASE_END)) { //Release key
			if (key == NVTEVT_KEY_POWER_REL) {
				System_ResetDetCloseLenCount();
				if (GxPower_GetControl(GXPWR_CTRL_SLEEP_LEVEL) > 1) { // drop key if sleep level > 1
					//NOTE! do not set GXPWR_CTRL_SLEEP_RESET before get GXPWR_CTRL_SLEEP_LEVEL,
					//  because GXPWR_CTRL_SLEEP_LEVEL status maybe alter by sleep wakeup flow~
					System_ResetPowerSaveCount();
				} else {
					//#NT#2016/03/07#KCHong -begin
					//#NT#Low power timelapse function
#if (TIMELAPSE_LPR_FUNCTION == ENABLE)
					MovieTLLPR_Process(TIMELAPSE_FROM_PWRKEY);
#endif
					//#NT#2016/03/07#KCHong -end
					#if (POWER_KEY_LONG_PRESS == ENABLE)
					power_key_press_count = 0;
					#else
					System_PowerOff(SYS_POWEROFF_NORMAL);
					#endif
				}
				return NVTEVT_CONSUME;
			}

			System_ResetDetCloseLenCount();
			System_ResetPowerSaveCount();
			return NVTEVT_PASS;
		}
	}
	return NVTEVT_PASS;
}

#if defined(_TOUCH_ON_)
INT32 System_UserTouchFilter(NVTEVT evt, UINT32 paramNum, UINT32 *paramArray)
{
	INT32 Ret = NVTEVT_PASS;
	//DBG_DUMP("^Bevt=%d, point=(%d, %d)\r\n", evt - NVTEVT_PRESS, paramArray[0], paramArray[1]);
	if (evt >= NVTEVT_PRESS && evt <= NVTEVT_SLIDE_DOWN) {
		if (GxPower_GetControl(GXPWR_CTRL_SLEEP_LEVEL) > 1) { // drop key if sleep level > 1
			//NOTE! do not set GXPWR_CTRL_SLEEP_RESET before get GXPWR_CTRL_SLEEP_LEVEL,
			//  because GXPWR_CTRL_SLEEP_LEVEL status maybe alter by sleep wakeup flow~
			System_ResetPowerSaveCount();
			return NVTEVT_CONSUME;
		} else {
			System_ResetPowerSaveCount();
			return NVTEVT_PASS;
		}
	}
	return Ret;
}


#endif
