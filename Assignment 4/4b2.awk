#!/usr/bin/awk -f

BEGIN {FS="~"; max1=0; max2=0; max3=0}; 
NR==1 {s1=$3; s2=$4; s3=$5};
NR>1 && NR<6 {if(max1<$3){max1=$3; name1=$1}; if(max2<$4){max2=$4; name2=$1}; if(max3<$5){max3=$5; name3=$1}}; 
END {print "Top scorers are : \n" s1 ": " name1 " with marks " max1 "\n" s2 ": " name2 " with marks " max2 "\n" s3 ": " name3 " with marks " max3};
