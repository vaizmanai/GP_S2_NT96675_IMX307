
#ifndef _GSENSOR_DA380_H
#define _GSENSOR_DA380_H
#include "Type.h"
#include "IOInit.h"
#include "pad.h"
#include "top.h"
#include "gpio.h"
#include "adc.h"
#include "pwm.h"

// DA380 I2C Addr
#define DA380_I2C_WR_ADDR		0x4e
#define DA380_I2C_RD_ADDR		0x4f

// BMA254 Reg Table
#define CHIP_ID_REG				0x01
#if 0
#define SW_RST_REG				0x14
#define OUT_X_L_REG				0x02
#define OUT_X_H_REG				0x03
#define OUT_Y_L_REG				0x04
#define OUT_Y_H_REG				0x05
#define OUT_Z_L_REG				0x06
#define OUT_Z_H_REG				0x07
#define PMU_RANGE_REG			0x0F
#define PMU_BW_REG				0x10
#endif
// For CHIP_ID_REG
#define CHIP_ID					0x13

#define NSA_REG_SPI_I2C                    0x00
#define NSA_REG_ACC_X_LSB            0x02
#define NSA_REG_MOTION_FLAG	 0x09 
#define NSA_REG_G_RANGE                 0x0f
#define NSA_REG_POWERMODE_BW            0x11
#define NSA_REG_ODR_AXIS_DISABLE        0x10
#define NSA_REG_INT_PIN_CONFIG          0x20
#define NSA_REG_INT_LATCH               0x21
#define NSA_REG_ENGINEERING_MODE        0x7f
#define NSA_REG_SWAP_POLARITY           0x12
#define NSA_REG_INTERRUPT_SETTINGS1     0x16
#define NSA_REG_INTERRUPT_MAPPING1      0x19
#define NSA_REG_INTERRUPT_MAPPING3      0x1b
#define NSA_REG_ACTIVE_DURATION         0x27
#define NSA_REG_ACTIVE_THRESHOLD        0x28


#endif

