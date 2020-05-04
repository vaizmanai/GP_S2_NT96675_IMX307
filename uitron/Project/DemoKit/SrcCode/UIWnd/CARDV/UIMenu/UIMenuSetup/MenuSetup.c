#include <stdio.h>
#include "UIFlow.h"


// --------------------------------------------------------------------------
// OPTIONS
// --------------------------------------------------------------------------
// Power Saving Options
#if(AUTOPWROFF_FUNCTION == ENABLE)
/*TMDEF_BEGIN_OPTIONS(AUTO_POWER_OFF)
    TMDEF_OPTION_TEXT(OFF)
    TMDEF_OPTION_TEXT(3MIN)
    TMDEF_OPTION_TEXT(5MIN)
    TMDEF_OPTION_TEXT(10MIN)
TMDEF_END_OPTIONS()*/
#endif

#if(BEEP_FUNCTION == ENABLE)
// Beep Options
TMDEF_BEGIN_OPTIONS(BEEP)
    TMDEF_OPTION_TEXT(BEEP_OFF)
    TMDEF_OPTION_TEXT(BEEP_ON)
TMDEF_END_OPTIONS()
#endif

// Language Options
TMDEF_BEGIN_OPTIONS(LANGUAGE)
    TMDEF_OPTION_TEXT(LANG_EN)
    TMDEF_OPTION_TEXT(LANG_FR)
    TMDEF_OPTION_TEXT(LANG_ES)
    TMDEF_OPTION_TEXT(LANG_PO)
    TMDEF_OPTION_TEXT(LANG_DE)
    TMDEF_OPTION_TEXT(LANG_IT)
    TMDEF_OPTION_TEXT(LANG_SC)
    TMDEF_OPTION_TEXT(LANG_TC)
    TMDEF_OPTION_TEXT(LANG_RU)
    TMDEF_OPTION_TEXT(LANG_JP)
TMDEF_END_OPTIONS()

// TV Mode Options
//TMDEF_BEGIN_OPTIONS(TV_MODE)
 //   TMDEF_OPTION_TEXT(TV_NTSC)
    //TMDEF_OPTION_TEXT(TV_PAL)
//TMDEF_END_OPTIONS()


// Frequency Options
TMDEF_BEGIN_OPTIONS(FREQUENCY)
    TMDEF_OPTION_TEXT(50HZ)
    TMDEF_OPTION_TEXT(60HZ)
TMDEF_END_OPTIONS()

// Sensor Rotate Options
TMDEF_BEGIN_OPTIONS(SENSOR_ROTATE)
    TMDEF_OPTION_TEXT(SENSOR_ROTATE_OFF)
    TMDEF_OPTION_TEXT(SENSOR_ROTATE_ON)
TMDEF_END_OPTIONS()

// Wi-Fi
TMDEF_BEGIN_OPTIONS(WIFI)
    TMDEF_OPTION_TEXT(WIFI_OFF)
    TMDEF_OPTION_TEXT(WIFI_ON)
TMDEF_END_OPTIONS()


// --------------------------------------------------------------------------
// ITEMS
// --------------------------------------------------------------------------
static int MenuCustom_DateTime(UINT32 uiMessage, UINT32 uiParam)
{
    Ux_OpenWindow(&UIMenuWndSetupDateTimeCtrl, 0);
    return TMF_PROCESSED;
}

static int MenuCustom_Format(UINT32 uiMessage, UINT32 uiParam)
{
    Ux_OpenWindow(&UIMenuWndSetupFormatCtrl, 0);
    return TMF_PROCESSED;
}

static int MenuCustom_Default(UINT32 uiMessage, UINT32 uiParam)
{
    Ux_OpenWindow(&UIMenuWndSetupDefaultSettingCtrl, 0);
    return TMF_PROCESSED;
}

static int MenuCustom_Version(UINT32 uiMessage, UINT32 uiParam)
{
    Ux_OpenWindow(&UIMenuWndSetupVersionCtrl, 0);
    return TMF_PROCESSED;
}

