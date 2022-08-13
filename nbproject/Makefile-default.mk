#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/TinySeq.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/TinySeq.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c zForth/src/zforth/zforth.c zForth/src/pic32mx/zmain.c zForth/forth/core.c xprintf/src/xprintf.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/zForth/src/zforth/zforth.o ${OBJECTDIR}/zForth/src/pic32mx/zmain.o ${OBJECTDIR}/zForth/forth/core.o ${OBJECTDIR}/xprintf/src/xprintf.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/zForth/src/zforth/zforth.o.d ${OBJECTDIR}/zForth/src/pic32mx/zmain.o.d ${OBJECTDIR}/zForth/forth/core.o.d ${OBJECTDIR}/xprintf/src/xprintf.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/zForth/src/zforth/zforth.o ${OBJECTDIR}/zForth/src/pic32mx/zmain.o ${OBJECTDIR}/zForth/forth/core.o ${OBJECTDIR}/xprintf/src/xprintf.o

# Source Files
SOURCEFILES=main.c zForth/src/zforth/zforth.c zForth/src/pic32mx/zmain.c zForth/forth/core.c xprintf/src/xprintf.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/TinySeq.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX270F256B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/fc91332bbd5cd6c78d56ca55d729462b1205f6e6 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/zForth/src/zforth/zforth.o: zForth/src/zforth/zforth.c  .generated_files/flags/default/d45adb6ce5b95e91371f9e25b4260819b2308fd0 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/zForth/src/zforth" 
	@${RM} ${OBJECTDIR}/zForth/src/zforth/zforth.o.d 
	@${RM} ${OBJECTDIR}/zForth/src/zforth/zforth.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/zForth/src/zforth/zforth.o.d" -o ${OBJECTDIR}/zForth/src/zforth/zforth.o zForth/src/zforth/zforth.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/zForth/src/pic32mx/zmain.o: zForth/src/pic32mx/zmain.c  .generated_files/flags/default/45e6df02af8d4a3fdeb9407abb199a1da80e6618 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/zForth/src/pic32mx" 
	@${RM} ${OBJECTDIR}/zForth/src/pic32mx/zmain.o.d 
	@${RM} ${OBJECTDIR}/zForth/src/pic32mx/zmain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/zForth/src/pic32mx/zmain.o.d" -o ${OBJECTDIR}/zForth/src/pic32mx/zmain.o zForth/src/pic32mx/zmain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/zForth/forth/core.o: zForth/forth/core.c  .generated_files/flags/default/ca7fac583eb532d71ad7d54de6f4cd36c5cfdcea .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/zForth/forth" 
	@${RM} ${OBJECTDIR}/zForth/forth/core.o.d 
	@${RM} ${OBJECTDIR}/zForth/forth/core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/zForth/forth/core.o.d" -o ${OBJECTDIR}/zForth/forth/core.o zForth/forth/core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/xprintf/src/xprintf.o: xprintf/src/xprintf.c  .generated_files/flags/default/971dd218a8d6f4e8a90b89bfec4d686801ee5abe .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/xprintf/src" 
	@${RM} ${OBJECTDIR}/xprintf/src/xprintf.o.d 
	@${RM} ${OBJECTDIR}/xprintf/src/xprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/xprintf/src/xprintf.o.d" -o ${OBJECTDIR}/xprintf/src/xprintf.o xprintf/src/xprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/61857ef0f3dce2ff8b24e01293cbad9b080363e9 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/zForth/src/zforth/zforth.o: zForth/src/zforth/zforth.c  .generated_files/flags/default/de9cbf353c97a5eb46a6053fda8d93a4646f677f .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/zForth/src/zforth" 
	@${RM} ${OBJECTDIR}/zForth/src/zforth/zforth.o.d 
	@${RM} ${OBJECTDIR}/zForth/src/zforth/zforth.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/zForth/src/zforth/zforth.o.d" -o ${OBJECTDIR}/zForth/src/zforth/zforth.o zForth/src/zforth/zforth.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/zForth/src/pic32mx/zmain.o: zForth/src/pic32mx/zmain.c  .generated_files/flags/default/c933f1a924091751667fb9e2416a1d54395fabd6 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/zForth/src/pic32mx" 
	@${RM} ${OBJECTDIR}/zForth/src/pic32mx/zmain.o.d 
	@${RM} ${OBJECTDIR}/zForth/src/pic32mx/zmain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/zForth/src/pic32mx/zmain.o.d" -o ${OBJECTDIR}/zForth/src/pic32mx/zmain.o zForth/src/pic32mx/zmain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/zForth/forth/core.o: zForth/forth/core.c  .generated_files/flags/default/706415ecc85b37c3dd1184f7b0020f6cdbfd349 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/zForth/forth" 
	@${RM} ${OBJECTDIR}/zForth/forth/core.o.d 
	@${RM} ${OBJECTDIR}/zForth/forth/core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/zForth/forth/core.o.d" -o ${OBJECTDIR}/zForth/forth/core.o zForth/forth/core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/xprintf/src/xprintf.o: xprintf/src/xprintf.c  .generated_files/flags/default/c330b36736c8b01f0fd43b6d52c8edc2103a6a98 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/xprintf/src" 
	@${RM} ${OBJECTDIR}/xprintf/src/xprintf.o.d 
	@${RM} ${OBJECTDIR}/xprintf/src/xprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"zForth/src/pic32mx" -I"zForth/src/zforth" -I"xprintf/src" -MP -MMD -MF "${OBJECTDIR}/xprintf/src/xprintf.o.d" -o ${OBJECTDIR}/xprintf/src/xprintf.o xprintf/src/xprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/TinySeq.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/TinySeq.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/TinySeq.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/TinySeq.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/TinySeq.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
