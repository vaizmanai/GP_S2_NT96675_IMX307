/*
    Display object object panel configuration parameters for ALT020DSLN

    @file       ALT020DSLN_J2.c
    @ingroup
    @note       Nothing

    Copyright   Novatek Microelectronics Corp. 2011.  All rights reserved.
*/

#include "debug.h"
#include "display.h"
#include "dispdev_IF8bits.h"
#include "dispdev_panlcomn.h"

#define IFCMD_CMD   0x01000000
#define IFCMD_DATA  0x02000000

/*
    Panel Parameters for ALT020DSLN
*/
//@{
#define LCD_TYPE_ALT_200  1
#define LCD_TYPE_ILI9342_231_GROUP1   2
#define LCD_TYPE_ILI9342_231_GROUP2   3
#define LCD_TYPE_ILI9342_C_HS_231   4
#define LCD_TYPE_ILI9342_C_TM_231   5
#define LCD_TYPE_ILI9342_FPC_FD231QA006 6
#define LCD_TYPE_ILI9342_FPC_FD234021000 7

#define LCD_TYPE_   LCD_TYPE_ILI9342_FPC_FD234021000//LCD_TYPE_ILI9342_C_HS_231//LCD_TYPE_ILI9342_C_TM_231

/*Used in RGB 960*/
const tPANEL_CMD tCmdModeRgbd320[] =
{
#if(LCD_TYPE_ == LCD_TYPE_ALT_200)///2.0' ALT 
        //---software reset----//
        {IFCMD_CMD, 0x01},
        {CMDDELAY_MS, 10},

        {IFCMD_CMD, 0xB9},
        {IFCMD_DATA,0xFF},
        {IFCMD_DATA,0x93},
        {IFCMD_DATA,0x42},

        {IFCMD_CMD, 0x21},
        {IFCMD_CMD, 0x36},
        {IFCMD_DATA,0xc8},

        {IFCMD_CMD, 0x3A},
        {IFCMD_DATA,0x55},

        {IFCMD_CMD, 0xB0},
        {IFCMD_DATA,0xE0},

        {IFCMD_CMD, 0xF6},
        {IFCMD_DATA,0x01},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x07},

        {IFCMD_CMD, 0xC0},
        {IFCMD_DATA,0x28},
        {IFCMD_DATA,0x0A},

        {IFCMD_CMD, 0xC1},
        {IFCMD_DATA,0x02},

        {IFCMD_CMD, 0xC5},
        {IFCMD_DATA,0x2F},
        {IFCMD_DATA,0x3A},

        {IFCMD_CMD, 0xC7},
        {IFCMD_DATA,0xC2},
        {IFCMD_DATA,0xB8},
        {IFCMD_DATA,0x0A},

        {IFCMD_CMD, 0xE0},
        {IFCMD_DATA,0x0F},
        {IFCMD_DATA,0x23},
        {IFCMD_DATA,0x20},
        {IFCMD_DATA,0x09},
        {IFCMD_DATA,0x0F},
        {IFCMD_DATA,0x07},
        {IFCMD_DATA,0x50},
        {IFCMD_DATA,0x76},
        {IFCMD_DATA,0x40},
        {IFCMD_DATA,0x0A},
        {IFCMD_DATA,0x15},
        {IFCMD_DATA,0x06},
        {IFCMD_DATA,0x11},
        {IFCMD_DATA,0x0E},
        {IFCMD_DATA,0x08},

        {IFCMD_CMD, 0xE1},
        {IFCMD_DATA,0x08},
        {IFCMD_DATA,0x1F},
        {IFCMD_DATA,0x21},
        {IFCMD_DATA,0x06},
        {IFCMD_DATA,0x0F},
        {IFCMD_DATA,0x03},
        {IFCMD_DATA,0x32},
        {IFCMD_DATA,0x23},
        {IFCMD_DATA,0x41},
        {IFCMD_DATA,0x01},
        {IFCMD_DATA,0x08},
        {IFCMD_DATA,0x08},
        {IFCMD_DATA,0x30},
        {IFCMD_DATA,0x33},
        {IFCMD_DATA,0x0F},


        {IFCMD_CMD, 0x11}, //Exit Sleep
        {CMDDELAY_MS, 10},

        {IFCMD_CMD, 0x11}, //Exit Sleep
        {CMDDELAY_MS, 80},

        {IFCMD_CMD, 0x29}, //Display ON
        {IFCMD_CMD, 0x2C}, //Display ON
