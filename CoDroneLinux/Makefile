TARGET = main


ROOT	 = $(dir $(lastword $(MAKEFILE_LIST)))
SRC_LIB = $(ROOT)/lib/cJoy.cpp \
		   $(ROOT)/lib/Joy.cpp 

SRC_ARDUINO = $(ROOT)/lib/arduino/variant.cpp \
		   $(ROOT)/lib/arduino/Print.cpp \
		   $(ROOT)/lib/arduino/Stream.cpp \
		   $(ROOT)/lib/arduino/WString.cpp \
		   $(ROOT)/lib/arduino/itoa.c \
		   $(ROOT)/lib/arduino/avr/dtostrf.c \
		   $(ROOT)/lib/arduino/ConsolSerial.cpp \
		   $(ROOT)/lib/arduino/WMath.cpp \
		   $(ROOT)/lib/arduino/EEPROMs.cpp \
		   $(ROOT)/lib/arduino/UARTClass.cpp 
		   
		   
SRC_DRONE = $(ROOT)/CoDrone/CoDrone.cpp 	   
		   
		   
		   
		   

SRC = 	main.cpp Arduino.cpp 	$(SRC_LIB) $(SRC_ARDUINO) $(SRC_DRONE)


INC = $(ROOT)/lib/ \
	   $(ROOT)/lib/arduino \
	   $(ROOT)/lib/arduino/avr \
	   $(ROOT)/CoDrone \
	   
	   
	   
		


CFLAGS = $(addprefix -I,$(INC))
LIBS = 

ALLSRC     =  $(SRC)
# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(ALLSRC)))

# Define all object files.
ALLOBJ = $(addsuffix .o, $(ALLSRCBASE))



MACHINE := $(shell uname -m)
ifeq ($(MACHINE), armv6l)
USERCFLAGS = -O2
endif

LDFLAGS = -lc  -lm 


all: build copyobj
#	g++ $(CFLAGS) $(USERCFLAGS) $(ALLOBJ) -I$(INC) $< -o $@ $(LIBS)


build: $(ALLOBJ)
	g++ $(CFLAGS) $(USERCFLAGS) $(ALLOBJ) --output $(TARGET) $(LDFLAGS) $(LIBS)

copyobj:
	rm -rf obj
	mkdir  obj			
	mv $(ALLOBJ) ./obj
	
	

# Compile: create object files from C source files.
define COMPILE_C_TEMPLATE
$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILING) $$< to $$@
	g++ -c $$(CFLAGS) $(USERCFLAGS) $$< -o $$@ $$(LIBS)
endef
$(foreach src, $(SRC), $(eval $(call COMPILE_C_TEMPLATE, $(src)))) 




clean: clean_list

clean_list :
	@echo $(MSG_CLEANING)
	rm -f $(TARGET)
	rm -f $(TARGET).sym
	rm -f $(TARGET).lss
	rm -f $(ALLOBJ)
	rm -f $(LSTFILES)
	rm -f $(DEPFILES)
