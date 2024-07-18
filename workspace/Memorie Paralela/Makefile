#==== OPTIONS ====================================================================
F_CPU 			= 16000000
PARTNUMBER      = atmega328p
# PARTNUMBER      = atmega168
OUTPUT_FOLDER   = builds/
TARGET 			= main
EXTENTION 		= c

#==== AVR dude Config ============================================================
AVRDUDE 		= avrdude
# AVR_DUDE_CONF   = C:/Users/andre/AppData/Local/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf
PROGRAMMER_TYPE = arduino
PORT 	  	    = COM7
CONFIG		    = arduino
BAUD_RATE 	    = 115200
PROGRAM			= $(OUTPUT_FOLDER)$(TARGET).hex
ARGS 		    = -p $(PARTNUMBER) -c $(CONFIG) -P $(PORT) -b $(BAUD_RATE) -D -U flash:w:$(PROGRAM):i

#==== AVR gcc config =============================================================
CXX    = avr-gcc
CFLAGS = -mmcu=$(PARTNUMBER) -Wall -DF_CPU=$(F_CPU) -Os

#===== AVR obj config  ===========================================================
AVROBJ  = avr-objcopy
AVRDUMP = avr-objcopy

#===== AVR assembler  ============================================================
ASSEMBLER = avrasm2
ASMFLAGS = -fI -W+ie -I"C:/Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\avrasm\inc" -d "C:\Users\andre\Documents\Atmel Studio\7.0\Assembly\Assembly\Debug\Assembly.obj" -I"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avrassembler\Include"

#===== Terminal  =================================================================
TERMINAL 		   = plink
DATA_BITS	 	   = 8
PARITY 			   = n#no parity
STOP_BITS 		   = 1
FLOW_CONTROL 	   = N #none
TERMINAL_BAUD_RATE = 9600
TERMINAL_ARGS	= -serial $(PORT) -sercfg $(TERMINAL_BAUD_RATE),$(DATA_BITS),$(PARITY),$(STOP_BITS),$(FLOW_CONTROL)

all: clean $(OUTPUT_FOLDER)$(TARGET).hex
	@$(AVRDUDE) $(ARGS)

$(OUTPUT_FOLDER)$(TARGET).hex:
ifeq ($(EXTENTION),c)
	@$(MAKE) $(OUTPUT_FOLDER)$(TARGET).elf
	@$(AVROBJ) -O ihex -j .text -j .data $(OUTPUT_FOLDER)$(TARGET).elf $@
else 
	@$(ASSEMBLER) $(ASMFLAGS) -o $@ $(TARGET).s
	@avr-size -A $@
endif

$(OUTPUT_FOLDER)$(TARGET).elf: $(OUTPUT_FOLDER)$(TARGET).o
	@$(CXX) $(CFLAGS) $< --output $@
	@avr-size -A $@

$(OUTPUT_FOLDER)$(TARGET).o: $(TARGET).c
	@$(CXX) $(CFLAGS) -o $@ -c $<  
	@$(CXX) $(CFLAGS) -o $(OUTPUT_FOLDER)$(TARGET).s -S $<  
	
.PHONY: clean
clean:
	rm -rf builds
	mkdir builds

com:
	@$(TERMINAL) $(TERMINAL_ARGS)