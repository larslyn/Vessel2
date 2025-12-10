# ST Visual Debugger Generated MAKE File, based on EeGrass.stp

ifeq ($(CFG), )
CFG=Release
$(warning ***No configuration specified. Defaulting to $(CFG)***)
endif

ToolsetRoot=§È
ToolsetBin=C:\Program Files (x86)\COSMIC\32K_Compilers
ToolsetInc=C:\Program Files (x86)\COSMIC\32K_Compilers\Hstm8
ToolsetLib=C:\Program Files (x86)\COSMIC\32K_Compilers\Lib
ToolsetIncOpts=-i"C:\Program Files (x86)\COSMIC\32K_Compilers\Hstm8" 
ToolsetLibOpts=-l"C:\Program Files (x86)\COSMIC\32K_Compilers\Lib" 
ObjectExt=o
OutputExt=elf
InputName=$(basename $(notdir $<))


# 
# Debug
# 
ifeq "$(CFG)" "Debug"


OutputPath=Debug
ProjectSFile=EeGrass
TargetSName=06_3300
TargetFName=06_3300.elf
IntermPath=$(dir $@)
CFLAGS_PRJ=$(ToolsetBin)\cxstm8  +warn +modsl0 +debug -pxp -no -pp -l -istack\inc -irtu\inc -iinc $(ToolsetIncOpts) -cl$(IntermPath:%\=%) -co$(IntermPath:%\=%) $<
ASMFLAGS_PRJ=$(ToolsetBin)\castm8  -xx -l $(ToolsetIncOpts) -o$(IntermPath)$(InputName).$(ObjectExt) $<

all : $(OutputPath) 06_3300.elf

$(OutputPath) : 
	if not exist $(OutputPath)/ mkdir $(OutputPath)

Debug\eeprom.$(ObjectExt) : src\eeprom.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_type.h inc\stm8s.h inc\stm8s_conf.h stack\inc\s_od.h inc\eeprom.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\encoder.$(ObjectExt) : src\encoder.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8_hw.h inc\stm8s_type.h inc\stm8s_gpio.h inc\stm8s.h inc\stm8s_conf.h inc\encoder.h stack\inc\s_od.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\main.$(ObjectExt) : src\main.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h inc\stm8s_gpio.h inc\eeprom.h inc\stm8s_rs485.h inc\stm8s_iwdg.h stack\inc\s_mb.h inc\stm8_hw.h stack\inc\s_od.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8_hw.$(ObjectExt) : src\stm8_hw.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_type.h inc\stm8_hw.h inc\stm8s_gpio.h inc\stm8s.h inc\stm8s_conf.h inc\stm8s_exti.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8s_exti.$(ObjectExt) : src\stm8s_exti.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_exti.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8s_gpio.$(ObjectExt) : src\stm8s_gpio.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_gpio.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8s_iwdg.$(ObjectExt) : src\stm8s_iwdg.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_iwdg.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8s_rs485.$(ObjectExt) : src\stm8s_rs485.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_type.h inc\stm8s.h inc\stm8s_conf.h inc\stm8s_gpio.h inc\stm8s_rs485.h inc\stm8_hw.h rtu\inc\s_mbrtu.h stack\inc\s_mb.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\stm8_interrupt_vector.$(ObjectExt) : stm8_interrupt_vector.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\encoder.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h inc\stm8s_rs485.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\s_mbcrc.$(ObjectExt) : rtu\src\s_mbcrc.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_type.h rtu\inc\s_mbcrc.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\s_mbrtu.$(ObjectExt) : rtu\src\s_mbrtu.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_type.h inc\stm8s_rs485.h inc\stm8s.h inc\stm8s_conf.h stack\inc\s_mb.h rtu\inc\s_mbrtu.h stack\inc\s_portevent.h rtu\inc\s_mbcrc.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\s_mb.$(ObjectExt) : stack\src\s_mb.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stdlib.h ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\string.h inc\eeprom.h inc\stm8s_type.h inc\stm8s_rs485.h inc\stm8s.h inc\stm8s_conf.h stack\inc\s_mbconfig.h stack\inc\s_mbproto.h stack\inc\s_portevent.h stack\inc\s_mb.h rtu\inc\s_mbrtu.h stack\inc\s_od.h stack\inc\s_mbfunc.h rtu\inc\s_mbcrc.h inc\encoder.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\s_mbfuncholding.$(ObjectExt) : stack\src\s_mbfuncholding.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stdlib.h ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\string.h stack\inc\s_mb.h inc\stm8s_rs485.h inc\stm8s_type.h inc\stm8s.h inc\stm8s_conf.h stack\inc\s_mbconfig.h stack\inc\s_mbproto.h stack\inc\s_od.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\s_od.$(ObjectExt) : stack\src\s_od.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_type.h stack\inc\s_od.h stack\inc\s_mb.h inc\stm8s_rs485.h inc\stm8s.h inc\stm8s_conf.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Debug\s_portevent.$(ObjectExt) : stack\src\s_portevent.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\modsl0.h inc\stm8s_type.h stack\inc\s_portevent.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

