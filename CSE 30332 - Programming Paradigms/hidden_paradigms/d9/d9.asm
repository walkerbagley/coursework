BITS 16

start:
	; here's our prelude of setting up the data and stack sections
	mov ax, 07C0h
	mov ds, ax
	cli		; cancel interrupts while creating stack
	mov ax, 07C0h   
	add ax, 0120h
	mov ss, ax
	mov sp, 1000h
	sti		; restore interrupts
	cld		; clear direction flag for lodsb, end of prelude

	mov si, thestring	; point the register SI to the string that
				; we want to print
	call print	; the call instruction causes the CPU to execute
			; instructions at the given label until
			; the ret instruction is hit
			; call puts the current instruction pointer on
			; the stack before it goes to the label
			; ret restores the instruction pointer by
			; reading it from the stack

.loop2:

; your code here!

; steps: 1) use interrupt 16h to get a char from the char buffer
;        2) use interrupt 10h to print that char to the screen via teletype
;        3) check if char is return (char code 13), if so jump to .done

; ingredients: int, jmp, je, cmp, mov 

; don't overthink it -- my solution is seven lines, and you do not need to
; modify anything outside this loop area

	mov ah, 00h
	int 16h
	mov ah, 0Eh
	int 10h
	cmp al, 0Dh
	je .done

	jmp .loop2	; ... keep looping
.done:

	jmp $		; loop until the power goes out

;; START OF PROCEDURE AREA;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; start of procedure print
print:
	mov ah, 0Eh	; set function code to 0Eh, which is for teletype

.loop1:			; now we begin a loop area with a unique label
	lodsb		; "load byte". What this does is copy a byte that is 
			; in memory at address DS:(E)SI into the register AL
	cmp al, 0h	; recall that strings are terminated with a null byte
			; by comparing AL to 0, we are seeing if the loaded
			; byte is null.  The instruction cmp sets the status
			; flag register to 1 if the comparison is true, and
			; 0 if it is false.
	je .done1	; je (jump equal) jumps to the label specified if
			; the status flag is 1.  The effect is that if AL==0
			; we jump to done1, otherwise...
	int 10h		; ... issue an interrupt to print char.
	jmp .loop1	; now we go back to .loop1 to check the next char
.done1:
	ret		; but if we're done, go ahead and return
; end of procedure print

;; END OF PROCEDURE AREA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; START OF DATA AREA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

thestring db '> ', 0

;; END OF DATA AREA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

times 510-($-$$) db 0	; fill remainder of sector with zeros
dw 0xAA55		; BIOS looks for AA55 at the end of the sector