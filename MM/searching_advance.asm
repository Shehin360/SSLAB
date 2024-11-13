data segment
    msg1 db 10,13, 'Enter the character to search: $'
    msg2 db 10,13, 'Character found in the string$'
    msg3 db 10,13, 'Character not found in the string$'
    search_char db ?             ; Character to search for
    msg4 db 10,13, 'Starting the program$'
    string db 10,13, 'Hello, World$'
data ends

code segment
ASSUME cs:code, ds:data

start:
    mov ax, data
    mov ds, ax
    
    lea dx, msg4      ; printing starting the program
    mov ah, 09h
    int 21h       
    
    lea dx , msg1     ; prompt to enter the character
    mov ah , 09h
    int 21h  
    
    mov ah, 01h       ; accept user input for the character
    int 21h
    mov search_char, al  
    
    lea si, string    ; load the address of 'Hello, World' into si
    
search_loop:    
    mov al , [si]     ; load the current character
    cmp al , '$'      ; check for end of string
    je not_found
    cmp al , search_char
    je found
    inc si            ; move to next character
    jmp search_loop

found:
    lea dx , msg2
    mov ah , 09h
    int 21h
    jmp exit

not_found:
    lea dx, msg3
    mov ah, 09h
    int 21h

exit:
    mov ah, 4ch
    int 21h
    
code ends
end start
