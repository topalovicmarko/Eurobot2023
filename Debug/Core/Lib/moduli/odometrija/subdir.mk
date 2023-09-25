################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/moduli/odometrija/odometrija.c 

OBJS += \
./Core/Lib/moduli/odometrija/odometrija.o 

C_DEPS += \
./Core/Lib/moduli/odometrija/odometrija.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/moduli/odometrija/odometrija.o: ../Core/Lib/moduli/odometrija/odometrija.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Lib/moduli/odometrija/odometrija.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

