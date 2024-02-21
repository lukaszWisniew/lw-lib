PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

export CXX=g++

BUILD_MODE=linuxtools

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
	EXTRA_CLEAN += lw-libs.gcda lw-libs.gcno $(PROJECT_ROOT)gmon.out
	EXTRA_CMDS = rm -rf lw-libs.gcda
else
	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

export CXXFLAGS=-g -Wall -pedantic -std=gnu++17

all:
	$(MAKE) -C $(PROJECT_ROOT)misc
	$(MAKE) -C $(PROJECT_ROOT)config
	$(MAKE) -C $(PROJECT_ROOT)ev_main
	$(MAKE) -C $(PROJECT_ROOT)log


clean:
	$(MAKE) -C $(PROJECT_ROOT)misc clean
	$(MAKE) -C $(PROJECT_ROOT)config clean
	$(MAKE) -C $(PROJECT_ROOT)ev_main clean
	$(MAKE) -C $(PROJECT_ROOT)log clean
