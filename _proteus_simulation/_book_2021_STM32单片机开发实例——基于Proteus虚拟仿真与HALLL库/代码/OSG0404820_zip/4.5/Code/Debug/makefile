################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
4.5.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
4.5.list \

OBJCOPY_HEX += \
4.5.hex \

OBJCOPY_BIN += \
4.5.bin \


# All Target
all: 4.5.elf secondary-outputs

# Tool invocations
4.5.elf: $(OBJS) $(USER_OBJS) D:\stm32_prj\4.5\Code\STM32F103R6TX_FLASH.ld
	arm-none-eabi-gcc -o "4.5.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\stm32_prj\4.5\Code\STM32F103R6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="4.5.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

4.5.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "4.5.list"
	@echo 'Finished building: $@'
	@echo ' '

4.5.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "4.5.hex"
	@echo 'Finished building: $@'
	@echo ' '

4.5.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "4.5.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
