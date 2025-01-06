.data

value:   10
Z:   0

.text

main:
    li $t0, 5           # Carrega o valor 5 no registrador $t0
    li $t1, 10          # Carrega o valor 10 no registrador $t1
    add $t2, $t0, $t1   # resultado em $t2
    print $t2

    li $t3, 7           # Carrega o valor 7 no registrador $t3
    sub $t4, $t1, $t3   # Subtrai $t3 (7) de $t1 (10), armazenando o resultado em $t4
    print $t4