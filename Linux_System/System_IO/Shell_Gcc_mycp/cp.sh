#!/usr/bin/bash
##############################
##############################
while :
do
        read -p "Are you sure Tripled[Y/N]: " contion
        if [ ${contion} == "Y" ];then
        size=`cat mycp2.c | awk '{if(NR==3){print $3}}'`
        addsize=$(($size*2))
        echo $addsize
        sed -i "s/#define MAXSIZE ${size}/#define MAXSIZE ${addsize}/" mycp2.c
        gcc -o mycp mycp.c
        time ./mycp /home/lijix/sample_code/sample_code.tar.gz txt
        else
                break
        fi
done
