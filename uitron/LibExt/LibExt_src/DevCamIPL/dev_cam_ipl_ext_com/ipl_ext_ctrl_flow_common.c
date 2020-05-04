/**
    ipl ctrl common fw.

    @file       ipl_ext_ctrl_common.c
    @ingroup    mISYSAlg
    @note       Nothing (or anything need to be mentioned).

    Copyright   Novatek Microelectronics Corp. 2011.  All rights reserved.
*/
#include "ipl_ext_common.h"

UINT32 IPL_IFE2InitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group);
void *IPL_AdaptSettingCBFlow(UINT32 id, IPL_RAW_IMG_INFO ipl_in_info, IPL_YCC_CH_INFO *ch_info);
IPH_CLK IPL_SIEClkCBFlow(UINT32 id);
UINT32 IPL_SIEClkSrcCBFlow(UINT32 id);
UINT32 IPL_SIEPclkSelCBFlow(UINT32 id);
IPH_CLK IPL_RHEClkCBFlow(UINT32 id);
IPH_CLK IPL_IFEClkCBFlow(UINT32 id);
IPH_CLK IPL_DCEClkCBFlow(UINT32 id);
IPH_CLK IPL_IPEClkCBFlow(UINT32 id);
IPH_CLK IPL_IFE2ClkCBFlow(UINT32 id);
IPH_CLK IPL_IMEClkCBFlow(UINT32 id);
UINT32 IPL_SIEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group);
UINT32 IPL_RHEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group);
UINT32 IPL_IFEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group);
UINT32 IPL_DCEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group);
UINT32 IPL_IPEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group);
UINT32 IPL_IMEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group);

IPLCTRL_FLOW_INFO IPL_FlowInfo = {
	{IPL_HAL_PAR_PRV, IPL_HAL_PAR_PRV},

	IPL_IFE2InitCBFlow,
	IPL_AdaptSettingCBFlow,
	IPL_SIEClkCBFlow,
	IPL_SIEClkSrcCBFlow,
	IPL_SIEPclkSelCBFlow,
	IPL_RHEClkCBFlow,
	IPL_IFEClkCBFlow,
	IPL_DCEClkCBFlow,
	IPL_IPEClkCBFlow,
	IPL_IFE2ClkCBFlow,
	IPL_IMEClkCBFlow,

	IPL_SIEInitCBFlow,
	IPL_RHEInitCBFlow,
	IPL_IFEInitCBFlow,
	IPL_DCEInitCBFlow,
	IPL_IPEInitCBFlow,
	IPL_IMEInitCBFlow,
};

static IPLCTRL_FLOW_INFO *IPL_GetCtrlFlowInfo(void)
{
	return &IPL_FlowInfo;
}

IPL_HAL_PARASET IPL_CtrlGetHalSetIdFlow(UINT32 Id)
{
	return IPL_GetCtrlFlowInfo()->IPL_HalParamId[Id];
}

void *IPL_AdaptSettingCBFlow(UINT32 id, IPL_RAW_IMG_INFO ipl_in_info, IPL_YCC_CH_INFO *ch_info)
{
	ch_info->width  = IPL_UTI_IMESUB_ADJ_HSIZE(ipl_in_info.width, iq_get_ife2_lca_ratio(id, FALSE, FALSE), 4);
	if (ch_info->width < 80) {
		ch_info->width = 80;
	}

	ch_info->height = IPL_UTI_IMESUB_ADJ_VSIZE(ipl_in_info.height, iq_get_ife2_lca_ratio(id, FALSE, FALSE), 4);
	if (ch_info->height < 60) {
		ch_info->height = 60;
	}

	ch_info->line_ofs = IPL_YSIZEH_CONV2LOFS(IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_FMT), ch_info->width);

	IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_H, ch_info->width);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_YLOS, ch_info->line_ofs);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_V, ch_info->height);

	//DBG_IND("LCA Size(%d %d) line_ofs(%d)\r\n", ch_info->width, ch_info->height, ch_info->line_ofs);
	return NULL;
}

#if 0
#endif
UINT32 IPL_SIEClkSrcCBFlow(UINT32 id)
{
	SEN_STATUS_PARAM sen_status = {0};
	ER rt = E_OK;

	sen_status.sensor_mode = IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE);
	rt = sensor_get_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_GET_STATUS, (void *)&sen_status);
	if (rt != E_OK || sen_status.sensor_info.mode == NULL) {
		DBG_ERR("Get Sensor Status Fail id:%d, Sensor_Mode: %d\r\n", IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE));
		return IPH_SIECLKSRC_CURR;
	}

	if (sen_status.sensor_info.data_type == SENSOR_DATA_PARALLEL) {
		return IPH_SIECLKSRC_480;
	} else {
		return IPH_SIECLKSRC_CURR;
	}
}

IPH_CLK IPL_SIEClkCBFlow(UINT32 id)
{
	UINT32 div;
	IPH_CLK clk = {0};
	SEN_STATUS_PARAM sen_status = {0};
	ER rt = E_OK;

	sen_status.sensor_mode = IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE);
	rt = sensor_get_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_GET_STATUS, (void *)&sen_status);
	if (rt != E_OK || sen_status.sensor_info.mode == NULL) {
		DBG_ERR("Get Sensor Status Fail id:%d, Sensor_Mode: %d\r\n", IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE));
		return clk;
	}

	switch (sen_status.sensor_info.data_type) {
	case SENSOR_DATA_PARALLEL:
		if (sen_status.sensor_info.mode->pclk == 0) {
			clk.SIEclk = 400000000;
		} else {
			clk.SIEclk = sen_status.sensor_info.mode->pclk * 2;
		}
		if (IPL_SIEClkSrcCBFlow(id) == IPH_SIECLKSRC_480) {
			if ((48000000 % clk.SIEclk) != 0) {
				div = 480000000 / clk.SIEclk;
				clk.SIEclk = 480000000 / div;
			}
		}

		if (clk.SIEclk > 400000000) {
			clk.SIEclk = 240000000;
		}
		break;

	case SENSOR_DATA_LVDS:
	case SENSOR_DATA_MIPI:
		clk.SIEclk = 0;
		break;

	case SENSOR_DATA_SIEPATGEN:
		clk.SIEclk = 0;
		break;

	default:
		clk.SIEclk = 48000000;
		break;
	}

#if _FPGA_EMULATION_
	clk.SIEclk = 48000000;
#endif
	return clk;
}

UINT32 IPL_SIEPclkSelCBFlow(UINT32 id)
{
	SEN_STATUS_PARAM sen_status = {0};
	ER rt = E_OK;

	sen_status.sensor_mode = IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE);
	rt = sensor_get_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_GET_STATUS, (void *)&sen_status);
	if (rt != E_OK || sen_status.sensor_info.mode == NULL) {
		DBG_ERR("Get Sensor Status Fail id:%d, Sensor_Mode: %d\r\n", IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE));
		return IPH_SIEPXCLK_OFF;
	}

	if (sen_status.sensor_info.sig_mode == SENSOR_SIGNAL_MODE_AHD) {
		return IPH_SIEPXCLK_PAD_AHD;
	}

	if (sen_status.sensor_info.data_type == SENSOR_DATA_SIEPATGEN) {
		return IPH_SIEPXCLK_MCLK;
	}

	return IPH_SIEPXCLK_PAD;
}

IPH_CLK IPL_RHEClkCBFlow(UINT32 id)
{
	IPH_CLK clk;
	clk.RHEclk = DxSys_GetCfgClk(CFG_RHE_CLK);
	return clk;
}

IPH_CLK IPL_IFEClkCBFlow(UINT32 id)
{
	IPH_CLK clk;
	clk.IFEclk = DxSys_GetCfgClk(CFG_IFE_CLK);
	return clk;
}

IPH_CLK IPL_DCEClkCBFlow(UINT32 id)
{
	IPH_CLK clk;
	clk.DCEclk = DxSys_GetCfgClk(CFG_DCE_CLK);
	return clk;
}

IPH_CLK IPL_IPEClkCBFlow(UINT32 id)
{
	IPH_CLK clk;
	clk.IPEclk = DxSys_GetCfgClk(CFG_IPE_CLK);
	return clk;
}

IPH_CLK IPL_IFE2ClkCBFlow(UINT32 id)
{
	IPH_CLK clk;
	clk.IFE2clk = DxSys_GetCfgClk(CFG_IFE2_CLK);
	return clk;
}

IPH_CLK IPL_IMEClkCBFlow(UINT32 id)
{
	IPH_CLK clk;
	clk.IMEclk = DxSys_GetCfgClk(CFG_IME_CLK);
	return clk;
}

#if 0
#endif

UINT32 IPL_SIEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group)
{
	SIE_UPDATE *SIE_Update;

	SIE_Update = (SIE_UPDATE *)group;

	IPL_SIESetOB_FCB(id, info->pSie_sub, SIE_Update);
	IPL_SIESetCA_FCB(id, info->pSie_sub, SIE_Update);
	IPL_SIESetLA_FCB(id, info->pSie_sub, SIE_Update);
	IPL_SIESetBP_FCB(id, &info->pSie_sub->InteEn, SIE_Update, info->pSie_sub);
	IPL_SIESetDMAOutSrc_FCB(id, &info->pSie_sub->sieFuncEn, SIE_Update);
	IPL_SIESetDMAOutCh3_FCB(id, &info->pSie_sub->sieFuncEn, SIE_Update, &info->pSie_sub->yout_info);
	IPL_SIESetDP_FCB(id, info->pSie_sub, SIE_Update, &info->pSie_sub->sieFuncEn);
	IPL_SIESetRawEnc_FCB(id, &info->pSie_sub->sieFuncEn, SIE_Update, &info->pSie_sub->RawEnc);
	IPL_SIECCIR_FCB(id, &info->pSie_sub->sieFuncEn, SIE_Update, info->pSie_sub->pDvi);
	IPL_SIEPatGen_FCB(id, &info->pSie_sub->sieFuncEn, SIE_Update, &info->pSie_sub->PatGen);

	*SIE_Update |= SIE_SUBFEN;

	iq_set_flow_cb(id, IQCB_PRV_SIE_INIT, info, group);
	return 1;
}

UINT32 IPL_IFEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group)
{
	iq_set_flow_cb(id, IQCB_PRV_IFE_INIT, info, group);

	return 1;
}

UINT32 IPL_DCEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group)
{
	iq_set_flow_cb(id, IQCB_PRV_DCE_INIT, info, group);
#if 0
	UINT32 sieOutH, sieOutV, ipl_sizeH, ipl_sizeV;

	sieOutH  = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_H);
	sieOutV  = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_V);
	ipl_sizeH = IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_H);
	ipl_sizeV = IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_V);
	RSC_GetNull2D(id, sieOutH, sieOutV, ipl_sizeH, ipl_sizeV, info->pDce_sub, group);
#endif
	return 1;
}

UINT32 IPL_IPEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group)
{
	iq_set_flow_cb(id, IQCB_PRV_IPE_INIT, info, group);
	return 1;
}

UINT32 IPL_IFE2InitCBFlow(UINT32 Id, ENG_SUBFUNC *Info, IPL_HAL_GROUP *group)
{
	iq_set_flow_cb(Id, IQCB_PRV_IFE2_INIT, Info, group);

	return 1;
}

UINT32 IPL_IMEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group)
{
#if IPL_IMEMD_FUNC_SUPPORT
	ER rt = E_OK;

	if (IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EN) == ENABLE) {
		static IME_HAL_MD_INFO md_info;
		rt = md_get_user_info(&md_info);
		if (rt == E_OK) {
			info->pIme_sub->pMdInfo = &md_info;
			group->imeUpdate |= IME_MD_PARAM;
		}
	}
#endif
	iq_set_flow_cb(id, IQCB_PRV_IME_INIT, info, group);

	return 1;
}

UINT32 IPL_RHEInitCBFlow(UINT32 id, ENG_SUBFUNC *info, IPL_HAL_GROUP *group)
{
	iq_set_flow_cb(id, IQCB_PRV_RHE_INIT, info, group);
	ExtFunc_Init(id);
	return 1;
}

