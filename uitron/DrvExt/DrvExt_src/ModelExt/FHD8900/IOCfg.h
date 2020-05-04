/**
    Copyright   Novatek Microelectronics Corp. 2012.  All rights reserved.

    @file       IOCfg.h
    @ingroup    mIPRJAPCommonIO

    @brief      Header file of IO config
                This file is the header file of IO config

    @note       Nothing.
    @date       2012/09/04
*/

/** \addtogroup mIPRJAPCommonIO */
//@{

#ifndef _IOCFG_H
#define _IOCFG_H

#include "Type.h"
#include "IOInit.h"
#include "pad.h"
#include "top.h"
#include "gpio.h"
#include "adc.h"
#include "pwm.h"
#include "gpio_info.h"
#define USE_EXTGPIO  DISABLE
#define USE_VIO ENABLE

#if (USE_VIO == ENABLE)
#define VIO_TV_DET                  1
#define VIO_HDMI_DET                2
#define VIO_LCD2_DET                3
#define VIO_SENSOR2_DET             4
#define VIO_SENSOR1_DET             5
#define VIO_AIN_DET                 6
#define VIO_MAX_ID                  16
extern UINT32 vio_getpin(UINT32 id);
extern void vio_setpin(UINT32 id, UINT32 v);
#endif

//--------------------------------------------------------------------
// GPIO common
//--------------------------------------------------------------------
#define GPIO_SET_NONE               0xffffff
#define GPIO_SET_OUTPUT_LOW         0x0
#define GPIO_SET_OUTPUT_HI          0x1

//--------------------------------------------------------------------
// ADC common
//--------------------------------------------------------------------

#define GPIO_KEY                    DISABLE
#define ADC_KEY                     ENABLE

#define VOLDET_ADC_CONT_MODE        ENABLE //!< ENABLE for continuous, DISABLE for one-shot

#if (VOLDET_ADC_CONT_MODE == ENABLE)
#define VOLDET_ADC_MODE             TRUE
#else
#define VOLDET_ADC_MODE             FALSE
#endif

//--------------------------------------------------------------------
// PWM common
//--------------------------------------------------------------------
#if USE_EXTGPIO
#define GPIO_NULL                   L_GPIO_16
#else
#define GPIO_NULL                   L_GPIO_16
#endif
//--------------------------------------------------------------------
// Display device
//--------------------------------------------------------------------
// LCD communicate
#define LCD_COMM_DUMMY              0
#define LCD_COMM_BY_GPIO            1
#define LCD_COMM_BY_SIF             2
#if _FPGA_EMULATION_
#define LCD_COMM_CTRL               LCD_COMM_BY_SIF //FPGA
#else
#define LCD_COMM_CTRL               LCD_COMM_BY_GPIO
#endif
#if (LCD_COMM_CTRL == LCD_COMM_BY_GPIO)
#define GPIO_LCD_SIF_SEN            L_GPIO_21
#define GPIO_LCD_SIF_SCK            L_GPIO_22
#define GPIO_LCD_SIF_SDA            L_GPIO_23
#endif
#if (LCD_COMM_CTRL == LCD_COMM_BY_SIF)
#define SIF_LCD_CH                  SIF_CH2
#define PAD_LCD_SIF_SEN             PAD_PIN_LGPIO21
#define PAD_LCD_SIF_SCK             PAD_PIN_LGPIO22
#define PAD_LCD_SIF_SDA             PAD_PIN_LGPIO23
#define DIR_LCD_SIF_SEN             PAD_PULLUP
#define DIR_LCD_SIF_SCK             PAD_PULLUP
#define DIR_LCD_SIF_SDA             PAD_PULLUP
#endif
//#define GPIO_LCD_SLEEP              87 //FPGA not support
#if USE_EXTGPIO
#define GPIO_LCD_RESET              extio_getGpioPinNumber(IO_LCD_CTRL_RESET)
#define GPIO_LCD_POWER_EN           extio_getGpioPinNumber(IO_LCD_CTRL_POWER)
#else
#define GPIO_LCD_RESET              P_GPIO_3
#define GPIO_LCD_POWER_EN           GPIO_NULL //P_GPIO_1
#endif
#define GPIO_LCD_BLG_PWR            GPIO_NULL//GPIO_LCD_POWER_EN

