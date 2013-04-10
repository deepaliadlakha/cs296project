#!/bin/bash

for i in {1..100}
	do
	for j in {1..100}
		do
		./bin/cs296_base $j > ./data/out-$j-$i.txt
	done
done

exit
