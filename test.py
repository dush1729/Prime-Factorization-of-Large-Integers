import random
import sympy
import os

numberList = []
for i in range(0, 18):
    numberList.append(sympy.randprime(pow(10,i), pow(10,i+1)))
    numberList.append(random.randint(pow(10,i), pow(10,i+1)))
numberList = sorted(numberList)

os.system("g++ main.cpp -std=c++11 -fopenmp")
print("              Number           Parallel Time             Serial Time                Speed Up")

for number in numberList:
    os.system("./a.out " + str(number))
os.system("rm ./a.out")