/*
    Display object object panel configuration parameters for TXDT270CDR_2V7

    @file       ILI9342C.c
    @ingroup
    @note       Nothing

    Copyright   Novatek Microelectronics Corp. 2011.  All rights reserved.
*/

#include "display.h"
#include "dispdev_IF8bits.h"
#include "dispdev_panlcomn.h"


#define IFCMD_CMD   0x01000000
#define IFCMD_DATA  0x02000000
const tPANEL_CMD tCmdStandby[] =
{

//  {MICMD_CMD,0x28}, //Display off
  {CMDDELAY_US, 1},
//  {MICMD_CMD,0x10}, //enter sleep mode
//  {MICMD_CMD,0x2c}, //memory write
};
const tPANEL_CMD tCmdModeRgbd320[] =
{
	#if	1
		{CMDDELAY_MS,120},                //ms

		{IFCMD_CMD,0x11},     //Sleep out

		{CMDDELAY_MS,120},                //Delay 120ms

		{IFCMD_CMD,0x36},     //Memory Data Access Control
		{IFCMD_DATA,0x00},  // MY MX MV ML RGB MH XX XX   14  00

		{IFCMD_CMD,0x21},     

		{IFCMD_CMD,0xB2},     
		{IFCMD_DATA,0x05},   
		{IFCMD_DATA,0x05},   
		{IFCMD_DATA,0x00},   
		{IFCMD_DATA,0x33},   
		{IFCMD_DATA,0x33},   

		{IFCMD_CMD,0xB7},     
		{IFCMD_DATA,0x77},   // 64

		{IFCMD_CMD,0xBB},     
		{IFCMD_DATA,0x20},   // 2A

		{IFCMD_CMD,0xC0},     
		{IFCMD_DATA,0x2C},   

		{IFCMD_CMD,0xC2},     
		{IFCMD_DATA,0x01},   

		{IFCMD_CMD,0xC3},     
		{IFCMD_DATA,0x13},   

		{IFCMD_CMD,0xC4},     
		{IFCMD_DATA,0x20},   

		{IFCMD_CMD,0xC6},     
		{IFCMD_DATA,0x11},   

		{IFCMD_CMD,0xD0},     
		{IFCMD_DATA,0xA7},   // A4
		{IFCMD_DATA,0xA1},   

		{IFCMD_CMD,0xD6},     
		{IFCMD_DATA,0xA1},

		{IFCMD_CMD,0xB0},     //影响RGB显示
		{IFCMD_DATA,0x11},  //11 
		{IFCMD_DATA,0xF4},  //CC

		{IFCMD_CMD,0xB1},  //影响RGB显示,如果显示方向不对，请调整这里  
		{IFCMD_DATA,0xEE},   
		{IFCMD_DATA,0x04}, //04 
		{IFCMD_DATA,0x14}, //15   

		{IFCMD_CMD,0xE0},
		{IFCMD_DATA,0xD0},
		{IFCMD_DATA,0x06},
		{IFCMD_DATA,0x06},
		{IFCMD_DATA,0x0E},
		{IFCMD_DATA,0x0D},
		{IFCMD_DATA,0x06},
		{IFCMD_DATA,0x2F},
		{IFCMD_DATA,0x3A},
		{IFCMD_DATA,0x47},
		{IFCMD_DATA,0x08},
		{IFCMD_DATA,0x15},
		{IFCMD_DATA,0x14},
		{IFCMD_DATA,0x2C},
		{IFCMD_DATA,0x33}, 

		{IFCMD_CMD,0xE1},
		{IFCMD_DATA,0xD0},
		{IFCMD_DATA,0x06},
		{IFCMD_DATA,0x06},
		{IFCMD_DATA,0x0E},
		{IFCMD_DATA,0x0D},
		{IFCMD_DATA,0x06},
		{IFCMD_DATA,0x2F},
		{IFCMD_DATA,0x3B},
		{IFCMD_DATA,0x47},
		{IFCMD_DATA,0x08},
		{IFCMD_DATA,0x15},
		{IFCMD_DATA,0x14},
		{IFCMD_DATA,0x2C},
		{IFCMD_DATA,0x33}, 



		{IFCMD_CMD,0x3A},     
		{IFCMD_DATA,0x06},   //06 ---->262K(RGB666},05---->65K   

		{IFCMD_CMD,0x29},     //Display on
		#elif	1
		{IFCMD_CMD,0x11},  
		
{CMDDELAY_MS,120},			   //ms
		
{IFCMD_CMD,0x36},	   //Memory Data Access Control
{IFCMD_DATA,0x00}, //flip 14   MY MX MV ML RGB MH XX XX 00

{IFCMD_CMD,0x21},   

{IFCMD_CMD,0x3A},	   
{IFCMD_DATA,0x06},  //06 ---->262K(RGB666},05---->65K(RGB565)
		
{IFCMD_CMD,0xB2},	   
{IFCMD_DATA,0x0C},  
{IFCMD_DATA,0x0C},  
{IFCMD_DATA,0x00},  
{IFCMD_DATA,0x33},  
{IFCMD_DATA,0x33},  
		
{IFCMD_CMD,0xB7},	   
{IFCMD_DATA,0x35},  
		
{IFCMD_CMD,0xBB},	   
{IFCMD_DATA,0x1D}, //vcom   
		
{IFCMD_CMD,0xC0},	   
{IFCMD_DATA,0x2C},  
		
{IFCMD_CMD,0xC2},	   
{IFCMD_DATA,0x01},  
		
{IFCMD_CMD,0xC3},	  //VRH--->值越大越暗，反之越白 
{IFCMD_DATA,0x02},  
		
{IFCMD_CMD,0xC4},	   
{IFCMD_DATA,0x20},  
		
{IFCMD_CMD,0xC6},	   
{IFCMD_DATA,0x0F}, //frame 
		
{IFCMD_CMD,0xD0},	   
{IFCMD_DATA,0xA7}, //内部代码
{IFCMD_DATA,0xA1},  
		
		
		
{IFCMD_CMD,0xB0},	   //影响RGB显示
{IFCMD_DATA,0x11}, //11 
{IFCMD_DATA,0xF4}, //CC
		
{IFCMD_CMD,0xB1},	//影响RGB显示,如果显示方向不对，请调整这里	
{IFCMD_DATA,0xEE},  
{IFCMD_DATA,0x04},//04 
{IFCMD_DATA,0x14},//15
		
		
{IFCMD_CMD,0xE0},	   //gamma
{IFCMD_DATA,0xD0},  
{IFCMD_DATA,0x00},  
{IFCMD_DATA,0x03},  
{IFCMD_DATA,0x09},  
{IFCMD_DATA,0x13},  
{IFCMD_DATA,0x1C},  
{IFCMD_DATA,0x3A},  
{IFCMD_DATA,0x55},  
{IFCMD_DATA,0x48},  
{IFCMD_DATA,0x18},  
{IFCMD_DATA,0x12},  
{IFCMD_DATA,0x0E},  
{IFCMD_DATA,0x20},  
{IFCMD_DATA,0x1E},  
		
{IFCMD_CMD,0xE1},	   //gamma
{IFCMD_DATA,0xD0},  
{IFCMD_DATA,0x00},  
{IFCMD_DATA,0x03},  
{IFCMD_DATA,0x09},  
{IFCMD_DATA,0x05},  
{IFCMD_DATA,0x25},  
{IFCMD_DATA,0x3A},  
{IFCMD_DATA,0x55},  
{IFCMD_DATA,0x50},  
{IFCMD_DATA,0x3D},  
{IFCMD_DATA,0x1C},  
{IFCMD_DATA,0x1D},  
{IFCMD_DATA,0x21},  
{IFCMD_DATA,0x1E},  
		
{IFCMD_CMD,0x29},	  

		#endif
};

