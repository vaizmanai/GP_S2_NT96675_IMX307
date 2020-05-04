#ifndef _PRJCFG_DVCAM_H_
#define _PRJCFG_DVCAM_H_
#include "Type.h"
#include "SysKer.h"
//#include "SysInitWdt.h"
//==============================================================================
//   MODE and Major Feature (Maintain these in \Kernel, \System, \Mode folder)
//==============================================================================
#define PLAY_MODE                       ENABLE
#define PHOTO_MODE                      ENABLE//ENABLE
#define MOVIE_MODE                      ENABLE
#define USB_MODE                        ENABLE//ENABLE
#define SLEEP_MODE                      ENABLE
#define ENG_MODE                        ENABLE
#define IPCAM_MODE                      DISABLE
#define UPDFW_MODE                      ENABLE

#define IPCAM_FUNC                      DISABLE
#define STAMP_FUNC                      ENABLE
#define UI_FUNC                         ENABLE
#if !defined(_NVT_SDIO_WIFI_NONE_) || !defined(_NVT_USB_WIFI_NONE_)
#define WIFI_FUNC                       ENABLE
#else
#define WIFI_FUNC                       DISABLE
#endif
//==============================================================================
//   GENERAL CONFIG
//==============================================================================
//..............................................................................
#if defined(_FW_PARTIAL_LOAD_ON_)
#else
#endif

//..............................................................................
// FW version and name
#define FW_UPDATE_NAME                  "A:\\FW96680Z.bin"
#define FW_VERSION_RELEASE              DISABLE //ENABLE
#define FW_VERSION_NUM                  "PWR2_V02_20180611"

//..............................................................................
/**
     The definition of EmbMem is the storage without any card detection,
     which means the end-user cannot take that storage out. The EmbMem can also
     be a combination of partition such as partition 0 is spi-uITRON,
     partition 1 is ram-FAT these depend on what you designed on DxStorage_Mem.c
     Normally, in SPI case, we design the ram-disk as internal FAT

*/
// Internal Storage Mapping to DxStorage
#define USER_DX_TYPE_EMBMEM_LOADER      DX_TYPE_EMBMEM0 //STRG_OBJ_FW_RSV1
#define USER_DX_TYPE_EMBMEM_MODELEXT    DX_TYPE_EMBMEM1 //STRG_OBJ_FW_RSV2
#define USER_DX_TYPE_EMBMEM_UITRON      DX_TYPE_EMBMEM2 //STRG_OBJ_FW_RSV3
#define USER_DX_TYPE_EMBMEM_UBOOT       DX_TYPE_EMBMEM3 //STRG_OBJ_FW_RSV4
#define USER_DX_TYPE_EMBMEM_LINUX       DX_TYPE_EMBMEM4 //STRG_OBJ_FW_RSV5
#define USER_DX_TYPE_EMBMEM_ECOS        DX_TYPE_EMBMEM4 //STRG_OBJ_FW_RSV5
#define USER_DX_TYPE_EMBMEM_DSP         DX_TYPE_EMBMEM5 //STRG_OBJ_FW_RSV6
#define USER_DX_TYPE_EMBMEM_DSP2        DX_TYPE_EMBMEM6 //STRG_OBJ_FW_RSV7
#define USER_DX_TYPE_EMBMEM_PSTORE      DX_TYPE_EMBMEM7 //STRG_OBJ_PSTORE
#define USER_DX_TYPE_EMBMEM_FAT         DX_TYPE_EMBMEM8 //STRG_OBJ_FAT1


//==============================================================================
//   SYSTEM FUNCTIONS
//==============================================================================
//..............................................................................
// Boot
#define POWERON_PERF                    ENABLE  //enable performance benchmark
#define POWERON_TRACE                   DISABLE //stop and wait for user enter cmd: "dsc boot"
#define POWERON_FAST_BOOT               DISABLE
#define POWERON_FAST_CPU2_BOOT          ENABLE
#define POWERON_FAST_RECORD             ENABLE//DISABLE
#define POWERON_FAST_WIFI               ENABLE//NOTE: need to enable POWERON_FAST_CPU2_BOOT too
#define POWERON_WAIT_FS_READY           ENABLE
#define WAITPHOTO_FUNCTION              ENABLE
#define POWERONLOGO_FUNCTION            ENABLE
#define POWEROFFLOGO_FUNCTION           ENABLE //ENABLE

#define YQ_CONFIG_POWEROFFLOGO_SAME           ENABLE //DISABLE, ENABLE   //pgl add 20180529

#if ((POWERON_FAST_BOOT == ENABLE) || (POWERON_FAST_RECORD == ENABLE))
#define POWERONSOUND_FUNCTION           ENABLE
#else
#define POWERONSOUND_FUNCTION           ENABLE
#endif
#define POWEROFFSOUND_FUNCTION          ENABLE
#define _LOGO_                          _LOGO_NOVATEK_
#if (defined(_LCDTYPE_ILI9341_IF8B_) || \
     defined(_LCDTYPE_TG078UW006A0_DSI_)|| \
     defined(_LCDTYPE_UT35067A0_ILI9488_DSI_))
#define LOGO_DISP_LAYER                 LAYER_VDO1 // VDO2 logo has no rotation
#else
#define LOGO_DISP_LAYER                 LAYER_VDO2
#endif
#define LENSERROFF_FUNCTION             DISABLE

#if (POWERON_PERF == ENABLE)
#define TM_BOOT_ARRAY(n)                static TIMEMARK tmbuf[(n)] = {0}
#define TM_BOOT_INIT(n)                 TM_Init(tmbuf, n)
#define TM_BOOT_BEGIN(a,b)              TM_Begin(a,b)
#define TM_BOOT_END(a,b)                TM_End(a,b)
#else
#define TM_BOOT_ARRAY(n)
#define TM_BOOT_INIT(n)
#define TM_BOOT_BEGIN(a,b)
#define TM_BOOT_END(a,b)
#endif

//#NT#2016/07/12#Niven Cho -begin
//#NT#LINUX_LOAD_BY_UBOOT
//#NT#2016/07/12#Niven Cho -end

//..............................................................................
// External Card Config (for SDIO device)
#if !defined(_CARD1_NONE_)
#define CARD1_FUNC                  ENABLE
#else
#define CARD1_FUNC                  DISABLE
#endif

#if !defined(_CARD3_NONE_)
#define CARD3_FUNC                  ENABLE
#else
#define CARD3_FUNC                  DISABLE
#endif

//..............................................................................
// Storage Config
#define FWS_FUNC                        ENABLE  //enable it, if require load fw for start DSP or update fw for eCos

