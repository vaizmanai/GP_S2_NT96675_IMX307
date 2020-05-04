#include "IntDirCfg.h"
#include "interrupt.h"
#include "DrvExt.h"

///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          DxDrv
#define __DBGLVL__          1 // 0=OFF, 1=ERROR, 2=TRACE
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include "DebugModule.h"
///////////////////////////////////////////////////////////////////////////////

#if 0
const INT_DST  uiIntDirTbl = {
	//MIPS1 interrupt destination
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_TIMER    = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SIE      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SIE2     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_DSP      = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_DRTC     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_IPE      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_IME      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_DCE      = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_IFE      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_IFE2     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_DIS      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_FDE      = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_TV       = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_RHE      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_NOE      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_DAI      = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_H264     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_JPEG     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_GRAPHIC  = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_GRAPHIC2 = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_RSA      = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_ISE      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_TGE      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_TSE      = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_GPIO     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_REMOTE   = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_PWM      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_USB      = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_HASH     = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_NAND     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SDIO     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SDIO2    = FALSE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SDIO3    = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_DMA      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_ETHERNET = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SPI      = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SPI2     = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SPI3     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_CRYPTO   = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_JPEG2    = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SIF      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_I2C      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_I2C2     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_UART     = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_UART2    = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_UART3    = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_UART4    = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_ADC      = TRUE,


	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_IDE      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_NULL_3   = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_NULL_4   = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_NULL_5   = FALSE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_NULL_6   = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_NULL_7   = FALSE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_LVDS     = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_LVDS2    = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_RTC      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_WDT      = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_CG       = TRUE,
	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_CC       = TRUE,

	.int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_I2C3     = TRUE,

	//MIPS2 interrupt destination
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_TIMER    = TRUE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SIE      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SIE2     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_DSP      = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_DRTC     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_IPE      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_IME      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_DCE      = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_IFE      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_IFE2     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_DIS      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_FDE      = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_TV       = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_RHE      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_NOE      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_DAI      = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_H264     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_JPEG     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_GRAPHIC  = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_GRAPHIC2 = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_RSA      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_ISE      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_TGE      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_TSE      = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_GPIO     = TRUE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_REMOTE   = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_PWM      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_USB      = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_HASH     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_NAND     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SDIO     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SDIO2    = TRUE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SDIO3    = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_DMA      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_ETHERNET = TRUE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SPI      = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SPI2     = TRUE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SPI3     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_CRYPTO   = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_JPEG2    = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_SIF      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_I2C      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_I2C2     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_UART     = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_UART2    = TRUE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_UART3    = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_UART4    = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_ADC      = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_IDE      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_NULL_3   = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_NULL_4   = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_NULL_5   = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_NULL_6   = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_NULL_7   = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_LVDS     = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_LVDS2    = FALSE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_RTC      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_WDT      = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_CG       = FALSE,
	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_CC       = TRUE,

	.int_id_dst[CC_CORE_MIPS2].Bit.bInt_ID_I2C3     = FALSE,

	//DSP interrupt destination
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_TIMER      = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SIE        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SIE2       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_DSP        = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_DRTC       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_IPE        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_IME        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_DCE        = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_IFE        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_IFE2       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_DIS        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_FDE        = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_TV         = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_RHE        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_NOE        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_DAI        = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_H264       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_JPEG       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_GRAPHIC    = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_GRAPHIC2   = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_RSA        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_ISE        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_TGE        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_TSE        = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_GPIO       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_REMOTE     = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_PWM        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_USB        = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_HASH       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_NAND       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SDIO       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SDIO2      = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SDIO3      = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_DMA        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_ETHERNET   = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SPI        = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SPI2       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SPI3       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_CRYPTO     = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_JPEG2      = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_SIF        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_I2C        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_I2C2       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_UART       = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_UART2      = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_UART3      = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_UART4      = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_ADC        = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_IDE        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_NULL_3     = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_NULL_4     = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_NULL_5     = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_NULL_6     = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_NULL_7     = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_LVDS       = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_LVDS2      = FALSE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_RTC        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_WDT        = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_CG         = FALSE,
	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_CC         = TRUE,

	.int_id_dst[CC_CORE_DSP].Bit.bInt_ID_I2C3       = FALSE,

};
#endif

void IO_InitIntDir(void)
{
	MODELEXT_HEADER *header;
	INT_DST  *uiIntDirTbl;

	uiIntDirTbl = (INT_DST *)Dx_GetModelExtCfg(MODELEXT_TYPE_INTDIR_CFG, &header);
	if (!uiIntDirTbl || !header) {
		DBG_FATAL("Modelext: Interrupt direction setting is null\n");
		return;
	}

	int_setConfig(INT_CONFIG_ID_INT_DESTINATION, (UINT32)uiIntDirTbl);
}


