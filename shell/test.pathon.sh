#!/usr/bin/bash
####################################
####this is test
cd WGCTF2
for(( i = 0; i < 10;i++ ))
do
        python run.py device=QAT-HuoYao-CPM20-KPT-3 primary=CentOS_8.4,64_bit,QAT20.L.0.8.3-00028 secondary=CentOS_8.4,64_bit,QAT20.L.0.8.3-00028 tag=QAT2.0_KPT_SVM_SRIOV packages=/home/swf_prc/liji/Packages systems=/home/swf_prc/liji/system_test/Resource/Systems logs=/home/swf_prc/liji devices=/home/swf_prc/liji/system_test/Resource/Devices tests=/home/swf_prc/liji/system_test/Resource/Tests test=QAT2.0_KPT_SVM_SRIOV
done
cd ..
path=/home/swf_prc/liji/QAT20.L.0.8.3-00028
cd $path
if [ $? -eq 0 ]; then

        for i in `ls | grep '2022-01-25'`
        do
                cat ${path}/${i}/report.csv|awk '{if(NR==2){print $0}}'>>./report.csv
        done
else
        echo "no dir"
fi
