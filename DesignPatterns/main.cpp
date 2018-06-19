#include <iostream>
#include "Strategy.h"
#include "Observer.h"

void printOptions()
{
	std::cout << "Choose an option: " << std::endl;
	std::cout << "1. Strategy Demo" << std::endl;
	std::cout << "2. Observer Demo" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

int main()
{
	int decision;
	do
	{
		printOptions();
		std::cin >> decision;
		std::cout << std::endl;

		switch (decision)
		{
		case 1: 
			StrategyDemo();
			break;
		case 2:
			ObserverDemo();
			break;
		}
		std::cout << std::endl;
	} while (decision != 0);
}