#Confirming that 512 512 inputs will work
# Creates the example output
echo 1024 > expected.txt

# Runs the program
./calc 512 512 > actual.txt 

# Ensures exit code is Zero
if [ $? -ne 0 ]; then
    echo "invalid exit code" $?
    rm actual.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff actual.txt expected.txt
if [ $? -ne 0 ]; then
    echo "Somehow, the program does not compute 512 and 512 as 1024!"
    rm actual.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that 512 + 512 = 1024, success!"

# Cleans up files created
rm actual.txt
rm expected.txt
exit 0
