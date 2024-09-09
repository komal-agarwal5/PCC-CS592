while true;
do
	echo "Menu : "
	echo "1)Sort records in reverse order of roll and store in new file"
	echo "2)Replace lowercase characters with uppercase characters"
	echo "3)To find out records with unique name and store"
	echo "4)Display only 2nd and 3rd lines from file"
	echo "5)Exit"
	read -p "Enter your choice : " n
	case "$n" in
		1) cat students.dat | sort -t'|' -k 2 -r >> sorted.dat
		   cat sorted.dat
			;;
		2) tr [:lower:] [:upper:] < sorted.dat > temp.dat
		   mv temp.dat sorted.dat
		   cat sorted.dat
			;;
		3) line=`cat sorted.dat | sort -t'|' -k 1 | cut -d'|' -f1 | uniq`
		   echo "Unique lines are : "
		   for i in $line;
		   do
		   	linep=`cat sorted.dat | grep -w "^$i" | head -n 1`
		   	echo $linep
		   	echo $linep >> students.dat
		   done
		   echo "Modified file is : "
		   cat students.dat
			;;
		4) cat students.dat | head -n 3 | tail -n 2
			;;
		5) echo "Exiting..."
			exit ;;
	esac
done
