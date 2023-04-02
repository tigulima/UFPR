.data
VET1:	.word 1 5 8 3 15 24 20 33 48 43 # vetor tam 10
VET2:	.word 0 31 6 1 44 21 17 25 7 50 # vetor tam 10
SOMA:	.word 0:10 # vetor tamanho 10, preenchidos com zeros 
TAM:	.word 10 # escalar
SEP: .asciiz ", "

.text
	la $t0, TAM    # Carrega o endereco (nao o valor) de TAM para $t0
	lw $t0, 0($t0) # Carrega o valor (conteudo) de TAM para $t0
	la $t1, VET1   # Carrega o endereco (nao o valor) de VET1 para $t1
	la $t2, VET2   # Carrega o endereco (nao o valor) de VET2 para $t2
	la $t3, SOMA   # Carrega o endereco (nao o valor) de SOMA para $t3

########################################################################
## Escreva aqui seu código!
########################################################################

_start:
	lw $t4, 0($t1)    # Carrega valor selecionado do VET1 no t4
  	lw $t5, 0($t2)    # Carrega valor selecionado do VET2 no t5
  	add $t4, $t4, $t5 # Soma os valores e salva no t4
  	sw $t4, 0($t3)    # Guarda valor no vetor SOMA
    	addi $t1, $t1, 4  # Pula para próximo elemento do VET1
    	addi $t2, $t2, 4  # Pula para próximo elemento do VET2
    	addi $t3, $t3, 4  # Pula para próximo elemento do SOMA
    	addi $t0, $t0, -1 # Diminui TAM
    	bne $t0, $0, _start # Repete até que o TAM seja 0

########################################################################
##          NAO MODIFICAR !!!
## Comandos para imprimir o valor do vetor SOMA 
########################################################################
	la $t0, SOMA # t0 = &SOMA[0]
	addi $t1, $zero, 0 # i = 0
	addi $t2, $zero, 10
PRINT:	beq $t1, $t2, FIM
	sll $t3, $t1, 2 # i*4
	add $t3, $t3, $t0
	li $v0, 1
	lw $a0, 0($t3)
	syscall
	addi $t1, $t1, 1
	li $v0, 4
	la $a0, SEP
	syscall
	j PRINT		

#####    ENCERRA O PROGRAMA   #####	
FIM:	li $v0, 10 # HALT
	syscall	
	
