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
