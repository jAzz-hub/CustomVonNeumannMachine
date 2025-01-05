.data

input1: 15
input2: 25
input3: 35
output1: 0
output2: 0
output3: 0

.text

main:
    lw $t0, input1       # Load input1 into $t0
    print $t0            # Print the value of $t0

    lw $t1, input2       # Load input2 into $t1
    print $t1            # Print the value of $t1

    lw $t2, input3       # Load input3 into $t2
    print $t2            # Print the value of $t2

    add $t3, $t0, $t1    # Add $t0 and $t1, store result in $t3
    sw $t3, output1      # Store the result in output1
    print $t3            # Print the value of $t3

    sub $t4, $t3, $t2    # Subtract $t2 from $t3, store result in $t4
    sw $t4, output2      # Store the result in output2
    print $t4            # Print the value of $t4

    mult $t5, $t4, $t0   # Multiply $t4 and $t0, store result in $t5
    sw $t5, output3      # Store the result in output3
    print $t5            # Print the value of $t5

    end                  # End of program
