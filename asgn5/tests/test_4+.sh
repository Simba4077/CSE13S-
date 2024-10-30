#!/bin/bash
./calc_x86 4 + > expected.txt
./calc 4 + > actual.txt


if diff expected.txt actual.txt > /dev/null; then
    echo "Your file did not output the expected"
    rm actual.txt
    rm expected.txt
    exit 1
fi


echo "Test was a success, the program produces the right error!"

rm actual.txt
rm expected.txt
exit 0
