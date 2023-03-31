		;		Moltiplicazione tra due numeri usando solo la somma
		
		MOV		R1, #13 ; primo numero
		MOV		R2, #4 ; secondo numero
		MOV		R3, #0 ; i = 0
loop
		CMP		R3, R2 ; controllo se ho già moltiplicato R2 volte
		BEQ		end_loop ; se sì, esco
		ADD		R0, R0, R1 ; "moltiplico"
		ADD		R3, R3, #1 ; incremento i
		B		loop
end_loop
