###############################################################################
# Makefile for the project ATMEGA128_ucosii
###############################################################################

## General Flags
PROJECT = vehicle
MCU = atmega128
TARGET = vehicle.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d -g

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=vehicle.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"..\main" -I"..\drive" 

## Objects that must be built in order to link
OBJECTS = main.o timer.o uart.o servo.o adc.o motor.o fight.o menu.o update.o init.o comn.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) vehicle.hex vehicle.eep vehicle.lss size

## Compile
main.o: ../main/main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer.o: ../drive/timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../drive/uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

servo.o: ../drive/servo.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

adc.o: ../drive/adc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

watch_dog.o: ../drive/watch_dog.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

motor.o: ../drive/motor.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fight.o: ../main/fight.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

menu.o: ../main/menu.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

update.o: ../main/update.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

init.o: ../main/init.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

comn.o: ../main/comn.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<


##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) vehicle.elf dep/* vehicle.hex vehicle.eep vehicle.lss vehicle.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

