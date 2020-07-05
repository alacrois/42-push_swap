#!/bin/bash
if [ $# -eq 1 ]
then
	./push_swapV1 $1 | ./checker $1
fi