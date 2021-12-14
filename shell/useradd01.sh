 1 #!/usr/bin/bash
  2 ######################
  3 #######Autor : liu
  4 #######Time  : 2021/12
  5 if [ $# -eq 0 ]; then
  6         echo " No paramaeter"
  7 fi
  8
  9 if [ ! $1 -f ];then
 10         echo " no file"
 11 fi
 12 for line in `cat $1`
 13 do
            if [ ${#line} -eq 0 ]; then
                  continue
            fi
 14         user=`echo "$line" | awk '{print $1}'`   ####qie ge
 15         passwd=`echo "$line" | awk '{print $2}'`
 16         id $user &>/dev/null
 17         if [ $? -eq 0 ];then
 18                 echo "$user is areadly exists"
 19         else
 20                 useradd $user
 21                 echo "passwd" | passwd  --stdin $user &>/dev/null
 22                 if [ $? -eq 0 ]; then
 23                         echo "$user is creat"
 24                 fi
 25         fi
 26
 27 done
~
