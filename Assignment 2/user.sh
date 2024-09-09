read -p "Enter username: " user
count=$(grep -c -i $user /etc/passwd)
if [ $count -ne 0 ]
then
	echo "VALID USER"
else
	echo "INVALID USER"
fi
