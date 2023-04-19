               MOV     R0, #10 ; n
               BL      fibonacci ; chiamata subroutine
               END

fibonacci      
               MOV     R2, R0 ; salvo n
               CMP     R2, #1 ; se n = 1 devo tornare 1
               BNE     init_loop
               MOV     R0, #1
               B       end_subroutine
init_loop      
               MOV     R0, #0 ; inizializzo R0 per risultato
               MOV     R3, #0 ; valore per n = 0
               MOV     R4, #1 ; valore per n = 1
               MOV     R5, #2 ; i = 2
loop           
               CMP     R5, R2 ; verifico i rispetto n
               BHI     end_subroutine ; se i > n, esco
               ADD     R0, R3, R4 ; salvo risultato
               MOV     R3, R4 ; f_(n-2) = f_(n-1)
               MOV     R4, R0 ; f_(n-1) = f_n
               ADD     R5, R5, #1 ; incremento i
               B       loop
end_subroutine 
               MOV     PC, LR ; uscita subroutine (BX)
