################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/27082024_MounRiver/Workspace/SecURad/Task-06_RF_Interface/RF_480E/Debug" -I"/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/27082024_MounRiver/Workspace/SecURad/Task-06_RF_Interface/RF_480E/Core" -I"/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/27082024_MounRiver/Workspace/SecURad/Task-06_RF_Interface/RF_480E/User" -I"/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/27082024_MounRiver/Workspace/SecURad/Task-06_RF_Interface/RF_480E/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


