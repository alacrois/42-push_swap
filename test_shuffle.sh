#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	# time ./push_swapV1 $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV2 $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV3 $arg | ./checker $arg | grep "Total number"
	time ./push_swap_no_cfnt $arg | ./checker $arg | grep "Total number"
	time ./push_swap $arg | ./checker $arg | grep "Total number"
fi