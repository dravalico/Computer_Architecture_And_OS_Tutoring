               MOV     R0, #111 ; a
               MOV     R1, #21 ; b
               BL      division ; chiamata subroutine
               MOV     R11, #99
               END

division       
               MOV     R2, R0 ; salvo a
               MOV     R3, R1 ; salvo b
               MOV     R0, #0
loop           
               CMP     R2, R3 ; verifico a rispetto b
               BLT     end_subroutine ; se a < b esco
               SUB     R2, R2, R3 ; a = a - b (resto)
               ADD     R0, R0, #1 ; quoziente
               B       loop
end_subroutine 
               MOV     R1, R2 ; salvo il resto in R1
               MOV     PC, LR ; uscita subroutine (BX)