#!/bin/bash
params=$(cat "./func_tests/data/neg_01_args.txt")
# input="./func_tests/data/neg_01_in.txt"


./app.exe "$params"
rc=$?
echo "$rc"
exit "$rc"