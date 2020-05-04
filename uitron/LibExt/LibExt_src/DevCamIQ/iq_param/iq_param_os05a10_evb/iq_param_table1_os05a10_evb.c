#ifndef _IQ_PARAM_TABLE1_OS05A10_EVB_C_
#define _IQ_PARAM_TABLE1_OS05A10_EVB_C_

#include "iq_param_common_os05a10_evb.h"

////////////////////////////////
//        Engine Ctrl          /
////////////////////////////////
static ENGINE_CTRL e_ctrl =
{
    {ECS_OFF,       NON_SUPPORT},    // 1
    {VIG_OFF,       100},            //0~200,default:100
    {GDC_OFF,       200},            //0~200,default:200(100, same with OFF)
    {CAC_OFF,       NON_SUPPORT},
    {CCM_ON,        NON_SUPPORT},    // 5
    {CC3D_OFF,      NON_SUPPORT},
    {CCTRL_ON,      100, 100, 100},  //sat:0~200;con:0~200;bri:0~200,fedault:100
    {HSV_ON,        0},              //H:0~360,default:0
    {GAMMA_ON,      NON_SUPPORT},
    {Y_CURVE_OFF,   NON_SUPPORT},    // 10
    {EDGE_ON,       100},            //0~200,default:100
    {OUTL_ON,       NON_SUPPORT},
    {RANGE_NR_ON,   100},            //0~200,default:100
    {GBAL_ON,       NON_SUPPORT},
    {LPF_ON,        NON_SUPPORT},    // 15
    {LCA_ON,        NON_SUPPORT},
    {LCA_C_ON,      NON_SUPPORT},
    {LCA_Y_ON,      NON_SUPPORT},
    {TMNR_ON,       NON_SUPPORT},
    {TNR_ON,        5},              // 20   //0~10,default:5
    {LCE_ON, 		NON_SUPPORT},
    {RESERVED_OFF,	NON_SUPPORT},
    {RESERVED_OFF,	NON_SUPPORT},
    {RESERVED_OFF,  NON_SUPPORT},
    {RESERVED_OFF,  NON_SUPPORT},
    {RESERVED_OFF,  NON_SUPPORT},
    {RESERVED_OFF,  NON_SUPPORT},
    {RESERVED_OFF,  NON_SUPPORT},
    {RESERVED_OFF,  NON_SUPPORT},
    {RESERVED_OFF,  NON_SUPPORT},
    {RESERVED_OFF,  NON_SUPPORT},
};

////////////////////////////////
//             SIE             /
////////////////////////////////

//////////////////////
//**  SIE-OB
//////////////////////
static UINT32 ob[TOTAL_GAIN_NUM][5] =
{
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
    {256, 256, 256, 256, 256},
};

////////////////////////////////
//             RHE             /
////////////////////////////////

//////////////////////
//**  RHE-WDR
//////////////////////
static UINT8 wdr_strength[21] = //LV0~20, range: 0 ~ 128, 1x = 64;
{
    64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64
};

static IQS_WDR_LCE_OFFSET wdr_lce_offset =
{
    5,  //for WDR_AUTO Mode
    10, //for WDR_MANUAL Mode
};

static SR_WDR_GCE_PARAM gce_strength[TOTAL_GAIN_NUM] = //sth_range: 0 ~ 128, 0 = 1X
{   //only work on WDR_AUTO and WDR_MANUAL Mode
    //dark, bright
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};

//////////////////////
//**  RHE-LCE
//////////////////////
static IQS_LCE lce_strength[TOTAL_GAIN_NUM] =
{
    //level(range: 0 ~ 128, 0 = OFF), clamp (range: 64 ~ 255, 64 = OFF)
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
    {0, 255},
};

////////////////////////////////
//             IFE             /
////////////////////////////////

//////////////////////
//**  IFE-Outlier
//////////////////////
static UINT32 outl_bri[TOTAL_GAIN_NUM][5] =
{
    {2500, 3000, 3500, 4095, 4095},
    {1800, 2800, 3300, 3895, 3895},
    {1300, 2300, 2800, 3395, 3395},
    {1000, 2000, 2500, 3095, 3095},
    {500, 1500, 2000, 2595, 2595},
    {250, 1250, 1750, 2345, 2345},
    {232, 852, 1352, 1740, 1947},
    {32, 64, 128, 512, 1024},
    {32, 360, 747, 1347, 1347},
    {532, 771, 1272, 1844, 3043},
    {410, 595, 982, 1424, 2350},//ISO12800
    {410, 595, 982, 1424, 2350},
};

static UINT32 outl_dark[TOTAL_GAIN_NUM][5] =
{
    {2500, 3000, 3500, 4095, 4095},
    {1800, 2800, 3300, 3895, 3895},
    {1300, 2300, 2800, 3395, 3395},
    {1000, 2000, 2500, 3095, 3095},
    {500, 1500, 2000, 2595, 2595},
    {250, 1250, 1750, 2345, 2345},
    {150, 1150, 1650, 2245, 2245},
    {100, 750, 1250, 1845, 1845},
    {32, 360, 833, 1347, 1347},
    {532, 771, 1272, 1844, 3043},
    {410, 595, 982, 1424, 2350},//ISO102400
    {410, 595, 982, 1424, 2350},
};

static UINT32 outl_cnt[TOTAL_GAIN_NUM][2] =
{
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
};

static IFE_OUTL outl_set[TOTAL_GAIN_NUM] =
{
    //BrightThres,      DarkThres,          OutlCnt,   Weight, DarkOfs, BrightOfs
	{(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
    {(UINT32*)outl_bri, (UINT32*)outl_dark, (UINT32*)outl_cnt, 0, 0, 0},
};

//////////////////////
//**  IFE-Spatial
//////////////////////
static UINT32 spatial_w[TOTAL_GAIN_NUM][6] =
{
	{31, 23, 17, 9, 7, 3},
	{31, 23, 17, 9, 7, 3},
	{31, 23, 17, 9, 7, 3},//ISO400
    {31, 23, 17, 9, 7, 3},
    {31, 23, 17, 9, 7, 3},
    {31, 23, 17, 9, 7, 3},//ISO3200
    {31, 23, 17, 9, 7, 3},
    {31, 23, 17, 9, 7, 3},//ISO12800
    {31, 23, 17, 9, 7, 3},
    {31, 23, 17, 9, 7, 3},
    {31, 23, 17, 9, 7, 3},//ISO102400
    {31, 23, 17, 9, 7, 3},
};

static Spatial_Filter spatial[TOTAL_GAIN_NUM] =
{
// sOnlyEn, sOnlyFiltLeng, pWeight
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
    {DISABLE, Filt_3x3, (UINT32*)spatial_w},
};

//////////////////////
//**  IFE-Range
//////////////////////
static UINT32 range_a_thr[TOTAL_GAIN_NUM][6] =
{
    {0, 3, 4, 6, 7, 9},
    {0, 3, 4, 6, 7, 9},
    {0, 3, 4, 6, 7, 9},
    {0, 4, 6, 8, 9, 13},
    {0, 9, 10, 11, 12, 13},
    {0, 4, 6, 8, 9, 13},
    {0, 16, 20, 23, 26, 35},
    {0, 16, 23, 28, 32, 46},
    {0, 31, 44, 55, 63, 89},
    {0, 38, 54, 66, 76, 108},
    {0, 43, 87, 130, 172, 216},
    {0, 102, 207, 309, 411, 516},
};

static UINT32 range_a_lut[TOTAL_GAIN_NUM][17] =
{
    {0, 4, 7, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
    {0, 7, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 18, 19, 20, 20, 21},
    {0, 13, 16, 19, 21, 23, 25, 27, 28, 30, 31, 33, 34, 35, 37, 38, 39},
    {0, 14, 18, 20, 23, 25, 27, 29, 31, 32, 34, 36, 37, 38, 40, 41, 42},
    {0, 16, 20, 23, 27, 30, 32, 35, 37, 39, 41, 42, 44, 46, 48, 49, 50},
    {0, 20, 24, 28, 32, 35, 38, 40, 43, 45, 47, 49, 51, 53, 55, 57, 59},
    {0, 18, 26, 31, 36, 41, 45, 48, 52, 55, 58, 61, 63, 66, 68, 71, 73},
    {0, 26, 37, 45, 52, 59, 64, 69, 74, 79, 83, 87, 91, 95, 98, 102, 105},
    {0, 17, 24, 30, 35, 39, 43, 46, 49, 52, 55, 58, 60, 63, 65, 68, 70},
    {0, 30, 42, 51, 60, 67, 73, 79, 84, 90, 94, 99, 103, 108, 112, 116, 120},
    {0, 17, 40, 57, 77, 86, 93, 102, 111, 113, 118, 122, 130, 136, 144, 156, 165},//ISO102400
    {0, 39, 96, 135, 183, 204, 222, 243, 264, 270, 279, 291, 309, 324, 342, 372, 393},
};

static UINT32 range_b_thr[TOTAL_GAIN_NUM][6] =
{
    {0, 4, 8, 12, 16, 18},
    {0, 4, 8, 12, 16, 20},
    {0, 6, 14, 20, 26, 32},
    {0, 10, 20, 28, 38, 48},
    {0, 16, 32, 48, 64, 82},
    {0, 24, 50, 74, 98, 124},
    {0, 24, 50, 74, 98, 124},
    {0, 58, 116, 174, 232, 290},
    {0, 58, 116, 174, 232, 290},
    {0, 58, 116, 174, 232, 290},
    {0, 38, 76, 114, 152, 188},
    {0, 38, 76, 114, 152, 188},
};

static UINT32 range_b_lut[TOTAL_GAIN_NUM][17] =
{
    {0, 3, 8, 10, 12, 14, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35},
    {0, 3, 9, 11, 13, 16, 18, 20, 22, 25, 27, 29, 31, 34, 36, 38, 40},
    {0, 5, 12, 15, 18, 20, 23, 26, 29, 31, 34, 37, 40, 43, 45, 48, 51},
    {0, 7, 17, 21, 25, 28, 32, 36, 40, 43, 47, 51, 55, 58, 62, 66, 70},
    {0, 11, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71, 76, 81, 86, 90, 95},
    {0, 16, 38, 45, 52, 59, 66, 73, 80, 87, 93, 100, 107, 114, 121, 128, 135},
    {0, 26, 61, 70, 78, 87, 96, 104, 113, 122, 130, 139, 148, 157, 165, 174, 183},
    {0, 33, 72, 80, 87, 94, 101, 108, 115, 122, 130, 137, 144, 151, 158, 165, 172},
    {0, 33, 72, 80, 87, 94, 101, 108, 115, 122, 130, 137, 144, 151, 158, 165, 172},
    {0, 33, 72, 80, 87, 94, 101, 108, 115, 122, 130, 137, 144, 151, 158, 165, 172},
    {0, 26, 67, 82, 97, 111, 126, 141, 155, 170, 185, 199, 214, 229, 244, 258, 273},
    {0, 26, 67, 82, 97, 111, 126, 141, 155, 170, 185, 199, 214, 229, 244, 258, 273},
};

static RangeCFGB range_b[TOTAL_GAIN_NUM] =
{
    //pThres,                  pThLut,            BilatThEn, BilatTh1, BilatTh2
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 15, 17}},
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 22, 24}},
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 35, 40}},//ISO400
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 77, 92}},
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 64, 128}},
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 129, 154}},
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 100, 143}},
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 243, 281}},//ISO12800
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 335, 402}},
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 503, 603}},
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 1005, 906}},//ISO102400
    {(UINT32*)range_b_thr, (UINT32*)range_b_lut, {TRUE, 1005, 906}},
};

//////////////////////
//**  IFE-CLAMP
//////////////////////
static RANGE_FILT_CLAMP_PARAM filter_clamp[TOTAL_GAIN_NUM] =
{
    //clamp{clamp_Th,Mul,Dlt}, bilat_w, Rth_w, Bin, BitDither}
    {{75, 100, 0}, 0, 0, 0, 0},
    {{75, 80, 0}, 0, 0, 0, 0},
    {{70, 80, 0}, 0, 0, 0, 0},
    {{70, 80, 0}, 0, 0, 0, 0},
    {{70, 80, 0}, 0, 0, 0, 0},
    {{64, 70, 0}, 0, 0, 0, 0},
    {{50, 64, 0}, 0, 0, 0, 0},
    {{32, 38, 0}, 0, 0, 0, 0},
    {{48, 80, 0}, 0, 0, 0, 0},
    {{48, 64, 0}, 0, 0, 0, 0},
    {{30, 64, 0}, 0, 0, 0, 0},
    {{30, 64, 0}, 0, 0, 0, 0},
};

//////////////////////
//**  IFE-Vig
//////////////////////
static IQS_VIG_CENTER_RATIO vig_center =
{
    500, 500
};

static IQS_VIG_SET vig =
{
    VIG_TAB_GAIN_2X, {0, 1, 4, 7, 10, 13, 23, 36, 57, 82, 112, 144, 198, 259, 375, 586, 1023}
};

static IQS_VIG_ISO_TH vig_iso_th =
{
    400, 1600
};

