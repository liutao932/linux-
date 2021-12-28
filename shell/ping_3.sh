#!/usr/bin/bash
###################################
######this is shell of ping three##

ip="10.10.10.10 10.101.10.4 10.10.34.97"
for i in "$ip"
do
	for count in {1..3}
	do
		ping -c1 &>/dev/null
		if [ $? -eq 0 ]; then
			echo " $ip is sucess"
			break
		else
			echo " $ip is fail, $count"
		   	fail_count[$count]=$ip
		fi		
	done
	if [ ${#fail_count[*]} -eq 3 ];then
		echo "${fail_count[$count]} is fail"
		unset fail_count[*]
	fi
done
