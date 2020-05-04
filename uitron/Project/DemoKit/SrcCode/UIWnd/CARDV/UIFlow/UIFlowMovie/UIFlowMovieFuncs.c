#include "Type.h"
//#include "ImageApp_Movie.h"
#include "UIFramework.h"
#include "UIFrameworkExt.h"
#include "UIFlow.h"
#include "FileDB.h"
#include "Perf.h"
#define MOVIE_REC_TIME_MIN  1 // 1 sec

#define MOVIE_REC_MIN_CLUSTER_SIZE      (0x8000)    //32KB
#define MOVIE_REC_SD_CLASS              (4)         // class 4

MOV_TASK_DATA   gMovData = { 0 };

static UINT32  g_MovRecMaxTime = 0;
static UINT32  g_MovRecCurrTime = 0;
static UINT32  g_MovRecSelfTimerSec = 0;
#if _ADAS_FUNC_
static ADAS_OSD_COORDINATE g_AdasOsdCoord = {0};
#endif
static UINT32  g_MovRecSelfTimerID = NULL_TIMER;
UINT8 FlowMovie_GetMovDataState(void)
{
    return gMovData.State;
}

void FlowMovie_StartRec(void)
{
    if (g_MovRecSelfTimerSec == 0)
    {
        g_MovRecCurrTime = 0;
#if (USE_FILEDB == DISABLE)
        // update DCF Folder/File name
        FlowDCF_UpdateName();
#endif
        if(System_GetState(SYS_STATE_POWERON) == SYSTEM_POWERON_SAFE)
        {
        // wait playing sound stop
        GxSound_WaitStop();
        }
        Ux_SendEvent(&CustomMovieObjCtrl,NVTEVT_EXE_MOVIE_REC_START,NULL);

        //#NT#2012/10/23#Philex Lin - begin
        // disable auto power off/USB detect timer
        KeyScan_EnableMisc(FALSE);
        //#NT#2012/10/23#Philex Lin - end
    }
    else
    {
        debug_err(("FlowMovie_StartRec: Not yet,g_MovSelfTimerSec=%d\r\n", g_MovRecSelfTimerSec));
    }
}

void FlowMovie_StopRec(void)
{
    UxCtrl_SetShow(&UIFlowWndMovie_PanelCtrl,FALSE);
    Ux_SendEvent(&CustomMovieObjCtrl,NVTEVT_EXE_MOVIE_REC_STOP,NULL);
    UxCtrl_SetShow(&UIFlowWndMovie_StaticICN_ProtectCtrl, FALSE);
    //#NT#2012/10/23#Philex Lin - begin
    // enable auto power off/USB detect timer
    KeyScan_EnableMisc(TRUE);
    //#NT#2016/06/21#Niven Cho -begin
    //#NT#Remove danger code
    //#NT#2016/06/21#Niven Cho -end

    gMovData.State= MOV_ST_VIEW;
    //#NT#2012/10/23#Philex Lin - end

}

void FlowMovie_StopRecSelfTimer(void)
{
    if (g_MovRecSelfTimerID != NULL_TIMER)
    {
        GxTimer_StopTimer(&g_MovRecSelfTimerID);
        g_MovRecSelfTimerID = NULL_TIMER;
    }
    g_MovRecSelfTimerSec = 0;
}

UINT8 FlowMovie_GetDataState(void)
{
    return gMovData.State;
}

void FlowMovie_SetRecMaxTime(UINT32 RecMaxTime)
{
    g_MovRecMaxTime = RecMaxTime;
}

UINT32 FlowMovie_GetRecMaxTime(void)
{
    return g_MovRecMaxTime;
}

void FlowMovie_SetRecCurrTime(UINT32 RecCurrTime)
{
    g_MovRecCurrTime = RecCurrTime;
}

UINT32 FlowMovie_GetRecCurrTime(void)
{
    return g_MovRecCurrTime;
}

