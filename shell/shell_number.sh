#!/usr/bin/bash
#############################
#########Autor:liu	
#########Time : 2021/12/16
#########descripe : this is shell of number of shell
declare -A shell
while read line
do
	type=`echo $line |awk -F ":" '{print $NF}'`
	let shell[$type]++
done </etc/passwd
for i in ${!shell[@]}
do
	echo "$i : ${shell[$i]}"
done
