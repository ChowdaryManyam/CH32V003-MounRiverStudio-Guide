################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v00x_it.c \
../User/main.c \
../User/system_ch32v00x.c 

OBJS += \
./User/ch32v00x_it.o \
./User/main.o \
./User/system_ch32v00x.o 

C_DEPS += \
./User/ch32v00x_it.d \
./User/main.d \
./User/system_ch32v00x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/02112024_MounRiver/Workspace/PWM-Tone/Debug" -I"/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/02112024_MounRiver/Workspace/PWM-Tone/Core" -I"/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/02112024_MounRiver/Workspace/PWM-Tone/User" -I"/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/02112024_MounRiver/Workspace/PWM-Tone/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


