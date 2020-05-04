#include "GSensor.h"
#include "GSensor_Combo.h"
#include "GSensor_DA380.h"
#include "SwTimer.h"
#include <stdlib.h>
#include "ErrorNo.h"
#include "Delay.h"

#define __MODULE__          GSensor_DA380
#define __DBGLVL__          2      // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*"    //*=All, [mark]=CustomClass
#include "DebugModule.h"

static BOOL GSensor_DA380_open(void);
static BOOL GSensor_DA380_close(void);
static BOOL GSensor_DA380_GetStatus(Gsensor_Data *GS_Data);
static BOOL GSensor_DA380_ParkingMode(void);
static BOOL GSensor_DA380_CrashMode(void);
static void GSensor_DA380_SetSensitivity(GSENSOR_SENSITIVITY GSensorSensitivity);
static void GSensor_DA380_GetAxisValue(INT32 *pX, INT32 *pY, INT32 *pZ);
static void DA380_ClearIntSts(void);


INT32 Gsensor_DA380_ClosePark(INT32 num);
UINT32 GSensor_DA380_ReadPowerOn(void);

INT32 DA380_RegMask_Write(UINT8 addr, UINT8 mask, UINT8 data);
int     i2c_read_byte_data( unsigned char addr, unsigned char *data);
int     i2c_write_byte_data( unsigned char addr, unsigned char data);
int     i2c_read_block_data( unsigned char base_addr, unsigned char count, unsigned char *data);
int mir3da_register_read( unsigned char addr, unsigned char *data);
int mir3da_register_write( unsigned char addr, unsigned char data);
int mir3da_register_read_continuously( unsigned char addr, unsigned char count, unsigned char *data);
int mir3da_register_mask_write(unsigned char addr, unsigned char mask, unsigned char data);
INT32 DA380_Read_XYZ(short *x, short *y, short *z);
void GSensor_DA380_PowerDown(INT8 sen);




static GSENSOR_OBJ g_GsensorDA380Obj = {
	GSensor_DA380_open,
	GSensor_DA380_close,
	GSensor_DA380_GetStatus,
	GSensor_DA380_ParkingMode,
	GSensor_DA380_CrashMode,
	GSensor_DA380_SetSensitivity,
	GSensor_DA380_GetAxisValue,
	DA380_ClearIntSts
};

PGSENSOR_OBJ GSensor_DA380_getGSensorObj(void)
{
    return &g_GsensorDA380Obj;
}

//********************************************************************************
//
//GSENSOR DA380
//
//********************************************************************************
//static INT32 GsXData = 0,OldGsXData = 0;
//static INT32 GsYData = 0,OldGsYData = 0;
//static INT32 GsZData = 0,OldGsZData = 0;
static BOOL  g_bGsensorOpened = FALSE;
static GSENSOR_SENSITIVITY g_GSensorSensitivity = GSENSOR_SENSITIVITY_OFF;
static GSENSOR_SENSITIVITY g_GSensorSensitivityParking = GSENSOR_SENSITIVITY_PARKING_OFF;


//**********************************************************************************
//
//
//**********************************************************************************
//static GSENSOR_INFO2 g_GsensorInfo;

#define abs(x) (((x) < 0) ? -(x) : (x))
INT32 DA380_RegMask_Write(UINT8 addr, UINT8 mask, UINT8 data)
{
	UINT8      tmp_data;

	tmp_data = GSensor_I2C_ReadReg(addr);
	tmp_data &= ~mask; 
	tmp_data |= data & mask;
	GSensor_I2C_WriteReg(addr, tmp_data);
	return 0;
}
#if 0
static UINT32 DA380Threshold=0xFFFFFFFF;
static UINT32 GSensor_GetSensitivityLevel(void)
{
	switch(g_GSensorSensitivity) {
	case GSENSOR_SENSITIVITY_OFF:
		DA380Threshold = 0xFFFFFFFF;
		break;
	case GSENSOR_SENSITIVITY_LOW:
		DA380Threshold = 1900;
		break;
	case GSENSOR_SENSITIVITY_MED:
		DA380Threshold = 1000;
		break;
	case GSENSOR_SENSITIVITY_HIGH:
		DA380Threshold = 300;
		break;
	default:
		DA380Threshold = 0xFFFFFFFF;
		break;
	}
	return DA380Threshold;
}
#endif

static void GSensor_OpenInterface(void)
{

}

static void GSensor_CloseInterface(void)
{

}

