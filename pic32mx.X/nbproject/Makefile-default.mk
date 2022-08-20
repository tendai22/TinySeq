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
FINAL_IMAGE=${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../zForth/forth/core.c main-pic32mx.c ../xprintf/src/xprintf.c ../zForth/src/zforth/zforth.c ../zForth/src/zforth/zmain.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1100060544/core.o ${OBJECTDIR}/main-pic32mx.o ${OBJECTDIR}/_ext/1363085609/xprintf.o ${OBJECTDIR}/_ext/1502618027/zforth.o ${OBJECTDIR}/_ext/1502618027/zmain.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1100060544/core.o.d ${OBJECTDIR}/main-pic32mx.o.d ${OBJECTDIR}/_ext/1363085609/xprintf.o.d ${OBJECTDIR}/_ext/1502618027/zforth.o.d ${OBJECTDIR}/_ext/1502618027/zmain.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1100060544/core.o ${OBJECTDIR}/main-pic32mx.o ${OBJECTDIR}/_ext/1363085609/xprintf.o ${OBJECTDIR}/_ext/1502618027/zforth.o ${OBJECTDIR}/_ext/1502618027/zmain.o

# Source Files
SOURCEFILES=../zForth/forth/core.c main-pic32mx.c ../xprintf/src/xprintf.c ../zForth/src/zforth/zforth.c ../zForth/src/zforth/zmain.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1100060544/core.o: ../zForth/forth/core.c  .generated_files/flags/default/e72a0cfe4e967fe5e1de654a49a946c0149edfa8 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1100060544" 
	@${RM} ${OBJECTDIR}/_ext/1100060544/core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1100060544/core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1100060544/core.o.d" -o ${OBJECTDIR}/_ext/1100060544/core.o ../zForth/forth/core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main-pic32mx.o: main-pic32mx.c  .generated_files/flags/default/2a353c0c9efb96569ba026f7de687f3c0fc672aa .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main-pic32mx.o.d 
	@${RM} ${OBJECTDIR}/main-pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/main-pic32mx.o.d" -o ${OBJECTDIR}/main-pic32mx.o main-pic32mx.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1363085609/xprintf.o: ../xprintf/src/xprintf.c  .generated_files/flags/default/a68e21c05ca6c98b4397869c29b726b04fc4dfc3 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1363085609" 
	@${RM} ${OBJECTDIR}/_ext/1363085609/xprintf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1363085609/xprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1363085609/xprintf.o.d" -o ${OBJECTDIR}/_ext/1363085609/xprintf.o ../xprintf/src/xprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1502618027/zforth.o: ../zForth/src/zforth/zforth.c  .generated_files/flags/default/2c053d2a50fba0076ac06d79b8db2329199526de .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1502618027" 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zforth.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zforth.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1502618027/zforth.o.d" -o ${OBJECTDIR}/_ext/1502618027/zforth.o ../zForth/src/zforth/zforth.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1502618027/zmain.o: ../zForth/src/zforth/zmain.c  .generated_files/flags/default/db27321bbcb58ede58208dfa808cbcc006af8b62 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1502618027" 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zmain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zmain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1502618027/zmain.o.d" -o ${OBJECTDIR}/_ext/1502618027/zmain.o ../zForth/src/zforth/zmain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1100060544/core.o: ../zForth/forth/core.c  .generated_files/flags/default/4a267e17e3064cdf35b17af3ed2a1cb47f4572f8 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1100060544" 
	@${RM} ${OBJECTDIR}/_ext/1100060544/core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1100060544/core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1100060544/core.o.d" -o ${OBJECTDIR}/_ext/1100060544/core.o ../zForth/forth/core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main-pic32mx.o: main-pic32mx.c  .generated_files/flags/default/284d8e5584444aa6b1ec068b8d9e16bf28fd29d4 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main-pic32mx.o.d 
	@${RM} ${OBJECTDIR}/main-pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/main-pic32mx.o.d" -o ${OBJECTDIR}/main-pic32mx.o main-pic32mx.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1363085609/xprintf.o: ../xprintf/src/xprintf.c  .generated_files/flags/default/c71883ac3c1578f6e413318d9370c0773ff7867e .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1363085609" 
	@${RM} ${OBJECTDIR}/_ext/1363085609/xprintf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1363085609/xprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1363085609/xprintf.o.d" -o ${OBJECTDIR}/_ext/1363085609/xprintf.o ../xprintf/src/xprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1502618027/zforth.o: ../zForth/src/zforth/zforth.c  .generated_files/flags/default/5d0561748d177587b41acf011c54e8b818b35166 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1502618027" 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zforth.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zforth.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1502618027/zforth.o.d" -o ${OBJECTDIR}/_ext/1502618027/zforth.o ../zForth/src/zforth/zforth.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1502618027/zmain.o: ../zForth/src/zforth/zmain.c  .generated_files/flags/default/1183a916433a4ea2269be5e03305dda802f829a2 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1502618027" 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zmain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zmain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1502618027/zmain.o.d" -o ${OBJECTDIR}/_ext/1502618027/zmain.o ../zForth/src/zforth/zmain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
