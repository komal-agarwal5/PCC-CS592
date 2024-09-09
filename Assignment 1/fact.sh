echo Enter a number
read n
if [ $n -lt 0 ]
then
	echo Factorial not possible for negative number
	exit 1
fi
p=1
for (( i=1; i<=$n; i++ ))
do
	p=$(expr $p \* $i)
done
echo Factorial of number is $p