// LCD backlight
#define LCD_BACKLIGHT_DUMMY         0
#define LCD_BACKLIGHT_BY_GPIO       1
#define LCD_BACKLIGHT_BY_PWM        2
#define LCD_BACKLIGHT_BY_PWRIC      3
#define LCD_BACKLIGHT_CTRL          LCD_BACKLIGHT_BY_GPIO
#if (LCD_BACKLIGHT_CTRL == LCD_BACKLIGHT_BY_PWM)
#if USE_EXTGPIO
#define GPIO_PWM_LCD_BLG_PCTL       extio_getGpioPinNumber(IO_LCD_BLG_PWM)
#define PWMID_LCD_BLG_PCTL          extio_getGpioPinNumber(IO_LCD_BLG_PWM)
#else
#define GPIO_PWM_LCD_BLG_PCTL       PWMID_7
#define PWMID_LCD_BLG_PCTL          PWMID_7
#endif
#elif (LCD_BACKLIGHT_CTRL == LCD_BACKLIGHT_BY_GPIO)
#if USE_EXTGPIO
#define GPIO_LCD_BLG_PCTL           extio_getGpioPinNumber(IO_LCD_BLG_PCTL)
#define PAD_LCD_BLG_PCTL            extio_getGpioPadNumber(IO_LCD_BLG_PCTL)
#else
#define GPIO_LCD_BLG_PCTL           P_GPIO_1
#define PAD_LCD_BLG_PCTL            PAD_PIN_PGPIO1
#endif
#endif

// LCD2 communicate
#define LCD2_COMM_CTRL              LCD_COMM_BY_GPIO //FPGA
#if (LCD2_COMM_CTRL == LCD_COMM_BY_GPIO)
#define GPIO_LCD2_SIF_SEN           P_GPIO_23 //FPGA --- NOTE! it will conflict with PIN_SIF_CFG_CH2
#define GPIO_LCD2_SIF_SCK           P_GPIO_25 //FPGA --- NOTE! it will conflict with PIN_SIF_CFG_CH2
#define GPIO_LCD2_SIF_SDA           P_GPIO_26 //FPGA --- NOTE! it will conflict with PIN_SIF_CFG_CH2
#endif
#if (LCD2_COMM_CTRL == LCD_COMM_BY_SIF)
#define SIF_LCD2_CH                 SIF_CHx
#define PAD_LCD2_SIF_SEN            PAD_PIN_PGPIO23
#define PAD_LCD2_SIF_SCK            PAD_PIN_PGPIO25
#define PAD_LCD2_SIF_SDA            PAD_PIN_PGPIO26
#endif
//#define GPIO_LCD2_SLEEP             87 //FPGA not support
//#define GPIO_LCD2_RESET             88 //FPGA not support

// LCD2 backlight
#define LCD2_BACKLIGHT_CTRL         LCD_BACKLIGHT_DUMMY //FPGA
#if (LCD2_BACKLIGHT_CTRL == LCD_BACKLIGHT_BY_PWM)
#define GPIO_PWM_LCD2_BLG_PCTL      x
#define PWMID_LCD2_BLG_PCTL         PWMID_x
#elif (LCD2_BACKLIGHT_CTRL == LCD_BACKLIGHT_BY_GPIO)
#define GPIO_LCD2_BLG_PCTL          x_GPIO_x
#define PAD_LCD2_BLG_PCTL           PAD_PIN_xGPIOx
#endif

// TV
#define TV_DET_DUMMY                0
#define TV_DET_BY_VIO               1
#define TV_DET_BY_GPIO              2
#define TV_DET_BY_ADC               3
#define TV_DET_CTRL                 TV_DET_BY_GPIO //FPGA
#if (TV_DET_CTRL == TV_DET_BY_GPIO)
#define GPIO_TV_PLUG                P_GPIO_23//C_GPIO_x
#define PAD_TV_PLUG                 PAD_PIN_PGPIO23//PAD_PIN_CGPIOx
#endif
#if (TV_DET_CTRL == TV_DET_BY_ADC)
#define ADC_CH_TV_PLUG              ADC_CHANNEL_x
#endif

// HDMI
#define HDMI_DET_DUMMY              0
#define HDMI_DET_BY_VIO             1
#define HDMI_DET_BY_GPIO            2
#define HDMI_DET_BY_ADC             3
#define HDMI_DET_BY_HOTPLUG         4
#define HDMI_DET_CTRL               HDMI_DET_BY_VIO //EVB

