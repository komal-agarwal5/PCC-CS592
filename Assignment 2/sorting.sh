read -p "Enter length of array : " n
arr=()
if [ $n -lt 1 ]
then
	echo Invalid input
	exit 1
fi
echo Enter array elements
for ((i=0; i<$n; i++))
do
	read arr[$i]
done
echo Unsorted array is
for ((i=0; i<$n; i++))
do
	echo -n "${arr[$i]} "
done 
for ((i=0; i<$n; i++))
do
	for((j=0; j<$((n - i - 1)); j++))
	do
		if [ ${arr[$j]} -gt ${arr[$((j + 1))]} ]
		then
			temp=${arr[$j]}
			arr[$j]=${arr[$((j + 1))]}
			arr[$((j + 1))]=$temp
		fi
	done
done
echo
echo Sorted array is :
for((i=0; i<$n; i++))
do
	echo -n "${arr[$i]} "
done
