################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/main.c 

COMPILER_OBJS += \
src/main.obj 

C_DEPS += \
src/main.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\cDepSubCommand.tmp=
	@sed -e "s/^/    /" "src\cDepSubCommand.tmp"
	ccrx -subcommand="src\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\cSubCommand.tmp=
	@sed -e "s/^/    /" "src\cSubCommand.tmp"
	ccrx -subcommand="src\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