BOOL PowerOnByGsensor = FALSE;
static BOOL GSensor_Init(void)
{
	GSENSOR_INFO GsensorInfo;

	GsensorInfo.I2C_RegBytes = GSENSOR_I2C_REGISTER_1BYTE;
	GsensorInfo.I2C_PinMux = I2C_PINMUX_1ST;//I2C_PINMUX_3RD;
	GsensorInfo.I2C_BusClock = I2C_BUS_CLOCK_400KHZ;//I2C_BUS_CLOCK_200KHZ;//;
	// DA380 GSensor I2C slave addresses
	GsensorInfo.I2C_Slave_WAddr = DA380_I2C_WR_ADDR;
	GsensorInfo.I2C_Slave_RAddr = DA380_I2C_RD_ADDR;
	if (GSensor_I2C_Init(GsensorInfo) == TRUE) {

		//init
		#if 1
		if(GSensor_DA380_ReadPowerOn())
		{
			debug_msg("------system power on by gsensor-----\r\n");
			PowerOnByGsensor=TRUE;
			Gsensor_DA380_ClosePark(0);
		}
		#endif
		if(GSensor_I2C_ReadReg(CHIP_ID_REG) != CHIP_ID) {				/// Check Chip ID
			DBG_ERR("[GSensor] DA380 checked failed!!\r\n");
			GSensor_I2C_Exit();											/// If not matched, close I2C bus.
			return FALSE;
		}

		// Init GSensor IC here
		//GSensor_I2C_WriteReg(SW_RST_REG, SW_RST);						/// Soft reset
		//Delay_DelayMs(2);												/// Delay wake-Up Time (1.8 ms)
		//GSensor_I2C_WriteReg(PMU_RANGE_REG, PMU_RANGE_2G);				/// Set PMU_RANGE = +/- 2g
		//GSensor_I2C_WriteReg(PMU_BW_REG, PMU_BW_31_25);					/// Set PMU_BW = 31.25 Hz
		DA380_RegMask_Write(NSA_REG_SPI_I2C, 0x24, 0x24);

		Delay_DelayMs(5);

		DA380_RegMask_Write(NSA_REG_G_RANGE, 0xFF, 0x02);
		DA380_RegMask_Write(NSA_REG_POWERMODE_BW, 0xFF, 0x5E);
		DA380_RegMask_Write(NSA_REG_ODR_AXIS_DISABLE, 0xFF, 0x06);

		DA380_RegMask_Write(NSA_REG_INT_PIN_CONFIG, 0x0F, 0x05);//set int_pin level
		DA380_RegMask_Write(NSA_REG_INT_LATCH, 0x8F, 0x86);//clear latch and set latch mode

		DA380_RegMask_Write(NSA_REG_ENGINEERING_MODE, 0xFF, 0x83);
		DA380_RegMask_Write(NSA_REG_ENGINEERING_MODE, 0xFF, 0x69);
		DA380_RegMask_Write(NSA_REG_ENGINEERING_MODE, 0xFF, 0xBD);
		DA380_RegMask_Write(NSA_REG_SWAP_POLARITY, 0xFF, 0x00);

		return TRUE;
	} else {
		DBG_ERR("GSensor init failed!!\r\n");
		return FALSE;
	}
}


/*return value: 0: is ok    other: is failed*/
int     i2c_read_byte_data( unsigned char addr, unsigned char *data){
	*data =  (unsigned char)GSensor_I2C_ReadReg(addr);
	return 0;
}

/*return value: 0: is ok    other: is failed*/
int     i2c_write_byte_data( unsigned char addr, unsigned char data){
	GSensor_I2C_WriteReg(addr,data);
	return 0;
}

/*return value: 0: is count    other: is failed*/
int     i2c_read_block_data( unsigned char base_addr, unsigned char count, unsigned char *data){
	int i = 0;
		
	for(i = 0; i < count;i++)
	{
		*data =  (unsigned char)GSensor_I2C_ReadReg(base_addr+i);
               data ++;
	}	
		
	return count;
}

int mir3da_register_read( unsigned char addr, unsigned char *data){
    int     res = 0;

    res = i2c_read_byte_data(addr, data);
    if(res != 0) {
          return res;
    }	

    return res;
}

int mir3da_register_write( unsigned char addr, unsigned char data){
    int     res = 0;

    res = i2c_write_byte_data(addr, data);
    if(res != 0) {
         return res;
    }

    return res;
}

int mir3da_register_read_continuously( unsigned char addr, unsigned char count, unsigned char *data)
{
    int     res = 0;

    res = (count==i2c_read_block_data(addr, count, data)) ? 0 : 1;
    if(res != 0) {
         return res;
    }

    return res;
}

int mir3da_register_mask_write(unsigned char addr, unsigned char mask, unsigned char data){
    int     res = 0;
    unsigned char      tmp_data;

    res = mir3da_register_read(addr, &tmp_data);
    if(res) {
        return res;
    }

    tmp_data &= ~mask; 
    tmp_data |= data & mask;
    res = mir3da_register_write(addr, tmp_data);

    return res;
}

