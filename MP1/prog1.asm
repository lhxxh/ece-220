;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
    AND R1,R1,#0        ; clear R1 to zero

HIS_CHECK
    LD  R0,TWO_SIX      ; load R0 with -26
    ADD R0,R1,R0        ; set for check if all has been done
    BRp DONE            ; jump to DONE if all has been done
    LD R2,AT            ; load R2 with @ ASCII value
    ADD R0,R2,R1        ; put histogram's subject in R0
    OUT                 
    LD R0,SPACE         ; put space ASCII value in R0
    OUT                 
    LD R2,HIST_ADDR     ; load R2 with histogram starting point
    ADD R3,R2,R1        ; calculate the address of histogram content
    LDR R3,R3,#0        ; get the content of desired histogram
    
;Flow chart
    LD R4,FOUR          ; set the digit counter to four 

LOOP
    ADD R4,R4,#0        ; set the condition checking for digit counter
    BRnz DONE_HEX       ; jump to DONE_HEX when digit counter is zero
    LD R5,FOUR          ; set bit counter to 4
    AND R6,R6,#0        ; clear R6 to 0
    
DEC_BIT_C
    ADD R5,R5,#0        ; set the condition to check bit counter is 0
    BRnz FOUR_BIT       
    ADD R6,R6,R6        ; left shift R6 once
    ADD R3,R3,#0        ; set condition for checking the MSB is 1 or 0
    BRn ADD_ONE         
    ADD R6,R6,0         ; add 0 to R6 when the MSB is 0
    BRnzp LEFT_SHIFT    
    
ADD_ONE
    ADD R6,R6,#1        ; add 1 to R6 when the MSB is 1
    
LEFT_SHIFT
    ADD R3,R3,R3        ; left shift R3 once
    ADD R5,R5,#-1       ; decrement bit counter
    BRnzp DEC_BIT_C     

FOUR_BIT 
    LD R0,NEGATIVE_NINE ; load R0 with -9 to compare
    ADD R0,R0,R6        ; compare R6 with -9
    BRp ALPHABET        
    LD R0,ZERO          ; load R0 with zero ASCII value
    ADD R0,R6,R0        ; calculate the bit ASCII value and load it to R0
    OUT
    BRnzp DEC_DIG_C     

ALPHABET
    LD R0,A_MINUS_TEN   ; load R0 with A-10
    ADD R0,R6,R0        ; calculate the bit ASCII value and load it to R0
    OUT
    
DEC_DIG_C
    ADD R4,R4,#-1       ; decrement digit counter 
    BRnzp LOOP          
    
DONE_HEX
    LD R0,NEW_LINE      ; load R0 with new line ASCII value
    OUT
    ADD R1,R1,#1        ; increment row counter
    BRnzp HIS_CHECK       

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
TWO_SIX     .FILL #-26  ; test for row counter
AT          .FILL x0040 ; fill with @ ASCII value
SPACE       .FILL x0020 ; fill with space ASCII valu
NEGATIVE_NINE  .FILL #-9 ; fill with #-9
ZERO        .FILL x0030 ; fill with 0's ASCII value
A_MINUS_TEN .FILL x0037 ; fill with A-10 ASCII value
NEW_LINE    .FILL x000A ; fill with New line ASCII value
FOUR        .FILL #4    ; fill with 4



; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
