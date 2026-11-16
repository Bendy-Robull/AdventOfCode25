#include "Days.h"

void dayOneFirstRound()
{
	int dial = 50;
	int counter = 0;

	std::ifstream file("inputs/day1_1.txt");
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << "Current dial: " << dial << std::endl;
		std::cout << "Instruction: " << line << std::endl;

		if (line.starts_with("L"))
		{
			int change = std::stoi(line.substr(1));
			dial -= change;
		}
		else if (line.starts_with("R"))
		{
			int change = std::stoi(line.substr(1));
			dial += change;
		}

		if (dial < 0) {
			//counter += ((-dial) / 100)+1;
			//std::cout << "Counter increased by: " << ((-dial) / 100) + 1 << std::endl;
			dial %= 100;
			dial += 100;
		}
		//else if (dial < 0)
		//	counter += 1;
		//	std::cout << "Counter increased by: " << 1 << std::endl;
		//	dial += 100;
		if (dial >= 100)
		{
			//counter += dial / 100;
			//std::cout << "Counter increased by: " << dial / 100 << std::endl;
			dial %= 100;

		}
		if (dial == 0)
		{
			counter++;
		}
	}
	std::cout << "Day 1 - First Round: " << counter << std::endl;
}

void dayOneSecondRound()
{
	int dial = 50;
	int counter = 0;
	int previousCounter = -1;
	int previousDial = -1;

	std::ifstream file("inputs/day1_1_test.txt");
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << "Current dial: " << dial << std::endl;
		std::cout << "Instruction: " << line << std::endl;

		if (line.starts_with("L"))
		{
			int change = std::stoi(line.substr(1));
			dial -= change;
		}
		else if (line.starts_with("R"))
		{
			int change = std::stoi(line.substr(1));

			dial += change;
		}
		if (dial < 0) {
			if (previousDial != 0) {
				std::cout << "Counter increased by: Minus " << std::abs(dial / 100) + 1 << std::endl;
				counter += std::abs(dial / 100) + 1;
			}
			dial %= 100;
			dial = 100 + dial;
		}
		//if ((previousDial - dial) < 0 || (previousDial - dial)) {
		//	counter++;
		//	std::cout << "Counter increased by: A" << 1 << std::endl;
		//}
		else if (dial >= 100)
		{
			std::cout << "Counter increased by: Plus " << std::abs(dial / 100) << std::endl;
			counter += std::abs(dial / 100);
			dial %= 100;
		}
		//if (dial == 0)
		//{
		//	counter++;
		//	std::cout << "Counter increased by: Zero " << 1 << std::endl;
		//}
		previousDial = dial;
	}
	std::cout << "Day 1 - Second Round: " << counter << std::endl;
}
static bool isRepeatedSequence(unsigned long long n, unsigned minRepeats = 2)
{

	std::string s = std::to_string(n);
	const std::size_t len = s.size();
	if (len == 0 || minRepeats < 2 || len < minRepeats)
		return false;

	// period is the length of the repeating block. The maximum allowed period
	// is len / minRepeats (so repeats >= minRepeats).
	for (std::size_t period = 1; period <= len / minRepeats; ++period)
	{
		if (len % period != 0)
			continue;
		const std::size_t repeats = len / period;
		if (repeats < minRepeats)
			continue;

		bool ok = true;
		// Compare each block to the first block
		for (std::size_t r = 1; r < repeats && ok; ++r)
		{
			if (s.compare(r * period, period, s, 0, period) != 0)
				ok = false;
		}
		if (ok)
			return true;
	}
	return false;
}

void dayTwoFirstRound()
{
	std::ifstream file("inputs/day2.txt");
	std::string line;
	unsigned long long result = 0;
	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
		std::regex reg(",");
		std::vector<std::string> v(std::sregex_token_iterator(line.begin(), line.end(), reg, -1), std::sregex_token_iterator());
		for (std::string s : v)
		{
			std::cout << s << std::endl;
			std::regex reg2("-");
			std::vector<std::string> v2(std::sregex_token_iterator(s.begin(), s.end(), reg2, -1), std::sregex_token_iterator());
			unsigned long long start = std::stoll(v2[0]);
			unsigned long long end = std::stoll(v2[1]);
			std::vector<unsigned long long> q;
			std::mutex mtx;
			std::ranges::iota_view numRange(start, end + 1);
			std::for_each(std::execution::par, numRange.begin(), numRange.end(), [&mtx, &q](auto i) {
				if (isRepeatedSequence(i))
				{
					std::scoped_lock<std::mutex> lock(mtx);
					q.push_back(i);
					//std::cout << "Repeated-twice ID: " << i << std::endl;
				}

				});
			for (auto i : q)
			{
				std::cout << "Repeated-twice ID: " << i << std::endl;
			}
			result += std::accumulate(q.begin(), q.end(), (unsigned long long)0);

		}
	}
	std::cout << "Result: " << result << std::endl;
}

