/*
    Copyright   Novatek Microelectronics Corp. 2018.  All rights reserved.

    @file       CommunicateToMCU.c
    @ingroup

    @brief      Execute command via UART interface.
                Execute command and output message via UART interface.

    @note       Nothing.

    @version    V1.00.000
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Debug.h"
#include "SysKer.h"
#include "kernel.h"
#include "uart.h"
#include "CommunicateToMCU.h"

//@{
#define __MODULE__					CommunicateToMCU
#define __DBGLVL__					1		//0=OFF, 1=ERROR, 2=TRACE
#define __DBGFLT__ 					"*"		//*=All, [mark]=CustomClass
#include "DebugModule.h"





//Declare functions



//Declare variables

#define PRI_CommunicateToMCURECEIVE            10
#define STKSIZE_CommunicateToMCURECEIVE        6144//64KB stack size

UINT32  CommunicateToMCURECEIVE_ID = 0;
UINT32  FLG_ID_CommunicateToMCU = 0;

UINT32 RecvieCMD_FromMCU=0;
BOOL RecvieFromMCU_Flag = FALSE;
//CommunicateToMCU heartbeat
//static UINT32 CommunicateToMCUHeartBeat = 0;         //#NT#2015/10/02#KCHong#Add GPS heartbeat to detect GPS status

static CommunicateToMCU_UART_OBJ CommunicateToMCUUart = {
	.open		= uart2_open,
	.close		= uart2_close,
	.init		= uart2_init,
	.getString	= uart2_getString,
};

extern void CommunicateToMCURecTsk(void);


void CommunicateToMCU_InstallID(void)
{
    OS_CONFIG_TASK(CommunicateToMCURECEIVE_ID, PRI_CommunicateToMCURECEIVE, STKSIZE_CommunicateToMCURECEIVE, CommunicateToMCURecTsk);
    OS_CONFIG_FLAG(FLG_ID_CommunicateToMCU);
}

void CommunicateToMCU_SetUartObj(CommunicateToMCU_UART_OBJ *UartObj)
{
	memcpy(&CommunicateToMCUUart, UartObj, sizeof(CommunicateToMCU_UART_OBJ));
}

static BOOL bCommunicateToMCURecOpened = FALSE;
ER CommunicateToMCURec_Open(UART_BAUDRATE BaudRate)
{
    if (bCommunicateToMCURecOpened)
        return E_SYS;
#if 1
    if (CommunicateToMCUUart.open() == E_OK)
    {
        DBG_DUMP("UART2 open success\r\n");
        CommunicateToMCUUart.init(BaudRate, UART_LEN_L8_S1, UART_PARITY_NONE);
    }
    else
    {
        DBG_ERR("UART2 open fail!\r\n");
        return E_SYS;
    }

    DBG_DUMP("Start CommunicateToMCU receive task\r\n");

    sta_tsk(CommunicateToMCURECEIVE_ID,0);

    loc_cpu();
    bCommunicateToMCURecOpened = TRUE;
    unl_cpu();
#endif
    return E_OK;
}

ER CommunicateToMCURec_Close(void)
{
    if (!bCommunicateToMCURecOpened)
        return E_SYS;

    if (CommunicateToMCUUart.close() == E_OK)
        DBG_DUMP("UART close success\r\n");
    else
        DBG_ERR("UART close fail!\r\n");

    DBG_DUMP("Terminate CommunicateToMCU receive task\r\n");

    ter_tsk(CommunicateToMCURECEIVE_ID);

    loc_cpu();
    bCommunicateToMCURecOpened = FALSE;
    unl_cpu();

    return E_OK;
}

void CommunicateToMCURecTsk(void)
{
    UINT32  uiLen;
  //  UINT16  CheckSentenceType1, CheckSentenceType2;
//    UINT32  CheckSentenceType3;
    CHAR    RecSentence[180];
   // CHAR    *pSentenceData;

    kent_tsk();

    clr_flg(FLG_ID_CommunicateToMCU, CommunicateToMCU_FLAG_DATAVALID);

    while(CommunicateToMCURECEIVE_ID)
    {
    	  uiLen = 180;
        if (CommunicateToMCUUart.getString(RecSentence, &uiLen) == E_PAR)
        {
            DBG_ERR("UART parameter error!\r\n");
        }
	/* for(i=0;i<uiLen;i++)
	 {
	 	debug_msg(" %c ",RecSentence[i]);
	 }*/
	 if((RecSentence[0]=='A')&&(RecSentence[1]=='T'))
	 {
	      if((memcmp(RecSentence,"AT",2) == 0) && (uiLen == 2))
		{
			RecvieCMD_FromMCU = Receive_AT;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+WIFION",9) == 0) && (uiLen == 9))
		{
			RecvieCMD_FromMCU = Receive_AT_WIFION;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+WIFIOFF",10) == 0) && (uiLen == 10))
		{
			RecvieCMD_FromMCU = Receive_AT_WIFIOFF;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+SD",5) == 0) && (uiLen == 5))
		{
			RecvieCMD_FromMCU = Receive_AT_SD;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+SOS",6) == 0) && (uiLen == 6))
		{
			RecvieCMD_FromMCU = Receive_AT_SOS;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}	
		else if((memcmp(RecSentence,"AT+RESET",8) == 0) && (uiLen == 8))
		{
			RecvieCMD_FromMCU = Receive_AT_RESET;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}		
		else if((memcmp(RecSentence,"AT+50HZ",7) == 0) && (uiLen == 7))
		{
			RecvieCMD_FromMCU = Receive_AT_50HZ;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}	
		else if((memcmp(RecSentence,"AT+60HZ",7) == 0) && (uiLen == 7))
		{
			RecvieCMD_FromMCU = Receive_AT_60HZ;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}	
		else if((memcmp(RecSentence,"AT+FORMAT",9) == 0) && (uiLen == 9))
		{
			RecvieCMD_FromMCU = Receive_AT_FORMAT;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}	
		else if((memcmp(RecSentence,"AT+MICR",7) == 0) && (uiLen == 7))
		{
			RecvieCMD_FromMCU = Receive_AT_MICR;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}				
		else if((memcmp(RecSentence,"AT+MICL",7) == 0) && (uiLen == 7))
		{
			RecvieCMD_FromMCU = Receive_AT_MICL;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}		
		else if((memcmp(RecSentence,"AT+MICOFF",9) == 0) && (uiLen == 9))
		{
			RecvieCMD_FromMCU = Receive_AT_MICOFF;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+PHOTO",8) == 0) && (uiLen == 8))
		{
			RecvieCMD_FromMCU = Receive_AT_PHOTO;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+MENU",7) == 0) && (uiLen == 7))
		{
			RecvieCMD_FromMCU = Receive_AT_MENU;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+MODE",7) == 0) && (uiLen == 7))
		{
			RecvieCMD_FromMCU = Receive_AT_MODE;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+UP",5) == 0) && (uiLen == 5))
		{
			RecvieCMD_FromMCU = Receive_AT_UP;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+DOWN",7) == 0) && (uiLen == 7))
		{
			RecvieCMD_FromMCU = Receive_AT_DOWN;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+ENTER",8) == 0) && (uiLen == 8))
		{
			RecvieCMD_FromMCU = Receive_AT_ENTER;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+DELBIN",9) == 0) && (uiLen == 9))
		{
			RecvieCMD_FromMCU = Receive_AT_DELBIN;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+RATE",7) == 0) && (uiLen == 7))
		{
			RecvieCMD_FromMCU = Receive_AT_RATE;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+RATEH",8) == 0) && (uiLen == 8))
		{
			RecvieCMD_FromMCU = Receive_AT_RATEH;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+RATEM",8) == 0) && (uiLen == 8))
		{
			RecvieCMD_FromMCU = Receive_AT_RATEM;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+RATEL",8) == 0) && (uiLen == 8))
		{
			RecvieCMD_FromMCU = Receive_AT_RATEL;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else if((memcmp(RecSentence,"AT+CCDMODE",10) == 0) && (uiLen == 10))
		{
			RecvieCMD_FromMCU = Receive_AT_CCDMODE;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}		
		else if((memcmp(RecSentence,"AT+PWROFF",9) == 0) && (uiLen == 9))
		{
			RecvieCMD_FromMCU = Receive_AT_PWROFF;
			RecvieFromMCU_Flag = TRUE;
			continue;
		}
		else
		{}
	 }
	 memset(RecSentence,0x00,sizeof(RecSentence));
    }
}

ER CommunicateToMCURec_Reset(void)
{
    return E_OK;
}


/*UINT32 GetGPSHeartBeat(void)
{
    return GPSHeartBeat;
}*/
//#NT#2015/10/02#KCHong -end