#if 0
#endif
void IPL_CtrlInitIpcInfoFlowCommon(UINT32 id, IPC_INFO *ipc_info)
{
	SEN_STATUS_PARAM sen_status = {0};
	IPLCTRL_FLOW_INFO *flow_info;
	ER rt = E_OK;
	UINT32 flip_type;

	flow_info = IPL_GetCtrlFlowInfo();
	if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_FUNC_EN) & ICF_FUNC_SHDR) {
		ipc_info->ICF_FC.BaseInfo.proc_bit_id = IPL_CtrlGetInfor(id, IPLCTRL_MF_TOTAL_FRM_BIT);
	} else {
		ipc_info->ICF_FC.BaseInfo.proc_bit_id = 1 << id;
	}
	ipc_info->ICF_FC.ParaIdx = flow_info->IPL_HalParamId[id];

	ipc_info->ICF_FC.BaseInfo.IPLCFMode = IPL_CF_NORMAL;
	ipc_info->ICF_FC.BaseInfo.IPLCFModeExt = IPL_CtrlGetInfor(id, IPLCTRL_CFMODEEXT);
	ipc_info->ICF_FC.BaseInfo.FlipInfo = IPL_CtrlGetInfor(id, IPLCTRL_IPL_FLIP_TYPE);

	sen_status.sensor_mode = IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE);
	rt = sensor_get_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_GET_STATUS, (void *)&sen_status);
	if (rt != E_OK || sen_status.sensor_info.mode == NULL) {
		DBG_ERR("Get Sensor Status Fail id:%d, Sensor_Mode: %d\r\n", IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE));
		return;
	}

	//Set Sensor flip/Mirror
	flip_type = IPL_CtrlGetInfor(id, IPLCTRL_SEN_FLIP_TYPE);
	rt = sensor_set_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_SET_USER_OPTION, (void *)&flip_type);
	if (rt == E_OK) {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVSTPIX, IPL_UTI_CONV_SEN_STPIX(sen_status.sensor_info.mode->stpix));
	} else {
		DBG_ERR("Set Sensor User Option Fail id: %d", IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)));
	}

	IPL_CtrlInitIpc_SIEAct(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo.SIE_Act);
	IPL_CtrlInitIpc_SIEIn(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo.SIE_In, &ipc_info->ICF_FC.BaseInfo.SIE_Ch0_Bayer_Type);
	IPL_CtrlInitIpc_SIESignal(id, &ipc_info->ICF_FC.BaseInfo.Sensor_In);

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh0PPB(id, &ipc_info->ICF_FC.BaseInfo);

		if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN) == ENABLE) {
			IPL_CtrlInitIpc_SIECh5PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch5_Ppb_Addr[0]);
		}
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CA_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh1PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch1_Img, &ipc_info->ICF_FC.BaseInfo.SIE_Ch1_Ppb_Addr[0]);
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_LA_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh2PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch2_Ppb_Addr[0]);
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_EN) == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.IPLCFModeExt |= IPL_CFEXT_CH3_OUT;
		IPL_CtrlInitIpc_SIECh3PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Img, &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Ppb_Addr[0], &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Ppb_Num);
	}

	IPL_CtrlInitIpc_IPLInPPB(id, &ipc_info->ICF_FC.BaseInfo.IPL_In, &ipc_info->ICF_FC.BaseInfo.IPL_StPos, &ipc_info->ICF_FC.BaseInfo.RHE_Mode);
    IPL_CtrlInitIpc_IPLStrpInfo(id, &ipc_info->ICF_FC.BaseInfo.strp_info);

	ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.defog_en = IPL_CtrlGetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.defog_en == ENABLE) {
		IPL_CtrlInitIpc_RHESubOutPPB(id, &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.addr[0], &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.subout_width, &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.subout_height);
	}

	IPL_CtrlInitIpc_DCEIn(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo);

	if (IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_EN) == ENABLE || IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN) == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn = ENABLE;
	} else {
		ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn = DISABLE;
	}

	if (ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn == ENABLE) {
		IPL_CtrlInitIpc_IPEEthPPB(id, &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.eth_addr[0], &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.eth_addr_subspl[0], &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.LineOfs);
	}

	ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_en = IPL_CtrlGetInfor(id, IPLCTRL_IPE_VA_OUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_en == ENABLE) {
		IPL_CtrlInitIpc_IPEVAPPB(id, &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_addr[0]);
	}

	ipc_info->ICF_FC.BaseInfo.LCA_info.LcaEn = IPL_CtrlGetInfor(id, IPLCTRL_IFE2_LCA_EN);
	if (ipc_info->ICF_FC.BaseInfo.LCA_info.LcaEn == ENABLE) {
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_SUB_OUT_1, &ipc_info->ICF_FC.BaseInfo.LCA_info.addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_NUM));
	}

	//primacy mask
	ipc_info->ICF_FC.BaseInfo.PriMsk.pixelation_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_EN);
	if (ipc_info->ICF_FC.BaseInfo.PriMsk.pixelation_en == ENABLE) {
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_PRI_MASK_1, &ipc_info->ICF_FC.BaseInfo.PriMsk.addr[0], IPLBUF_IME_PRI_MASK_MAX - IPLBUF_IME_PRI_MASK_1);
	}

	//TMNR out
	ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_EN);
	if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_CTRL_EN) & IPL_EXT_CTRL_TMNR_SHARE_BUF) {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_buf_share_en = ENABLE;
	} else {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_buf_share_en = DISABLE;
	}

	if (ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_en == ENABLE) {
		IQS_TMNR_YCC_COMPRESSION_INFO *ycc_comp_info;

		ycc_comp_info = iqs_get_ycc_compression_info();

		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.mot_bufsize =  IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_MOT_BUF_SIZE);
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.period = ycc_comp_info->period;
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.period_length = ycc_comp_info->period_length;
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_TMNR_MOTION_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.mot_addr[0], IPLBUF_IME_TMNR_MOTION_OUT_MAX - IPLBUF_IME_TMNR_MOTION_OUT_1);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_TMNR_STA_INFO_1, &ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.sta_addr[0], IPLBUF_IME_TMNR_STA_INFO_MAX - IPLBUF_IME_TMNR_STA_INFO_1);
	}

	//MD out
	ipc_info->ICF_FC.BaseInfo.ime_md_info.md_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EN);
	if (ipc_info->ICF_FC.BaseInfo.ime_md_info.md_en == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.ime_md_info.sta_bufsize = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_SIZE);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_MD_STA_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_md_info.sta_addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_NUM));
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_MD_EVT_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_md_info.evt_addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EVT_BUF_NUM));
	}

	//set ime yuv type
	ipc_info->ICF_FC.BaseInfo.ime_yuv_type = IPL_CtrlGetInfor(id, IPLCTRL_IME_YUV_TYPE);
	//set ime scale method
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.threshold = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALE_RATIO_THR);
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.method_h = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALER_OVER);
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.method_l = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALER_UNDER);

	//Set IME Separate Img Infor.
	if (!(IPL_CtrlGetInfor(id, IPLCTRL_EXT_FUNC_EN) & ICF_FUNC_STITCH)) {
		ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P1_EN, &ipc_info->ICF_FC.BaseInfo.IME_p1_info, &ipc_info->ICF_FC.BaseInfo.IME_p1_encode_en);

		ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P2_EN, &ipc_info->ICF_FC.BaseInfo.IME_p2_info, NULL);

		ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P3_EN, &ipc_info->ICF_FC.BaseInfo.IME_p3_info, NULL);

		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ipc_info->ICF_FC.BaseInfo.IME_p4_info.info, NULL);

		ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN);
		if (ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable == ENABLE) {
			ipc_info->ICF_FC.BaseInfo.IME_p4_info.EdgeMapBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS);
			ipc_info->ICF_FC.BaseInfo.IME_p4_info.HistoBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS);
		}
	} else {
		/*  //Jarkko tmp
		            ipc_info->ICF_FC.IME_P1_SprtEn = ENABLE;
		            IPL_CtrlInitIpc_IMEPxOutInfo_Stitch(id, IPLCTRL_IME_P1_EN, &ipc_info->ICF_FC.BaseInfo.IME_P1_PPB0, &ipc_info->ICF_FC.SprtP1Img);
		            IPL_CtrlInitIpc_DispPxPPB_Stitch(id, IPLCTRL_IME_P1_EN);
		            ipc_info->ICF_FC.BaseInfo.IME_p1_info.crop_info.Start.x = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_OUT_CROP_STR_X);
		            ipc_info->ICF_FC.BaseInfo.IME_p1_info.crop_info.Start.y = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_OUT_CROP_STR_Y);
		            ipc_info->ICF_FC.BaseInfo.IME_p1_info.crop_info.Width = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_OUT_CROP_H);
		            ipc_info->ICF_FC.BaseInfo.IME_p1_info.crop_info.Height = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_OUT_CROP_V);

		            ipc_info->ICF_FC.IME_P2_SprtEn = ENABLE;
		            IPL_CtrlInitIpc_IMEPxOutInfo_Stitch(id, IPLCTRL_IME_P2_EN, &ipc_info->ICF_FC.BaseInfo.IME_P2_PPB0, &ipc_info->ICF_FC.SprtP2Img);
		            IPL_CtrlInitIpc_DispPxPPB_Stitch(id, IPLCTRL_IME_P2_EN);
		            ipc_info->ICF_FC.BaseInfo.IME_p2_info.crop_info.Start.x = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_OUT_CROP_STR_X);
		            ipc_info->ICF_FC.BaseInfo.IME_p2_info.crop_info.Start.y = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_OUT_CROP_STR_Y);
		            ipc_info->ICF_FC.BaseInfo.IME_p2_info.crop_info.Width = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_OUT_CROP_H);
		            ipc_info->ICF_FC.BaseInfo.IME_p2_info.crop_info.Height = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_OUT_CROP_V);

		            ipc_info->ICF_FC.IME_P3_SprtEn = ENABLE;
		            IPL_CtrlInitIpc_IMEPxOutInfo_Stitch(id, IPLCTRL_IME_P3_EN, &ipc_info->ICF_FC.BaseInfo.IME_P3_PPB0, &ipc_info->ICF_FC.SprtP3Img);
		            IPL_CtrlInitIpc_DispPxPPB_Stitch(id, IPLCTRL_IME_P3_EN);
		            ipc_info->ICF_FC.BaseInfo.IME_p3_info.crop_info.Start.x = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_OUT_CROP_STR_X);
		            ipc_info->ICF_FC.BaseInfo.IME_p3_info.crop_info.Start.y = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_OUT_CROP_STR_Y);
		            ipc_info->ICF_FC.BaseInfo.IME_p3_info.crop_info.Width = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_OUT_CROP_H);
		            ipc_info->ICF_FC.BaseInfo.IME_p3_info.crop_info.Height = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_OUT_CROP_V);

		            ipc_info->ICF_FC.BaseInfo.IME_P4_ENABLE = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EN);
		            IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ipc_info->ICF_FC.BaseInfo.IME_P4_PPB0);
		            IPL_CtrlInitIpc_DispPxPPB(id, IPLCTRL_IME_P4_EN);
		            ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.crop_info.Start.x = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_OUT_CROP_STR_X);
		            ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.crop_info.Start.y = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_OUT_CROP_STR_Y);
		            ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.crop_info.Width = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_OUT_CROP_H);
		            ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.crop_info.Height = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_OUT_CROP_V);

		            if (IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN) == ENABLE)
		            {
		                ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable = ENABLE;
		                ipc_info->ICF_FC.BaseInfo.IME_p4_info.EdgeMapBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p4_info.HistoBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS);
		            }

		            if (id == IPL_ID_1)
		            {
		                ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.YBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.UVBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_SPRT_CBUFOFS);

		                ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.YBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.UVBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_SPRT_CBUFOFS);

		                ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.YBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.UVBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_SPRT_CBUFOFS);
		            }
		            else
		            {
		                ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.YBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.UVBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_SPRT_CBUFOFS);

		                ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.YBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.UVBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_SPRT_CBUFOFS);

		                ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.YBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.UVBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_SPRT_CBUFOFS);
		            }
		*/
	}
	ipc_info->ICF_FC.fp_AdaptSetting = flow_info->fp_AdaptSetting;
	//engine clock
	ipc_info->ICF_FC.Ext.fp_SIEClk = flow_info->fp_SIEClk;
	ipc_info->ICF_FC.Ext.fp_SIEClkSrc = flow_info->fp_SIEClkSrc;
	ipc_info->ICF_FC.Ext.fp_SIEPclkSel = flow_info->fp_SIEPclkSel;
	ipc_info->ICF_FC.Ext.fp_RHEClk = flow_info->fp_RHEClk;
	ipc_info->ICF_FC.Ext.fp_IFEClk = flow_info->fp_IFEClk;
	ipc_info->ICF_FC.Ext.fp_IFE2Clk = flow_info->fp_IFE2Clk;
	ipc_info->ICF_FC.Ext.fp_DCEClk = flow_info->fp_DCEClk;
	ipc_info->ICF_FC.Ext.fp_IPEClk = flow_info->fp_IPEClk;
	ipc_info->ICF_FC.Ext.fp_IMEClk = flow_info->fp_IMEClk;

	//engine setting
	ipc_info->ICF_FC.Ext.fp_SieInit = flow_info->fp_SieInit;
	ipc_info->ICF_FC.Ext.fp_RheInit = flow_info->fp_RheInit;
	ipc_info->ICF_FC.Ext.fp_IfeInit = flow_info->fp_IfeInit;
	ipc_info->ICF_FC.Ext.fp_DceInit = flow_info->fp_DceInit;
	ipc_info->ICF_FC.Ext.fp_IpeInit = flow_info->fp_IpeInit;
	ipc_info->ICF_FC.Ext.fp_ImeInit = flow_info->fp_ImeInit;
	ipc_info->ICF_FC.Ext.fp_Ife2Init = flow_info->fp_IFE2Init;
}