06_3300.elf :  $(OutputPath)\eeprom.o $(OutputPath)\encoder.o $(OutputPath)\main.o $(OutputPath)\stm8_hw.o $(OutputPath)\stm8s_exti.o $(OutputPath)\stm8s_gpio.o $(OutputPath)\stm8s_iwdg.o $(OutputPath)\stm8s_rs485.o $(OutputPath)\stm8_interrupt_vector.o $(OutputPath)\s_mbcrc.o $(OutputPath)\s_mbrtu.o $(OutputPath)\s_mb.o $(OutputPath)\s_mbfuncholding.o $(OutputPath)\s_od.o $(OutputPath)\s_portevent.o $(OutputPath)\06_3300.lkf
	$(ToolsetBin)\clnk  $(ToolsetLibOpts) -o $(OutputPath)\$(TargetSName).sm8 -m$(OutputPath)\$(TargetSName).map $(OutputPath)\$(TargetSName).lkf 
	$(ToolsetBin)\cvdwarf  $(OutputPath)\$(TargetSName).sm8

	$(ToolsetBin)\chex  -o $(OutputPath)\$(TargetSName).s19 $(OutputPath)\$(TargetSName).sm8
clean : 
	-@erase $(OutputPath)\eeprom.o
	-@erase $(OutputPath)\encoder.o
	-@erase $(OutputPath)\main.o
	-@erase $(OutputPath)\stm8_hw.o
	-@erase $(OutputPath)\stm8s_exti.o
	-@erase $(OutputPath)\stm8s_gpio.o
	-@erase $(OutputPath)\stm8s_iwdg.o
	-@erase $(OutputPath)\stm8s_rs485.o
	-@erase $(OutputPath)\stm8_interrupt_vector.o
	-@erase $(OutputPath)\s_mbcrc.o
	-@erase $(OutputPath)\s_mbrtu.o
	-@erase $(OutputPath)\s_mb.o
	-@erase $(OutputPath)\s_mbfuncholding.o
	-@erase $(OutputPath)\s_od.o
	-@erase $(OutputPath)\s_portevent.o
	-@erase $(OutputPath)\06_3300.elf
	-@erase $(OutputPath)\06_3300.elf
	-@erase $(OutputPath)\06_3300.map
	-@erase $(OutputPath)\eeprom.ls
	-@erase $(OutputPath)\encoder.ls
	-@erase $(OutputPath)\main.ls
	-@erase $(OutputPath)\stm8_hw.ls
	-@erase $(OutputPath)\stm8s_exti.ls
	-@erase $(OutputPath)\stm8s_gpio.ls
	-@erase $(OutputPath)\stm8s_iwdg.ls
	-@erase $(OutputPath)\stm8s_rs485.ls
	-@erase $(OutputPath)\stm8_interrupt_vector.ls
	-@erase $(OutputPath)\s_mbcrc.ls
	-@erase $(OutputPath)\s_mbrtu.ls
	-@erase $(OutputPath)\s_mb.ls
	-@erase $(OutputPath)\s_mbfuncholding.ls
	-@erase $(OutputPath)\s_od.ls
	-@erase $(OutputPath)\s_portevent.ls