#elif(LCD_TYPE_ == LCD_TYPE_ILI9342_231_GROUP1)//group one ruiyun 2.31 hight display LCD
	     	{CMDDELAY_MS, 10},
	     	{IFCMD_CMD, 0xB9},
	     	{IFCMD_DATA, 0xFF},
	     	{IFCMD_DATA, 0x93},
	     	{IFCMD_DATA, 0x42},
	     	{IFCMD_CMD, 0x21},
	     	{IFCMD_CMD, 0x36},
	     	{IFCMD_DATA, 0x08},
	     
	     	{IFCMD_CMD, 0xC0},
	     	{IFCMD_DATA, 0x1D},
	     	{IFCMD_DATA, 0x0A},
	     	
	     	{IFCMD_CMD, 0xC1},
	     	{IFCMD_DATA, 0x01},
	     
	     
	     
	     	{IFCMD_CMD, 0xC5},  
	     	{IFCMD_DATA, 0x2C}, 
	     	{IFCMD_DATA, 0x2C},   
	     
	     	{IFCMD_CMD, 0xC7}, 
	     	{IFCMD_DATA, 0Xc6},
	     
	     	{IFCMD_CMD, 0xB8},   
	     	{IFCMD_DATA, 0x09},   
	     
	     	{IFCMD_CMD, 0xE0},   
	     	{IFCMD_DATA, 0x0F},   
	     	{IFCMD_DATA, 0x26}, 
	     	{IFCMD_DATA, 0x21}, 
	     	{IFCMD_DATA, 0x07}, 
	     	{IFCMD_DATA, 0x0A}, 
	     	{IFCMD_DATA, 0x03},  
	     	{IFCMD_DATA, 0x4E},  
	     	{IFCMD_DATA, 0x62},  
	     	{IFCMD_DATA, 0x3E},  
	     	{IFCMD_DATA, 0x0B},  
	     	{IFCMD_DATA, 0x11},  
	     	{IFCMD_DATA, 0x00},  
	     	{IFCMD_DATA, 0x08}, 
	     	{IFCMD_DATA, 0x02},
	     	{IFCMD_DATA, 0x00},   
	     	{IFCMD_CMD, 0xE1},  
	     	{IFCMD_DATA, 0x00}, 
	     	{IFCMD_DATA, 0x19}, 
	     	{IFCMD_DATA, 0x1E},  
	     	{IFCMD_DATA, 0x03},  
	     	{IFCMD_DATA, 0x0E},  
	     	{IFCMD_DATA, 0x03},  
	     	{IFCMD_DATA, 0x30},  
	     	{IFCMD_DATA, 0x23}, 
	     	{IFCMD_DATA, 0x41},  
	     	{IFCMD_DATA, 0x03},  
	     	{IFCMD_DATA, 0x0B}, 
	     	{IFCMD_DATA, 0x07},  
	     	{IFCMD_DATA, 0x2F}, 
	     	{IFCMD_DATA, 0x36},  
	     	{IFCMD_DATA, 0x0F},
	     
	     	{IFCMD_CMD, 0x11},      //Exit Sleep 
	     	{CMDDELAY_MS, 10},
	     	{IFCMD_CMD, 0x11},     //Exit Sleep 
	     
	     	{CMDDELAY_MS, 80},
	     
	     	{IFCMD_CMD, 0xB0},  
	     	{IFCMD_DATA, 0xe0},
	     
	     	{IFCMD_CMD, 0x3A},   
	     	{IFCMD_DATA, 0x66},
	     	{IFCMD_CMD, 0xf6},  
	     	{IFCMD_DATA, 0x01},
	     	{IFCMD_DATA, 0x00},
	     	{IFCMD_DATA, 0x03},	
	     
	     
	     	{IFCMD_CMD, 0x29},    //Display ON 
	     	{CMDDELAY_MS, 180},
