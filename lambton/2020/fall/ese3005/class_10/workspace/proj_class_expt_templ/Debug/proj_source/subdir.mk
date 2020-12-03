################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../proj_source/proj_class_expt_templ.cpp \
../proj_source/proj_classes.cpp \
../proj_source/students.cpp 

OBJS += \
./proj_source/proj_class_expt_templ.o \
./proj_source/proj_classes.o \
./proj_source/students.o 

CPP_DEPS += \
./proj_source/proj_class_expt_templ.d \
./proj_source/proj_classes.d \
./proj_source/students.d 


# Each subdirectory must supply rules for building sources it contributes
proj_source/proj_class_expt_templ.o: ../proj_source/proj_class_expt_templ.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/takis/Identities/takiszourntos/teaching/lambton/2020/fall/ese3005/class_10/workspace/proj_class_expt_templ/proj_includes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"proj_source/proj_class_expt_templ.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

proj_source/%.o: ../proj_source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/takis/Identities/takiszourntos/teaching/lambton/2020/fall/ese3005/class_10/workspace/proj_class_expt_templ/proj_includes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


