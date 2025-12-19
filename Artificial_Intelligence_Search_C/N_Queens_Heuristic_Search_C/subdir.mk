################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/nqueens.c 

C_DEPS += \
./src/main.d \
./src/nqueens.d 

OBJS += \
./src/main.o \
./src/nqueens.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DUSE_SDL_GUI -I/opt/homebrew/include -O0 -g3 -Wall -arch arm64 -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/main.d ./src/main.o ./src/nqueens.d ./src/nqueens.o

.PHONY: clean-src