#define PST_FUNC                        ENABLE  //enable it, if require write pstore

#define FS_FUNC                         ENABLE  //enable it, if require write file

//#NT#2016/12/14#Niven Cho -begin
//#NT#EMMC_AS_PSTORE
// only for (_CPU2_TYPE_==_CPU2_LINUX_ && _INTERSTORAGE_ == _INTERSTORAGE_EMMC_)
#define PST_DEV_ID 4 //used for gxstrg to mount linux emmc-pstore partition
#define PST_FS_DRIVE "E:\\"
//#NT#2016/12/14#Niven Cho -end


#if defined(_DSP1_FREERTOS_)
#if (FWS_FUNC != ENABLE)
#warning Not enable FWS_FUNC for DSP?
#warning Please enable your "FWS_FUNC" config in header "PrjCfg_XXXX.h"
#error (see above)
#endif
#endif

//..............................................................................
// Input Config
#define INPUT_FUNC                      ENABLE
//key
#define POWERKEY_FUNCTION               ENABLE //Auto Detect
#define NORMALKEY_FUNCTION              DISABLE //Auto Detect
#define STATUSKEY_FUNCTION              DISABLE //Auto Detect
#define MODEKEY_FUNCTION                DISABLE //Auto Detect

//..............................................................................
// Output Config
#define OUTPUT_FUNC                     ENABLE
//LED
#define LED_FUNCTION                    ENABLE //Auto Detect

//..............................................................................
// Power-Saving Config
#define PWR_FUNC                        ENABLE
//battery level
#define PWRLEVEL_FUNCTION               ENABLE //ENABLE //Auto Detect
//auto power-off when battery level = empty
#define EMPTYPWROFF_FUNCTION            ENABLE //ENABLE
//auto sleep
#define AUTOSLEEP_FUNCTION              ENABLE //ENABLE //Auto Detect
//auto power-off
#define AUTOPWROFF_FUNCTION             ENABLE //ENABLE //Auto Detect

//..............................................................................
// Date-Time Config
#define DEF_YEAR                        2015
#define DEF_MONTH                       1
#define DEF_DAY                         1
#define MIN_YEAR                        2000
#define MAX_YEAR                        2050


//..............................................................................
// Sensor Config (for 1,2,4 devices)

#if ((!defined(_SENSOR1_CMOS_OFF_)) && (!defined(_SENSOR2_CMOS_OFF_)))
#define SENSOR_CAPS_COUNT               2
#define SENSOR_CAPS_MASK                (SENSOR_1 | SENSOR_2)
#else
#define SENSOR_CAPS_COUNT               1
#define SENSOR_CAPS_MASK                (SENSOR_1)
#endif

#define SENSOR_MAP_1                    SENSOR_ID_1
#define SENSOR_MAP_2                    SENSOR_ID_2


#define SENSOR_GP_FUNC                  DISABLE

// Sensor group
#define SENSOR_GP_1                     SENSOR_MULTI_ID_NONE /*ex: SENSOR_MULTI_ID_1|SENSOR_MULTI_ID_2*/
#define SENSOR_GP_2                     SENSOR_MULTI_ID_NONE /*ex: SENSOR_MULTI_ID_3|SENSOR_MULTI_ID_4*/
// Sensor sub group

#define SENSOR_SUBGP_1                  SENSOR_MULTI_ID_NONE
#define SENSOR_SUBGP_2                  SENSOR_MULTI_ID_NONE

// Sensor Insert Mask
//#define SENSOR_INSERT_MASK              (SENSOR_1) // support insert sensor
#if ((!defined(_SENSOR1_CMOS_OFF_)) && (!defined(_SENSOR2_CMOS_OFF_)))
#define SENSOR_INSERT_MASK              (SENSOR_2) // support insert sensor
#else
#define SENSOR_INSERT_MASK              (0) // if NOT support insert sensor, please choose this
#endif
#define SENSOR_DEFAULT_ATTACH_MASK      (SENSOR_CAPS_MASK & ~(SENSOR_INSERT_MASK)) // hw default attach sensors

#define SENSOR_INSERT_FUNCTION          ((SENSOR_CAPS_MASK == SENSOR_DEFAULT_ATTACH_MASK)?(DISABLE):(ENABLE)) //Auto Detect (Dynamic attach)

#define SENSOR_DEFAULT_DISPLAY_MASK     (SENSOR_1)
//..............................................................................
// Flashlight Config

#define FLASHLIGHT_FUNCTION             DISABLE //DISABLE


//..............................................................................
// Lens Config
#define LENS_FUNCTION                   DISABLE
#define LENS_FOCAL_LENGTH               2880    // unit:um


//..............................................................................
// Display Config (for LCD, LCD2, TV and HDMI device)

#define LCD2_FUNC_USERSTATUS            DISABLE //use LCD2 as status display. (not for video display)

//NOTE: LCD1 output from DOUT1 only
#if defined(_Disp_VIRTUAL_LCD1_OFF_)
#define LCD1_FUNC                       DISABLE
#define LCD1_MASK                       0x00
#else
#define LCD1_FUNC                       ENABLE
#define LCD1_MASK                       0x01
#endif
//NOTE: TV output from DOUT1 or DOUT2
#if defined(_TV_OFF_)
#define TV_FUNC                         DISABLE
#define TV_MASK                         0x00
#else
#define TV_FUNC                         ENABLE
#define TV_MASK                         0x02
#endif
//NOTE: HDMI output from DOUT1 or DOUT2
#if defined(_HDMI_OFF_)
#define HDMI_FUNC                       DISABLE
#define HDMI_MASK                       0x00
#else
#define HDMI_FUNC                       ENABLE
#define HDMI_MASK                       0x04
#endif
#if defined(_Disp_VIRTUAL_LCD2_OFF_)
#define LCD2_FUNC                       DISABLE
#define LCD2_MASK                       0x00
#else
#define LCD2_FUNC                       ENABLE
#define LCD2_MASK                       0x08
#endif

#define TEST_DUAL_DISP                  DISABLE

#if (TEST_DUAL_DISP)
#define DISPLAY_FUNC                    ENABLE
#define DISPLAY2_FUNC                   DISABLE
#define DISPLAY_CAPS_COUNT              1 //1: only single display, 2: allow single display or dual display
#define DISPLAY_CAPS_MASK               (LCD1_MASK|TV_MASK)//|HDMI_MASK|LCD2_MASK
#define DUALDISP_FUNC                   ((DISPLAY_CAPS_COUNT == 2)?ENABLE:DISABLE)

