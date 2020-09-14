################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_pincfg/r_pinset.c 

COMPILER_OBJS += \
r_pincfg/r_pinset.obj 

C_DEPS += \
r_pincfg/r_pinset.d 

# Each subdirectory must supply rules for building sources it contributes
r_pincfg/%.obj: ../r_pincfg/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo r_pincfg\cDepSubCommand.tmp=
	@sed -e "s/^/    /" "r_pincfg\cDepSubCommand.tmp"
	ccrx -subcommand="r_pincfg\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo r_pincfg\cSubCommand.tmp=
	@sed -e "s/^/    /" "r_pincfg\cSubCommand.tmp"
	ccrx -subcommand="r_pincfg\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

