#
# Programma per il calcolo della somma degli elementi di un vettore
# La somma viene effettuata mediante un sottoprogramma 
#

.data 
V: .byte 5,0,1,3,2
dim: .byte 5
stringa_ris: .asciiz "la somma degli elementi del vettore e': "
RTN: .asciiz "\n"


.text
.globl main

# Programma principale

main:	
	la $t0, V		# carica l'indirizzo del vettore V in $t0
	lb $t1, dim		# carica dim in $t1
		
	li $s0,0	#metto 0 in $s0 che sarà il contatore degli elementi
	li $s1,0	#metto 0 in $s1 che sarà la somma
ciclo:
	#lb $t2, V($s0)		#carica l'elemento i-esimo di V in $t2 
	#add $s1, $s1, $t2	#aggiunge l'elemento i-esimo $t2 alla somma parziale $s1 
	#addi $s0, $s0, 1	#aggiunge 1 al contatore
	#bne  $s0, $t1, ciclo     #salta a ciclo se $s0<$t1
		
	# versione alternativa:
	 lb $t2,($t0)	#carica in $t2 l'elemento i-esimo, puntato da $t0. Questo modo di indirizzamento è nativo della macchina HW
	 add $s1, $s1, $t2	#aggiunge l'elemento i-esimo $t2 alla somma parziale $s1 
	 addi $t0, $t0, 1 #fa avanzare il puntatore di un byte per puntare al byte successivo
	 addi $s0, $s0, 1 #aggiunge 1 al contatore
	 bne  $s0, $t1, ciclo     #salta a ciclo se $s0<$t1
	
	
	#scrittura del risultato in $v0
	move $v0, $s1 		# pseudo istruzione che sposta il risultato da $s1 a $v0
			
	#chiamate aggiuntive che sfruttano le system call
	#per la visualizzazione del risultato: in $v0 viene posto sempre il codice
	#della system call da invocare, in $a0-$a3 gli argomenti
	
	#stampa messaggio per il risultato (servizio #4)
	la $a0, stringa_ris
	li $v0, 4 	#4 è il codice per print_string
	syscall
	
	# stampa somma (servizio #1)
	move $a0, $s1
	li $v0, 1
	syscall
	
	# stampa \n (servizio #4)
	la $a0, RTN
	li $v0, 4
	syscall
	
	# exit (servizio #10) i programmi finiscono sempre con exit
	li $v0, 10
	syscall
