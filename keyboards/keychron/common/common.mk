COMMON_DIR = common
SRC += $(COMMON_DIR)/matrix.c

VPATH += $(TOP_DIR)/keyboards/keychron/$(COMMON_DIR)

include $(TOP_DIR)/keyboards/keychron/$(COMMON_DIR)/debounce/debounce.mk
