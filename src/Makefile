BUILD_DIR ?= $(CURDIR)

TOOLCHAIN_PREFIX ?= 
CC_FLAGS_APPEND ?= 

CC := $(TOOLCHAIN_PREFIX)gcc
INC := ../include/
FLAGS := -fpic -std=gnu99 -Wall -pedantic -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -lm -I$(INC) -O3

FLAGS += $(CC_FLAGS_APPEND)

.PHONY: all
all: $(BUILD_DIR)/tle.o

$(BUILD_DIR)/sgp4.o: sgp4.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/tle.o: tle.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(BUILD_DIR)/*.o
