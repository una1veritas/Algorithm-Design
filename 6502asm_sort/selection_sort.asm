; Selection Sort for 6502 (Ascending)
; Data to sort is in 'ARRAY', length is in 'LEN'
; Uses zero page locations for pointers

ARRAY   = $0200         ; Start address of data
LEN     = 10            ; Length of array

ptr1    = $10           ; Zero page pointers
ptr2    = $12

SORT:
    LDX #0              ; Outer loop index
OUTER:
    STX ptr1            ; Store outer loop index
    TXA
    TAY                 ; Inner loop starts from OUTER+1
    INY
    
MIN_LOOP:
    CPY #LEN            ; Check if end of array
    BCS NEXT_OUTER
    
    LDA ARRAY, Y
    CMP ARRAY, X        ; Compare current min with Y element
    BCS NO_SWAP         ; If ARRAY[X] <= ARRAY[Y], no swap
    
    ; Swap elements
    PHA
    LDA ARRAY, X
    STA ARRAY, Y
    PLA
    STA ARRAY, X
    
NO_SWAP:
    INY
    BNE MIN_LOOP        ; Loop until Y wraps

NEXT_OUTER:
    INX
    CPX #LEN-1          ; Check if done
    BNE OUTER
    RTS