#elif (LCD_TYPE_ == LCD_TYPE_ILI9342_C_HS_231)// 

        {IFCMD_CMD,0xC8},
        {IFCMD_DATA,0xFF},
        {IFCMD_DATA,0x93},
        {IFCMD_DATA,0x42},
 
        //{IFCMD_CMD, 0x21},  
 
        {IFCMD_CMD, 0x36}, 
        {IFCMD_DATA,0xC8},
 
        {IFCMD_CMD, 0xC0},  
        {IFCMD_DATA,0x13},  
        {IFCMD_DATA,0x0E},   
        {IFCMD_CMD, 0xC1},  
        {IFCMD_DATA,0x02}, 
 
        {IFCMD_CMD, 0xC5},  
        {IFCMD_DATA,0xD3}, 

 
        {IFCMD_CMD, 0xC7},   
        {IFCMD_DATA,0Xc6},

        {IFCMD_CMD, 0xB1},
        {IFCMD_DATA,0x00},  
        {IFCMD_DATA,0x1B},

        {IFCMD_CMD, 0xB4},
        {IFCMD_DATA,0x02},

 
        {IFCMD_CMD, 0xB8},   
        {IFCMD_DATA,0x09},   
 

        {IFCMD_CMD, 0xE0},
        {IFCMD_DATA,0x00},//P01-VP63   
        {IFCMD_DATA,0x03},//P02-VP62   
        {IFCMD_DATA,0x08},//P03-VP61   
        {IFCMD_DATA,0x06},//P04-VP59   
        {IFCMD_DATA,0x13},//P05-VP57   
        {IFCMD_DATA,0x09},//P06-VP50   
        {IFCMD_DATA,0x39},//P07-VP43   
        {IFCMD_DATA,0x39},//P08-VP27,36
        {IFCMD_DATA,0x48},//P09-VP20   
        {IFCMD_DATA,0x02},//P10-VP13   
        {IFCMD_DATA,0x0A},//P11-VP6    
        {IFCMD_DATA,0x08},//P12-VP4    
        {IFCMD_DATA,0x17},//P13-VP2    
        {IFCMD_DATA,0x17},//P14-VP1    
        {IFCMD_DATA,0x0F},//P15-VP0    
  
        {IFCMD_CMD, 0xE1},
        {IFCMD_DATA,0x00},//P01
        {IFCMD_DATA,0x28},//P02
        {IFCMD_DATA,0x29},//P03
        {IFCMD_DATA,0x01},//P04
        {IFCMD_DATA,0x0D},//P05
        {IFCMD_DATA,0x03},//P06
        {IFCMD_DATA,0x3F},//P07
        {IFCMD_DATA,0x33},//P08
        {IFCMD_DATA,0x52},//P09
        {IFCMD_DATA,0x04},//P10
        {IFCMD_DATA,0x0F},//P11
        {IFCMD_DATA,0x0E},//P12
        {IFCMD_DATA,0x37},//P13
        {IFCMD_DATA,0x38},//P14
        {IFCMD_DATA,0x0F},//P15 
 
   
        {IFCMD_CMD, 0xB0},   
        {IFCMD_DATA,0xe0},

        {IFCMD_CMD, 0x3A},   
        {IFCMD_DATA,0x66},
        {IFCMD_CMD, 0xf6},   
        {IFCMD_DATA,0x01},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x07},	

         {IFCMD_CMD, 0x11},      //Exit Sleep 
        {CMDDELAY_MS, 10},
        {IFCMD_CMD, 0x11},      //Exit Sleep 
 
        {CMDDELAY_MS, 80},
        
        {IFCMD_CMD, 0x29},     //Display ON 
        {CMDDELAY_MS, 100}
