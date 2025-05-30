LANGUAGE_DIR = common/language
SRC += \
     $(LANGUAGE_DIR)/language.c \

VPATH += $(TOP_DIR)/keyboards/keychron/$(LANGUAGE_DIR)

OPT_DEFS += -DLANGUAGE_ENABLE
