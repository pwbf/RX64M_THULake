################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.bls *.libelf *.rel *.lbk *.abs  *.obj *.p *.pp *.d *.asm 1st/*.obj 1st/*.d 1st/*.asm 1st/*.abs

# All of the sources participating in the build are defined here
-include sources.mk
-include r_bsp/mcu/rx64m/subdir.mk
-include src/tcp_blocking_sample/subdir.mk
-include r_ether_rx/src/targets/rx64m/subdir.mk
-include src/subdir.mk
-include r_t4_driver_rx/src/subdir.mk
-include r_pincfg/subdir.mk
-include r_cmt_rx/src/subdir.mk
-include r_ether_rx/src/subdir.mk
-include r_sys_time_rx/src/subdir.mk
-include r_ether_rx/src/phy/subdir.mk
-include r_bsp/board/rskrx64m/subdir.mk
-include r_bsp/mcu/all/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
rx64m_rsk.abs

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
rx64m_rsk.lib

CONVERTOR_OUTPUT_OUTPUTS += \
rx64m_rsk.mot \
rx64m_rsk.x

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all: $(CONVERTOR_OUTPUT_OUTPUTS) 
	@echo 'Build complete.'

rx64m_rsk.mot: $(LINKER_OUTPUT_OUTPUTS) 
	@echo 'Invoking: Converter'
	@echo 'Building target:'
	@echo Converterrx64m_rsk.tmp=
	@sed -e "s/^/    /" "Converterrx64m_rsk.tmp"
	rlink   "rx64m_rsk.abs" -subcommand="Converterrx64m_rsk.tmp"
	@echo 'Finished building target:'
	@echo.


rx64m_rsk.abs: $(OBJS)  $(ALL_ASMS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)   \
C:\Users\User\Desktop\TEST\rx64m_rsk\r_t4_rx\lib\T4_Library_rxv1_ether_little.lib
	@echo 'Invoking: Linker'
	@echo Linkerrx64m_rsk.tmp=
	@sed -e "s/^/    /" "Linkerrx64m_rsk.tmp"
	rlink -subcommand="Linkerrx64m_rsk.tmp"
	@echo 'Finished building:'
	@echo.


rx64m_rsk.lib: 
	@echo 'Invoking: Library Generator'
	@echo LibraryGeneratorrx64m_rsk.tmp=
	@sed -e "s/^/    /" "LibraryGeneratorrx64m_rsk.tmp"
	lbgrx -subcommand="LibraryGeneratorrx64m_rsk.tmp"
	@echo 'Finished building:'
	@echo.

rx64m_rsk.x: rx64m_rsk.abs
		-C:\Renesas\e2_studio\eclipse\/../\Utilities\\ccrx\renesas_cc_converter.exe rx64m_rsk.abs rx64m_rsk.x

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	-rm -rf r_bsp/mcu/rx64m/*.obj r_bsp/mcu/rx64m/*.d r_bsp/mcu/rx64m/*.asm r_bsp/mcu/rx64m/*.p r_bsp/mcu/rx64m/*.src r_bsp/mcu/rx64m/*.jmp r_bsp/mcu/rx64m/*.lst r_bsp/mcu/rx64m/*.prn 
	-rm -rf src/tcp_blocking_sample/*.obj src/tcp_blocking_sample/*.d src/tcp_blocking_sample/*.asm src/tcp_blocking_sample/*.p src/tcp_blocking_sample/*.src src/tcp_blocking_sample/*.jmp src/tcp_blocking_sample/*.lst src/tcp_blocking_sample/*.prn 
	-rm -rf r_ether_rx/src/targets/rx64m/*.obj r_ether_rx/src/targets/rx64m/*.d r_ether_rx/src/targets/rx64m/*.asm r_ether_rx/src/targets/rx64m/*.p r_ether_rx/src/targets/rx64m/*.src r_ether_rx/src/targets/rx64m/*.jmp r_ether_rx/src/targets/rx64m/*.lst r_ether_rx/src/targets/rx64m/*.prn 
	-rm -rf src/*.obj src/*.d src/*.asm src/*.p src/*.src src/*.jmp src/*.lst src/*.prn 
	-rm -rf r_t4_driver_rx/src/*.obj r_t4_driver_rx/src/*.d r_t4_driver_rx/src/*.asm r_t4_driver_rx/src/*.p r_t4_driver_rx/src/*.src r_t4_driver_rx/src/*.jmp r_t4_driver_rx/src/*.lst r_t4_driver_rx/src/*.prn 
	-rm -rf r_pincfg/*.obj r_pincfg/*.d r_pincfg/*.asm r_pincfg/*.p r_pincfg/*.src r_pincfg/*.jmp r_pincfg/*.lst r_pincfg/*.prn 
	-rm -rf r_cmt_rx/src/*.obj r_cmt_rx/src/*.d r_cmt_rx/src/*.asm r_cmt_rx/src/*.p r_cmt_rx/src/*.src r_cmt_rx/src/*.jmp r_cmt_rx/src/*.lst r_cmt_rx/src/*.prn 
	-rm -rf r_ether_rx/src/*.obj r_ether_rx/src/*.d r_ether_rx/src/*.asm r_ether_rx/src/*.p r_ether_rx/src/*.src r_ether_rx/src/*.jmp r_ether_rx/src/*.lst r_ether_rx/src/*.prn 
	-rm -rf r_sys_time_rx/src/*.obj r_sys_time_rx/src/*.d r_sys_time_rx/src/*.asm r_sys_time_rx/src/*.p r_sys_time_rx/src/*.src r_sys_time_rx/src/*.jmp r_sys_time_rx/src/*.lst r_sys_time_rx/src/*.prn 
	-rm -rf r_ether_rx/src/phy/*.obj r_ether_rx/src/phy/*.d r_ether_rx/src/phy/*.asm r_ether_rx/src/phy/*.p r_ether_rx/src/phy/*.src r_ether_rx/src/phy/*.jmp r_ether_rx/src/phy/*.lst r_ether_rx/src/phy/*.prn 
	-rm -rf r_bsp/board/rskrx64m/*.obj r_bsp/board/rskrx64m/*.d r_bsp/board/rskrx64m/*.asm r_bsp/board/rskrx64m/*.p r_bsp/board/rskrx64m/*.src r_bsp/board/rskrx64m/*.jmp r_bsp/board/rskrx64m/*.lst r_bsp/board/rskrx64m/*.prn 
	-rm -rf r_bsp/mcu/all/*.obj r_bsp/mcu/all/*.d r_bsp/mcu/all/*.asm r_bsp/mcu/all/*.p r_bsp/mcu/all/*.src r_bsp/mcu/all/*.jmp r_bsp/mcu/all/*.lst r_bsp/mcu/all/*.prn 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets