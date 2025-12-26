#!/bin/bash

pathA=./generate_test_case.cpp
pathB=./main.cpp
pathC=./gt_sol.cpp
execA=./datagen.exe
execB=./main.exe
execC=./gt.exe

g++ -O2 -std=c++11 "$pathA" -o "$execA" -DLOCAL &&  # Compile and run A
g++ -O2 -std=c++11 "$pathB" -o "$execB" -DLOCAL # Compile B
g++ -O2 -std=c++11 "$pathC" -o "$execC" -DLOCAL # Compile C

echo "start loop"
for i in {1..1000}
do
        "$execA"
        if ! diff -q <("$execB") <("$execC"); then    # The output is different
        echo "In run number $i, the output was different"
        cp input.txt wa_input.txt
        break
    fi
done
