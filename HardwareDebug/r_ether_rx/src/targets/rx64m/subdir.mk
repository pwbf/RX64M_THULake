################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_ether_rx/src/targets/rx64m/r_ether_setting_rx64m.c 

COMPILER_OBJS += \
r_ether_rx/src/targets/rx64m/r_ether_setting_rx64m.obj 

C_DEPS += \
r_ether_rx/src/targets/rx64m/r_ether_setting_rx64m.d 

# Each subdirectory must supply rules for building sources it contributes
r_ether_rx/src/targets/rx64m/%.obj: ../r_ether_rx/src/targets/rx64m/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo r_ether_rx\src\targets\rx64m\cDepSubCommand.tmp=
	@sed -e "s/^/    /" "r_ether_rx\src\targets\rx64m\cDepSubCommand.tmp"
	ccrx -subcommand="r_ether_rx\src\targets\rx64m\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo r_ether_rx\src\targets\rx64m\cSubCommand.tmp=
	@sed -e "s/^/    /" "r_ether_rx\src\targets\rx64m\cSubCommand.tmp"
	ccrx -subcommand="r_ether_rx\src\targets\rx64m\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

