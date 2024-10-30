#Tests for decimal argument: 3.14 and 4
# Creates the example output
echo "BAD INPUT" > expected.txt 

# Runs the program
./calc 3 @ > actual.txt 

# Ensures exit code is non-Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm expected.txt
    rm actual.txt
    iexit 1
fi

# Ensures differences *are* found
diff actual.txt expected.txt
if [ $? -ne 0 ]; then
    echo "Program didn't print BAD INPUT"
    rm expected.txt
    rm actual.txt
    exit 1
fi

# Prints a message on success
echo "Detected non-integer characters"

# Cleans up files created
rm expected.txt
rm actual.txt
exit 0
