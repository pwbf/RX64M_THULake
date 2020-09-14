################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/tcp_blocking_sample/config_tcpudp.c \
../src/tcp_blocking_sample/echo_srv.c 

COMPILER_OBJS += \
src/tcp_blocking_sample/config_tcpudp.obj \
src/tcp_blocking_sample/echo_srv.obj 

C_DEPS += \
src/tcp_blocking_sample/config_tcpudp.d \
src/tcp_blocking_sample/echo_srv.d 

# Each subdirectory must supply rules for building sources it contributes
src/tcp_blocking_sample/%.obj: ../src/tcp_blocking_sample/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\tcp_blocking_sample\cDepSubCommand.tmp=
	@sed -e "s/^/    /" "src\tcp_blocking_sample\cDepSubCommand.tmp"
	ccrx -subcommand="src\tcp_blocking_sample\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\tcp_blocking_sample\cSubCommand.tmp=
	@sed -e "s/^/    /" "src\tcp_blocking_sample\cSubCommand.tmp"
	ccrx -subcommand="src\tcp_blocking_sample\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

