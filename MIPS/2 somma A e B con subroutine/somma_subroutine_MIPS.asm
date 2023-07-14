#
# Programma per il calcolo di A+B
# La somma viene effettuata mediante un sottoprogramma 
#

# L'area dati viene allocata a partire dalla locazione 0x10010000 di default 

.data
A: .byte 4
B: .byte 5
stringa_ris: .asciiz "la somma e': "
RTN: .asciiz "\n"



.text
.globl main

# Programma principale

main:	
	lb $t0, A		# carica A in $t0
	lb $t1, B		# carica B in $t1
	
	#passaggio dei parametri nel registri preposti $a0 e $a1	
	move $a0, $t0 		# pseudo istruzione che sposta il contenuto di $t0=A in $a0
	move $a1, $t1		# pseudo istruzione che sposta il contenuto di $t1=B in $a1
	
	#salto a subroutine
	jal SUM				# salta a SUM e salva l'indirizzo di ritorno in $ra
	
	#lettura del risultato da $v0
	move $t4, $v0 		# pseudo istruzione che sposta il risultato da $v0 a $t4
			
	#chiamate aggiuntive che sfruttano le system call
	#per la visualizzazione del risultato: in $v0 viene posto sempre il codice
	#della system call da invocare, in $a0-$a3 gli argomenti
	
	#stampa messaggio per il risultato (servizio #4)
	la $a0, stringa_ris
	li $v0, 4 	           # 4 è il codice per print_string
	syscall
	
	# stampa somma (servizio #1)
	move $a0, $t4
	li $v0, 1
	syscall
	
	# stampa \n (servizio #4)
	la $a0, RTN
	li $v0, 4
	syscall
	
	# exit (servizio #10) i programmi finiscono sempre con exit
	li $v0, 10
	syscall
	
	
# subroutine

SUM:
	subu $sp, $sp, 24 	# la subroutine salva $ra, $fp e riserva lo spazio
				# per 2 variabili locali (A e B, solo a scopo dimostrativo)
				# di 1 word ciascuna. In tutto abbiamo 4 word = 16 byte
				# ma la dimensione minima dello stack frame è di 24 byte (6 word)
				# sottraendo 24 byte a $sp si ottiene ancora un valore 2word-aligned--->OK!
		
	# nello stack abbiamo:

		#-------------------------------------------
#       sp---->	# - - - - - - - - - - -    | offset 0 byte
				# - - - - - - - - - - -    | offset 4 byte
				# 1 word per var locale V2 | offset 8 byte
				# 1 word per var locale V1 | offset 12 byte
				# 1 word per $fp 	   	   | offset 16 byte
#       fp---->	# 1 word per $ra	       | offset 20 byte			      
		#-----------------------------------------------
		
					
	sw $ra, 20($sp) 	# salvataggio dell'indirizzo di ritorno sullo stack
	sw $fp, 16($sp) 	# salvataggio del frame pointer
	
	# caricamento variabili locali (dimostrativo)
	addi $t3, $a0, 3	# valore V1
	sw $t3, 12($sp) 	# salvataggio di V1 nel call frame come variabile locale 
	addi $t3, $a1, 6	# valore V2
	sw $t3, 8($sp) 		# salvataggio di V2 nel call frame come variabile locale

	addiu $fp, $sp, 20	# nuovo frame pointer, punta al primo elemento del call frame 

	# utilizzo variabili locali (dimostrativo)
	lw $t2, 12($sp) 	# carico nel registro $t2 la variabile locale V1
	lw $t3, 8($sp)		# carico nel registro $t3 la variabile locale V2
	add $t4, $t2, $t3 	# la somma viene inserita in $t4
	
	# calcolo del risultato
	add $v0, $a0, $a1

	lw $ra, 20($sp) 	# recupera l'indirizzo di ritorno dal call frame
	lw $fp, 16($sp) 	# recupera il vecchio frame pointer
	
	addu $sp, $sp, 24 	# elimina il call frame dallo stack
	jr $ra 			# ritorna al chiamante


