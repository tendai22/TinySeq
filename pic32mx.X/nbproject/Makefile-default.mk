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
SOURCEFILES_QUOTED_IF_SPACED=../zForth/forth/core.c main-pic32mx.c ../xprintf/src/xprintf.c ../zForth/src/zforth/zforth.c ../zForth/src/zforth/zmain.c ../tinyseq/tinyseq.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1100060544/core.o ${OBJECTDIR}/main-pic32mx.o ${OBJECTDIR}/_ext/1363085609/xprintf.o ${OBJECTDIR}/_ext/1502618027/zforth.o ${OBJECTDIR}/_ext/1502618027/zmain.o ${OBJECTDIR}/_ext/1302072336/tinyseq.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1100060544/core.o.d ${OBJECTDIR}/main-pic32mx.o.d ${OBJECTDIR}/_ext/1363085609/xprintf.o.d ${OBJECTDIR}/_ext/1502618027/zforth.o.d ${OBJECTDIR}/_ext/1502618027/zmain.o.d ${OBJECTDIR}/_ext/1302072336/tinyseq.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1100060544/core.o ${OBJECTDIR}/main-pic32mx.o ${OBJECTDIR}/_ext/1363085609/xprintf.o ${OBJECTDIR}/_ext/1502618027/zforth.o ${OBJECTDIR}/_ext/1502618027/zmain.o ${OBJECTDIR}/_ext/1302072336/tinyseq.o

# Source Files
SOURCEFILES=../zForth/forth/core.c main-pic32mx.c ../xprintf/src/xprintf.c ../zForth/src/zforth/zforth.c ../zForth/src/zforth/zmain.c ../tinyseq/tinyseq.c



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

MP_PROCESSOR_OPTION=32MX220F032B
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
${OBJECTDIR}/_ext/1100060544/core.o: ../zForth/forth/core.c  .generated_files/flags/default/3e4768f34aa57d607af6965dbdb2fe959e2f28a8 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1100060544" 
	@${RM} ${OBJECTDIR}/_ext/1100060544/core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1100060544/core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1100060544/core.o.d" -o ${OBJECTDIR}/_ext/1100060544/core.o ../zForth/forth/core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main-pic32mx.o: main-pic32mx.c  .generated_files/flags/default/faf4814584c4706ce34d3a9fd3148ee8330e349d .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main-pic32mx.o.d 
	@${RM} ${OBJECTDIR}/main-pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/main-pic32mx.o.d" -o ${OBJECTDIR}/main-pic32mx.o main-pic32mx.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1363085609/xprintf.o: ../xprintf/src/xprintf.c  .generated_files/flags/default/d5e449c26ed46d30116e777c21012c979fbef32a .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1363085609" 
	@${RM} ${OBJECTDIR}/_ext/1363085609/xprintf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1363085609/xprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1363085609/xprintf.o.d" -o ${OBJECTDIR}/_ext/1363085609/xprintf.o ../xprintf/src/xprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1502618027/zforth.o: ../zForth/src/zforth/zforth.c  .generated_files/flags/default/1ec5129f1ce21ad6e3ced65af27cfffcebe98aea .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1502618027" 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zforth.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zforth.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1502618027/zforth.o.d" -o ${OBJECTDIR}/_ext/1502618027/zforth.o ../zForth/src/zforth/zforth.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1502618027/zmain.o: ../zForth/src/zforth/zmain.c  .generated_files/flags/default/aecc499fec60acbce2dbf83ff04384ef46d5468a .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1502618027" 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zmain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zmain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1502618027/zmain.o.d" -o ${OBJECTDIR}/_ext/1502618027/zmain.o ../zForth/src/zforth/zmain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1302072336/tinyseq.o: ../tinyseq/tinyseq.c  .generated_files/flags/default/e66c95e54589d29b05cca80664e33592ea7f83ce .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1302072336" 
	@${RM} ${OBJECTDIR}/_ext/1302072336/tinyseq.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302072336/tinyseq.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1302072336/tinyseq.o.d" -o ${OBJECTDIR}/_ext/1302072336/tinyseq.o ../tinyseq/tinyseq.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1100060544/core.o: ../zForth/forth/core.c  .generated_files/flags/default/91d3bca3ab00e8649a89a0e997f48f8c2bd6ae28 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1100060544" 
	@${RM} ${OBJECTDIR}/_ext/1100060544/core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1100060544/core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1100060544/core.o.d" -o ${OBJECTDIR}/_ext/1100060544/core.o ../zForth/forth/core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main-pic32mx.o: main-pic32mx.c  .generated_files/flags/default/b6c9d4d28acc1b17f7b893d4a26ad050f25e820d .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main-pic32mx.o.d 
	@${RM} ${OBJECTDIR}/main-pic32mx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/main-pic32mx.o.d" -o ${OBJECTDIR}/main-pic32mx.o main-pic32mx.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1363085609/xprintf.o: ../xprintf/src/xprintf.c  .generated_files/flags/default/c9b6e2f802cb8538173ea268b6cd4799df71b919 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1363085609" 
	@${RM} ${OBJECTDIR}/_ext/1363085609/xprintf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1363085609/xprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1363085609/xprintf.o.d" -o ${OBJECTDIR}/_ext/1363085609/xprintf.o ../xprintf/src/xprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1502618027/zforth.o: ../zForth/src/zforth/zforth.c  .generated_files/flags/default/dfddb8af6483306e2139f0cd9e28d218b3fa219a .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1502618027" 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zforth.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zforth.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1502618027/zforth.o.d" -o ${OBJECTDIR}/_ext/1502618027/zforth.o ../zForth/src/zforth/zforth.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1502618027/zmain.o: ../zForth/src/zforth/zmain.c  .generated_files/flags/default/638d9a8564d42fb85343f8c3434b2070629c3571 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1502618027" 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zmain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1502618027/zmain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1502618027/zmain.o.d" -o ${OBJECTDIR}/_ext/1502618027/zmain.o ../zForth/src/zforth/zmain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1302072336/tinyseq.o: ../tinyseq/tinyseq.c  .generated_files/flags/default/fcb06b693205823936030b7b54fa60d691a6b6f7 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1302072336" 
	@${RM} ${OBJECTDIR}/_ext/1302072336/tinyseq.o.d 
	@${RM} ${OBJECTDIR}/_ext/1302072336/tinyseq.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"../zForth/src/zforth" -I"../xprintf/src" -I"../tinyseq" -MP -MMD -MF "${OBJECTDIR}/_ext/1302072336/tinyseq.o.d" -o ${OBJECTDIR}/_ext/1302072336/tinyseq.o ../tinyseq/tinyseq.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/pic32mx.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
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
