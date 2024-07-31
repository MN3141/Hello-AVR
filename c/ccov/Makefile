#==== OPTIONS ====================================================================
F_CPU 			= 16000000
PARTNUMBER      = atmega328p
# PARTNUMBER      = atmega168
OUTPUT_FOLDER   = builds/
TARGET 			= main
EXTENSION 		= c

#==== AVR dude Config ============================================================
AVRDUDE 		= avrdude
AVR_DUDE_CONF   = ${avrdude_conf}
PROGRAMMER_TYPE = arduino
PORT 	  	    = COM7
CONFIG		    = arduino
BAUD_RATE 	    = 115200
PROGRAM			= $(OUTPUT_FOLDER)$(TARGET).hex
ARGS 		    = -p $(PARTNUMBER) -c $(CONFIG) -P $(PORT) -b $(BAUD_RATE) -D -U flash:w:$(PROGRAM):i -C $(AVR_DUDE_CONF)

#==== AVR gcc config =============================================================
CXX    = avr-gcc
CFLAGS = -mmcu=$(PARTNUMBER) -Wall -DF_CPU=$(F_CPU) -Os

#===== AVR obj config  ===========================================================
AVROBJ  = avr-objcopy
AVRDUMP = avr-objcopy

#===== AVR assembler  ============================================================
ASSEMBLER = avrasm2
ASMFLAGS = -fI -W+ie -I$(avrasm_include) -o $(OUTPUT_FOLDER)$(TARGET).hex  -m $(OUTPUT_FOLDER)$(TARGET).map -l $(OUTPUT_FOLDER)$(TARGET)lss -S $(OUTPUT_FOLDER)$(TARGET).tmp

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
ifeq ($(EXTENSION),c)
	@$(MAKE) $(OUTPUT_FOLDER)$(TARGET).elf
	@$(AVROBJ) -O ihex -j .text -j .data $(OUTPUT_FOLDER)$(TARGET).elf $@
else 
	@$(ASSEMBLER) $(ASMFLAGS) -o $@ $(TARGET).s
	@avr-size -A $@ >> $(OUTPUT_FOLDER)/memory_segments.txt
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

#We want to thank Thanassis Tsiodras, Alexander Tarasikov and Ken Peters
#for their contribution to CCOV with GCC on embedded systems
#At the moment code coverage is only for C source files
ccov:$(TARGET).c
	@CFLAGS_CCOV=-mmcu=$(PARTNUMBER) -Wall -DF_CPU=$(F_CPU) -O0 --coverage
	@$(CXX) $(CFLAGS_CCOV) -o $(OUTPUT_FOLDER)$(TARGET).o -c $<
	@$(CXX) $(CFLAGS_CCOV) $< --output $(OUTPUT_FOLDER)$(TARGET).elf 
	@$(AVROBJ) -O ihex -j .text -j .data $(OUTPUT_FOLDER)$(TARGET).elf $(OUTPUT_FOLDER)$(TARGET).hex
	@$(AVRDUDE) $(ARGS)