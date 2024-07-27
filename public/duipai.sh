# on linux
#!/bin/bash
generator="./datamaker"
prog1="./prog1"
prog2="./prog2"

cnt=0

while true; do
    $generator > input.txt
    time $prog1 < input.txt > output1.txt # show prog1 time
    $prog2 < input.txt > output2.txt
    diff output1.txt output2.txt
    if [ $? -eq 0 ]; then
        cnt=$((cnt+1))
        echo "Test $cnt passed"
    else
        echo "Failed"
    fi
done