#define DISPLAY_DEFAULT_ATTACH_MASK     (DISPLAY_1) // hw default attach display//|DISPLAY_2

#if defined(_Disp_VIRTUAL_LCD1_OFF_)
#define DISPLAY_DEFAULT_ATTACH_DEVICE   TV_MASK //LCD1_MASK or HDMI_MASK or TV_MASK
#else
#define DISPLAY_DEFAULT_ATTACH_DEVICE   LCD1_MASK //LCD1_MASK or HDMI_MASK or TV_MASK
#endif
#define DISPLAY2_DEFAULT_ATTACH_DEVICE  HDMI_MASK //LCD2_MASK or TV_MASK or HDMI_MASK

//LCD related
#define LCD_AUTORESET_FUNCTION          DISABLE //Auto Reset - LCD register
#define LCD_AUTOBACKLIGHT_FUNCTION      DISABLE //Auto Adjust Backlight - with AE LV
#define LCD_ROTATE_FUNCTION             DISABLE //Auto Detect - LCD rotate (enable to support LCD body mirror or flip)
//TV related
#define TV_INSERT_FUNCTION              DISABLE //TV_FUNC //Auto Detect - TV cable insert
//HDMI related
#define HDMI_INSERT_FUNCTION            DISABLE //HDMI_FUNC //Auto Detect - HDMI cable insert
//LCD2 related
#define LCD2_INSERT_FUNCTION            DISABLE //LCD2_FUNC //Auto Detect - LCD2 cable insert

#else
#if((LCD1_FUNC == ENABLE) || (TV_FUNC == ENABLE) || (HDMI_FUNC == ENABLE) || (LCD2_FUNC == ENABLE))
#define DISPLAY_FUNC                    ENABLE
#define DISPLAY2_FUNC                   DISABLE
#define DISPLAY_CAPS_COUNT              1 //1: only single display, 2: allow single display or dual display
#define DISPLAY_CAPS_MASK               (LCD1_MASK|TV_MASK)//|HDMI_MASK|LCD2_MASK
#define DUALDISP_FUNC                   ((DISPLAY_CAPS_COUNT == 2)?ENABLE:DISABLE)

#define DISPLAY_DEFAULT_ATTACH_MASK     DISPLAY_1 // hw default attach display

#if defined(_Disp_VIRTUAL_LCD1_OFF_)
#define DISPLAY_DEFAULT_ATTACH_DEVICE   TV_MASK //LCD1_MASK or HDMI_MASK or TV_MASK
#else
#define DISPLAY_DEFAULT_ATTACH_DEVICE   LCD1_MASK //LCD1_MASK or HDMI_MASK or TV_MASK
#endif
#define DISPLAY2_DEFAULT_ATTACH_DEVICE  0 //LCD2_MASK or TV_MASK or HDMI_MASK

//LCD related
#define LCD_AUTORESET_FUNCTION          DISABLE //Auto Reset - LCD register
#define LCD_AUTOBACKLIGHT_FUNCTION      DISABLE //Auto Adjust Backlight - with AE LV
#define LCD_ROTATE_FUNCTION             DISABLE //Auto Detect - LCD rotate (enable to support LCD body mirror or flip)
//TV related
#define TV_INSERT_FUNCTION              TV_FUNC //Auto Detect - TV cable insert
//HDMI related
#define HDMI_INSERT_FUNCTION            HDMI_FUNC //Auto Detect - HDMI cable insert
//LCD2 related
#define LCD2_INSERT_FUNCTION            LCD2_FUNC //Auto Detect - LCD2 cable insert
#else
#define DISPLAY_FUNC                    DISABLE
#define DISPLAY2_FUNC                   DISABLE
#define DISPLAY_CAPS_COUNT              0
#define DISPLAY_CAPS_MASK               0
#define DUALDISP_FUNC                   0

#define DISPLAY_DEFAULT_ATTACH_MASK     0 // hw default attach display

#define DISPLAY2_DEFAULT_ATTACH_DEVICE  0 //LCD2_MASK or TV_MASK or HDMI_MASK

//LCD related
#define LCD_AUTORESET_FUNCTION          DISABLE //Auto Reset - LCD register
#define LCD_AUTOBACKLIGHT_FUNCTION      DISABLE //Auto Adjust Backlight - with AE LV
#define LCD_ROTATE_FUNCTION             DISABLE //Auto Detect - LCD rotate (enable to support LCD body mirror or flip)
//TV related
#define TV_INSERT_FUNCTION              TV_FUNC //Auto Detect - TV cable insert
//HDMI related
#define HDMI_INSERT_FUNCTION            HDMI_FUNC //Auto Detect - HDMI cable insert
//LCD2 related
#define LCD2_INSERT_FUNCTION            LCD2_FUNC //Auto Detect - LCD2 cable insert
#endif
#endif

// Display Config (for UI window, FD window)

// OSD size and format
#if defined(_Disp_IFPA_LCD1_PW27P106_ST7701_)
#define DISPLAY_OSD_W                   640//640
#define DISPLAY_OSD_H                   480
#else
#define DISPLAY_OSD_W                   320//640//640
#define DISPLAY_OSD_H                   240//480
#endif
#define DISPLAY_OSD_FMT                 DISP_PXLFMT_INDEX8 // 256 colors
//#define DISPLAY_OSD_FMT                 DISP_PXLFMT_RGBA5658_PK // 16bpp-colors

//UI tool layout size setting
#if defined(_Disp_IFPA_LCD1_PW27P106_ST7701_)
#define TOOL_LAYOUT_W                   640//640
#define TOOL_LAYOUT_H                   480//480
#else
#define TOOL_LAYOUT_W                   320//640//640
#define TOOL_LAYOUT_H                   240//480//480
#endif
#define OSD_USE_DOUBLE_BUFFER           ENABLE //use double buffer
#if (defined(_Disp_IF8B_LCD1_ILI9341_) || \
     defined(_Disp_IFPA_LCD1_PW27P106_ST7701_) || \
     defined(_Disp_IFPA_LCD1_ST7789V2_))
#define OSD_USE_ROTATE_BUFFER           ENABLE  //use rotate buffer (enable to support LCD with stripe-type subpixel)
#else
#define OSD_USE_ROTATE_BUFFER           DISABLE //use rotate buffer (enable to support LCD with stripe-type subpixel)
#endif

#define OSD2_FUNC                       DISABLE
#define OSD2_USE_DOUBLE_BUFFER          DISABLE //use double buffer


// Display Config (for UI background, App quickview, photo frame, ...)

// VDO size and format
#define DISPLAY_VDO_W                   640
#define DISPLAY_VDO_H                   480
#define DISPLAY_VDO_FMT                 DISP_PXLFMT_YUV422_PK

