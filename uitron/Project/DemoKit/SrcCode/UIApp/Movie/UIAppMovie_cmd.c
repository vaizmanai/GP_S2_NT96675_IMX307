//global debug level: PRJ_DBG_LVL
#include "PrjCfg.h"

#include "SysCommon.h"
#include "SysCfg.h"
#include "AppLib.h"
#include "UIAppCommon.h"
#include "UIModeMovie.h"
#include "UIAppMovie.h"  // Isiah, implement YUV merge mode of recording func.
#include "UIAppMovie_Param.h"
#include "UIMovieMapping.h"

#include "UIModePhoto.h"
#include "UIAppPhoto.h"
#include "UIPhotoMapping.h"
#include "ImageApp_MovieMulti.h"
#if (USE_FILEDB==ENABLE)
#include "FileDB.h"
#endif
#include "AppDisp_PipView.h"

//local debug level: THIS_DBGLVL
#define THIS_DBGLVL         2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          UiAppMovieCmd
#define __DBGLVL__          ((THIS_DBGLVL>=PRJ_DBG_LVL)?THIS_DBGLVL:PRJ_DBG_LVL)
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include "DebugModule.h"
///////////////////////////////////////////////////////////////////////////////

static BOOL Cmd_movie(CHAR *strCmd)
{
	UINT32 menuIdx, value;

	sscanf_s(strCmd, "%d %d", &menuIdx, &value);

	if (menuIdx == 0) {
#if (MOVIE_REC_YUVMERGE == ENABLE)
		BOOL bEnable;
		UINT32 uiInterval;
		DBG_DUMP("Test merge record\r\n");
		sscanf_s(strCmd, "%d %d %d", &menuIdx, &bEnable, &uiInterval);
		FlowMovie_RecSetYUVMergeRecInterval(uiInterval);
		FlowMovie_RecSetYUVMergeRecCounter(0);
		FlowMovie_RecSetYUVMergeMode(bEnable);
		if (bEnable) {
			debug_msg("Enable YUV merge record mode, interval=%d\r\n", uiInterval);
		} else {
			debug_msg("Disable YUV merge record mode\r\n");
		}
#endif
	} else if (menuIdx == 1) {
#if(MOVIE_MODE==ENABLE)
		DBG_DUMP("ADAS(LDWS+FCW) %d\r\n", value);
		Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_LDWS,          1,  value);
		Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_FCW,           1,  value);
#endif
	} else if (menuIdx == 2) {
#if(MOVIE_MODE==ENABLE)
		DBG_DUMP("Urgent Protect Manual %d\r\n", value);
		Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_PROTECT_MANUAL, 1,  value);
#endif
	} else if (menuIdx == 3) {
#if(MOVIE_MODE==ENABLE)
		DBG_DUMP("Image Rotation %d\r\n", value);
		Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_SENSOR_ROTATE, 1,  value);
#endif
	} else if (menuIdx == 5) {
#if(MOVIE_MODE==ENABLE)
		DBG_DUMP("Movie RSC %d\r\n", value);
		Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_MOVIE_RSC,          1,  value);
#endif
	} else if (menuIdx == 7) {
#if(PHOTO_MODE==ENABLE)
		UI_SetData(FL_DUAL_CAM, value);
		DBG_DUMP("Sensor index %d\r\n", value);
		Ux_SendEvent(&CustomMovieObjCtrl,   NVTEVT_EXE_DUALCAM,      1, SysGetFlag(FL_DUAL_CAM));
#endif
	} else if (menuIdx == 11) {
#if(MOVIE_MODE==ENABLE)
		DBG_DUMP("Movie WDR index %d\r\n", value);
		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_MOVIE_WDR, 1, value);
#endif
	} else if (menuIdx == 13) {
#if 1//(PIP_VIEW_LR == ENABLE)
		DBG_DUMP("enter value=%d\r\n", value);
		if(value>=DUALCAM_FRONT && value<=DUALCAM_BOTH2 )
		{
		}
		else
		{
		    value=DUALCAM_FRONT;
		}
#if(MOVIE_MODE==ENABLE)
		DBG_DUMP("out value=%d\r\n", value);
		UI_SetData(FL_DUAL_CAM, value);

		Ux_SendEvent(&CustomMovieObjCtrl, NVTEVT_EXE_IMAGE_RATIO, 1, GetMovieSizeRatio(UI_GetData(FL_MOVIE_SIZE)));
		PipView_SetStyle(UI_GetData(FL_DUAL_CAM));
#endif
#endif
	}

	return TRUE;
}
static BOOL Cmd_movie_SetFmtFree(CHAR *strCmd)
{
	CHAR drive = 'A';
	UINT32 is_format_free;

	sscanf_s(strCmd, "%d", &is_format_free);

	ImageApp_MovieMulti_SetFormatFree(drive, is_format_free);

	return TRUE;
}

