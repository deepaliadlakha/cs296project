#!/bin/bash

cnt=0;
while read line
do
	let cnt=cnt+1;
	if [ $(($cnt % 100)) -eq 20 ];
	then echo "$line" >> ./data/g09_data2.csv;
	fi;
done < ./data/g09_data.csv
