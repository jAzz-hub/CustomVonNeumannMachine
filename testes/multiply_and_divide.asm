.data

var1: 6
var2: 7
div_value: 3
result: 0

.text

main:
    lw $t0, var1        # Load var1 into $t0
    lw $t1, var2        # Load var2 into $t1
    mult $t2, $t0, $t1  # Multiply $t0 and $t1, store result in $t2
    sw $t2, result      # Store the result in memory
    lw $t3, div_value   # Load div_value into $t3
    div $t4, $t2, $t3   # Divide $t2 by $t3, store result in $t4
    print $t4           # Print the final result
    end                 # End of program
