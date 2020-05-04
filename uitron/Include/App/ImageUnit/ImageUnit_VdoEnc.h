/*
    Copyright   Novatek Microelectronics Corp. 2005~2014.  All rights reserved.

    @file       ImageUnit_VdoIn.h
    @ingroup    mVdoIn

    @note       Nothing.

    @date       2017/10/01
*/

#ifndef IMAGEUNIT_VDOENC_H
#define IMAGEUNIT_VDOENC_H

typedef struct {
	UINT32 SrcOutYAddr;     ///< Src Out Y Addr
	UINT32 SrcOutUVAddr;	///< Src Out UV Addr
	UINT32 SrcOutWidth;     ///< Src Out Width
	UINT32 SrcOutHeight;    ///< Src Out Height
	UINT32 SrcOutYLoft;     ///< Src Out Y Line Offset
	UINT32 SrcOutUVLoft;    ///< Src Out UV Line Offset
} VDOENC_SOURCBS_INFO, *PVDOENC_SOURCBS_INFO;

enum {
	VDOENC_PARAM_START = 0x0000F000,
	VDOENC_PARAM_CODEC = VDOENC_PARAM_START,
	VDOENC_PARAM_PROFILE,
	VDOENC_PARAM_LEVEL_IDC,
	VDOENC_PARAM_TARGETRATE,
	VDOENC_PARAM_ENCODER_OBJ,
	VDOENC_PARAM_MAX_MEM_INFO,
	VDOENC_PARAM_ENCBUF_MS,							//unit: ms
	VDOENC_PARAM_ENCBUF_RESERVED_MS,				//unit: ms
	VDOENC_PARAM_FRAMERATE,
	VDOENC_PARAM_GOPTYPE,
	VDOENC_PARAM_GOPNUM,
	VDOENC_PARAM_RECFORMAT,
	VDOENC_PARAM_FILETYPE,
	VDOENC_PARAM_INITQP,
	VDOENC_PARAM_MINQP,
	VDOENC_PARAM_MAXQP,
    VDOENC_PARAM_MIN_I_RATIO,
    VDOENC_PARAM_MIN_P_RATIO,
    VDOENC_PARAM_MAX_FRAME_QUEUE,
	VDOENC_PARAM_DAR,
	VDOENC_PARAM_SKIP_FRAME,
	VDOENC_PARAM_SVC,
	VDOENC_PARAM_LTR,
	VDOENC_PARAM_SEI,
	VDOENC_PARAM_MULTI_TEMPORARY_LAYER,
	VDOENC_PARAM_USRQP,
	VDOENC_PARAM_CBRINFO,
	VDOENC_PARAM_EVBRINFO,
	VDOENC_PARAM_VBRINFO,
	VDOENC_PARAM_FIXQPINFO,
	VDOENC_PARAM_AQINFO,
	VDOENC_PARAM_3DNR_CB,
	VDOENC_PARAM_IMM_CB,
	VDOENC_PARAM_FRAME_INTERVAL,
	VDOENC_PARAM_EVENT_CB,
	VDOENC_PARAM_ENCBUF_ADDR,
	VDOENC_PARAM_ENCBUF_SIZE,
	VDOENC_PARAM_ROI,
    VDOENC_PARAM_DIS,
	VDOENC_PARAM_TV_RANGE,
	VDOENC_PARAM_START_TIMER_BY_MANUAL,
	VDOENC_PARAM_START_TIMER,
	VDOENC_PARAM_STOP_TIMER,
	VDOENC_PARAM_START_SMART_ROI,
	VDOENC_PARAM_WAIT_SMART_ROI,
	VDOENC_PARAM_RESET_IFRAME,
	VDOENC_PARAM_RESET_SEC,
	VDOENC_PARAM_RAW_DATA_CB,
	VDOENC_PARAM_SRC_OUT_CB,
	VDOENC_PARAM_TIMELAPSE_TIME,
    VDOENC_PARAM_ALLOC_SNAPSHOT_BUF,
    VDOENC_PARAM_SNAPSHOT,
    VDOENC_PARAM_SYNCSRC,
    VDOENC_PARAM_FPS_IMM,
    VDOENC_PARAM_FUNC,
	VDOENC_PARAM_PROC_CB,
	VDOENC_PARAM_REC_COMPRESS_ENABLE,
	// ImgCap
	VDOENC_PARAM_IMGCAP_THUMB,
	VDOENC_PARAM_IMGCAP_ACTION,
	VDOENC_PARAM_IMGCAP_W,
	VDOENC_PARAM_IMGCAP_H,
	VDOENC_PARAM_IMGCAP_JPG_BUFNUM,     // set jpg buffer number
	VDOENC_PARAM_IMGCAP_GET_JPG_ADDR,   // get jpg encoded addr
	VDOENC_PARAM_IMGCAP_GET_JPG_SIZE,   // get jpg encoded size
	VDOENC_PARAM_IMGCAP_MAX_MEM_INFO,
	VDOENC_PARAM_IMGCAP_FUNC_DISABLE,   // ImgCap Function Disable, 0: func enable (default) / 1: func disable
	VDOENC_PARAM_IMGCAP_EXIF_FUNC,      // EXIF function (1: on, 0: off)
};

typedef void (IsfVdoEncEventCb)(CHAR *Name, UINT32 event_id, UINT32 value);
typedef UINT32 (*VDOENC_PROC_CB)(UINT32 id, UINT32 state);

extern ISF_UNIT ISF_VdoEnc;

#define VDOENC_FUNC_NOWAIT			0x00000001 //do not wait for encode finish

extern void ISF_VdoEnc_InstallID(void) _SECTION(".kercfg_text");
extern UINT32 _SECTION(".kercfg_data") ISF_VDOENC_SEM_ID[];
extern UINT32 _SECTION(".kercfg_data") ISF_VDOENC_COMMON_SEM_ID;

#endif //IMAGEUNIT_VDOENC_680_H
