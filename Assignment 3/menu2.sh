#!/bin/bash
add()
{
	read -p "Enter name : " name
	read -p "Enter roll number : " roll
	read -sp "Enter password: " pass
	echo "$name $roll $pass" >> personal.dat
	echo "Data added"
}
show()
{
	read -sp "Enter password : " pass
	cat personal.dat | cut -d' ' -f3 > samplecheck.dat
	echo
	if [ $(grep -cE "^$pass$" samplecheck.dat) -ne 0 ];then
		echo "$(grep -E "$pass$" personal.dat | cut -d' ' -f1,2)"
	else
		echo "Data not found"
	fi
	echo
	rm samplecheck.dat
}
while true ; do
	echo "Menu : "
	echo "1) Add data"
	echo "2) Show data"
	echo "3)Exit"
	echo
	read -p "Enter choice : " ch
	case "$ch" in
		1) add ;;
		2) show ;;
		3) echo "Exiting from menu"
			exit ;;
		4) echo "Invalid choice"
	esac
done
}
