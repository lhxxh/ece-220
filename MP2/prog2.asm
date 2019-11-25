
.ORIG x3000
	
READ_NEXT
	GETC                        ; get a character
	LD R1,NEG_EQUAL
	ADD R1,R0,R1
	BRz DONE_EXP                ; judge whether it is =
	LD R1,NEG_SPACE
	ADD R1,R0,R1
	BRz READ_NEXT               ; judge whether it is space
	LD R1,NEG_PLUS   
	ADD R1,R0,R1
	BRz OPERATOR                ; judge whether it is +
	LD R1,NEG_MINUS            
	ADD R1,R0,R1
	BRz OPERATOR                ; judge whether it is -
	LD R1,NEG_MUL
	ADD R1,R0,R1                   
	BRz OPERATOR                ; judge whether it is *
	LD R1,NEG_DIV           
	ADD R1,R0,R1
	BRz OPERATOR                ; judge whether it is /
	LD R1,NEG_POWER
	ADD R1,R0,R1               
	BRz OPERATOR                ; judge whether it is ^
	LD R1,NEG_ZERO           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 0
	LD R1,NEG_ONE           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 1
	LD R1,NEG_TWO           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 2
	LD R1,NEG_THREE           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 3
	LD R1,NEG_FOUR           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 4
	LD R1,NEG_FIVE           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 5
	LD R1,NEG_SIX           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 6
	LD R1,NEG_SEVEN           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 7
	LD R1,NEG_EIGHT           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 8
	LD R1,NEG_NINE           
	ADD R1,R0,R1               
	BRz NUMBER                  ; judge whether it is 9
    BRnzp INVALID               ; unconditional jump to INVALID when no case is met

NUMBER
    LD R1,NUMBER_MASK          
    AND R0,R1,R0
    BRnzp STACK_PUSH

OPERATOR
    ADD R6,R0,#0                ; store the value of operand into R6
	JSR POP
	ADD R5,R5,#0                
    BRp INVALID 
    ADD R3,R0,#0                ; load R3 with the value of R0
    JSR POP
    ADD R5,R5,#0
    BRp INVALID    
    ADD R4,R0,#0                ; load R4 with the value of R0
    LD R1,NEG_PLUS         
    ADD R1,R6,R1                
    BRz PLUS_SIGN               ; conditional jump to plus if +
	LD R1,NEG_MINUS         
    ADD R1,R6,R1                
    BRz MINUS_SIGN              ; conditional jump to min if -
    LD R1,NEG_MUL         
    ADD R1,R6,R1                
    BRz MUL_SIGN                ; conditional jump to mul if *
    LD R1,NEG_DIV        
    ADD R1,R6,R1                
    BRz DIV_SIGN                ; conditional jump to div if /
    LD R1,NEG_POWER         
    ADD R1,R6,R1                
    BRz EXP_SIGN                ; conditional jump to exp if ^

PLUS_SIGN
    JSR PLUS
    BRnzp STACK_PUSH

MINUS_SIGN
	JSR MIN
    BRnzp STACK_PUSH

MUL_SIGN
	JSR MUL
    BRnzp STACK_PUSH

DIV_SIGN
	JSR DIV
	BRnzp STACK_PUSH

EXP_SIGN
	JSR EXP
    
STACK_PUSH
	JSR PUSH
    BRnzp READ_NEXT             ; unconditional jump back to get the next char

DONE_EXP
	LD R1,STACK_TOP
    LD R2,STACK_START
    ADD R1,R1,#1                ; increment R1 by 1
	NOT R1,R1
	ADD R1,R1,#1                ; get negative R1
    ADD R1,R1,R2               
	BRz LOAD_RESULT			    ; get result if only one value exists on stack
	
INVALID
	LEA R0,IN_EXP
	PUTS
	BRnzp DONE

LOAD_RESULT
	LDR R5,R2,#0
    LD R0,HEX_SIGN
    OUT
    
;print R5
    AND R1,R1,#0
    ADD R1,R1,#4				; set R1 to four bit counter
	
