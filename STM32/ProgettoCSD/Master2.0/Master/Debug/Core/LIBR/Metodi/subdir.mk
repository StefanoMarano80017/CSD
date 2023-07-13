################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LIBR/Metodi/ManageStr.c \
../Core/LIBR/Metodi/invio.c 

OBJS += \
./Core/LIBR/Metodi/ManageStr.o \
./Core/LIBR/Metodi/invio.o 

C_DEPS += \
./Core/LIBR/Metodi/ManageStr.d \
./Core/LIBR/Metodi/invio.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LIBR/Metodi/%.o Core/LIBR/Metodi/%.su Core/LIBR/Metodi/%.cyclo: ../Core/LIBR/Metodi/%.c Core/LIBR/Metodi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-LIBR-2f-Metodi

clean-Core-2f-LIBR-2f-Metodi:
	-$(RM) ./Core/LIBR/Metodi/ManageStr.cyclo ./Core/LIBR/Metodi/ManageStr.d ./Core/LIBR/Metodi/ManageStr.o ./Core/LIBR/Metodi/ManageStr.su ./Core/LIBR/Metodi/invio.cyclo ./Core/LIBR/Metodi/invio.d ./Core/LIBR/Metodi/invio.o ./Core/LIBR/Metodi/invio.su

.PHONY: clean-Core-2f-LIBR-2f-Metodi

