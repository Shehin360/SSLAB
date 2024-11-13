data SEGMENT
    MSG1 DB 10,13, 'ENTER THE STRING:$'
    STR1 DB 50 DUP(0)                ; Space for input string, max 50 characters
    MSG2 DB 10,13, 'REVERSED STRING:$'
data ENDS

code SEGMENT
    ASSUME CS:code, DS:data
START:
    MOV AX, data
    MOV DS, AX

    ; Display "ENTER THE STRING:" message
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    ; Read characters into STR1
    LEA SI, STR1           ; SI points to start of STR1
    LEA DI, STR1           ; DI also points to start of STR1 to save the input
    MOV AH, 01H            ; AH = 01h for character input

NEXT:
    INT 21H                ; Get character in AL
    CMP AL, 0DH            ; Check if Enter key (0DH) was pressed
    JE TERMINATE           ; Jump if Enter was pressed
    MOV [DI], AL           ; Store character in STR1
    INC DI                 ; Move DI to the next position
    JMP NEXT               ; Repeat for the next character

TERMINATE:
    MOV BYTE PTR [DI], '$' ; Mark end of string with $
    DEC DI                 ; Set DI to last character of input

REVERSE:
    CMP SI, DI             ; Compare SI and DI to check if reversal is complete
    JAE PRINT              ; If SI >= DI, we are done

    MOV AL, [SI]           ; Load character at SI
    MOV BL, [DI]           ; Load character at DI
    MOV [DI], AL           ; Swap characters
    MOV [SI], BL
    INC SI                 ; Move SI to the next character
    DEC DI                 ; Move DI to the previous character
    JMP REVERSE            ; Repeat the reversal

PRINT:
    ; Display "REVERSED STRING:" message
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    ; Display the reversed string
    LEA DX, STR1
    MOV AH, 09H
    INT 21H

    ; Exit the program
    MOV AH, 4CH
    INT 21H

code ENDS
END START
