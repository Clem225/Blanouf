################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../diner_philosphes.c \
../imx_serial.c \
../led.c \
../noyau.c \
../noyaufil.c \
../noyautes.c \
../noyautes_sem.c \
../pipe.c \
../sem.c \
../serialio.c \
../testfile.c 

S_UPPER_SRCS += \
../crt0.S \
../lowlevel_init.S 

OBJS += \
./crt0.o \
./diner_philosphes.o \
./imx_serial.o \
./led.o \
./lowlevel_init.o \
./noyau.o \
./noyaufil.o \
./noyautes.o \
./noyautes_sem.o \
./pipe.o \
./sem.o \
./serialio.o \
./testfile.o 

C_DEPS += \
./diner_philosphes.d \
./imx_serial.d \
./led.d \
./noyau.d \
./noyaufil.d \
./noyautes.d \
./noyautes_sem.d \
./pipe.d \
./sem.d \
./serialio.d \
./testfile.d 


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


