/**
    @file       CommunicateToMCU.h
    @ingroup

    @brief      Sample module brief
                Sample module description

    @note       Nothing (or anything need to be mentioned).

    Copyright   Novatek Microelectronics Corp. 2005.  All rights reserved.
*/

#ifndef _CommunicateToMCU_H
#define _CommunicateToMCU_H

#include "Type.h"
#include "uart.h"



#define CommunicateToMCU_FLAG_DATAVALID		0x00000001
#define CommunicateToMCU_FLAG_LOG			0x00000002

#define Return_AT   		   "AT OK\r\n"
#define Return_AT_POWOFF_OK   	   "AT+PWROFF OK\r\n"
#define Return_AT_CCDMODE_OK   	   "AT+CCDMODE OK\r\n"
#define Return_AT_DELBIN_OK   	   "AT+DELBIN OK\r\n"
#define Return_AT_RATEH_OK   	   "AT+RATEH OK\r\n"
#define Return_AT_RATEM_OK   	   "AT+RATEM OK\r\n"
#define Return_AT_RATEL_OK   	   "AT+RATEL OK\r\n"
#define Return_WIFION        "AT+WIFION OK\r\n"
#define Return_WIFIOFF       "AT+WIFIOFF OK\r\n"
#define Return_SD_OK	    "AT+SD OK\r\n"
#define Return_SD_ERROR     "AT+SD ERROR\r\n"
#define Return_SD_SLOW      "AT+SD SLOW\r\n"
#define Return_SD_FULL       "AT+SD FULL\r\n"
#define Return_SD_FAIL       "AT+SD FAILL\r\n"
#define Return_SD_NOFILESYSTEM      "AT+SD NO_FILESYSTEM\r\n"
#define Return_SOSING     	 "AT+SOSING\r\n"
#define Return_SOSFINISH  	 "AT+SOS FINISH\r\n"
#define Return_AT_SOS      	 "AT+SOS\r\n"
#define Return_SOSERROR  	 "AT+SOS ERROR\r\n"
#define Return_RESETOK    	 "AT+RESET OK\r\n"
#define Return_50HZ  	       "AT+50HZ OK\r\n"
#define Return_60HZ  	       "AT+60HZ OK\r\n"
#define Return_FORMATING      "AT+FORMATING\r\n"
#define Return_FORMAT_OK      "AT+FORMAT OK\r\n"
#define Return_FORMAT_ERROR 	        "AT+FORMAT ERROR\r\n"
#define Return_MICR_OK 	        "AT+MICR OK\r\n"
#define Return_MICL_OK 	        "AT+MICL OK\r\n"
#define Return_MICOFF_OK 	  "AT+MICOFF OK\r\n"
#define Return_PHOTO_OK 	  "AT+PHOTO OK\r\n"
#define Return_PHOTO_ERROR 	  "AT+PHOTO ERROR\r\n"
#define Return_MENU 	      		  "AT+MENU OK\r\n"
#define Return_MODE 	      		  "AT+MODE OK\r\n"
#define Return_UP 	      		  "AT+UP OK\r\n"
#define Return_DOWN 	        "AT+DOWN OK\r\n"
#define Return_ENTER 	        "AT+ENTER OK\r\n"



typedef struct {
	ER(*open)(void);
	ER(*close)(void);
	void(*init)(UART_BAUDRATE BaudRate, UART_LENGTH Length, UART_PARITY Parity);
	ER(*getString)(CHAR *pcString, UINT32 *pcBufferLen);
} CommunicateToMCU_UART_OBJ, *pCommunicateToMCU_UART_OBJ;

typedef struct {
	CHAR    *pCommunicateToMCUDataStartAddr;
	UINT32  CommunicateToMCUBufUsedPos;
	UINT32  CommunicateToMCUBufSize;
} CommunicateToMCUBuf, *pCommunicateToMCUBuf;



typedef enum {
	Receive_AT,
	Receive_AT_WIFION,
	Receive_AT_WIFIOFF,
	Receive_AT_SD,
	Receive_AT_SOS,
	Receive_AT_RESET,
	Receive_AT_50HZ,
	Receive_AT_60HZ,
	Receive_AT_FORMAT,
	Receive_AT_MICR,
	Receive_AT_MICL,
	Receive_AT_MICOFF,
	Receive_AT_PHOTO,
	Receive_AT_MENU,
	Receive_AT_MODE,
	Receive_AT_UP,
	Receive_AT_DOWN,
	Receive_AT_ENTER,
	Receive_AT_DELBIN,
	Receive_AT_RATE,
	Receive_AT_RATEH,
	Receive_AT_RATEM,
	Receive_AT_RATEL,
	Receive_AT_CCDMODE,
	Receive_AT_PWROFF,
} ReceiveCMDFromMCU;



extern void CommunicateToMCU_InstallID(void) _SECTION(".kercfg_text");
extern void CommunicateToMCU_SetUartObj(CommunicateToMCU_UART_OBJ *UartObj);
extern ER CommunicateToMCURec_Open(UART_BAUDRATE BaudRate);
extern ER CommunicateToMCURec_Close(void);
extern ER CommunicateToMCURec_Reset(void);


extern UINT32 RecvieCMD_FromMCU;
extern BOOL RecvieFromMCU_Flag;

extern UINT32 _SECTION(".kercfg_data") CommunicateToMCURECEIVE_ID; // GPS Task
extern UINT32 _SECTION(".kercfg_data") FLG_ID_CommunicateToMCU; // GPS Flag
#endif
