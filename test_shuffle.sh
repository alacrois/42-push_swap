#!/bin/bash
if [ $# -eq 1 ]
then
	arg=`ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
	echo "arg = $arg"
	./push_swap $arg | ./checker -v -d -c -f $arg
fi