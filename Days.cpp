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

	std::ifstream file("inputs/day1_1.txt");
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << "Current dial: " << dial << std::endl;
		std::cout << "Instruction: " << line << std::endl;

		if (line.starts_with("L"))
		{
			int change = std::stoi(line.substr(1));
			counter += change / 100;
			change %= 100;
			dial -= change;
		}
		else if (line.starts_with("R"))
		{
			int change = std::stoi(line.substr(1));
			counter += change / 100;
			change %= 100;
			dial += change;
		}
		if (dial < 0 && previousDial > 0) {
			counter++;
			std::cout << "Counter increased by: A" << 1 << std::endl;
		}
		if (dial < 0) {
			dial %= 100;
			dial += 100;
		}
		if (dial >= 100)
		{
			dial %= 100;
		}
		if (dial == 0)
		{
			counter++;
			std::cout << "Counter increased by: B" << 1 << std::endl;
		}
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
