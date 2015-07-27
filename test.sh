#!/bin/bash

declare -a arr=("tests/test_1")

for i in "${arr[@]}"
do
    printf "Running %s\n" $i
    eval $i
    code=$?
    if [ $code != 0 ]; then
        printf "Error: %s exited with status %d\n" $i $code
        exit $code
    fi
done

printf "All tests succesfully executed!\n"
exit 0

