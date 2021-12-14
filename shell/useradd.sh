  1 #!/usr/bin/bash
  2 ##############################
  3 ######Autor :liu
  4 ######Time  :2021/12
  5 ######Desrcipe: Adduser
  6 while :
  7 do
  8         read -p "please inout perfix & passwd & num[liji 123456 5]: " perfix passwd num
  9         echo "
 10                 userAdd infomation:
 11                 useradd name : $perfix
 12                 useradd passwd : $passwd
 13                 useradd num  : $num "
 14
 15         read -p "Are you sure?[Y/N]: " action
 16                 if [ "$action" == "Y" ]; then
 17                         break;
 18                 fi
 19 done
 20 for i in `seq -w $num`
 21 do
 22         user=$perfix$i
 23         id $user &>/dev/null
 24         if [ $? -eq 0 ];then
 25             echo "$user is areadly  exist"
 26         else
 27            useradd $user
 28            echo "passwd" | passwd --stdin $user &>/dev/null
 29            if [ $? -eq 0 ];then
 30                    echo " $user is creat"
 31            fi
 32         fi
 33 done
~
