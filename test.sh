#!/bin/bash
if [ $# -eq 1 ]
then
	./push_swap $1 | ./checker $1
fi