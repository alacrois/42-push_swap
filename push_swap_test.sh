#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	echo "arg = $arg"
	# argument=`cat arg.txt`
	# ./push_swap $argument
	time ./push_swap $arg
	# time ./push_swap $argument > output.txt
	# time ./push_swapV13 $arg
	# time ./push_swap $arg | grep "r"
fi