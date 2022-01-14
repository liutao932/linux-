#!/usr/bin/bash
####this is test
while read line
do
        cd WGCTF2
        python run.py device=qat-ArcherCity31 primary=CentOS_8.4,64_bit,QAT20.L.0.8.3-00028 secondary=CentOS_8.4,64_bit,QAT20.L.0.8.3-00028 tag=${line} packages=/home/swf_prc/liji/Packages systems=/home/swf_prc/liji/system_test/Resource/Systems logs=/home/swf_prc/liji devices=/home/swf_prc/liji/system_test/Resource/Devices tests=/home/swf_prc/liji/system_test/Resource/Tests test=${line} option=No_Reboot,True
        cd /home/swf_prc/liji/QAT20.L.0.8.3-00028
        str=`ls | grep "$line"`
        cd $str
        cat report.csv >> ~/liji/result.csv
done <case_file
