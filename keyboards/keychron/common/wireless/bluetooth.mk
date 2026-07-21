OPT_DEFS += -DKC_BLUETOOTH_ENABLE
OPT_DEFS += -DWIRELESS_CONFIG_ENABLE
OPT_DEFS += -DNO_USB_STARTUP_CHECK
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

INFO_RULES_MK = $(shell $(QMK_BIN) generate-rules-mk --quiet --escape --keyboard $(KEYBOARD) --output $(INTERMEDIATE_OUTPUT)/src/info_rules.mk)
include $(INFO_RULES_MK)

WIRELESS_DIR = $(TOP_DIR)/keyboards/keychron/common/wireless
SRC += \
     $(WIRELESS_DIR)/wireless.c \
     $(WIRELESS_DIR)/report_buffer.c \
     $(WIRELESS_DIR)/ckbt51.c \
     $(WIRELESS_DIR)/indicator.c \
     $(WIRELESS_DIR)/wireless_main.c \
     $(WIRELESS_DIR)/transport.c \
     $(WIRELESS_DIR)/lpm.c \
     $(WIRELESS_DIR)/battery.c \
     $(WIRELESS_DIR)/bat_level_animation.c \
     $(WIRELESS_DIR)/rtc_timer.c \
     $(WIRELESS_DIR)/keychron_wireless_common.c

ifeq ($(strip $(MCU)), STM32F401)
SRC += $(WIRELESS_DIR)/lpm_stm32f401.c
endif

ifeq ($(strip $(MCU)), STM32L432)
SRC += $(WIRELESS_DIR)/lpm_stm32l43x.c
endif

ifeq ($(strip $(MCU)), WB32F3G71)
SRC += $(WIRELESS_DIR)/lpm_wb32f3g71.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
OPT_DEFS += -DRGB_MATRIX_DRIVER_SHUTDOWN_ENABLE -DRGB_MATRIX_DRIVER_GET_TOTAL_DUTY_RATIO_ENABLE
OPT_DEFS += -DRGB_MATRIX_TIMEOUT=RGB_MATRIX_TIMEOUT_INFINITE
endif

ifeq ($(strip $(LED_MATRIX_ENABLE)), yes)
OPT_DEFS += -DLED_MATRIX_DRIVER_SHUTDOWN_ENABLE -DLED_MATRIX_DRIVER_GET_TOTAL_DUTY_RATIO_ENABLE
OPT_DEFS += -DLED_MATRIX_TIMEOUT=LED_MATRIX_TIMEOUT_INFINITE
endif

VPATH += $(WIRELESS_DIR)