void IPL_CtrlInitIpcInfoFlowCCIR(UINT32 id, IPC_INFO *ipc_info)
{
	SEN_STATUS_PARAM sen_status = {0};
	IPLCTRL_FLOW_INFO *flow_info;
	ER rt = E_OK;

	flow_info = IPL_GetCtrlFlowInfo();
	ipc_info->ICF_FC.BaseInfo.proc_bit_id = 1 << id; //IPL_CtrlGetInfor(id, IPLCTRL_MF_TOTAL_FRM_BIT);
	ipc_info->ICF_FC.ParaIdx = flow_info->IPL_HalParamId[id];

	ipc_info->ICF_FC.BaseInfo.IPLCFMode = IPL_CF_CCIR;
	ipc_info->ICF_FC.BaseInfo.IPLCFModeExt = IPL_CtrlGetInfor(id, IPLCTRL_CFMODEEXT);
	ipc_info->ICF_FC.BaseInfo.FlipInfo = IPL_CtrlGetInfor(id, IPLCTRL_IPL_FLIP_TYPE);

	sen_status.sensor_mode = IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE);
	rt = sensor_get_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_GET_STATUS, (void *)&sen_status);
	if (rt != E_OK || sen_status.sensor_info.mode == NULL) {
		DBG_ERR("Get Sensor Status Fail id:%d, Sensor_Mode: %d\r\n", IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE));
		return;
	}

	IPL_CtrlInitIpc_SIEAct(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo.SIE_Act);
	IPL_CtrlInitIpc_SIEIn(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo.SIE_In, &ipc_info->ICF_FC.BaseInfo.SIE_Ch0_Bayer_Type);
	IPL_CtrlInitIpc_SIESignal(id, &ipc_info->ICF_FC.BaseInfo.Sensor_In);

    if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh0PPB(id, &ipc_info->ICF_FC.BaseInfo);

		if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN) == ENABLE) {
			IPL_CtrlInitIpc_SIECh5PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch5_Ppb_Addr[0]);
		}
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH1_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh1PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch1_Img, &ipc_info->ICF_FC.BaseInfo.SIE_Ch1_Ppb_Addr[0]);
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_LA_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh2PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch2_Ppb_Addr[0]);
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_EN) == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.IPLCFModeExt |= IPL_CFEXT_CH3_OUT;
		IPL_CtrlInitIpc_SIECh3PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Img, &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Ppb_Addr[0], &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Ppb_Num);
	}

    IPL_CtrlInitIpc_IPLInPPB(id, &ipc_info->ICF_FC.BaseInfo.IPL_In, &ipc_info->ICF_FC.BaseInfo.IPL_StPos, &ipc_info->ICF_FC.BaseInfo.RHE_Mode);

    ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.defog_en = IPL_CtrlGetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.defog_en == ENABLE) {
		IPL_CtrlInitIpc_RHESubOutPPB(id, &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.addr[0], &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.subout_width, &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.subout_height);
	}

    IPL_CtrlInitIpc_DCEIn(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo);

    if (IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_EN) == ENABLE || IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN) == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn = ENABLE;
	} else {
		ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn = DISABLE;
	}

	if (ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn == ENABLE) {
		IPL_CtrlInitIpc_IPEEthPPB(id, &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.eth_addr[0], &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.eth_addr_subspl[0], &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.LineOfs);
	}

	ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_en = IPL_CtrlGetInfor(id, IPLCTRL_IPE_VA_OUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_en == ENABLE) {
		IPL_CtrlInitIpc_IPEVAPPB(id, &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_addr[0]);
	}

	ipc_info->ICF_FC.BaseInfo.LCA_info.LcaEn = IPL_CtrlGetInfor(id, IPLCTRL_IFE2_LCA_EN);
	if (ipc_info->ICF_FC.BaseInfo.LCA_info.LcaEn == ENABLE) {
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_SUB_OUT_1, &ipc_info->ICF_FC.BaseInfo.LCA_info.addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_NUM));
	}

	//primacy mask
	ipc_info->ICF_FC.BaseInfo.PriMsk.pixelation_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_EN);
	if (ipc_info->ICF_FC.BaseInfo.PriMsk.pixelation_en == ENABLE) {
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_PRI_MASK_1, &ipc_info->ICF_FC.BaseInfo.PriMsk.addr[0], IPLBUF_IME_PRI_MASK_MAX - IPLBUF_IME_PRI_MASK_1);
	}

	//TMNR out
	ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_EN);
	if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_CTRL_EN) & IPL_EXT_CTRL_TMNR_SHARE_BUF) {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_buf_share_en = ENABLE;
	} else {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_buf_share_en = DISABLE;
	}
	if (ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_en == ENABLE) {
		IQS_TMNR_YCC_COMPRESSION_INFO *ycc_comp_info;

		ycc_comp_info = iqs_get_ycc_compression_info();

		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.mot_bufsize =  IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_MOT_BUF_SIZE);
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.period = ycc_comp_info->period;
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.period_length = ycc_comp_info->period_length;
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_TMNR_MOTION_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.mot_addr[0], IPLBUF_IME_TMNR_MOTION_OUT_MAX - IPLBUF_IME_TMNR_MOTION_OUT_1);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_TMNR_STA_INFO_1, &ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.sta_addr[0], IPLBUF_IME_TMNR_STA_INFO_MAX - IPLBUF_IME_TMNR_STA_INFO_1);
	}

	//MD out
	ipc_info->ICF_FC.BaseInfo.ime_md_info.md_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EN);
	if (ipc_info->ICF_FC.BaseInfo.ime_md_info.md_en == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.ime_md_info.sta_bufsize =  IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_SIZE);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_MD_STA_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_md_info.sta_addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_NUM));
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_MD_EVT_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_md_info.evt_addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EVT_BUF_NUM));
	}

	//set ime yuv type
	ipc_info->ICF_FC.BaseInfo.ime_yuv_type = IPL_CtrlGetInfor(id, IPLCTRL_IME_YUV_TYPE);
	//set ime scale method
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.threshold = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALE_RATIO_THR);
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.method_h = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALER_OVER);
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.method_l = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALER_UNDER);

	//Set IME Separate Img Infor.
	if (!(IPL_CtrlGetInfor(id, IPLCTRL_EXT_FUNC_EN) & ICF_FUNC_STITCH)) {
		ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P1_EN, &ipc_info->ICF_FC.BaseInfo.IME_p1_info, &ipc_info->ICF_FC.BaseInfo.IME_p1_encode_en);

		ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P2_EN, &ipc_info->ICF_FC.BaseInfo.IME_p2_info, NULL);

		ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P3_EN, &ipc_info->ICF_FC.BaseInfo.IME_p3_info, NULL);

		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ipc_info->ICF_FC.BaseInfo.IME_p4_info.info, NULL);

		ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN);
		if (ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable == ENABLE) {
			ipc_info->ICF_FC.BaseInfo.IME_p4_info.EdgeMapBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS);
			ipc_info->ICF_FC.BaseInfo.IME_p4_info.HistoBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS);
		}
	}
    ipc_info->ICF_FC.fp_AdaptSetting = flow_info->fp_AdaptSetting;
	//engine clock
	ipc_info->ICF_FC.Ext.fp_SIEClk = flow_info->fp_SIEClk;
	ipc_info->ICF_FC.Ext.fp_SIEClkSrc = flow_info->fp_SIEClkSrc;
	ipc_info->ICF_FC.Ext.fp_SIEPclkSel = flow_info->fp_SIEPclkSel;
	ipc_info->ICF_FC.Ext.fp_IFE2Clk = flow_info->fp_IFE2Clk;
	ipc_info->ICF_FC.Ext.fp_DCEClk = flow_info->fp_DCEClk;
	ipc_info->ICF_FC.Ext.fp_IPEClk = flow_info->fp_IPEClk;
	ipc_info->ICF_FC.Ext.fp_IMEClk = flow_info->fp_IMEClk;

	//engine setting
	ipc_info->ICF_FC.Ext.fp_SieInit = flow_info->fp_SieInit;
	ipc_info->ICF_FC.Ext.fp_DceInit = flow_info->fp_DceInit;
	ipc_info->ICF_FC.Ext.fp_IpeInit = flow_info->fp_IpeInit;
	ipc_info->ICF_FC.Ext.fp_ImeInit = flow_info->fp_ImeInit;
	ipc_info->ICF_FC.Ext.fp_Ife2Init = flow_info->fp_IFE2Init;
}

void IPL_CtrlInitIpcInfoFlowDirect(UINT32 id, IPC_INFO *ipc_info)
{
	SEN_STATUS_PARAM sen_status = {0};
	IPLCTRL_FLOW_INFO *flow_info;
	UINT32 flip_type;
	ER rt = E_OK;

	flow_info = IPL_GetCtrlFlowInfo();
	if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_FUNC_EN) & ICF_FUNC_SHDR) {
		ipc_info->ICF_FC.BaseInfo.proc_bit_id = IPL_CtrlGetInfor(id, IPLCTRL_MF_TOTAL_FRM_BIT);
	} else {
		ipc_info->ICF_FC.BaseInfo.proc_bit_id = 1 << id;
	}
	ipc_info->ICF_FC.ParaIdx = flow_info->IPL_HalParamId[id];
	ipc_info->ICF_FC.BaseInfo.IPLCFMode = IPL_CF_DIRECT;
	ipc_info->ICF_FC.BaseInfo.IPLCFModeExt = IPL_CtrlGetInfor(id, IPLCTRL_CFMODEEXT);

	sen_status.sensor_mode = IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE);
	rt = sensor_get_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_GET_STATUS, (void *)&sen_status);
	if (rt != E_OK || sen_status.sensor_info.mode == NULL) {
		DBG_ERR("Get Sensor Status Fail id:%d, Sensor_Mode: %d\r\n", IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_SEN_MODE));
		return;
	}
	//Set Sensor flip/Mirror
	ipc_info->ICF_FC.BaseInfo.FlipInfo = IPL_CtrlGetInfor(id, IPLCTRL_IPL_FLIP_TYPE);
	flip_type = IPL_CtrlGetInfor(id, IPLCTRL_SEN_FLIP_TYPE);
	rt = sensor_set_info(IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)), SEN_SET_USER_OPTION, (void *)&flip_type);
	if (rt == E_OK) {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVSTPIX, IPL_UTI_CONV_SEN_STPIX(sen_status.sensor_info.mode->stpix));
	} else {
		DBG_ERR("Set Sensor User Option Fail id: %d", IPL_UTI_CONV2_SEN_ID(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID)));
	}

	IPL_CtrlInitIpc_SIEAct(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo.SIE_Act);
	IPL_CtrlInitIpc_SIEIn(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo.SIE_In, &ipc_info->ICF_FC.BaseInfo.SIE_Ch0_Bayer_Type);
	IPL_CtrlInitIpc_SIESignal(id, &ipc_info->ICF_FC.BaseInfo.Sensor_In);

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh0PPB(id, &ipc_info->ICF_FC.BaseInfo);

		if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN) == ENABLE) {
			IPL_CtrlInitIpc_SIECh5PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch5_Ppb_Addr[0]);
		}
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CA_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh1PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch1_Img, &ipc_info->ICF_FC.BaseInfo.SIE_Ch1_Ppb_Addr[0]);
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_LA_EN) == ENABLE) {
		IPL_CtrlInitIpc_SIECh2PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch2_Ppb_Addr[0]);
	}

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_EN) == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.IPLCFModeExt |= IPL_CFEXT_CH3_OUT;
		IPL_CtrlInitIpc_SIECh3PPB(id, &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Img, &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Ppb_Addr[0], &ipc_info->ICF_FC.BaseInfo.SIE_Ch3_Ppb_Num);
	}

	IPL_CtrlInitIpc_IPLInPPB(id, &ipc_info->ICF_FC.BaseInfo.IPL_In, &ipc_info->ICF_FC.BaseInfo.IPL_StPos, &ipc_info->ICF_FC.BaseInfo.RHE_Mode);

	ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.defog_en = IPL_CtrlGetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.defog_en == ENABLE) {
		IPL_CtrlInitIpc_RHESubOutPPB(id, &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.addr[0], &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.subout_width, &ipc_info->ICF_FC.BaseInfo.RHE_Defog_info.subout_height);
	}

	IPL_CtrlInitIpc_DCEIn(id, &sen_status.sensor_info, &ipc_info->ICF_FC.BaseInfo);

	if (IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_EN) == ENABLE || IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN) == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn = ENABLE;
	} else {
		ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn = DISABLE;
	}

	if (ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn == ENABLE) {
		IPL_CtrlInitIpc_IPEEthPPB(id, &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.eth_addr[0], &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.eth_addr_subspl[0], &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.LineOfs);
	}

	ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_en = IPL_CtrlGetInfor(id, IPLCTRL_IPE_VA_OUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_en == ENABLE) {
		IPL_CtrlInitIpc_IPEVAPPB(id, &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_addr[0]);
	}

	ipc_info->ICF_FC.BaseInfo.LCA_info.LcaEn = IPL_CtrlGetInfor(id, IPLCTRL_IFE2_LCA_EN);
	if (ipc_info->ICF_FC.BaseInfo.LCA_info.LcaEn == ENABLE) {
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_SUB_OUT_1, &ipc_info->ICF_FC.BaseInfo.LCA_info.addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_NUM));
	}

	//primacy mask
	ipc_info->ICF_FC.BaseInfo.PriMsk.pixelation_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_EN);
	if (ipc_info->ICF_FC.BaseInfo.PriMsk.pixelation_en == ENABLE) {
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_PRI_MASK_1, &ipc_info->ICF_FC.BaseInfo.PriMsk.addr[0], IPLBUF_IME_PRI_MASK_MAX - IPLBUF_IME_PRI_MASK_1);
	}

	//TMNR out
	ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_EN);
	if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_CTRL_EN) & IPL_EXT_CTRL_TMNR_SHARE_BUF) {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_buf_share_en = ENABLE;
	} else {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_buf_share_en = DISABLE;
	}
	if (ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_en == ENABLE) {
		IQS_TMNR_YCC_COMPRESSION_INFO *ycc_comp_info;

		ycc_comp_info = iqs_get_ycc_compression_info();

		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.mot_bufsize =  IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_MOT_BUF_SIZE);
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.period = ycc_comp_info->period;
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.period_length = ycc_comp_info->period_length;
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_TMNR_MOTION_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.mot_addr[0], IPLBUF_IME_TMNR_MOTION_OUT_MAX - IPLBUF_IME_TMNR_MOTION_OUT_1);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_TMNR_STA_INFO_1, &ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.sta_addr[0], IPLBUF_IME_TMNR_STA_INFO_MAX - IPLBUF_IME_TMNR_STA_INFO_1);
	}

	//MD out
	ipc_info->ICF_FC.BaseInfo.ime_md_info.md_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EN);
	if (ipc_info->ICF_FC.BaseInfo.ime_md_info.md_en == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.ime_md_info.sta_bufsize =  IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_SIZE);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_MD_STA_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_md_info.sta_addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_NUM));
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_MD_EVT_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_md_info.evt_addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EVT_BUF_NUM));
	}

	//set ime yuv type
	ipc_info->ICF_FC.BaseInfo.ime_yuv_type = IPL_CtrlGetInfor(id, IPLCTRL_IME_YUV_TYPE);
	//set ime scale method
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.threshold = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALE_RATIO_THR);
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.method_h = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALER_OVER);
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.method_l = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALER_UNDER);

	//Set IME Separate Img Infor.
	if (!(IPL_CtrlGetInfor(id, IPLCTRL_EXT_FUNC_EN) & ICF_FUNC_STITCH)) {
		ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P1_EN, &ipc_info->ICF_FC.BaseInfo.IME_p1_info, &ipc_info->ICF_FC.BaseInfo.IME_p1_encode_en);

		ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P2_EN, &ipc_info->ICF_FC.BaseInfo.IME_p2_info, NULL);

		ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.enable = DISABLE;
		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P3_EN, &ipc_info->ICF_FC.BaseInfo.IME_p3_info, NULL);

		IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ipc_info->ICF_FC.BaseInfo.IME_p4_info.info, NULL);

		ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN);
		if (ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable == ENABLE) {
			ipc_info->ICF_FC.BaseInfo.IME_p4_info.EdgeMapBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS);
			ipc_info->ICF_FC.BaseInfo.IME_p4_info.HistoBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS);
		}
	} else {
		/*  //Jarkko tmp
		            ipc_info->ICF_FC.IME_P1_SprtEn = ENABLE;
		            IPL_CtrlInitIpc_IMEPxOutInfo_Stitch(id, IPLCTRL_IME_P1_EN, &ipc_info->ICF_FC.BaseInfo.IME_P1_PPB0, &ipc_info->ICF_FC.SprtP1Img);
		            IPL_CtrlInitIpc_DispPxPPB_Stitch(id, IPLCTRL_IME_P1_EN);
		            ipc_info->ICF_FC.BaseInfo.IME_p1_info.crop_info.Start.x = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_OUT_CROP_STR_X);
		            ipc_info->ICF_FC.BaseInfo.IME_p1_info.crop_info.Start.y = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_OUT_CROP_STR_Y);
		            ipc_info->ICF_FC.BaseInfo.IME_p1_info.crop_info.Width = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_OUT_CROP_H);
		            ipc_info->ICF_FC.BaseInfo.IME_p1_info.crop_info.Height = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_OUT_CROP_V);

		            ipc_info->ICF_FC.IME_P2_SprtEn = ENABLE;
		            IPL_CtrlInitIpc_IMEPxOutInfo_Stitch(id, IPLCTRL_IME_P2_EN, &ipc_info->ICF_FC.BaseInfo.IME_P2_PPB0, &ipc_info->ICF_FC.SprtP2Img);
		            IPL_CtrlInitIpc_DispPxPPB_Stitch(id, IPLCTRL_IME_P2_EN);
		            ipc_info->ICF_FC.BaseInfo.IME_p2_info.crop_info.Start.x = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_OUT_CROP_STR_X);
		            ipc_info->ICF_FC.BaseInfo.IME_p2_info.crop_info.Start.y = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_OUT_CROP_STR_Y);
		            ipc_info->ICF_FC.BaseInfo.IME_p2_info.crop_info.Width = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_OUT_CROP_H);
		            ipc_info->ICF_FC.BaseInfo.IME_p2_info.crop_info.Height = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_OUT_CROP_V);

		            ipc_info->ICF_FC.IME_P3_SprtEn = ENABLE;
		            IPL_CtrlInitIpc_IMEPxOutInfo_Stitch(id, IPLCTRL_IME_P3_EN, &ipc_info->ICF_FC.BaseInfo.IME_P3_PPB0, &ipc_info->ICF_FC.SprtP3Img);
		            IPL_CtrlInitIpc_DispPxPPB_Stitch(id, IPLCTRL_IME_P3_EN);
		            ipc_info->ICF_FC.BaseInfo.IME_p3_info.crop_info.Start.x = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_OUT_CROP_STR_X);
		            ipc_info->ICF_FC.BaseInfo.IME_p3_info.crop_info.Start.y = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_OUT_CROP_STR_Y);
		            ipc_info->ICF_FC.BaseInfo.IME_p3_info.crop_info.Width = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_OUT_CROP_H);
		            ipc_info->ICF_FC.BaseInfo.IME_p3_info.crop_info.Height = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_OUT_CROP_V);

		            ipc_info->ICF_FC.BaseInfo.IME_P4_ENABLE = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EN);
		            IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ipc_info->ICF_FC.BaseInfo.IME_P4_PPB0);
		            IPL_CtrlInitIpc_DispPxPPB(id, IPLCTRL_IME_P4_EN);
		            ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.crop_info.Start.x = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_OUT_CROP_STR_X);
		            ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.crop_info.Start.y = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_OUT_CROP_STR_Y);
		            ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.crop_info.Width = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_OUT_CROP_H);
		            ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.crop_info.Height = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_OUT_CROP_V);

		            if (IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN) == ENABLE)
		            {
		                ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable = ENABLE;
		                ipc_info->ICF_FC.BaseInfo.IME_p4_info.EdgeMapBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p4_info.HistoBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS);
		            }

		            if (id == IPL_ID_1)
		            {
		                ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.YBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.UVBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_SPRT_CBUFOFS);

		                ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.YBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.UVBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_SPRT_CBUFOFS);

		                ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.YBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.UVBufOfs = -IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_SPRT_CBUFOFS);
		            }
		            else
		            {
		                ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.YBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.UVBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P1_SPRT_CBUFOFS);

		                ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.YBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.UVBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P2_SPRT_CBUFOFS);

		                ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.YBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_SPRT_YBUFOFS);
		                ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.UVBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P3_SPRT_CBUFOFS);
		            }
		*/
	}
	ipc_info->ICF_FC.fp_AdaptSetting = flow_info->fp_AdaptSetting;
	//engine clock
	ipc_info->ICF_FC.Ext.fp_SIEClk = flow_info->fp_SIEClk;
	ipc_info->ICF_FC.Ext.fp_SIEClkSrc = flow_info->fp_SIEClkSrc;
	ipc_info->ICF_FC.Ext.fp_SIEPclkSel = flow_info->fp_SIEPclkSel;
	ipc_info->ICF_FC.Ext.fp_RHEClk = flow_info->fp_RHEClk;
	ipc_info->ICF_FC.Ext.fp_IFEClk = flow_info->fp_IFEClk;
	ipc_info->ICF_FC.Ext.fp_IFE2Clk = flow_info->fp_IFE2Clk;
	ipc_info->ICF_FC.Ext.fp_DCEClk = flow_info->fp_DCEClk;
	ipc_info->ICF_FC.Ext.fp_IPEClk = flow_info->fp_IPEClk;
	ipc_info->ICF_FC.Ext.fp_IMEClk = flow_info->fp_IMEClk;

	//engine setting
	ipc_info->ICF_FC.Ext.fp_SieInit = flow_info->fp_SieInit;
	ipc_info->ICF_FC.Ext.fp_RheInit = flow_info->fp_RheInit;
	ipc_info->ICF_FC.Ext.fp_IfeInit = flow_info->fp_IfeInit;
	ipc_info->ICF_FC.Ext.fp_DceInit = flow_info->fp_DceInit;
	ipc_info->ICF_FC.Ext.fp_IpeInit = flow_info->fp_IpeInit;
	ipc_info->ICF_FC.Ext.fp_ImeInit = flow_info->fp_ImeInit;
	ipc_info->ICF_FC.Ext.fp_Ife2Init = flow_info->fp_IFE2Init;
}

