#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include "StatusContainer.h"

class Visitor
{
private:
	static int validOption(std::string, int);
	static void quickAscOrder();
	static void mergeAscOrder();
	static void algo1Search();
	static void algo2Search();
public:
	static void displayAllUniversity();
	static void chooseSearchAlgo();
	static void chooseSortAlgo();
};

int Visitor::validOption(std::string input, int maxOption)
{
	//if input not a number
	if (input.find_first_not_of("0123456789") != std::string::npos)
	{
		Message::error("Invalid input!");
		return -1;
	}

	//convert string to int
	int option = std::stoi(input);

	//if option is not in range
	if (option < 1 || option > maxOption)
	{
		Message::warning("Input option out of range!");
		return -1;
	}

	return option;
}


void Visitor::displayAllUniversity()
{
	// std::cout << "Display all university" << std::endl;
	// TODOs
	StatusContainer::universityList.displayUniversityList();
}

void Visitor::chooseSearchAlgo()
{
	std::cout << std::endl;
	std::cout << "Please select a search algorithm: " << std::endl;
	std::cout << "1. Search 1" << "\t\t" << "2. Search 2" << std::endl;
	
	std::string input = "";
	while (true) {
		std::cout << "> ";
		std::cin.ignore();
		std::cin >> input;
		int option = validOption(input, 2);
		if (option != -1)
		{
			if (option == 1)
			{
				algo1Search();
			}
			else if (option == 2)
			{
				algo2Search();
			}
			break;
		}
	}
}

void Visitor::chooseSortAlgo()
{
	std::cout << std::endl;
	std::cout << "Please select a sort algorithm: " << std::endl;
	std::cout << "1. Quick Sort" << "\t\t" << "2. Merge Sort" << std::endl;

	std::string input = "";
	while (true)
	{
		std::cout << "> ";
		std::cin.ignore();
		std::cin >> input;
		int option = validOption(input, 2);
		if (option != -1)
		{
			if (option == 1)
			{
				quickAscOrder();
			}
			else if (option == 2)
			{
				mergeAscOrder();
			}
			break;
		}
	}
}

void Visitor::quickAscOrder()
{
	std::cout << "Quick sort in ascending order" << std::endl;
	// TODOs
}

void Visitor::mergeAscOrder()
{
	std::cout << "Merge sort in ascending order" << std::endl;
	// TODOs
}

void Visitor::algo1Search()
{
	std::cout << "Algorithm 1 search" << std::endl;
	// TODOs
}

void Visitor::algo2Search()
{
	std::cout << "Algorithm 2 search" << std::endl;
	// TODOs
}