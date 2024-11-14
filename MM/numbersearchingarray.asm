.model small
.stack 100h

.data
    array db 5, 10, 15, 20, 25      ; Array of numbers
    searchNumber db 15             ; Number to search for
    foundMessage db "Number found at index: $"
    notFoundMessage db "Number not found.$"
    index db 0                       ; To store index of found element

.code
main:
    ; Initialize data segment
    mov ax, @data
    mov ds, ax

    ; Set up the loop counter (index)
    lea si, array         ; SI points to the beginning of the array
    mov bl, 0             ; BL will be used as the index counter
    mov al, [searchNumber] ; AL holds the search number

    ; Loop through the array
searchLoop:
    cmp al, [si]          ; Compare search number (AL) with current element ([SI])
    je found              ; If equal, jump to found label

    inc si                ; Move to the next element in the array
    inc bl                ; Increment the index counter
    cmp bl, 5             ; Check if we've reached the end of the array
    jl searchLoop         ; If not, continue the loop

    ; If not found, print "Not Found"
    lea dx, notFoundMessage
    mov ah, 09h
    int 21h
    jmp endProgram

found:
    ; If found, print "Found" message with index
    lea dx, foundMessage
    mov ah, 09h
    int 21h

    ; Print the index (in BL)
    mov al, bl            ; Move the index (BL) into AL
    add al, 30h           ; Convert index to ASCII
    mov dl, al
    mov ah, 02h
    int 21h

endProgram:
    mov ah, 4Ch           ; Exit program
    int 21h
end main
