/*
 * IOTCCMDs.h
 *
 *  Created on: Jan 6, 2016
 *      Author: user
 */


#ifndef IOTCCMDS_H_
#define IOTCCMDS_H_

#include "AVIOCTRLDEFs.h"

// AVIOCTRL Message Type
typedef enum
{

    // dropbox support
//	IOTYPE_XM_CALL_REQ_1      					= 0x603,  //Device?�App?�呼?�请�?//	IOTYPE_XM_CALL_RESP_1     					= 0x604,  //App?�叫应�?
//	IOTYPE_XM_CALL_IND_1						= 0x605,  //Device?�知App已�?移动设�??�听?�令?��?设�??�叫
    IOTYPE_XM_GETDOORLIST_REQ_IOS               = 0x611,  //for iOS use another IOTYPE_XM_GETDOORLIST_REQ
	IOTYPE_XM_CALL_REQ       					= 0x700,//Device?�App?�呼?�请�?	IOTYPE_XM_CALL_RESP    						= 0x701,//App?�叫应�?
    IOTYPE_XM_CALL_RESP                         = 0x701,
	IOTYPE_XM_CALL_IND							= 0x702,//Device?�知App已�?移动设�??�听?�令?��?设�??�叫
    IOTYPE_XM_GETDOORLIST_REQ                   = 0x710,
    IOTYPE_XM_GETDOORLIST_RESP                  = 0x711,
    IOTYPE_XM_GETUNLOCKPASSWDSWITCH_REQ         = 0x714,
    IOTYPE_XM_GETUNLOCKPASSWDSWITCH_RESP        = 0x715,
	IOTYPE_USER_IPCAM_DEVICESLEEP_REQ			= 0x720,
	IOTYPE_USER_IPCAM_DEVICESLEEP_RESP			= 0x721,

	IOTYPE_USER_IPCAM_STARTFWUPGRADE_REQ			= 0x800,
	IOTYPE_USER_IPCAM_STARTFWUPGRADE_RESP			= 0x801,

}ENUM_AVIOCTRL_MSGTYPE_1;

typedef struct
{
	unsigned int channel; // AvServer Index
} SMsgAVIoctrlStartFWUpgradeReq;

typedef struct
{
int result; // ?�傳??0: success;
					//-1: failed case 1
					//-2: failed case 2 ??
} SMsgAVIoctrlStartFWUpgradeResp;

typedef struct{
	unsigned  char  index; //?�索引号�?：Door1,1:Door2
	STimeDay stTime; //事件?�间
    unsigned char reserved[3];
} SMsgAVIoctrlCallReq;

typedef struct{
   unsigned  char  index;
   int nAnswered;
   unsigned char reserved[3];
}__attribute__((packed))SMsgAVIoctrlCallResp;

typedef struct{
   unsigned  char  index; //?�索引号�?：Door1,1:Door2
   unsigned  char  type; //类�?�?：�??�户?�叫,1:?�其他用?��?�?   STimeDay stTime; //事件?�间
   unsigned  char reserved[3];
}SMsgAVIoctrlCallInd;


typedef struct{
      int  channel; // Camera Index
      unsigned  char reserved[4];
} SMsgAVIoctrlSetDeviceSleepReq;

typedef struct{
    int result; //0 success; otherwise: failed
    unsigned  char reserved[4];
} SMsgAVIoctrlSetDeviceSleepResp;



typedef struct
{
    unsigned char bEnable;//�O�_��???�A1��?�A0����?
    unsigned int nTime;//�@�� ????�]0.1~1,1~25��^
    unsigned char reserved[3];
}SAVDoor;

typedef struct{
    unsigned  int count;//?��??
    SAVDoor Door[1]; //??? first address of all Door 0�G??�A1�G��?
} SMsgAVIoctrlGetDoorListResp;

typedef struct{
    int nEnable; //0�G�T��,  1�G?��
    unsigned char reserved[4];
}SMsgAVIoctrlGetUnlockSwitchResp;

#endif
