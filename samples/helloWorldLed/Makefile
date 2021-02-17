# select the BOARD type here:
# BOARD :=nucleo_l011k4
# BOARD :=nucleo_l476rg
# BOARD :=nucleo_h743zi
# BOARD :=nucleo_h743zi
BOARD := adafruit_feather_nrf52840_sense

THIS_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
BOARD_ROOT := $(abspath $(THIS_DIR)/../../)


all:
	@echo get the build process working...
	west build -p auto -b $(BOARD) ./      -DBOARD_ROOT=$(BOARD_ROOT)

clean:
	-west build -t clean 
	rm ./build/ -rf
	
flash:
	west flash
