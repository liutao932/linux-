#!/usr/bin/bash
#################################
#################################
ls /home/lijix/QSN4-1388-PF |awk '{print $1}' >> case_pf.txt
ls /home/lijix/QSN4-1388 |awk '{print $1}' >>case_sriov.txt
while read line1
do
        case_number1=`echo $line1 | awk -F "." '{print $1}'`
        echo -n "$case_number1     " >>pf_funtion.txt
        cat $line1 |awk '{if(NR==23){print $0}}' >>pf_funtion.txt
done<case_pf.txt
while read line2
do
        case_number2=`echo $line2 | awk -F "." '{print $1}'`
        echo -n "$case_number2     " >>sriov_funtion.txt
        cat $line2 |awk '{if(NR==55){print $0}}' >>sriov_funtion.txt
done<case_sriov.txt
rm -r case_pf.txt
rm -r case_sriov.txt
