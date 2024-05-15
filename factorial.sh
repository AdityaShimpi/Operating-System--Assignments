#1/bin/bash

echo "Enter a number"
read num

fact=1

if [ $num -lt 0 ]; then
	echo "Factorial is not defined for negative numbers. "
	exit
fi

for (( i=1; i<=$num; i++)); do
	fact=$((fact*i))
done

echo "The Factorial of $num is $fact."