void dayTwoSecondRound()
{
	std::ifstream file("inputs/day2.txt");
	std::string line;
	unsigned long long result = 0;
	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
		std::regex reg(",");
		std::vector<std::string> v(std::sregex_token_iterator(line.begin(), line.end(), reg, -1), std::sregex_token_iterator());
		for (std::string s : v)
		{
			std::cout << s << std::endl;
			std::regex reg2("-");
			std::vector<std::string> v2(std::sregex_token_iterator(s.begin(), s.end(), reg2, -1), std::sregex_token_iterator());
			unsigned long long start = std::stoll(v2[0]);
			unsigned long long end = std::stoll(v2[1]);
			std::vector<unsigned long long> q;
			std::mutex mtx;
			std::ranges::iota_view numRange(start, end + 1);
			std::for_each(std::execution::par, numRange.begin(), numRange.end(), [&mtx, &q](auto i) {
				std::string s = std::to_string(i);
				if (s.size() % 2 == 0 && s.size() >= 4) {
					for (int j = 2; j <= s.size() / 2; j++) {

						if (isRepeatedSequence(i, j))
						{
							std::scoped_lock<std::mutex> lock(mtx);
							q.push_back(i);
							break;
							//std::cout << "Repeated-twice ID: " << i << std::endl;
						}
					}
				}
				else {
					if (isRepeatedSequence(i))
					{
						std::scoped_lock<std::mutex> lock(mtx);
						q.push_back(i);
						//std::cout << "Repeated-twice ID: " << i << std::endl;
					}
				}

				});
			for (auto i : q)
			{
				std::cout << "Repeated-twice ID: " << i << std::endl;
			}
			result += std::accumulate(q.begin(), q.end(), (unsigned long long)0);

		}
	}
	std::cout << "Result: " << result << std::endl;
}

void dayThreeFirstRound()
{
	std::ifstream file("inputs/day3.txt");
	std::string line;
	std::vector<int> results;
	while (std::getline(file, line))
	{
		std::deque<int> row;
		for (char c : line)
		{
			row.push_back(c - '0');
		}
		int max = 0;
		int pos = 0;
		for (int i = 0; i < row.size()-1; i++) {
			if (row[i] > max)
			{
				max = row[i];
				pos = i;
			}
		}
		if (pos == row.size() - 1) {
			results.push_back(max * 10 + row[pos + 1]);
		}
		else
		{
			int otmax = 0;
			for (int i = pos + 1; i < row.size(); i++) {
				if (row[i] > otmax)
				{
					otmax = row[i];
					pos = i;
				}
			}
			std::cout << max * 10 + otmax << std::endl;
			results.push_back(max * 10 + otmax);
		}
	}

	std::cout << "Result: " << std::accumulate(results.begin(), results.end(), (unsigned long long)0) << std::endl;
}

void dayThreeSecondRound()
{

	std::ifstream file("inputs/day3.txt");
	std::string line;
	const std::size_t K = 12; // number of digits to pick (in-order) to maximize the result
	std::vector<unsigned long long> results;

	while (std::getline(file, line))
	{
		// collect digits from the line
		std::vector<int> digits;
		digits.reserve(line.size());
		for (char c : line)
		{
			if (c >= '0' && c <= '9')
				digits.push_back(c - '0');
		}

		if (digits.size() < K)
		{
			// not enough digits; skip or treat as needed
			continue;
		}

		// Greedy, stack-style algorithm to compute the lexicographically largest subsequence of length K
		std::vector<int> chosen;
		chosen.reserve(K);
		std::size_t n = digits.size();

		for (std::size_t i = 0; i < n; ++i)
		{
			int d = digits[i];

			// while we can pop a smaller digit and still be able to fill K digits later, pop it
			while (!chosen.empty()
				&& chosen.back() < d
				&& (chosen.size() - 1 + (n - i)) >= K)
			{
				chosen.pop_back();
			}

			// push if we still need digits
			if (chosen.size() < K)
				chosen.push_back(d);
		}

		// In case chosen is longer than K (defensive), truncate
		if (chosen.size() > K)
			chosen.resize(K);

		// build numeric value (fits in unsigned long long for 12 digits)
		unsigned long long value = 0;
		for (int d : chosen)
			value = value * 10ULL + static_cast<unsigned long long>(d);

		// debug output and store result
		std::cout << "Best 12-digit subsequence: ";
		for (int d : chosen) std::cout << d;
		std::cout << " -> " << value << std::endl;

		results.push_back(value);
	}

	// sum (or otherwise reduce) results as before
	unsigned long long total = std::accumulate(results.begin(), results.end(), (unsigned long long)0);
	std::cout << "Result: " << total << std::endl;
}
