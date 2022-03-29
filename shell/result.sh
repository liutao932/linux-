#!/usr/bin/bash
#####找到所有测试文件的Warining
rm -f result.txt

for i in `find ./ -name output.log | sort`
do
            grep 'Warning' ${i}
            if [ $? -eq 0 ];then
                a=`echo "$i" | awk -F '/' '{print $2}'`
                b=`grep 'Warning' ${i}`
                echo "${a} ${b}" >> result.txt
            fi
done