// LCD2
#define LCD2_DET_DUMMY              0
#define LCD2_DET_BY_VIO             1
#define LCD2_DET_BY_GPIO            2
#define LCD2_DET_BY_ADC             3
#define LCD2_DET_CTRL               LCD2_DET_BY_VIO //EVB

// AIN
#define AIN_DET_DUMMY               0
#define AIN_DET_BY_VIO              1
#define AIN_DET_BY_GPIO             2
#define AIN_DET_CTRL                AIN_DET_BY_VIO //EVB
#if (AIN_DET_CTRL == AIN_DET_BY_GPIO)
#define GPIO_AIN_PLUG               C_GPIO_x
#define PAD_AIN_PLUG                PAD_PIN_CGPIOx
#endif

//--------------------------------------------------------------------
// Storage device
//--------------------------------------------------------------------
// CARD
// SD card power
#define GPIO_CARD_POWER             P_GPIO_17//3
#define PAD_CARD_POWER              PAD_PIN_PGPIO17//3
// SD card detect
#define GPIO_CARD_DETECT            P_GPIO_18
#define PAD_CARD_DETECT             PAD_PIN_PGPIO18
// SD card write protect (useless)
#define GPIO_CARD_WP                GPIO_NULL //P_GPIO_24
#define PAD_CARD_WP                 GPIO_NULL //PAD_PIN_PGPIO24

#define GPIO_CARD_WP_DET           P_GPIO_9         // Key Shutter2 (ks2)
#define PAD_CARD_WP_DET            PAD_PIN_PGPIO9

extern BOOL     SDIOCardUser_CheckCardInserted(void);
extern BOOL     SDIOCardUser_CheckCardWP(void);
#if defined(_EMBMEM_EMMC_)
extern BOOL     SDIO2CardUser_CheckCardInserted(void);
extern BOOL     SDIO2CardUser_CheckCardWP(void);
#endif

//--------------------------------------------------------------------
// Audio device
//--------------------------------------------------------------------
//Audio
extern BOOL     GPIOMap_DetAudio(void);


//--------------------------------------------------------------------
// Input device
//--------------------------------------------------------------------
// Key defined (650 FPGA KEYPAD)
//
// <Layout>
//--------------------------//   //--------------------------//
//  SW3   SW1   SW4   SW2   //   //  kzi   kzo   ks1   ks2   //
//                          //   //                          //
//           SW7            //   //           ku             //
//                          //   //                          //
//      SW5  SW6  SW8       //   //      kl   ke   kr        //
//                          //   //                          //
//           SW10           //   //           kd             //
//                          //   //                          //
//    SW12   SW11   SW9     //   //    km     kmd    kmp     //
//                          //   //                          //
//--------------------------//   //--------------------------//
//
// <Mapping>  SW1~SW12 = MC22~MC31,DCPIO4,5 = C_GPIO_22~31,DCPIO4,5 (Roy)
// <Active>   Low (Roy)
//
#define GPIO_KEY_ZOOMOUT            P_GPIO_20           // Key Zoom Out (kzo)
#define PAD_KEY_ZOOMOUT             PAD_PIN_CGPIO20
#define GPIO_KEY_SHUTTER2           P_GPIO_21           // Key Shutter2 (ks2)
#define PAD_KEY_SHUTTER2            PAD_PIN_CGPIO21
#define GPIO_KEY_ZOOMIN             P_GPIO_22           // Key Zoom In (kzi)
#define PAD_KEY_ZOOMIN              PAD_PIN_CGPIO22
#define GPIO_KEY_SHUTTER1           P_GPIO_23           // Key Shutter1 (ks1)
#define PAD_KEY_SHUTTER1            PAD_PIN_CGPIO23
#define GPIO_KEY_LEFT               P_GPIO_24           // Key Left (kl)
#define PAD_KEY_LEFT                PAD_PIN_CGPIO24
#define GPIO_KEY_ENTER              P_GPIO_25           // Key OK (ke)
#define PAD_KEY_ENTER               PAD_PIN_CGPIO25
#define GPIO_KEY_UP                 C_GPIO_27           // Key Up (ku)
#define PAD_KEY_UP                  PAD_PIN_CGPIO27
#define GPIO_KEY_RIGHT              C_GPIO_29           // Key Right (kr)
#define PAD_KEY_RIGHT               PAD_PIN_CGPIO29
#define GPIO_KEY_PLAYBACK           C_GPIO_30           // Key Playback (kmp)
#define PAD_KEY_PLAYBACK            PAD_PIN_CGPIO30
#define GPIO_KEY_DOWN               C_GPIO_31           // Key Down (kd)
#define PAD_KEY_DOWN                PAD_PIN_CGPIO31
#define GPIO_KEY_MODE               D_GPIO_4            // Key Mode (kmd)
#define PAD_KEY_MODE                PAD_PIN_DGPIO4
#define GPIO_KEY_MENU               D_GPIO_5            // Key Menu (km)
#define PAD_KEY_MENU                PAD_PIN_DGPIO5

