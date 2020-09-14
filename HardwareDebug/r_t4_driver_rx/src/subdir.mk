################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_t4_driver_rx/src/ether_callback.c \
../r_t4_driver_rx/src/t4_driver.c \
../r_t4_driver_rx/src/timer.c 

COMPILER_OBJS += \
r_t4_driver_rx/src/ether_callback.obj \
r_t4_driver_rx/src/t4_driver.obj \
r_t4_driver_rx/src/timer.obj 

C_DEPS += \
r_t4_driver_rx/src/ether_callback.d \
r_t4_driver_rx/src/t4_driver.d \
r_t4_driver_rx/src/timer.d 

# Each subdirectory must supply rules for building sources it contributes
r_t4_driver_rx/src/%.obj: ../r_t4_driver_rx/src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo r_t4_driver_rx\src\cDepSubCommand.tmp=
	@sed -e "s/^/    /" "r_t4_driver_rx\src\cDepSubCommand.tmp"
	ccrx -subcommand="r_t4_driver_rx\src\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo r_t4_driver_rx\src\cSubCommand.tmp=
	@sed -e "s/^/    /" "r_t4_driver_rx\src\cSubCommand.tmp"
	ccrx -subcommand="r_t4_driver_rx\src\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