// Setup Menu Items
TMDEF_BEGIN_ITEMS(SETUP)
    TMDEF_ITEM_TEXTID(WIFI)
    TMDEF_ITEM_CUSTOM(DATE_TIME, MenuCustom_DateTime)
    #if(AUTOPWROFF_FUNCTION == ENABLE)
    //TMDEF_ITEM_TEXTID(AUTO_POWER_OFF)
    #endif

    #if(BEEP_FUNCTION == ENABLE)
    	TMDEF_ITEM_TEXTID(BEEP)
    #endif
    TMDEF_ITEM_TEXTID(LANGUAGE)
    #if (TV_FUNC == ENABLE)
    //TMDEF_ITEM_TEXTID(TV_MODE)
    #endif
    TMDEF_ITEM_TEXTID(FREQUENCY)
    //TMDEF_ITEM_TEXTID(SENSOR_ROTATE)
    TMDEF_ITEM_CUSTOM(FORMAT, MenuCustom_Format)
    TMDEF_ITEM_CUSTOM(DEFAULT, MenuCustom_Default)
    TMDEF_ITEM_CUSTOM(VERSION, MenuCustom_Version)
TMDEF_END_ITEMS()

// --------------------------------------------------------------------------
// PAGES
// --------------------------------------------------------------------------
// Setup Menu Pages
TMDEF_BEGIN_PAGES(SETUP)
    TMDEF_PAGE_TEXT_ICON(SETUP)
TMDEF_END_PAGES()

TMDEF_EMNU(gSetupMenu, SETUP, Setup_MenuCallback)

// --------------------------------------------------------------------------
// Menu Callback
// --------------------------------------------------------------------------
extern BOOL CurrentRateBeforWIFI_onFlag;
int Setup_MenuCallback(UINT32 uiMessage, UINT32 uiParam)
{
    UINT16  uwItemId;
    UINT16  uwOption;

    if (uiMessage == TMM_CONFIRM_OPTION)
    {
        uwItemId = LO_WORD(uiParam);
        uwOption = HI_WORD(uiParam);

        switch (uwItemId)
        {
        #if(AUTOPWROFF_FUNCTION == ENABLE)
        case IDM_AUTO_POWER_OFF:
            //Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_POWEROFF, 1, uwOption);
            break;
	#endif
	#if(BEEP_FUNCTION == ENABLE)
        case IDM_BEEP:
            Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_BEEPKEY, 1, uwOption);
            break;
	#endif
        case IDM_LANGUAGE:
            Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_LANGUAGE, 1, uwOption);
            break;

        case IDM_TV_MODE:
          //  Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_TVFORMAT, 1, uwOption);
            break;

        case IDM_FREQUENCY:
            Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_FREQ, 1, uwOption);
            break;

        case IDM_SENSOR_ROTATE:
            Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_SENSOR_ROTATE, 1, uwOption);
            break;

        case IDM_WIFI:
            //Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_WIFI, 1, uwOption);
            if (uwOption ==WIFI_ON)
            {
                if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_NG)
                {
                    if(CheckWiFiMapTbl()!=E_OK)
                    {
                        UI_SetData(FL_WIFI_LINK,WIFI_LINK_NG);
                        return TMF_PROCESSED;
                    }
			 if(UI_GetData(FL_MOVIE_RATE) == MOVIE_RATE_HIGH)
                  	{
                  	      CurrentRateBeforWIFI_onFlag = TRUE;
                  		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_RATE_SET, 1, MOVIE_RATE_NORMAL);
				Delay_DelayMs(100);		
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
                if (UI_GetData(FL_WIFI_LINK) == WIFI_LINK_OK)
                {
                    UI_SetData(FL_WIFI_LINK,WIFI_LINK_DISCONNECTING);
                    Ux_SendEvent(0,NVTEVT_EXE_WIFI_STOP,0);
                }                
            }
            break;
        }
    }

    return TMF_PROCESSED;
}
