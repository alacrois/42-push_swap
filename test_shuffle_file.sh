#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	echo "arg = $arg"
	./push_swap -w "operations.txt" $arg
	./checker -r "operations.txt" -v -f -d -c $arg
fi