void IPL_CtrlInitIpcInfoFlowVirtual(UINT32 id, IPC_INFO *ipc_info)
{
	IPLCTRL_FLOW_INFO *flow_info;

	flow_info = IPL_GetCtrlFlowInfo();
	if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_FUNC_EN) & ICF_FUNC_SHDR) {
		ipc_info->ICF_FC.BaseInfo.proc_bit_id = IPL_CtrlGetInfor(id, IPLCTRL_MF_TOTAL_FRM_BIT);
	} else {
		ipc_info->ICF_FC.BaseInfo.proc_bit_id = 1 << id;
	}
	ipc_info->ICF_FC.ParaIdx = flow_info->IPL_HalParamId[id];
	ipc_info->ICF_FC.BaseInfo.IPLCFMode = IPL_CF_NORMAL;
	ipc_info->ICF_FC.BaseInfo.IPLCFModeExt = IPL_CtrlGetInfor(id, IPLCTRL_CFMODEEXT);
	ipc_info->ICF_FC.BaseInfo.FlipInfo = IPL_CtrlGetInfor(id, IPLCTRL_IPL_FLIP_TYPE);

	ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn = IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.EthEn == ENABLE) {
		IPL_CtrlInitIpc_IPEEthPPB(id, &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.eth_addr[0], &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.eth_addr_subspl[0], &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.LineOfs);
	}

	ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_en = IPL_CtrlGetInfor(id, IPLCTRL_IPE_VA_OUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_en == ENABLE) {
		IPL_CtrlInitIpc_IPEVAPPB(id, &ipc_info->ICF_FC.BaseInfo.IPE_EthVA_info.va_addr[0]);
	}

	ipc_info->ICF_FC.BaseInfo.LCA_info.LcaEn = IPL_CtrlGetInfor(id, IPLCTRL_IFE2_LCA_EN);
	if (ipc_info->ICF_FC.BaseInfo.LCA_info.LcaEn == ENABLE) {
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_SUB_OUT_1, &ipc_info->ICF_FC.BaseInfo.LCA_info.addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_NUM));
	}

	//primacy mask
	ipc_info->ICF_FC.BaseInfo.PriMsk.pixelation_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_EN);
	if (ipc_info->ICF_FC.BaseInfo.PriMsk.pixelation_en == ENABLE) {
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_PRI_MASK_1, &ipc_info->ICF_FC.BaseInfo.PriMsk.addr[0], IPLBUF_IME_PRI_MASK_MAX - IPLBUF_IME_PRI_MASK_1);
	}

	//TMNR out
	ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_EN);
	if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_CTRL_EN) & IPL_EXT_CTRL_TMNR_SHARE_BUF) {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_buf_share_en = ENABLE;
	} else {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_buf_share_en = DISABLE;
	}
	if (ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.tmnr_en == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.mot_bufsize =  IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_MOT_BUF_SIZE);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_TMNR_MOTION_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.mot_addr[0], IPLBUF_IME_TMNR_MOTION_OUT_MAX - IPLBUF_IME_TMNR_MOTION_OUT_1);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_TMNR_STA_INFO_1, &ipc_info->ICF_FC.BaseInfo.ime_tmnr_info.sta_addr[0], IPLBUF_IME_TMNR_STA_INFO_MAX - IPLBUF_IME_TMNR_STA_INFO_1);
	}

	//MD out
	ipc_info->ICF_FC.BaseInfo.ime_md_info.md_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EN);
	if (ipc_info->ICF_FC.BaseInfo.ime_md_info.md_en == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.ime_md_info.sta_bufsize =  IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_SIZE);
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_MD_STA_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_md_info.sta_addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_NUM));
		IPL_CtrlInitIpc_IMESubFuncPPB(id, IPLBUF_IME_MD_EVT_OUT_1, &ipc_info->ICF_FC.BaseInfo.ime_md_info.evt_addr[0], IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EVT_BUF_NUM));
	}

	//set ime yuv type
	ipc_info->ICF_FC.BaseInfo.ime_yuv_type = IPL_CtrlGetInfor(id, IPLCTRL_IME_YUV_TYPE);
	//set ime scale method
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.threshold = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALE_RATIO_THR);
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.method_h = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALER_OVER);
	ipc_info->ICF_FC.BaseInfo.ime_scl_info.method_l = IPL_CtrlGetInfor(id, IPLCTRL_IME_SCALER_UNDER);

	ipc_info->ICF_FC.BaseInfo.IME_p1_info.sprt_info.enable = DISABLE;
	IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P1_EN, &ipc_info->ICF_FC.BaseInfo.IME_p1_info, &ipc_info->ICF_FC.BaseInfo.IME_p1_encode_en);

	ipc_info->ICF_FC.BaseInfo.IME_p2_info.sprt_info.enable = DISABLE;
	IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P2_EN, &ipc_info->ICF_FC.BaseInfo.IME_p2_info, NULL);

	ipc_info->ICF_FC.BaseInfo.IME_p3_info.sprt_info.enable = DISABLE;
	IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P3_EN, &ipc_info->ICF_FC.BaseInfo.IME_p3_info, NULL);

	ipc_info->ICF_FC.BaseInfo.IME_p4_info.info.enable = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EN);
	IPL_CtrlInitIpc_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ipc_info->ICF_FC.BaseInfo.IME_p4_info.info, NULL);

	ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN);
	if (ipc_info->ICF_FC.BaseInfo.IME_p4_info.ext_out_enable == ENABLE) {
		ipc_info->ICF_FC.BaseInfo.IME_p4_info.EdgeMapBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS);
		ipc_info->ICF_FC.BaseInfo.IME_p4_info.HistoBufOfs = IPL_CtrlGetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS);
	}

	ipc_info->ICF_FC.fp_AdaptSetting = flow_info->fp_AdaptSetting;
	//engine clock
	ipc_info->ICF_FC.Ext.fp_RHEClk = flow_info->fp_RHEClk;
	ipc_info->ICF_FC.Ext.fp_IFEClk = flow_info->fp_IFEClk;
	ipc_info->ICF_FC.Ext.fp_IFE2Clk = flow_info->fp_IFE2Clk;
	ipc_info->ICF_FC.Ext.fp_DCEClk = flow_info->fp_DCEClk;
	ipc_info->ICF_FC.Ext.fp_IPEClk = flow_info->fp_IPEClk;
	ipc_info->ICF_FC.Ext.fp_IMEClk = flow_info->fp_IMEClk;

	//engine setting
	ipc_info->ICF_FC.Ext.fp_RheInit = flow_info->fp_RheInit;
	ipc_info->ICF_FC.Ext.fp_IfeInit = flow_info->fp_IfeInit;
	ipc_info->ICF_FC.Ext.fp_DceInit = flow_info->fp_DceInit;
	ipc_info->ICF_FC.Ext.fp_IpeInit = flow_info->fp_IpeInit;
	ipc_info->ICF_FC.Ext.fp_ImeInit = flow_info->fp_ImeInit;
	ipc_info->ICF_FC.Ext.fp_Ife2Init = flow_info->fp_IFE2Init;
}