endif

# 
# Release
# 
ifeq "$(CFG)" "Release"


OutputPath=Release
ProjectSFile=EeGrass
TargetSName=06_3300
TargetFName=06_3300.elf
IntermPath=$(dir $@)
CFLAGS_PRJ=$(ToolsetBin)\cxstm8  +mods -pp -l -istack\inc -irtu\inc -iinc $(ToolsetIncOpts) -cl$(IntermPath:%\=%) -co$(IntermPath:%\=%) $<
ASMFLAGS_PRJ=$(ToolsetBin)\castm8  $(ToolsetIncOpts) -o$(IntermPath)$(InputName).$(ObjectExt) $<

all : $(OutputPath) 06_3300.elf

$(OutputPath) : 
	if not exist $(OutputPath)/ mkdir $(OutputPath)

Release\eeprom.$(ObjectExt) : src\eeprom.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_type.h inc\stm8s.h inc\stm8s_conf.h stack\inc\s_od.h inc\eeprom.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\encoder.$(ObjectExt) : src\encoder.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8_hw.h inc\stm8s_type.h inc\stm8s_gpio.h inc\stm8s.h inc\stm8s_conf.h inc\encoder.h stack\inc\s_od.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\main.$(ObjectExt) : src\main.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h inc\stm8s_gpio.h inc\eeprom.h inc\stm8s_rs485.h inc\stm8s_iwdg.h stack\inc\s_mb.h inc\stm8_hw.h stack\inc\s_od.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8_hw.$(ObjectExt) : src\stm8_hw.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_type.h inc\stm8_hw.h inc\stm8s_gpio.h inc\stm8s.h inc\stm8s_conf.h inc\stm8s_exti.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_exti.$(ObjectExt) : src\stm8s_exti.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_exti.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_gpio.$(ObjectExt) : src\stm8s_gpio.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_gpio.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_iwdg.$(ObjectExt) : src\stm8s_iwdg.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_iwdg.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_rs485.$(ObjectExt) : src\stm8s_rs485.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_type.h inc\stm8s.h inc\stm8s_conf.h inc\stm8s_gpio.h inc\stm8s_rs485.h inc\stm8_hw.h rtu\inc\s_mbrtu.h stack\inc\s_mb.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8_interrupt_vector.$(ObjectExt) : stm8_interrupt_vector.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\encoder.h inc\stm8s.h inc\stm8s_type.h inc\stm8s_conf.h inc\stm8s_rs485.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\s_mbcrc.$(ObjectExt) : rtu\src\s_mbcrc.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_type.h rtu\inc\s_mbcrc.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\s_mbrtu.$(ObjectExt) : rtu\src\s_mbrtu.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_type.h inc\stm8s_rs485.h inc\stm8s.h inc\stm8s_conf.h stack\inc\s_mb.h rtu\inc\s_mbrtu.h stack\inc\s_portevent.h rtu\inc\s_mbcrc.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\s_mb.$(ObjectExt) : stack\src\s_mb.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stdlib.h ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\string.h inc\eeprom.h inc\stm8s_type.h inc\stm8s_rs485.h inc\stm8s.h inc\stm8s_conf.h stack\inc\s_mbconfig.h stack\inc\s_mbproto.h stack\inc\s_portevent.h stack\inc\s_mb.h rtu\inc\s_mbrtu.h stack\inc\s_od.h stack\inc\s_mbfunc.h rtu\inc\s_mbcrc.h inc\encoder.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\s_mbfuncholding.$(ObjectExt) : stack\src\s_mbfuncholding.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\stdlib.h ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\string.h stack\inc\s_mb.h inc\stm8s_rs485.h inc\stm8s_type.h inc\stm8s.h inc\stm8s_conf.h stack\inc\s_mbconfig.h stack\inc\s_mbproto.h stack\inc\s_od.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\s_od.$(ObjectExt) : stack\src\s_od.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_type.h stack\inc\s_od.h stack\inc\s_mb.h inc\stm8s_rs485.h inc\stm8s.h inc\stm8s_conf.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\s_portevent.$(ObjectExt) : stack\src\s_portevent.c ..\..\..\..\..\..\..\..\PROGRA~2\cosmic\FSE_CO~1\cxstm8\hstm8\mods.h inc\stm8s_type.h stack\inc\s_portevent.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

