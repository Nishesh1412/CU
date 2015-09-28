################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dynamic_size_array_sorted.cpp \
../test_int_array.cpp 

OBJS += \
./src/dynamic_size_array_sorted.o \
./src/test_int_array.o 

CPP_DEPS += \
./src/dynamic_size_array_sorted.d \
./src/test_int_array.d 


# Each subdirectory must supply rules for building sources it contributes
src/dynamic_size_array_sorted.o: /Users/Nishesh/Dropbox/CU/2014/Fall/CSCI\ 2270/Labs/Lab\ 3\ -\ part\ 2/dynamic_size_array_sorted.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/dynamic_size_array_sorted.d" -MT"src/dynamic_size_array_sorted.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/test_int_array.o: /Users/Nishesh/Dropbox/CU/2014/Fall/CSCI\ 2270/Labs/Lab\ 3\ -\ part\ 2/test_int_array.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/test_int_array.d" -MT"src/test_int_array.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


