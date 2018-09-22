number=1
count=0

g++ main.cpp -std=c++11 -fopenmp
echo "              Number             Serial Time           Parallel Time                Speed Up"

while [ $count -lt 18 ]
do
	./a.out $number
	number=`expr $number \* 10`
	count=`expr $count + 1`
done