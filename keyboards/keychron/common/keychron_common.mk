OPT_DEFS += -DFACTORY_TEST_ENABLE -DAPDAPTIVE_NKRO_ENABLE

KEYCHRON_COMMON_DIR = common
SRC += \
    $(KEYCHRON_COMMON_DIR)/keychron_task.c \
    $(KEYCHRON_COMMON_DIR)/keychron_common.c \
    $(KEYCHRON_COMMON_DIR)/keychron_raw_hid.c \
    $(KEYCHRON_COMMON_DIR)/factory_test.c \
    $(KEYCHRON_COMMON_DIR)/eeconfig_kb.c \
    $(KEYCHRON_COMMON_DIR)/dfu_info.c

VPATH += $(TOP_DIR)/keyboards/keychron/$(KEYCHRON_COMMON_DIR)

INFO_RULES_MK = $(shell $(QMK_BIN) generate-rules-mk --quiet --escape --keyboard $(KEYBOARD) --output $(INTERMEDIATE_OUTPUT)/src/info_rules.mk)
include $(INFO_RULES_MK)

include $(TOP_DIR)/keyboards/keychron/$(KEYCHRON_COMMON_DIR)/language/language.mk

ifeq ($(strip $(DEBOUNCE_TYPE)), custom)
include $(TOP_DIR)/keyboards/keychron/$(KEYCHRON_COMMON_DIR)/debounce/debounce.mk
endif

ifeq ($(strip $(SNAP_CLICK_ENABLE)), yes)
include $(TOP_DIR)/keyboards/keychron/$(KEYCHRON_COMMON_DIR)/snap_click/snap_click.mk
endif

ifeq ($(strip $(KEYCHRON_RGB_ENABLE)), yes)
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
include $(TOP_DIR)/keyboards/keychron/$(KEYCHRON_COMMON_DIR)/rgb/rgb.mk
endif
endif
