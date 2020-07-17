#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	echo "arg = $arg"
	# time ./push_swapV5 $arg
	time ./push_swap $arg
	# time ./push_swap $arg | grep "r"
fi