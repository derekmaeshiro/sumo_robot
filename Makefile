# Check arguments
ifeq ($(HW), LAUNCHPAD) # HW argument
TARGET_HW = launchpad
else ifeq ($(HW), NSUMO)
TARGET_HW = nsumo
else ifeq ($(MAKECMDGOALS), clean)
else ifeq ($(MAKECMDGOALS), cppcheck)
else ifeq ($(MAKECMDGOALS), format)
# HW argument not required for this rule
else
$(error "Must pass HW=LAUNCHPAD or HW=NSUMO")
endif
TARGET_NAME = $(TARGET_HW)

ifneq ($(TEST),) # TEST argument
ifeq ($(findstring test_, $(TEST)),)
$(error "TEST=$(TEST) is invalid (test function must start with test_)")
else
TARGET_NAME=$(TEST)
endif
endif

#Directories
TOOLS_DIR = ${TOOLS_PATH}
MSPGCC_ROOT_DIR = $(TOOLS_DIR)
MSPGCC_BIN_DIR = $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR = $(MSPGCC_ROOT_DIR)/include
INCLUDE_DIRS = $(MSPGCC_INCLUDE_DIR)
LIB_DIRS = $(MSPGCC_INCLUDE_DIR)
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
TI_CCS_DIR = /Applications/ti/ccs2011/ccs
DEBUG_BIN_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/drivers

#Toolchain
CC = $(MSPGCC_BIN_DIR)/msp430-elf-gcc
RM = rm
DEBUG = DYLD_LIBRARY_PATH=$(DEBUG_DRIVERS_DIR) $(DEBUG_BIN_DIR)/mspdebug
CPPCHECK = cppcheck
FORMAT = clang-format

#Files
TARGET = $(BUILD_DIR)/bin/$(TARGET_HW)/$(TARGET_NAME)

SOURCES_WITH_HEADERS = \
	  src/drivers/io.c \
	  src/drivers/mcu_init.c \
	  src/drivers/led.c \
	  src/app/drive.c \
	  src/app/enemy.c \
	  src/common/assert_handler.c \

ifndef TEST

SOURCES = \
	  src/main.c \
	  $(SOURCES_WITH_HEADERS)
else
SOURCES = \
	  src/test/test.c \
	  $(SOURCES_WITH_HEADERS)
# Delete object file to force rebuild when changing test
$(shell rm -f $(BUILD_DIR)/obj/src/test/test.o)
endif

HEADERS = \
	  $(SOURCES_WITH_HEADERS:.c=.h) \
	  src/common/defines.h \

OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %, $(OBJ_DIR)/%, $(OBJECT_NAMES))

# Defines
HW_DEFINE = $(addprefix -D, $(HW)) # e.g. -DNSUMO or -DLAUNCHPAD
TEST_DEFINE = $(addprefix -DTEST=, $(TEST))
DEFINES = \
	$(HW_DEFINE) \
	$(TEST_DEFINE)

#Static Analysis
##Don't check the msp430 helper headers
CPPCHECK_INCLUDES = ./src
CPPCHECK_IGNORE = external/printf
CPPCHECK_FLAGS = \
	--quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=unmatchedSuppression \
	--suppress=staticFunction \
	--suppress=unusedFunction \
	$(addprefix -I, $(CPPCHECK_INCLUDES)) \
	$(addprefix -i, $(CPPCHECK_IGNORE))

#Flags
MCU = msp430g2553
WFLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = -mmcu=$(MCU) $(WFLAGS) -fshort-enums $(addprefix -I, $(INCLUDE_DIRS)) $(DEFINES) -Og -g
LDFLAGS = -mmcu=$(MCU) $(DEFINES) $(addprefix -L, $(LIB_DIRS))

#Build
#Linking
$(TARGET): $(OBJECTS) $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

#Compiling
$(OBJ_DIR)/%.o: %.c	
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

# Phonies
.PHONY: all clean flash cppcheck format

all: $(TARGET)

clean:
	$(RM) -rf $(BUILD_DIR)

flash: $(TARGET)
	$(DEBUG) tilib "prog $(TARGET)"

cppcheck:
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SOURCES)

format:
	@$(FORMAT) -i $(SOURCES) $(HEADERS)
