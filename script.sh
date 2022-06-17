#!/bin/bash
i=0
max=0
min=100000000
sum=0
OPT=$@
while [ $i -lt 200 ] 
do
	res=$(LD_PRELOAD=./libft_malloc.so /usr/bin/time --verbose 2>&1 ./test$OPT | grep Minor \
	| cut -d':' -f2)
	#echo "Res = $res"
	if [ $res -gt $max ]
	then
		max=$res
	fi
	if [ $res -lt $min ]
	then
		min=$res
	fi
	true $(( sum+=$res ))
	true $(( i+=1 ))
done;
echo "Min = $min"
echo "Max = $max"
echo -n "Average = "
echo "scale=4;$sum/200" | bc
