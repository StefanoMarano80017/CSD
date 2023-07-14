#
# Programma per la gestione di una coda:
# la coda è costituita da un massimo di QSIZE elementi 
# e occupa gli indirizzi da QSTART a QEND.
# Si gestiscono due puntatori:
# - QHEAD: inizializzato a QSTART, durante l'evoluzione della coda punterà 
#          all'elemento di testa
# - QTAIL: inizializzato a QSTART, durante l'evoluzione della coda punterà 
#          alla prima locazione vuota dopo l'elemento di coda


.data
# alloca spazio per la coda
queue: .space 20 #riserva 5 word per gli elementi della coda

# alloca spazio per i puntatori
QSTART: .space 4
QEND: .space 4
QHEAD: .space 4
QTAIL: .space 4

# alloca 1 word per memorizzare il numero corrente di elementi della coda
QLENGTH: .space 4

# definisce la lunghezza massima della coda
QSIZE: .word 5  #massima capienza della coda

stringa_enq: .asciiz "elemento inserito correttamente"
stringa_deq: .asciiz "l' elemento prelevato è:"
stringa_len: .asciiz "il numero di elementi nella coda è:"
err_enq: .asciiz "impossibile inserire nuovi elementi: coda piena!"
err_deq: .asciiz "impossibile prelevare elementi: coda vuota!"
RTN: .asciiz "\n"



.text
.globl main

# Programma principale che testa le operazioni sulla coda

main:	
	la $s0, queue		# carica l'indirizzo della coda in $t0
	lw $s1, QSIZE       # carica QSIZE in $s1
	
	jal INIT			# inizializza la coda
	
	li $a0,33			# carica il valore 33 in $a0
	jal ENQUEUE
	
	li $a0,2			# carica il valore 2 in $a0
	jal ENQUEUE
	
	li $a0,555			# carica il valore 555 in $a0
	jal ENQUEUE
	
	li $a0,7			# carica il valore 7 in $a0
	jal ENQUEUE
	
	li $a0,-1			# carica il valore -1 in $a0
	jal ENQUEUE
	
	li $a0,77			# prova a caricare il valore 77 in $a0
	jal ENQUEUE
	
	jal GETLEN
	
	jal DEQUEUE
	jal DEQUEUE
	jal DEQUEUE
	jal DEQUEUE
	jal DEQUEUE
	jal DEQUEUE        	# prova a prelevare un elemento dalla coda vuota
	
	jal GETLEN
	
	# exit (servizio #10) i programmi finiscono sempre con exit
	li $v0, 10
	syscall

	
	
	
INIT:	
	sw $s0, QSTART	   # pone in QSTART l'indirizzo di partenza della coda
	
	sll $t2, $s1, 2    # moltiplica per 4 il valore di QSIZE per avere il numero di byte totali della coda
	add $t1,$s0,$t2	   # calcola QEND, l'indirizzo del primo elemento al di fuori della coda
	
	sw $t1, QEND       # pone in QEND l'indirizzo finale della coda
	
	sw $zero, QLENGTH  # pone 0 in QLENGTH

	sw $s0, QTAIL      # QTAIL viene inizializzato con il valore QSTART
	
	sw $s0, QHEAD      # QHEAD viene inizializzato con il valore QSTART
	
	jr $ra			   # salta al main


	
# -------------------------------------------	
# aggiunta di un elemento nella coda	
ENQUEUE:
	lw $t2, QTAIL     # carica il valore di QTAIL, che rappresenta l'indirizzo in cui inserire il nuovo elemento
	lw $t3, QEND	  # carica il valore di QEND
	lw $t4, QLENGTH	  # carica il valore di QLENGTH
	
							
	beq $t4,$s1,ERR_ENQ  # se QLENGTH=QSIZE ritorna senza aggiungere l'elemento in coda, altrimenti:
	
	sw $a0,($t2)	  # memorizza il nuovo elemento $a0 in corrispondenza di QTAIL ($t2)
	
	addi $t4,$t4,1    # incrementa QLENGTH di un'unità
	
	addi $t2,$t2,4    # incrementa il puntatore di QTAIL di 4 byte per puntare alla prossima locazione vuota
	
	bne $t2,$t3, INCR_TAIL # se il nuovo valore di QTAIL è uguale a QEND allora setta QTAIL=QSTART
	lw $t2, QSTART
	
INCR_TAIL:	
	sw $t2, QTAIL	  # aggiorna il puntatore QTAIL con il valore giusto
	sw $t4, QLENGTH	  # aggiorna QLENGTH
	j STAMPA_ENQ
	


# -------------------------------------------	
# eliminazione di un elemento dalla coda
DEQUEUE:	
	lw $t2, QHEAD     # carica l'indirizzo di QHEAD, da cui prelevare il dato 
	lw $t3, QEND	  # carica il valore di QEND
	lw $t4, QLENGTH	  # carica QLENGTH in $t4
	
	beq $t4,$zero,ERR_DEQ  # se QLENTGH=0 ritorna senza aggiungere l'elemento in coda, altrimenti:
	
	lw $a1,($t2)	  # preleva l'elemento in testa e lo pone in $a0
	
	addi $t4,$t4,-1   # decrementa QLENGTH di un'unità
	
	addi $t2,$t2,4    # incrementa il puntatore di QHEAD di 4 byte per puntare al primo elemento della coda
	
	bne $t2,$t3,INCR_HEAD # se il nuovo valore di QHEAD è uguale a QEND allora setta QHEAD=QSTART
	lw $t2, QSTART
	
INCR_HEAD:	
	sw $t2, QHEAD	  # aggiorna il puntatore in memoria
	sw $t4, QLENGTH	  # aggiorna QLENGTH
	j STAMPA_DEQ

# -------------------------------------------	
#stampa del numero di elementi presenti nella coda	
GETLEN:
	lw $t4, QLENGTH	  # carica QLENGTH in $t4
	move $a1,$t4
	j STAMPA_LEN


# -------------------------------------------	
# procedure di stampa	
ERR_ENQ:
	#stampa messaggio di errore di enqueue
	la $a0, err_enq
	li $v0, 4 	#4 è il codice per print_string
	syscall
	# stampa \n (servizio #4)
	la $a0, RTN
	li $v0, 4
	syscall
	jr $ra	

ERR_DEQ:
	#stampa messaggio di errore di dequeue
	la $a0, err_deq
	li $v0, 4 	#4 è il codice per print_string
	syscall
	# stampa \n (servizio #4)
	la $a0, RTN
	li $v0, 4
	syscall
	jr $ra
	
STAMPA_ENQ:
	#stampa messaggio di avvenuto accodamento
	la $a0, stringa_enq
	li $v0, 4 	#4 è il codice per print_string
	syscall
	# stampa \n (servizio #4)
	la $a0, RTN
	li $v0, 4
	syscall
	jr $ra
	
STAMPA_DEQ:
	#stampa messaggio de avvenuto prelevamento
	la $a0, stringa_deq
	li $v0, 4 	#4 è il codice per print_string
	syscall	
	# stampa somma (servizio #1)
	move $a0, $a1
	li $v0, 1
	syscall	
	# stampa \n (servizio #4)
	la $a0, RTN
	li $v0, 4
	syscall
	jr $ra
	
STAMPA_LEN:
	#stampa lunghezza della coda
	la $a0, stringa_len
	li $v0, 4 	#4 è il codice per print_string
	syscall
	# stampa lunghezza (servizio #1)
	move $a0, $a1
	li $v0, 1
	syscall	
	# stampa \n (servizio #4)
	la $a0, RTN
	li $v0, 4
	syscall
	jr $ra