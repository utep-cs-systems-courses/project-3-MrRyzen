	.arch msp430g2553
	.p2align 1,0
	.text

	;;  routines to access sr

STATE1:
    .string "STATE 1"
STATE2:
    .string "STATE 2"
STATE3:
    .string "STATE 3"
STATE4:
    .string "STATE 4"
STATE0:
    .string "STATE 0"

	.global dimmerControl
dimmerControl:
	CMP.B #4, R12
	JNE zero
	MOV.B #1, R12
	JMP return
zero:
	MOV.B #0, R12
return:
	RET

	.global stateToString
stateToString:
	CMP.B #1, R12
	JEQ one
	CMP.B #2, R12
	JEQ two
	CMP.B #3, R12
	JEQ three
	CMP.B #4, R12
	JEQ four
	jmp default
one:
	MOV.W #STATE1, R12
	jmp end
two:
	MOV.W #STATE2, R12
	jmp end
three:
	MOV.W #STATE3, R12
	jmp end
four:
	MOV.W #STATE4, R12
	jmp end
default:
	MOV.W #STATE0, R12
end:
	RET
