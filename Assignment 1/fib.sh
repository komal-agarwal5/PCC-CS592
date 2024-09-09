echo Enter value of n
read n
if [ $n -le 0 ]
then
	echo Invalid input
	exit 1
fi
f0=0
f1=1
f2=0
echo Fibonacci series is :
echo $f0
for (( i=2; i<=$n; i++ ))
do
	echo $f1
	f2=$((f0 + f1))
	f0=$f1
	f1=$f2
done
