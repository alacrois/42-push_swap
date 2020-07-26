#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	# valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind_output.txt ./push_swap $arg
	./push_swap $arg | valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind_output.txt ./checker $arg
fi