#Include all the file needed for project
INC += -I $(HAL_DIR)/core/Include
INC += -I $(HAL_DIR)/peripherals/Include
INC += -I $(HAL_DIR)/utilities/Include

VPATH += $(HAL_DIR)/core/Source
VPATH += $(HAL_DIR)/peripherals/Source
VPATH += $(HAL_DIR)/utilities/Source

SOURCES += $(HAL_DIR)/core/Source/mik32_hal_scr1_timer.c

SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_adc.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_crc32.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_crypto.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_dac.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_dma.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_eeprom.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_gpio.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_i2c.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_irq.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_otp.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_pcc.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_rtc.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_spi.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_spifi.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_timer16.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_timer32.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_tsens.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_usart.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal_wdt.c
SOURCES += ./platform/mik32-hal/peripherals/Source/mik32_hal.c

SOURCES += ./platform/mik32-hal/utilities/Source/mik32_hal_spifi_w25.c
SOURCES += ./platform/mik32-hal/utilities/Source/mik32_hal_ssd1306.c
####################################################################

INC += -I $(SHARED_DIR)/include
INC += -I $(SHARED_DIR)/libs
INC += -I $(SHARED_DIR)/periphery

VPATH += $(SHARED_DIR)/runtime
VPATH += $(SHARED_DIR)/libs

SOURCES += $(SHARED_DIR)/libs/dma_lib.c
SOURCES += $(SHARED_DIR)/libs/rtc_lib.c
SOURCES += $(SHARED_DIR)/libs/spi_lib.c
SOURCES += $(SHARED_DIR)/libs/uart_lib.c
SOURCES += $(SHARED_DIR)/libs/xprintf.c


SOURCES_ASM += $(SHARED_DIR)/runtime/crt0.S

LDFILE 		= $(SHARED_DIR)/ldscripts/spifi.lds
#LDFILE 		= $(SHARED_DIR)/ldscripts/eeprom.lds
#LDFILE 		= $(SHARED_DIR)/ldscripts/ram.lds















