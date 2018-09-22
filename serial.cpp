std::vector <long long> findDivisorsSerial(long long number) {
	long long squareRoot = sqrtl(number);
	std::vector <long long> divisorsList;

	for(int divisor = 1; divisor < squareRoot; divisor++) {
		if(number % divisor != 0) continue;
		divisorsList.push_back(divisor);
		divisorsList.push_back(number / divisor);
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