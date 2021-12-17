#!/usr/bin/bash
####################################
###############Autor : liu
###############Time  :2021/12/17
###############Descride : this is a shell of geting number
while read line
do
        number=`echo $line |awk -F "." '{print $1}'`
        echo "<int>$number</int>" >> QAT2.0_KPT_SVM.xml
done <id.txt