#elif (LCD_TYPE_ == LCD_TYPE_ILI9342_C_TM_231)// 

        {IFCMD_CMD, 0x01},     //software reset  
        {CMDDELAY_MS, 20}, 

        {IFCMD_CMD, 0xC8},    
        {IFCMD_DATA,0xFF},  
        {IFCMD_DATA,0x93}, 
        {IFCMD_DATA,0x42},  
 
        {IFCMD_CMD, 0x36}, 
        {IFCMD_DATA,0xC8}, //   {IFCMD_DATA,0xC8},  
 
        {IFCMD_CMD, 0xC0},    
        {IFCMD_DATA,0x09}, //(0xFF);   
        {IFCMD_DATA,0x09},//(0xFF);   
        {IFCMD_CMD, 0xC1},   
        {IFCMD_DATA,0x01},//(0x01); 

        {IFCMD_CMD, 0xC5},   
        {IFCMD_DATA,0xe7},//(0xF7);  

 
        {IFCMD_CMD, 0xC7},   
//        {IFCMD_DATA,(0Xc6}, 
        {IFCMD_DATA,0x00}, 
        {IFCMD_DATA,0x02},

        {IFCMD_CMD, 0xB4},   
        {IFCMD_DATA,0x02},

 
        {IFCMD_CMD, 0xB8},   
        {IFCMD_DATA,0x00},   
 
        {IFCMD_CMD, 0xE0}, //Set Gamma 
        {IFCMD_DATA,0x00}, 
        {IFCMD_DATA,0x05}, 
        {IFCMD_DATA,0x08}, 
        {IFCMD_DATA,0x04}, 
        {IFCMD_DATA,0x13}, 
        {IFCMD_DATA,0x0a}, 
        {IFCMD_DATA,0x34}, 
        {IFCMD_DATA,0x8a}, 
        {IFCMD_DATA,0x46},
        {IFCMD_DATA,0x07}, 
        {IFCMD_DATA,0x0e}, 
        {IFCMD_DATA,0x0a}, 
        {IFCMD_DATA,0x1b}, 
        {IFCMD_DATA,0x1d}, 
        {IFCMD_DATA,0x0F},

        {IFCMD_CMD, 0XE1}, //Set Gamma 
        {IFCMD_DATA,0x00}, 
        {IFCMD_DATA,0x25}, 
        {IFCMD_DATA,0x27}, 
        {IFCMD_DATA,0x03}, 
        {IFCMD_DATA,0x0F},
        {IFCMD_DATA,0x06}, 
        {IFCMD_DATA,0x3C}, 
        {IFCMD_DATA,0x37}, 
        {IFCMD_DATA,0x4D}, 
        {IFCMD_DATA,0x05}, 
        {IFCMD_DATA,0x0E}, 
        {IFCMD_DATA,0x0B}, 
        {IFCMD_DATA,0x31}, 
        {IFCMD_DATA,0x34}, 
        {IFCMD_DATA,0x0F}, 
  
        {IFCMD_CMD, 0xB0},   
        {IFCMD_DATA,0xe0},

        {IFCMD_CMD, 0x3A},   
        {IFCMD_DATA,0x66},
        {IFCMD_CMD, 0xf6},   
        {IFCMD_DATA,0x01},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x07},	

        {IFCMD_CMD, 0x11},      //Exit Sleep 
        {CMDDELAY_MS, 80},
        {IFCMD_CMD, 0x11},      //Exit Sleep 
 
        {CMDDELAY_MS, 80},

 
        {IFCMD_CMD, 0x29},     //Display ON 
        {CMDDELAY_MS, 80}
