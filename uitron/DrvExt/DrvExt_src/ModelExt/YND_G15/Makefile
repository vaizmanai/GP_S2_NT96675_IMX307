include ../../../../Project/ProjectConfig.txt
include ../../../../Project/$(ACTIVE_PROJECT)/ModelConfig.txt
include ../../../../Project/$(ACTIVE_PROJECT)/ModelConfig_$(MODEL).txt
include ../../../../Project/$(ACTIVE_PROJECT)/MakeConfig.txt

#----------------------------------------------------------------------
# set the library name here
#----------------------------------------------------------------------
PRJ_NAME = MODELEXT_YND_G15

#----------------------------------------------------------------------
# add/delete source files here
#----------------------------------------------------------------------
ifeq ($(ACTIVE_PROJECT), $(filter $(ACTIVE_PROJECT),DemoKit TestKit))
SRC = \
    DxCfg.c \
    IntDirCfg.c \
    PinmuxCfg.c \
    IOCfg.c \
    DxStorage_Card.c \
    DxStorage_EmbMem.c \
    DxInput_Key.c \
    DxCamera_Lens.c \
    DxCamera_Sensor.c \
    DxDisplay_LCD.c \
    DxDisplay_TV.c \
    DxOutput_LED.c \
    DxCmd.c \
    DxUsb.c \
    DxWiFi.c \
    DxGSensor.c \
    DxGPS.c \
    PartitionInfo.c \
    DxSound_Audio.c \
    DxIPL.c \
    dx_ipl_cal.c \
    DxPower_Battery.c \
    DxPower_DC.c \
    DxPQs.c \
    DxMCU.c \
    MCUCtrlTsk.c \
    MCU2CtrlTsk.c \
    MCUCtrlID.c \
    MCU2CtrlID.c

SRC += \
    independant/modelext_info.c \
    independant/bin_info.c \
    independant/pinmux_cfg.c \
    independant/intdir_cfg.c \
    independant/emb_partition_info.c \
    independant/gpio_info.c \
    independant/dram_partition_info.c \
    independant/model_cfg.c

ASM =
endif
#----------------------------------------------------------------------
# set the include directory here
#----------------------------------------------------------------------
INC_DIR = . \
	../../../../Include \

#----------------------------------------------------------------------
# set the image output directory here
#----------------------------------------------------------------------
IMG_BASE_DIR = ../../../../ARC/Drv

#----------------------------------------------------------------------
# add additional C and assembly flags here
#----------------------------------------------------------------------
CFLAGS_D = $(C_DEFINE_EXT)

ASMFLAGS_D = \
	$(CHIP_PARAM_ASM) \
	$(DRAMSIZE_PARAM_ASM) \
	$(MODEL_PARAM_ASM)

CFLAGS_R = $(C_DEFINE_EXT)

ASMFLAGS_R = \
	$(CHIP_PARAM_ASM) \
	$(DRAMSIZE_PARAM_ASM) \
	$(MODEL_PARAM_ASM)

GCCFLAGS = $(C_DEFINE_EXT)

#----------------------------------------------------------------------
# include common parts of the makefile
#----------------------------------------------------------------------
MAKE_COMMON_DIR = ../../../../MakeCommon
include $(MAKE_COMMON_DIR)/OutputLib.txt
