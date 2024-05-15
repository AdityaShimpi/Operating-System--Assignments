#!/bin/bash

echo "Enter a number"
read num

is_prime=1

if [ $num -le 1 ]; then
	is_prime=0
fi

for (( i=2; i<=num/2; i++ )); do
	if [ $((num%i)) -eq 0 ]; then
	   is_prime=0
	   break
	fi
done

if [ $is_prime -eq 1 ]; then
	echo "$num is a prime number."
else
	echo "$num is not a prime number"
fi

