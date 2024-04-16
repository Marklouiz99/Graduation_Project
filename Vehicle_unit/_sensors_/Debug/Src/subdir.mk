################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/AFIO_program.c \
../Src/EXTI_program.c \
../Src/GPIO_program.c \
../Src/I2C_program.c \
../Src/MPU6050_program.c \
../Src/NVIC_program.c \
../Src/RCC_program.c \
../Src/SPI_Program.c \
../Src/SYSTICK_program.c \
../Src/UART_program.c \
../Src/ULTRA_program.c \
../Src/main.c \
../Src/nRF_programe.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/AFIO_program.o \
./Src/EXTI_program.o \
./Src/GPIO_program.o \
./Src/I2C_program.o \
./Src/MPU6050_program.o \
./Src/NVIC_program.o \
./Src/RCC_program.o \
./Src/SPI_Program.o \
./Src/SYSTICK_program.o \
./Src/UART_program.o \
./Src/ULTRA_program.o \
./Src/main.o \
./Src/nRF_programe.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/AFIO_program.d \
./Src/EXTI_program.d \
./Src/GPIO_program.d \
./Src/I2C_program.d \
./Src/MPU6050_program.d \
./Src/NVIC_program.d \
./Src/RCC_program.d \
./Src/SPI_Program.d \
./Src/SYSTICK_program.d \
./Src/UART_program.d \
./Src/ULTRA_program.d \
./Src/main.d \
./Src/nRF_programe.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/AFIO_program.d ./Src/AFIO_program.o ./Src/AFIO_program.su ./Src/EXTI_program.d ./Src/EXTI_program.o ./Src/EXTI_program.su ./Src/GPIO_program.d ./Src/GPIO_program.o ./Src/GPIO_program.su ./Src/I2C_program.d ./Src/I2C_program.o ./Src/I2C_program.su ./Src/MPU6050_program.d ./Src/MPU6050_program.o ./Src/MPU6050_program.su ./Src/NVIC_program.d ./Src/NVIC_program.o ./Src/NVIC_program.su ./Src/RCC_program.d ./Src/RCC_program.o ./Src/RCC_program.su ./Src/SPI_Program.d ./Src/SPI_Program.o ./Src/SPI_Program.su ./Src/SYSTICK_program.d ./Src/SYSTICK_program.o ./Src/SYSTICK_program.su ./Src/UART_program.d ./Src/UART_program.o ./Src/UART_program.su ./Src/ULTRA_program.d ./Src/ULTRA_program.o ./Src/ULTRA_program.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/nRF_programe.d ./Src/nRF_programe.o ./Src/nRF_programe.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

