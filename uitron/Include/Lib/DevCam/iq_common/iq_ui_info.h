#ifndef _IQ_UI_INFOR_H_
#define _IQ_UI_INFOR_H_

#include "Type.h"
#include "ipl_utility.h"

#define IQ_UI_INFOR_ERR   0xFFFFFFFF

typedef struct _IQ_UI_INFO_TAB {
	UINT32 value;
	UINT32 max_value;
} IQ_UI_INFO_TAB;

/**
    IQ informatin selection index(iq_set_ui_info() or iq_get_ui_info())
*/
typedef enum _IQ_UI_INFO {
	IQ_UI_SHARPNESS,              	///<Sharpness, data type #IQ_SHARPNESS
	IQ_UI_SATURATION,             	///<Saturation, data type #IQ_SATURATION
	IQ_UI_CONTRAST,               	///<Contrast, data type #IQ_CONTRAST
	IQ_UI_IMAGEEFFECT,            	///<Color effect, data type #IQ_IMAGEEFFECT
	IQ_UI_GDCCOMP,                	///<prv GDC on/off, data type #IQ_GDCCOMP
	IQ_UI_CCID,                   	///<Image effect "selective color" index, data type #IQ_CCID
	IQ_UI_IRCUT,                  	///<IR Cut on/off, data type #IQ_IRCUT
	IQ_UI_IPPNR,                  	///<IPL Flow select, data type #IQ_NR
	IQ_UI_IPPEDGE,                	///<IPL Flow select, data type #IQ_EDGE
	IQ_UI_BLC,                    	///<BackLight Compensation mode on/off, data type #IQ_BLC
	IQ_UI_BLC_LEVEL,              	///<BackLight Compensation Level, data type #IQ_BLC_LEVEL
	IQ_UI_HUE,                    	///<HUE, data type #IQ_HUE
	IQ_UI_IPC_MODE,					///<IPC mode on/off, data type #IQ_IPC
	IQ_UI_USER_GAMMA_MODE,        	///<USER GAMMA, data type #IQ_USER_GAMMA_MODE
	IQ_UI_USER_CC,                	///<USER CC, Data type #IQ_USER_CC
	IQ_UI_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_UI_INFO)
} IQ_UI_INFO;

/**
    Sharpness
*/
typedef enum _IQ_SHARPNESS_VALSE {
	IQ_SHARPNESS_N1      = 25,    ///< Sharpness 25
	IQ_SHARPNESS_NORMAL  = 50,    ///< Sharpness 50
	IQ_SHARPNESS_P1      = 75,    ///< Sharpness 75
	IQ_SHARPNESS_MAX_CNT = 101,
	ENUM_DUMMY4WORD(IQ_SHARPNESS)
} IQ_SHARPNESS_VALUE;

/**
    Saturation
*/
typedef enum _IQ_SATURATION_VALUE {
	IQ_SATURATION_N1      = 25,    ///< Saturation 25
	IQ_SATURATION_NORMAL  = 50,    ///< Saturation 50
	IQ_SATURATION_P1      = 75,    ///< Saturation 75
	IQ_SATURATION_MAX_CNT = 101,
	ENUM_DUMMY4WORD(IQ_SATURATION)
} IQ_SATURATION_VALUE;

/**
    Contrast
*/
typedef enum _IQ_CONTRAST_VALUE {
	IQ_CONTRAST_N1       = 25,    ///< Contrast 25
	IQ_CONTRAST_NORMAL   = 50,    ///< Contrast 50
	IQ_CONTRAST_P1       = 75,    ///< Contrast 75
	IQ_CONTRAST_MAX_CNT  = 101,
	ENUM_DUMMY4WORD(IQ_CONTRAST)
} IQ_CONTRAST_VALUE;

/**
    Image effect
*/
typedef enum _IQ_IMAGEEFFECT {
	IQ_IMAGEEFFECT_OFF,            
	IQ_IMAGEEFFECT_BW,                 
	IQ_IMAGEEFFECT_SEPIA,              
	IQ_IMAGEEFFECT_VIVID,              
	IQ_IMAGEEFFECT_NEUTRAL,            
	IQ_IMAGEEFFECT_LOWSHARPING,        
	IQ_IMAGEEFFECT_ROCK,               
	IQ_IMAGEEFFECT_FASION2,            
	IQ_IMAGEEFFECT_CUSTOMMANUAL,       
	IQ_IMAGEEFFECT_RED,                
	IQ_IMAGEEFFECT_GREEN,              
	IQ_IMAGEEFFECT_BLUE,               
	IQ_IMAGEEFFECT_YELLOW,             
	IQ_IMAGEEFFECT_PURPLE,             
	IQ_IMAGEEFFECT_SKETCH,             
	IQ_IMAGEEFFECT_FISHEYE,            
	IQ_IMAGEEFFECT_COLORPENCIL,        
	IQ_IMAGEEFFECT_NEGATIVE_DEFOG,     
	IQ_IMAGEEFFECT_JAPANSTYLE,         
	IQ_IMAGEEFFECT_COOLGREEN,          
	IQ_IMAGEEFFECT_WARMYELLOW,         
	IQ_IMAGEEFFECT_CCID,               
	IQ_IMAGEEFFECT_D2D_SHADING,
	IQ_IMAGEEFFECT_D2D_FANTASY,
	IQ_IMAGEEFFECT_D2D_FISHEYE,
	IQ_IMAGEEFFECT_D2D_MIRROR,
	IQ_IMAGEEFFECT_D2D_ROCK,
	IQ_IMAGEEFFECT_D2D_SKETCH,
	IQ_IMAGEEFFECT_D2D_MINIATURE,
	IQ_IMAGEEFFECT_D2D_SPARKLE,
	IQ_IMAGEEFFECT_GAMMA_Anti_Fog,
	IQ_IMAGEEFFECT_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_IMAGEEFFECT)
} IQ_IMAGEEFFECT;