const tLCD_PARAM tMode[] =
{
    /***********       RGB Dummy-320 MODE         *************/
    {
        // tPANEL_PARAM
        {
        #if	0
            PINMUX_LCDMODE_RGB_SERIAL,         //!< LCDMode
            6.25f, //24.00f,                        //!< fDCLK
           (0x3c+720),              //0x3C       //!< uiHSyncTotalPeriod
            720,//960,                            //!< uiHSyncActivePeriod
            0x3b,              // 0x3b             //!< uiHSyncBackPorch
            0x0a+320,                        //!< uiVSyncTotalPeriod
            320,                            //!< uiVSyncActivePeriod
            0x05,                           //!< uiVSyncBackPorchOdd
            0x05,                           //!< uiVSyncBackPorchEven
            720,                            //!< uiBufferWidth
            320,                            //!< uiBufferHeight
            720,                            //!< uiWindowWidth
            320,                            //!< uiWindowHeight
            FALSE,                          //!< bYCbCrFormat

            /* New added parameters */
            0x01,                           //!< uiHSyncSYNCwidth
            0x01                            //!< uiVSyncSYNCwidth
            #else
	     PINMUX_LCDMODE_RGB_THROUGH,         //!< LCDMode
           6.25f, //  6.8f, //24.00f,                        //!< fDCLK
           (0x3c+240),              //0x3C       //!< uiHSyncTotalPeriod
            240,//960,                            //!< uiHSyncActivePeriod
            0x17,              // 0x3b             //!< uiHSyncBackPorch
            0x0a+320,                        //!< uiVSyncTotalPeriod
            320,                            //!< uiVSyncActivePeriod
            0x05,                           //!< uiVSyncBackPorchOdd
            0x05,                           //!< uiVSyncBackPorchEven
            240,                            //!< uiBufferWidth
            320,                            //!< uiBufferHeight
            240,                            //!< uiWindowWidth
            320,                            //!< uiWindowHeight
            FALSE,                          //!< bYCbCrFormat

            /* New added parameters */
            0x01,                           //!< uiHSyncSYNCwidth
            0x01                            //!< uiVSyncSYNCwidth	
	    #endif

        },

        // tIDE_PARAM
        {
            /* Old prototype */
            PINMUX_LCD_SEL_SERIAL_RGB_6BITS,//!< pinmux_select_lcd;
            ICST_CCIR601,                   //!< icst;
            {FALSE,FALSE},                  //!< dithering[2];
            DISPLAY_DEVICE_CASIO2G,         //!< **DONT-CARE**
            IDE_PDIR_RGB,                   //!< pdir;
            IDE_LCD_R,                      //!< odd;
             IDE_LCD_R,                      //!< even;
            TRUE,                           //!< hsinv;
            TRUE,                           //!< vsinv;
            
            FALSE,                          //!< hvldinv;
            FALSE,                          //!< vvldinv;
            
            TRUE,                           //!< clkinv;
            TRUE,                          //!< fieldinv;
            
            FALSE,                          //!< **DONT-CARE**
            FALSE,                          //!< interlace;
            FALSE,                          //!< **DONT-CARE**
            0x3A,                           //!< ctrst;
            0x00,                           //!< brt;
            0x40,                           //!< cmults;
            FALSE,                          //!< cex;
            FALSE,                          //!< **DONT-CARE**
            TRUE,                           //!< **DONT-CARE**
            TRUE,                           //!< tv_powerdown;
            {0x00,0x00},                    //!< **DONT-CARE**

            /* New added parameters */
            FALSE,                          //!< YCex
            FALSE,                          //!< HLPF
            {FALSE,FALSE,FALSE},               //!< subpixOdd[3]
            {FALSE,FALSE,FALSE},            //!< subpixEven[3]
            {IDE_DITHER_6BITS,IDE_DITHER_6BITS,IDE_DITHER_6BITS}//!< DitherBits[3]
        },

        (tPANEL_CMD*)tCmdModeRgbd320,                  //!< pCmdQueue
        sizeof(tCmdModeRgbd320)/sizeof(tPANEL_CMD),    //!< nCmd
    }

};