static BOOL Cmd_movie_SetFldInfo(CHAR *strCmd)
{
	CHAR   fld_full_path[128] = {0};
	UINT32 fld_ratio = 0;
	UINT64 fixed_size = 0;
	UINT32 is_set;

	sscanf_s(strCmd, "%d", &is_set);

	if (is_set) {

	//Set "Infinite"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Infinite\\");
	fld_ratio = 50;
	fixed_size = 190 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	//Set "Event"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Event\\");
	fld_ratio = 10;
	fixed_size = 30 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	//Set "Parking"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Parking\\");
	fld_ratio = 10;
	fixed_size = 30 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	//Set "Manual"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Manual\\");
	fld_ratio = 10;
	fixed_size = 30 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	//Set "Timelapse"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Timelapse\\");
	fld_ratio = 10;
	fixed_size = 30 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	//Set "Image"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Image\\");
	fld_ratio = 10;
	fixed_size = 30 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	} else {

	//Set "Movie"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Novatek\\Movie\\");
	fld_ratio = 10;//70;
	fixed_size = 190 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	//Set "EMR"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Novatek\\EMR\\");
	fld_ratio = 80;//20;
	fixed_size = 30 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	//Set "Photo"
	snprintf(fld_full_path, sizeof(fld_full_path), "A:\\Novatek\\Photo\\");
	fld_ratio = 10;
	fixed_size = 30 * 1024 * 1024ULL;
	ImageApp_MovieMulti_SetFolderInfo(fld_full_path, fld_ratio, fixed_size);

	}
	return TRUE;
}

static BOOL Cmd_movie_FMAllocate(CHAR *strCmd)
{
	CHAR drive = 'A';
	UINT32 is_set;

	sscanf_s(strCmd, "%d", &is_set);

	if (!is_set) {
		return TRUE;
	}

	ImageApp_MovieMulti_FMAllocate(drive);

	return TRUE;
}
static BOOL Cmd_movie_SetCyclicRec(CHAR *strCmd)
{
	CHAR dir_path[32]="A:\\Novatek\\Movie\\";
	UINT32 is_on;

	sscanf_s(strCmd, "%d", &is_on);

	DBG_DUMP("is_set=%d\r\n", is_on);

	ImageApp_MovieMulti_SetCyclicRec(dir_path, is_on);

	return TRUE;
}

static BOOL Cmd_movie_format_free_testflow(CHAR *strCmd)
{
	SxCmd_DoCommand("uimovie setfmtfree 1");
	SxCmd_DoCommand("uimovie setfldinfo 0");
	SxCmd_DoCommand("filesys format");
	SxCmd_DoCommand("uimovie fmallocate 1");
	SxCmd_DoCommand("uimovie cyclicrec 0");

	return TRUE;
}
BOOL Cmd_movie_dumpfdb(CHAR *strCmd)
{
#if (USE_FILEDB==ENABLE)
	FileDB_DumpInfo(0);
#if defined(_EMBMEM_EMMC_) && (FS_MULTI_STRG_FUNC==ENABLE)
	FileDB_DumpInfo(1);
#endif
#endif
	return TRUE;
}

SXCMD_BEGIN(uimovie, "uimovie command")
SXCMD_ITEM("movie %", Cmd_movie, "movie mode test")
SXCMD_ITEM("dumpfdb",   Cmd_movie_dumpfdb,   "dump filedb 0")
SXCMD_ITEM("setfmtfree %", Cmd_movie_SetFmtFree, "Set Format Free")
SXCMD_ITEM("setfldinfo %", Cmd_movie_SetFldInfo, "Set Folder Info")
SXCMD_ITEM("fmallocate ", Cmd_movie_FMAllocate, "FM Allocate")
SXCMD_ITEM("cyclicrec %d", Cmd_movie_SetCyclicRec, "Set Cyclic Rec")
SXCMD_ITEM("fmtest", Cmd_movie_format_free_testflow, "FM test flow")
SXCMD_END()