BOOL FlowMovie_IsStorageErr(BOOL IsCheckFull)
{
#if (MOVIE_ENSURE_SD_32KCLUSTER == ENABLE)
    UINT32  uiClusterSize;
#endif
#if (MOVIE_ENSURE_SD_CLASS4 == ENABLE)
    PSDIO_MISC_INFORMATION pMiscInfo;
#endif
    UINT32 MaxTime,ret,Cnt = 0;
    // check card inserted
    
    if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED)
    {CHKPNT;
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_PLEASE_INSERT_SD,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }

	if(FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE) == 0x0000)
	{
		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,FLOWWRNMSG_ISSUE_NO_FAT32,FLOWWRNMSG_TIMER_KEEP);
             return TRUE;
	}
    // check storage error

    if(UIStorageCheck(STORAGE_CHECK_ERROR, NULL) == TRUE)
    {CHKPNT;
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,FLOWWRNMSG_ISSUE_MEM_ERR,FLOWWRNMSG_TIMER_KEEP);
        return TRUE;
    }


    // check storage lock or directory read only
    if (UIStorageCheck(STORAGE_CHECK_LOCKED, NULL) == TRUE ||
        UIStorageCheck(STORAGE_CHECK_DCIM_READONLY, NULL) == TRUE)
    {CHKPNT;
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_LOCKED,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }

    // check storage full
    if (TRUE == IsCheckFull)
    {
    CHKPNT;
        g_MovRecMaxTime = MovieExe_GetMaxRecSec();
	 debug_msg("g_MovRecMaxTime =%d	\r\n",g_MovRecMaxTime);	
	 if(UI_GetData(FL_MOVIE_CYCLIC_REC) != MOVIE_CYCLICREC_OFF)
	 {
	 	if(g_MovRecMaxTime <60*3)
	 	{
	 		for (Cnt = 0; Cnt < 5; Cnt++)
			{
				ret =Force_FDB_DelOldFile(3);	
				MaxTime = MovieExe_GetMaxRecSec();
				debug_msg("MaxTime =%d  \r\n",MaxTime);
				if(MaxTime >60*3)
					break;
			}
	 	}
	 }
	 else
	 {
	       if (g_MovRecMaxTime <= MOVIE_REC_TIME_MIN)
     	       {CHKPNT;
          		  g_MovRecMaxTime = 0;
            		Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_FULL,FLOWWRNMSG_TIMER_2SEC);
            		return TRUE;
       	 }
	 }
    }

    // check folder full
    if (UIStorageCheck(STORAGE_CHECK_FOLDER_FULL, NULL) == TRUE)
    {CHKPNT;
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CARD_FULL,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }


#if (MOVIE_ENSURE_SD_CLASS4 == ENABLE)
    // check sd card whether faster than class 4
    pMiscInfo = sdio_getMiscInfo();
    if (pMiscInfo->uiWriteRate < MOVIE_REC_SD_CLASS)
    {CHKPNT;
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_SD_CLASS4,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }
#endif

#if (MOVIE_ENSURE_SD_32KCLUSTER == ENABLE)
    // Check cluster size, need to be larger than 32KB

	debug_msg("***********------ Check cluster size  ************\r\n");
    uiClusterSize = FileSys_GetDiskInfo(FST_INFO_CLUSTER_SIZE);
    if (uiClusterSize < MOVIE_REC_MIN_CLUSTER_SIZE)
    {CHKPNT;
        Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,UIFlowWndWrnMsg_StatusTXT_Msg_STRID_CLUSTER_WRONG,FLOWWRNMSG_TIMER_2SEC);
        return TRUE;
    }
#endif

    return FALSE;
}

UINT32 FlowMovie_GetSelfTimerID(void)
{
    return g_MovRecSelfTimerID;
}

#if 0
BOOL FlowMovie_ChkDrawStoreFullFolderFull(void)
{

    if(UIStorageCheck(STORAGE_CHECK_FULL, &(g_MovRecMaxTime)) == TRUE)
    {
        g_MovRecMaxTime = UIMovRecObj_GetData(RECMOVIE_MAXSECOND);
		if (System_GetState(SYS_STATE_CARD) == CARD_REMOVED)
        {
            Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,FLOWWRNMSG_ISSUE_MEM_FULL,FLOWWRNMSG_TIMER_2SEC);
            return TRUE;
        }
        else
        {
            Ux_OpenWindow(&UIFlowWndWrnMsgCtrl,2,FLOWWRNMSG_ISSUE_CARD_FULL,FLOWWRNMSG_TIMER_2SEC);
            return TRUE;
        }
    }

    return FALSE;
}
#endif

void FlowMovie_GetPictureInMovie(void)
{
#if (0)//(_MOVIE_PIM_MODE_ == ENABLE)
    UINT32  sec, unsafe;

    switch (gMovData.State)
    {
    case MOV_ST_REC:
        sec = MovRec_Disk2Second();
        unsafe = MovRec_CheckUnsavedFileBlocks();

        if ((sec > 3)&&(unsafe == 0))
        {
            RawEnc_SetCaptureOne();
            //UxCtrl_SetShow(&UIFlowWndMovie_Static_pimCtrl, TRUE);
        }
        else
        {
            if (unsafe)
            {
                debug_err(("unsafe to take picture !\r\n"));
            }
            else
            {
                debug_err(("no space to encode RAW !\r\n"));
            }
        }
        break;
    }
#endif
}

void FlowMovie_OnTimer1SecIndex(void)
{

    switch (gMovData.State)
    {
    case MOV_ST_VIEW:
    case MOV_ST_VIEW | MOV_ST_ZOOM:
    case MOV_ST_REC:
    case MOV_ST_REC | MOV_ST_ZOOM:
        gMovData.SysTimeCount++;
        if (UxCtrl_IsShow(&UIFlowWndMovie_YMD_StaticCtrl))
        {
            FlowMovie_IconDrawDateTime();
        }
        break;

    }
}



