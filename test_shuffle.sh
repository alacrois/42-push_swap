#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	# echo "arg = $arg"
	# time ./push_swapV1 $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV2 $arg | ./checker $arg | grep "Total number"
	# time ./push_swap_no_cfnt $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV3 $arg | ./checker $arg | grep "Total number"
	time ./push_swapV4 $arg | ./checker $arg | grep "Total number"
	time ./push_swapV5 $arg | ./checker $arg | grep "Total number"
	# echo "================================"
	# echo "================================"
	time ./push_swap $arg | ./checker $arg | grep "Total number"
fi