#define VDO_USE_DOUBLE_BUFFER           DISABLE //use double buffer
#define VDO2_USE_DOUBLE_BUFFER          DISABLE
#define VDO_USE_PHOTO_SOURCE            ENABLE  //display photo video streaming
#if (defined(_Disp_IF8B_LCD1_ILI9341_) || \
     defined(_Disp_IFPA_LCD1_PW27P106_ST7701_) || \
     defined(_Disp_IFPA_LCD1_ST7789V2_))
#define VDO_ROTATE_DIR                  ISF_VDO_DIR_ROTATE_270
#define VDO_USE_ROTATE_BUFFER           ENABLE  //use rotate buffer (enable to support LCD with stripe-type subpixel)
#undef  LOGO_DISP_LAYER
#define LOGO_DISP_LAYER                 LAYER_VDO1
#else
#define VDO_ROTATE_DIR                  ISF_VDO_DIR_ROTATE_0
#define VDO_USE_ROTATE_BUFFER           DISABLE //use rotate buffer (enable to support LCD with stripe-type subpixel)
#endif

#define VDO_USE_COPY_BUFFER             ENABLE //use copy buffer to avoid black between UI mode

#define VDO2_USE_ROTATE_BUFFER          DISABLE //use rotate buffer (enable to support LCD with stripe-type subpixel)

#if (DISPLAY2_FUNC == ENABLE)
//#define VDOOUT_MASK                   (DISPLAY_1) // app's video will output to which display
//#define VDOOUT_MASK                   (DISPLAY_2) // app's video will output to which display
#define VDOOUT_MASK                     (DISPLAY_1|DISPLAY_2) // app's video will output to which display
#else
#define VDOOUT_MASK                     (DISPLAY_1) // app's video will output to which display
#endif

#define LCD_PREVIEW_VDO_FMT             GX_IMAGE_PIXEL_FMT_YUV420_PACKED
#define LCD2_PREVIEW_VDO_FMT            GX_IMAGE_PIXEL_FMT_YUV420_PACKED
#define TV_PREVIEW_VDO_FMT              GX_IMAGE_PIXEL_FMT_YUV420_PACKED
#define HDMI_PREVIEW_VDO_FMT            GX_IMAGE_PIXEL_FMT_YUV420_PACKED

// Display Config (for DispSrv; Photo App, Movie App and Play App)
// VDO1 size and format (for LCD device)
//LCD1:
#if defined(_Disp_VIRTUAL_LCD1_OFF_)
#define LCDMODE                         DISABLE
#elif (defined(_Disp_IF8B_LCD1_AUCN01_) || defined(_Disp_IF8B_LCD1_TXDT270C_8961_6A6_R2_) || defined(_Disp_IF8B_LCD1_RZWT15P00_))
#define LCDMODE                         DISP_LCDMODE_RGBD320//PINMUX_LCDMODE_RGBD320 //PINMUX_LCDMODE_RGBD320//DISP_LCDMODE_RGBD320 //DISP_LCDMODE_YUV640
#elif defined(_Disp_IF8B_LCD1_PW35P00_HX8238D_) || \
      defined(_Disp_IF8B_LCD1_ILI9341_)
#define LCDMODE                         DISP_LCDMODE_RGB_SERIAL
#elif defined(_Disp_IF8B_LCD1_ILI9342C_)
#define LCDMODE                         DISP_LCDMODE_RGB_THROUGH
#elif defined(_Disp_IFPA_LCD1_PW27P106_ST7701_) || \
      defined(_Disp_IFPA_LCD1_ST7789V2_) || \
      defined(_Disp_IF8B_LCD1_T20P52_ILI9342C_)
#define LCDMODE                         DISP_LCDMODE_RGB_PARALL565
#else
#error "Unknown _LCD_"
#endif

#define LCD2MODE                        DISABLE

// VDO1 size and format (for TV device)
//TV: DISP_TVMODE_PAL mode
#define TVMODE                          DISP_TVMODE_NTSC

// VDO1 size and format (for HDMI device)
//HDMI: DISP_HDMIMODE_1920X1080I60 mode
//#define HDMIMODE                        DISP_HDMIMODE_1920X1080I60
#define HDMIMODE                        DISP_HDMIMODE_MAX


#define DUALCAM_PIP_BEHIND_FLIP         DISABLE  //Flip 2nd cam image in PIP view. Need extra 1/2 VDO buffer



//..............................................................................
// Audio Config
#define AUDIO_FUNC                      ENABLE
//..............................................................................
// External Audio Config (for LineOut device)

//LINE related

//..............................................................................
// External Storage Config
#define SDINSERT_FUNCTION               ENABLE //Auto Detect
#define SDHOTPLUG_FUNCTION              DISABLE

//#define MOVIE_ROOT_PATH         "A:\\CARDV\\"
#define PHPOTO_ROOT_PATH        "A:\\CARDV\\"

//..............................................................................
// FILEDB Config
#define USE_FILEDB                      ENABLE //DISABLE
#define FILEDB_CARDV_ROOT               "CARDV"   // the max length should not exceeds 16
// DCF Config
#define USE_DCF                         ENABLE
#define DCF_SUPPORT_FORMAT              (DCF_FILE_TYPE_JPG|DCF_FILE_TYPE_AVI|DCF_FILE_TYPE_MOV|DCF_FILE_TYPE_MP4)
//..............................................................................
// EXIF Config
#define USE_EXIF                        ENABLE
// End string must be '\0', total char must be 31
#define EXIF_MAKER_NAME                 "DvCam"
// End string must be '\0', total char must be 31
#define EXIF_MODEL_NAME                 "96680"
// End string must be '\0', total char must be 31
#define EXIF_IMAGE_DESCROPTOIN          "NOVATEK CAMERA"

#define EXIF_SOFTWARE_VERSION           FW_VERSION_NUM    // <= 20 char (TagSoftVerLen)

//..............................................................................
// Movie Maker/Model name Config
// End string must be '\0', total char must plus 1
#define MOVAPP_COMP_MANU_STRING         "NOVATEK"
// End string must be '\0', total char must plus 1
#define MOVAPP_COMP_NAME_STRING         "DEMO1"
//..............................................................................
// Usb Config

#define USBINSERT_FUNCTION              ENABLE //Auto Detect

#define USB_VID                         0x0603
#define USB_PID_PCCAM                   0x8612 // not support pc cam
#define USB_PID_WRITE                   0x8614
#define USB_PID_PRINT                   0x8613
#define USB_PID_MSDC                    0x8611

