.title "init assembleur"


.text
.arm

vectors:
	b start
	b .              @ Reserved vector, not used => boucle infinie
	b .
	b .
	b .
	b .
	b irq_handler
	b .

start:
bl _lowlevel_init

mrs r0, CPSR      @ Copie CPSR dans r0
bic r0, r0, #0x1f @ Met à 0 les 5 bits M
orr r0, r0, #0x12 @ 1001 0010
msr CPSR_c, r0    @ Recharge les bits de contrôle
nop               @ de CPSR

mov sp,#0x09000000

mrs r0, CPSR      @ Copie CPSR dans r0
bic r0, r0, #0x1f @ Met à 0 les 5 bits M
orr r0, r0, #0x13 @ 1001 0010
msr CPSR_c, r0    @ Recharge les bits de contrôle
nop               @ de CPSR

ldr sp,=0x0800f000
ldr r0,=bss_start
ldr r1,=bss_end
mov r2,#0

ldr r3,=text_end
ldr r4,=data_end
ldr r5,=data_start

boucle1:
ldr r7, [r3]
str r7, [r5]
add r3, #4
add r5, #4
cmp r3, r4
bne boucle1


boucle2:
str r2, [r0]
add r0, #4
cmp r0, r1
bne boucle2


bl main
b .
@mov pc, lr


.section "init_assembleur", "ax", %progbits
.end
