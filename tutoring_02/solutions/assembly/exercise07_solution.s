		MOV		R0, #5 ; n
		MOV		R1, R0 ; copia di n per moltiplicazione con somma
		MOV		R2, R0
		ADD		R2, R2, #1 ; n+1
		MOV		R3, #0 ; i = 0
loop_sum
		CMP		R3, R1 ; verifico se ho finito la moltiplicazione
		BEQ		end_sum ; se sì, esco
		ADD		R0, R0, R1 ; "moltiplico"
		ADD		R3, R3, #1 ; incremento i
		B		loop_sum
end_sum
		MOV		R3, R0 ; copia di n*(n+1) per divisione
		MOV		R0, #0 ; R0 diventa accumulatore per ospitare n*(n+1)/2
loop_sub
		CMP		R3, #0 ; ciclo fino a R3 = 0 cioè divisione conclusa
		BEQ		end_sub
		SUB		R3, R3, #2 ; "divido"
		ADD		R0, R0, #1 ; aumento il numero di volte che ho diviso
		B		loop_sub
end_sub