#define ROTATE_PARA_COUNT 5
const tPANEL_CMD tCmdRotate_None[] =
{
 /*       {IFCMD_CMD, 0x11}, //Exit Sleep
        {IFCMD_CMD, 0x36},
        {IFCMD_DATA,0x08},//0xc8 for rotate
        {IFCMD_CMD, 0x29}, //Display ON
        {IFCMD_CMD,0x2c}, //memory write
        */
        {CMDDELAY_MS, 120},
};
const tPANEL_CMD tCmdRotate_180[] =
{
    /*    {IFCMD_CMD, 0x11}, //Exit Sleep
        {IFCMD_CMD, 0x36},
        {IFCMD_DATA,0xC8},//0xc8 for rotate
        {IFCMD_CMD, 0x29}, //Display ON
        {IFCMD_CMD,0x2c}, //memory write
        */
        {CMDDELAY_MS, 120},
};
const tLCD_ROT tRotate[] =
{
    {DISPDEV_LCD_ROTATE_NONE,(tPANEL_CMD*)tCmdRotate_None,ROTATE_PARA_COUNT},
    {DISPDEV_LCD_ROTATE_180,(tPANEL_CMD*)tCmdRotate_180,ROTATE_PARA_COUNT}
};

tLCD_ROT* dispdev_getLcdRotateCmd(UINT32 *ModeNumber)
{
    if(tRotate != NULL)
    {
        *ModeNumber = sizeof(tRotate)/sizeof(tLCD_ROT);
    }
    else
    {
        *ModeNumber = 0;
    }
    return (tLCD_ROT*)tRotate;
}

