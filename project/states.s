	.arch msp430g2553
	.p2align 1,0
	.text

	;;  routines to access sr

	.global dimmerControl
dimmerControl:
	CMP.B #4, R12
	JNE zero
	MOV.B #1, R12
	JMP one
zero:
	MOV.B #0, R12
one:
	RET
