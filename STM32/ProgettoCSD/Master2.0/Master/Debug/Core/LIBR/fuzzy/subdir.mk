################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LIBR/fuzzy/fuzzy.c 

OBJS += \
./Core/LIBR/fuzzy/fuzzy.o 

C_DEPS += \
./Core/LIBR/fuzzy/fuzzy.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LIBR/fuzzy/%.o Core/LIBR/fuzzy/%.su Core/LIBR/fuzzy/%.cyclo: ../Core/LIBR/fuzzy/%.c Core/LIBR/fuzzy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-LIBR-2f-fuzzy

clean-Core-2f-LIBR-2f-fuzzy:
	-$(RM) ./Core/LIBR/fuzzy/fuzzy.cyclo ./Core/LIBR/fuzzy/fuzzy.d ./Core/LIBR/fuzzy/fuzzy.o ./Core/LIBR/fuzzy/fuzzy.su

.PHONY: clean-Core-2f-LIBR-2f-fuzzy

