CPP = g++

CPPFLAGS  = -std=c++17
CPPFLAGS += -Wall
CPPFLAGS += -Wextra
CPPFLAGS += -pedantic
CPPFLAGS += -Werror

CLI  = arduino-cli
FQBN = arduino:samd:mkr1000
PORT = /dev/ttyACM0
INO  = arduino_rain_gauge.ino
WARN = --warnings all

build: 
	$(CLI) compile --fqbn $(FQBN) $(INO) $(WARN)

upload:
	$(CLI) upload -p $(PORT) --fqbn $(FQBN) $(INO) 

test_tlv: test/test_tlv.cpp
	@$(CPP) $(CPPFLAGS) -o build/$@ $^
	@./build/$@
	@rm ./build/$@

test: test_tlv

all: build upload
