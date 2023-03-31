		;		Dato n, si sommino i primi n numeri naturali
		
		MOV		R1, #10 ; n
		MOV		R2, #0 ; contatore
loop
		CMP		R2, R1 ; verifico se ho già sommato tutti i numeri
		BEQ		end_loop ; se sì, esco
		ADD		R2, R2, #1 ; i = i + 1
		ADD		R0, R0, R2 ; uso i come numero naturale i-esimo e lo sommo
		B		loop
end_loop
