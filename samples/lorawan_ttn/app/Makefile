# select the BOARD type here:
BOARD :="nucleo_wl55jc"

BIN_NAME := "xxx"
VERSION := "0.1.0.0"

THIS_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
#BOARD_ROOT := $(abspath $(THIS_DIR)/../../../../zephyr/)


all:
	@echo get the build process working...
	west build -p auto -b $(BOARD) ./      #-DBOARD_ROOT=$(BOARD_ROOT)

clean:
	rm ./build/ -rf
	
flash:
	west flash


bin-release: all
	mkdir -p bin/
	cp build/zephyr/zephyr.bin  bin/earlyBird-$(BIN_NAME)-$(BOARD)-$(VERSION).bin