/*return value: 0: is ok    other: is failed*/
INT32 DA380_Read_XYZ(short *x, short *y, short *z)
{
	UINT8    tmp_data[6] = {0};
	#if 0
	for(i=0;i<6;i++)
	{
		tmp_data[0]=GSensor_I2C_ReadReg(NSA_REG_ACC_X_LSB+i);
	}
	#else
	if (mir3da_register_read_continuously(NSA_REG_ACC_X_LSB, 6, tmp_data) != 0) 
	{
        	return -1;
    	}
	#endif
	*x = ((short)(tmp_data[1] << 8 | tmp_data[0]))>> 4;
	*y = ((short)(tmp_data[3] << 8 | tmp_data[2]))>> 4;
	*z = ((short)(tmp_data[5] << 8 | tmp_data[4]))>> 4;
	return 0;
}

void GSensor_DA380_PowerDown(INT8 sen)
{
	int   res = 0;
	res = mir3da_register_write(NSA_REG_INTERRUPT_SETTINGS1,0x03);
	res = mir3da_register_write(NSA_REG_ACTIVE_DURATION,0x03 );
	res = mir3da_register_write(NSA_REG_ACTIVE_THRESHOLD,0x03 ); //0x30  0x20 //0x08 Í£³µ\u0152à¿Ø Åö×²ÁéÃô¶È --dch 
			
	switch(sen){

		case 0:
			res = mir3da_register_write(NSA_REG_INTERRUPT_MAPPING1,0x04 );
			break;

		case 1:
			res = mir3da_register_write(NSA_REG_INTERRUPT_MAPPING3,0x04 );
			break;
	}
}
UINT32 GSensor_DA380_ReadPowerOn(void)
{
	UINT8 data = 0;
	mir3da_register_read(NSA_REG_MOTION_FLAG,&data);
	if(data&0x04)
	{
		debug_msg("power on by DA380 interrupt\r\n");
		return 1;
	}
	return 0;
}

static BOOL GSensor_DA380_open(void)
{CHKPNT;
	if (g_bGsensorOpened == TRUE) {
		DBG_ERR("GSensor open already\r\n");
		return TRUE;
	}
	// open Gsensor interface
	GSensor_OpenInterface();
	// Gsensor init
	if(GSensor_Init()) {
		CHKPNT;
		g_bGsensorOpened = TRUE;
		DBG_DUMP("[GSensor] DA380 is opened OK!!\r\n");
		return TRUE;
	}
	return FALSE;
}

static BOOL GSensor_DA380_close(void)
{
	if (g_bGsensorOpened == FALSE) {
		DBG_ERR("I2C close already\r\n");
		return TRUE;
	}

	// close Gsensor interface
	GSensor_CloseInterface();

	GSensor_I2C_Exit();

	g_bGsensorOpened = FALSE;

	return TRUE;
}

//static int PrtCnt=0;
static short threhold[4] = {10000,1200,900,600};//{300,600,1200,10000};//value 10000
static BOOL GSensor_DA380_GetStatus(Gsensor_Data *GS_Data)
{
	static short prev_x = 0,prev_y = 0,prev_z = 0,Z_buf=0;
	static short Pprev_x = 0,Pprev_y = 0,Pprev_z = 0;
	short x = 0, y = 0, z = 0;
	static char b_is_first = 0;
	char is_collision = 0;
	
	INT32 level;
	
	if(DA380_Read_XYZ(&x,&y,&z))
		return -1;
		
	if(b_is_first == 0)
	{
		prev_x = x;
		prev_y = y;
		prev_z = z;
		Pprev_x = x;
		Pprev_y = y;
		Pprev_z = z;		
		b_is_first = 1;
	}
	level=3;
	#if 0
	PrtCnt++;
	if(PrtCnt>45)
	{
		PrtCnt=0;
		debug_msg("\r\n");
		debug_msg("x=%d,y=%x,z=%d\r\n",x,y,z);
		debug_msg("\r\n");
	}
	#endif
	level = g_GSensorSensitivity;
	//debug_msg("X=%d Y=%d Z=%d\r\n",x,y,z);
	if((abs(x - prev_x) > threhold[level])||(abs(y - prev_y) > threhold[level])||(abs(z - prev_z) > threhold[level]))
	{
		if((abs(z - prev_z) > threhold[level]))
		{
			Z_buf ++;
			if(Z_buf >=2)
			{
				is_collision = 1;
				debug_msg("----------DA380 Carsh------ -\r\n");
			}
		}
		else if((abs(x - prev_x) > threhold[level]))
		{
			Z_buf ++;
			if(Z_buf >=2)
			{
				is_collision = 1;
				debug_msg("----------DA380 Carsh------ -\r\n");
			}
		}
		else
		{
			is_collision = 1;
			debug_msg("----------DA380 Carsh------ -\r\n");
		}
	}
	else
	{
		Z_buf = 0;
	}
	//else
	//	is_collision = 0;
	Pprev_x = prev_x;
	Pprev_y = prev_y;
	Pprev_z = prev_z;	
	prev_x = x;
	prev_y = y;
	prev_z = z;
	return is_collision;
}

