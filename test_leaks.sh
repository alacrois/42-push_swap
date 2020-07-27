#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	echo "arg = '$arg'"

	# The following line checks 'push_swap' :
	# valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind_output.txt ./push_swap $arg

	# The following line checks 'checker' :
	./push_swap $arg | valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind_output.txt ./checker -d -c -v -f $arg
fi