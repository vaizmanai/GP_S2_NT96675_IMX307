#include "modelext_info.h"
#include "top.h"

PIN_GROUP_CONFIG ind_pinmux_cfg_data[] __attribute__((section("modelext_data.pinmux_cfg"))) = {
	// Module name              pinmux config

	//
	// Storage configuration
	//
	{PIN_FUNC_SDIO,             PIN_SDIO_CFG_4BITS | PIN_SDIO_CFG_1ST_PINMUX},
	{PIN_FUNC_SDIO2,            PIN_SDIO_CFG_4BITS},
	{PIN_FUNC_SDIO3,            PIN_SDIO_CFG_NONE},
#if defined(_EMBMEM_NAND_)
	{PIN_FUNC_NAND,             PIN_NAND_CFG_1CS},
#elif defined(_EMBMEM_SPI_NAND_)
	{PIN_FUNC_NAND,             PIN_NAND_CFG_1CS | PIN_NAND_CFG_SPI_NAND},
#elif defined(_EMBMEM_SPI_NOR_)
	{PIN_FUNC_NAND,             PIN_NAND_CFG_1CS | PIN_NAND_CFG_SPI_NOR},
#else
	{PIN_FUNC_NAND,             PIN_NAND_CFG_NONE},
#endif

	//
	// Sensor configuration
	//
#if (defined(_SENSOR1_CMOS_IMX291M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},
#elif (defined(_SENSOR1_CMOS_IMX291M_) && defined(_SENSOR2_CMOS_TP2827P_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_CCIR8BITS | PIN_SENSOR2_CFG_MCLK},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},
#elif (defined(_SENSOR1_CMOS_IMX290M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
#elif (defined(_SENSOR1_CMOS_IMX291M_) && defined(_SENSOR2_CMOS_TP2825_))
    {PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
    {PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_CCIR8BITS|PIN_SENSOR2_CFG_MCLK},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},
#elif (defined(_SENSOR1_CMOS_GC2053P_) && defined(_SENSOR2_CMOS_TP2825_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
    {PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_CCIR8BITS|PIN_SENSOR2_CFG_MCLK},
    {
        PIN_FUNC_MIPI_LVDS,
        PIN_MIPI_LVDS_CFG_NONE
        //PIN_MIPI_LVDS_CFG_CLK0 |
        //PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
    },
#elif (defined(_SENSOR1_CMOS_GC2053P_) && defined(_SENSOR2_CMOS_OFF_))
        {PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
        {PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
        {
            PIN_FUNC_MIPI_LVDS,
            PIN_MIPI_LVDS_CFG_NONE
            //PIN_MIPI_LVDS_CFG_CLK0 |
            //PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
        },
#elif (defined(_SENSOR1_CMOS_GC2053M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,			PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,			PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0
	},
#elif (defined(_SENSOR1_CMOS_OV2715M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0
	},
#elif (defined(_SENSOR1_CMOS_OV2715M_) && defined(_SENSOR2_CMOS_OV2715M_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 | PIN_MIPI_LVDS_CFG_CLK1 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT2
	},
#elif (defined(_SENSOR1_CMOS_OV2735M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0
	},
#elif (defined(_SENSOR1_CMOS_OV2735M_) && defined(_SENSOR2_CMOS_OV2735M_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 | PIN_MIPI_LVDS_CFG_CLK1 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT2
	},
#elif (defined(_SENSOR1_CMOS_AR0237L_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_LVDS | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},
#elif (defined(_SENSOR1_CMOS_OS05A10M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},
#elif (defined(_SENSOR1_CMOS_OS08A10M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},
#elif (defined(_SENSOR1_CMOS_OV4689M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},
#elif (defined(_SENSOR1_CMOS_AR0237P_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_NONE
	},
#elif (defined(_SENSOR1_CMOS_AR0237IRP_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_NONE
	},
#elif (defined(_SENSOR1_CMOS_AR0521M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},

#elif (defined(_SENSOR1_CMOS_AR0330M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3
	},

