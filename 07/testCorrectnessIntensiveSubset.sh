#!/bin/bash

seq_program=$1
par_program=$2
N=$3
NumTests=$4
printLevel=2
if [ -n "$5" ]; then
	runs=$5
else
	runs="1 2 4 8"
fi

# Compile checkSubset if not already compiled
if [ ! -f "./checkSubset" ]; then
	gcc -o checkSubset checkSubset.c -Wall -O3 -std=gnu99
fi

rm -f out*
./$seq_program $N $printLevel 1 > out
# we add 1 here just so we can use a par_program instead of a missing sequential one
echo The result of your parallel program is
echo ======================================
cat out
echo ======================================
echo Running intensive correctness test with $P threads
for i in `seq 1 $NumTests`; do
	echo Test $i/$NumTests
	for P in $runs; do
		./$par_program $N $printLevel $P > out.$i.$P 
	done
done

# Use checkSubset instead of diff
# Check if all lines from sequential output are in parallel output
# and vice versa (to ensure same number of solutions)
all_correct=1
for file in out.*; do
	./checkSubset out $file > /dev/null 2>&1
	if [ $? -ne 0 ]; then
		echo "Error: $file is missing some solutions from sequential version"
		all_correct=0
	fi
	./checkSubset $file out > /dev/null 2>&1
	if [ $? -ne 0 ]; then
		echo "Error: $file has extra solutions not in sequential version"
		all_correct=0
	fi
done

if [ $all_correct -eq 1 ]; then
	echo Output correct on intensive test
	rm -f out*
else
	echo Some outputs are incorrect
fi
