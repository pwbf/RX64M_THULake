################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_sys_time_rx/src/r_sys_time_rx.c 

COMPILER_OBJS += \
r_sys_time_rx/src/r_sys_time_rx.obj 

C_DEPS += \
r_sys_time_rx/src/r_sys_time_rx.d 

# Each subdirectory must supply rules for building sources it contributes
r_sys_time_rx/src/%.obj: ../r_sys_time_rx/src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo r_sys_time_rx\src\cDepSubCommand.tmp=
	@sed -e "s/^/    /" "r_sys_time_rx\src\cDepSubCommand.tmp"
	ccrx -subcommand="r_sys_time_rx\src\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo r_sys_time_rx\src\cSubCommand.tmp=
	@sed -e "s/^/    /" "r_sys_time_rx\src\cSubCommand.tmp"
	ccrx -subcommand="r_sys_time_rx\src\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