#elif(LCD_TYPE_ == LCD_TYPE_ILI9342_FPC_FD231QA006)
		 {IFCMD_CMD, 0x01},
        {CMDDELAY_MS, 10},

        {IFCMD_CMD,0xC8},
        {IFCMD_DATA,0xFF},
        {IFCMD_DATA,0x93},
        {IFCMD_DATA,0x42},
 
        //{IFCMD_CMD, 0x21},  
 
        {IFCMD_CMD, 0x36}, 
        {IFCMD_DATA,0x08},//{IFCMD_DATA,0xC8},
 
        {IFCMD_CMD, 0xC0},  
        {IFCMD_DATA,0x09},//{IFCMD_DATA,0x13},  
        {IFCMD_DATA,0x09},//{IFCMD_DATA,0x0E},   
        {IFCMD_CMD, 0xC1},  
        {IFCMD_DATA,0x01},//{IFCMD_DATA,0x02}, 
 
        {IFCMD_CMD, 0xC5},  
        {IFCMD_DATA,0xE7},//{IFCMD_DATA,0xD3}, 

 
        {IFCMD_CMD, 0xC7},   
        {IFCMD_DATA,0Xc6},
        {IFCMD_DATA,0X00},
        {IFCMD_DATA,0X02},
/*
        {IFCMD_CMD, 0xB1},
        {IFCMD_DATA,0x00},  
        {IFCMD_DATA,0x1B},
*/
        {IFCMD_CMD, 0xB4},
        {IFCMD_DATA,0x02},

 
        {IFCMD_CMD, 0xB8},   
        {IFCMD_DATA,0x00},//{IFCMD_DATA,0x09},   
 

        {IFCMD_CMD, 0xE0},
        {IFCMD_DATA,0x00},//P01-VP63   
        {IFCMD_DATA,0x05},//P02-VP62   
        {IFCMD_DATA,0x08},//P03-VP61   
        {IFCMD_DATA,0x04},//P04-VP59   
        {IFCMD_DATA,0x13},//P05-VP57   
        {IFCMD_DATA,0x0A},//P06-VP50   
        {IFCMD_DATA,0x34},//P07-VP43   
        {IFCMD_DATA,0x8A},//P08-VP27,36
        {IFCMD_DATA,0x46},//P09-VP20   
        {IFCMD_DATA,0x07},//P10-VP13   
        {IFCMD_DATA,0x0E},//P11-VP6    
        {IFCMD_DATA,0x0A},//P12-VP4    
        {IFCMD_DATA,0x1B},//P13-VP2    
        {IFCMD_DATA,0x1D},//P14-VP1    
        {IFCMD_DATA,0x0F},//P15-VP0    
  
        {IFCMD_CMD, 0xE1},
        {IFCMD_DATA,0x00},//P01
        {IFCMD_DATA,0x25},//P02
        {IFCMD_DATA,0x27},//P03
        {IFCMD_DATA,0x03},//P04
        {IFCMD_DATA,0x0F},//P05
        {IFCMD_DATA,0x06},//P06
        {IFCMD_DATA,0x3C},//P07
        {IFCMD_DATA,0x37},//P08
        {IFCMD_DATA,0x4D},//P09
        {IFCMD_DATA,0x05},//P10
        {IFCMD_DATA,0x0E},//P11
        {IFCMD_DATA,0x0B},//P12
        {IFCMD_DATA,0x31},//P13
        {IFCMD_DATA,0x34},//P14
        {IFCMD_DATA,0x0F},//P15 
 
   
        {IFCMD_CMD, 0xB0},   
        {IFCMD_DATA,0xe0},

        {IFCMD_CMD, 0x3A},   
        {IFCMD_DATA,0x66},
        {IFCMD_CMD, 0xf6},   
        {IFCMD_DATA,0x01},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x07},	

         {IFCMD_CMD, 0x11},      //Exit Sleep 
        {CMDDELAY_MS, 10},
        {IFCMD_CMD, 0x11},      //Exit Sleep 
 
        {CMDDELAY_MS, 80},
        
        {IFCMD_CMD, 0x29},     //Display ON 
        {CMDDELAY_MS, 180}
