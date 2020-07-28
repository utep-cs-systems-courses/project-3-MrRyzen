	.arch msp430g2553
	.p2align 1,0
	.text

	;;  routines to access sr

	.global dimmerControl
dimmerControl:
    MOV.B   &dim, R12
    ADD.B   #1, R12
    AND     #0xff, R12
    MOV.B   R12, &dim
    MOV.B   &dim, R12
    CMP.B   #4, R12
    JNE zero
    MOV.B   #1, R12
    JMP one
zero:
    MOV.B   #0, R12
one:
    RET