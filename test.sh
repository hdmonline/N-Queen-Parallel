#!/bin/bash

mkdir -p avg
n=8
k=5
for p in 1 2 4
do
	counter=1
	sum=0
	while [ $counter -le 5 ]
	do
		# mpirun -np $p ./nqueen $n $k
		qsub -v p=$p,n=$n,k=$k pbs_script.pbs
		a=`head -2 out\_$n\_$p\_$k.txt`
		sum=`expr $sum + $a`
		((counter++))
	done
	sum=`expr $sum / 5`
	echo for $n $p $k, average = $sum > avg\_$n\_$p\_$k.txt
done
echo plot 1-1 done