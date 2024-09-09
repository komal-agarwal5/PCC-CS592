#!/bin/bash
n=$1
if [ $n -lt 0 ]
then
    echo "Invalid input"
    exit 1
fi
echo Common logarithm is : 
echo "scale=2; l($n)/l(10)" | bc -l

