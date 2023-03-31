		MOV		R1, #88 ; firstNumber
		MOV		R2, #24 ; secondNumber
		CMP		R2, R1 ; condizione invertita per eseguire prima l'if
		BGT		else ; se < vado a else
		ADD		R0, R1, R2 ; result = firstNumber + secondNumber
		B		exit ; esco dall'if
else
		SUB		R0, R2, R1 ; else, ovvero result = secondNumber - firstNumber
exit
