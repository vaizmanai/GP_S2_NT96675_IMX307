#ifndef _PRJCFG_H_
#define _PRJCFG_H_
#include "Type.h"
//#include "SysKer.h"

//==============================================================================
//   GENERAL CONFIG
//==============================================================================
//..............................................................................
// LD version and name
#define LOADER_VERSION                  1
#define LOADER_VERSION_CHECK            DISABLE

//..............................................................................
// FW version and name
#define FW_VERSION_HIDDEN               "00.00" //�̦h32��bytes, �]�t�r�Ŧ굲����'\0'//���ê�����
#define FW_UPDATE_NAME                  "A:\\FW96650A.bin"
#define FW_VERSION_RELEASE              DISABLE //ENABLE
#define FW_VERSION_NUM                  "ECOSDEMO_001_001"
//..............................................................................
// Debug Message
#define MSG_OUTPUT_UART1_DIRECT ENABLE

#endif //_PRJCFG_H_