CHECK_DONE
	ADD R1,R1,#0
	BRnz DONE                   ; if four bits get and then jump to done
	AND R2,R2,#0				; clear R2 to zero
 	AND R3,R3,#0				
	ADD R3,R3,#4				; set R3 to four digit counter
	
CHECK_FOUR
	ADD R3,R3,#0
	BRnz PRINT_DIGIT
	ADD R2,R2,R2				; left shift R2 once
	ADD R5,R5,#0
	BRn ADD_ONE
	ADD R2,R2,#0				; add 0 to R2 in case of MSB=0
	BRnzp RFIVE_LEFT 
	
ADD_ONE
	ADD R2,R2,#1
	
RFIVE_LEFT
	ADD R5,R5,R5
    ADD R3,R3,#-1
	BRnzp CHECK_FOUR

PRINT_DIGIT
	AND R4,R4,#0
	ADD R4,R4,#-9				; set R4 to -9
	ADD R4,R4,R2
	BRnz ADD_ZEROAS
	LD R4,A_MIN_TEN				; in the case R2>9
	ADD R0,R2,R4				
	BRnzp PRINT
	
ADD_ZEROAS
	LD R4,ZEROAS				; in the case R2<=9
	ADD R0,R2,R4
	
PRINT
	OUT
	ADD R1,R1,#-1
	BRnzp CHECK_DONE

DONE
	HALT
					





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
ADD R0,R3,R4
RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
NOT R3,R3
ADD R3,R3,#1
ADD R0,R3,R4
RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
AND R0,R0,#0

LOOP_MUL
ADD R0,R0,R4
ADD R3,R3,#-1
BRp LOOP_MUL
RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
AND R0,R0,#0	
NOT R3,R3
ADD R3,R3,#1

LOOP_DIV
ADD R4,R4,R3
BRn DONE_LOOP_DIV
ADD R0,R0,#1
BRnzp LOOP_DIV

DONE_LOOP_DIV
RET
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
    AND R0,R0,#0
    ADD R0,R4,#0
    ST R5,POWER_SAVER5
    ST R6,POWER_SAVER6

    BIG_LOOP_POWER
    ADD R3,R3,#-1
	BRz POWER_LOOP_DONE
	ADD R5,R4,#-1
	ADD R6,R0,#0

POWER_SMALL_LOOP
	ADD R0,R0,R6
	ADD R5,R5,#-1
	BRp POWER_SMALL_LOOP
	ADD R0,R0,#0
	BRnzp BIG_LOOP_POWER

POWER_LOOP_DONE
	LD R5,POWER_SAVER5
	LD R6,POWER_SAVER6
RET

POWER_SAVER5 .BLKW 1
POWER_SAVER6 .BLKW 1
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	
POP_SaveR4	.BLKW #1	
STACK_END	.FILL x3FF0	
STACK_START	.FILL x4000	
STACK_TOP	.FILL x4000	
NEG_EQUAL   .FILL xFFC3 
NEG_SPACE   .FILL xFFE0 
NUMBER_MASK .FILL x000F 
IN_EXP      .STRINGZ "Invalid Expression"
NEG_PLUS    .FILL xFFD5 
NEG_MINUS   .FILL xFFD3
NEG_MUL     .FILL xFFD6
NEG_DIV     .FILL xFFD1
NEG_POWER   .FILL xFFA2
A_MIN_TEN   .FILL x0037
ZEROAS      .FILL x0030
NEG_ZERO    .FILL xFFD0
NEG_ONE		.FILL xFFCF
NEG_TWO		.FILL xFFCE
NEG_THREE	.FILL xFFCD
NEG_FOUR	.FILL xFFCC
NEG_FIVE	.FILL xFFCB
NEG_SIX		.FILL xFFCA
NEG_SEVEN	.FILL xFFC9
NEG_EIGHT	.FILL xFFC8
NEG_NINE	.FILL xFFC7
HEX_SIGN    .FILL x0078

.END
