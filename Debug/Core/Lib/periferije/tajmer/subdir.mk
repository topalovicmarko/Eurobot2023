################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/periferije/tajmer/tajmer.c 

OBJS += \
./Core/Lib/periferije/tajmer/tajmer.o 

C_DEPS += \
./Core/Lib/periferije/tajmer/tajmer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/periferije/tajmer/tajmer.o: ../Core/Lib/periferije/tajmer/tajmer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Lib/periferije/tajmer/tajmer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

