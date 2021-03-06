/**
    Copyright   Novatek Microelectronics Corp. 2009.  All rights reserved.

    @file       DetKey.c
    @ingroup    mIPRJAPKeyIO

    @brief      Scan key, modedial
                Scan key, modedial

    @note       Nothing.

    @date       2017/05/02
*/

/** \addtogroup mIPRJAPKeyIO */
//@{

#include "DxCfg.h"
#include "IOCfg.h"

#include "DxInput.h"
#include "Debug.h"
#include "KeyDef.h"
#include "rtc.h"
#include "HwPower.h"
#include "Delay.h"

///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          DxDrv
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include "DebugModule.h"
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ADC related
////////////////////////////////////////////////////////////////////////////////
#if (ADC_KEY == ENABLE)
#define VOLDET_KEY_ADC_RANGE        (20)
#define VOLDET_KEY_ADC_LVL0         (0)
#define VOLDET_KEY_ADC_LVL1         (91)
#define VOLDET_KEY_ADC_LVL2         (177)
#define VOLDET_KEY_ADC_LVL3         (253)
#define VOLDET_KEY_ADC_LVL4         (340)

#define VOLDET_KEY_LVL_UNKNOWN      0xFFFFFFFF
#define VOLDET_KEY_LVL_0            0
#define VOLDET_KEY_LVL_1            1
#define VOLDET_KEY_LVL_2            2
#define VOLDET_KEY_LVL_3            3
#define VOLDET_KEY_LVL_4            4
#define VOLDET_KEY_LVL_5            5
#endif
#define key_ConditionPresMode(KeyMode,uiKeyCode,Condition) do{\
		static UINT32 powerKeyCount =0;\
		if(TRUE == Condition){\
			powerKeyCount ++;\
			if(powerKeyCount>2){\
				powerKeyCount = 0;\
				Condition = FALSE;\
			}else uiKeyCode = KeyMode;\
		}\
	}while(0);

