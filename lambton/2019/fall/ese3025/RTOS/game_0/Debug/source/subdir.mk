################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/cr_startup_lpc175x_6x.c \
../source/crp.c \
../source/game_0.c \
../source/libgameIO.c \
../source/libgameds.c \
../source/libgametasks.c \
../source/libtakisbasics.c \
../source/sysinit.c 

OBJS += \
./source/cr_startup_lpc175x_6x.o \
./source/crp.o \
./source/game_0.o \
./source/libgameIO.o \
./source/libgameds.o \
./source/libgametasks.o \
./source/libtakisbasics.o \
./source/sysinit.o 

C_DEPS += \
./source/cr_startup_lpc175x_6x.d \
./source/crp.d \
./source/game_0.d \
./source/libgameIO.d \
./source/libgameds.d \
./source/libgametasks.d \
./source/libtakisbasics.d \
./source/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/game_0/inc" -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/lpc_chip_175x_6x/inc" -I"/home/takis/Identities/takiszourntos/teaching/lambton/2019/fall/ese3025/RTOS/game_0/freertos/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


