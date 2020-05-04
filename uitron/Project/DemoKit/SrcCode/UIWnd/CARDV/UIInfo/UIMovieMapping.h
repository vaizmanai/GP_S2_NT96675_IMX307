#ifndef MOVIE_MAPPING_H
#define MOVIE_MAPPING_H

#include "SysSensor.h"
/*#include "UIAppMoviePlay.h"
#include "UIMovieInfo.h"
#include "UIPhotoInfo.h" //for IMAGERATIO_XXX
#include "Audio.h"
#include "SysMain.h"
#include "UIMovieMapping.h"
#include "UIFlow.h"
#include "media_def.h"
#include "ImageApp_MovieCommon.h"*/

typedef enum _MOVIE_REC_TYPE{
    MOVIE_REC_TYPE_UNKNOWN,
    MOVIE_REC_TYPE_FRONT,
    MOVIE_REC_TYPE_BEHIND,
    MOVIE_REC_TYPE_DUAL,
    MOVIE_REC_TYPE_CLONE,
}MOVIE_REC_TYPE;



typedef struct {
	UINT32  uiWidth;
	UINT32  uiHeight;
	UINT32  uiVidFrameRate;
	UINT32  uiTargetBitrate;
	UINT32  uiDispAspectRatio;
	UINT32  uiImageRatio;
} MOVIE_SIZE_PARAM;

typedef struct {
	INT32  aq_enable;
	UINT32 aq_str;
	INT32  sraq_init_aslog2;
	INT32  max_sraq;
	INT32  min_sraq;
	INT32  sraq_const_aslog2;
} MOVIE_AQ_PARAM;

typedef struct {
	UINT32 uiEnable;
	UINT32 uiStaticTime;
	UINT32 uiFrameRate;
	UINT32 uiByteRate;
	UINT32 uiGOP;
	UINT32 uiInitIQp;
	UINT32 uiMinIQp;
	UINT32 uiMaxIQp;
	UINT32 uiInitPQp;
	UINT32 uiMinPQp;
	UINT32 uiMaxPQp;
	INT32  iIPWeight;
	UINT32 uiRowRcEnalbe;
	UINT32 uiRowRcQpRange;
	UINT32 uiRowRcQpStep;
} MOVIE_CBR_PARAM;

typedef struct {
	MOVIE_REC_TYPE Type;
	MOVIE_SIZE_PARAM Front;
	MOVIE_SIZE_PARAM Behind;
	MOVIE_AQ_PARAM AqFrontInfo;
	MOVIE_AQ_PARAM AqBehindInfo;
	MOVIE_CBR_PARAM CbrFrontInfo;
	MOVIE_CBR_PARAM CbrBehindInfo;
} MOVIE_REC_ITEM;

//-------------------------------------------------------------------------------------------------
#define MOVIE_SIZE_WIFI_STREAMING	MOVIE_SIZE_848x480P30	// always use 848x480 for WiFi streaming temporarily

typedef struct {
	MOVIE_SIZE_PARAM SizeInfo;
	MOVIE_AQ_PARAM AqInfo;
	MOVIE_CBR_PARAM CbrInfo;
} MOVIE_SIZE_ITEM;

typedef struct {
	MOVIE_REC_TYPE Type;
	UINT32 SizeIdx[SENSOR_MAX_NUM];			// movie size index for main movie, max 4 sensors
	UINT32 SizeIdxClone[SENSOR_MAX_NUM];	// movie size index for clone movie, max 4 sensors
} MOVIE_SIZE_MAPPING;



extern UINT32   GetMovieSizeWidth(UINT32 uiIndex);
extern UINT32   GetMovieSizeHeight(UINT32 uiIndex);
extern UINT32   GetMovieFrameRate(UINT32 uiIndex);
extern UINT32   GetMovieTargetBitrate(UINT32 uiSize, UINT32 uiQuality);
extern void     SetMovieTargetBitrate(UINT32 uiType, UINT32 uiSize, UINT32 uiBitRate);
extern UINT32   GetMovieDispAspectRatio(UINT32 uiIndex);
extern UINT32   GetMovieSizeRatio(UINT32 ubIndex);
extern UINT32   GetMovieAudioVolumeValue(UINT32 uiIndex);
extern UINT32   Get_MovieTimeLapseValue(UINT32 uhIndex);
//#NT#2015/03/18#Lily Kao -begin
//#NT#Add for UVAC to set parameters for MFK
extern UINT32   GetMovieTBRAspRatio(UINT32 width, UINT32 height, UINT32 fps, UINT32 *pTBR, UINT32 *pAspRatio);
//#NT#2015/03/18#Lily Kao -end

extern UINT32   GetMovieSizeWidth_2p(UINT32 uiPath, UINT32 uiIndex);
extern UINT32   GetMovieSizeHeight_2p(UINT32 uiPath, UINT32 uiIndex);
extern UINT32   GetMovieFrameRate_2p(UINT32 uiPath, UINT32 uiIndex);
extern UINT32   GetMovieTargetBitrate_2p(UINT32 uiPath, UINT32 uiIndex);
extern UINT32   GetMovieDispAspectRatio_2p(UINT32 uiPath, UINT32 uiIndex);
extern MOVIE_REC_TYPE GetMovieRecType_2p(UINT32 uiIndex);
extern UINT32   GetMovieVidEncFmt_2p(UINT32 uiPath);
extern UINT32   CheckWiFiMapTbl(void);
extern void GetMovieAqInfo(UINT32 uiIndex, UINT32 Value);
extern void GetMovieCbrInfo(UINT32 uiIndex, UINT32 Value);
extern void GetMovieAqInfo_2p(UINT32 uiIndex, UINT32 Value);
extern void GetMovieCbrInfo_2p(UINT32 uiIndex, UINT32 Value);
// main movie
extern UINT32 MovieMapping_GetRecType(UINT32 uiSizeIdx);
extern UINT32 MovieMapping_GetWidth(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetHeight(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetFrameRate(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetTargetBitrate(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetDispAspectRatio(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetImageRatio(UINT32 uiSizeIdx, UINT32 uiIplId);
extern void MovieMapping_GetAqInfo(UINT32 uiSizeIdx, UINT32 uiIplId, UINT32 Value);
extern void MovieMapping_GetCbrInfo(UINT32 uiSizeIdx, UINT32 uiIplId, UINT32 Value);
// clone movie
extern UINT32 MovieMapping_GetCloneWidth(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetCloneHeight(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetCloneFrameRate(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetCloneTargetBitrate(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetCloneDispAspectRatio(UINT32 uiSizeIdx, UINT32 uiIplId);
extern UINT32 MovieMapping_GetCloneImageRatio(UINT32 uiSizeIdx, UINT32 uiIplId);
extern void MovieMapping_GetCloneAqInfo(UINT32 uiSizeIdx, UINT32 uiIplId, UINT32 Value);
extern void MovieMapping_GetCloneCbrInfo(UINT32 uiSizeIdx, UINT32 uiIplId, UINT32 Value);
// WiFi/UVC streaming
extern void MovieMapping_GetStreamInfo(UINT32 uiSizeIdx, UINT32 Value);
#endif