#if 0
#endif
void IPL_CtrlInitbuf_infoFlowCommon(UINT32 id, IPLBUF_ENG2DRAMINFO *buf_info)
{
	//reset parameter
	memset((void *)buf_info, 0x0, sizeof(IPLBUF_ENG2DRAMINFO));

	//SIE Ch0 Output
	buf_info->sie_ch0_en  = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_EN);
	if (buf_info->sie_ch0_en  == ENABLE) {
		buf_info->sie_out_ch0.buf_num = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_BUFNUM);
		buf_info->sie_out_ch0.width = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_H);
		if ((IPL_CtrlGetInfor(id, IPLCTRL_PRVFLOW) == ICF_FLOW_DIRECT) && (IPL_CtrlGetInfor(id, IPLCTRL_EXT_FUNC_EN) & ICF_FUNC_SHDR)) {
			if (IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID) == id) {
				buf_info->sie_out_ch0.height = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_V);
			} else {
				buf_info->sie_out_ch0.height = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_RING_BUF_V);
			}
		} else {
			buf_info->sie_out_ch0.height = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_V);
		}
		buf_info->sie_out_ch0.bit = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT);
		buf_info->sie_out_ch0.line_ofs = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS);
	}

	//SIE Ch1 Output
	buf_info->sie_ch1_en  = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH1_EN);
	buf_info->sie_ca_en  = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CA_EN);
	if (buf_info->sie_ch1_en  == ENABLE) {
		buf_info->sie_ca_en  = DISABLE;
		buf_info->sie_out_ch1.buf_num = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH1_BUFNUM);
		buf_info->sie_out_ch1.width = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_H);
		buf_info->sie_out_ch1.height = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_V);
		buf_info->sie_out_ch1.line_ofs = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS);
	} else if (buf_info->sie_ca_en  == ENABLE) {
		buf_info->sie_ca_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH1_BUFNUM);
		//CA Output R/G/B/IR_th/R_th/G_th/B_th/Cnt @16bit, total 16KB * ppb
		buf_info->sie_ca_buf_size = ((IPL_CtrlGetInfor(id, IPLCTRL_SIE_CA_WINXNUM) * IPL_CtrlGetInfor(id, IPLCTRL_SIE_CA_WINYNUM) << 1) << 3);
	}

	//SIE Ch2 Output
	buf_info->sie_la_en  = IPL_CtrlGetInfor(id, IPLCTRL_SIE_LA_EN);
	if (buf_info->sie_la_en  == ENABLE) {
		buf_info->sie_la_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_SIE_LA_BUFNUM);
		//LA Output PreGamma Lum/PostGamma Lum @16bit
		//Histogram 64bin@12bit read from register
		buf_info->sie_la_buf_size = IPL_CtrlGetInfor(id, IPLCTRL_SIE_LA_WINXNUM) * IPL_CtrlGetInfor(id, IPLCTRL_SIE_LA_WINYNUM) << 2;
	}

	//SIE Ch3 Output
	buf_info->sie_ch3_en  = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_EN);
	buf_info->sie_out_ch3.buf_num = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_BUFNUM);
	if (buf_info->sie_ch3_en  == ENABLE) {
		if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_SRC) == CH3_YOUT_ACC) {
			buf_info->sie_out_ch3.width = 128;	//maximum wdr/hdr y out window number
			buf_info->sie_out_ch3.height = 128;	//maximum wdr/hdr y out window number
			buf_info->sie_out_ch3.line_ofs = IPL_ALIGN_ROUNDUP(((128 * 3) >> 1), 4);	//maximum wdr/hdr y out window number@12bit, 510 y out lineoffset need word align
		} else {
			buf_info->sie_out_ch3.width = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_SIZE_H);
			buf_info->sie_out_ch3.height = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_SIZE_V);
			buf_info->sie_out_ch3.line_ofs = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH3_SIZE_HLOS);
		}
	}
	//SIE CH5 Sub out SIZE = (Ceil(RawW/32)*2)*RawH, ref. from sie1_getBccsideSz
	//only valid when raw encode is enable and sie ch0 output enable, side info buffer
	if ((buf_info->sie_ch0_en  == ENABLE) && (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN) == ENABLE)) {
		buf_info->sie_ch5_en = ENABLE;
		buf_info->sie_ch5_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_BUFNUM);
		buf_info->sie_ch5_buf_size = (((buf_info->sie_out_ch0.width + 31) >> 5) << 1) * IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_V);
	}

	//RHE defog sub output
	buf_info->rhe_defog_sub_out_en = IPL_CtrlGetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN);
	if (buf_info->rhe_defog_sub_out_en  == ENABLE) {
		buf_info->rhe_defog_sub_out_size = 128 * 128 * 4; //subout size 128x128x4
	}

	//IPE ETH Output
	buf_info->ipe_eth_en  = IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_EN);
	if (buf_info->ipe_eth_en  == ENABLE) {
		buf_info->ipe_eth_size = (IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_HLOS) * IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_V));
	} else {
		buf_info->ipe_eth_size = 0;
	}

	//IPE ETH Sub Sample Output
	buf_info->ipe_eth_sub_sample_en = IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN);
	if (buf_info->ipe_eth_sub_sample_en  == ENABLE) {
		buf_info->ipe_eth_sub_sample_size = ((IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_HLOS) >> 1) * (IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_V) >> 1));
	} else {
		buf_info->ipe_eth_sub_sample_size = 0;
	}

	if (buf_info->ipe_eth_en == ENABLE || buf_info->ipe_eth_sub_sample_en == ENABLE) {
		buf_info->ipe_eth_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_BUF_NUM);
	}

	//IPE VA Output
	buf_info->ipe_va_en  = IPL_CtrlGetInfor(id, IPLCTRL_IPE_VA_OUT_EN);
	if (buf_info->ipe_va_en  == ENABLE) {
		buf_info->ipe_va_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_IPE_VA_OUT_BUF_NUM);
		buf_info->ipe_va_size = IPL_CtrlGetIPEVAbuf_info();
	}

	//IME Sub out for IFE2
	buf_info->ife2_lca_en  = IPL_CtrlGetInfor(id, IPLCTRL_IFE2_LCA_EN);
	if (buf_info->ife2_lca_en == ENABLE) {
		buf_info->ime_sub_out_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_NUM);
		buf_info->ime_sub_out_size = IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_YLOS) * IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_V);
	}

	//PRIMACY MASK BUF
	buf_info->ime_primacy_mask_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_EN);
	if (buf_info->ime_primacy_mask_en  == ENABLE) {
		buf_info->ime_primacy_mask_buf_size = IPL_YUV_SIZE(IPL_IMG_YUV444, IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_H), IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_V));
	}

	//TMNR BUF
	buf_info->ime_tmnr_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_EN);
	if (buf_info->ime_tmnr_en == ENABLE) {
		buf_info->ime_tmnr_motion_out_buf_size = IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_MOT_BUF_SIZE);
		buf_info->ime_tmnr_sta_info_buf_size = IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_STA_BUF_SIZE);
		buf_info->ime_tmnr_ref_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM);
		buf_info->ime_tmnr_ref_size = total_dbg_data_size + IPL_YUV_SIZE(IPL_IMG_Y_PACK_UV420, IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_H), IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_V));
	}

	//MD BUF
	buf_info->ime_md_en = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EN);
	if (buf_info->ime_md_en == ENABLE) {
		buf_info->ime_md_sta_out_buf_size = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_SIZE);
		buf_info->ime_md_sta_out_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_STA_BUF_NUM);
		buf_info->ime_md_evt_out_buf_size = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EVT_BUF_SIZE);
		buf_info->ime_md_evt_out_buf_num = IPL_CtrlGetInfor(id, IPLCTRL_IME_MD_EVT_BUF_NUM);
	}

	buf_info->ime_out_group.total_win_num_h = IPL_CtrlGetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H);
	buf_info->ime_out_group.total_win_num_v = IPL_CtrlGetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_V);
	buf_info->ime_out_group.pos_h = IPL_CtrlGetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_H);
	buf_info->ime_out_group.pos_v = IPL_CtrlGetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_V);
}

#if 0
#endif

void IPL_CtrlPrvInitFlow_IMEPxOutInfo(UINT32 id, UINT32 path_en_idx, IPL_IME_PATH_INFO *path_info)
{
	UINT32 Px;

	UINT32 Pxidx[4][12] = {
		{IPLCTRL_IME_P1_EN, IPLCTRL_IME_P1_MD_EVT_OUT_EN, IPLCTRL_IME_P1_SAMPLE_RATE, IPLCTRL_IME_P1_IMG_FMT, IPLCTRL_IME_P1_OUT_SIZE_H, IPLCTRL_IME_P1_OUT_SIZE_V, IPLCTRL_IME_P1_OUT_SIZE_HLOS, IPLCTRL_IME_P1_OUT_CROP_STR_X, IPLCTRL_IME_P1_OUT_CROP_STR_Y, IPLCTRL_IME_P1_OUT_CROP_H, IPLCTRL_IME_P1_OUT_CROP_V,  IPLCTRL_IME_P1_ENC_EN},
		{IPLCTRL_IME_P2_EN, IPLCTRL_IME_P2_MD_EVT_OUT_EN, IPLCTRL_IME_P2_SAMPLE_RATE, IPLCTRL_IME_P2_IMG_FMT, IPLCTRL_IME_P2_OUT_SIZE_H, IPLCTRL_IME_P2_OUT_SIZE_V, IPLCTRL_IME_P2_OUT_SIZE_HLOS, IPLCTRL_IME_P2_OUT_CROP_STR_X, IPLCTRL_IME_P2_OUT_CROP_STR_Y, IPLCTRL_IME_P2_OUT_CROP_H, IPLCTRL_IME_P2_OUT_CROP_V,					0},
		{IPLCTRL_IME_P3_EN, IPLCTRL_IME_P3_MD_EVT_OUT_EN, IPLCTRL_IME_P3_SAMPLE_RATE, IPLCTRL_IME_P3_IMG_FMT, IPLCTRL_IME_P3_OUT_SIZE_H, IPLCTRL_IME_P3_OUT_SIZE_V, IPLCTRL_IME_P3_OUT_SIZE_HLOS, IPLCTRL_IME_P3_OUT_CROP_STR_X, IPLCTRL_IME_P3_OUT_CROP_STR_Y, IPLCTRL_IME_P3_OUT_CROP_H, IPLCTRL_IME_P3_OUT_CROP_V,					0},
		{IPLCTRL_IME_P4_EN, IPLCTRL_IME_P4_MD_EVT_OUT_EN, IPLCTRL_IME_P4_SAMPLE_RATE, IPLCTRL_IME_P4_IMG_FMT, IPLCTRL_IME_P4_OUT_SIZE_H, IPLCTRL_IME_P4_OUT_SIZE_V, IPLCTRL_IME_P4_OUT_SIZE_HLOS, IPLCTRL_IME_P4_OUT_CROP_STR_X, IPLCTRL_IME_P4_OUT_CROP_STR_Y, IPLCTRL_IME_P4_OUT_CROP_H, IPLCTRL_IME_P4_OUT_CROP_V,					0},
	};

	switch (path_en_idx) {
	case IPLCTRL_IME_P1_EN:
		Px = 0;
		//YCC Encode setting
		if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_CTRL_EN) & IPL_EXT_CTRL_TMNR_SHARE_BUF && path_info->out_ycc_compress_en == ENABLE) {
			DBG_WRN("id: %d, path1 N.S. ycc compress when TMNR share buffer enable\r\n", id);
			IPL_CtrlSetInfor(id, Pxidx[Px][11], DISABLE);
		} else {
			IPL_CtrlSetInfor(id, Pxidx[Px][11], path_info->out_ycc_compress_en);
		}
		break;

	case IPLCTRL_IME_P2_EN:
		Px = 1;
		break;

	case IPLCTRL_IME_P3_EN:
		Px = 2;
		break;

	case IPLCTRL_IME_P4_EN:
		Px = 3;
		break;

	default:
		DBG_ERR("id: %d, PathEnidx error %d\r\n", id, path_en_idx);
		return;
	}

	IPL_CtrlSetInfor(id, Pxidx[Px][0], path_info->output_en);
	IPL_CtrlSetInfor(id, Pxidx[Px][1], path_info->md_evt_out_en);
	IPL_CtrlSetInfor(id, Pxidx[Px][2], path_info->sample_rate);

	if (path_info->output_en == ENABLE) {
		IPL_CtrlSetInfor(id, Pxidx[Px][4], path_info->scale_size_h);
		IPL_CtrlSetInfor(id, Pxidx[Px][6], path_info->out_img_lofs * IPL_CtrlGetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H));
		IPL_CtrlSetInfor(id, Pxidx[Px][5], path_info->scale_size_v);

		IPL_CtrlSetInfor(id, Pxidx[Px][7], path_info->out_crop_start_x);
		IPL_CtrlSetInfor(id, Pxidx[Px][8], path_info->out_crop_start_y);
		IPL_CtrlSetInfor(id, Pxidx[Px][9], path_info->out_crop_size_h);
		IPL_CtrlSetInfor(id, Pxidx[Px][10], path_info->out_crop_size_v);
		IPL_CtrlSetInfor(id, Pxidx[Px][3], path_info->img_fmt);
	}
}