/**
    GDC
*/
typedef enum _IQ_GDCCOMP {
	IQ_GDCCOMP_OFF,
	IQ_GDCCOMP_ON,
	IQ_GDCCOMP_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_GDCCOMP)
} IQ_GDCCOMP;

/**
    Image effect: select color id
*/
typedef enum _IQ_CCID_ {
	IQ_CCID_NO_EFFECT,
	IQ_CCID_ENHANCE_RED,
	IQ_CCID_ENHANCE_YELLOW,
	IQ_CCID_ENHANCE_GREEN,
	IQ_CCID_ENHANCE_BLUE,
	IQ_CCID_ENHANCE_CYAN,
	IQ_CCID_ENHANCE_ORANGE,
	IQ_CCID_ENHANCE_MAGENTA,
	IQ_CCID_REMOVAL_RED,
	IQ_CCID_REMOVAL_YELLOW,
	IQ_CCID_REMOVAL_GREEN,
	IQ_CCID_REMOVAL_BLUE,
	IQ_CCID_REMOVAL_CYAN,
	IQ_CCID_REMOVAL_ORANGE,
	IQ_CCID_REMOVAL_MAGENTA,
	IQ_CCID_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_CCID)
} IQ_CCID;

/**
    IR cut on/off
*/
typedef enum _IQ_IRCUT {
	IQ_IRCUT_DAY,        
	IQ_IRCUT_NIGHT,       
	IQ_IRCUT_AUTO,       
	IQ_IRCUT_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_IRCUT)
} IQ_IRCUT;

/**
    NR on/off
*/
typedef enum _IQ_NR {
	IQ_NR_OFF,
	IQ_NR_ON,
	IQ_NR_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_NR)
} IQ_NR;

/**
    Edge on/off
*/
typedef enum _IQ_EDGE {
	IQ_EDGE_OFF,   
	IQ_EDGE_ON,       
	IQ_EDGE_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_EDGE)
} IQ_EDGE;

/**
    Back light compensation on/off
*/
typedef enum _IQ_BLC {
	IQ_BLC_OFF,   
	IQ_BLC_ON,       
	IQ_BLC_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_BLC)
} IQ_BLC;

/**
    Back light compensation level
*/
typedef enum _IQ_BLC_LEVEL {
	IQ_BLC_LEVEL_LV0,       
	IQ_BLC_LEVEL_LV1,          
	IQ_BLC_LEVEL_LV2,          
	IQ_BLC_LEVEL_LV3,           
	IQ_BLC_LEVEL_LV4,          
	IQ_BLC_LEVEL_LV5,          
	IQ_BLC_LEVEL_LV6,           
	IQ_BLC_LEVEL_LV7,          
	IQ_BLC_LEVEL_LV8,         
	IQ_BLC_LEVEL_LV9,           
	IQ_BLC_LEVEL_LV10,          
	IQ_BLC_LEVEL_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_BLC_LEVEL)
} IQ_BLC_LEVEL;

/**
    HUE
*/
typedef enum _IQ_HUE {
	IQ_HUE_0       = 0,    ///< HUE Normal
	IQ_HUE_MAX_CNT = 361,
	ENUM_DUMMY4WORD(IQ_HUE)
} IQ_HUE;

/**
    IPC
*/
typedef enum _IQ_IPC {
	IQ_IPC_OFF,   
	IQ_IPC_ON,
	IQ_IPC_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_IPC)
} IQ_IPC;

/**
    User gamma
*/
typedef enum _IQ_USER_GAMMA {
	IQ_USER_GAMMA_LINEAR =   0,    
	IQ_USER_GAMMA_DEFAULT =  1,
	IQ_USER_GAMMA_16 =      16,
	IQ_USER_GAMMA_18 =      18,
	IQ_USER_GAMMA_20 =      20,
	IQ_USER_GAMMA_22 =      22,
	IQ_USER_GAMMA_24 =      24,
	IQ_USER_GAMMA_USER =    99,
	IQ_USER_GAMMA_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_USER_GAMMA_MODE)
} IQ_USER_GAMMA_MODE;

/**
    User CC
*/
typedef enum _IQ_USER_CC {
	IQ_USER_CC_OFF,   
	IQ_USER_CC_AUTO,        
	IQ_USER_CC_MANUAL,
	IQ_USER_CC_MAX_CNT,
	ENUM_DUMMY4WORD(IQ_USER_CC)
} IQ_USER_CC;

extern ER iq_set_ui_info(IPL_PROC_ID id, IQ_UI_INFO index, UINT32 value);
extern UINT32 iq_get_ui_info(IPL_PROC_ID Id, IQ_UI_INFO index);

#endif
