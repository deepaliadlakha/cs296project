#!/bin/bash
touch ./data/g09_data.csv
rm ./data/g09_data.csv



for i in {1..100}
	do
	for j in {1..100}
		do
		./bin/cs296_base $j | 
		awk 'BEGIN {print '"$i"'}
			{if (NR == 1){ print $NF;}
			else if (NR == 6){}
			else { print ( $(NF-1) );} }' | 
			awk 'NR==1 {x=$0; next} NF {x=x","$0} END {print x}' >> ./data/g09_data.csv
	done
done

exit