void IPL_CtrlPrvInitFlowCommon(UINT32 id, IPLCTRL_INFO *ctrl_info)
{
	UINT32 width = 0, height = 0, rhe_sub_out_size = 0;
	IPC_QINFO ipc_info = {0};
 	awb_ca_info CAInfo = {0};
    AE_LAINFO LAInfo = {0};
	UINT32 ipl_ext_func = ICF_FUNC_NONE;
	UINT32 ipl_cf_mode_ext = IPL_CFEXT_NONE;
#if IPL_WDR_FUNC_SUPPORT
	SR_WDR_SUBIMG_INFO wdr_sub_info = {0};
#endif
#if IPL_SHDR_FUNC_SUPPORT
	SHDR_SUBIMG_INFO shdr_sub_info = {0};
#endif
	DxSys_Cfg_DirectMode(FALSE);
	ICF_SetSIEPPBNum(id, ctrl_info->chg_mode->raw_out_buf_num);
	ipc_info = IPL_Ctrl_Query(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_PRVFLOW));

	//ipl ext ctrl flow mode
	ipl_cf_mode_ext |= IPL_CFEXT_NONE;
	IPL_CtrlSetInfor(id, IPLCTRL_CFMODEEXT, ipl_cf_mode_ext);

	IPL_CtrlSetInfor(id, IPLCTRL_PRVAUTO_OB_EN, DISABLE);

	//set sie signal
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_VD_INV, ctrl_info->info->sig_info.vd_inv);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_HD_INV, ctrl_info->info->sig_info.hd_inv);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_VD_PHASE, ctrl_info->info->sig_info.vd_phase);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_HD_PHASE, ctrl_info->info->sig_info.hd_phase);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_DATA_PHASE, ctrl_info->info->sig_info.data_phase);
	//SIE Input Information
	IPL_CtrlSetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO, ctrl_info->chg_mode->crop_ratio);
	IPL_CtrlSetInfor(id, IPLCTRL_FLIP_TYPE, ctrl_info->chg_mode->flip_info);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVSTPIX, IPL_UTI_CONV_SEN_STPIX(ctrl_info->info->mode->stpix));
	IPL_DzoomGetSIECropSize(id, IPL_DzoomGetIndex(id), FALSE, &width, &height);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVCROP_SIZE_H, width);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVCROP_SIZE_V, height);

	IPL_CtrlSetInfor(id, IPLCTRL_EXT_CTRL_EN, ctrl_info->chg_mode->ext_ctrl_en);
	//ICF EXT FUNC. ON/OFF
    if (ctrl_info->chg_mode->func_en & IPL_FUNC_SHDR) {
		if (ctrl_info->info->mode->mode_type == SENSOR_MODE_STAGGER_HDR) {
			ipl_ext_func |= ICF_FUNC_SHDR;
		}
	} else if (ctrl_info->chg_mode->func_en & IPL_FUNC_WDR) {
		ipl_ext_func |= ICF_FUNC_WDR;
	}

	if (ctrl_info->chg_mode->func_en & IPL_FUNC_STITCH) {
		ipl_ext_func |= ICF_FUNC_STITCH;
	}

	if (ctrl_info->chg_mode->func_en & IPL_FUNC_DEFOG) {
		ipl_ext_func |= ICF_FUNC_DEFOG;
	}

	IPL_CtrlSetInfor(id, IPLCTRL_EXT_FUNC_EN, ipl_ext_func);

	//SIE output ch0 - raw output
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_EN, ENABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_BUFNUM, ipc_info.QUE_FC.nBUF_SIEPPB);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_H, width);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_V, height);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_RING_BUF_V, height);

	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_DISABLE_RAWENC_MANUAL) == 0) {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN, DISABLE);
	} else {
		if (ipc_info.QUE_FC.nBUF_SIEPPB == 1) {
			IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN, DISABLE);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN, ENABLE);
			IPL_AlgSetUIInfo(id, IPL_SEL_RAW_BITDEPTH_PRV, SEL_RAW_BITDEPTH_12);    //raw encode always output 12 bitdepth
		}
	}

	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_PRVBIT, IPL_AlgGetUIInfo(id, IPL_SEL_RAW_BITDEPTH_PRV));
	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN) == ENABLE) {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS, IPL_ALIGN_ROUNDUP(IPL_UTI_RAWH_CONV2_LOFS(width, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT))*IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAWENC_BUF_RATIO) / 100, 4));
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS, IPL_UTI_RAWH_CONV2_LOFS(width, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT)));
	}

	//SIE output ch1
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_EN, DISABLE);

	//SIE output ch1 - CA Out
	AWB_GetCAInfo(IPL_UTI_CONV2_AWB_ID(id), &CAInfo);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CA_EN, ENABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CA_WINXNUM, CAInfo.WinNumX);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CA_WINYNUM, CAInfo.WinNumY);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_BUFNUM, ipc_info.QUE_FC.nBUF_CAPPB);

	//SIE ch2 output - LA Out
	AE_GetLAInfo(IPL_UTI_CONV2_AE_ID(id), &LAInfo);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_EN, ENABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_WINXNUM, LAInfo.WinNumX);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_WINYNUM, LAInfo.WinNumY);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_BUFNUM, ipc_info.QUE_FC.nBUF_LAPPB);

	//SIE output ch3 - Y or VA Out
	if (ctrl_info->chg_mode->func_en & (IPL_FUNC_WDR | IPL_FUNC_SHDR)) {
		//Y output
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_EN, ENABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_SRC, CH3_YOUT_ACC);
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_BUFNUM, ipc_info.QUE_FC.nBUF_SIE_SUBPPB);

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_SHDR) {
#if IPL_SHDR_FUNC_SUPPORT
			shdr_sub_info = SensorHDR_GetSubImgInfo();
			if (shdr_sub_info.uiSubRatio == 1) {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINXNUM, IPL_UTI_SENCROPRATIO_ADJ_HSIZE(IPL_CtrlGetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO), IPL_UTI_CONV2_UINT32(1,1), shdr_sub_info.uiSubWidth, 1)); //maximum y output window number 128
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINYNUM, IPL_UTI_SENCROPRATIO_ADJ_VSIZE(IPL_CtrlGetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO), IPL_UTI_CONV2_UINT32(1,1), shdr_sub_info.uiSubHeight, 1)); //maximum y output window number 128
			} else {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINXNUM, shdr_sub_info.uiSubWidth); //maximum y output window number 128
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINYNUM, shdr_sub_info.uiSubHeight); //maximum y output window number 128
			}
#endif
		} else if (ctrl_info->chg_mode->func_en & IPL_FUNC_WDR) {
#if IPL_WDR_FUNC_SUPPORT
			SceneRender_WDR_GetSubImgInfo(IPL_UTI_CONV2_WDR_ID(id), &wdr_sub_info);
			if (wdr_sub_info.uiSubRatio == 1) {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINXNUM, IPL_UTI_SENCROPRATIO_ADJ_HSIZE(IPL_CtrlGetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO), IPL_UTI_CONV2_UINT32(1,1), wdr_sub_info.uiSubWidth, 1)); //maximum y output window number 128
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINYNUM, IPL_UTI_SENCROPRATIO_ADJ_VSIZE(IPL_CtrlGetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO), IPL_UTI_CONV2_UINT32(1,1), wdr_sub_info.uiSubHeight, 1)); //maximum y output window number 128
			} else {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINXNUM, wdr_sub_info.uiSubWidth); //maximum y output window number 128
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINYNUM, wdr_sub_info.uiSubHeight); //maximum y output window number 128
			}
#endif
		}
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_EN, DISABLE);
	}

	//set ime buffer push output type
	IPL_CtrlSetInfor(id, IPLCTRL_IME_PUSH_SORT_EN, IPL_AlgGetUIInfo(id, IPL_SEL_PUSH_OUT_TYPE));

	//HDR Sensor multi frame Setting, disable all In/Out Path except SIE
	if ((ctrl_info->chg_mode->func_en & IPL_FUNC_SHDR) && (IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID) != id)) {
		//IPE ETH Out
		IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_EN, DISABLE);
		//IFE2 Out
		IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, DISABLE);
		//IME Out
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P1_EN, DISABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P2_EN, DISABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P3_EN, DISABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EN, DISABLE);
	} else {
		//IPL input information - RHE IN
		IPL_DzoomGetRaw2YUVInSize(id, IPL_DzoomGetIndex(id), &width, &height);
		IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_BIT, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT));
		IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_H, width);
		IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_V, height);
		IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_HLOS, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS));

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_DEFOG) {
#if IPL_DEFOG_FUNC_SUPPORT
			IPL_CtrlSetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN, ENABLE);
			defog_lib_get_subimg_size(id, &rhe_sub_out_size);
#endif
			IPL_CtrlSetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_SIZE, rhe_sub_out_size);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN, DISABLE);
		}

		//IPE ETH Output
		if (ctrl_info->chg_mode->func_en & IPL_FUNC_ETH) {
			IPE_EethParam eth_param = {0};
			iq_get_ipe_eth_param(&eth_param);
			//dis use both eth out and eth subspl out, 2 bit mode
			if (eth_param.EthOutSel == SEL_ETH_ORG || eth_param.EthOutSel == SEL_ETH_BOTH) {
				IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_EN, ENABLE);
			}

			if (eth_param.EthOutSel == SEL_ETH_DOWNSAMPLED || eth_param.EthOutSel == SEL_ETH_BOTH) {
				IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN, ENABLE);
			}

			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_BUF_NUM, ipc_info.QUE_FC.nBUF_IPE_ETHPPB);
			IPL_DzoomGetRaw2YUVInSize(id, IPL_DzoomGetIndex(id), &width, &height);
            IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_H, width);
			if (eth_param.EthOutFmt == ETH_2BITS) {
                IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_HLOS, IPL_ALIGN_ROUNDUP(width>>2, 4));
			} else {
                IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_HLOS, IPL_ALIGN_ROUNDUP(width, 4));
			}
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_V, height);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_EN, DISABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN, DISABLE);
		}

		//IPE VA Output
		if (ctrl_info->chg_mode->func_en & IPL_FUNC_VA) {
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_VA_OUT_EN, ENABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_VA_OUT_BUF_NUM, ipc_info.QUE_FC.nBUF_IPE_VAPPB);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_VA_OUT_EN, DISABLE);
		}

		//PRIMACY MASK BUF
		if (ctrl_info->chg_mode->func_en & IPL_FUNC_PRIMACY_MASK) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_EN, ENABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_H, IPL_ALIGN_ROUNDUP(width >> 3, 4));
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_V, IPL_ALIGN_ROUNDUP(height >> 3, 4));
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_EN, DISABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_H, 0);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_V, 0);
		}

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_IME_TMNR) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_EN, ENABLE);
			IPL_QUE_TMNR_BUFINFO_IN tmnr_buf_in = {0};
			IPL_STRP_INFO strp_info;
			IPL_QUE_TMNR_BUFINFO_OUT tmnr_buf_out = {0};

			tmnr_buf_in.width = width;
			tmnr_buf_in.height = height;
            IPL_GetDceStrpInfo(id, &strp_info);
			tmnr_buf_in.strp_info = &strp_info;
			if (ipc_info.QUE_FC.fp_get_tmnr_bufinfo != NULL) {
				ipc_info.QUE_FC.fp_get_tmnr_bufinfo(&tmnr_buf_in, &tmnr_buf_out);
			} else {
				DBG_ERR("null fp for get tmnr buf info\r\n");
			}
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_STA_BUF_SIZE, tmnr_buf_out.sta_bufsize);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_MOT_BUF_SIZE, tmnr_buf_out.mot_bufsize);
			if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_CTRL_EN) & IPL_EXT_CTRL_TMNR_SHARE_BUF) {
				IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, 0);
			} else {
				if (width > DIR_SIE_MAX_WIDTH) {
					IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, IPL_MULTI_STRP_IME_TMNR_REF_PPB);
				} else {
					IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, IPL_SINGLE_STRP_IME_TMNR_REF_PPB);
				}
			}
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_EN, DISABLE);
		}

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_MD) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EN, ENABLE);
			IPL_QUE_MD_BUFINFO_IN md_buf_in;
			IPL_STRP_INFO strp_info;
			IPL_QUE_MD_BUFINFO_OUT md_buf_out = {0};

			md_buf_in.width = width;
			md_buf_in.height = height;
            IPL_GetDceStrpInfo(id, &strp_info);
			md_buf_in.strp_info = &strp_info;

			md_buf_in.md_win_manual = DISABLE;
			if (ipc_info.QUE_FC.fp_get_md_bufinfo != NULL) {
				ipc_info.QUE_FC.fp_get_md_bufinfo(&md_buf_in, &md_buf_out);
			} else {
				DBG_ERR("null fp for get md buf info\r\n");
			}
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_STA_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_MD_STAPPB);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_STA_BUF_SIZE, md_buf_out.sta_bufsize);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EVT_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_MD_EVTPPB);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EVT_BUF_SIZE, md_buf_out.evt_bufsize);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EN, DISABLE);
		}

		if (iq_check_ife2_lca(id, FALSE) || IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_EN)) {
			width  = IPL_UTI_IMESUB_ADJ_HSIZE(IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_H), iq_get_ife2_lca_ratio(id, FALSE, TRUE), 4);
			height = IPL_UTI_IMESUB_ADJ_VSIZE(IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_V), iq_get_ife2_lca_ratio(id, FALSE, TRUE), 4);
			IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, ENABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_LCAPPB);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_FMT, IPL_IMG_PACK_YUV444);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_H, width);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_V, height);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_YLOS, IPL_YSIZEH_CONV2LOFS(IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_FMT), IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_H)));
		} else {
			//IFE2 output
			IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, DISABLE);
		}

		//Jarkko tmp, not ready
		if (ctrl_info->chg_mode->ime_path1_out_group.group_en  == ENABLE) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H, ((ctrl_info->chg_mode->ime_path1_out_group.win_num & 0xffff0000) >> 16));
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_V, (ctrl_info->chg_mode->ime_path1_out_group.win_num & 0x0000ffff));
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_H, ((ctrl_info->chg_mode->ime_path1_out_group.out_img_pos & 0xffff0000) >> 16));
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_V, (ctrl_info->chg_mode->ime_path1_out_group.out_img_pos & 0xffff0000));
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H, 1);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_V, 1);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_H, 0);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_V, 0);
		}

		IPL_CtrlSetInfor(id, IPLCTRL_IME_YUV_TYPE, ctrl_info->chg_mode->ime_yuv_type);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALE_RATIO_THR, ctrl_info->chg_mode->ime_scale_ratio_thr);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALER_OVER, ctrl_info->chg_mode->ime_scaler_over);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALER_UNDER, ctrl_info->chg_mode->ime_scaler_under);

		IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P1_EN, &ctrl_info->chg_mode->ime_path_1);
		IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P2_EN, &ctrl_info->chg_mode->ime_path_2);
		IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P3_EN, &ctrl_info->chg_mode->ime_path_3);
		IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ctrl_info->chg_mode->ime_path_4);

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_ADAS) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN, ENABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS, ADAS_GetEdgeMapSz());
			IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS, ADAS_GetFcwsHistSz());
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN, DISABLE);
		}
	}
}

