################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Lib/Peripheries/TIMER/subdir.mk
-include Core/Lib/Peripheries/GPIO/subdir.mk
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
Eurobot2023.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Eurobot2023.list \

OBJCOPY_BIN += \
Eurobot2023.bin \


# All Target
all: Eurobot2023.elf secondary-outputs

# Tool invocations
Eurobot2023.elf: $(OBJS) $(USER_OBJS) /home/marko/STM32CubeIDE/workspace_1.2.0/Eurobot2023/STM32F405RGTX_FLASH.ld
	arm-none-eabi-gcc -o "Eurobot2023.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/marko/STM32CubeIDE/workspace_1.2.0/Eurobot2023/STM32F405RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Eurobot2023.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Eurobot2023.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Eurobot2023.list"
	@echo 'Finished building: $@'
	@echo ' '

Eurobot2023.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Eurobot2023.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
