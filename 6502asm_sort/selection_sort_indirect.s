; Selection Sort Algorithm for Indexes (Indirect Sort) - 6502 Assembly
; Sorts indexes that reference 4-byte character strings without modifying original strings
;
; Memory layout:
; - $0200-$020F: Array of 4 strings (4 bytes each) - NEVER MODIFIED
;   String 0: $0200-$0203
;   String 1: $0204-$0207
;   String 2: $0208-$020B
;   String 3: $020C-$020F
;
; - $0210-$0213: Index array (sorted result)
;   INDEX[0]: $0210 (initially 0)
;   INDEX[1]: $0211 (initially 1)
;   INDEX[2]: $0212 (initially 2)
;   INDEX[3]: $0213 (initially 3)
;
; Register usage:
; - X: Outer loop counter (current position)
; - Y: Inner loop counter (search for minimum)
; - A: Temp storage and comparison results

            .ORG $0600

; Main entry point - Initialize index array
START:      LDX #$00
INIT_LOOP:  CPX #$04
            BEQ OUTER_LOOP
            TXA
            STA $0210,X         ; INDEX[i] = i
            INX
            JMP INIT_LOOP

; Outer loop - iterate through each position
OUTER_LOOP: LDA #$00
            STA OUTER_IDX       ; outer_idx = 0
            JMP OUTER_START

OUTER_START:
            LDA OUTER_IDX
            CMP #$03            ; Check if we've sorted all but last element
            BEQ DONE            ; If outer_idx == 3, we're done
            
            STA MIN_IDX         ; min_idx = outer_idx
            LDA OUTER_IDX
            CLC
            ADC #$01
            STA INNER_IDX       ; inner_idx = outer_idx + 1
            JMP INNER_LOOP

; Inner loop - find minimum element
INNER_LOOP: LDA INNER_IDX
            CMP #$04            ; Check if we've checked all remaining elements
            BEQ SWAP_CHECK      ; If inner_idx == 4, exit inner loop
            
            ; Compare strings referenced by INDEX[min_idx] and INDEX[inner_idx]
            JSR COMPARE_INDEXED_STRINGS
            
            ; If strings[INDEX[inner_idx]] < strings[INDEX[min_idx]], update min_idx
            CMP #$01
            BNE SKIP_UPDATE
            
            LDA INNER_IDX
            STA MIN_IDX         ; min_idx = inner_idx
            
SKIP_UPDATE:LDA INNER_IDX
            CLC
            ADC #$01
            STA INNER_IDX       ; inner_idx++
            JMP INNER_LOOP

; Swap indexes if minimum found is different from current position
SWAP_CHECK: LDA MIN_IDX
            CMP OUTER_IDX
            BEQ NEXT_OUTER      ; If min_idx == outer_idx, no swap needed
            
            JSR SWAP_INDEXES    ; Swap INDEX[OUTER_IDX] and INDEX[MIN_IDX]
            
NEXT_OUTER: LDA OUTER_IDX
            CLC
            ADC #$01
            STA OUTER_IDX       ; outer_idx++
            JMP OUTER_START

; Done - program ends
DONE:       BRK

; ============================================================================
; COMPARE_INDEXED_STRINGS
; Compares two strings indirectly via index array, lexicographically
; Inputs:
;   MIN_IDX: Position in index array (0-3)
;   INNER_IDX: Position in index array (0-3)
; Uses:
;   INDEX[MIN_IDX]: Index into string array
;   INDEX[INNER_IDX]: Index into string array
; Returns:
;   A = $00 if strings are equal
;   A = $FF if strings[INDEX[min_idx]] < strings[INDEX[inner_idx]] (1st < 2nd)
;   A = $01 if strings[INDEX[min_idx]] > strings[INDEX[inner_idx]] (1st > 2nd)
; ============================================================================
COMPARE_INDEXED_STRINGS:
            LDY #$00            ; byte counter = 0
            
