################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_bsp/mcu/rx64m/cpu.c \
../r_bsp/mcu/rx64m/locking.c \
../r_bsp/mcu/rx64m/mcu_clocks.c \
../r_bsp/mcu/rx64m/mcu_init.c \
../r_bsp/mcu/rx64m/mcu_interrupts.c \
../r_bsp/mcu/rx64m/mcu_locks.c \
../r_bsp/mcu/rx64m/mcu_mapped_interrupts.c 

COMPILER_OBJS += \
r_bsp/mcu/rx64m/cpu.obj \
r_bsp/mcu/rx64m/locking.obj \
r_bsp/mcu/rx64m/mcu_clocks.obj \
r_bsp/mcu/rx64m/mcu_init.obj \
r_bsp/mcu/rx64m/mcu_interrupts.obj \
r_bsp/mcu/rx64m/mcu_locks.obj \
r_bsp/mcu/rx64m/mcu_mapped_interrupts.obj 

C_DEPS += \
r_bsp/mcu/rx64m/cpu.d \
r_bsp/mcu/rx64m/locking.d \
r_bsp/mcu/rx64m/mcu_clocks.d \
r_bsp/mcu/rx64m/mcu_init.d \
r_bsp/mcu/rx64m/mcu_interrupts.d \
r_bsp/mcu/rx64m/mcu_locks.d \
r_bsp/mcu/rx64m/mcu_mapped_interrupts.d 

# Each subdirectory must supply rules for building sources it contributes
r_bsp/mcu/rx64m/%.obj: ../r_bsp/mcu/rx64m/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo r_bsp\mcu\rx64m\cDepSubCommand.tmp=
	@sed -e "s/^/    /" "r_bsp\mcu\rx64m\cDepSubCommand.tmp"
	ccrx -subcommand="r_bsp\mcu\rx64m\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo r_bsp\mcu\rx64m\cSubCommand.tmp=
	@sed -e "s/^/    /" "r_bsp\mcu\rx64m\cSubCommand.tmp"
	ccrx -subcommand="r_bsp\mcu\rx64m\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