void IPL_CtrlPrvInitFlowCCIR(UINT32 id, IPLCTRL_INFO *ctrl_info)
{
	UINT32 width = 0, height = 0;
	IPC_QINFO ipc_info = {0};
	UINT32 ipl_ext_func = ICF_FUNC_NONE;
	UINT32 ipl_cf_mode_ext = IPL_CFEXT_NONE;

	DxSys_Cfg_DirectMode(FALSE);
	ICF_SetSIEPPBNum(id, ctrl_info->chg_mode->raw_out_buf_num);
	ipc_info = IPL_Ctrl_Query(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_PRVFLOW));

    //ipl ext ctrl flow mode
    if (ctrl_info->info->mode->mode_type == SENSOR_MODE_CCIR_INTERLACE)
	    ipl_cf_mode_ext |= IPL_CFEXT_CCIR_DEINTERLACE;
	IPL_CtrlSetInfor(id, IPLCTRL_CFMODEEXT, ipl_cf_mode_ext);

    IPL_CtrlSetInfor(id, IPLCTRL_PRVAUTO_OB_EN, DISABLE);

	//set sie signal
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_VD_INV, ctrl_info->info->sig_info.vd_inv);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_HD_INV, ctrl_info->info->sig_info.hd_inv);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_VD_PHASE, ctrl_info->info->sig_info.vd_phase);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_HD_PHASE, ctrl_info->info->sig_info.hd_phase);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_DATA_PHASE, ctrl_info->info->sig_info.data_phase);

	//SIE Input Information
	IPL_CtrlSetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO, ctrl_info->chg_mode->crop_ratio);
	IPL_CtrlSetInfor(id, IPLCTRL_FLIP_TYPE, ctrl_info->chg_mode->flip_info);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVSTPIX, IPL_UTI_CONV_SEN_STPIX(ctrl_info->info->mode->stpix));
	IPL_DzoomGetSIECropSize(id, IPL_DzoomGetIndex(id), FALSE, &width, &height);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVCROP_SIZE_H, width);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVCROP_SIZE_V, height);

	IPL_CtrlSetInfor(id, IPLCTRL_EXT_CTRL_EN, ctrl_info->chg_mode->ext_ctrl_en);
	//ICF EXT FUNC. ON/OFF
	if (ctrl_info->chg_mode->func_en & IPL_FUNC_STITCH) {
		ipl_ext_func |= ICF_FUNC_STITCH;
	}
	IPL_CtrlSetInfor(id, IPLCTRL_EXT_FUNC_EN, ipl_ext_func);

	//SIE output information
	if(ctrl_info->info->mode->dvi != NULL) {
		if(ctrl_info->info->mode->dvi->out_split_en == TRUE)
		{
			width = width >> 1;
			//when MD or TMNE enable, width should be multiple of 8x
			width = IPL_ALIGN_ROUNDDOWN(width,8);
		} else {
		}
	} else {
		DBG_WRN("DVI information is NULL\r\n");
	}
    IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_EN, ENABLE);
    IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_BUFNUM, ipc_info.QUE_FC.nBUF_SIEPPB);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_H, width);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_V, height);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS, width);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_RING_BUF_V, height);
    IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN, DISABLE);
	IPL_AlgSetUIInfo(id, IPL_SEL_RAW_BITDEPTH_PRV, SEL_RAW_BITDEPTH_8);    //ccir always output 8 bitdepth
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_PRVBIT, IPL_AlgGetUIInfo(id, IPL_SEL_RAW_BITDEPTH_PRV));

	//SIE ch1 output - DVI Y output
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_EN, ENABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_BUFNUM, ipc_info.QUE_FC.nBUF_SIEPPB);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_H_FLIP, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_V_FLIP, DISABLE);

	//SIE LA/CA/CH3/CH4 Output
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CA_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_EN, DISABLE);

    //set ime buffer push output type
	IPL_CtrlSetInfor(id, IPLCTRL_IME_PUSH_SORT_EN, IPL_AlgGetUIInfo(id, IPL_SEL_PUSH_OUT_TYPE));

    //IPL input information
	IPL_DzoomGetRaw2YUVInSize(id, IPL_DzoomGetIndex(id), &width, &height);
	IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_BIT, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT));
	IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_H, width);
	IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_V, height);
	IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_HLOS, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS));

    //IPE ETH Out
	IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN, DISABLE);

    //IPE VA Output
	IPL_CtrlSetInfor(id, IPLCTRL_IPE_VA_OUT_EN, DISABLE);

	//PRIMACY MASK BUF
	if (ctrl_info->chg_mode->func_en & IPL_FUNC_PRIMACY_MASK) {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_EN, ENABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_H, IPL_ALIGN_ROUNDUP(width >> 3, 4));
		IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_V, IPL_ALIGN_ROUNDUP(height >> 3, 4));
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_EN, DISABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_H, 0);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_V, 0);
	}

	if (ctrl_info->chg_mode->func_en & IPL_FUNC_IME_TMNR) {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_EN, ENABLE);
		IPL_QUE_TMNR_BUFINFO_IN tmnr_buf_in = {0};
		IPL_STRP_INFO strp_info;
		IPL_QUE_TMNR_BUFINFO_OUT tmnr_buf_out = {0};

		tmnr_buf_in.width = width;
		tmnr_buf_in.height = height;
        IPL_GetDceStrpInfo(id, &strp_info);
		tmnr_buf_in.strp_info = &strp_info;
		if (ipc_info.QUE_FC.fp_get_tmnr_bufinfo != NULL) {
			ipc_info.QUE_FC.fp_get_tmnr_bufinfo(&tmnr_buf_in, &tmnr_buf_out);
		} else {
			DBG_ERR("null fp for get tmnr buf info\r\n");
		}
		IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_STA_BUF_SIZE, tmnr_buf_out.sta_bufsize);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_MOT_BUF_SIZE, tmnr_buf_out.mot_bufsize);
		if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_CTRL_EN) & IPL_EXT_CTRL_TMNR_SHARE_BUF) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, 0);
		} else {
			if (width > DIR_SIE_MAX_WIDTH) {
				IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, IPL_MULTI_STRP_IME_TMNR_REF_PPB);
			} else {
				IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, IPL_SINGLE_STRP_IME_TMNR_REF_PPB);
			}
		}
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_EN, DISABLE);
	}

	if (ctrl_info->chg_mode->func_en & IPL_FUNC_MD) {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EN, ENABLE);
		IPL_QUE_MD_BUFINFO_IN md_buf_in;
		IPL_STRP_INFO strp_info;
		IPL_QUE_MD_BUFINFO_OUT md_buf_out = {0};

		md_buf_in.width = width;
		md_buf_in.height = height;
        IPL_GetDceStrpInfo(id, &strp_info);
		md_buf_in.strp_info = &strp_info;

		md_buf_in.md_win_manual = DISABLE;

		if (ipc_info.QUE_FC.fp_get_md_bufinfo != NULL) {
			ipc_info.QUE_FC.fp_get_md_bufinfo(&md_buf_in, &md_buf_out);
		} else {
			DBG_ERR("null fp for get md buf info\r\n");
		}
		IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_STA_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_MD_STAPPB);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_STA_BUF_SIZE, md_buf_out.sta_bufsize);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EVT_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_MD_EVTPPB);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EVT_BUF_SIZE, md_buf_out.evt_bufsize);
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EN, DISABLE);
	}

    if (iq_check_ife2_lca(id, FALSE) || IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_EN)) {
		width  = IPL_UTI_IMESUB_ADJ_HSIZE(IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_H), iq_get_ife2_lca_ratio(id, FALSE, TRUE), 4);
		height = IPL_UTI_IMESUB_ADJ_VSIZE(IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_V), iq_get_ife2_lca_ratio(id, FALSE, TRUE), 4);
		IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, ENABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_LCAPPB);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_FMT, IPL_IMG_PACK_YUV444);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_H, width);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_V, height);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_YLOS, IPL_YSIZEH_CONV2LOFS(IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_FMT), IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_H)));
	} else {
		//IFE2 output
		IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, DISABLE);
	}

	//Jarkko tmp, not ready
	if (ctrl_info->chg_mode->ime_path1_out_group.group_en  == ENABLE) {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H, ((ctrl_info->chg_mode->ime_path1_out_group.win_num & 0xffff0000) >> 16));
		IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_V, (ctrl_info->chg_mode->ime_path1_out_group.win_num & 0x0000ffff));
		IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_H, ((ctrl_info->chg_mode->ime_path1_out_group.out_img_pos & 0xffff0000) >> 16));
		IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_V, (ctrl_info->chg_mode->ime_path1_out_group.out_img_pos & 0xffff0000));
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H, 1);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_V, 1);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_H, 0);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_V, 0);
	}

	IPL_CtrlSetInfor(id, IPLCTRL_IME_YUV_TYPE, ctrl_info->chg_mode->ime_yuv_type);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALE_RATIO_THR, ctrl_info->chg_mode->ime_scale_ratio_thr);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALER_OVER, ctrl_info->chg_mode->ime_scaler_over);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALER_UNDER, ctrl_info->chg_mode->ime_scaler_under);

	IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P1_EN, &ctrl_info->chg_mode->ime_path_1);
	IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P2_EN, &ctrl_info->chg_mode->ime_path_2);
	IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P3_EN, &ctrl_info->chg_mode->ime_path_3);
	IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ctrl_info->chg_mode->ime_path_4);

	if (ctrl_info->chg_mode->func_en & IPL_FUNC_ADAS) {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN, ENABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS, ADAS_GetEdgeMapSz());
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS, ADAS_GetFcwsHistSz());
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN, DISABLE);
	}
}

void IPL_CtrlPrvInitFlowDirect(UINT32 id, IPLCTRL_INFO *ctrl_info)
{
	UINT32 width = 0, height = 0, rhe_sub_out_size = 0;
	IPC_QINFO ipc_info = {0};
	awb_ca_info CAInfo = {0};
	AE_LAINFO LAInfo = {0};
	UINT32 ipl_ext_func = ICF_FUNC_NONE;
	UINT32 ipl_cf_mode_ext = IPL_CFEXT_NONE;
#if IPL_WDR_FUNC_SUPPORT
	SR_WDR_SUBIMG_INFO wdr_sub_info = {0};
#endif
#if IPL_SHDR_FUNC_SUPPORT
	SHDR_SUBIMG_INFO shdr_sub_info = {0};
#endif
	UINT32 sen_vts;

	DxSys_Cfg_DirectMode(TRUE);
	ipc_info = IPL_Ctrl_Query(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_CtrlGetInfor(id, IPLCTRL_PRVFLOW));
	IPL_CtrlSetInfor(id, IPLCTRL_PRVAUTO_OB_EN, DISABLE);

	//set sie signal
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_VD_INV, ctrl_info->info->sig_info.vd_inv);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_HD_INV, ctrl_info->info->sig_info.hd_inv);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_VD_PHASE, ctrl_info->info->sig_info.vd_phase);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_HD_PHASE, ctrl_info->info->sig_info.hd_phase);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_DATA_PHASE, ctrl_info->info->sig_info.data_phase);

	//SIE Input Information
	IPL_CtrlSetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO, ctrl_info->chg_mode->crop_ratio);
	IPL_CtrlSetInfor(id, IPLCTRL_FLIP_TYPE, ctrl_info->chg_mode->flip_info);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVSTPIX, IPL_UTI_CONV_SEN_STPIX(ctrl_info->info->mode->stpix));
	IPL_DzoomGetSIECropSize(id, IPL_DzoomGetIndex(id), FALSE, &width, &height);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVCROP_SIZE_H, width);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_PRVCROP_SIZE_V, height);

	//ipl ext ctrl flow mode
	ipl_cf_mode_ext |= IPL_CFEXT_NONE;
	IPL_CtrlSetInfor(id, IPLCTRL_CFMODEEXT, ipl_cf_mode_ext);

	IPL_CtrlSetInfor(id, IPLCTRL_EXT_CTRL_EN, ctrl_info->chg_mode->ext_ctrl_en);
	//ICF EXT FUNC. ON/OFF
	if (ctrl_info->chg_mode->func_en & IPL_FUNC_SHDR) {
		if (ctrl_info->info->mode->mode_type == SENSOR_MODE_STAGGER_HDR) {
			ipl_ext_func |= ICF_FUNC_SHDR;
		}
	} else if (ctrl_info->chg_mode->func_en & IPL_FUNC_WDR) {
		ipl_ext_func |= ICF_FUNC_WDR;
	}

	if (ctrl_info->chg_mode->func_en & IPL_FUNC_STITCH) {
		ipl_ext_func |= ICF_FUNC_STITCH;
	}

	if (ctrl_info->chg_mode->func_en & IPL_FUNC_DEFOG) {
		ipl_ext_func |= ICF_FUNC_DEFOG;
	}

	IPL_CtrlSetInfor(id, IPLCTRL_EXT_FUNC_EN, ipl_ext_func);

	//SIE output ch0 - raw output
    if(id == IPL_ID_1){
	    IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN, DISABLE);   //direct mode N.S. raw encode
    }else{
    	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_DISABLE_RAWENC_MANUAL) == 0) {
    		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN, DISABLE);
    	} else {
    		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN, ENABLE);
    		IPL_AlgSetUIInfo(id, IPL_SEL_RAW_BITDEPTH_PRV, SEL_RAW_BITDEPTH_12);    //raw encode always output 12 bitdepth
    	}
    }

	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_PRVBIT, IPL_AlgGetUIInfo(id, IPL_SEL_RAW_BITDEPTH_PRV));
	//IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS, IPL_UTI_RAWH_CONV2_LOFS(width, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT)));
	if (IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAWENC_EN) == ENABLE) {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS, IPL_ALIGN_ROUNDUP(IPL_UTI_RAWH_CONV2_LOFS(width, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT))*IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAWENC_BUF_RATIO) / 100, 4));
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS, IPL_UTI_RAWH_CONV2_LOFS(width, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT)));
	}

	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_EN, ENABLE);
	if ((IPL_CtrlGetInfor(id, IPLCTRL_EXT_FUNC_EN) & ICF_FUNC_SHDR)) {
		if (IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID) == id) {
			IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_BUFNUM, 0);    //Direct mode force set id_0 raw buffer number to zero
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_BUFNUM, IPL_DIRECT_SIE_PPB);	//force set direct mode SIE2 ppb to 1
			sen_vts = IPL_UTI_SEN_FPS_ADJ_VTS(ctrl_info->info->mode->frame_rate, IPL_AlgGetUIInfo(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), IPL_SEL_VIDEO_FPS), ctrl_info->info->mode->sen_vd[0]->period);
			sen_vts = IPL_CtrlCalHdrRingBuf(IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID), sen_vts);
			if (sen_vts == 0) {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_RING_BUF_V, height);
			} else {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_RING_BUF_V, sen_vts);	//get from ae
			}
		}
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_BUFNUM, 0);    //Direct mode force set raw buffer number to zero
	}
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_H, width);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_V, height);

	//SIE output ch1
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_EN, DISABLE);
	//SIE output ch1 - CA Out
	AWB_GetCAInfo(IPL_UTI_CONV2_AWB_ID(id), &CAInfo);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CA_EN, ENABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CA_WINXNUM, CAInfo.WinNumX);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CA_WINYNUM, CAInfo.WinNumY);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_BUFNUM, ipc_info.QUE_FC.nBUF_CAPPB);

	//SIE ch2 output - LA Out
	AE_GetLAInfo(IPL_UTI_CONV2_AE_ID(id), &LAInfo);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_EN, ENABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_WINXNUM, LAInfo.WinNumX);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_WINYNUM, LAInfo.WinNumY);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_BUFNUM, ipc_info.QUE_FC.nBUF_LAPPB);

	//SIE output ch3 - Y or VA Out
	if (ctrl_info->chg_mode->func_en & (IPL_FUNC_WDR | IPL_FUNC_SHDR)) {
		//Y output
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_EN, ENABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_SRC, CH3_YOUT_ACC);
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_BUFNUM, ipc_info.QUE_FC.nBUF_SIE_SUBPPB);

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_SHDR) {
#if IPL_SHDR_FUNC_SUPPORT
			shdr_sub_info = SensorHDR_GetSubImgInfo();
			if (shdr_sub_info.uiSubRatio == 1) {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINXNUM, IPL_UTI_SENCROPRATIO_ADJ_HSIZE(IPL_CtrlGetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO), IPL_UTI_CONV2_UINT32(1,1), shdr_sub_info.uiSubWidth, 1)); //maximum y output window number 128
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINYNUM, IPL_UTI_SENCROPRATIO_ADJ_VSIZE(IPL_CtrlGetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO), IPL_UTI_CONV2_UINT32(1,1), shdr_sub_info.uiSubHeight, 1)); //maximum y output window number 128
			} else {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINXNUM, shdr_sub_info.uiSubWidth); //maximum y output window number 128
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINYNUM, shdr_sub_info.uiSubHeight); //maximum y output window number 128
			}
