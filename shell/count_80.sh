#!/usr/bin/bash
#########################
#########Autor : liu
#########Time  : 2021/12/16
#########descripe: git 80's information
declare -A status
type=`ss -an|grep :80|awk '{print $2}'`
for i in $type
do
	let status[$i]++
done
for j in ${!status[@]}
do
	echo "$j : ${status[$j]}"
done
