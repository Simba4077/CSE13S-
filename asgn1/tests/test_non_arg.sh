# Creates the example output
echo "NOT ENOUGH INPUT" > expected.txt

# Runs the program
./calc > actual.txt 

# Ensures exit code is non-Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm expected.txt
    rm actual.txt
    exit 1
fi

# Ensures differences *are* found
diff actual.txt expected.txt
if [ $? -ne 0 ]; then
    echo "The program didn't print NOT ENOUGH INPUT"
    rm expected.txt
    rm actual.txt
    exit 1
fi

# Prints a message on success
echo "Test found no arguments"

# Cleans up files created
rm actual.txt
rm expected.txt
exit 0