COMPARE_LOOP:
            CPY #$04            ; Compare all 4 bytes
            BEQ STRINGS_EQUAL
            
            ; Get INDEX[min_idx]
            LDA MIN_IDX
            TAX
            LDA $0210,X         ; Load index value
            STA IDX1_VALUE
            
            ; Get INDEX[inner_idx]
            LDA INNER_IDX
            TAX
            LDA $0210,X         ; Load index value
            STA IDX2_VALUE
            
            ; Calculate address of first string byte
            ; Address = $0200 + (index * 4) + byte_offset
            LDA IDX1_VALUE
            ASL                 ; multiply by 4
            ASL
            CLC
            ADC $0210,Y         ; Add byte offset (Y has byte counter)
            STA ADDR1           ; Low byte of address
            LDA #$02            ; High byte is always $02
            STA ADDR1+1
            
            ; Calculate address of second string byte
            LDA IDX2_VALUE
            ASL                 ; multiply by 4
            ASL
            CLC
            ADC $0210,Y         ; Add byte offset
            STA ADDR2           ; Low byte of address
            LDA #$02            ; High byte is always $02
            STA ADDR2+1
            
            ; Load characters from calculated addresses
            LDX ADDR1
            LDA ($0200,X)       ; Indirect addressing would need setup
            ; Use direct indexed addressing instead
            LDA IDX1_VALUE
            ASL
            ASL
            STA CALC_OFFSET
            LDX CALC_OFFSET
            LDA $0200,X         ; Get first byte of first string
            CLC
            ADC $0210,Y         ; Add byte offset
            TAX
            LDA $0200,X
            STA CHAR1
            
            ; Load second character
            LDA IDX2_VALUE
            ASL
            ASL
            STA CALC_OFFSET
            LDX CALC_OFFSET
            LDA $0200,X         ; Get first byte of second string
            CLC
            ADC $0210,Y         ; Add byte offset
            TAX
            LDA $0200,X
            STA CHAR2
            
            ; Compare characters
            LDA CHAR1
            CMP CHAR2
            BEQ NEXT_BYTE       ; If equal, check next byte
            BLT LESS_THAN       ; If CHAR1 < CHAR2, first string is less
            BRA GREATER_THAN    ; Otherwise, first string is greater
            
NEXT_BYTE:  INY                 ; byte counter++
            JMP COMPARE_LOOP

STRINGS_EQUAL:
            LDA #$00
            RTS

LESS_THAN:  LDA #$FF            ; Indicate first < second
            RTS

GREATER_THAN:
            LDA #$01            ; Indicate first > second
            RTS

; ============================================================================
; SWAP_INDEXES
; Swaps two index values in the index array
; Inputs:
;   OUTER_IDX: Position in index array (0-3)
;   MIN_IDX: Position in index array (0-3)
; ============================================================================
SWAP_INDEXES:
            ; Load INDEX[outer_idx]
            LDA OUTER_IDX
            TAX
            LDA $0210,X
            STA TEMP_INDEX      ; temp = INDEX[outer_idx]
            
            ; Load INDEX[min_idx] and store in INDEX[outer_idx]
            LDA MIN_IDX
            TAX
            LDA $0210,X
            LDX OUTER_IDX
            STA $0210,X         ; INDEX[outer_idx] = INDEX[min_idx]
            
            ; Store temp in INDEX[min_idx]
            LDA TEMP_INDEX
            LDX MIN_IDX
            STA $0210,X         ; INDEX[min_idx] = temp
            
            RTS

; ============================================================================
; DATA SECTION
; ============================================================================

; Variables
OUTER_IDX:  .BYTE $00
INNER_IDX:  .BYTE $00
MIN_IDX:    .BYTE $00
ADDR_CALC:  .BYTE $00
CALC_OFFSET:.BYTE $00
ADDR1:      .WORD $0000
ADDR2:      .WORD $0000
IDX1_VALUE: .BYTE $00
IDX2_VALUE: .BYTE $00
CHAR1:      .BYTE $00
CHAR2:      .BYTE $00
TEMP_INDEX: .BYTE $00

; Test data - 4 strings of 4 bytes each (never modified)
            .ORG $0200
STRING_0:   .BYTE "DOGS"
STRING_1:   .BYTE "CATS"
STRING_2:   .BYTE "BIRD"
STRING_3:   .BYTE "ANTS"

; Index array - sorted result (modified during sort)
            .ORG $0210
INDEX:      .BYTE $00, $01, $02, $03