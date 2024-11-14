.model small
.stack 100h

.data
    ; Define the source array with some numbers
    sourceArray db 5, 10, 15, 20, 25  ; Source array (5 elements)
    
    ; Define the destination array (same size as source)
    destArray db 5 dup(0)  ; Destination array initialized to 0s

    ; Message to display (for debugging purpose)
    msg db "Array copied successfully!$"

.code
main:
    ; Initialize data segment
    mov ax, @data
    mov ds, ax

    ; Initialize the source and destination array pointers
    lea si, sourceArray  ; Load the address of the source array into SI
    lea di, destArray    ; Load the address of the destination array into DI

    ; Initialize counter (number of elements to copy)
    mov cx, 5            ; We know the source array has 5 elements

copy_loop:
    ; Move byte from sourceArray to destArray
    mov al, [si]         ; Load the current byte from sourceArray into AL
    mov [di], al         ; Store the byte from AL into destArray

    ; Increment pointers (SI and DI)
    inc si               ; Move to the next byte in the source array
    inc di               ; Move to the next byte in the destination array

    ; Decrement counter (CX) and check if we are done
    loop copy_loop       ; Repeat until CX reaches 0

    ; Optional: Print success message (DOS interrupt for printing)
    lea dx, msg
    mov ah, 09h          ; DOS function to print string
    int 21h

    ; Exit the program
    mov ah, 4Ch          ; DOS function to terminate the program
    int 21h

end main
