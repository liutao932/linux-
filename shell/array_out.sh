  1 #!/usr/bin/bash
  2 ########################
  3 ########################
  4 num=(1 2 3)
  5 array() {
  6         local newarray=($*)
  7         local i
  8         for((i =0;i<$#;i++))
  9         do
 10                 newarray[$i]=$((${newarray[$i]} * 5))
 11         done
 12         echo "${newarray[*]}"
 13 }
 14 result=`array ${num[*]}`
 15 echo ${result[*]}
