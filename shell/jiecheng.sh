#!/usr/bin/bash
############################
############################
factorial()
{

        sun=1
	for((i=1;i<=$num;i++))
do
       	sun=$[$sun * $i]
done			
	echo "$sun"
}
num=$1
factorial
