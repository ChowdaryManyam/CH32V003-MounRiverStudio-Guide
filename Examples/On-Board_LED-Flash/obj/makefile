################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
On-Board_LED-Flash.hex \

SECONDARY_LIST += \
On-Board_LED-Flash.lst \

SECONDARY_SIZE += \
On-Board_LED-Flash.siz \


# All Target
all: On-Board_LED-Flash.elf secondary-outputs

# Tool invocations
On-Board_LED-Flash.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/02112024_MounRiver/Workspace/On-Board_LED-Flash/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"On-Board_LED-Flash.map" --specs=nano.specs --specs=nosys.specs -o "On-Board_LED-Flash.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

On-Board_LED-Flash.hex: On-Board_LED-Flash.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "On-Board_LED-Flash.elf"  "On-Board_LED-Flash.hex"
	@echo 'Finished building: $@'
	@echo ' '

On-Board_LED-Flash.lst: On-Board_LED-Flash.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --all-headers --demangle --disassemble "On-Board_LED-Flash.elf" > "On-Board_LED-Flash.lst"
	@echo 'Finished building: $@'
	@echo ' '

On-Board_LED-Flash.siz: On-Board_LED-Flash.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "On-Board_LED-Flash.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) On-Board_LED-Flash.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
