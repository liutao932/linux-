#!/usr/bin/bash
##############################
##############################
############funtion out
funtion1(){
	read -p "please you are email:  " email
        echo $email | awk -F "@" '{print $1}'
}
funtion2(){
	read -p "please two number: " a b
	echo $[$a+$b]
}
#sum=`funtion2`
#echo "$sum"
#qq=`funtion1`
#echo "$qq"
echo  "please seletc number:
       1:get qq
       2:sum"
read number
case $number in
1)
	sum=`funtion1`
        echo "$sum"
	;;
2)
       	qq=`funtion2`
 	echo "$qq"
esac