#elif (defined(_SENSOR1_CMOS_AR0330P_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_NONE
	},

#elif (defined(_SENSOR1_CMOS_PS5250M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1
	},

#elif (defined(_SENSOR1_CMOS_SC4236M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1
	},

#elif (defined(_SENSOR1_CMOS_SC5035M_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,
		PIN_MIPI_LVDS_CFG_CLK0 |
		PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1
	},

#elif (defined(_SENSOR1_CMOS_SIEPATGEN_) && defined(_SENSOR2_CMOS_OFF_))
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_NONE},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{
		PIN_FUNC_MIPI_LVDS,        PIN_MIPI_LVDS_CFG_NONE
	},
	
#elif (defined(_SENSOR1_CMOS_IMX323P_) && defined(_SENSOR2_CMOS_OFF_))
    {PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
    {PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
    {
        PIN_FUNC_MIPI_LVDS,
        PIN_MIPI_LVDS_CFG_NONE
    },
#elif (defined(_SENSOR1_CMOS_IMX323P_) && defined(_SENSOR2_CMOS_TVP5150_))
{PIN_FUNC_SENSOR,			PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
{PIN_FUNC_SENSOR2,			PIN_SENSOR2_CFG_CCIR8BITS | PIN_SENSOR_CFG_SP2CLK},
{PIN_FUNC_MIPI_LVDS,        PIN_MIPI_LVDS_CFG_NONE},

#elif (defined(_SENSOR1_CMOS_GC2053P_) && defined(_SENSOR2_CMOS_TVP5150_))
	{PIN_FUNC_SENSOR,			PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
	{PIN_FUNC_SENSOR2,			PIN_SENSOR2_CFG_CCIR8BITS | PIN_SENSOR2_CFG_MCLK},
	{PIN_FUNC_MIPI_LVDS,		PIN_MIPI_LVDS_CFG_NONE},
#elif (defined(_SENSOR1_CMOS_GC2053P_) && defined(_SENSOR2_CMOS_OFF_))
		{PIN_FUNC_SENSOR,			PIN_SENSOR_CFG_12BITS | PIN_SENSOR_CFG_MCLK},
		{PIN_FUNC_SENSOR2,			PIN_SENSOR2_CFG_NONE},
		{PIN_FUNC_MIPI_LVDS,		PIN_MIPI_LVDS_CFG_NONE},

#else
	{PIN_FUNC_SENSOR,           PIN_SENSOR_CFG_MIPI},
	{PIN_FUNC_SENSOR2,          PIN_SENSOR2_CFG_NONE},
	{PIN_FUNC_MIPI_LVDS,        PIN_MIPI_LVDS_CFG_CLK0 | PIN_MIPI_LVDS_CFG_DAT0 | PIN_MIPI_LVDS_CFG_DAT1 | PIN_MIPI_LVDS_CFG_DAT2 | PIN_MIPI_LVDS_CFG_DAT3},
#endif
	//
	// Serial interface configuration
	//
	{
		PIN_FUNC_I2C,              PIN_I2C_CFG_NONE |

#if (1) // //for PowerIC
		PIN_I2C_CFG_CH3 |
#endif
#if(defined(_SENSOR1_CMOS_IMX291M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH1 |
#endif
#if(defined(_SENSOR1_CMOS_IMX291M_) && defined(_SENSOR2_CMOS_TP2827P_))
		PIN_I2C_CFG_CH2 | PIN_I2C_CFG_CH1 |
#endif
#if(defined(_SENSOR1_CMOS_IMX290M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif

#if(defined(_SENSOR1_CMOS_GC2053P_) && defined(_SENSOR2_CMOS_TP2825_))
		PIN_I2C_CFG_CH2 | PIN_I2C_CFG_CH1 |
#endif

#if(defined(_SENSOR1_CMOS_GC2053P_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH1 |
#endif

#if(defined(_SENSOR1_CMOS_GC2053M_) && defined(_SENSOR2_CMOS_OFF_))
			PIN_I2C_CFG_CH1 |
#endif

#if (defined(_SENSOR1_CMOS_IMX291M_) && defined(_SENSOR2_CMOS_TP2825_))
    PIN_I2C_CFG_CH1 |PIN_I2C_CFG_CH2|
#endif

#if(defined(_SENSOR1_CMOS_OV2715M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_OV2715M_) && defined(_SENSOR2_CMOS_OV2715M_))
		PIN_I2C_CFG_CH2 | PIN_I2C_CFG_CH1 |
#endif
#if(defined(_SENSOR1_CMOS_OV2735M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_OV2735M_) && defined(_SENSOR2_CMOS_OV2735M_))
		PIN_I2C_CFG_CH2 | PIN_I2C_CFG_CH1 |
#endif
#if(defined(_SENSOR1_CMOS_IMX323P_) && defined(_SENSOR2_CMOS_TVP5150_))
		PIN_I2C_CFG_CH1 |
#endif
#if(defined(_SENSOR1_CMOS_GC2053P_) && defined(_SENSOR2_CMOS_TVP5150_))
				PIN_I2C_CFG_CH1 |
#endif
#if(defined(_SENSOR1_CMOS_AR0237L_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_OS05A10M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_OS08A10M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_OV4689M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_AR0237P_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_AR0237IRP_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_AR0521M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_AR0330M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_AR0330P_) && defined(_SENSOR2_CMOS_OFF_)) //for TP-LINK
		PIN_I2C_CFG_CH1 |
#endif
#if(defined(_SENSOR1_CMOS_PS5250M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_SC4236M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_SC5035M_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_I2C_CFG_CH2 |
#endif
#if(defined(_SENSOR1_CMOS_IMX323P_) && defined(_SENSOR2_CMOS_OFF_))
	PIN_I2C_CFG_CH1 |
#endif
		0
	},

	{
		PIN_FUNC_SIF,              PIN_SIF_CFG_NONE |

#if (defined(_SENSOR1_CMOS_OFF_) && defined(_SENSOR2_CMOS_OFF_))
		PIN_SIF_CFG_NONE |
#endif
		0
	},


	{PIN_FUNC_UART,             PIN_UART_CFG_CH1 |PIN_UART_CFG_CH2 | PIN_UART_CFG_CH3},
	{
		PIN_FUNC_SPI,              PIN_SPI_CFG_NONE |
#if 0//!defined(_Gyro_None_)
		PIN_SPI_CFG_CH3 | PIN_SPI_CFG_CH3_2BITS |
#endif
		0
	},

	{PIN_FUNC_REMOTE,           PIN_REMOTE_CFG_NONE},

	//
	// PWM configuration
	//
	{PIN_FUNC_PWM,              PIN_PWM_CFG_NONE /*| PIN_PWM_CFG_PWM7*/},

	//
	// AUDIO configuration
	//
	{PIN_FUNC_AUDIO,            PIN_AUDIO_CFG_NONE},

	//
	// Display configuration
	//
	{PIN_FUNC_LCD,              PINMUX_DISPMUX_SEL_LCD | PINMUX_LCDMODE_AUTO_PINMUX /*PINMUX_LCDMODE_RGB_PARALL565*/}, // for ILI9342C
	{PIN_FUNC_TV,               PINMUX_TV_HDMI_CFG_NORMAL},

	{PIN_FUNC_ETH,              PIN_ETH_CFG_NONE/*PIN_ETH_CFG_INTERANL*/},
	{PIN_FUNC_MISC,             PIN_MISC_CFG_NONE}
};


MODELEXT_HEADER ind_pinmux_cfg_header __attribute__((section("modelext_header.pinmux_cfg"))) = {
	.size = sizeof(ind_pinmux_cfg_data) + sizeof(MODELEXT_HEADER),
	.type = MODELEXT_TYPE_PINMUX_CFG,
	.number = sizeof(ind_pinmux_cfg_data) / sizeof(PIN_GROUP_CONFIG),
	.version = PIN_GROUP_CONFIG_VER,
};
