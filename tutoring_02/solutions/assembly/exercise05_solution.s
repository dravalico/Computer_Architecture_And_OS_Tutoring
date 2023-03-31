		MOV		R1, #0x100 ; indirizzo base per salvare vettore
		MOV		R2, #21 ; primo valore da salvare
		STR		R2, [R1, #0] ; salvo il primo valore in 0x100
		MOV		R2, #5 ; secondo valore ecc..
		STR		R2, [R1, #4]
		MOV		R2, #66
		STR		R2, [R1, #8]
		MOV		R2, #14
		STR		R2, [R1, #12]
		MOV		R2, #37
		STR		R2, [R1, #16]
		
		MOV		R0, #0 ; registro per il risultato
		MOV		R2, #0 ; indice per accedere a myArray[i]
loop
		CMP		R2, #20 ; controllo se ho già letto 5 elementi
		BEQ		end_loop ; esco se ho letto tutto
		LDR		R3, [R1, R2] ; salvo in R3 il valore di myArray[i]
		CMP		R3, #30 ; confronto myArray[i] con 30
		BLT		no_adding
		ADD		R0, R0, R3 ; accumulo in R0 il risultato
no_adding
		ADD		R2, R2, #4 ; i = i + 4
		B		loop
end_loop
		