INT32 Force_FDB_DelOldFile(UINT32  FileCount)
{
	FILEDB_HANDLE		FileDBHdl = 0;
	PFILEDB_FILE_ATTR  	FileAttr = NULL;
	INT32			   	ret;
	INT32			   	FileNum,i,FileC,ROfileNum = 0;
	UINT32  			DeleFileNUM =0;
	//CHAR 				CurFileFullPath[60] = {0};

/*
主动删除旧文件 ---DCH
*/
	FileSys_WaitFinish();
	FileDB_Refresh(FileDBHdl);
	Perf_Mark();
	FileNum = FileDB_GetTotalFileNum(FileDBHdl);
	debug_msg("TotalFileNum:%d \r\n",FileNum);
	debug_msg("^Y Force_FDB_DelOldFile FileCount =%d\r\n",FileCount);

	if(!FileNum)
		return FALSE;
	i =0; 
	for(FileC=0; FileC<FileNum; FileC++)
	{
		FileAttr = FileDB_SearhFile(FileDBHdl, i);
		if(FileAttr->attrib ==33)
		{
			i++; //  跳过只读文件
			ROfileNum++;
			continue;
 		}

		if (FileAttr)
		{
			ret = FileSys_DeleteFile(FileAttr->filePath);
			if (ret == FST_STA_OK)
			{
				FileDB_DeleteFile(FileDBHdl,i);
				debug_msg("------------FDB_Delete_ ok!---------------\r\n");
				DeleFileNUM ++;
			}
			else
			{
				debug_msg("FDB_Delete_Err!! \r\n");
				i++; //  跳过错误文件
				debug_msg("FileIndex i=%d  \r\n",i);
				continue;
			}
		}
		else
		{
			debug_msg("FileAttr  Err!! \r\n");
			 goto FDB_DelOldFile_Err;
		}

		if(DeleFileNUM >=FileCount)
		{
			debug_msg("Succeed DeleFileNUM =%d  \r\n",DeleFileNUM);
			break;
		}

		if(i >=FileNum)
		{
			debug_msg("FileIndex i =%d  out of range  TotalFileNum !!\r\n",i);
			break;
		}
		
	}
	
	//如果全部是只读,就删除最早的---DCH

	debug_msg("\r\n FileIndex i=%d  FileNum =%d  \r\n",i,FileNum);
	if(ROfileNum == FileNum) 
	{
		debug_msg(" All is readonly ,delete first file ! \r\n"); 
		i =0;
		FileAttr = FileDB_SearhFile(FileDBHdl, i);
		if(FileAttr->attrib ==33)
		{
			debug_msg("FileIndex i=%d  is readonly \r\n",i);
			ret = FileSys_SetAttrib(FileAttr->filePath,FST_ATTRIB_READONLY,FALSE);
			if (ret == FST_STA_OK)
			{
				debug_msg(" FileIndex =%d  FileSys_SetAttrib OK!\r\n",i);
			}
			else
			{
	
				debug_msg(" FileIndex =%d  FileSys_SetAttrib false !\r\n",i);
			}
		}	
		if (FileAttr)
		{	
			debug_msg("DeleteFile FileIndex %d  FileAttr->filePath:%s \r\n",i,FileAttr->filePath); 
			ret = FileSys_DeleteFile(FileAttr->filePath);
			if (ret == FST_STA_OK)
			{
				FileDB_DeleteFile(FileDBHdl,i);
				debug_msg("FDB_Delete_ ok! \r\n"); 
			}
			else
			{
				debug_msg("FDB_Delete_Err!! \r\n"); 
				debug_msg("FileIndex i=%d  \r\n",i);
				goto FDB_DelOldFile_Err;
			}	
		}
		else
		{
			debug_msg("FileAttr  Err!! \r\n");	
			 goto FDB_DelOldFile_Err;
		}	
	}
	
	return FileC;
FDB_DelOldFile_Err:
	 return FALSE;
}



#if _ADAS_FUNC_
//#NT#2016/06/01#KCHong -begin
//#NT#Change 1st param to pointer type and add 3rd paramter due to FlowMovie_AdasProcess() need to distinguish differnt CB event.
void FlowMovie_AdasProcess(ADAS_OSD_COORDINATE *pAdasOsdCoord, ADAS_APPS_RESULT_INFO *pAdasInfo, UINT32 EvtType)
{
    //g_AdasOsdCoord = AdasOsdCoord;
    memcpy (&g_AdasOsdCoord, pAdasOsdCoord, sizeof(g_AdasOsdCoord));

    /* Enable FD frame show */
    UxCtrl_SetShow(&UIFlowWndMovie_LDWS_FrameCtrl,TRUE);

    /* Redraw all window OSD */
    UxCtrl_SetDirty(&UIFlowWndMovieCtrl, TRUE);
}
//#NT#2016/06/01#KCHong -end

UINT32 FlowMovie_GetAdasOsdIno(void)
{
    return (UINT32)&g_AdasOsdCoord;
}
#endif


