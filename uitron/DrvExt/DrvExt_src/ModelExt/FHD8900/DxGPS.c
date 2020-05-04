#include "DxCfg.h"
#include "uart.h"
#include "GPS.h"
#include "DxGPS.h"
#include "Debug.h"

///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          DxGPS
#define __DBGLVL__          1 // 0=OFF, 1=ERROR, 2=TRACE
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include "DebugModule.h"
///////////////////////////////////////////////////////////////////////////////

static GPS_UART_OBJ UartObj = {
	.open       = uart2_open,
	.close      = uart2_close,
	.init       = uart2_init,
	.getString  = uart2_getString,
};

void DrvGPS_SetUartPort(void)
{
	GPS_SetUartObj(&UartObj);
}
