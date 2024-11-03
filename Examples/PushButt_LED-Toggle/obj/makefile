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
PushButt_LED-Toggle.hex \

SECONDARY_LIST += \
PushButt_LED-Toggle.lst \

SECONDARY_SIZE += \
PushButt_LED-Toggle.siz \


# All Target
all: PushButt_LED-Toggle.elf secondary-outputs

# Tool invocations
PushButt_LED-Toggle.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "/home/chowdarymanyam/Downloads/Work-Space/Firmware/CH32V/27082024_MounRiver/Workspace/SecURad/Task-02_PushButt_LED/PushButt_LED-Toggle/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"PushButt_LED-Toggle.map" --specs=nano.specs --specs=nosys.specs -o "PushButt_LED-Toggle.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

PushButt_LED-Toggle.hex: PushButt_LED-Toggle.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "PushButt_LED-Toggle.elf"  "PushButt_LED-Toggle.hex"
	@echo 'Finished building: $@'
	@echo ' '

PushButt_LED-Toggle.lst: PushButt_LED-Toggle.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --all-headers --demangle --disassemble "PushButt_LED-Toggle.elf" > "PushButt_LED-Toggle.lst"
	@echo 'Finished building: $@'
	@echo ' '

PushButt_LED-Toggle.siz: PushButt_LED-Toggle.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "PushButt_LED-Toggle.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) PushButt_LED-Toggle.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
