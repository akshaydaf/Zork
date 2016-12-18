################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Attack.cpp \
../Border.cpp \
../Condition.cpp \
../Container.cpp \
../Creature.cpp \
../Item.cpp \
../Main.cpp \
../Room.cpp \
../Trigger.cpp \
../Turnon.cpp 

OBJS += \
./Attack.o \
./Border.o \
./Condition.o \
./Container.o \
./Creature.o \
./Item.o \
./Main.o \
./Room.o \
./Trigger.o \
./Turnon.o 

CPP_DEPS += \
./Attack.d \
./Border.d \
./Condition.d \
./Container.d \
./Creature.d \
./Item.d \
./Main.d \
./Room.d \
./Trigger.d \
./Turnon.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


