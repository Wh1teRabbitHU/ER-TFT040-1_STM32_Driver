##########################################################################################################################
# File automatically-generated by STM32forVSCode
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = STM32F446_Driver


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/main.c \
Core/Src/stm32f4xx_hal_msp.c \
Core/Src/stm32f4xx_it.c \
Core/Src/system_stm32f4xx.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c \
FATFS/App/fatfs.c \
FATFS/Target/bsp_driver_sd.c \
FATFS/Target/fatfs_platform.c \
FATFS/Target/sd_diskio.c \
LIBJPEG/App/libjpeg.c \
LIBJPEG/Target/jdata_conf.c \
Middlewares/Third_Party/FatFs/src/diskio.c \
Middlewares/Third_Party/FatFs/src/ff.c \
Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
Middlewares/Third_Party/FatFs/src/option/syscall.c \
Middlewares/Third_Party/LibJPEG/source/jaricom.c \
Middlewares/Third_Party/LibJPEG/source/jcapimin.c \
Middlewares/Third_Party/LibJPEG/source/jcapistd.c \
Middlewares/Third_Party/LibJPEG/source/jcarith.c \
Middlewares/Third_Party/LibJPEG/source/jccoefct.c \
Middlewares/Third_Party/LibJPEG/source/jccolor.c \
Middlewares/Third_Party/LibJPEG/source/jcdctmgr.c \
Middlewares/Third_Party/LibJPEG/source/jchuff.c \
Middlewares/Third_Party/LibJPEG/source/jcinit.c \
Middlewares/Third_Party/LibJPEG/source/jcmainct.c \
Middlewares/Third_Party/LibJPEG/source/jcmarker.c \
Middlewares/Third_Party/LibJPEG/source/jcmaster.c \
Middlewares/Third_Party/LibJPEG/source/jcomapi.c \
Middlewares/Third_Party/LibJPEG/source/jcparam.c \
Middlewares/Third_Party/LibJPEG/source/jcprepct.c \
Middlewares/Third_Party/LibJPEG/source/jcsample.c \
Middlewares/Third_Party/LibJPEG/source/jctrans.c \
Middlewares/Third_Party/LibJPEG/source/jdapimin.c \
Middlewares/Third_Party/LibJPEG/source/jdapistd.c \
Middlewares/Third_Party/LibJPEG/source/jdarith.c \
Middlewares/Third_Party/LibJPEG/source/jdatadst.c \
Middlewares/Third_Party/LibJPEG/source/jdatasrc.c \
Middlewares/Third_Party/LibJPEG/source/jdcoefct.c \
Middlewares/Third_Party/LibJPEG/source/jdcolor.c \
Middlewares/Third_Party/LibJPEG/source/jddctmgr.c \
Middlewares/Third_Party/LibJPEG/source/jdhuff.c \
Middlewares/Third_Party/LibJPEG/source/jdinput.c \
Middlewares/Third_Party/LibJPEG/source/jdmainct.c \
Middlewares/Third_Party/LibJPEG/source/jdmarker.c \
Middlewares/Third_Party/LibJPEG/source/jdmaster.c \
Middlewares/Third_Party/LibJPEG/source/jdmerge.c \
Middlewares/Third_Party/LibJPEG/source/jdpostct.c \
Middlewares/Third_Party/LibJPEG/source/jdsample.c \
Middlewares/Third_Party/LibJPEG/source/jdtrans.c \
Middlewares/Third_Party/LibJPEG/source/jerror.c \
Middlewares/Third_Party/LibJPEG/source/jfdctflt.c \
Middlewares/Third_Party/LibJPEG/source/jfdctfst.c \
Middlewares/Third_Party/LibJPEG/source/jfdctint.c \
Middlewares/Third_Party/LibJPEG/source/jidctflt.c \
Middlewares/Third_Party/LibJPEG/source/jidctfst.c \
Middlewares/Third_Party/LibJPEG/source/jidctint.c \
Middlewares/Third_Party/LibJPEG/source/jmemmgr.c \
Middlewares/Third_Party/LibJPEG/source/jmemnobs.c \
Middlewares/Third_Party/LibJPEG/source/jquant1.c \
Middlewares/Third_Party/LibJPEG/source/jquant2.c \
Middlewares/Third_Party/LibJPEG/source/jutils.c


CPP_SOURCES = \


# ASM sources
ASM_SOURCES =  \
startup_stm32f446xx.s



#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
POSTFIX = "
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
GCC_PATH="/Users/tom/Library/Application Support/Code/User/globalStorage/bmd.stm32-for-vscode/@xpack-dev-tools/arm-none-eabi-gcc/12.2.1-1.2.1/.content/bin
ifdef GCC_PATH
CXX = $(GCC_PATH)/$(PREFIX)g++$(POSTFIX)
CC = $(GCC_PATH)/$(PREFIX)gcc$(POSTFIX)
AS = $(GCC_PATH)/$(PREFIX)gcc$(POSTFIX) -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy$(POSTFIX)
SZ = $(GCC_PATH)/$(PREFIX)size$(POSTFIX)
else
CXX = $(PREFIX)g++
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DSTM32F446xx \
-DUSE_HAL_DRIVER


# CXX defines
CXX_DEFS =  \
-DSTM32F446xx \
-DUSE_HAL_DRIVER


# AS includes
AS_INCLUDES = \

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IFATFS/App \
-IFATFS/Target \
-ILIBJPEG/App \
-ILIBJPEG/Target \
-IMiddlewares/Third_Party/FatFs/src \
-IMiddlewares/Third_Party/LibJPEG/include



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CXXFLAGS = $(MCU) $(CXX_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -feliminate-unused-debug-types

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf -ggdb
CXXFLAGS += -g -gdwarf -ggdb
endif

# Add additional flags
CFLAGS += -Wall -fdata-sections -ffunction-sections 
ASFLAGS += -Wall -fdata-sections -ffunction-sections 
CXXFLAGS += 

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F446RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = \


# Additional LD Flags from config file
ADDITIONALLDFLAGS = -specs=nano.specs 

LDFLAGS = $(MCU) $(ADDITIONALLDFLAGS) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of cpp program objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

# list of C objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
# list of ASM program objects
UPPER_CASE_ASM_SOURCES = $(filter %.S,$(ASM_SOURCES))
LOWER_CASE_ASM_SOURCES = $(filter %.s,$(ASM_SOURCES))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(UPPER_CASE_ASM_SOURCES:.S=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(LOWER_CASE_ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp STM32Make.make | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cxx STM32Make.make | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cxx=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.c STM32Make.make | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s STM32Make.make | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S STM32Make.make | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) STM32Make.make
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# flash
#######################################
flash: $(BUILD_DIR)/$(TARGET).elf
	"/Users/tom/Library/Application Support/Code/User/globalStorage/bmd.stm32-for-vscode/@xpack-dev-tools/openocd/0.12.0-1.1/.content/bin/openocd" -f ./openocd.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

#######################################
# erase
#######################################
erase: $(BUILD_DIR)/$(TARGET).elf
	"/Users/tom/Library/Application Support/Code/User/globalStorage/bmd.stm32-for-vscode/@xpack-dev-tools/openocd/0.12.0-1.1/.content/bin/openocd" -f ./openocd.cfg -c "init; reset halt; stm32f4x mass_erase 0; exit"

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)

#######################################
# custom makefile rules
#######################################


	
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***