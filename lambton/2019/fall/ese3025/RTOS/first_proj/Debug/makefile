################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: first_proj.axf

# Tool invocations
first_proj.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/lpc_board_nxp_lpcxpresso_1769/Debug" -L"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/lpc_chip_175x_6x/Debug" -Xlinker -Map="first_proj.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "first_proj_Debug.ld" -o "first_proj.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) first_proj.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "first_proj.axf"; # arm-none-eabi-objcopy -v -O binary "first_proj.axf" "first_proj.bin" ; # checksum -p LPC1769 -d "first_proj.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