#define USB_PRODUCT_REVISION            '1', '.', '0', '0'
#define USB_VENDER_DESC_STRING          'N', 0x00,'O', 0x00,'V', 0x00,'A', 0x00,'T', 0x00,'E', 0x00,'K', 0x00, 0x20, 0x00,0x00, 0x00 // NULL
#define USB_VENDER_DESC_STRING_LEN      0x09
#define USB_PRODUCT_DESC_STRING         'D', 0x00,'E', 0x00,'M', 0x00,'O', 0x00,'1', 0x00, 0x20, 0x00, 0x00, 0x00 // NULL
#define USB_PRODUCT_DESC_STRING_LEN     0x07
#define USB_PRODUCT_STRING              'N','v','t','-','D','S','C'
#define USB_SIDC_DESC_STRING            'D', 0x00,'E', 0x00,'M', 0x00,'O', 0x00,'1', 0x00, 0x20, 0x00, 0x00, 0x00 // NULL
#define USB_SIDC_DESC_STRING_LEN        0x07
#define USB_MTP_FRIENDNAME_STRING       'D','E','M','O','1',0x00  //maximum length is 253 bytes
#define USB_MTP_FRIENDNAME_STRING_LEN   0x06                      //maximum length is 253 bytes
#define USB_VENDER_STRING               'N','O','V','A','T','E','K'
#define USB_VENDER_SIDC_DESC_STRING     'N', 0x00,'O', 0x00,'V', 0x00,'A', 0x00,'T', 0x00,'E', 0x00,'K', 0x00, 0x20, 0x00,0x00, 0x00 // NULL
#define USB_VENDER_SIDC_DESC_STRING_LEN 0x09
#define USB_SERIAL_NUM_STRING           '5', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0'

//..............................................................................
// Other Config

#define GSENSOR_FUNCTION                DISABLE  //G-sensor
#define GPS_FUNCTION                    DISABLE //DISABLE

#define SHOW_ADC_ON_SCREEN              DISABLE
#define CALIBRATION_FUNC                DISABLE  // Enable/Disable Calibration
#define WATERLOGO_FUNCTION              ENABLE  // Enable/Disable waterlogo function

// Important Notice:
//    If enable MULTILINGUAL_FUNCTION, remember to update font table and make sure the font height is not exceed the buffer size!!
#define MULTILINGUAL_FUNCTION           DISABLE  // Enable/Disable Multi-Lingual movie stamp function

#define TIMELAPSE_LPR_FUNCTION          DISABLE   // Enable/Disable Timelapse Low Power Record function

//---------------------------------------------------------------------------
// For Video Debug Info
//---------------------------------------------------------------------------
#define _MOVIE_IQLOG_                   DISABLE     // Enable/Disable Video IQLOG, Spark Chou

//==============================================================================
//   PLAYBACK FUNCTIONS
//==============================================================================
#define SLIDESHOW_MUSIC_OPTION          DISABLE //longer no maintain
// copy card to card function
#define COPYCARD2CARD_FUNCTION          DISABLE

//==============================================================================
//   PHOTO FUNCTIONS
//==============================================================================

#define ASSIST_BEAM_FUNC                DISABLE
#define GDC_FUNC                        DISABLE
#define AF_BEAM_EV_THRESHOLD            540
#define _FD_FUNC_                       DISABLE
#define _TSR_FUNC_                      DISABLE
#define MAX_FDNUM                       10
#define PIP_VIEW_FUNC                   DISABLE // PipView (ENABLE: display 2 sensor by PipView, DISABLE: display user selected sensor)
#define PIP_VIEW_FASTSWITCH             DISABLE // display single sensor method (ENABLE: always display by Pipview, DISABLE: display by direct path)
#define PIP_VIEW_LR                     DISABLE //(ENABLE: display 2 sensor by PipView in left, right view, side by side, DISABLE: normal pipview)

#define SBS_VIEW_FUNC                   DISABLE // SbsView (ENABLE: display 2 sensor by SbsView, DISABLE: display user selected sensor)
#define SHDR_FUNC                       DISABLE // ENABLE
#define WDR_FUNC                        ENABLE
#define DEFOG_FUNC                      DISABLE // ENABLE

#if !defined(_Gyro_None_)
#define RSC_FUNC                        DISABLE//ENABLE
#else
#define RSC_FUNC                        DISABLE
#endif
//..............................................................................
#define _SCREENNAIL_SIZE_               _SCREENNAIL_SIZE_VGA_
#define _QUICKVIEW_SIZE_                _QUICKVIEW_SIZE_SUIT_FOR_DISP

//..............................................................................
// Photo Frame Pstore Version Config
#define PF_PSTORE_VER                   0x00000105

//==============================================================================
//   MOVIE FUNCTIONS
//==============================================================================
#if !defined(_Gyro_None_)
#define MOVIE_RSC                       DISABLE//ENABLE
#else
#define MOVIE_RSC                       DISABLE
#endif
#define MOVIE_PIM_CAPTURE               DISABLE // picture in movie method 1 (capture full resolution image)
#define MOVIE_GDC_FUNC                  DISABLE
#define MOVIE_SMEAR_R_FUNC              DISABLE
#define MOVIE_ENSURE_SD_CLASS4          DISABLE
#define MOVIE_ENSURE_SD_32KCLUSTER      DISABLE
#define MOVIE_MULTI_RECORD_FUNC         ENABLE
#define MOVIE_REC_YUVMERGE              DISABLE // slowly timelapse record mode, frame period >= 1S
#define MOVIE_AUTOREC_ACPLUG            ENABLE
#define MOVIE_NET_USE_STREAM_1          DISABLE
#define MOVIE_UVAC_FUNC                 DISABLE
#define MOVIE_DSP_FUNC                  DISABLE

#define MOVIE_MAPPING_MULTIREC			ENABLE

#define MOVIE_DIS                       DISABLE
#define MOVIE_FD_FUNC_                  DISABLE
#define MOVIE_FD_DRAW_VIDEO             DISABLE
#define MOVIE_BC_FUNC                   DISABLE
#define MOVIE_TD_FUNC                   DISABLE // Depend on MOVIE_BC_FUNC
#define MOVIE_TD_DRAW_VIDEO             DISABLE
#define MOVIE_TWD_FUNC                  DISABLE // Depend on MOVIE_BC_FUNC
#define MOVIE_TWD_DRAW_VIDEO            DISABLE
#define MOVIE_TZD_FUNC                  DISABLE // Depend on MOVIE_BC_FUNC
#define MOVIE_TZD_DRAW_VIDEO            DISABLE
#define MOVIE_ODT_FUNC                  DISABLE
#define MOVIE_ODT_DRAW_VIDEO            DISABLE

