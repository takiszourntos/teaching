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
all: game_0.axf

# Tool invocations
game_0.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/lpc_board_nxp_lpcxpresso_1769/Debug" -L"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/lpc_chip_175x_6x/Debug" -Xlinker -Map="game_0.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "game_0_Debug.ld" -o "game_0.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) game_0.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "game_0.axf"; # arm-none-eabi-objcopy -v -O binary "game_0.axf" "game_0.bin" ; # checksum -p LPC1769 -d "game_0.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
