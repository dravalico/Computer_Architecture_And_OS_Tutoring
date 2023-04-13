		MOV		R1, #4 ; dimensione vettore
		MOV		R2, #0x100 ; indirizzo base per salvare vettore
		MOV		R3, #12 ; primo valore da salvare
		STR		R3, [R2, #0] ; salvo il primo valore in 0x100
		MOV		R3, #-4 ; secondo valore ecc..
		STR		R3, [R2, #4]
		MOV		R3, #52
		STR		R3, [R2, #8]
		MOV		R3, #-40
		STR		R3, [R2, #12]
		MOV		R3, #0 ; j = 0
		MOV		R4, #0 ; registro per leggere vettore
		LDR		R0, [R2, R4] ; carico il primo valore
		ADD		R4, R4, #4 ; i parte dal secondo valore
loop
		CMP		R3, #3 ; verifico se ho già letto i 3 numeri restanti
		BEQ		end_loop ; se sì, esco
		LDR		R5, [R2, R4] ; carico myArray[i]
		CMP		R5, R0 ; confronto con il valore maggiore attuale
		BLT		next ; se non è maggiore, vado avanti col ciclo
		MOV		R0, R5 ; se è maggiore, aggionrno R0
next
		ADD		R3, R3, #1 ; incremento j
		ADD		R4, R4, #4 ; incremento i
		B		loop
end_loop
