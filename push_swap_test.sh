#!/bin/bash
if [ $# -eq 1 ]
then
	time ./push_swap `ruby -e "puts (-$1...$1).to_a.shuffle.join(' ')"`
fi