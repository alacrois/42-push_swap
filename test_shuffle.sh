#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	# arg2=`ruby -e "puts (-5000...5000).to_a.reverse.insert(rand(8000) + 1000, 10001).join(' ')"`
	# echo "arg = $arg"
	# time ./push_swapV1 $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV2 $arg | ./checker $arg | grep "Total number"
	# time ./push_swap_no_cfnt $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV3 $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV5 $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV6 $arg | ./checker $arg | grep "Total number"
	# time ./push_swapV7 $arg | ./checker $arg | grep -A 1 "Total number"
	# echo "================================"
	# echo "================================"
	time ./push_swapV8 $arg | ./checker $arg | grep -A 1 "Total number"
	echo -e "\n"
	time ./push_swap $arg | ./checker $arg | grep -A 1 "Total number"
	# time ./push_swap $arg | ./checker $arg
	# time ./push_swap $arg
	echo -e "\n"

	# time ./push_swap $arg | grep "order"
	# time ./push_swap $arg2 | ./checker $arg2
fi