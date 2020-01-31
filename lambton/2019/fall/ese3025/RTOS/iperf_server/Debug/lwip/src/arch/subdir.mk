################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/arch/lpc17xx_40xx_emac.c \
../lwip/src/arch/lpc17xx_40xx_systick_arch.c \
../lwip/src/arch/lpc_debug.c 

OBJS += \
./lwip/src/arch/lpc17xx_40xx_emac.o \
./lwip/src/arch/lpc17xx_40xx_systick_arch.o \
./lwip/src/arch/lpc_debug.o 

C_DEPS += \
./lwip/src/arch/lpc17xx_40xx_emac.d \
./lwip/src/arch/lpc17xx_40xx_systick_arch.d \
./lwip/src/arch/lpc_debug.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/arch/%.o: ../lwip/src/arch/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/lpc_chip_175x_6x/inc" -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/iperf_server/example/inc" -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/iperf_server/lwip/inc" -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/iperf_server/lwip/inc/ipv4" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


