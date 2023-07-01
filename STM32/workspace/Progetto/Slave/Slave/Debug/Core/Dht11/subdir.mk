################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Dht11/DHT.c 

OBJS += \
./Core/Dht11/DHT.o 

C_DEPS += \
./Core/Dht11/DHT.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Dht11/%.o Core/Dht11/%.su Core/Dht11/%.cyclo: ../Core/Dht11/%.c Core/Dht11/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Dht11

clean-Core-2f-Dht11:
	-$(RM) ./Core/Dht11/DHT.cyclo ./Core/Dht11/DHT.d ./Core/Dht11/DHT.o ./Core/Dht11/DHT.su

.PHONY: clean-Core-2f-Dht11