//#define ADC_CH_VOLDET_MS1           ADC_CHANNEL_1
//#define ADC_CH_VOLDET_MS2           ADC_CHANNEL_0
#define ADC_CH_VOLDET_KEY1          ADC_CHANNEL_1
#define ADC_CH_VOLDET_KEY2          ADC_CHANNEL_2

//Touch panel controller

//#define GPIO_TP_BUSY                (2 | GPIO_IS_DGPIO)  //HW TS_INT =DGPIO-02
#define GPIO_TP_PENIRQ              (7 | GPIO_IS_DGPIO) //HW TS_PENIRQ =DGPIO-12
#define GPIO_TP_DOUT                P_GPIO_8 //P_GPIO_58 //HW TP_DI  =SBDAT0/AGPIO-26   (FW output = HW input)
#define GPIO_TP_DIN                 (1 | GPIO_IS_DGPIO) //HW TS_DO  =DGPIO-01  (FW input = HW output)
#define GPIO_TP_DCLK                P_GPIO_7//P_GPIO_57 //HW TS_CLK =SBCK0/AGPIO-25
//#define GPIO_TP_CS                  28 //HW TS_CS  =SBCS1/AGPIO-28  //SIF channel 1
#define GPIO_TP_CS                  P_GPIO_6//P_GPIO_56 //HW TS_CS  =SBCS0/AGPIO-27  //SIF channel 0
//#define PAD_TP_BUSY                 PAD_PIN_DGPIO2
#define PAD_TP_PENIRQ               PAD_PIN_DGPIO7
#define PAD_TP_DOUT                 PAD_PIN_PGPIO58
#define PAD_TP_DIN                  PAD_PIN_DGPIO1
#define PAD_TP_DCLK                 PAD_PIN_PGPIO57
//#define PAD_TP_CS                   PAD_PIN_SBCS1  //SIF channel 1
#define PAD_TP_CS                   PAD_PIN_PGPIO56  //SIF channel 0


//G-Sensor
/*
#define GPIO_GS_INT1                (3 | GPIO_IS_DGPIO)
#define GPIO_GS_INT2                (4 | GPIO_IS_DGPIO)
#define PAD_GS_INT1                 PAD_PIN_DGPIO3
#define PAD_GS_INT2                 PAD_PIN_DGPIO4
*/
//#define GPIO_GS_RST                 P_GPIO_1

extern UINT32   GPIOMap_DetKey(void);
extern UINT32   GPIOMap_DetModeDial(void);
extern BOOL     GPIOMap_DetShutter1(void);
extern BOOL     GPIOMap_DetMacro(void);
extern BOOL     GPIOMap_DetPoweroff(void);

//--------------------------------------------------------------------
// Output device
//--------------------------------------------------------------------
// LED
#define LED_RED_DUMMY               0
#define LED_RED_BY_GPIO             1
#define LED_RED_BY_MCU              3
#define LED_RED_CTRL                LED_RED_BY_GPIO
#define GPIO_RED_LED                P_GPIO_10
#define PAD_RED_LED                 PAD_PIN_PGPIO10


#define GPIO_POWER_LED              P_GPIO_10 //Yellow
#define GPIO_REC_LED                P_GPIO_12  //RED
#define GPIO_WIFI_LED               P_GPIO_2  //Blue

#define LED_BLUE_DUMMY               0
#define LED_BLUE_BY_GPIO             1
#define LED_BLUE_BY_MCU              3
#define LED_BLUE_CTRL                LED_RED_DUMMY
#define GPIO_BLUE_LED                P_GPIO_25  //FPGA  // WIFI LED
#define PAD_BLUE_LED                 PAD_PIN_PGPIO25