#endif
		} else if (ctrl_info->chg_mode->func_en & IPL_FUNC_WDR) {
#if IPL_WDR_FUNC_SUPPORT
			SceneRender_WDR_GetSubImgInfo(IPL_UTI_CONV2_WDR_ID(id), &wdr_sub_info);
			if (wdr_sub_info.uiSubRatio == 1) {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINXNUM, IPL_UTI_SENCROPRATIO_ADJ_HSIZE(IPL_CtrlGetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO), IPL_UTI_CONV2_UINT32(1,1), wdr_sub_info.uiSubWidth, 1)); //maximum y output window number 128
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINYNUM, IPL_UTI_SENCROPRATIO_ADJ_VSIZE(IPL_CtrlGetInfor(id, IPLCTRL_SEN_PRV_CROP_RATIO), IPL_UTI_CONV2_UINT32(1,1), wdr_sub_info.uiSubHeight, 1)); //maximum y output window number 128
			} else {
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINXNUM, wdr_sub_info.uiSubWidth); //maximum y output window number 128
				IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_YOUT_WINYNUM, wdr_sub_info.uiSubHeight); //maximum y output window number 128
			}
#endif
		}
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_EN, DISABLE);
	}

	//set ime buffer push output type
	IPL_CtrlSetInfor(id, IPLCTRL_IME_PUSH_SORT_EN, IPL_AlgGetUIInfo(id, IPL_SEL_PUSH_OUT_TYPE));

	//HDR Sensor multi frame Setting, disable all In/Out Path except SIE
	if (IPL_CtrlGetInfor(id, IPLCTRL_MF_BASE_ID) != id) {
		//IPE ETH Out
		IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_EN, DISABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN, DISABLE);
		//IFE2 Out
		IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, DISABLE);
		//IME Out
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P1_EN, DISABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P2_EN, DISABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P3_EN, DISABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EN, DISABLE);
	} else {
		//IPL input information - RHE IN, direct mode N.S. RHE Crop
		IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_BIT, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_PRVBIT));
		IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_H, width);
		IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_V, height);
		IPL_CtrlSetInfor(id, IPLCTRL_IPL_IN_SIZE_HLOS, IPL_CtrlGetInfor(id, IPLCTRL_SIE_CH0_RAW_SIZE_HLOS));

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_DEFOG) {
#if IPL_DEFOG_FUNC_SUPPORT
			IPL_CtrlSetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN, ENABLE);
			defog_lib_get_subimg_size(id, &rhe_sub_out_size);
#endif
			IPL_CtrlSetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_SIZE, rhe_sub_out_size);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN, DISABLE);
		}

		//IPE ETH Output
		if (ctrl_info->chg_mode->func_en & IPL_FUNC_ETH) {
			IPE_EethParam eth_param = {0};
			iq_get_ipe_eth_param(&eth_param);
			//dis use both eth out and eth subspl out, 2 bit mode
			if (eth_param.EthOutSel == SEL_ETH_ORG || eth_param.EthOutSel == SEL_ETH_BOTH) {
				IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_EN, ENABLE);
			}

			if (eth_param.EthOutSel == SEL_ETH_DOWNSAMPLED || eth_param.EthOutSel == SEL_ETH_BOTH) {
				IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN, ENABLE);
			}

			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_BUF_NUM, ipc_info.QUE_FC.nBUF_IPE_ETHPPB);
			IPL_DzoomGetRaw2YUVInSize(id, IPL_DzoomGetIndex(id), &width, &height);
/*
            if (eth_param.EthOutFmt == ETH_2BITS) {
				IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_H, (width << 1) >> 3);    //2 bit eth out
			} else {
				IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_H, width);	//8 bit eth out
			}
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_HLOS, IPL_ALIGN_ROUNDUP(IPL_CtrlGetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_H), 4));
*/
            IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_H, width);
			if (eth_param.EthOutFmt == ETH_2BITS) {
                IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_HLOS, IPL_ALIGN_ROUNDUP(width>>2, 4));
			} else {
                IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_HLOS, IPL_ALIGN_ROUNDUP(width, 4));
			}

			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_SIZE_V, height);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_EN, DISABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN, DISABLE);
		}

		//IPE VA Output
		if (ctrl_info->chg_mode->func_en & IPL_FUNC_VA) {
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_VA_OUT_EN, ENABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_VA_OUT_BUF_NUM, ipc_info.QUE_FC.nBUF_IPE_VAPPB);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IPE_VA_OUT_EN, DISABLE);
		}

		//PRIMACY MASK BUF
		if (ctrl_info->chg_mode->func_en & IPL_FUNC_PRIMACY_MASK) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_EN, ENABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_H, IPL_ALIGN_ROUNDUP(width >> 3, 4));
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_V, IPL_ALIGN_ROUNDUP(height >> 3, 4));
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_EN, DISABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_H, 0);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_V, 0);
		}

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_IME_TMNR) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_EN, ENABLE);
			IPL_QUE_TMNR_BUFINFO_IN tmnr_buf_in = {0};
			IPL_STRP_INFO strp_info;
			IPL_QUE_TMNR_BUFINFO_OUT tmnr_buf_out = {0};

			tmnr_buf_in.width = width;
			tmnr_buf_in.height = height;
            IPL_GetDceStrpInfo(id, &strp_info);
			tmnr_buf_in.strp_info = &strp_info;

			if (ipc_info.QUE_FC.fp_get_tmnr_bufinfo != NULL) {
				ipc_info.QUE_FC.fp_get_tmnr_bufinfo(&tmnr_buf_in, &tmnr_buf_out);
			} else {
				DBG_ERR("null fp for get tmnr buf info\r\n");
			}
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_STA_BUF_SIZE, tmnr_buf_out.sta_bufsize);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_MOT_BUF_SIZE, tmnr_buf_out.mot_bufsize);
			if (IPL_CtrlGetInfor(id, IPLCTRL_EXT_CTRL_EN) & IPL_EXT_CTRL_TMNR_SHARE_BUF) {
				IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, 0);
			} else {
				if (width > DIR_SIE_MAX_WIDTH) {
					IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, IPL_MULTI_STRP_IME_TMNR_REF_PPB);
				} else {
					IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_REF_BUF_NUM, IPL_SINGLE_STRP_IME_TMNR_REF_PPB);
				}
			}
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_EN, DISABLE);
		}

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_MD) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EN, ENABLE);
			IPL_QUE_MD_BUFINFO_IN md_buf_in = {0};
			IPL_STRP_INFO strp_info;
			IPL_QUE_MD_BUFINFO_OUT md_buf_out = {0};

			md_buf_in.width = width;
			md_buf_in.height = height;
            IPL_GetDceStrpInfo(id, &strp_info);
			md_buf_in.strp_info = &strp_info;

			md_buf_in.md_win_manual = DISABLE;
			if (ipc_info.QUE_FC.fp_get_md_bufinfo != NULL) {
				ipc_info.QUE_FC.fp_get_md_bufinfo(&md_buf_in, &md_buf_out);
			} else {
				DBG_ERR("null fp for get md buf info\r\n");
			}
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_STA_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_MD_STAPPB);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_STA_BUF_SIZE, md_buf_out.sta_bufsize);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EVT_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_MD_EVTPPB);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EVT_BUF_SIZE, md_buf_out.evt_bufsize);
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_MD_EN, DISABLE);
		}

		if (iq_check_ife2_lca(id, FALSE) || IPL_CtrlGetInfor(id, IPLCTRL_IME_PRI_MASK_EN)) {
			width  = IPL_UTI_IMESUB_ADJ_HSIZE(IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_H), iq_get_ife2_lca_ratio(id, FALSE, TRUE), 4);
			height = IPL_UTI_IMESUB_ADJ_VSIZE(IPL_CtrlGetInfor(id, IPLCTRL_IPL_IN_SIZE_V), iq_get_ife2_lca_ratio(id, FALSE, TRUE), 4);
			IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, ENABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_NUM, ipc_info.QUE_FC.nBUF_IME_LCAPPB);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_FMT, IPL_IMG_PACK_YUV444);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_H, width);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_V, height);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_YLOS, IPL_YSIZEH_CONV2LOFS(IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_FMT), IPL_CtrlGetInfor(id, IPLCTRL_IME_SUB_OUT_BUF_SIZE_H)));
		} else {
			//IFE2 output
			IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, DISABLE);
		}

		//Jarkko tmp, not ready
		if (ctrl_info->chg_mode->ime_path1_out_group.group_en  == ENABLE) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H, ((ctrl_info->chg_mode->ime_path1_out_group.win_num & 0xffff0000) >> 16));
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_V, (ctrl_info->chg_mode->ime_path1_out_group.win_num & 0x0000ffff));
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_H, ((ctrl_info->chg_mode->ime_path1_out_group.out_img_pos & 0xffff0000) >> 16));
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_V, (ctrl_info->chg_mode->ime_path1_out_group.out_img_pos & 0xffff0000));
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H, 1);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_V, 1);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_H, 0);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_V, 0);
		}

		IPL_CtrlSetInfor(id, IPLCTRL_IME_YUV_TYPE, ctrl_info->chg_mode->ime_yuv_type);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALE_RATIO_THR, ctrl_info->chg_mode->ime_scale_ratio_thr);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALER_OVER, ctrl_info->chg_mode->ime_scaler_over);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALER_UNDER, ctrl_info->chg_mode->ime_scaler_under);

		IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P1_EN, &ctrl_info->chg_mode->ime_path_1);
		IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P2_EN, &ctrl_info->chg_mode->ime_path_2);
		IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P3_EN, &ctrl_info->chg_mode->ime_path_3);
		IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ctrl_info->chg_mode->ime_path_4);

		if (ctrl_info->chg_mode->func_en & IPL_FUNC_ADAS) {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN, ENABLE);
			IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS, ADAS_GetEdgeMapSz());
			IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS, ADAS_GetFcwsHistSz());
		} else {
			IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN, DISABLE);
		}

	}
}

void IPL_CtrlPrvInitFlowVirtual(UINT32 id, IPLCTRL_INFO *ctrl_info)
{
	UINT32 ipl_cf_mode_ext = IPL_CFEXT_NONE;

	//ipl ext ctrl flow mode
	ipl_cf_mode_ext |= IPL_CFEXT_VIRTUAL;
	IPL_CtrlSetInfor(id, IPLCTRL_CFMODEEXT, ipl_cf_mode_ext);

	DxSys_Cfg_DirectMode(FALSE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH0_RAW_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH1_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CA_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_LA_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_SIE_CH3_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_EXT_FUNC_EN, ICF_FUNC_NONE);

	///IFE2 LCA Disable
	IPL_CtrlSetInfor(id, IPLCTRL_IFE2_LCA_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_RHE_DEFOG_SUB_OUT_EN, DISABLE);

	//IPE ETH Output
	IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_OUT_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_IPE_ETH_SUBSPL_OUT_EN, DISABLE);

	IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_EN, DISABLE);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_H, 0);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_PRI_MASK_V, 0);

	IPL_CtrlSetInfor(id, IPLCTRL_IME_TMNR_EN, DISABLE);

	IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_H, 1);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_TOTAL_NUM_V, 1);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_H, 0);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_OUT_GROUP_POS_V, 0);

	IPL_CtrlSetInfor(id, IPLCTRL_IME_YUV_TYPE, ctrl_info->chg_mode->ime_yuv_type);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALE_RATIO_THR, ctrl_info->chg_mode->ime_scale_ratio_thr);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALER_OVER, ctrl_info->chg_mode->ime_scaler_over);
	IPL_CtrlSetInfor(id, IPLCTRL_IME_SCALER_UNDER, ctrl_info->chg_mode->ime_scaler_under);

	IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P1_EN, &ctrl_info->chg_mode->ime_path_1);
	IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P2_EN, &ctrl_info->chg_mode->ime_path_2);
	IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P3_EN, &ctrl_info->chg_mode->ime_path_3);
	IPL_CtrlPrvInitFlow_IMEPxOutInfo(id, IPLCTRL_IME_P4_EN, &ctrl_info->chg_mode->ime_path_4);

	if (ctrl_info->chg_mode->func_en & IPL_FUNC_ADAS) {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN, ENABLE);
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EDGEMAP_BUFOFS, ADAS_GetEdgeMapSz());
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_HISTO_BUFOFS, ADAS_GetFcwsHistSz());
	} else {
		IPL_CtrlSetInfor(id, IPLCTRL_IME_P4_EXTOUT_EN, DISABLE);
	}
}
