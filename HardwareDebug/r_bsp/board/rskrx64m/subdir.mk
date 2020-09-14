################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_bsp/board/rskrx64m/dbsct.c \
../r_bsp/board/rskrx64m/hwsetup.c \
../r_bsp/board/rskrx64m/lowlvl.c \
../r_bsp/board/rskrx64m/lowsrc.c \
../r_bsp/board/rskrx64m/resetprg.c \
../r_bsp/board/rskrx64m/sbrk.c \
../r_bsp/board/rskrx64m/vecttbl.c 

COMPILER_OBJS += \
r_bsp/board/rskrx64m/dbsct.obj \
r_bsp/board/rskrx64m/hwsetup.obj \
r_bsp/board/rskrx64m/lowlvl.obj \
r_bsp/board/rskrx64m/lowsrc.obj \
r_bsp/board/rskrx64m/resetprg.obj \
r_bsp/board/rskrx64m/sbrk.obj \
r_bsp/board/rskrx64m/vecttbl.obj 

C_DEPS += \
r_bsp/board/rskrx64m/dbsct.d \
r_bsp/board/rskrx64m/hwsetup.d \
r_bsp/board/rskrx64m/lowlvl.d \
r_bsp/board/rskrx64m/lowsrc.d \
r_bsp/board/rskrx64m/resetprg.d \
r_bsp/board/rskrx64m/sbrk.d \
r_bsp/board/rskrx64m/vecttbl.d 

# Each subdirectory must supply rules for building sources it contributes
r_bsp/board/rskrx64m/%.obj: ../r_bsp/board/rskrx64m/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo r_bsp\board\rskrx64m\cDepSubCommand.tmp=
	@sed -e "s/^/    /" "r_bsp\board\rskrx64m\cDepSubCommand.tmp"
	ccrx -subcommand="r_bsp\board\rskrx64m\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo r_bsp\board\rskrx64m\cSubCommand.tmp=
	@sed -e "s/^/    /" "r_bsp\board\rskrx64m\cSubCommand.tmp"
	ccrx -subcommand="r_bsp\board\rskrx64m\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

