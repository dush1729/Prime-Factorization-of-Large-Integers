number=1
count=0

g++ main.cpp -std=c++11 -fopenmp
echo "              Number             Serial Time           Parallel Time                Speed Up"

while true
do
	./a.out $number
	count=`expr $count + 1`
	
	# We could simply have written while loop with condition on count < 19
	# but with that solution value of number will overflow
	if [ $count -eq 19 ]
	then
		break
	fi

	number=`expr $number \* 10`
done

rm a.out