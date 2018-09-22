std::vector <long long> findDivisorsParallel(long long number, int threads) {
	long long squareRoot = sqrt(number);
	std::vector <long long> divisorsList;

	omp_set_num_threads(threads);
	#pragma omp parallel
	{
		std::vector <long long> temporaryDivisorsList;
		#pragma omp for nowait
		for(int divisor = 1; divisor < squareRoot; divisor++) {
			if(number % divisor != 0) continue;
			temporaryDivisorsList.push_back(divisor);
			temporaryDivisorsList.push_back(number / divisor);
		}

		#pragma omp critical
		{
			divisorsList.insert(divisorsList.end(),
				temporaryDivisorsList.begin(),temporaryDivisorsList.end());
		}
	}

	/*
		If number is a perfect square then
		we need to avoid inserting square root
		in divisor list twice
	*/
	if(number % squareRoot == 0) {
		divisorsList.push_back(squareRoot);
		if(squareRoot * squareRoot != number) {
			divisorsList.push_back(number / squareRoot);
		}
	}

	sort(divisorsList.begin(), divisorsList.end());
	return divisorsList;
}