#define UCTRL_APP_MOVIE_FEATURE_SETGET  DISABLE
#define MEDIA_VASTREAM                  DISABLE
#define IR_CUT_FUNC                     DISABLE
#define LOGFILE_FUNC                    DISABLE
#define _ADAS_FUNC_                     ENABLE//DISABLE
//..............................................................................
// ADAS subsetting (The following sub-functions are available only if _ADAS_FUNC_ = ENABLE
#define _AUTOVP_FUNC_                   ENABLE
#define _SNG_FUNC_                      DISABLE
#define _DRAW_LDFCINFO_ON_OSD_          ENABLE
#define _DRAW_SNG_ROI_                  DISABLE
#define _DRAW_LDWSINFO_ON_VIDEO_        DISABLE     // This function is only valid if data path is D2D!!

#define MOVIE_TSR_FUNC_                 DISABLE
#define MOVIE_TSR_DRAW_VIDEO            DISABLE
#define TSR_MODEL_IN_PSTORE             DISABLE

#define CROP_SOURCE_W                   3840
#define CROP_SOURCE_H                   2160

//==============================================================================
//   USER Custom FUNCTIONS
//==============================================================================
//#undef  LCD_AUTOBACKLIGHT_FUNCTION
//#define LCD_AUTOBACKLIGHT_FUNCTION      ENABLE //Auto Adjust Backlight - with AE LV

#define YI_CAR_CAM_FUNC                 ENABLE
#define YI_CAR_CAM_MENU                 ENABLE
#define YI_SOS_REC_FUNC                 ENABLE

