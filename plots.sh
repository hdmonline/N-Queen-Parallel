#!/bin/bash

# plot 1
n=15
k=5
sum=0;
for p in 1 2 4 6 8 10 12 14 16
do
	counter=1
	while [ $counter -le 5 ]
	do
		qsub -v p=$p,n=$n,k=$k pbs_script.pbs
		a=`head -2 out\_$n\_$p\_$k.txt`
		((counter++))
	done
done
echo plot 1-1 done

n=12
k=5
for p in 1 2 4 6 8 10 12 14 16
do
	counter=1
	while [ $counter -le 5 ]
	do
		qsub -v p=$p,n=$n,k=$k pbs_script.pbs
		((counter++))
	done
done
echo plot 1-2 done

# plot 2
n=16
p=8
for k in 1 2 4 6 8 10 12 14 16
do
	counter=1
	while [ $counter -le 5 ]
	do
		qsub -v p=$p,n=$n,k=$k pbs_script.pbs
		((counter++))
	done
done
echo plot 2-1 done

n=13
p=8
for k in 1 2 4 6 8 10 12
do
	counter=1
	while [ $counter -le 5 ]
	do
		qsub -v p=$p,n=$n,k=$k pbs_script.pbs
		((counter++))
	done
done
echo plot 2-2 done

# plot 3
k=4
p=8
for n in 8 9 10 11 12 13 14 15 16
do
	counter=1
	while [ $counter -le 5 ]
	do
		qsub -v p=$p,n=$n,k=$k pbs_script.pbs
		((counter++))
	done
done
echo plot 3-2 done

k=6
p=8
for n in 8 9 10 11 12 13 14 15 16
do
	counter=1
	while [ $counter -le 5 ]
	do
		qsub -v p=$p,n=$n,k=$k pbs_script.pbs
		((counter++))
	done
done
echo plot 3-2 done