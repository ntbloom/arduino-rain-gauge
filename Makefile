CPP = g++

CPPFLAGS  = -std=c++17
CPPFLAGS += -Wall
CPPFLAGS += -Wextra
CPPFLAGS += -pedantic
CPPFLAGS += -Werror

VFLAGS	= --quiet
VFLAGS += -v
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1
VFLAGS += --show-reachable=yes
VFLAGS += --show-possibly-lost=yes
VFLAGS += --undef-value-errors=yes
VFLAGS += --track-origins=yes

CLI  = arduino-cli
FQBN = arduino:samd:mkr1000
PORT = /dev/ttyACM0
INO  = arduino_rain_gauge.ino
WARN = --warnings all

build: 
	$(CLI) compile --fqbn $(FQBN) $(INO) $(WARN)

upload:
	$(CLI) upload -p $(PORT) --fqbn $(FQBN) $(INO) 

test_tlv: test/test_tlv.cpp src/tlv.cpp
	@$(CPP) $(CPPFLAGS) -o build/$@ $^
	@./build/$@

memcheck: test_tlv
	@valgrind $(VFLAGS) build/$^

test: test_tlv

clean: 
	$(CLI) cache clean

all: build upload
