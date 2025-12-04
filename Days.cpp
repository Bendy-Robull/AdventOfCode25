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
