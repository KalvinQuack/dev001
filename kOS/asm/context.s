
    IMPORT scheduler
    IMPORT running
    IMPORT next
    PUBLIC tswitch
    SECTION .text:CODE:REORDER(2)
    THUMB
tswitch:
    //disable IRQ interrupts SVC mode
    cpsid i // Disable interrupts
    mrs r0, control
    orr r0, r0, #0x1
    msr control, r0
    //store cpu registers in proc stack 
    push {r4-r11}
    ldr r0, =running
    ldr r1, [r0, #0]
    str sp, [r1, #8]
    //load the new running process
    ldr r0, =next
    ldr r1, [r0, #0]
    ldr sp, [r1, #8]
    //running = next
    ldr r0, =running
    ldr r1, =next
    ldr r2, [r1]
    str r2, [r0]
    //restore cpu register values from sp
    pop {r4-r11}
    //return without FPU extended
    mov lr, #0xFFFFFFF9
    //enable irq interrupts SVC mode 
    mrs r0, control
    bic r0, r0, #0x1
    msr control, r0
    cpsie i // Enable interrupts//change to lr or pc?
    bx lr
    END
    
