.data

var1: 10
var2: 20
sub_value: 5
result: 0

.text

main:
    lw $t0, var1       # Load var1 into $t0
    lw $t1, var2       # Load var2 into $t1
    add $t2, $t0, $t1  # Add $t0 and $t1, store result in $t2
    sw $t2, result     # Store the result in memory
    lw $t3, sub_value  # Load sub_value into $t3
    sub $t4, $t2, $t3  # Subtract $t3 from $t2, store result in $t4
    print $t4          # Print the final result
    end                # End of program