tLCD_PARAM* dispdev_getConfigMode(UINT32 *ModeNumber)
{
    *ModeNumber = sizeof(tMode)/sizeof(tLCD_PARAM);
    return (tLCD_PARAM*)tMode;
}

tPANEL_CMD* dispdev_getStandbyCmd(UINT32 *CmdNumber)
{
    *CmdNumber = sizeof(tCmdStandby)/sizeof(tPANEL_CMD);
    return (tPANEL_CMD*)tCmdStandby;
}

void dispdev_writeToLcdSif(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32 value)
{
    UINT32                  uiSIFData;
    DISPDEV_IOCTRL_PARAM    DevIOCtrl;

    uiSIFData = ((((UINT32)addr << 8)|((UINT32)value)) << 16);

    pDispDevControl(DISPDEV_IOCTRL_GET_REG_IF, &DevIOCtrl);
    sif_send(DevIOCtrl.SEL.GET_REG_IF.uiSifCh, uiSIFData, 0, 0);
}

static void dispdev_writeToLcdGpio_Cmd(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32 value)
{
    UINT32                  uiSIFData,j;
    UINT32                  SifClk,SifSen,SifData;
    DISPDEV_IOCTRL_PARAM    DevIOCtrl;


    pDispDevControl(DISPDEV_IOCTRL_GET_REG_IF, &DevIOCtrl);
    SifClk  = DevIOCtrl.SEL.GET_REG_IF.uiGpioClk;
    SifSen  = DevIOCtrl.SEL.GET_REG_IF.uiGpioSen;
    SifData = DevIOCtrl.SEL.GET_REG_IF.uiGpioData;

    gpio_setDir(SifSen, GPIO_DIR_OUTPUT);
    gpio_setDir(SifClk, GPIO_DIR_OUTPUT);
    gpio_setDir(SifData, GPIO_DIR_OUTPUT);

    gpio_setPin(SifSen);
    gpio_setPin(SifData);
    gpio_clearPin(SifClk);

    uiSIFData = (UINT32)value;

    Delay_DelayUs(500);

    gpio_clearPin(SifSen);
    for(j=9; j>0; j--)
    {
        if(((uiSIFData >> (j - 1)) & 0x01))
        {
            gpio_setPin(SifData);
        }
        else
        {
            gpio_clearPin(SifData);
        }

        Delay_DelayUs(100);
        gpio_setPin(SifClk);
        Delay_DelayUs(200);
        gpio_clearPin(SifClk);
        Delay_DelayUs(100);
    }
    Delay_DelayUs(500);
    gpio_setPin(SifSen);

}


static void dispdev_writeToLcdGpio_data(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32 value)
{
    UINT32                  uiSIFData,j;
    UINT32                  SifClk,SifSen,SifData;
    DISPDEV_IOCTRL_PARAM    DevIOCtrl;


    pDispDevControl(DISPDEV_IOCTRL_GET_REG_IF, &DevIOCtrl);
    SifClk  = DevIOCtrl.SEL.GET_REG_IF.uiGpioClk;
    SifSen  = DevIOCtrl.SEL.GET_REG_IF.uiGpioSen;
    SifData = DevIOCtrl.SEL.GET_REG_IF.uiGpioData;

    gpio_setDir(SifSen, GPIO_DIR_OUTPUT);
    gpio_setDir(SifClk, GPIO_DIR_OUTPUT);
    gpio_setDir(SifData, GPIO_DIR_OUTPUT);

    gpio_setPin(SifSen);
    gpio_setPin(SifData);
    gpio_clearPin(SifClk);

    uiSIFData = (UINT32)value;
    uiSIFData |= 0x100;

    Delay_DelayUs(500);

    gpio_clearPin(SifSen);

    for(j=9; j>0; j--)
    {
        if(((uiSIFData >> (j - 1)) & 0x01))
        {
            gpio_setPin(SifData);
        }
        else
        {
            gpio_clearPin(SifData);
        }

        Delay_DelayUs(100);
        gpio_setPin(SifClk);
        Delay_DelayUs(200);
        gpio_clearPin(SifClk);
        Delay_DelayUs(100);
    }
    Delay_DelayUs(500);
    gpio_setPin(SifSen);
}
void dispdev_writeToLcdGpio(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32 value)
{

    if(addr & IFCMD_DATA)
            dispdev_writeToLcdGpio_data(pDispDevControl,addr,value);
        else
            dispdev_writeToLcdGpio_Cmd(pDispDevControl,addr,value);
}

void dispdev_readFromLcdGpio(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32* p_value)
{
   // debug_err(("Has not implement dispdev_readFromLcdGpio \r\n"));
}