static BOOL powerKeyNvtevt = FALSE;
#if (ADC_KEY == ENABLE)
static UINT32 VolDet_GetKey1ADC(void)
{
#if (VOLDET_ADC_CONT_MODE == DISABLE)
	UINT32 uiADCValue;

	uiADCValue = adc_readData(ADC_CH_VOLDET_KEY1);
	// One-Shot Mode, trigger one-shot
	adc_triggerOneShot(ADC_CH_VOLDET_KEY1);

	return uiADCValue;
#else
	return adc_readData(ADC_CH_VOLDET_KEY1);
#endif
}
static UINT32 VolDet_GetKey2ADC(void)
{
#if (VOLDET_ADC_CONT_MODE == DISABLE)
	UINT32 uiADCValue;

	uiADCValue = adc_readData(ADC_CH_VOLDET_KEY2);
	// One-Shot Mode, trigger one-shot
	adc_triggerOneShot(ADC_CH_VOLDET_KEY2);

	return uiADCValue;
#else
	return adc_readData(ADC_CH_VOLDET_KEY2);
#endif
}
/**
  Get ADC key voltage level

  Get  ADC key  2 voltage level.

  @param void
  @return UINT32 key level, refer to VoltageDet.h -> VOLDET_MS_LVL_XXXX
*/
static UINT32 VolDet_GetKey1Level(void)
{
	static UINT32   uiRetKey1Lvl;
	UINT32          uiKey1ADC, uiCurKey2Lvl;

	uiKey1ADC = VolDet_GetKey1ADC();
	if( uiKey1ADC < 500 )
	    DBG_IND("uiKey1ADC %d \r\n", uiKey1ADC);
	if (abs(uiKey1ADC-VOLDET_KEY_ADC_LVL0) <= VOLDET_KEY_ADC_RANGE) {
		uiCurKey2Lvl = VOLDET_KEY_LVL_0;
	} else if (abs(uiKey1ADC-VOLDET_KEY_ADC_LVL1) <= VOLDET_KEY_ADC_RANGE) {
		uiCurKey2Lvl = VOLDET_KEY_LVL_1;
	} else if (abs(uiKey1ADC-VOLDET_KEY_ADC_LVL2) <= VOLDET_KEY_ADC_RANGE) {
		uiCurKey2Lvl = VOLDET_KEY_LVL_2;
	} else if (abs(uiKey1ADC-VOLDET_KEY_ADC_LVL3) <= VOLDET_KEY_ADC_RANGE) {
		uiCurKey2Lvl = VOLDET_KEY_LVL_3;
	}else if (abs(uiKey1ADC-VOLDET_KEY_ADC_LVL4) <= VOLDET_KEY_ADC_RANGE) {
		uiCurKey2Lvl = VOLDET_KEY_LVL_4;
	}else {
		uiCurKey2Lvl = VOLDET_KEY_LVL_UNKNOWN;
	}
    
	uiRetKey1Lvl = uiCurKey2Lvl;
    if(uiRetKey1Lvl != VOLDET_KEY_LVL_UNKNOWN)
        DBG_IND(uiRetKey1Lvl);
	return uiRetKey1Lvl;
}
static UINT32 VolDet_GetKey2Level(void)
{
	static UINT32   uiRetKey1Lvl;
	UINT32          uiKey1ADC, uiCurKey2Lvl;

	uiKey1ADC = VolDet_GetKey2ADC();
	if( uiKey1ADC < 500 )
	    DBG_IND("uiKey2ADC %d \r\n", uiKey1ADC);
	if (abs(uiKey1ADC-VOLDET_KEY_ADC_LVL0) <= VOLDET_KEY_ADC_RANGE) {
		uiCurKey2Lvl = VOLDET_KEY_LVL_0;
	} else if (abs(uiKey1ADC-VOLDET_KEY_ADC_LVL1) <= VOLDET_KEY_ADC_RANGE) {
		uiCurKey2Lvl = VOLDET_KEY_LVL_1;
	} else if (abs(uiKey1ADC-VOLDET_KEY_ADC_LVL2) <= VOLDET_KEY_ADC_RANGE) {
		uiCurKey2Lvl = VOLDET_KEY_LVL_2;
	}else {
		uiCurKey2Lvl = VOLDET_KEY_LVL_UNKNOWN;
	}
    if(uiCurKey2Lvl != VOLDET_KEY_LVL_UNKNOWN)
        DBG_IND(uiCurKey2Lvl);
	uiRetKey1Lvl = uiCurKey2Lvl;

	return uiRetKey1Lvl;
}
/**
  Detect Mode Switch state.

  Detect Mode Switch state.

  @param void
  @return UINT32 Mode Switch state (DSC Mode)
*/
#endif

////////////////////////////////////////////////////////////////////////////////
// GPIO related

//static BOOL g_bIsShutter2Pressed = FALSE;

/**
  Delay between toggle GPIO pin of input/output

  Delay between toggle GPIO pin of input/output

  @param void
  @return void
*/
static void DrvKey_DetKeyDelay(void)
{
	gpio_readData(0);
	gpio_readData(0);
	gpio_readData(0);
	gpio_readData(0);
}

