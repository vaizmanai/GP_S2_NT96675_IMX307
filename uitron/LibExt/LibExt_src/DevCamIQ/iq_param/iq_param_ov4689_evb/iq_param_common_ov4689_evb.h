#ifndef _IQ_PARAM_COMMON_OV4689_EVB_H_
#define _IQ_PARAM_COMMON_OV4689_EVB_H_

#include "iq_common.h"

extern ISOMAP iso_map_tab_ov4689_evb[IQS_ISOMAPTAB_NUM];
extern DIST dist_ov4689_evb;
extern Fact_Norm   radious_ov4689_evb;
extern DCE_CFAPARAM cfa_ov4689_evb;
extern FOV fov_ov4689_evb;
extern UINT32 ldc_g_lut_ov4689_evb[65];
extern INT32 ldc_r_lut_ov4689_evb[65];
extern INT32 ldc_b_lut_ov4689_evb[65];
extern Aberation cac_ov4689_evb;
extern IQS_COLOR_TEMPERATURE_TH color_temperature_th_ov4689_evb;
extern IQS_COLOR_TEMPERATURE_PARAM color_low_ov4689_evb;
extern IQS_COLOR_TEMPERATURE_PARAM color_middle_ov4689_evb;
extern IQS_COLOR_TEMPERATURE_PARAM color_high_ov4689_evb;
extern UINT8 fs_tab_ov4689_evb[TOTAL_GAIN_NUM][16];
extern UINT8 fd_tab_ov4689_evb[TOTAL_GAIN_NUM][16];
extern IPE_CC cc_ov4689_evb;
extern UINT32 y_curve_ov4689_evb[129];
extern IQS_GAMMA_LV_TH gamma_lv_th_ov4689_evb;
extern UINT32 gamma_day_ov4689_evb[129];
extern UINT32 gamma_night_ov4689_evb[129];
extern UINT8 edg_tab_ov4689_evb[24];
extern UINT8 dds_tab_ov4689_evb[8];
extern INT16 cst_coef_ov4689_evb[9];
extern IPE_CST cst_ov4689_evb;
extern IPE_YCCFIX ycc_fix_ov4689_evb;
extern IPE_RAND_NR noise_param_ov4689_evb;
extern IPE_GamRand gamma_rand_ov4689_evb;
extern UINT32 color_3d_lut_ov4689_evb[900] ;
extern IPE_3DCCRound color_3d_ov4689_evb;
extern IQS_SHDR_EVRATIO_TH hdr_lv_th_ov4689_evb;
extern SHDR_IQ_PARA hdr_high_ov4689_evb;
extern SHDR_IQ_PARA hdr_middle_ov4689_evb;
extern SHDR_IQ_PARA hdr_low_ov4689_evb;
extern IQS_PATHCURVE_LV_TH pathcurve_lv_th_ov4689_evb;
extern UINT32 pathcurve_high_ov4689_evb[33];
extern UINT32 pathcurve_middle_ov4689_evb[33];
extern UINT32 pathcurve_low_ov4689_evb[33];
extern S_DEFOG_LIB_INIT_PARA defog_init_param_ov4689_evb;
extern UINT32 defog_wet_ov4689_evb[17];
extern IME_TMNR_DISPMOMAP tmnr_momap_sel_ov4689_evb;
extern TMNR_AUTO_INFO tmnr_auto_info_ov4689_evb;

extern void iq_param_ov4689_evb_table1_init(UINT32 id,UINT32 mode_idx);

#endif
