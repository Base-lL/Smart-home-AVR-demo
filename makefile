# --- MCU & Clock Configuration ---
MCU       = atmega32
F_CPU     = 8000000UL
BUILD_DIR = build
TARGET    = $(BUILD_DIR)/main

# --- Compiler Toolchain ---
CC        = avr-gcc
OBJCOPY   = avr-objcopy
SIZE      = avr-size

# --- Source Files ---
MCAL_C = $(shell find MCAL -name "*.c" 2>/dev/null)
HAL_C  = $(shell find HAL -name "*.c" 2>/dev/null)

SRC = main.c \
      FreeRTOS-Kernel/croutine.c \
      FreeRTOS-Kernel/event_groups.c \
      FreeRTOS-Kernel/list.c \
      FreeRTOS-Kernel/tasks.c \
      FreeRTOS-Kernel/timers.c \
      FreeRTOS-Kernel/portable/GCC/ATMega323/port.c \
      FreeRTOS-Kernel/portable/MemMang/heap_1.c \
      MCAL/DIO/DIO_program.c \
      MCAL/GIE/GIE_program.c \
      MCAL/TMR/TMR_program.c \
      MCAL/UART/UART_Program.c \
      MCAL/TWI/TWI_Program.c \
      HAL/KPD/KPD_program.c \
      HAL/LCD/LCD_program.c \
      HAL/LED/LED_program.c \
      HAL/MTR/MTR_program.c \
      HAL/SRV/SRV_program.c 


# --- Include Directories (-I) ---
INC_DIRS = . \
           FreeRTOS-Kernel/include \
           FreeRTOS-Kernel/portable/GCC/ATMega323 \
           LIB \
           $(wildcard MCAL/*) \
           $(wildcard HAL/*) 

INC = $(addprefix -I,$(INC_DIRS))

# --- Compiler Flags ---
CFLAGS = -mmcu=$(MCU) \
         -DF_CPU=$(F_CPU) \
         -D GCC_MEGA_AVR \
         -Os \
         -Wall \
         -std=gnu99 \
         $(INC) \
         -ffunction-sections -fdata-sections

# --- Objects Mapping ---
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all clean size showdir

all: showdir $(TARGET).hex size flash

build: showdir $(TARGET).hex size

# Debug target to inspect variables
showdir:
	@echo "Sources:"
	@echo "$(SRC)"
	@echo ""
	@echo "Includes:"
	@echo "$(INC)"
	@echo ""
	@echo "building...:"

# Generate Intel HEX for flashing
$(TARGET).hex: $(TARGET).elf
	@$(OBJCOPY) -O ihex -R .eeprom $< $@

# Link Objects into ELF binary
$(TARGET).elf: $(OBJ)
	@$(CC) -mmcu=$(MCU) $(OBJ) -Wl,--gc-sections -o $@

# Compile C sources (recipe MUST start with a real Tab)
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Display binary size stats
size: $(TARGET).elf
	@$(SIZE) --format=avr --mcu=$(MCU) $(TARGET).elf

clean:
	@rm -rf $(BUILD_DIR)


flash:
	@avrdude -c usbasp -p m32 -U flash:w:${BUILD_DIR}/main.hex:i