06_3300.elf :  $(OutputPath)\eeprom.o $(OutputPath)\encoder.o $(OutputPath)\main.o $(OutputPath)\stm8_hw.o $(OutputPath)\stm8s_exti.o $(OutputPath)\stm8s_gpio.o $(OutputPath)\stm8s_iwdg.o $(OutputPath)\stm8s_rs485.o $(OutputPath)\stm8_interrupt_vector.o $(OutputPath)\s_mbcrc.o $(OutputPath)\s_mbrtu.o $(OutputPath)\s_mb.o $(OutputPath)\s_mbfuncholding.o $(OutputPath)\s_od.o $(OutputPath)\s_portevent.o $(OutputPath)\06_3300.lkf
	$(ToolsetBin)\clnk  $(ToolsetLibOpts) -o $(OutputPath)\$(TargetSName).sm8 $(OutputPath)\$(TargetSName).lkf 
	$(ToolsetBin)\cvdwarf  $(OutputPath)\$(TargetSName).sm8

	$(ToolsetBin)\chex  -o $(OutputPath)\$(TargetSName).s19 $(OutputPath)\$(TargetSName).sm8
clean : 
	-@erase $(OutputPath)\eeprom.o
	-@erase $(OutputPath)\encoder.o
	-@erase $(OutputPath)\main.o
	-@erase $(OutputPath)\stm8_hw.o
	-@erase $(OutputPath)\stm8s_exti.o
	-@erase $(OutputPath)\stm8s_gpio.o
	-@erase $(OutputPath)\stm8s_iwdg.o
	-@erase $(OutputPath)\stm8s_rs485.o
	-@erase $(OutputPath)\stm8_interrupt_vector.o
	-@erase $(OutputPath)\s_mbcrc.o
	-@erase $(OutputPath)\s_mbrtu.o
	-@erase $(OutputPath)\s_mb.o
	-@erase $(OutputPath)\s_mbfuncholding.o
	-@erase $(OutputPath)\s_od.o
	-@erase $(OutputPath)\s_portevent.o
	-@erase $(OutputPath)\06_3300.elf
	-@erase $(OutputPath)\06_3300.elf
	-@erase $(OutputPath)\eeprom.ls
	-@erase $(OutputPath)\encoder.ls
	-@erase $(OutputPath)\main.ls
	-@erase $(OutputPath)\stm8_hw.ls
	-@erase $(OutputPath)\stm8s_exti.ls
	-@erase $(OutputPath)\stm8s_gpio.ls
	-@erase $(OutputPath)\stm8s_iwdg.ls
	-@erase $(OutputPath)\stm8s_rs485.ls
	-@erase $(OutputPath)\stm8_interrupt_vector.ls
	-@erase $(OutputPath)\s_mbcrc.ls
	-@erase $(OutputPath)\s_mbrtu.ls
	-@erase $(OutputPath)\s_mb.ls
	-@erase $(OutputPath)\s_mbfuncholding.ls
	-@erase $(OutputPath)\s_od.ls
	-@erase $(OutputPath)\s_portevent.ls
endif
