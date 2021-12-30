;/*******************************************************************************
; * Copyright (c) baifeiq.
; * 
; * @date            @author         @brief
; * 2021-07-12       baifeiq         First version: Handling the switch of ByOs system context.
; * 2021-12-30       baifeiq         Reorganize the coding style
; */

        MODULE osContext

        PUBLIC PendSV_Handler
        PUBLIC SysTick_Handler
        PUBLIC InitRAM
        PUBLIC os_tTaskRunFirst
        PUBLIC os_trigerPendSVC
        SECTION osContext:CODE(2)

        THUMB
        
PendSV_Handler
        IMPORT currentTask
        IMPORT nextTask

        MRS R0, PSP 
        CBZ R0, PendSVHander_nosave
    
        STMDB   R0!, {R4-R11}
        LDR R1, =currentTask
        LDR R1, [R1]
        STR R0, [R1]
        NOP
    
PendSVHander_nosave
        LDR R0, =currentTask
        LDR R1, =nextTask
        LDR R2, [R1]
        STR R2, [R0]

        LDR R0, [R2]
        LDMIA R0!,  {R4-R11}

        MSR PSP, R0
        ORR LR, LR, #0X04
        BX LR
     
SysTick_Handler
        IMPORT os_scheduler
        PUSH {LR}
        BL os_scheduler
        POP {LR}
        NOP
        BX LR
        
InitRAM
RAM_START       EQU 0x20000000
RAM_END         EQU 0x2001FFFF
        MOV R0, #0
        MOV32 R1, #RAM_START
        ;MOVW  R1, #0X0
        ;MOVT  R1, #0X2000
        MOV32 R2, #RAM_END
        ;MOVW  R2, #0XFFFF
        ;MOVT  R2, #0X2001

.Loop   STMIA.W R1!, {R0} 
        CMP R2, R1    
        BHI    .Loop    
        BX LR

NVIC_INT_CTRL		EQU	0xE000ED04
NVIC_PENDSVSET		EQU	0x10000000
NVIC_SYSPRI2		EQU	0xE000ED22
NVIC_PENDSV_PRI		EQU	0x000000FF

os_tTaskRunFirst
        MOV r0, #0
        MSR PSP, r0

os_trigerPendSVC
        MOV r0, #NVIC_PENDSV_PRI
        MOV32 r1, #NVIC_SYSPRI2
        ;MOVW r1, #0xED22
        ;MOVT r1, #0xE000
        STRB r0, [r1]

        MOV32 r0, #NVIC_PENDSVSET
        ;MOVW R0, #0X0
        ;MOVT R0, #0x1000
        MOV32 r1, #NVIC_INT_CTRL
        ;MOVW R1, #0XED04
        ;MOVT R1, #0xE000
        STR r0, [r1]  

        BX LR           
     
        END