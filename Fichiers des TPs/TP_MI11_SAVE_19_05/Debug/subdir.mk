################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../imx_serial.c \
../led.c \
../noyau.c \
../noyaufil.c \
../noyautes.c \
../serialio.c \
../testfile.c \
../tp2.c \
../tp22.c 

S_UPPER_SRCS += \
../crt0.S \
../init.S \
../lowlevel_init.S 

OBJS += \
./crt0.o \
./imx_serial.o \
./init.o \
./led.o \
./lowlevel_init.o \
./noyau.o \
./noyaufil.o \
./noyautes.o \
./serialio.o \
./testfile.o \
./tp2.o \
./tp22.o 

C_DEPS += \
./imx_serial.d \
./led.d \
./noyau.d \
./noyaufil.d \
./noyautes.d \
./serialio.d \
./testfile.d \
./tp2.d \
./tp22.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	arm-none-eabi-as -ggdb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -O0 -g3 -Wall -c -fmessage-length=0 -ffreestanding -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


