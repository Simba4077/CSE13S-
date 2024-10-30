#!/bin/bash

# Run the command and capture the output
bash delayinput.sh my_file.txt |./xd > actual.txt

# Generate the expected output
xxd my_file.txt > expected.txt

# Compare the actual and expected outputs
if diff actual.txt expected.txt; then
  exit 0
else
  exit 1
fi