#elif(LCD_TYPE_ == LCD_TYPE_ILI9342_FPC_FD234021000)
		 {IFCMD_CMD, 0x01},
        {CMDDELAY_MS, 10},

        {IFCMD_CMD,0xC8},
        {IFCMD_DATA,0xFF},
        {IFCMD_DATA,0x93},
        {IFCMD_DATA,0x42},
 
        //{IFCMD_CMD, 0x21},  
 
        {IFCMD_CMD, 0x36}, 
        {IFCMD_DATA,0x08},//{IFCMD_DATA,0xC8},

        {IFCMD_CMD, 0x3A}, 
        {IFCMD_DATA,0x55},//{IFCMD_DATA,0xC8},
        
        {IFCMD_CMD, 0xC0},  
        {IFCMD_DATA,0x13},//{IFCMD_DATA,0x13},  
        {IFCMD_DATA,0x0E},//{IFCMD_DATA,0x0E},   
        
        {IFCMD_CMD, 0xC1},  
        {IFCMD_DATA,0x02},//{IFCMD_DATA,0x02}, 
 
        {IFCMD_CMD, 0xC5},  
        {IFCMD_DATA,0xD3},//{IFCMD_DATA,0xD3}, 

         {IFCMD_CMD, 0xB0},  
        {IFCMD_DATA,0xE0},//{IFCMD_DATA,0xD3}, 
        
        {IFCMD_CMD, 0xB1},
        {IFCMD_DATA,0x00},  
        {IFCMD_DATA,0x1B},

        {IFCMD_CMD, 0xB4},
        {IFCMD_DATA,0x02},

 
        {IFCMD_CMD, 0xF6},   
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x07},
        
        {IFCMD_CMD, 0xE0},
        {IFCMD_DATA,0x00},//P01-VP63   
        {IFCMD_DATA,0x01},//P02-VP62   
        {IFCMD_DATA,0x04},//P03-VP61   
        {IFCMD_DATA,0x00},//P04-VP59   
        {IFCMD_DATA,0x11},//P05-VP57   
        {IFCMD_DATA,0x08},//P06-VP50   
        {IFCMD_DATA,0x35},//P07-VP43   
        {IFCMD_DATA,0x79},//P08-VP27,36
        {IFCMD_DATA,0x45},//P09-VP20   
        {IFCMD_DATA,0x07},//P10-VP13   
        {IFCMD_DATA,0x0D},//P11-VP6    
        {IFCMD_DATA,0x09},//P12-VP4    
        {IFCMD_DATA,0x16},//P13-VP2    
        {IFCMD_DATA,0x17},//P14-VP1    
        {IFCMD_DATA,0x0F},//P15-VP0    
  
        {IFCMD_CMD, 0xE1},
        {IFCMD_DATA,0x00},//P01
        {IFCMD_DATA,0x28},//P02
        {IFCMD_DATA,0x29},//P03
        {IFCMD_DATA,0x02},//P04
        {IFCMD_DATA,0x0F},//P05
        {IFCMD_DATA,0x06},//P06
        {IFCMD_DATA,0x3F},//P07
        {IFCMD_DATA,0x25},//P08
        {IFCMD_DATA,0x55},//P09
        {IFCMD_DATA,0x06},//P10
        {IFCMD_DATA,0x15},//P11
        {IFCMD_DATA,0x0F},//P12
        {IFCMD_DATA,0x38},//P13
        {IFCMD_DATA,0x38},//P14
        {IFCMD_DATA,0x0F},//P15 
        
		/*
        {IFCMD_CMD, 0x2A},  
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x01},
        {IFCMD_DATA,0x3F},

        {IFCMD_CMD, 0x2B},  
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x1F},
		*/

        {IFCMD_CMD, 0x11},      //Exit Sleep 
        {CMDDELAY_MS, 10},
        {IFCMD_CMD, 0x11},      //Exit Sleep 
 
        {CMDDELAY_MS, 10},
        
        {IFCMD_CMD, 0x29},     //Display ON 
        {CMDDELAY_MS,100},
        
			/*
        {IFCMD_CMD, 0x2A},  
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x01},
        {IFCMD_DATA,0x3F},

        {IFCMD_CMD, 0x2B},  
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x00},
        {IFCMD_DATA,0x1F},
		  */
		  
        //{IFCMD_CMD, 0x2C},  

		 {CMDDELAY_MS, 50},		
        
