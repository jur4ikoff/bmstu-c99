#!/bin/bash

directories=$(find . -type d)
slice=("${directories[@]:1}")
directories=$slice
for dir in $directories
do  
    if [[ $dir == *".git"* ]]; then
        continue
    fi    
    echo $dir

    mkdir -p $dir/func_tests/data
    mkdir  $dir/func_tests/scripts
    counter=0
    str1="0"
    while [ $counter -le 4 ]
    do
        name=$str1$counter
        counter=$((counter + 1))
        pos_in=$dir/func_tests/data/pos_"$name"_in.txt
        pos_out=$dir/func_tests/data/pos_"$name"_out.txt

        touch $pos_in
        touch $pos_out

        if [ $counter -le 2 ]; then
            neg_in=$dir/func_tests/data/neg_"$name"_in.txt
            neg_out=$dir/func_tests/data/neg_"$name"_out.txt
            touch $neg_in
            touch $neg_out
        fi
    
    done
done