#define ENCRYPTION_FUNC                 ENABLE
#define PMU_FUNC                        DISABLE
#define ABORTP_POWER_OFF                ENABLE  // The USB shutdown process re-USB, does not boot
//WIFI
//#MC#Do not display WiFi interface, direct display video interface.
#define MAC_APPEN_SSID_LEN              6 //max len 12
#define VIDEO_WIFI_MERGER               DISABLE
#if defined(VIDEO_WIFI_MERGER) && (VIDEO_WIFI_MERGER == ENABLE)
#define VIDEO_WIFI_MERGER_SENDEVENT(NVTEVT,args...) do{\
		if(SYS_SUBMODE_WIFI==System_GetState(SYS_STATE_CURRSUBMODE)) \
		{   extern VControl UIMenuWndWiFiMobileLinkOKCtrl; \
			Ux_SendEvent(&UIMenuWndWiFiMobileLinkOKCtrl,NVTEVT,##args); \
		} else Ux_PostEvent(NVTEVT,##args);\
	}while(0)
#else
#define VIDEO_WIFI_MERGER_SENDEVENT(NVTEVT,args...) do{}while(0)
#endif

//==============================================================================
//   MOVIE PLAY FUNCTIONS
//==============================================================================
#define MOVIE_PLAY_VIEW_FUNC            ENABLE // MoviePlayView


//==============================================================================
//   USBCAM FUNCTIONS
//==============================================================================
#define UVAC_MODE_2_PATH                DISABLE
#if (UVAC_MODE_2_PATH==ENABLE)
#undef MOVIE_MULTI_RECORD_FUNC
#define MOVIE_MULTI_RECORD_FUNC         ENABLE
#endif
//==============================================================================
//   USBCHARGE FUNCTIONS
//==============================================================================
#define USB_CHARGE_FUNCTION             DISABLE
#define USB_CHARGE_VERIFY               DISABLE

//==============================================================================
//   USBDISK FUNCTIONS
//==============================================================================

//==============================================================================
//   MSDCVENDOR_NVT, is required for PC tools to transmit commands and data via USB / NET
//==============================================================================
#define MSDCVENDOR_NVT                  ENABLE  //via USB, depend on USBINSERT_FUNCTION and _USB3_INT_CORE1_
#define MSDCVENDOR_UPDFW                DISABLE //enable it will cause disalbing MSDC and MTP/PTP/UAVC Mode, MSDCVENDOR_NVT must enable
#define MSDCVENDOR_IDENTITY_FILE        "A:\\MSDCNVT"
#if (defined(_MODEL_DVCAM1_EVB_) || defined(_MODEL_DVCAM2_EVB_))
#define MSDCVENDOR_NVT_EXAM             ENABLE  //only for novatek internal use
#else
#define MSDCVENDOR_NVT_EXAM             DISABLE //for customer, disable it to reduce memory
#endif
//==============================================================================
//   USBPRINT FUNCTIONS
//==============================================================================

//==============================================================================
//   USBPRINT FUNCTIONS
//==============================================================================

//==============================================================================
//   UI FUNCTIONS
//==============================================================================
//..............................................................................
// UI Resource Storage Config
#define _LANG_STORE_                    _INSIDECODE_
#define _JPG_STORE_                     _INSIDECODE_
#define SPECIAL_KEY_RESET_FUNC          DISABLE
#define EXTRA_MENU                      DISABLE

//==============================================================================
//   IPCam FUNCTION
//==============================================================================
//..............................................................................

///////FD param
#define IPCAM_FD_FUNC                   DISABLE
#define MAX_FDNUM                       10        //set face detection max face number
//////MD param
#define IPCAM_MD_FUNC                   DISABLE
//////VQA param
#define IPCAM_VQA_FUNC                  DISABLE

/////AUDIO param
#define IPCAM_AUDIO_IN_FUNC             DISABLE
#define IPCAM_AUDIO_OUT_FUNC            DISABLE
#define IPCAM_AEC_FUNC                  DISABLE
#define AUDIO_FUNC_AAC                  ENABLE


//==============================================================================
//   NET FUNCTIONS
//==============================================================================
#if (!defined(_NVT_SDIO_WIFI_NONE_) || !defined(_NVT_USB_WIFI_NONE_))
#define _NETWORK_DEVICE_
#define _NETWORK_ON_WIFI_
#endif
#if !defined(_NVT_USB_4G_NONE_)
#define _NETWORK_DEVICE_
#define _NETWORK_ON_4G_
#endif
#if !defined(_NVT_ETHERNET_NONE_)
#define _NETWORK_DEVICE_
#define _NETWORK_ON_ETH_
#endif

#define MAC_APPEN_SSID                  ENABLE
#define ACL_TIME                        15000 //minmum 15 sec
#define WIFI_APP_MANUFACTURER           "NVT"
#define WIFI_APP_MODLE                  "CarDV_WiFi"
#define ONVIF_PROFILE_S                 DISABLE  //Enable it to cause NO CARD DETECTED.
#define ECOS_POWER_OFF_FLOW             DISABLE

//#NT#2016/10/21#YongChang Qui -begin
//#NT#wifi modules on EVB can't be powered off by default
#define WIFI_POWER_OFF_FLOW             DISABLE //Enabled only if ECOS_POWER_OFF_FLOW == DISABLE and DrvWiFi_PowerOff() actually powers off wifi module
//#NT#2016/10/21#YongChang Qui -end

#define HFS_FUNC                        DISABLE

#define HTTP_LIVEVIEW_FUNC              DISABLE
#if (WIFI_FUNC==ENABLE)
#define WIFI_AP_FUNC                    ENABLE
#else
#define WIFI_AP_FUNC                    DISABLE
#endif
#define WIFI_FTP_FUNC                   DISABLE

#define HTTP_MJPG_W_4                   640
#define HTTP_MJPG_H_3                   480

#define HTTP_MJPG_W_16                  640
#define HTTP_MJPG_H_9                   360

#define AUTO_WIFI                       DISABLE

#define HTTP_LIVEVIEW                   1
#define RTSP_LIVEVIEW                   2
#define MOVIE_LIVEVIEW                  RTSP_LIVEVIEW

#if(WIFI_AP_FUNC==ENABLE)
#undef HTTP_LIVEVIEW_FUNC
#define HTTP_LIVEVIEW_FUNC              ENABLE
#define MOVIE_MULTI_RECORD_FUNC         ENABLE


#undef HTTP_MJPG_W_4
#undef HTTP_MJPG_H_3
#undef HTTP_MJPG_W_16
#undef HTTP_MJPG_H_9
#define HTTP_MJPG_W_4                   640
#define HTTP_MJPG_H_3                   480
#define HTTP_MJPG_W_16                  640
#define HTTP_MJPG_H_9                   360

#undef HFS_FUNC
#define HFS_FUNC                        ENABLE
#endif

#define WIFI_APP_MANUFACTURER           "NVT"
#define WIFI_APP_MODLE                  "CarDV_WiFi"
#define WIFI_APP_DOWNLOAD_URL           "http://115.29.201.46:8020/download/filedesc.xml"


#if defined(_CPU2_LINUX_)
#define UCTRL_FUNC                      ENABLE
#else
#define UCTRL_FUNC                      DISABLE
#endif
#define ONVIF_FUNC                      DISABLE  //CarDV-Linux is no using of ONVIF


#define WIFI_FINALCAM_APP_STYLE         DISABLE
#define WIFI_BG_COLOR                   14

#define WIFI_STA_RECONNECT_MAX_COUNT 5
#define WIFI_STA_RECONNECT_INTERVAL 300

#define YOUKU_SDK                       DISABLE
#define IOT_P2P_FUNC                    DISABLE
#define NETWORK_4G_MODULE               DISABLE

#if (YOUKU_SDK == ENABLE)
#define WIFI_MOVIE_FOLDER               "MOVIE_WIFI"
#define CUT_MOVIE_FOLDER                "MOVIE_CUT"
//the following two functions should be exclusive
#define SAVE_DUAL_STREAM_FUNC           ENABLE
#define CUT_MOVIE_FUNC                  DISABLE
#endif

#define MOVIE_OT_FUNC                   DISABLE
#define MOVIE_OT_DRAW_VIDEO             DISABLE



#define CURL_FUNC                       DISABLE

#define _DDD_FUNC_                      DISABLE
#define MOVIE_DDD_FUNC                  DISABLE
#define MOVIE_DDD_FD_FUNC               DISABLE
#define MOVIE_DDD_DRAW_VIDEO            DISABLE
#define MOVIE_DDD_SAVE_LOG              DISABLE
#define DDD_MODEL_IN_PSTORE             DISABLE

#define MOVIE_FTG_FUNC                  DISABLE
#define MOVIE_FTG_DRAW_VIDEO            DISABLE

//#NT#2017/04/28#KCHong -begin
//#NT# CNN Object detection
#define _OD_FUNC_                       DISABLE
//#NT#2017/04/28#KCHong -end

#define USERLOG_FUNC                    DISABLE


// fileSize align function
#define FILESIZE_ALIGN_FUNC             DISABLE
#define PHOTO_FILESIZE_ALIGN_VALUE      2*1024*1024   //  2MB
#define FS_ALIGN_RESERVED_SIZE          (2 * MOVIE_FILESIZE_ALIGN_VALUE)

// mount sd-2 as "B:\\"
// To mount sd-2 as "B:\\" please do the following steps
// 1. set .int_id_dst[CC_CORE_MIPS1].Bit.bInt_ID_SDIO2 to TRUE
// 2. enable FS_DX_TYPE_DRIVE_B as DX_TYPE_CARD2
// 3. enable FS_MULTI_STRG_FUNC
// 4. NETWORK = NETWORK_NONE (Both uITRON and eCos)
#define FS_MULTI_STRG_FUNC              ENABLE
//MULTI_DRIVE
#if defined(_EMBMEM_EMMC_) && (FS_MULTI_STRG_FUNC==DISABLE)
#define FS_DX_TYPE_DRIVE_A              USER_DX_TYPE_EMBMEM_FAT
#else
#define FS_DX_TYPE_DRIVE_A              DX_TYPE_CARD1
#endif
#define FS_DX_TYPE_DRIVE_B              USER_DX_TYPE_EMBMEM_FAT //FS_MULTI_STRG_FUNC must enable for FS_DX_TYPE_DRIVE_B

#define _3DNROUT_FUNC                   DISABLE

#define RTC_FUNC                        ENABLE

#define DISPLAY_FAST_SWITCH DISABLE //fast swicth display device
#define DISPLAY_OSD2_FMT DISP_PXLFMT_INDEX8 // 256 colors
#define SPK_MASK 0x01
#define LOUT_MASK 0x02
#define LINE_INSERT_FUNCTION DISABLE //Auto Detect - LINE cable insert (audio out)
#define USE_DPOF DISABLE
#define BT_FUNC DISABLE
#define ECOS_DBG_MSG_FORCE_UART1_DIRECT ENABLE
#define USOCKET_CLIENT DISABLE
#define MOVIE_DISDSP_FUNC DISABLE
#define WIFI_UI_VER_1_0 0
#define WIFI_UI_VER_2_0 1
#define WIFI_UI_FLOW_VER WIFI_UI_VER_1_0 //WIFI_UI_VER_2_0
#define LOG_DBGINFO_IN_GPS_SECTION ENABLE
#define MOVIE_TD_SAVE_LOG DISABLE
#define MOVIE_SCD_FUNC DISABLE
#define UVC_MULTIMEDIA_FUNC DISABLE
#define FORCE_UNPLUG_RTSP DISABLE
#define IQTOOL_FUNC DISABLE
#define GXGFX_ADVANCED_STRING_FUNC ENABLE
#define SMALL_CLONE_MOVIE DISABLE
#define CUSTOM_NAMING_RULE DISABLE
#define LINUX_CVHOST_FUNC DISABLE
#define AUDIO_PLAY_TEST DISABLE
#define FTG_SNAPSHOT_FUN DISABLE
#define FTG_MAX_SNAPSHOT_NUM 5
#define FTG_OVERRALL_MAX_BUF_SIZE 250*1024
#define FTG_FACE_MAX_BUF_SIZE 100*1024
#define FTG_MAX_SNAPSHOT_SIZE 1024*1024*25
#define FTG_MAX_FACE_PIC_NUM 3
#define RTSP_AUDIO_ENABLE ENABLE
#define AUDIO_CMD_UCTRL_ENABLE ENABLE
#define FACE_GRADE_TEST DISABLE
#define IPCAM_UVC_FUNC DISABLE
#define BOOT_RESET_MENU_INFO ENABLE
#define VIDEOSPRITEIPC DISABLE
#define IPCAM_FD_FUNC DISABLE
//#define IPCAM_DIS_FUNC DISABLE
#define IPCAM_DIS_MV_FUNC			DISABLE //Digital Image Stabilzier: calculate motion vector
#define IPCAM_DIS_COMP_FUNC			DISABLE //DIS compensation: if set IPCAM_DIS_COMP_FUNC = enable, it should set IPCAM_DIS_MV_FUNC = TRUE, too
#define HOT_PLUG_REMAIN_SIZE 0
#define _CVHOST_EX_                     DISABLE
#define _CVHOST_EX_ENDSP_               DISABLE
#define _NVTCV_EX_                      DISABLE
#define _NVTCV_EX_ENDSP_                DISABLE
#define MOVIE_MAX_CHANNEL               16
#define LINUX_MSDC DISABLE //ENABLE
#define STEREO_FUNC                     DISABLE
#define THUMB_STAMP_FUNC				DISABLE
#define STAMP_PRIVATE_POOL				ENABLE
#define VIDEOSPRITE_STAMP_FUNC          ENABLE
#define VDOENC_MULTI_TEMPORARY_LAYER 	ENABLE 	  	//Multi Temporary Layer
#define YUV_TV_RANGE 				    DISABLE  	//YUV color space in tv range
#define VIDEO_FUNC_MJPG            		ENABLE
#define VIDEO_FUNC_H264            		ENABLE
#define VIDEO_FUNC_H265            		ENABLE
#define STOP_REC_BK                     DISABLE//ENABLE
#define NMEDIAPLAY_FUNC                 ENABLE//DISABLE     // switch SMediaPlay and NMediaPlay flow, use NMediaPlay when ENABLE to be set.


#define YOUQING_COMMON_CHANGE DISABLE
#define DRIVER_REPORT_FUNC  DISABLE

#define YOUQING_USB_UNPLUG_POWER_OFF DISABLE

//pgl 20180529 add beg
#define YQ_CONFIG_SET_DEFAULT_DATETIME DISABLE
#if (YQ_CONFIG_SET_DEFAULT_DATETIME==ENABLE)
#define YQ_DEFAULT_DATETIME_YEAR        2018
#define YQ_DEFAULT_DATETIME_MONTH       6
#define YQ_DEFAULT_DATETIME_DAY         18
#define YQ_DEFAULT_DATETIME_HOUR        0
#define YQ_DEFAULT_DATETIME_MINUTE      0
#define YQ_DEFAULT_DATETIME_SEC      0
#endif
//pgl 20180529 add end

#define YQ_CONFIG_SYNC_DATETIME_AUTO DISABLE

#define YQ_CONFIG_SHOW_USER_GUIDE DISABLE //ENABLE


#define YQCONFIG_WIFI_CRASH_CMD

//#BS#2018/04/27#Drew Wu -begin
//#BS#Do not display WiFi interface, direct display video interface.
#ifndef VIDEO_WIFI_MERGER
#define VIDEO_WIFI_MERGER               DISABLE
#endif

#ifndef VIDEO_WIFI_MERGER_SENDEVENT
#define VIDEO_WIFI_MERGER_SENDEVENT(NVTEVT,args...) Ux_PostEvent(NVTEVT,##args)
#endif
//#BS#2018/04/27#Drew Wu -end

//pgl 20180529 add beg
#ifndef YQ_CONFIG_SET_DEFAULT_DATETIME
#define YQ_CONFIG_SET_DEFAULT_DATETIME DISABLE
#endif
//pgl 20180529 add end

//-----------------------------------------------------------------------
//user add new define here
//Delay power-off
#define DELAYPWROFF_FUNCTION            DISABLE //ENABLE //Delay Detect
#define PHOTO_MODE_CAP_YUV420_FUNC      ENABLE
#define ACC_DET_FUNC                    DISABLE //ENABLE// DISABLE

#define CAR_PROTECT_DET_FUNC                 ENABLE// ENABLE//ENABLE
#define UART_TO_MCU_FUNCTION                 ENABLE
#define FIRST_INSERT_CARD_REMIND_FORMAT_FUNC ENABLE
#define DISPLAY_CHANGE_AUTO_REC_FUNC         ENABLE
#define SET_SYSTEM_TIME_FUNC                 ENABLE
#define REC_SOUND_CLOSE_FUNC                 ENABLE
#define REMIND_FORMAT_CARD_FUNC              ENABLE
#define WIFI_AND_ADAS_OPEN_FUNC              ENABLE
#define CAR_NUMBER_STAMP_FUNC                ENABLE
#define CC_APP_FUNC                          ENABLE
//TEST SN:AI7DHH000151111811B1
#define DEFAULT_SERIAL_NUMBER		 "B9IR88000151111811B5"

#define CAR_NUMBER_STAMP_STR_EN            "AAAAAAAA" //lacyli add 2015-11-14
#define CAR_NUMBER_STAMP_STR_CH            "AAAAAA" //lacyli add 2015-11-14
#define MOVIE_MODE_D2D_FUNC    ENABLE

#define DEFAULT_SOUND_LANG_EN   DISABLE   //LANG_EN
#define DEFAULT_SOUND_LANG_SC   ENABLE    //LANG_SC


//-----------------------------------------------------------------------
#endif //_PRJCFG_DVCAM_H_
