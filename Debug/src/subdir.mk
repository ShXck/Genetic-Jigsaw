################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GeneticJigsaw.cpp \
../src/ImageHandler.cpp \
../src/Jigsaw.cpp \
../src/util.cpp 

OBJS += \
./src/GeneticJigsaw.o \
./src/ImageHandler.o \
./src/Jigsaw.o \
./src/util.o 

CPP_DEPS += \
./src/GeneticJigsaw.d \
./src/ImageHandler.d \
./src/Jigsaw.d \
./src/util.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


