#!/usr/bin/awk -f

BEGIN {FS="~"; max=0}; NR>1 && NR<6 {total=$3+$4+$5; if(max<total) {max=total; rec=$0}}; END {print "Highest scorer is :\n" rec" with total marks of : "max}
