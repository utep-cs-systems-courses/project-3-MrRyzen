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
    MOV.B   #4, R13
    CMP.B   R12, R13 { JLO        .L2
    MOV.B   &dim, R12
    BR      #.L3
.L2:
    MOV.B   #0, R12
.L3:
    MOV.B   R12, &dim
    MOV.B   &dim, R12
    CMP.W   #0, R12 { JNE .L4
    MOV.B   #1, R12
    BR      #.L5
.L4:
    MOV.B   #0, R12
.L5:
    RET