//////////////////////
//**  IFE-Gbal
//////////////////////
static UINT8 gbal_s_tab[TOTAL_GAIN_NUM][17] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static UINT8 gbal_d_tab[TOTAL_GAIN_NUM][17] =
{
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static IFE_GBAL gbal[TOTAL_GAIN_NUM] =
{
    //Thres,pGbalStab,            pGbalDtab,    uiGbalSmtThr
    {3, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {3, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {3, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {3, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {4, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {7, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {9, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {16, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {5, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {8, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {8, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
    {8, (UINT8*)gbal_s_tab, (UINT8*)gbal_d_tab, 0},
};

//////////////////////
//**  IFE-RBFill
//////////////////////
static UINT8 rbfill_luma_tab[TOTAL_GAIN_NUM][17] =
{
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4},
    {0, 16, 24, 27, 27, 28, 30, 31, 31, 30, 29, 28, 28, 27, 26, 12, 4}
};

static UINT8 rbfill_ratio_tab[TOTAL_GAIN_NUM][32] =
{
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0},
    {31, 31, 31, 31, 31, 31, 30, 30, 29, 28, 24, 20, 16, 12, 10,  8,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  3,  2,  1,  0}
};

static IFE_RBFILL rbfill[TOTAL_GAIN_NUM] =
{
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1},
    {(UINT8*)rbfill_luma_tab, (UINT8*)rbfill_ratio_tab, 1}
};

////////////////////////////////
//             IPE             /
////////////////////////////////

//////////////////////
//**  IPE-Edge EXT
//////////////////////
static INT16 edge_kernel[TOTAL_GAIN_NUM][12] =
{
    //eext0 ~ eext9, eextdiv
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
    {0x017c, 0x002a, 0x03b0, 0x03e2, 0x03dd, 0x0004, 0x000a, 0x000a, 0x0004, 0x0001, 0x000a, 0x0004},
};

static UINT8 edir_tab[TOTAL_GAIN_NUM][8]=
{
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8},
};

static IPE_DEE edir_ext[TOTAL_GAIN_NUM] =
{
   //YDRange,uiYDMaxTh,PndAdjEn,uiPndShft,uiES,EdirSel
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
    {IPE_YDR_7x7, 22, DISABLE, 3, 2, KER_SEL_A},
};

static IPE_DirScorCal score_tab[TOTAL_GAIN_NUM] =
{
    //iA0; iB0; iC0; uiD0; iA1; iB1; iC1; uiD1; iA2; iB2; iC2; uiD2;
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
    {   3,  15,  15,    0,   5,   1,   1,    0,   3,   0,  15,   0},
};

static IPE_DirScorCalTh score_th[TOTAL_GAIN_NUM] =
{
    //uiScoreTh0~3
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},
    {63, 0, 63, 0},//ISO102400
    {63, 0, 63, 0},
};

static IPE_KAEdgeW ewa[TOTAL_GAIN_NUM] =
{
  //EWKer2DSel, uiAdwt0~5,           iAds0~5
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},  //ISO400
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},  //ISO102400
    {KER_SEL_A, 8, 8, 12, 12, 16, 16, 3, 3, 3, 3, 3, 3},
};

static IPE_KBEdgeW ewb[TOTAL_GAIN_NUM] =
{
    //uiBdwt0~1, iBds0~1, EwKerBOutSel
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
    {1, 1, 2, 2, SEL_AVG_4D},
};

static IPE_EdgeW ewparam[TOTAL_GAIN_NUM] =
{
    //uiEWDir0,1,2, DynEMEn
    {6, 4, 8, 0},
    {6, 6, 8, 0},
    {8, 6, 8, 0},
    {8, 6, 8, 0},
    {10, 8, 10, 0},
    {10, 8, 10, 0},
    {10, 8, 10, 0},
    {10, 8, 10, 0},
    {10, 8, 10, 0},
    {14, 12, 14, 0},
    {14, 14, 14, 0},
    {14, 14, 14, 0},
};

//////////////////////
//**  IPE-Edge Enh
//////////////////////
static IPE_EDGEENH edge_enh[TOTAL_GAIN_NUM] =
{
    //EnhP,EnhN, InvP,  InvN
    {160, 150, FALSE, FALSE},
    {150, 150, FALSE, FALSE},
    {150, 150, FALSE, FALSE},
    {150, 140, FALSE, FALSE},
    {138, 138, FALSE, FALSE},
    {138, 138, FALSE, FALSE},
    {120, 120, FALSE, FALSE},
    {120, 120, FALSE, FALSE},
    {120, 120, FALSE, FALSE},
    {120, 120, FALSE, FALSE},
    {120, 120, FALSE, FALSE},
    {120, 120, FALSE, FALSE},
};

//////////////////////
//**  IPE-Edge Map
//////////////////////
static UINT8 ed_tab[TOTAL_GAIN_NUM][16] =
{
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 255, 255, 255, 255, 255, 255, 255},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 255, 255, 255, 255, 255, 255, 255},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 255, 255, 255, 255, 255, 255, 255},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 255, 255, 255, 240, 220, 200, 180},
    {0, 40, 80, 120, 160, 200, 230, 255, 255, 255, 255, 240, 220, 200, 180, 160},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 224, 192, 170, 154, 144, 136, 128},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 224, 192, 170, 154, 144, 136, 128},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 224, 192, 170, 154, 144, 136, 128},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 224, 192, 170, 154, 144, 136, 128},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 224, 192, 170, 154, 144, 136, 128},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 224, 192, 170, 154, 144, 136, 128},
    {0, 36, 72, 108, 144, 180, 216, 255, 255, 224, 192, 170, 154, 144, 136, 128},
};

static EdgeMap ed_map[TOTAL_GAIN_NUM] =
{
    {EMI_E57 , 0, 128, 0, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 0, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 1, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 1, 2, (UINT32)ed_tab},
    {EMI_E57 , 5, 128, 2, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 2, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 2, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 2, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 2, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 2, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 3, 2, (UINT32)ed_tab},
    {EMI_E57 , 0, 128, 3, 2, (UINT32)ed_tab},
};

