#!/usr/bin/awk -f

BEGIN {FS="~";sum=0;flag=0}
NR>1 && NR<6 {if(sm=="Subject_1"){sum+=$3;} else if(sm=="Subject_2"){sum+=$4;} else if(sm=="Subject_3"){sum+=$5;} else{flag=1;}}
END {if(flag==0){avg=sum/4; print "Average score in " sm " is : " avg} else{print "Invalid input"}}
