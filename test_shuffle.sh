#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	# arg2=`ruby -e "puts (-5000...5000).to_a.reverse.insert(rand(8000) + 1000, 10001).join(' ')"`
	echo "arg = $arg"
	# time ./push_swap $arg | ./checker $arg | grep -A 3 "Total number"
	# push_swap_result=`./push_swap $arg`
	# echo "$push_swap_result" | ./checker $arg
	time ./push_swap $arg | ./checker $arg
	# echo -e "\n"
fi