static UINT8 es_tab[TOTAL_GAIN_NUM][16] =
{
    {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {0, 32, 48, 64, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {0, 32, 48, 52, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {0, 32, 48, 52, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {0, 32, 48, 52, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {0, 32, 48, 52, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
    {0, 32, 48, 52, 64, 64, 64, 64, 64, 64, 64, 52, 44, 38, 32, 32},
};

static EdgeMapS es_map[TOTAL_GAIN_NUM] =
{
 //EthrL,EthrH, EtabL, EtabH, TAB_TblAddr
    {0,   512,     0,     5, (UINT32)es_tab},
    {0,   512,     0,     5, (UINT32)es_tab},
    {0,   512,     0,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
    {0,   512,     5,     5, (UINT32)es_tab},
};

//////////////////////
//**  IPE-LPF
//////////////////////
static LPF lpf[TOTAL_GAIN_NUM] =
{
   //lpfw,sonlyw,rangeth0,rangeth1,lpfsize
    {4, 0, 4, 8, _5x5},
    {4, 0, 5, 10, _5x5},
    {4, 0, 6, 13, _5x5},//ISO400
    {4, 0, 8, 16, _5x5},
    {4, 0, 8, 16, _5x5},
    {4, 0, 8, 16, _5x5},
    {4, 0, 10, 22, _5x5},
    {4, 0, 10, 22, _5x5},
    {4, 0, 10, 22, _5x5},
    {4, 0, 10, 22, _5x5},
    {4, 0, 10, 22, _5x5},
    {4, 0, 10, 22, _5x5},
};


static INT8 saturation[TOTAL_GAIN_NUM]=
{
    10,
    5,
    -10,
    -10,
    -35,
    -50,
    -50,
    -50,
    -50,
    -50,
    -50,
    -50,
};

static INT8 contrast[TOTAL_GAIN_NUM] =
{
    10,
    10,
    5,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static UINT32 ccon_tab[TOTAL_GAIN_NUM][17] =
{
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128},
    {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128}
};

static IQS_CCTRL_INFO cctrl_info[TOTAL_GAIN_NUM] =
{
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80},
    {CCTRL_SEL_E7, 0x80}
};

////////////////////////////////
//             IFE2            /
////////////////////////////////

//////////////////////
//**  IFE2-ReferenceCenter
//////////////////////
static UINT32 ref_center_y_th[TOTAL_GAIN_NUM][3] =
{
    {1, 2, 3},
    {1, 2, 3},
    {2, 4, 6},
    {6, 9, 12},
    {6, 9, 12},
    {15, 22, 29},
    {15, 22, 29},
    {15, 22, 29},
    {22, 33, 44},
    {44, 66, 88},
    {44, 66, 88},
    {44, 66, 88},
};

static UINT32 ref_center_y_wt[TOTAL_GAIN_NUM][4] =
{
    {8, 4, 2, 1},
    {8, 4, 2, 1},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
};

static IFE2_REFCENT_Set ref_center_y[TOTAL_GAIN_NUM] =
{
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
    {(UINT32)ref_center_y_th, (UINT32)ref_center_y_wt, 31, 9, 6},
};

static UINT32 ref_center_uv_th[TOTAL_GAIN_NUM][3] =
{
    {1, 2, 3},
    {1, 2, 3},
    {2, 4, 6},
    {7, 10, 13},
    {7, 10, 13},
    {10, 15, 18},
    {13, 19, 26},
    {13, 19, 26},
    {13, 19, 26},
    {26, 38, 52},
    {26, 38, 52},
    {26, 38, 52},
};

static UINT32 ref_center_uv_wt[TOTAL_GAIN_NUM][4] =
{
    {8, 4, 2, 1},
    {8, 4, 2, 1},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
    {8, 6, 4, 2},
};

static IFE2_REFCENT_Set ref_center_uv[TOTAL_GAIN_NUM] =
{
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
    {(UINT32)ref_center_uv_th, (UINT32)ref_center_uv_wt, 31, 9, 6},
};

//////////////////////
//**  IFE2-Filter
//////////////////////
static UINT32 ife2filter_y_th[TOTAL_GAIN_NUM][5] =
{
    {1, 2, 3, 4, 5},
    {1, 2, 3, 4, 5},
    {4, 6, 8, 10, 12},
    {8, 11, 14, 17, 20},
    {8, 11, 14, 17, 20},//{15, 22, 29, 36, 43},//{8, 11, 14, 17, 20},//
    {15, 22, 29, 36, 43},//{8, 11, 14, 17, 20},
    {15, 22, 29, 36, 43},//{8, 11, 14, 17, 20},//{22, 33, 44, 55, 66},
    {15, 22, 29, 36, 43},//{8, 11, 14, 17, 20},//{22, 33, 44, 55, 66},
	{22, 33, 44, 55, 66},
	{44, 66, 88, 110, 132},
	{44, 66, 88, 110, 132},
	{44, 66, 88, 110, 132},
};

static UINT32 ife2filter_y_wt[TOTAL_GAIN_NUM][6] =
{
    {16, 8, 4, 2, 1, 0},
    {16, 8, 4, 2, 1, 0},
    {16, 8, 4, 2, 1, 0},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
};

static UINT32 ife2filter_uv_th[TOTAL_GAIN_NUM][5] =
{
    {1, 1, 3, 3, 5},
    {1, 1, 3, 3, 5},
    {6, 8, 10, 12, 14},
    {10, 14, 18, 22, 26},
    {10, 15, 20, 25, 30},
    {10, 14, 18, 21, 25},
    {10, 14, 18, 21, 25},//{13, 19, 26, 32, 39},
    {10, 14, 18, 21, 25},//{13, 19, 26, 32, 39},
	{13, 19, 26, 32, 39},
	{26, 38, 52, 64, 78},
	{26, 38, 52, 64, 78},
	{26, 38, 52, 64, 78},
};

static UINT32 ife2filter_uv_wt[TOTAL_GAIN_NUM][6] =
{
    {16, 16, 8, 8, 4, 4},
    {16, 16, 8, 8, 4, 4},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
    {16, 13, 10, 7, 4, 1},
};

static IQS_IFE2_FILTER ife2filter[TOTAL_GAIN_NUM] =
{
//RepNum,FiltSize,     {uiEdthHV, uiEdthPN},EdgeKernelSize, FiltSetY,                                        FiltSetU,                                                   FiltSetV
    {1, {FLTR_SIZE_9x9, {32, 32}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {32, 32}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {18, 18}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {18, 18}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {14, 14}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {18, 18}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {14, 14}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {14, 14}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {14, 14}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {14, 14}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {14, 14}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
    {1, {FLTR_SIZE_9x9, {14, 14}, EKNL_SIZE_3x3, {(UINT32)ife2filter_y_th, (UINT32)ife2filter_y_wt},  {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}, {(UINT32)ife2filter_uv_th, (UINT32)ife2filter_uv_wt}}},
};

//////////////////////
//**  IFE2-Gray
//////////////////////
static IFE2_GRAY_Statal gray_statical[TOTAL_GAIN_NUM] =
{
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
    {125, 131, 125, 131},
};

////////////////////////////////
//             IME             /
////////////////////////////////

//////////////////////
//**  IME-LCA
//////////////////////
static IME_CHRA_ADAP chroma_adapt[TOTAL_GAIN_NUM] =
{
    //LcaRefWt{RefY,RefUV,OutUV},LcaYinfo{LcaY,LcaYTh,LcaYWtPrc,LcaYWtS,LcaYWtE}, LcaUVinfo{UV, UVTh, UVWtPrc, UVWtS, UVWtE}, SubRatio
    {{0, 0, 0}, {RANGE_8, 0, RANGE_8, 8, 0}, {RANGE_8, 0, RANGE_8, 8, 0}, 25},
    {{8, 8, 4}, {RANGE_8, 0, RANGE_8, 8, 0}, {RANGE_8, 0, RANGE_8, 8, 0}, 25},
    {{8, 8, 4}, {RANGE_8, 0, RANGE_8, 8, 0}, {RANGE_8, 0, RANGE_8, 8, 0}, 25},
    {{8, 8, 4}, {RANGE_8, 0, RANGE_8, 8, 0}, {RANGE_8, 0, RANGE_8, 8, 0}, 25},
    {{10, 10, 6}, {RANGE_8, 0, RANGE_8, 8, 0}, {RANGE_8, 0, RANGE_8, 8, 0}, 25},
    {{14, 14, 6}, {RANGE_8, 0, RANGE_8, 8, 2}, {RANGE_8, 0, RANGE_8, 8, 0}, 25},
    {{18, 18, 10}, {RANGE_8, 0, RANGE_8, 6, 0}, {RANGE_16, 0, RANGE_16, 16, 0}, 25},
    {{22, 24, 12}, {RANGE_8, 0, RANGE_8, 8, 5}, {RANGE_32, 0, RANGE_32, 32, 0}, 25},
    {{18, 18, 12}, {RANGE_8, 0, RANGE_8, 8, 5}, {RANGE_16, 0, RANGE_16, 16, 0}, 25},
    {{18, 18, 12}, {RANGE_16, 0, RANGE_16, 16, 12}, {RANGE_32, 0, RANGE_32, 32, 16}, 25},
    {{18, 18, 12}, {RANGE_16, 0, RANGE_16, 16, 12}, {RANGE_32, 0, RANGE_32, 32, 16}, 25},
    {{18, 18, 12}, {RANGE_16, 0, RANGE_16, 16, 12}, {RANGE_32, 0, RANGE_32, 32, 16}, 25},
};

static IME_CHRA_CADAP chroma_adapt_color[TOTAL_GAIN_NUM] =
{
 //LcaCLREn, LcaRefWt{CentU, CentV}, LcaCLRinfo{LumRng,LumTh,LumWtPrc,LumWtS,LumWtE}
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
	{DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
    {DISABLE,         {128,     128},          {RANGE_8,   0,   RANGE_8,   8,     0}},
};

static IME_CHRA_LADAP chroma_adapt_lum[TOTAL_GAIN_NUM] =
{
  //LcaLumEn, LcaRefWt{RefWt,OutWt}, LcaLuminfo{LumRng, LumTh,LumWtPrc,LumWtS,LumWtE}
    {DISABLE,         {0,        0},           {RANGE_8,    0, RANGE_8,     0,     0}},
    {DISABLE,         {0,        0},           {RANGE_8,    0, RANGE_8,     0,     0}},
    {DISABLE,         {0,        0},           {RANGE_8,    0, RANGE_8,     0,     0}},
    {DISABLE,         {0,        0},           {RANGE_8,    0, RANGE_8,     0,     0}},
    {DISABLE,         {16,      24},           {RANGE_8,    0, RANGE_8,     0,     6}},
    {ENABLE,          {14,      24},           {RANGE_8,    0, RANGE_8,     0,     6}},
    {ENABLE,          {24,      24},           {RANGE_8,    0, RANGE_8,     0,     6}},
    {ENABLE,          {24,      24},           {RANGE_8,    0, RANGE_8,     0,     6}},
    {ENABLE,          {24,      24},           {RANGE_8,    0, RANGE_8,     0,     6}},
    {ENABLE,          {24,      24},           {RANGE_8,    0, RANGE_8,     0,     6}},
    {ENABLE,          {24,      24},           {RANGE_8,    0, RANGE_8,     0,     6}},
    {ENABLE,          {24,      24},           {RANGE_8,    0, RANGE_8,     0,     6}},
};

//////////////////////
//**  IME-ChromaSuppression
//////////////////////
static UINT32 chroma_supp_w_y[TOTAL_GAIN_NUM][16] =
{
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
};

static UINT32 chroma_supp_w_c[TOTAL_GAIN_NUM][16] =
{
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
    {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
};

static IME_ChromaSupp chroma_supp[TOTAL_GAIN_NUM] =
{
    //ModeSel,      Cetner,     Step,   puiWeightY,                      puiWeightC
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
    {0,DBCS_DK_MODE, {128, 128}, {0, 0}, (UINT32*)chroma_supp_w_y, (UINT32*)chroma_supp_w_c},
};

//////////////////////
//**  IME-TMNR
//////////////////////
static IME_HAL_TMNR_INFO tmnr_info_1x =
{
    0, 1, 1, 1, 1, 1, 40,
    {6, 10, 4, 8},
    2, 2, 8, 8,
    {{{20, 10, 10, 142},{20, 10, 10, 162},{20, 10, 10, 162},{20, 8, 8, 152},{20, 8, 8, 152},{20, 8, 8, 72},{20, 8, 8, 72},{20, 8, 8, 62}},
    {{48, 10},{60, 9},{67, 11},{64, 11},{62, 10},{54, 10},{53, 12},{53, 12}},
    {{48, 10},{60, 9},{67, 11},{64, 11},{62, 10},{54, 10},{53, 12},{53, 12}}},
    {11, 33, 55, 77},
    {11, 24, 35, 45},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};
static IME_HAL_TMNR_INFO tmnr_info_2x =
{
    0, 1, 1, 1, 1, 1, 40,
    {6, 10, 4, 8},
    3, 2, 8, 8,
    {{{50, 12, 10, 100},{50, 12, 10, 160},{50, 12, 10, 160},{50, 10, 8, 150},{50, 10, 8, 140},{50, 10, 8, 100},{50, 10, 8, 70},{50, 10, 8, 60}},
    {{115, 10},{135, 10},{135, 10},{135, 10},{95, 10},{65, 10},{55, 10},{45, 10}},
    {{115, 10},{135, 10},{135, 10},{135, 10},{95, 10},{65, 10},{55, 10},{45, 10}}},
    {11, 33, 55, 77},
    {11, 24, 35, 45},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};
static IME_HAL_TMNR_INFO tmnr_info_4x =
{
    0, 1, 1, 1, 1, 1, 40,
    {6, 10, 4, 8},
    2, 2, 8, 8,
    {{{80, 12, 14, 120},{80, 12, 14, 170},{80, 12, 14, 190},{80, 10, 14, 190},{80, 10, 14, 180},{80, 10, 14, 130},{80, 10, 14, 100},{80, 10, 14, 100}},
    {{121, 10},{121, 10},{121, 10},{121, 10},{121, 10},{121, 10},{121, 10},{121, 10}},
    {{121, 10},{121, 10},{121, 10},{121, 10},{121, 10},{121, 10},{121, 10},{121, 10}}},
    {11, 33, 55, 77},
    {13, 32, 46, 57},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};
static IME_HAL_TMNR_INFO tmnr_info_8x =
{
    0, 1, 1, 1, 1, 1, 40,
    {4, 8, 3, 7},
    3, 1, 16, 16,
    {{{104, 12, 18, 280},{104, 12, 18, 280},{104, 12, 18, 280},{100, 10, 17, 270},{100, 10, 16, 260},{100, 10, 16, 180},{100, 10, 16, 150},{100, 10, 16, 100}},
    {{145, 10},{153, 12},{156, 12},{157, 12},{158, 12},{155, 12},{143, 10},{143, 10}},
    {{145, 10},{153, 12},{156, 12},{157, 12},{158, 12},{155, 12},{143, 10},{143, 10}}},
    {11, 33, 55, 77},
    {11, 24, 35, 45},
    {40, 14, 7, 3},
    {13, 32, 46, 57},
    {36, 20, 13, 8}
};
static IME_HAL_TMNR_INFO tmnr_info_16x =
{
    0, 1, 1, 1, 1, 1, 40,
    {4, 8, 4, 8},
    2, 1, 16, 16,
    {{{102, 12, 18, 280},{102, 12, 18, 330},{102, 12, 18, 330},{100, 10, 17, 280},{98, 10, 16, 280},{98, 10, 16, 210},{98, 10, 16, 180},{98, 10, 16, 150}},
    {{150, 10},{154, 12},{156, 13},{156, 13},{156, 13},{155, 14},{149, 12},{149, 12}},
    {{150, 10},{154, 12},{156, 13},{156, 13},{156, 13},{155, 14},{149, 12},{149, 12}}},
    {11, 33, 55, 77},
    {13, 32, 46, 57},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {36, 20, 13, 8}
};
static IME_HAL_TMNR_INFO tmnr_info_32x =
{
    0, 1, 1, 1, 1, 1, 40,
    {3, 8, 4, 8},
    2, 1, 16, 16,
    {{{145, 16, 19, 380},{145, 16, 19, 380},{145, 16, 19, 380},{143, 14, 18, 380},{143, 14, 17, 350},{143, 14, 17, 280},{143, 14, 17, 210},{143, 14, 17, 180}},
    {{148, 14},{168, 18},{148, 18},{138, 14},{138, 14},{138, 14},{138, 14},{138, 14}},
    {{148, 14},{168, 18},{148, 18},{138, 14},{138, 14},{138, 14},{138, 14},{138, 14}}},
    {11, 33, 55, 77},
    {13, 28, 40, 53},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {36, 20, 13, 8}
};
static IME_HAL_TMNR_INFO tmnr_info_64x =
{
    0, 1, 1, 1, 1, 1, 40,
    {4, 8, 4, 8},
    2, 1, 16, 16,
    {{{160, 25, 20, 540},{160, 25, 20, 540},{160, 25, 19, 540},{160, 25, 18, 540},{144, 23, 18, 510},{144, 23, 18, 410},{144, 23, 18, 360},{144, 23, 17, 310}},
    {{163, 15},{163, 15},{163, 15},{163, 15},{163, 15},{163, 15},{163, 15},{163, 15}},
    {{163, 15},{163, 15},{163, 15},{163, 15},{163, 15},{163, 15},{163, 15},{163, 15}}},
    {11, 33, 55, 77},
    {13, 32, 50, 67},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};
static IME_HAL_TMNR_INFO tmnr_info_128x =
{
    0, 1, 1, 1, 1, 1, 40,
    {4, 10, 3, 8},
    2, 1, 16, 16,
    {{{177, 35, 24, 780},{177, 35, 24, 830},{177, 35, 24, 830},{177, 33, 23, 830},{161, 33, 22, 780},{161, 33, 22, 680},{161, 33, 22, 520},{161, 33, 22, 480}},
    {{231, 24},{251, 25},{257, 26},{239, 24},{225, 20},{207, 22},{229, 22},{229, 22}},
    {{231, 24},{251, 25},{257, 26},{239, 24},{225, 20},{207, 22},{229, 22},{229, 22}}},
    {11, 33, 55, 77},
    {13, 32, 50, 67},
    {38, 16, 9, 5},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};

static IME_HAL_TMNR_INFO tmnr_info_256x =
{
    0, 1, 1, 1, 1, 1, 40,
    {8, 12, 4, 8},
    3, 1, 16, 16,
    {{{64, 18, 6, 720},{64, 18, 6, 720},{64, 18, 6, 720},{64, 16, 5, 680},{64, 16, 5, 680},{64, 12, 5, 650},{64, 12, 5, 650},{64, 12, 5, 650}},
    {{66, 23},{98, 30},{105, 33},{78, 29},{57, 22},{64, 25},{64, 25},{64, 25}},
    {{66, 23},{98, 30},{105, 33},{78, 29},{57, 22},{64, 25},{64, 25},{64, 25}}},
    {11, 33, 55, 77},
    {11, 24, 35, 45},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};
static IME_HAL_TMNR_INFO tmnr_info_512x =
{
    0, 1, 1, 1, 1, 1, 40,
    {12, 18, 8, 16},
    3, 1, 16, 16,
    {{{64, 20, 10, 850},{64, 20, 10, 850},{64, 20, 10, 850},{64, 16, 8, 800},{64, 16, 6, 800},{64, 16, 6, 750},{64, 16, 6, 750},{64, 16, 6, 750}},
    {{66, 24},{98, 24},{105, 24},{78, 24},{57, 24},{64, 24},{64, 24},{64, 24}},
    {{66, 24},{98, 24},{105, 24},{78, 24},{57, 24},{64, 24},{64, 24},{64, 24}}},
    {11, 33, 55, 77},
    {11, 24, 35, 45},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};
static IME_HAL_TMNR_INFO tmnr_info_1024x =
{
    0, 1, 1, 1, 1, 1, 40,
    {12, 18, 8, 16},
    6, 6, 16, 16,
    {{{64, 32, 10, 1000},{64, 32, 10, 1000},{64, 32, 10, 1000},{64, 32, 8, 900},{64, 28, 8, 850},{64, 28, 8, 850},{64, 28, 8, 850},{64, 28, 8, 850}},
    {{160, 30},{160, 30},{160, 30},{140, 30},{140, 30},{140, 30},{100, 30},{84, 30}},
    {{160, 30},{160, 30},{160, 30},{140, 30},{140, 30},{140, 30},{100, 30},{84, 30}}},
    {11, 33, 55, 77},
    {18, 32, 42, 49},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};
static IME_HAL_TMNR_INFO tmnr_info_2048x =
{
    0, 1, 1, 1, 1, 1, 40,
    {8, 16, 8, 16},
    10, 12, 16, 16,
    {{{120, 32, 24, 32},{120, 40, 24, 32},{120, 40, 24, 64},{120, 40, 24, 64},{120, 40, 24, 64},{120, 40, 24, 64},{120, 40, 24, 64},{120, 40, 24, 64}},
    {{66, 23},{98, 30},{105, 33},{78, 29},{57, 22},{64, 25},{64, 25},{64, 25}},
    {{66, 23},{98, 30},{105, 33},{78, 29},{57, 22},{64, 25},{64, 25},{64, 25}}},
    {11, 33, 55, 77},
    {18, 32, 42, 49},
    {40, 14, 7, 3},
    {11, 33, 55, 77},
    {37, 19, 11, 7}
};

static IME_HAL_TMNR_INFO* tmnr_info[TOTAL_GAIN_NUM] =
{
    &tmnr_info_1x,
    &tmnr_info_2x,
    &tmnr_info_4x,
    &tmnr_info_8x,
    &tmnr_info_16x,
    &tmnr_info_32x,
    &tmnr_info_64x,
    &tmnr_info_128x,
    &tmnr_info_256x,
    &tmnr_info_512x,
    &tmnr_info_1024x,
    &tmnr_info_2048x
};

////////////////////////////////
//            Codec            /
////////////////////////////////

////////////////////
// SIE-ECS
////////////////////
static SIE_EmbeddedCS ecs = {ECS_D2F8, ENABLE, ENABLE, _BIT_0_1};
static UINT32 ecs_tab[4225] =
{

    0x11243100,0x11143500,0x11043500,0x10F43100,0x10E42D00,0x10D42100,0x10E42900,0x10F42100,0x10F42100,0x10C41D00,0x10D41900,0x10E41D00,0x10D41D00,0x10D41D00,0x10B42100,0x10B42100,0x10C42100,0x10C42100,0x10C42500,0x10A42100,0x10A41D00,0x10941D00,0x10941D00,0x10A42100,0x10941900,0x10841D00,0x10941D00,0x10841D00,0x10842100,0x10842100,0x10741D00,0x10841D00,0x10842100,0x10741900,0x10942100,0x10841D00,0x10742100,0x10942100,0x10742100,0x10941D00,0x10942100,0x10842100,0x10942100,0x10641D00,0x10841900,0x10942500,0x10741D00,0x10741D00,0x10941D00,0x10A42100,0x10942100,0x10A42100,0x10A41D00,0x10941900,0x10A41D00,0x10B42500,0x10C42100,0x10C42D00,0x10D42D00,0x10B42D00,0x10D43100,0x10D42D00,0x10D43900,0x10D43900,0x10F44500,
    0x11142500,0x11142500,0x11042500,0x11042500,0x10E42100,0x10E41900,0x10E41500,0x10E41500,0x10E41500,0x10E41100,0x10D41100,0x10D41100,0x10C41500,0x10C41100,0x10C41500,0x10B41500,0x10B41100,0x10C41500,0x10A41100,0x10941100,0x10941100,0x10941500,0x10A41500,0x10841100,0x10A41500,0x10A41500,0x10841500,0x10941500,0x10841500,0x10841500,0x10741100,0x10841500,0x10841500,0x10741100,0x10841100,0x10841100,0x10741500,0x10741100,0x10741100,0x10841100,0x10741100,0x10841100,0x10841500,0x10841500,0x10740D00,0x10941500,0x10841100,0x10841500,0x10841100,0x10941500,0x10941500,0x10941100,0x10B41500,0x10A41100,0x10B41500,0x10B41900,0x10B41900,0x10B41900,0x10B41D00,0x10C41D00,0x10C42500,0x10D42900,0x10D42900,0x10E42D00,0x10F42D00,
    0x10F41900,0x10F41900,0x10F41900,0x10E41900,0x10D41100,0x10D41500,0x10C41100,0x10D40D00,0x10D40900,0x10C40500,0x10C40900,0x10B40500,0x10C40900,0x10B40900,0x10940900,0x10940900,0x10A40900,0x10A40D00,0x10940900,0x10940900,0x10740500,0x10840900,0x10840900,0x10740900,0x10740500,0x10740500,0x10640900,0x10640900,0x10640900,0x10640900,0x10740900,0x10640900,0x10640900,0x10640900,0x10640D00,0x10640900,0x10540900,0x10640900,0x10640900,0x10640900,0x10640900,0x10640500,0x10740900,0x10640900,0x10640900,0x10740500,0x10640900,0x10740900,0x10740900,0x10740900,0x10840900,0x10840500,0x10740500,0x10940D00,0x10940900,0x10940900,0x10A41100,0x10A41100,0x10A41100,0x10B41500,0x10C41900,0x10B41900,0x10C42100,0x10D42100,0x10F42500,
    0x11041900,0x10F41900,0x10F41900,0x10D41500,0x10D41100,0x10D41100,0x10C40D00,0x10B40500,0x10B40500,0x10B40500,0x10A40500,0x10B40500,0x10A40900,0x10A40900,0x10940900,0x10940500,0x10840500,0x10840500,0x10840500,0x10840900,0x10740500,0x10740500,0x10740900,0x10740500,0x10640500,0x10640900,0x10640500,0x10540500,0x10540500,0x10540500,0x10540500,0x10640900,0x10540900,0x10540500,0x10540900,0x10540500,0x10440500,0x10540900,0x10540900,0x10440500,0x10440500,0x10540500,0x10440500,0x10640900,0x10640900,0x10640500,0x10640900,0x10640500,0x10540500,0x10640500,0x10740900,0x10840500,0x10740500,0x10840D00,0x10840500,0x10840900,0x10940D00,0x10940D00,0x10940D00,0x10A41500,0x10A41500,0x10C41900,0x10C42100,0x10D42100,0x10C42100,
    0x11041900,0x10F41900,0x10D41500,0x10D41500,0x10C41100,0x10B40D00,0x10D40D00,0x10C40900,0x10A40100,0x10A40500,0x10A40500,0x10A40500,0x10940500,0x10A40900,0x10840900,0x10840900,0x10840900,0x10740900,0x10740500,0x10740900,0x10740500,0x10640500,0x10640900,0x10640500,0x10540500,0x10640900,0x10440500,0x10340100,0x10540900,0x10540900,0x10540900,0x10440500,0x10540500,0x10540500,0x10440500,0x10440900,0x10440900,0x10440500,0x10540D00,0x10540900,0x10440500,0x10540500,0x10440500,0x10540500,0x10540500,0x10540900,0x10540500,0x10540500,0x10540100,0x10640900,0x10640500,0x10640500,0x10640100,0x10840900,0x10740500,0x10840900,0x10840900,0x10940D00,0x10840D00,0x10841100,0x10A41900,0x10A41900,0x10A41900,0x10C41D00,0x10C42100,
    0x10F41900,0x10F41900,0x10E41900,0x10C41500,0x10C41100,0x10B40D00,0x10C40D00,0x10A40900,0x10A40500,0x10A40500,0x10A40500,0x10A40900,0x10840500,0x10840900,0x10840900,0x10740500,0x10840D00,0x10740900,0x10740900,0x10740900,0x10540500,0x10640900,0x10640900,0x10640500,0x10440500,0x10540900,0x10540900,0x10440500,0x10540900,0x10440500,0x10440900,0x10440900,0x10440900,0x10440500,0x10540900,0x10440900,0x10440900,0x10340500,0x10440500,0x10440900,0x10440900,0x10440500,0x10440500,0x10440500,0x10340500,0x10540500,0x10540500,0x10540500,0x10540500,0x10540500,0x10640500,0x10640500,0x10640500,0x10640500,0x10740900,0x10840D00,0x10740900,0x10840D00,0x10841100,0x10941500,0x10A41500,0x10941500,0x10B41D00,0x10C42100,0x10D42500,
    0x10E41500,0x10E41500,0x10E41900,0x10D41900,0x10C41100,0x10A40D00,0x10A40900,0x10B40900,0x10940500,0x10A40500,0x10A40900,0x10940500,0x10840900,0x10840900,0x10840900,0x10740900,0x10640900,0x10740500,0x10740900,0x10640900,0x10640500,0x10640D00,0x10540900,0x10540500,0x10440500,0x10540900,0x10640900,0x10340500,0x10440900,0x10340900,0x10340500,0x10440500,0x10440500,0x10340900,0x10340500,0x10440900,0x10340500,0x10340500,0x10340500,0x10240900,0x10340500,0x10340900,0x10340500,0x10440500,0x10340500,0x10440500,0x10440900,0x10440900,0x10440500,0x10440500,0x10540500,0x10540500,0x10640100,0x10740900,0x10640900,0x10740900,0x10840D00,0x10740D00,0x10740D00,0x10841100,0x10941500,0x10941900,0x10A41900,0x10B41D00,0x10A41900,
    0x11041900,0x10E41500,0x10D41900,0x10C41500,0x10B41100,0x10B41100,0x10940900,0x10A40900,0x10A40500,0x10A40500,0x10840500,0x10840500,0x10840500,0x10840500,0x10740900,0x10740900,0x10740900,0x10740900,0x10540500,0x10540500,0x10540500,0x10540500,0x10440500,0x10440900,0x10540500,0x10440900,0x10440500,0x10340500,0x10540900,0x10340500,0x10340500,0x10340500,0x10340500,0x10340900,0x10340500,0x10340500,0x10340900,0x10340500,0x10240500,0x10340900,0x10340500,0x10340500,0x10340900,0x10340500,0x10440500,0x10540900,0x10340900,0x10340500,0x10440500,0x10540500,0x10440500,0x10440100,0x10640500,0x10640900,0x10640500,0x10640900,0x10640900,0x10840D00,0x10740D00,0x10941100,0x10841100,0x10841500,0x10A41D00,0x10A41D00,0x10B42100,
    0x10F41100,0x10D41500,0x10B41100,0x10C41500,0x10B41100,0x10A40D00,0x10A40D00,0x10940500,0x10940100,0x10840100,0x10840100,0x10740100,0x10740500,0x10640100,0x10740900,0x10640900,0x10540500,0x10540500,0x10540500,0x10540500,0x10540500,0x10340100,0x10540100,0x10440500,0x10440500,0x10340100,0x10340100,0x10340500,0x10440500,0x10440900,0x10240100,0x10340500,0x10340500,0x10340500,0x10240500,0x10340500,0x10340500,0x10240100,0x10240500,0x10340500,0x10240500,0x10240100,0x10240100,0x10340500,0x10340500,0x10340500,0x10340500,0x10340100,0x10340500,0x10440500,0x10440500,0x10440100,0x10440500,0x10540100,0x10540500,0x10540900,0x10640900,0x10640900,0x10740900,0x10941100,0x10741100,0x10841500,0x10941900,0x10941500,0x10B41D00,
    0x10D40D00,0x10C41100,0x10B41100,0x10C41100,0x10B41100,0x10940900,0x10840100,0x10740100,0x10840100,0x10940100,0x10840100,0x10840100,0x10740100,0x10640100,0x10640500,0x10540500,0x10540500,0x10540500,0x10440100,0x10440100,0x10340100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340500,0x10340100,0x10240100,0x10340100,0x10240100,0x10240100,0x10340500,0x10240500,0x10240100,0x10340500,0x10240100,0x10140100,0x10240100,0x10240500,0x10240100,0x10240500,0x10240100,0x10240100,0x10340500,0x10240100,0x10240100,0x10340100,0x10240100,0x10340100,0x10240100,0x10340100,0x10340100,0x10440100,0x10540100,0x10540500,0x10540100,0x10640900,0x10740900,0x10640900,0x10740900,0x10840D00,0x10841100,0x10841500,0x10941500,0x10A41900,
    0x10D40D00,0x10C40D00,0x10C40D00,0x10B40D00,0x10A40D00,0x10940900,0x10940500,0x10840100,0x10840100,0x10740100,0x10840100,0x10640100,0x10740100,0x10640100,0x10740500,0x10540100,0x10540100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10340100,0x10140100,0x10240100,0x10240100,0x10140100,0x10140100,0x10240100,0x10140100,0x10240100,0x10140100,0x10140100,0x10140100,0x10140100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10140100,0x10240100,0x10340100,0x10340100,0x10340100,0x10440100,0x10440100,0x10440100,0x10440100,0x10640500,0x10640900,0x10540900,0x10740D00,0x10740D00,0x10740D00,0x10741100,0x10841500,0x10741500,
    0x10E40D00,0x10D41100,0x10D41100,0x10C41100,0x10940900,0x10940500,0x10840500,0x10840100,0x10840100,0x10840100,0x10740100,0x10740100,0x10640100,0x10740100,0x10540100,0x10540100,0x10540100,0x10540100,0x10440100,0x10540100,0x10440100,0x10340100,0x10440100,0x10440100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10240100,0x10240100,0x10240100,0x10240100,0x10340100,0x10240100,0x10240100,0x10240100,0x10140100,0x10340100,0x10340100,0x10340100,0x10440100,0x10440100,0x10440100,0x10440100,0x10540100,0x10540100,0x10640100,0x10640500,0x10540500,0x10740900,0x10740D00,0x10941500,0x10841500,0x10941100,
    0x10E41100,0x10D41100,0x10A40D00,0x10A40D00,0x10940900,0x10840500,0x10840500,0x10740100,0x10740100,0x10840101,0x10740100,0x10740100,0x10640100,0x10640100,0x10540100,0x10440100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10240100,0x10140100,0x10240100,0x10140100,0x10140100,0x10040100,0x10140100,0x10240100,0x10140100,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10340101,0x10240100,0x10340100,0x10340101,0x10340101,0x10340100,0x10440100,0x10440100,0x10440100,0x10540100,0x10640500,0x10540500,0x10640500,0x10640900,0x10740D00,0x10740D00,0x10941100,0x10941500,
    0x10F41500,0x10C40D00,0x10B41100,0x10A40D00,0x10A40900,0x10840500,0x10840500,0x10740100,0x10840100,0x10740100,0x10840100,0x10740100,0x10640100,0x10640100,0x10540100,0x10440100,0x10440100,0x10540100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10140100,0x10240100,0x10140100,0x10240100,0x10140100,0x10240100,0x10140100,0x10140100,0x10140100,0x10140100,0x10140100,0x10140100,0x10040100,0x10140100,0x10140100,0x10140100,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10340101,0x10240100,0x10340101,0x10340100,0x10340101,0x10340100,0x10340100,0x10440100,0x10440100,0x10540500,0x10440100,0x10640500,0x10740900,0x10640900,0x10740D00,0x10841100,0x10741100,
    0x10C40D00,0x10B40D00,0x10B41100,0x10940D00,0x10940900,0x10840500,0x10840100,0x10740100,0x10740100,0x10740101,0x10740100,0x10640100,0x10640100,0x10640100,0x10540100,0x10440100,0x10540100,0x10340100,0x10440100,0x10340100,0x10440100,0x10340100,0x10340100,0x10340100,0x10440100,0x10340100,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10240100,0x10040100,0x10040100,0x10140100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140100,0x10040100,0x10140100,0x10140100,0x10140100,0x10140100,0x10240100,0x10140100,0x10140100,0x10240100,0x10240100,0x10240100,0x10240100,0x10340100,0x10340100,0x10440101,0x10440100,0x10540100,0x10440100,0x10540100,0x10640500,0x10640900,0x10640900,0x10740D00,0x10841100,0x10741100,
    0x10E41100,0x10B40D00,0x10B41100,0x10A41100,0x10940900,0x10740500,0x10840500,0x10840100,0x10640100,0x10740100,0x10640100,0x10640100,0x10640100,0x10540100,0x10540100,0x10540100,0x10440100,0x10340100,0x10340100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10140100,0x10240100,0x10140100,0x10140100,0x10240100,0x10140100,0x10140100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140100,0x10140500,0x10040100,0x10040100,0x10140100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140100,0x10240100,0x10240100,0x10140100,0x10240100,0x10240100,0x10340100,0x10240100,0x10340100,0x10240100,0x10440100,0x10540500,0x10540500,0x10540500,0x10540500,0x10640900,0x10740D00,0x10841100,0x10841100,
    0x10D41100,0x10C41100,0x10B41100,0x10A41100,0x10940D00,0x10840900,0x10640100,0x10840500,0x10740100,0x10740100,0x10640100,0x10640100,0x10540100,0x10640100,0x10540500,0x10540100,0x10440500,0x10440100,0x10440500,0x10340100,0x10440500,0x10340100,0x10340500,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10340500,0x10140100,0x10140500,0x10240500,0x10140100,0x10040100,0x10140500,0x10040100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040500,0x10040100,0x10040100,0x10140100,0x10140100,0x10240500,0x10140100,0x10140100,0x10240100,0x10140100,0x10240100,0x10240100,0x10340100,0x10340100,0x10340100,0x10340100,0x10440100,0x10440500,0x10440100,0x10540500,0x10540900,0x10640900,0x10640D00,0x10741100,0x10740D00,
    0x10D41500,0x10C41500,0x10C41500,0x10940D00,0x10940D00,0x10840900,0x10840500,0x10740100,0x10640100,0x10640100,0x10640100,0x10640100,0x10540500,0x10440100,0x10540500,0x10440500,0x10540500,0x10440500,0x10240500,0x10440500,0x10340500,0x10240100,0x10240100,0x10340100,0x10140100,0x10240100,0x10240100,0x10240500,0x10140500,0x10140100,0x10140500,0x10240500,0x10140100,0x10040100,0x10040100,0x10040500,0x10040500,0x10140500,0x10040100,0x10040100,0x10040500,0x10040100,0x10040100,0x10040100,0x10140100,0x10140100,0x10140100,0x10040100,0x10240100,0x10140100,0x10140100,0x10240100,0x10340100,0x10240100,0x10440500,0x10340100,0x10340100,0x10340500,0x10440500,0x10440500,0x10440500,0x10640D00,0x10640D00,0x10841100,0x10740D00,
    0x10C41100,0x10C41500,0x10B41500,0x10A41100,0x10941100,0x10840900,0x10740500,0x10740500,0x10640100,0x10740500,0x10640100,0x10640100,0x10640500,0x10540500,0x10640500,0x10440500,0x10440500,0x10440500,0x10240100,0x10340500,0x10340500,0x10340500,0x10240100,0x10240500,0x10240500,0x10240500,0x10240500,0x10140500,0x10140100,0x10140500,0x10140100,0x10140100,0x100400FF,0x10040100,0x10140500,0x10040500,0x10140500,0x10140100,0x10040100,0x10040500,0x100400FF,0x10040500,0x10040500,0x10040100,0x10040100,0x10140100,0x10140500,0x10040100,0x10040100,0x10140100,0x10240100,0x10140100,0x10140100,0x10340100,0x10340100,0x10240100,0x10340500,0x10440500,0x10440500,0x10440500,0x10540500,0x10640D00,0x10740D00,0x10740D00,0x10740D00,
    0x10D41500,0x10C41500,0x10B41500,0x10841100,0x10941100,0x10840D00,0x10740900,0x10640100,0x10640100,0x10540100,0x10640500,0x10640100,0x10540100,0x10440500,0x10640900,0x10440500,0x10440900,0x10440500,0x10340500,0x10240100,0x10240500,0x10240100,0x10240500,0x10240100,0x10240500,0x10140100,0x10240500,0x10140100,0x10140500,0x10040100,0x10140500,0x10140500,0x10040100,0x10140500,0x10140500,0x10040500,0x10040100,0x10140500,0x10040500,0x10040100,0x10040100,0x10140500,0x100400FF,0x10040100,0x10040100,0x10240500,0x10140500,0x10040100,0x10140100,0x10140100,0x10240100,0x10140100,0x10140100,0x10340100,0x10240100,0x10240100,0x10240100,0x10340100,0x10340100,0x10540900,0x10540500,0x10640900,0x10540D00,0x10741100,0x10740D00,
    0x10C41100,0x10C41500,0x10A41500,0x10941500,0x10840D00,0x10840D00,0x10740500,0x10640500,0x10640500,0x10640100,0x10640500,0x10740500,0x10540500,0x10440500,0x10540500,0x10440500,0x10440900,0x10440900,0x10440500,0x10440500,0x10340900,0x10240500,0x10440500,0x10240500,0x10240500,0x10140100,0x10240500,0x10240500,0x10040100,0x10140100,0x10040100,0x10240500,0x10140500,0x10140500,0x10040100,0x10040500,0x10040100,0x10040500,0x100404FF,0x10040100,0x10040500,0x10140500,0x10040500,0x10140500,0x10040100,0x10140100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140500,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10340100,0x10440500,0x10440500,0x10340500,0x10640900,0x10640900,0x10640D00,0x10741100,0x10740D00,
    0x10D41500,0x10C41500,0x10C41900,0x10941100,0x10841500,0x10740900,0x10640500,0x10740500,0x10740100,0x10540100,0x10640100,0x10540100,0x10640500,0x10540500,0x10540500,0x10440500,0x10340500,0x10340500,0x10340500,0x10340500,0x10340900,0x10240500,0x10240500,0x10240500,0x10240500,0x10140100,0x10240500,0x10240500,0x10140100,0x10040100,0x10140500,0x10140500,0x10040100,0x10040500,0x100400FF,0x10040500,0x10040100,0x10040500,0x10040500,0x10040500,0x10140500,0x10040100,0x10140500,0x10140500,0x10040100,0x10040100,0x10040100,0x10040500,0x10140100,0x10240500,0x10140100,0x10140100,0x10240100,0x10340100,0x10240100,0x10240100,0x10340100,0x10340100,0x10440500,0x10540900,0x10440900,0x10540D00,0x10640D00,0x10740D00,0x10741100,
    0x10F41500,0x10C41500,0x10B41500,0x10941100,0x10840D00,0x10740900,0x10740900,0x10640100,0x10740500,0x10640100,0x10740500,0x10640100,0x10640500,0x10640900,0x10540500,0x10540900,0x10440900,0x10440500,0x10340500,0x10340500,0x10340500,0x10240100,0x10340500,0x10140100,0x10240500,0x10040100,0x10140100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040500,0x10140500,0x10040100,0x10140500,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10040100,0x10040100,0x10140100,0x10240100,0x10140100,0x10240100,0x10240100,0x10340100,0x10240100,0x10340100,0x10340100,0x10340100,0x10340100,0x10640900,0x10540900,0x10640D00,0x10640D00,0x10741100,
    0x10D41100,0x10C41500,0x10A41500,0x10941100,0x10841100,0x10740900,0x10740900,0x10640100,0x10740500,0x10640100,0x10640100,0x10540100,0x10640500,0x10540500,0x10440500,0x10440500,0x10340500,0x10440500,0x10340500,0x10340500,0x10340500,0x10340500,0x10340500,0x10240500,0x10240100,0x10140100,0x10040100,0x10140100,0x10040100,0x10040100,0x100400FF,0x10040100,0x10040100,0x10040100,0x10040100,0x100400FF,0x10040500,0x10040100,0x10040100,0x10040500,0x10040500,0x100400FF,0x10040100,0x10140500,0x10040100,0x10140100,0x10040100,0x10040100,0x10140100,0x10140100,0x10140100,0x10140100,0x10140100,0x10140100,0x10140100,0x10240100,0x10340100,0x10340100,0x10440500,0x10540500,0x10440500,0x10440900,0x10640D00,0x10540900,0x10741100,
    0x10B40D00,0x10A41100,0x10941100,0x10941500,0x10840900,0x10740500,0x10640500,0x10640500,0x10740100,0x10640100,0x10540100,0x10440100,0x10640500,0x10540100,0x10440500,0x10340100,0x10440500,0x10440900,0x10340100,0x10340500,0x10340500,0x10240100,0x10240500,0x10240500,0x10240100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040500,0x10040500,0x10040500,0x10040100,0x10040500,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10040100,0x10140100,0x10140100,0x10240100,0x10240100,0x10140100,0x10240100,0x10240100,0x10340100,0x10240100,0x10340100,0x10340500,0x10340500,0x10540500,0x10540900,0x10540500,0x10640D00,
    0x10B40D00,0x10B41100,0x10A41500,0x10841100,0x10941100,0x10840900,0x10640500,0x10640100,0x10640100,0x10540100,0x10540100,0x10540100,0x10540500,0x10540500,0x10440500,0x10440500,0x10440500,0x10340100,0x10240100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240500,0x10240100,0x10140500,0x10040100,0x10140100,0x10140500,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040501,0x10040100,0x10040100,0x100400FF,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x100400FF,0x10040100,0x10040100,0x10040100,0x10140100,0x10140100,0x10240100,0x10240100,0x10140100,0x10240100,0x10240100,0x10340100,0x10240100,0x10240100,0x10440500,0x10440500,0x10540900,0x10540900,0x10540900,0x10540900,
    0x10C40D00,0x10B40D00,0x10A41100,0x10940D00,0x10740900,0x10740900,0x10640500,0x10640500,0x10640100,0x10640100,0x10640100,0x10640100,0x10540100,0x10440100,0x10440500,0x10340500,0x10340100,0x10340500,0x10340100,0x10140100,0x10240100,0x10340500,0x10040100,0x10240500,0x10140100,0x10140100,0x10140100,0x10140100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x100400FF,0x10040100,0x10040500,0x10040100,0x10040100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140101,0x10140100,0x10240100,0x10240100,0x10140100,0x10340100,0x10340100,0x10140100,0x10340100,0x10440900,0x10540900,0x10640900,0x10740900,0x10640D00,
    0x10B40D00,0x10B40D00,0x10A41100,0x10941100,0x10740900,0x10640500,0x10640500,0x10640100,0x10740100,0x10640100,0x10540100,0x10540100,0x10540100,0x10540100,0x10440100,0x10440100,0x10440500,0x10340100,0x10340500,0x10340500,0x10340500,0x10240100,0x10240500,0x10240100,0x10240100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x100400FF,0x10040100,0x10040101,0x10040501,0x10040100,0x10040501,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x100400FF,0x10040100,0x10140100,0x10140100,0x10240100,0x10140100,0x10240100,0x10140100,0x10240100,0x10240100,0x10340100,0x10340100,0x10440500,0x10340500,0x10340500,0x10540900,0x10540900,0x10640900,
    0x10D41100,0x10C41100,0x10A41100,0x10740D00,0x10840D00,0x10740500,0x10840500,0x10740100,0x10640100,0x10740100,0x10640100,0x10540100,0x10440100,0x10540500,0x10440100,0x10340100,0x10340500,0x10340100,0x10340500,0x10240100,0x10240100,0x10140100,0x10240100,0x10140100,0x10140100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10040100,0x10040101,0x10040100,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040501,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140100,0x10140100,0x10240100,0x10240100,0x10140100,0x10240100,0x10240100,0x10240100,0x10340100,0x10340100,0x10440500,0x10440500,0x10540500,0x10640900,0x10640D00,
    0x10C40D00,0x10B41100,0x10A41100,0x10941100,0x10740D00,0x10740900,0x10740500,0x10640100,0x10640100,0x10640100,0x10640100,0x10540100,0x10440100,0x10540100,0x10440100,0x10440500,0x10340100,0x10240100,0x10240100,0x10340500,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10240100,0x10140100,0x10040100,0x10140100,0x10040100,0x10040100,0x10040101,0x10040101,0x10040101,0x10040100,0x10040100,0x10040100,0x10040500,0x10040100,0x10040100,0x10040101,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10240100,0x10240101,0x10240101,0x10240101,0x10240100,0x10240100,0x10340100,0x10340100,0x10440100,0x10340500,0x10340100,0x10640900,0x10540500,0x10640D00,
    0x10B40900,0x10D41500,0x10A41100,0x10940D00,0x10840D00,0x10840900,0x10640500,0x10640100,0x10540100,0x10640100,0x10640100,0x10540100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340500,0x10340500,0x10340500,0x10240100,0x10140100,0x10140100,0x10140100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040101,0x10040101,0x10040101,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140100,0x10140101,0x10040100,0x10140101,0x10240100,0x10240101,0x10240100,0x10240100,0x10240100,0x10340100,0x10340100,0x10440100,0x10440100,0x10340100,0x10540900,0x10640900,0x10640D00,
    0x10C40D00,0x10A40D00,0x10A41100,0x10941100,0x10840D00,0x10640900,0x10640100,0x10640100,0x10640100,0x10640100,0x10540100,0x10540100,0x10540500,0x10440100,0x10440100,0x10440500,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10140100,0x10240500,0x10140100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x100400FF,0x100400FF,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10040100,0x10140100,0x10140100,0x10140101,0x10240100,0x10240100,0x10240100,0x10340100,0x10240100,0x10240100,0x10340100,0x10240100,0x10340100,0x10440500,0x10540900,0x10741100,
    0x10D41100,0x10C41100,0x10A41100,0x10A41100,0x10940D00,0x10740500,0x10740900,0x10540100,0x10540100,0x10640100,0x10640100,0x10440100,0x10640500,0x10540500,0x10440100,0x10440500,0x10340500,0x10340100,0x10340100,0x10340500,0x10340500,0x10240100,0x10140100,0x10240100,0x10240100,0x10140100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040101,0x10040100,0x10040101,0x10040101,0x10040501,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140101,0x10040100,0x10040100,0x10040101,0x10040100,0x10140101,0x10240101,0x10240101,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10340100,0x10340500,0x10440500,0x10440500,0x10440500,0x10740900,
    0x10C40D00,0x10B41100,0x10A41100,0x10840D00,0x10840D00,0x10840500,0x10640500,0x10640100,0x10640100,0x10640100,0x10640100,0x10540100,0x10540500,0x10440100,0x10340100,0x10440500,0x10340100,0x10440500,0x10340100,0x10240100,0x10340500,0x10240100,0x10140100,0x10240100,0x10140100,0x10140100,0x10040100,0x10140100,0x10040100,0x10040101,0x10040100,0x10040101,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140101,0x10040100,0x10240101,0x10240101,0x10140101,0x10240101,0x10140100,0x10240100,0x10240100,0x10340100,0x10340100,0x10340100,0x10440100,0x10440100,0x10640500,0x10540500,0x10640900,
    0x10C40D00,0x10C41100,0x10C41500,0x10940D00,0x10840D00,0x10740900,0x10740500,0x10640100,0x10640100,0x10740100,0x10540100,0x10440100,0x10540100,0x10540500,0x10440100,0x10440500,0x10440500,0x10340100,0x10340100,0x10340500,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10140100,0x10040100,0x10140100,0x10040100,0x10040101,0x10040100,0x10040100,0x10040101,0x10040101,0x10040101,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040100,0x10040100,0x10140100,0x10040100,0x10040100,0x10040100,0x10040101,0x10140101,0x10140101,0x10240101,0x10240101,0x10240101,0x10240100,0x10240100,0x10340100,0x10340101,0x10240100,0x10340100,0x10340100,0x10440100,0x10540100,0x10640900,0x10540900,
    0x10C40900,0x10B40D00,0x10B41100,0x10940D00,0x10840D00,0x10640500,0x10740500,0x10640100,0x10540100,0x10640100,0x10540100,0x10540100,0x10540100,0x10540500,0x10440500,0x10440100,0x10440500,0x10240100,0x10340100,0x10340100,0x10240100,0x10240100,0x10140100,0x10140100,0x10140100,0x10140100,0x10040100,0x10140100,0x10040100,0x10040101,0x10040100,0x10040101,0x10140101,0x10040100,0x10040101,0x10040100,0x100400FF,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10140101,0x10140101,0x10040101,0x10140100,0x10140100,0x10240101,0x10240101,0x10440101,0x10240101,0x10240100,0x10240100,0x10240100,0x10340100,0x10240100,0x10340100,0x10340100,0x10440500,0x10540500,0x10640500,0x10640500,
    0x10D40D00,0x10D41100,0x10B41100,0x10941100,0x10840D00,0x10640500,0x10740100,0x10740500,0x10640100,0x10540100,0x10540100,0x10440100,0x10540500,0x10440500,0x10440500,0x10540500,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10340100,0x10140100,0x10240100,0x10140100,0x10140100,0x10040100,0x10140100,0x10140100,0x10040100,0x10140101,0x10040100,0x10040101,0x10040101,0x10040101,0x10040100,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040100,0x10140101,0x10040100,0x10040101,0x10040100,0x10140101,0x10240100,0x10140101,0x10240101,0x10240101,0x10340101,0x10340101,0x10340101,0x10340100,0x10340100,0x10340101,0x10340100,0x10440100,0x10440500,0x10640500,0x10540500,
    0x10D40900,0x10C41100,0x10A40D00,0x10940D00,0x10840D00,0x10840900,0x10740500,0x10640100,0x10640100,0x10640100,0x10540100,0x10540100,0x10540100,0x10540500,0x10540500,0x10340100,0x10340100,0x10240100,0x10340100,0x10340100,0x10340100,0x10340100,0x10140100,0x10240100,0x10140100,0x10240100,0x10140100,0x10140100,0x10140100,0x10140100,0x10040100,0x10140101,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040101,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140101,0x10140101,0x10140100,0x10140100,0x10140101,0x10240101,0x10140101,0x10340101,0x10340101,0x10240100,0x10240100,0x10340100,0x10340100,0x10340100,0x10440100,0x10340100,0x10340100,0x10440100,0x10540500,0x10540100,
    0x10E40D00,0x10B40D00,0x10B40D00,0x10A40D00,0x10840D00,0x10840900,0x10840900,0x10640100,0x10740100,0x10640100,0x10640100,0x10540100,0x10640100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10440500,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10040100,0x10140100,0x10140101,0x10140100,0x10040101,0x10040101,0x10040100,0x10140101,0x10040101,0x10040100,0x10040101,0x10040100,0x10040100,0x10040100,0x10040101,0x10040100,0x10140100,0x10040101,0x10140101,0x10140101,0x10140101,0x10140100,0x10240100,0x10240101,0x10240101,0x10240102,0x10240101,0x10340101,0x10340101,0x10340100,0x10340100,0x10340100,0x10340100,0x10440100,0x10340100,0x10440100,0x10540100,0x10640500,
    0x10D41100,0x10B40900,0x10A40D00,0x10A41100,0x10940900,0x10840500,0x10840500,0x10740100,0x10540100,0x10740100,0x10540100,0x10540100,0x10540100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10140100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10140101,0x10140100,0x10140100,0x10040101,0x10140101,0x10140100,0x10040100,0x10040100,0x10040100,0x10040101,0x10040101,0x10040100,0x10040101,0x10140101,0x10040100,0x10140100,0x10040100,0x10140101,0x10140100,0x10140100,0x10140101,0x10140101,0x10340102,0x10240101,0x10240102,0x10240101,0x10240101,0x10340101,0x10440100,0x10340100,0x10340100,0x10440100,0x10440100,0x10440100,0x10640500,0x10740900,
    0x10B40900,0x10A40D00,0x10A40D00,0x10A40D00,0x10A40D00,0x10840500,0x10840500,0x10640100,0x10740100,0x10640100,0x10740100,0x10540100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10140100,0x10140100,0x10140101,0x10040101,0x10140100,0x10140101,0x10140100,0x10040101,0x10140101,0x10040100,0x10040101,0x10040101,0x10040100,0x10140101,0x10140100,0x10140100,0x10140101,0x10140101,0x10140100,0x10140101,0x10140101,0x10240101,0x10340101,0x10240101,0x10240101,0x10340101,0x10340101,0x10340101,0x10340101,0x10340100,0x10340100,0x10440100,0x10440100,0x10340100,0x10440100,0x10540500,0x10540500,
    0x10E40D00,0x10B40D00,0x10B41100,0x10A40D00,0x10A40D00,0x10840900,0x10740100,0x10740100,0x10740100,0x10740100,0x10640100,0x10640100,0x10540100,0x10540100,0x10540100,0x10440100,0x10340100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10140100,0x10240100,0x10140100,0x10140101,0x10140101,0x10140101,0x10040100,0x10040101,0x10040101,0x10040100,0x10140101,0x10140101,0x10140101,0x10140100,0x10040100,0x10140100,0x10140100,0x10240101,0x10240101,0x10140101,0x10140101,0x10140101,0x10240101,0x10340101,0x10240101,0x10340101,0x10340101,0x10240100,0x10340100,0x10440100,0x10340100,0x10440100,0x10440100,0x10440100,0x10340100,0x10540500,0x10640100,
    0x10C40D00,0x10C40900,0x10B40D00,0x10A41100,0x10940D00,0x10740900,0x10740500,0x10840500,0x10740100,0x10640100,0x10640100,0x10640100,0x10640100,0x10540100,0x10540100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10340100,0x10240100,0x10240100,0x10240101,0x10240100,0x10240100,0x10140100,0x10140100,0x10140100,0x10040100,0x10140100,0x10140100,0x10140101,0x10040101,0x10140100,0x10040100,0x10040100,0x10040100,0x10040100,0x10040100,0x10140100,0x10140100,0x10140101,0x10240101,0x10140100,0x10240101,0x10240101,0x10240102,0x10240101,0x10340101,0x10240102,0x10340102,0x10340101,0x10340101,0x10440100,0x10340100,0x10340100,0x10440100,0x10440100,0x10540500,0x10640500,0x10740500,
    0x10C40D00,0x10B40D00,0x10C41100,0x10A40D00,0x10940D00,0x10840500,0x10740500,0x10740100,0x10740100,0x10740100,0x10640100,0x10640100,0x10540100,0x10540100,0x10440100,0x10440100,0x10340100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140101,0x10240100,0x10140100,0x10140100,0x10140101,0x10140101,0x10040101,0x10040101,0x10040101,0x10140101,0x10140101,0x10140100,0x10040100,0x10140100,0x10140101,0x10140101,0x10140101,0x10140100,0x10240101,0x10140101,0x10240102,0x10340101,0x10340101,0x10340101,0x10340101,0x10340101,0x10340100,0x10440100,0x10340100,0x10440100,0x10440100,0x10440100,0x10540100,0x10640500,0x10640500,
    0x10C40D00,0x10C40D00,0x10B40D00,0x10B41100,0x10A40D00,0x10940900,0x10840900,0x10740100,0x10740100,0x10740100,0x10640100,0x10640100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10340100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10240101,0x10140101,0x10140100,0x10240100,0x10140101,0x10040100,0x10040101,0x10040100,0x10140101,0x10140100,0x10140101,0x10140101,0x10140100,0x10140100,0x10140101,0x10240101,0x10240101,0x10140101,0x10240101,0x10240101,0x10340101,0x10340101,0x10340101,0x10340102,0x10340101,0x10340100,0x10440100,0x10440101,0x10440100,0x10340100,0x10540500,0x10540500,0x10640500,0x10640900,
    0x10C40500,0x10C40D00,0x10A40D00,0x10A41100,0x10840900,0x10840900,0x10840500,0x10640100,0x10640100,0x10740100,0x10640100,0x10640100,0x10540100,0x10640500,0x10440100,0x10540100,0x10540100,0x10440100,0x10340100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10140100,0x10140100,0x10140100,0x10140101,0x10140100,0x10140100,0x10040101,0x10140101,0x10140101,0x10140100,0x10040100,0x10040101,0x10140100,0x10140101,0x10040100,0x10040101,0x10140101,0x10240100,0x10240101,0x10140101,0x10240100,0x10340101,0x10240102,0x10340101,0x10340101,0x10440101,0x10340100,0x10440100,0x10340100,0x10440100,0x10440100,0x10440100,0x10440500,0x10540500,0x10640500,
    0x10C40900,0x10C40D00,0x10B40D00,0x10940D00,0x10940D00,0x10940900,0x10840500,0x10740100,0x10740100,0x10740100,0x10640100,0x10640100,0x10640100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10240100,0x10140101,0x10140101,0x10140101,0x10040101,0x10140101,0x10140100,0x10140100,0x10040101,0x10140100,0x10140100,0x10140101,0x10240102,0x10140100,0x10140101,0x10140101,0x10240101,0x10240101,0x10340102,0x10340101,0x10240101,0x10240100,0x10340100,0x10340100,0x10340100,0x10340100,0x10440100,0x10440100,0x10540100,0x10540500,0x10740500,0x10740900,
    0x10C40900,0x10D41100,0x10A40D00,0x10940D00,0x10840900,0x10740500,0x10840500,0x10740100,0x10840100,0x10740100,0x10740100,0x10640100,0x10640100,0x10640100,0x10540100,0x10440100,0x10440100,0x10540500,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240101,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140100,0x10140101,0x10140100,0x10140101,0x10140101,0x10140101,0x10040101,0x10140101,0x10040101,0x10040101,0x10140100,0x10140101,0x10140101,0x10040100,0x10240101,0x10140100,0x10140102,0x10240101,0x10240101,0x10240101,0x10240101,0x10340101,0x10340101,0x10440101,0x10440101,0x10340102,0x10340100,0x10440100,0x10340100,0x10440100,0x10540500,0x10440100,0x10540500,0x10640900,
    0x10C40900,0x10B40900,0x10B40D00,0x10940900,0x10A41100,0x10840D00,0x10840500,0x10740100,0x10640100,0x10740100,0x10740100,0x10640100,0x10540100,0x10640100,0x10440100,0x10540100,0x10340100,0x10440100,0x10440100,0x10340100,0x10340100,0x10240100,0x10240100,0x10340100,0x10240100,0x10240101,0x10240101,0x10340100,0x10240100,0x10240101,0x10140101,0x10240100,0x10140100,0x10140101,0x10140100,0x10240100,0x10140100,0x10240101,0x10140100,0x10040100,0x10040100,0x10140101,0x10140101,0x10140101,0x10140101,0x10140100,0x10240101,0x10140101,0x10140101,0x10240101,0x10240100,0x10240102,0x10240101,0x10340102,0x10340101,0x10440101,0x10440100,0x10340100,0x10440100,0x10440100,0x10540100,0x10540100,0x10540100,0x10640500,0x10540500,
    0x10D40900,0x10C40D00,0x10B41100,0x10B41100,0x10940D00,0x10940900,0x10840500,0x10840500,0x10740100,0x10740100,0x10640100,0x10740100,0x10640500,0x10540100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10440100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10240100,0x10140100,0x10140101,0x10140100,0x10140100,0x10140101,0x10140101,0x10140100,0x10140101,0x10140100,0x10140100,0x10140101,0x10140100,0x10040100,0x10140101,0x10140101,0x10140101,0x10240101,0x10140101,0x10240101,0x10240101,0x10240101,0x10440101,0x10340101,0x10340101,0x10340101,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10540100,0x10640500,0x10740500,
    0x10D40900,0x10C40D00,0x10B40D00,0x10A40D00,0x10A40900,0x10840900,0x10840500,0x10940900,0x10840500,0x10740100,0x10640100,0x10640100,0x10640100,0x10540100,0x10540100,0x10540100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240101,0x10240100,0x10240100,0x10240101,0x10140101,0x10140101,0x10140100,0x10140101,0x10240101,0x10140101,0x10140101,0x10140101,0x10140101,0x10140101,0x10140101,0x10140100,0x10140100,0x10240101,0x10240101,0x10140101,0x10240101,0x10140101,0x10240101,0x10340101,0x10340101,0x10340102,0x10340101,0x10340101,0x10440101,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10540500,0x10640900,0x10540100,
    0x10E40D00,0x10D40D00,0x10C41100,0x10B40D00,0x10940D00,0x10940900,0x10940500,0x10940500,0x10640100,0x10740100,0x10740100,0x10540100,0x10740500,0x10640100,0x10640100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240101,0x10240100,0x10240101,0x10240101,0x10240101,0x10140101,0x10140101,0x10140101,0x10140101,0x10140100,0x10040100,0x10240101,0x10140101,0x10240100,0x10140101,0x10240101,0x10140100,0x10140101,0x10140101,0x10140101,0x10140101,0x10240101,0x10340101,0x10340101,0x10240100,0x10340101,0x10340100,0x10340100,0x10340100,0x10440100,0x10440100,0x10440100,0x10540100,0x10640500,0x10640900,0x10740900,
    0x10E40D00,0x10D41100,0x10B40D00,0x10A40D00,0x10A40900,0x10940500,0x10940500,0x10840500,0x10840100,0x10740100,0x10640100,0x10740100,0x10740100,0x10540100,0x10640100,0x10540100,0x10540100,0x10640100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10340100,0x10340101,0x10240101,0x10240101,0x10240101,0x10240101,0x10240101,0x10240101,0x10240100,0x10140101,0x10240100,0x10140100,0x10140100,0x10240100,0x10140100,0x10140100,0x10240100,0x10240100,0x10240101,0x10240100,0x10240100,0x10240101,0x10240101,0x10340101,0x10240100,0x10340101,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10540100,0x10640500,0x10840900,0x10740900,
    0x10E40D00,0x10C40D00,0x10D40D00,0x10C41100,0x10940900,0x10A40900,0x10940500,0x10940100,0x10840500,0x10840100,0x10640100,0x10640100,0x10740100,0x10640100,0x10640100,0x10540100,0x10540100,0x10540100,0x10440100,0x10340100,0x10340100,0x10440100,0x10340100,0x10440100,0x10340100,0x10340100,0x10340101,0x10240100,0x10240100,0x10340101,0x10340101,0x10240100,0x10340101,0x10240100,0x10240101,0x10340101,0x10240101,0x10140100,0x10240101,0x10140101,0x10240100,0x10140100,0x10140100,0x10140100,0x10140101,0x10340101,0x10240100,0x10240101,0x10240101,0x10340101,0x10240100,0x10340101,0x10340101,0x10340101,0x10440100,0x10440100,0x10440100,0x10440101,0x10440100,0x10440100,0x10440100,0x10540500,0x10640500,0x10740900,0x10640500,
    0x10F41100,0x10D40D00,0x10B40D00,0x10B40900,0x10A40D00,0x10840900,0x10840500,0x10940500,0x10840100,0x10740100,0x10740100,0x10740100,0x10740500,0x10740500,0x10640100,0x10540100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10440100,0x10340100,0x10340101,0x10340101,0x10240100,0x10340100,0x10240100,0x10240101,0x10340101,0x10340101,0x10340100,0x10240100,0x10240101,0x10240100,0x10140100,0x10140100,0x10240101,0x10140101,0x10240100,0x10240101,0x10240100,0x10240100,0x10240100,0x10340100,0x10340100,0x10240101,0x10340101,0x10340100,0x10340100,0x10440100,0x10440100,0x10440100,0x10340100,0x10540100,0x10540100,0x10440100,0x10640500,0x10740500,0x10840D00,
    0x10E40D00,0x10D40D00,0x10D41100,0x10C41100,0x10B40D00,0x10940900,0x10940500,0x10940500,0x10840500,0x10940500,0x10840100,0x10740100,0x10740500,0x10740100,0x10740500,0x10640100,0x10640100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10440100,0x10240100,0x10340100,0x10340100,0x10340100,0x10240100,0x10240101,0x10240100,0x10240100,0x10240100,0x10240100,0x10240101,0x10240100,0x10240100,0x10140100,0x10240100,0x10240101,0x10240100,0x10240100,0x10240101,0x10340101,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10440100,0x10540100,0x10440100,0x10540100,0x10540500,0x10540100,0x10740900,0x10840D00,0x10740D00,0x10840D00,
    0x10E40D00,0x10D40D00,0x10E41100,0x10B40D00,0x10B41100,0x10B40D00,0x10A40900,0x10A40900,0x10A40500,0x10940500,0x10740100,0x10740100,0x10740500,0x10840500,0x10640500,0x10640100,0x10640100,0x10540100,0x10540100,0x10540100,0x10440100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340101,0x10440101,0x10340100,0x10240100,0x10240100,0x10240101,0x10240101,0x10240100,0x10240100,0x10240100,0x10140100,0x10240100,0x10240100,0x10340100,0x10240101,0x10340100,0x10340100,0x10240100,0x10340100,0x10440100,0x10340100,0x10340100,0x10440100,0x10440100,0x10440100,0x10440100,0x10540100,0x10640100,0x10640500,0x10640500,0x10840900,0x10840D00,0x10940D00,
    0x10F41500,0x11041100,0x10C41100,0x10C41100,0x10B40D00,0x10B40900,0x10A40900,0x10B40500,0x10A40500,0x10A40500,0x10840100,0x10840500,0x10840500,0x10740500,0x10740500,0x10740500,0x10540100,0x10540100,0x10640100,0x10640500,0x10540100,0x10540100,0x10540100,0x10540100,0x10540100,0x10440100,0x10340100,0x10440100,0x10440100,0x10440100,0x10340100,0x10240100,0x10340100,0x10340100,0x10440100,0x10340101,0x10340100,0x10340100,0x10340100,0x10340100,0x10240100,0x10340100,0x10340100,0x10240100,0x10240100,0x10240100,0x10240100,0x10340100,0x10340100,0x10340100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10540100,0x10540100,0x10640100,0x10540100,0x10640500,0x10740500,0x10740500,0x10940D00,0x10940D00,0x10A41100,
    0x10F41100,0x10E41100,0x10E41500,0x10C40D00,0x10C40D00,0x10B40D00,0x10B40900,0x10A40500,0x10A40500,0x10A40900,0x10940500,0x10940500,0x10840500,0x10840900,0x10740500,0x10740100,0x10840500,0x10740100,0x10740500,0x10640500,0x10540100,0x10640500,0x10540100,0x10540100,0x10540500,0x10440100,0x10440100,0x10340100,0x10440100,0x10340100,0x10340100,0x10440100,0x10440101,0x10340100,0x10340100,0x10340100,0x10340100,0x10340101,0x10340100,0x10440100,0x10340101,0x10340100,0x10240100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10340100,0x10440100,0x10340100,0x10440100,0x10440100,0x10540100,0x10540100,0x10540100,0x10540100,0x10640500,0x10740500,0x10740500,0x10840900,0x10840900,0x10840D00,0x10A40D00,0x10940D00,
    0x10E41100,0x10D41100,0x10E41500,0x10E41500,0x10B40D00,0x10C40D00,0x10B40900,0x10A40900,0x10A40900,0x10B40500,0x10940500,0x10A40900,0x10940500,0x10A40900,0x10840900,0x10740500,0x10840900,0x10740500,0x10740500,0x10740500,0x10640100,0x10640500,0x10640500,0x10540500,0x10440100,0x10540100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440101,0x10440100,0x10340100,0x10440100,0x10440100,0x10340100,0x10340100,0x10240100,0x10340100,0x10340100,0x10440100,0x10340100,0x10340100,0x10440100,0x10340100,0x10440100,0x10340100,0x10540100,0x10440100,0x10540100,0x10540100,0x10540100,0x10540100,0x10540100,0x10640500,0x10540500,0x10840900,0x10740900,0x10940D00,0x10940D00,0x10B41100,0x10941100,
    0x10F41100,0x10F41500,0x10E41500,0x10D41100,0x10D40D00,0x10C41100,0x10B40D00,0x10A40500,0x10C40D00,0x10B40D00,0x10B40D00,0x10940500,0x10A40900,0x10940500,0x10940500,0x10940900,0x10940900,0x10840900,0x10740500,0x10840500,0x10740500,0x10740100,0x10540100,0x10640500,0x10640500,0x10640100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10440100,0x10440100,0x10440100,0x10440100,0x10340100,0x10440100,0x10340100,0x10440100,0x10440100,0x10340100,0x10440100,0x10440100,0x10340100,0x10340100,0x10440100,0x10340100,0x10440100,0x10440100,0x10540500,0x10440100,0x10540100,0x10540100,0x10640100,0x10640500,0x10540100,0x10840900,0x10640500,0x10740500,0x10840D00,0x10840D00,0x10740D00,0x10840D00,0x10A41500,0x10A41100,
    0x11141900,0x11141900,0x10F41500,0x10F41900,0x10E41100,0x10E41100,0x10D40D00,0x10D40D00,0x10C40D00,0x10B40900,0x10B40900,0x10A40D00,0x10B40D00,0x10A40D00,0x10B40D00,0x10A40D00,0x10940D00,0x10940900,0x10840D00,0x10740900,0x10940900,0x10840900,0x10740500,0x10840900,0x10640100,0x10740500,0x10640500,0x10540500,0x10540100,0x10540100,0x10640500,0x10640500,0x10540100,0x10440100,0x10540100,0x10540100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10440100,0x10540500,0x10440100,0x10540500,0x10540500,0x10540500,0x10540500,0x10640500,0x10540500,0x10640500,0x10640500,0x10640100,0x10640500,0x10640500,0x10740900,0x10740500,0x10840D00,0x10840900,0x10740900,0x10940D00,0x10B41500,0x10B41100,0x10B41500,0x10E41D00,
    0x11041500,0x11141D00,0x11041900,0x11041D00,0x11041500,0x10F41900,0x10E41500,0x10E41500,0x10C40D00,0x10C40D00,0x10C41100,0x10C41100,0x10D41100,0x10C41100,0x10B41100,0x10B41100,0x10B40D00,0x10B41100,0x10940D00,0x10A40D00,0x10A40D00,0x10840900,0x10840D00,0x10840900,0x10840900,0x10740500,0x10840D00,0x10740900,0x10840900,0x10640500,0x10640500,0x10740900,0x10640500,0x10640100,0x10740900,0x10640500,0x10640500,0x10540500,0x10640500,0x10640500,0x10640500,0x10640500,0x10640500,0x10640500,0x10640500,0x10640500,0x10640900,0x10540900,0x10540900,0x10640D00,0x10740500,0x10640500,0x10740500,0x10840D00,0x10840D00,0x10840900,0x10940D00,0x10840D00,0x10B41100,0x10A41100,0x10A41100,0x10C41900,0x10C41900,0x10C41D00,0x10E41D00,
    0x11241900,0x11342100,0x11141900,0x11241D00,0x10F41900,0x11041900,0x11041900,0x10F41500,0x10F41100,0x10F41500,0x10E41100,0x10E41100,0x10E41500,0x10C41100,0x10D41100,0x10D41100,0x10C41100,0x10C40D00,0x10C40D00,0x10A40D00,0x10A40D00,0x10940D00,0x10A40D00,0x10A41100,0x10A40D00,0x10B40D00,0x10940900,0x10940900,0x10940900,0x10840900,0x10840900,0x10840900,0x10840900,0x10740500,0x10740900,0x10840900,0x10840900,0x10840900,0x10740500,0x10740500,0x10740900,0x10740900,0x10740900,0x10840D00,0x10840900,0x10740900,0x10740900,0x10840900,0x10840D00,0x10840D00,0x10840900,0x10840D00,0x10940D00,0x10A40D00,0x10A41100,0x10940D00,0x10A41100,0x10B41100,0x10A40D00,0x10C41500,0x10B41500,0x10E41D00,0x10D41D00,0x10E42100,0x10E42100,
    0x11241500,0x11241500,0x11141500,0x11141900,0x10F41500,0x11141900,0x10E41100,0x11041100,0x10D40D00,0x10D40D00,0x10C40900,0x10C40900,0x10E40D00,0x10E40D00,0x10B40D00,0x10B40900,0x10C40D00,0x10B40900,0x10A40900,0x10B40D00,0x10940900,0x10940900,0x10940900,0x10940100,0x10940900,0x10940900,0x10840500,0x10840500,0x10840500,0x10740100,0x10640100,0x10740500,0x10840900,0x10840500,0x10740500,0x10740100,0x10840100,0x10640100,0x10640100,0x10740500,0x10640100,0x10540100,0x10740900,0x10740900,0x10740500,0x10740500,0x10740500,0x10740900,0x10740500,0x10840500,0x10940900,0x10740500,0x10840500,0x10940900,0x10940500,0x10A40900,0x10940D00,0x10B40D00,0x10A40D00,0x10B40D00,0x10A40D00,0x10D41900,0x10C41500,0x10E41900,0x10D41900
};

static H26XEncTnr tnr_param_off =
{   0,                  //enable temporal noise reduction (0: disable, 1:enable)
    0,                  //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    1,                  //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,                  //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    2,                  //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,                  //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {3, 7, 12},         //TNR_P2P_SAD_THRESHOLD (0~255)
    {8, 6, 2},          //TNR_P2P_WEIGHT (0~16)
    12,                 //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,                  //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,                  //TNR_P2P_INPUT (0: original source, 1: mctf result)
    16,                 //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {1, 1, 1, 1},       //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {3, 2, 3},          //TNR_P2P_REF_Y_WEIGHT (0~7)
    {3, 2, 3},          //TNR_P2P_REF_C_WEIGHT (0~7)
    {6, 10, 16},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {0, 2, 3},          //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    2,                  //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    1,                  //TNR_P2P_CLAMP_Y_LSR (0~7)
    2,                  //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    1,                  //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {3, 2, 3},          //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {3, 2, 3},          //TNR_MCTF_REF_C_WEIGHT (0~7)
    {5, 6, 7},          //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {0, 2, 3},          //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    2,                  //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    1,                  //TNR_MCTF_CLAMP_Y_LSR (0~7)
    2,                  //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    1,                  //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
	0,                  //NR3D_CUR_MOTION_SAD_TH
	4,                  //NR3D_CUR_MOTION_RAT_TH
	{255, 255},         //NR3D_CUR_MOTION_TWR_P2P_TH
	{255, 255},         //NR3D_REF_MOTION_TWR_P2P_TH
	{255, 255},         //NR3D_CUR_MOTION_TWR_MCTF_TH
	{255, 255},         //NR3D_REF_MOTION_TWR_MCTF_TH
	{1, 2, 1},          //NR3D_MCTF_REF_Y_WEIGHT
	{1, 2, 1},          //NR3D_MCTF_REF_C_WEIGHT
	{1, 2, 1},          //NR3D_P2P_REF_Y_WEIGHT
	{1, 2, 1},          //NR3D_P2P_REF_C_WEIGHT
	3,                  //NR3D_P2P_INPUT_WEIGHT
	255,                //NR3D_REF_MOTION_THRESH
	{255, 255},         //NR3D_SAD_TWR_P2P_TH
	{255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0,                  //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv1 = //ISO100
{   0,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    1,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    2,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {3, 7, 12},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {8, 6, 2},        //TNR_P2P_WEIGHT (0~16)
    12,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    16,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {1, 1, 1, 1},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {3, 2, 3},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {3, 2, 3},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {6, 10, 16},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {0, 2, 3},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    1,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    2,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    1,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {3, 2, 3},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {3, 2, 3},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {5, 6, 7},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {0, 2, 3},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    2,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    1,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    2,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    1,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv2 = //ISO200
{   0,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    1,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    2,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {3, 7, 12},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {8, 6, 2},        //TNR_P2P_WEIGHT (0~16)
    12,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    16,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {1, 1, 1, 1},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {3, 2, 3},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {3, 2, 3},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {6, 10, 16},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {0, 2, 3},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    1,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    2,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    1,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {3, 2, 3},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {3, 2, 3},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {5, 6, 7},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {0, 2, 3},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    2,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    1,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    2,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    1,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv3 = //ISO400
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    0,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {2, 4, 6},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    5,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    10,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {1, 1, 1, 1},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 5, 1},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 5, 1},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {8, 15, 30},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {8, 15, 30},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 5, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 5, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {8, 15, 30},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {8, 15, 30},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv4 = //ISO800
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {2, 4, 8},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    5,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    10,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {1, 1, 1, 1},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 5, 1},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 5, 1},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {8, 15, 30},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {8, 15, 30},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 5, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 5, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {8, 15, 30},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {8, 15, 30},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv5 = //ISO1600
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {2, 4, 8},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    6,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    10,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {1, 1, 1, 1},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 5, 1},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 5, 1},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {40, 60, 80},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {20, 30, 60},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 5, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 5, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {30, 40, 60},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {15, 25, 45},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv6 = //ISO3200
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {6, 8, 12},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    16,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    10,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {1, 1, 1, 1},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 5, 2},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 5, 2},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {40, 60, 80},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {30, 50, 60},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 5, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 5, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {30, 50, 70},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {15, 35, 55},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv7 = //ISO6400
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {6, 8, 12},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    16,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    10,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {1, 1, 1, 1},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 5, 2},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 5, 2},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {60, 70, 80},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {30, 50, 60},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 5, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 5, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {40, 60, 80},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {20, 40, 60},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv8 = //ISO12800
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {6, 8, 12},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    16,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    10,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {2, 2, 2, 2},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 5, 2},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 3, 2},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {90, 110, 120},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {80, 100, 110},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 7, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 7, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {40, 60, 80},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {20, 40, 60},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv9 = //ISO25600
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {12, 15, 20},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    12,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    6,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {3, 3, 3, 3},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 7, 2},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 7, 2},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {110, 120, 140},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {20, 40, 50},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 7, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 7, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {110, 120, 130},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {30, 50, 60},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv10 = //ISO51200
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {12, 15, 20},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    12,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    6,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {3, 3, 3, 3},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 5, 2},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 5, 2},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {90, 110, 120},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {40, 60, 80},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 7, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 7, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {80, 90, 100},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {40, 60, 80},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv11 = //ISO102400
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {20, 25, 28},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    16,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    5,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {3, 3, 3, 3},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 3, 3},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 4, 2},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {150, 160, 170},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {40, 60, 80},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 7, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 7, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {80, 90, 100},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {40, 60, 80},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static H26XEncTnr tnr_param_lv12 = //ISO204800
{   1,          //enable temporal noise reduction (0: disable, 1:enable)
    0,          //TNR Mode as OSD enabled: fully TNR (0: fully TNR, 1: P2P only, 2: no TNR)
    0,          //enable mctf/p2p pixel blending (0: disable, 1:enable)
    3,          //P2P SAD Mode (0: pixel, 3: SAD + pixel)
    0,          //MCTF SAD Mode (0: pixel, 1: b8x8, 2: b16x16, 3: auto)
    0,          //MCTF Bias Mode (0: disable, 1: b8x8, 2: b16x16, 3: auto)
    {20, 25, 28},        //TNR_P2P_SAD_THRESHOLD (0~255)
    {16, 8, 0},        //TNR_P2P_WEIGHT (0~16)
    16,          //TNR_P2P_BORDER_CHECK_THRES (0~255)
    4,          //TNR_P2P_BORDER_CHECK_SCALE (0~7)
    0,          //TNR_P2P_INPUT (0: original source, 1: mctf result)
    5,          //TNR_P2P_MCTF_MOTION_THRESHOLD (0~255)
    {3, 3, 3, 3},        //TNR_P2P_MCTF_MOTION_WEIGHT (0~3)
    //P2P TNR Config----------------------------------------------------------------------------
    {1, 1, 3},        //TNR_P2P_REF_Y_WEIGHT (0~7)
    {1, 2, 2},        //TNR_P2P_REF_C_WEIGHT (0~7)
    {150, 160, 170},        //TNR_P2P_RANGE_Y_THRESHOLD (0~255)
    {40, 60, 80},        //TNR_P2P_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_P2P_CLAMP_Y_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_Y_LSR (0~7)
    0,          //TNR_P2P_CLAMP_C_THRESHOLD (0~255)
    2,          //TNR_P2P_CLAMP_C_LSR (0~7)
    //MCTF TNR Config----------------------------------------------------------------------------
    {1, 3, 1},        //TNR_MCTF_REF_Y_WEIGHT (0~7)
    {1, 3, 1},        //TNR_MCTF_REF_C_WEIGHT (0~7)
    {80, 90, 100},        //TNR_MCTF_RANGE_Y_THRESHOLD (0~255)
    {40, 60, 80},        //TNR_MCTF_RANGE_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_Y_LSR (0~7)
    0,          //TNR_MCTF_CLAMP_C_THRESHOLD (0~255)
    0,          //TNR_MCTF_CLAMP_C_LSR (0~7)
    //ADDITIONAL TNR Config---------------------------------------------------------------------
    0,          //NR3D_CUR_MOTION_SAD_TH
    4,          //NR3D_CUR_MOTION_RAT_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_P2P_TH
    {255, 255},        //NR3D_CUR_MOTION_TWR_MCTF_TH
    {255, 255},        //NR3D_REF_MOTION_TWR_MCTF_TH
    {1, 2, 1},        //NR3D_MCTF_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_MCTF_REF_C_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_Y_WEIGHT
    {1, 2, 1},        //NR3D_P2P_REF_C_WEIGHT
    3,          //NR3D_P2P_INPUT_WEIGHT
    255,          //NR3D_REF_MOTION_THRESH
    {255, 255},        //NR3D_SAD_TWR_P2P_TH
    {255, 255},         //NR3D_SAD_TWR_MCTF_TH
    0           //enable I frame weight refresh (0: disable, 1:enable)
};

