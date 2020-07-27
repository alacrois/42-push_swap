#!/bin/bash
if [ $# -eq 1 ]
then
	result=`./push_swap $1`
	echo "===== PUSH_SWAP RESULT ====="
	echo "$result"
	echo "====== CHECKER RESULT ======"
	echo -ne "$result" | ./checker -v -f -c -d $1
fi