#define LED_GREEN_DUMMY             0
#define LED_GREEN_BY_GPIO           1
#define LED_GREEN_BY_MCU            3
#define LED_GREEN_CTRL              LED_GREEN_BY_GPIO
#define GPIO_GREEN_LED              P_GPIO_12
#define PAD_GREEN_LED               PAD_PIN_PGPIO12

#define LED_FOCUS_DUMMY             0
#define LED_FOCUS_BY_GPIO           1
#define LED_FOCUS_BY_PWM            2 //use PWM to control LED brightness
#define LED_FOCUS_BY_MCU            3

#define LED_FOCUS_CTRL              LED_FOCUS_DUMMY
#define GPIO_FOCUS_LED              P_GPIO_43
#define PAD_FOCUS_LED               PAD_PIN_PGPIO43
#define PWMID_FOCUS_LED             PWMID_7

#define LED_MOVIE_DUMMY             0
#define LED_MOVIE_BY_GPIO           1
#define LED_MOVIE_CTRL              LED_MOVIE_BY_GPIO
#define GPIO_MOVIE_LED              P_GPIO_12
#define PAD_MOVIE_LED               PAD_PIN_PGPIO12

#if defined(_MCU_ENABLE_)
#undef  LED_RED_CTRL
#define LED_RED_CTRL                LED_RED_BY_MCU

#undef  LED_GREEN_CTRL
#define LED_GREEN_CTRL              LED_GREEN_BY_MCU

#undef  LED_FOCUS_CTRL
#define LED_FOCUS_CTRL              LED_FOCUS_BY_MCU
#endif

//VOICE
#define GPIO_VOICE_BUSY_DET         GPIO_NULL//P_GPIO_8//5
#define PAD_VOICE_BUSY_DET          GPIO_NULL//PAD_PIN_PGPIO8//5
#define GPIO_VOICE_DATA             GPIO_NULL//P_GPIO_7
#define PAD_VOICE_DATA              GPIO_NULL//PAD_PIN_PGPIO7

#define GPIO_VOICE_PWR_ON           P_GPIO_8

//power amplifier module
#define GPIO_AMP_POWER              GPIO_NULL//P_GPIO_10//19
#define PAD_AMP_POWER               GPIO_NULL//PAD_PIN_PGPIO10//19

#define GPIO_AMP_SHDN               GPIO_NULL//P_GPIO_6
#define PAD_AMP_SHDN                GPIO_NULL//PAD_PIN_PGPIO6

//Edog onoff
#define GPIO_EDOG_CTL               GPIO_NULL//P_GPIO_9
#define PAD_EDOG_CTL                GPIO_NULL//PAD_PIN_PGPIO9


//--------------------------------------------------------------------
// Power device
//--------------------------------------------------------------------
//Battery
#define ADC_CH_VOLDET_BATTERY       ADC_CHANNEL_0
extern char    *VolDet_GetStatusString(void);



//--------------------------------------------------------------------
// Sensor device
//--------------------------------------------------------------------
// CCD
/*
typedef enum
{
    CCD_PWR_STATUS_OFF = 0,
    CCD_PWR_STATUS_ON,
    CCD_PWR_STATUS_SLEEP,
    CCD_PWR_STATUS_MAXIDX
}CCD_PWR_STATUS;
*/
/*
#define GPIO_CCDTG_VH               L_GPIO_20
#define GPIO_CCDTG_VL               L_GPIO_19
//#define GPIO_CCDTG_VH_2             50
#define GPIO_CCDTG_RST              C_GPIO_22
//#define GPIO_CCDTG_HDRV_EN          88
#define SIF_SENSOR_TG               SIF_CH2
#define SIF_SENSOR_AFE              SIF_CH3
*/
#if USE_EXTGPIO
#define GPIO_SENSOR_RESET			extio_getGpioPinNumber(IO_SENSOR_RESET)
#define GPIO_SENSOR_29VEN			extio_getGpioPinNumber(IO_SENSOR_28V)
#define GPIO_SENSOR_18VEN			extio_getGpioPinNumber(IO_SENSOR_18V)
#define GPIO_SENSOR_12VEN			extio_getGpioPinNumber(IO_SENSOR_12V)
#else
#define GPIO_SENSOR_RESET           S_GPIO_9
#define GPIO_SENSOR_29VEN           S_GPIO_4
#define GPIO_SENSOR_18VEN           S_GPIO_5
#define GPIO_SENSOR_12VEN           S_GPIO_6
#endif

