#include "modelext_info.h"
#include "gpio_info.h"
#include "IOCfg.h"

GPIO_INIT_OBJ ind_gpio_info_data[] __attribute__((section("modelext_data.gpio_info"))) = {
#if 0
	{  GPIO_LENS_RESET,        GPIO_DIR_OUTPUT,    PAD_NONE,             PAD_PIN_NOT_EXIST   },
	{  GPIO_LENS_ZOOM_INTR,    GPIO_DIR_INPUT,     PAD_PULLDOWN,         PAD_LENS_ZOOM_INTR  },
	{  GPIO_LENS_FOCUS_INTR,   GPIO_DIR_INPUT,     PAD_PULLDOWN,         PAD_LENS_FOCUS_INTR },
	{  GPIO_LENS_IR_CTRL0,     GPIO_DIR_OUTPUT,    PAD_NONE,             PAD_PIN_NOT_EXIST   },
	{  GPIO_LENS_IR_CTRL1,     GPIO_DIR_OUTPUT,    PAD_NONE,             PAD_PIN_NOT_EXIST   },

	{  GPIO_KEY_LEFT,          GPIO_DIR_INPUT,     PAD_PULLUP,           PAD_KEY_LEFT        },
	{  GPIO_KEY_ENTER,         GPIO_DIR_INPUT,     PAD_PULLUP,           PAD_KEY_ENTER       },
	{  GPIO_KEY_UP,            GPIO_DIR_INPUT,     PAD_PULLUP,           PAD_KEY_UP          },
	{  GPIO_KEY_RIGHT,         GPIO_DIR_INPUT,     PAD_PULLUP,           PAD_KEY_RIGHT       },
	{  GPIO_KEY_PLAYBACK,      GPIO_DIR_INPUT,     PAD_PULLUP,           PAD_KEY_PLAYBACK    },
	{  GPIO_KEY_DOWN,          GPIO_DIR_INPUT,     PAD_PULLUP,           PAD_KEY_DOWN        },
	{  GPIO_KEY_MODE,          GPIO_DIR_INPUT,     PAD_PULLUP,           PAD_KEY_MODE        },
#endif
//	{  GPIO_LCD_BLG_PCTL,		GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_LOW,	PAD_PIN_NOT_EXIST	}, // high active
	{  GPIO_LCD_BLG_PCTL,		GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_PIN_NOT_EXIST	}, // high active
	{  GPIO_LCD_RESET,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_PIN_NOT_EXIST	}, // low reset
	{  GPIO_CARD_DETECT,		GPIO_DIR_INPUT,		PAD_PULLUP,				PAD_CARD_DETECT		}, // low detect
	{  GPIO_CARD_POWER,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_PIN_NOT_EXIST	}, // low active
	{  GPIO_WIFI_PWR_ON,		GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_PIN_NOT_EXIST	}, // high active
	{  GPIO_WIFI_REG_ON,		GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_PIN_NOT_EXIST	}, // high active
	{  GPIO_SENSOR_18,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_PIN_NOT_EXIST	}, // high active
	{  GPIO_SENSOR_28,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_PIN_NOT_EXIST	}, // high active
	{  GPIO_MOVIE_LED,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		GPIO_SET_NONE		},
	{  GPIO_GS_RST,				GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_LOW,	GPIO_SET_NONE		},
	// VOICE
	{  GPIO_VOICE_BUSY_DET,		GPIO_DIR_INPUT,		PAD_PULLUP,				PAD_VOICE_BUSY_DET	},
	{  GPIO_VOICE_DATA,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_VOICE_DATA		},
	//amplifier
	{  GPIO_AMP_POWER,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_AMP_POWER		},
	{  GPIO_AMP_SHDN,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_AMP_SHDN		},
	//Edog onoff
	{  GPIO_EDOG_CTL,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_LOW,	PAD_EDOG_CTL		},

	{  GPIO_LCD_DISP,			GPIO_DIR_OUTPUT,	GPIO_SET_OUTPUT_HI,		PAD_PIN_NOT_EXIST	}, // high active


};

MODELEXT_HEADER ind_gpio_info_header __attribute__((section("modelext_header.gpio_info"))) = {
	.size = sizeof(ind_gpio_info_data) + sizeof(MODELEXT_HEADER),
	.type = MODELEXT_TYPE_GPIO_INFO,
	.number = sizeof(ind_gpio_info_data) / sizeof(GPIO_INIT_OBJ),
	.version = GPIO_INFO_VER,
};