static BOOL GSensor_DA380_ParkingMode(void)
{
	UINT8 data = 0;
	data=GSensor_I2C_ReadReg(NSA_REG_MOTION_FLAG);
	debug_msg("DA380 Parking Mode on\r\n");
	GSensor_DA380_PowerDown(0);
	return 0;
}

static void DA380_ClearIntSts(void)
{
	// Since we didnot use interrupt mode here.
	return;
}

static BOOL GSensor_DA380_CrashMode(void)
{
	if (g_bGsensorOpened == FALSE)
		return FALSE;

	DBG_DUMP("[GSensor] DA380 Enter crash mode..\r\n");
	//GSensor_I2C_WriteReg(0x17, 0x00);	// disable high-g interrupt, x/y/z component
	GSensor_I2C_WriteReg(NSA_REG_INTERRUPT_SETTINGS1,0x03);
	GSensor_I2C_WriteReg(NSA_REG_ACTIVE_DURATION,0x03 );
	GSensor_I2C_WriteReg(NSA_REG_ACTIVE_THRESHOLD,0x02 );///µ÷¿ª»úÁéÃô¶È //change activate threhould 
	int sen=0;
	switch(sen)
	{
		case 0:
			GSensor_I2C_WriteReg(NSA_REG_INTERRUPT_MAPPING1,0x04 );
			break;
		case 1:
			GSensor_I2C_WriteReg(NSA_REG_INTERRUPT_MAPPING3,0x04 );
			break;
	}
    return TRUE;
}

static void GSensor_DA380_SetSensitivity(GSENSOR_SENSITIVITY GSensorSensitivity)
{
	if (GSensorSensitivity >= GSENSOR_SENSITIVITY_BEGIN && GSensorSensitivity <= GSENSOR_SENSITIVITY_END) {
		g_GSensorSensitivity = GSensorSensitivity;
	}
	if (GSensorSensitivity >= GSENSOR_SENSITIVITY_PARKING_BEGIN && GSensorSensitivity <= GSENSOR_SENSITIVITY_PARKING_END) {
		g_GSensorSensitivityParking = GSensorSensitivity;
	}
}

static void GSensor_DA380_GetAxisValue(INT32 *pX, INT32 *pY, INT32 *pZ)
{

	if (g_bGsensorOpened == FALSE)
		return;
#if 0
    g_X_Data_L = GSensor_I2C_ReadReg(OUT_X_L_REG);
    g_Y_Data_L = GSensor_I2C_ReadReg(OUT_Y_L_REG);
    g_Z_Data_L = GSensor_I2C_ReadReg(OUT_Z_L_REG);

    g_X_Data_H = GSensor_I2C_ReadReg(OUT_X_H_REG);
    g_Y_Data_H = GSensor_I2C_ReadReg(OUT_Y_H_REG);
    g_Z_Data_H = GSensor_I2C_ReadReg(OUT_Z_H_REG);

	GsXData = ((g_X_Data_L & 0xF0) >> 4) | ((g_X_Data_H & 0xFF) << 4);
	if (GsXData > 0x7FF)
		GsXData = (-1)*(0xFFF - GsXData);
	//GsXData = (GsXData*98*2)/(2048*10);

	GsYData = ((g_Y_Data_L & 0xF0) >> 4) | ((g_Y_Data_H & 0xFF) << 4);
	if (GsYData > 0x7FF)
		GsYData = (-1)*(0xFFF - GsYData);
	//GsYData = (GsYData*98*2)/(2048*10);

	GsZData = ((g_Z_Data_L & 0xF0) >> 4) | ((g_Z_Data_H & 0xFF) << 4);
	if (GsZData > 0x7FF)
		GsZData = (-1)*(0xFFF - GsZData);
	//GsZData = (GsZData*98*2)/(2048*10);

	*pX = GsXData;
	*pY = GsYData;
	*pZ = GsZData;
#endif	
}


INT32 Gsensor_DA380_ClosePark(INT32 num)
{
	int   res = 0;
	res = mir3da_register_write(NSA_REG_INTERRUPT_SETTINGS1,0x00 );
	switch(num){
		case 0:
			res = mir3da_register_write(NSA_REG_INTERRUPT_MAPPING1,0x00 );
			break;
		case 1:
			res = mir3da_register_write(NSA_REG_INTERRUPT_MAPPING3,0x00 );
			break;
	}
	return res;
}