static INT8 tnr_level[TOTAL_GAIN_NUM]=
{
    H264_UI_3DNR_LV1,
    H264_UI_3DNR_LV2,
    H264_UI_3DNR_LV3,
    H264_UI_3DNR_LV4,
    H264_UI_3DNR_LV5,
    H264_UI_3DNR_LV6,
    H264_UI_3DNR_LV7,
    H264_UI_3DNR_LV8,
    H264_UI_3DNR_LV9,
    H264_UI_3DNR_LV10,
    H264_UI_3DNR_LV11,
    H264_UI_3DNR_LV12,
};

static H26XEncTnr* tnr_param[TOTAL_UI_3DNR_LV]=
{
    &tnr_param_off,
    &tnr_param_lv1,
    &tnr_param_lv2,
    &tnr_param_lv3,
    &tnr_param_lv4,
    &tnr_param_lv5,
    &tnr_param_lv6,
    &tnr_param_lv7,
    &tnr_param_lv8,
    &tnr_param_lv9,
    &tnr_param_lv10,
    &tnr_param_lv11,
    &tnr_param_lv12,
};

static sISP_ISOINDEX gISO_Index[Total_SENIDNum] = {0};
void iq_param_os05a10_evb_table1_init(UINT32 id,UINT32 mode_idx)
{
	//iqs_set_range
	UINT32 *iq_param_addr[IQ_PARAM_MAX];
	static UINT32 num_3DNR_param = TOTAL_UI_3DNR_LV;
	gISO_Index[id].Id = id;
    gISO_Index[id].num = IQS_ISOMAPTAB_NUM - 1;

	iq_param_addr[IQ_ISOIDX     ] = (UINT32 *)&gISO_Index[id];
    iq_param_addr[IQ_ISOIDX_MAP ] = (UINT32*)&iso_map_tab_os05a10_evb[0];
    iq_param_addr[IQ_ENGINE_CTRL] = (UINT32*)&e_ctrl;

	//***********
	//**  SIE  **
	//***********
    iq_param_addr[IQ_OBSUB      ] = (UINT32 *)ob[0];
	iq_param_addr[IQ_ECS_TAB    ] = (UINT32 *)ecs_tab;
	iq_param_addr[IQ_ECS        ] = (UINT32 *)&ecs;

	//***********
	//**  RHE  **
	//***********
	iq_param_addr[IQ_WDR             ] = (UINT32*) &wdr_strength[0];
    iq_param_addr[IQ_WDR_LCE_OFFSET  ] = (UINT32*) &wdr_lce_offset;
	iq_param_addr[IQ_LCE             ] = (UINT32*) &lce_strength[0];
    iq_param_addr[IQ_GCE             ] = (UINT32*) &gce_strength[0];
	iq_param_addr[IQ_DEFOG_INIT_PARAM] = (UINT32 *)&defog_init_param_os05a10_evb;
	iq_param_addr[IQ_DEFOG_WET       ] = (UINT32 *)&defog_wet_os05a10_evb[0];

	//***********
	//**  IFE  **
	//***********
	iq_param_addr[IQ_OUTL_BRI        ] = (UINT32 *)outl_bri[0];
	iq_param_addr[IQ_OUTL_DARK       ] = (UINT32 *)outl_dark[0];
	iq_param_addr[IQ_OUTL_CNT        ] = (UINT32 *)outl_cnt[0];
	iq_param_addr[IQ_OUTL            ] = (UINT32 *)&outl_set[0];
	iq_param_addr[IQ_SPATIAL_W       ] = (UINT32 *)spatial_w[0];
	iq_param_addr[IQ_SPATAL          ] = (UINT32 *)&spatial[0];
	iq_param_addr[IQ_RANGEA_THR      ] = (UINT32 *)range_a_thr[0];
	iq_param_addr[IQ_RANGEA_LUT      ] = (UINT32 *)range_a_lut[0];
	iq_param_addr[IQ_RANGEB_THR      ] = (UINT32 *)range_b_thr[0];
	iq_param_addr[IQ_RANGEB_LUT      ] = (UINT32 *)range_b_lut[0];
	iq_param_addr[IQ_RANGEB          ] = (UINT32 *)&range_b[0];
	iq_param_addr[IQ_CLAMP           ] = (UINT32 *)&filter_clamp[0];
	iq_param_addr[IQ_VIG_CENTER      ] = (UINT32 *)&vig_center;
	iq_param_addr[IQ_VIG_TAB         ] = (UINT32 *)&vig;
    iq_param_addr[IQ_VIG_ISO_TH 	 ] = (UINT32 *)&vig_iso_th;
	iq_param_addr[IQ_GBAL_STAB       ] = (UINT32 *)gbal_s_tab[0];
	iq_param_addr[IQ_GBAL_DTAB       ] = (UINT32 *)gbal_d_tab[0];
	iq_param_addr[IQ_GBAL            ] = (UINT32 *)&gbal[0];
    iq_param_addr[IQ_RBFILL_LUMA_TAB ] = (UINT32 *)rbfill_luma_tab;
    iq_param_addr[IQ_RBFILL_RATIO_TAB] = (UINT32 *)rbfill_ratio_tab;
    iq_param_addr[IQ_RBFILL          ] = (UINT32 *)&rbfill[0];


	//***********
	//**  DCE  **
	//***********
    iq_param_addr[IQ_DCE_DIST	] = (UINT32*)&dist_os05a10_evb;
    iq_param_addr[IQ_DCE_RADIOUS] = (UINT32*)&radious_os05a10_evb;
    iq_param_addr[IQ_CFAINTER	] = (UINT32*)&cfa_os05a10_evb;
	iq_param_addr[IQ_GDC_FOV	] = (UINT32*)&fov_os05a10_evb;
    iq_param_addr[IQ_GDC_GLUT	] = (UINT32*)ldc_g_lut_os05a10_evb;
    iq_param_addr[IQ_GDC_RLUT	] = (UINT32*)ldc_r_lut_os05a10_evb;
    iq_param_addr[IQ_GDC_BLUT	] = (UINT32*)ldc_b_lut_os05a10_evb;
	iq_param_addr[IQ_DCE_CA	    ] = (UINT32*)&cac_os05a10_evb;

	//***********
	//**  IPE  **
	//***********
	iq_param_addr[IQ_EDGEKER    ] = (UINT32 *)edge_kernel[0];
	iq_param_addr[IQ_DIR_TAB    ] = (UINT32 *)edir_tab[0];
	iq_param_addr[IQ_DIREDGE_EXT] = (UINT32 *)&edir_ext[0];
	iq_param_addr[IQ_DIRSCORETAB] = (UINT32 *)&score_tab[0];
	iq_param_addr[IQ_DIRSCORETH ] = (UINT32 *)&score_th[0];
	iq_param_addr[IQ_EWA        ] = (UINT32 *)&ewa[0];
	iq_param_addr[IQ_EWB        ] = (UINT32 *)&ewb[0];
	iq_param_addr[IQ_EWPARAM    ] = (UINT32 *)&ewparam[0];
	iq_param_addr[IQ_EDGEENH    ] = (UINT32 *)&edge_enh[0];
	iq_param_addr[IQ_EDMAP      ] = (UINT32 *)&ed_map[0];
	iq_param_addr[IQ_EDTAB      ] = (UINT32 *)ed_tab[0];
	iq_param_addr[IQ_ESMAP      ] = (UINT32 *)&es_map[0];
	iq_param_addr[IQ_ESTAB      ] = (UINT32 *)es_tab[0];
	iq_param_addr[IQ_RGBLPF     ] = (UINT32 *)&lpf[0];
    iq_param_addr[IQ_CCM_TH     ] = (UINT32*)&color_temperature_th_os05a10_evb;
	iq_param_addr[IQ_Color_L    ] = (UINT32*)&color_low_os05a10_evb;
	iq_param_addr[IQ_Color_M    ] = (UINT32*)&color_middle_os05a10_evb;
	iq_param_addr[IQ_Color_H    ] = (UINT32*)&color_high_os05a10_evb;
    iq_param_addr[IQ_FSTAB      ] = (UINT32*)fs_tab_os05a10_evb[0];
	iq_param_addr[IQ_FDTAB	    ] = (UINT32*)fd_tab_os05a10_evb[0];
    iq_param_addr[IQ_CC         ] = (UINT32*)&cc_os05a10_evb;
    iq_param_addr[IQ_Y_CURVE    ] = (UINT32*)y_curve_os05a10_evb;
	iq_param_addr[IQ_GAMMA_TH	] = (UINT32*)&gamma_lv_th_os05a10_evb;
    iq_param_addr[IQ_GAMMA_DAY	] = (UINT32*)gamma_day_os05a10_evb;
	iq_param_addr[IQ_GAMMA_NIGHT] = (UINT32*)gamma_night_os05a10_evb;
	iq_param_addr[IQ_3DCC_TAB   ] = (UINT32*)color_3d_lut_os05a10_evb;
    iq_param_addr[IQ_3DCC_ROUND ] = (UINT32*)&color_3d_os05a10_evb;
	iq_param_addr[IQ_EDGTAB     ] = (UINT32*)edg_tab_os05a10_evb;
    iq_param_addr[IQ_DDSTAB     ] = (UINT32*)dds_tab_os05a10_evb;
	iq_param_addr[IQ_SATURATION ] = (UINT32 *)&saturation[0];
	iq_param_addr[IQ_CONTRAST   ] = (UINT32 *)&contrast[0];
    iq_param_addr[IQ_CCON_TAB   ] = (UINT32 *)&ccon_tab[0];
	iq_param_addr[IQ_CCTRL_INFO ] = (UINT32 *)&cctrl_info[0];

	iq_param_addr[IQ_CST_COEF	] = (UINT32*)cst_coef_os05a10_evb;
    iq_param_addr[IQ_CST_PARAM	] = (UINT32*)&cst_os05a10_evb;
	iq_param_addr[IQ_YCCFIX	    ] = (UINT32*)&ycc_fix_os05a10_evb;
    iq_param_addr[IQ_NOISE_PARAM] = (UINT32*)&noise_param_os05a10_evb;
    iq_param_addr[IQ_GAMMA_RAND ] = (UINT32*)&gamma_rand_os05a10_evb;

	//***********
	//** IFE2  **
	//***********
	iq_param_addr[IQ_REFCENTER_YTH  ] = (UINT32 *)ref_center_y_th[0];
	iq_param_addr[IQ_REFCENTER_YWT  ] = (UINT32 *)ref_center_y_wt[0];
	iq_param_addr[IQ_REFCENTER_Y    ] = (UINT32 *)&ref_center_y[0];
	iq_param_addr[IQ_REFCENTER_UVTH ] = (UINT32 *)ref_center_uv_th[0];
	iq_param_addr[IQ_REFCENTER_UVWT ] = (UINT32 *)ref_center_uv_wt[0];
	iq_param_addr[IQ_REFCENTER_UV   ] = (UINT32 *)&ref_center_uv[0];
	iq_param_addr[IQ_IFE2FILTER_YTH ] = (UINT32 *)ife2filter_y_th[0];
	iq_param_addr[IQ_IFE2FILTER_YWT ] = (UINT32 *)ife2filter_y_wt[0];
	iq_param_addr[IQ_IFE2FILTER_UVTH] = (UINT32 *)ife2filter_uv_th[0];
	iq_param_addr[IQ_IFE2FILTER_UVWT] = (UINT32 *)ife2filter_uv_wt[0];
	iq_param_addr[IQ_IFE2FILTER     ] = (UINT32 *)&ife2filter[0];
	iq_param_addr[IQ_GRAY           ] = (UINT32 *)&gray_statical[0];

	//***********
	//**  IME  **
	//***********
	iq_param_addr[IQ_CHROMAADAPT        ] = (UINT32 *)&chroma_adapt[0];
	iq_param_addr[IQ_CHROMAADAPT_COLOR  ] = (UINT32 *)&chroma_adapt_color[0];
	iq_param_addr[IQ_CHROMAADAPT_LUM    ] = (UINT32 *)&chroma_adapt_lum[0];
	iq_param_addr[IQ_CHROMASUPP_WEIGHTY ] = (UINT32 *)chroma_supp_w_y[0];
	iq_param_addr[IQ_CHROMASUPP_WEIGHTC ] = (UINT32 *)chroma_supp_w_c[0];
	iq_param_addr[IQ_CHROMASUPP         ] = (UINT32 *)&chroma_supp[0];
    iq_param_addr[IQ_TMNR               ] = (UINT32 *)&tmnr_info;
    iq_param_addr[IQ_TMNR_DEBUG         ] = (UINT32 *)&tmnr_momap_sel_os05a10_evb;
    iq_param_addr[IQ_TMNR_AUTO          ] = (UINT32 *)&tmnr_auto_info_os05a10_evb;

	//***********
	//** Codec **
	//***********
	iq_param_addr[IQ_NUM_3DNR_PARAM ] = (UINT32 *)&num_3DNR_param;
	iq_param_addr[IQ_3DNR_LEVEL     ] = (UINT32 *)&tnr_level[0];
	iq_param_addr[IQ_3DNR_PARAM     ] = (UINT32 *)&tnr_param;

	//***********
	//**  HDR  **
	//***********
	iq_param_addr[IQ_HDR_TH			] = (UINT32 *)&hdr_lv_th_os05a10_evb;
	iq_param_addr[IQ_HDR_HIGH		] = (UINT32 *)&hdr_high_os05a10_evb;
	iq_param_addr[IQ_HDR_MIDDLE		] = (UINT32 *)&hdr_middle_os05a10_evb;
	iq_param_addr[IQ_HDR_LOW		] = (UINT32 *)&hdr_low_os05a10_evb;

	iq_param_addr[IQ_PATHCURVE_TH		] = (UINT32 *)&pathcurve_lv_th_os05a10_evb;
	iq_param_addr[IQ_PATHCURVE_HIGH		] = (UINT32 *)&pathcurve_high_os05a10_evb;
	iq_param_addr[IQ_PATHCURVE_MIDDLE	] = (UINT32 *)&pathcurve_middle_os05a10_evb;
	iq_param_addr[IQ_PATHCURVE_LOW		] = (UINT32 *)&pathcurve_low_os05a10_evb;
	iq_set_param_addr(id,mode_idx, iq_param_addr);
}

#endif
