#!/bin/bash
if [ $# -eq 1 ]
then
	./push_swapV6 $1 | ./checker $1
	./push_swap $1 | ./checker $1
fi