#include <algorithm>		// std::sort
#include <assert.h>		// assert
#include <iomanip>		// std::setprecision
#include <iostream>		// std::cout
#include <math.h>		// sqrt
#include <omp.h>		// openmp
#include <vector>		// std::vector
#include "parallel.cpp"
#include "serial.cpp"
const int THREADS = 600;

std::vector <long long> primeFactorization(long long number, std::vector <long long> &divisorsList) {
	std::vector <long long> primeFactorsList;
	for(auto divisor: divisorsList) {
		if(divisor == 1) continue;
		while(number % divisor == 0) {
			primeFactorsList.push_back(divisor);
			number /= divisor;
		}
	}
	if(number != 1) primeFactorsList.push_back(number);
	return primeFactorsList;
}

double timeElapsed(long long number, std::vector <long long> &divisorsList, bool serial) {
	struct timespec begin;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	divisorsList = (serial ? findDivisorsSerial(number) : findDivisorsParallel(number, THREADS));
	struct timespec end;
	clock_gettime(CLOCK_MONOTONIC, &end);
	double elapsed=(end.tv_sec - begin.tv_sec) + ((end.tv_nsec - begin.tv_nsec) / 1e9);
	return elapsed;
}

void printPrimeFactorization(long long number, std::vector <long long> &primeFactorsList)
{
	std::cout << number << " = ";
	for(int i = 0; i + 1 < primeFactorsList.size(); i++) {
		std::cout << primeFactorsList[i] << " * ";
	}
	std::cout << primeFactorsList.back() << "\n";
}

void printTime(long long number, double parallelTime, double serialTime) {
	std::cout << std::setw(20) << number << "    ";
	std::cout << std::fixed << std::setprecision(10);
	std::cout << std::setw(20) << parallelTime << "    ";
	std::cout << std::setw(20) << serialTime << "    ";
	double speedUp = serialTime / parallelTime;
	std::cout << std::setw(20) << speedUp << "\n";
}

int main(int argc, char **argv)
{
	// Input number to be factorized, as first command line argument
	long long number = atoll(argv[1]);

	std::vector <long long> divisorsListParallel, divisorsListSerial;
	double parallelTime = timeElapsed(number, divisorsListParallel, false);
	double serialTime = timeElapsed(number, divisorsListSerial, true);
	assert(divisorsListParallel == divisorsListSerial);
	std::vector <long long> primeFactorsList = primeFactorization(number, divisorsListSerial);
	//printPrimeFactorization(number, primeFactorsList);
	printTime(number, parallelTime, serialTime);
}