#define GPIO_SENSOR2_RESET           GPIO_NULL//L_GPIO_12
#define GPIO_SENSOR2_PWR             GPIO_NULL//P_GPIO_9
#define GPIO_SENSOR2_12VEN           GPIO_NULL//L_GPIO_11
#define GPIO_SENSOR2_DET             GPIO_NULL//L_GPIO_13
#define GPIO_SENSOR2_IRQ             GPIO_NULL//L_GPIO_14


extern void     GPIOMap_TurnOnCCDPower(void);
extern void     GPIOMap_TurnOffCCDPower(void);
extern UINT8    GPIOMap_IsCCDPowerOn(void);
extern void     GPIOMap_SleepCCDPower(void);
extern void     GPIOMap_WakeUpCCDPower(void);

//--------------------------------------------------------------------
// NET
//--------------------------------------------------------------------
// WiFi
#if USE_EXTGPIO
#define GPIO_WIFI_REG_ON			extio_getGpioPinNumber(IO_WIFI_CS)// WiFi regulator on, high active
#define GPIO_WIFI_PWR_ON			extio_getGpioPinNumber(IO_WIFI_SHDN)// WiFi power on, high active
#else
#define GPIO_WIFI_REG_ON            P_GPIO_11//4 // WiFi regulator on, high active
#define GPIO_WIFI_PWR_ON            P_GPIO_0//2 // WiFi power on, high active
#endif

//GPS
#define GPIO_GPS_PWR_ON           D_GPIO_0

//ACC
#define GPIO_ACC_DET                P_GPIO_24
#define PAD_ACC_DET                 PAD_PIN_PGPIO24
extern UINT32 GPIOMap_AccSignalDetect(void);

//--------------------------------------------------------------------
// Storbe device
//--------------------------------------------------------------------
// STROBE
/*
#define GPIO_FLASH_CHARGE           C_GPIO_21
#define PAD_FL_CHARGE               PAD_PIN_CGPIO21
#define GPIO_FLASH_RDY              P_GPIO_12
#define PAD_FL_RDY                  PAD_PIN_PGPIO12
#define GPIO_FLASH_TRIGGER          D_GPIO_7
#define PAD_FL_TRIGGER              PAD_PIN_DGPIO7
*/

//--------------------------------------------------------------------
// Lens device
//--------------------------------------------------------------------
// BCS 2.7 ~ 12 mm lens + SANYO LV8044 motor IC
#define GPIO_LENS_RESET             0              // output

#define GPIO_LENS_ZOOM_INTR         0              // input
#define PAD_LENS_ZOOM_INTR          0

#define GPIO_LENS_FOCUS_INTR        0              // input
#define PAD_LENS_FOCUS_INTR         0

#define GPIO_LENS_IR_CTRL0          P_GPIO_12//6       // output
#define GPIO_LENS_IR_CTRL1          P_GPIO_12//7       // output
#define PAD_LENS_IR_CTRL0           PAD_PIN_PGPIO12//6
#define PAD_LENS_IR_CTRL1           PAD_PIN_PGPIO12//7



//MCU
//--------------------------------------------------------------------
// Notify  MCU  GPIO
//--------------------------------------------------------------------
#define GPIO_NOTIFY_MCU   P_GPIO_4

//notify gpio
#define GPIO_REC_MODE           P_GPIO_6

//--------------------------------------------------------------------
// Hold  power
//--------------------------------------------------------------------
#define GPIO_HOLD_DVR_POWER   P_GPIO_25

extern void GPIOMap_ToMcuSystemOK(BOOL Flag);
extern void GPIOMap_DVR_5V_Power_Ctrl(BOOL Flag);
extern void GPIOMap_RecordingModeOut(BOOL Flag);
//extern void GPIOMap_CapacityChargeEn(BOOL Flag);
extern BOOL GPIOMap_CardProtect_Det(void);
extern void GPIOMap_AmpPowerOn(void);
extern void GPIOMap_AmpPowerOff(void);
extern void GPIOMap_WifiOn_LED(void);
extern void GPIOMap_WifiOff_LED(void);
extern BOOL GPOIMap_GetWifiLED_Status(void);
extern void GPIOMap_AudioPowerOff(void);



#endif

//@}
