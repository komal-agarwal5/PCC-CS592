#!/bin/bash
sum=0
for i in $*
do
	if [ $i -le 0 ]
	then
		echo Invalid input enter only natural numbers
		exit 1
	fi
	sum=$(expr $sum + $i)
done
echo Summation is $sum