#else //group 2
	     	{CMDDELAY_MS, 10},
	     	{IFCMD_CMD, 0xB9},
	     	{IFCMD_DATA, 0xFF},
	     	{IFCMD_DATA, 0x93},
	     	{IFCMD_DATA, 0x42},
	     	{IFCMD_CMD, 0x21},
	     	{IFCMD_CMD, 0x36},
	     	{IFCMD_DATA, 0xC8},
	     
	     	{IFCMD_CMD, 0xC0},
	     	{IFCMD_DATA, 0x1D},
	     	{IFCMD_DATA, 0x0A},
	     	
	     	{IFCMD_CMD, 0xC1},   
	     	{IFCMD_DATA, 0x02},   			
	     	
	     	{IFCMD_CMD, 0xC5},   
	     	{IFCMD_DATA, 0x2F},   			
	     	{IFCMD_DATA, 0x27},
	     	
	     	{IFCMD_CMD, 0xC7},   
	     	{IFCMD_DATA, 0xA4},   	
	     	
	     	{IFCMD_CMD, 0xB8},   
	     	{IFCMD_DATA, 0x0B},  
	     	

	     	{IFCMD_CMD, 0xE0},   
	     	{IFCMD_DATA, 0x0F},   			
	     	{IFCMD_DATA, 0x24},
	     	{IFCMD_DATA, 0x21},   			
	     	{IFCMD_DATA, 0x0c},	     	
	     	{IFCMD_DATA, 0x0F},   			
	     	{IFCMD_DATA, 0x06},
	     	{IFCMD_DATA, 0x50},   			
	     	{IFCMD_DATA, 0x75},		     	
	     	{IFCMD_DATA, 0x3f},
	     	{IFCMD_DATA, 0x07},   			
	     	{IFCMD_DATA, 0x12},	     	
	     	{IFCMD_DATA, 0x05},   			
	     	{IFCMD_DATA, 0x11},
	     	{IFCMD_DATA, 0x0B},   			
	     	{IFCMD_DATA, 0x08},			

	     	{IFCMD_CMD, 0xE1},   
	     	{IFCMD_DATA, 0x08},   			
	     	{IFCMD_DATA, 0x1d},
	     	{IFCMD_DATA, 0x20},   			
	     	{IFCMD_DATA, 0x02},	     	
	     	{IFCMD_DATA, 0x0e},   			
	     	{IFCMD_DATA, 0x04},
	     	{IFCMD_DATA, 0x31},   			
	     	{IFCMD_DATA, 0x24},		     	
	     	{IFCMD_DATA, 0x42},
	     	{IFCMD_DATA, 0x03},   			
	     	{IFCMD_DATA, 0x0b},	     	
	     	{IFCMD_DATA, 0x09},   			
	     	{IFCMD_DATA, 0x30},
	     	{IFCMD_DATA, 0x36},   			
	     	{IFCMD_DATA, 0x0f},

	     	{IFCMD_CMD, 0xF2},   
	     	{IFCMD_DATA, 0x00}, 	

	     	{IFCMD_CMD, 0x11},      //Exit Sleep 
	     	{CMDDELAY_MS, 10},
	     	{IFCMD_CMD, 0x11},     //Exit Sleep 
	     
	     	{CMDDELAY_MS, 80},
	     
	     	{IFCMD_CMD, 0xB0},  
	     	{IFCMD_DATA, 0xe0},
	     
	     	{IFCMD_CMD, 0x3A},   
	     	{IFCMD_DATA, 0x66},
	     	{IFCMD_CMD, 0xf6},  
	     	{IFCMD_DATA, 0x01},
	     	{IFCMD_DATA, 0x00},
	     	{IFCMD_DATA, 0x03},	
	     	{IFCMD_CMD, 0x29},    //Display ON 
	     	{CMDDELAY_MS, 180},	     	
#endif 
};

const tPANEL_CMD tCmdStandby[] =
{
    {0x05, 0x5E}
};