void DrvKey_Init(void)
{
}
/**
  Detect normal key is pressed or not.

  Detect normal key is pressed or not.
  Return key pressed status (refer to KeyDef.h)

  @param void
  @return UINT32
*/
UINT32 DrvKey_DetNormalKey(void)
{
	UINT32 uiKeyCode = 0;

#if (ADC_KEY == ENABLE)
	UINT32 uiKey1Lvl = VolDet_GetKey1Level();
	UINT32 uiKey2Lvl = VolDet_GetKey2Level();

    if(uiKey1Lvl != VOLDET_KEY_LVL_UNKNOWN || uiKey2Lvl != VOLDET_KEY_LVL_UNKNOWN)
	    DBG_IND("uiKey1Lvl =%d,uiKey2Lvl=%d \r\n",uiKey1Lvl, uiKey2Lvl);
	switch (uiKey1Lvl) {
	case VOLDET_KEY_LVL_4:
		uiKeyCode |= FLGKEY_CUSTOM1;	
		break;

	case VOLDET_KEY_LVL_3:
		uiKeyCode |= FLGKEY_DOWN;	
		break;

	case VOLDET_KEY_LVL_2:
		uiKeyCode |= FLGKEY_MENU;	
		break;

	case VOLDET_KEY_LVL_1:
		uiKeyCode |= FLGKEY_SHUTTER2;	
		break;

	case VOLDET_KEY_LVL_0:
		uiKeyCode |= FLGKEY_UP;
		break;
	}
	switch (uiKey2Lvl) {
	#if 0
	case VOLDET_KEY_LVL_2:
		uiKeyCode |= FLGKEY_CUSTOM1;	
		break;
	case VOLDET_KEY_LVL_1:
		uiKeyCode |= FLGKEY_DOWN;
		break;
		
	case VOLDET_KEY_LVL_0:
		uiKeyCode |= FLGKEY_UP;
		break;	
	#endif
	}
#endif


#if (GPIO_KEY == ENABLE)
	if (gpio_getPin(GPIO_KEY_LEFT)) {
		uiKeyCode |= FLGKEY_LEFT;
	}
	if (gpio_getPin(GPIO_KEY_SHUTTER1)) {
		uiKeyCode |= FLGKEY_SHUTTER1;
	}
	if (gpio_getPin(GPIO_KEY_SHUTTER2)) {
		uiKeyCode |= FLGKEY_SHUTTER2;
	}
	if (gpio_getPin(GPIO_KEY_ZOOMIN)) {
		uiKeyCode |= FLGKEY_ZOOMIN;
	}
	if (gpio_getPin(GPIO_KEY_ZOOMOUT)) {
		uiKeyCode |= FLGKEY_ZOOMOUT;
	}
	if (gpio_getPin(GPIO_KEY_ENTER)) {
		uiKeyCode |= FLGKEY_ENTER;
	}
#endif
	//Power Key Function
	key_ConditionPresMode(FLGKEY_ENTER, uiKeyCode, powerKeyNvtevt);
	/*
	    //detect if power-on by press playback key
	    if (!HwPower_GetPowerKey(POWER_ID_PSW2))
	    {
	        uiKeyCode |= FLGKEY_PLAYBACK;
	    }
	*/
#if 0
	if (uiKeyCode) {
		DBG_IND("KEY=%08x\r\n", uiKeyCode);
	}
	switch (uiKeyCode) {
	case FLGKEY_UP:
		debug_msg("Key Prev\r\n");
		break;
	case FLGKEY_DOWN:
		debug_msg("Key Next\r\n");
		break;
	case FLGKEY_ENTER:
		debug_msg("Key OK\r\n");
		break;
	case FLGKEY_MENU:
		debug_msg("Key Menu\r\n");
		break;
	}
#endif
	DrvKey_DetKeyDelay();
	return uiKeyCode;
}
/**
  Detect power key is pressed or not.

  Detect power key is pressed or not.
  Return key pressed status (refer to KeyDef.h)

  @param void
  @return UINT32
*/
UINT32 DrvKey_DetPowerKey(void)
{
	UINT32 uiKeyCode = 0;
	static INT16 keyPushTimeCount = 0;
	static BOOL firstRun = TRUE;
	//debug_msg("rtc_getPWRStatus:%d \r\n",rtc_getPWRStatus());
	if (HwPower_GetPowerKey(POWER_ID_PSW1)) {
		if (firstRun) {
			return uiKeyCode;
		}
		keyPushTimeCount++;
		// Reset shutdown timer
		HwPower_SetPowerKey(POWER_ID_PSW1, 0xf0);
		if (keyPushTimeCount > 20) {
			uiKeyCode = FLGKEY_KEY_POWER;
			debug_msg("^M%s: Key Power Off!\r\n", __func__);
		}
	} else {
		firstRun = FALSE;
		if ((keyPushTimeCount < 16) && (keyPushTimeCount > 0)) {
			powerKeyNvtevt = TRUE;
		}
		keyPushTimeCount = 0;
	}
	return uiKeyCode;
}
UINT32 DrvKey_DetStatusKey(DX_STATUS_KEY_GROUP KeyGroup)
{
	UINT32 uiReturn = STATUS_KEY_LVL_UNKNOWN;
	switch (KeyGroup) {
	case DX_STATUS_KEY_GROUP1:
		break;

	case DX_STATUS_KEY_GROUP2:
		break;

	case DX_STATUS_KEY_GROUP3:
		break;

	case DX_STATUS_KEY_GROUP4:
		break;

	case DX_STATUS_KEY_GROUP5:
		break;

	default:
		DBG_ERR("[StatusKey]no this attribute");
		break;
	}
	return uiReturn;
}
