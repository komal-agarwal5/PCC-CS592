echo Enter year
read y
if [ $y -le 0 ]
then
	echo Invalid input
	exit 1
fi
if [  $((y % 4)) -eq 0 ] && [ $((y % 100)) -ne 0 ]
then
	echo Year is leap
elif [ $((y % 400)) -eq 0 ]
then
	echo Year is leap
else
	echo Year is not leap
fi