const tLCD_PARAM tMode[] =
{
    /***********       RGB-SERIAL MODE         *************/
    {
        // tPANEL_PARAM
        {
            /* Old prototype */
            PINMUX_LCDMODE_RGB_THROUGH,//PINMUX_LCDMODE_RGB_SERIAL,      //!< LCDMode
            27.0f,//27.0f,                           //!< fDCLK
            1716,                            //!< uiHSyncTotalPeriod
            960,//960,                            //!< uiHSyncActivePeriod
            20,    //21                         //!< uiHSyncBackPorch
            268,  //246,                            //!< uiVSyncTotalPeriod
            240,                            //!< uiVSyncActivePeriod
            1,                             //!< uiVSyncBackPorchOdd
            1,                             //!< uiVSyncBackPorchEven
            320,//960,                            //!< uiBufferWidth
            240,                            //!< uiBufferHeight
            320,//960,                            //!< uiWindowWidth
            240,                            //!< uiWindowHeight
            FALSE,                          //!< bYCbCrFormat

            /* New added parameters */
            0x00,                           //!< uiHSyncSYNCwidth
            0x05                            //!< uiVSyncSYNCwidth
        },

        // tIDE_PARAM
        {
            /* Old prototype */
            PINMUX_LCD_SEL_SERIAL_RGB_8BITS,//!< pinmux_select_lcd;
            ICST_CCIR601,                   //!< icst;
            {FALSE,FALSE},                  //!< dithering[2];
            DISPLAY_DEVICE_TOPPOLY,         //!< **DONT-CARE**
            IDE_PDIR_RGB,                   //!< pdir;
            IDE_LCD_R,                      //!< odd;
            IDE_LCD_R,                      //!< even;
            TRUE,                           //!< hsinv;
            TRUE,                           //!< vsinv;
            FALSE,                          //!< hvldinv;
            FALSE,                          //!< vvldinv;
            TRUE,                           //!< clkinv;
            FALSE,                          //!< fieldinv;
            FALSE,                           //!< rgbdummy
            FALSE,                          //!< interlace;
            FALSE,                          //!< **DONT-CARE**
            0x40,                           //!< ctrst;
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
            {TRUE,TRUE,TRUE},               //!< subpixOdd[3]
            {FALSE,FALSE,FALSE},            //!< subpixEven[3]
            {IDE_DITHER_6BITS,IDE_DITHER_6BITS,IDE_DITHER_6BITS}//!< DitherBits[3]
        },

        (tPANEL_CMD*)tCmdModeRgbd320,                  //!< pCmdQueue
        sizeof(tCmdModeRgbd320)/sizeof(tPANEL_CMD),    //!< nCmd
    },
};

const tLCD_ROT *tRotate = NULL;

//@}

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

#if 1
void dispdev_writeToLcdSif(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32 value)
{
    UINT32                  uiSIFData;
    DISPDEV_IOCTRL_PARAM    DevIOCtrl;

    uiSIFData = ((((UINT32)addr << 8)|(UINT32)value) << 16);

    pDispDevControl(DISPDEV_IOCTRL_GET_REG_IF, &DevIOCtrl);
    //sif_send(DevIOCtrl.SEL.GET_REG_IF.uiSifCh, uiSIFData);
    sif_send(DevIOCtrl.SEL.GET_REG_IF.uiSifCh, uiSIFData, 0, 0);

}

void dispdev_writeToLcdGpio_Cmd(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32 value)
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

void dispdev_writeToLcdGpio_data(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32 value)
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
    //UINT32                  uiSIFData,j;
    //UINT32                  SifClk,SifSen,SifData;
    //DISPDEV_IOCTRL_PARAM    DevIOCtrl;

    if(addr & IFCMD_DATA)
        dispdev_writeToLcdGpio_data(pDispDevControl,addr,value);
    else
        dispdev_writeToLcdGpio_Cmd(pDispDevControl,addr,value);
}

void dispdev_readFromLcdGpio(DISPDEV_IOCTRL pDispDevControl, UINT32 addr, UINT32* p_value)
{
  //  debug_err(("Has not implement dispdev_readFromLcdGpio \r\n"));
}
#endif
