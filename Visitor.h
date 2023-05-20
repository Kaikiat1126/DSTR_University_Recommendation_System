#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include "StatusContainer.h"
#include "Structure.h"
#include "UniversityBTree.h"


class Visitor
{
private:
	static int validOption(std::string, int);
	static void quickAscOrder();
	static void mergeAscOrder();
	static void BTreeSearch(std::string institution);
	static void RedBlackTreeSearch(std::string institution);
public:
	static void displayAllUniversity();
	static void chooseSearchAlgo(std::string uniName);
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
	//StatusContainer::universityList.displayCompleteUniversityList();
	StatusContainer::universityList.displayInPagination();

	bool isContinue = proceedNext("Do you want to Continue Search");
	if (isContinue)
		Visitor::displayAllUniversity();
}

void Visitor::chooseSearchAlgo(std::string institution)
{
	std::cout << "Please select a search algorithm: " << std::endl;
	std::cout << "1. B Tree" << "\t\t" << "2. Red Black Tree" << std::endl;
	
	std::string input = "";
	while (true) {
		std::cout << "> ";
		//std::cin.ignore();
		std::cin >> input;
		int option = validOption(input, 2);
		if (option != -1)
		{
			if (option == 1)
			{
				BTreeSearch(institution);
			}
			else if (option == 2)
			{
				RedBlackTreeSearch(institution);
			}
			break;
		}
	}
}

void Visitor::chooseSortAlgo()
{
	//std::cout << std::endl;
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
	StatusContainer::universityList.quickSort();
}

void Visitor::mergeAscOrder()
{
	StatusContainer::universityList.mergeSort();
}

void Visitor::BTreeSearch(std::string institution)
{
	std::cout << std::endl;
	//std::cout << "B Tree search" << std::endl;
	StatusContainer::universityBTree.searchUniversityByName(institution);
}

void Visitor::RedBlackTreeSearch(std::string institution)
{
	std::cout << "Algorithm 2 search" << std::endl;

	int option = Menu::chooseSearchMethod();
	string msg = "University with name ";

	UniversityRBTreeNode* result;

	if (option == 1) {
		result = StatusContainer::universityRBTree.search(institution);
	}
	else {
		result = StatusContainer::universityRBTree.search(institution, 1);
	}
	if (result) {
		if (result->element) {
			msg = msg + result->element->institution;
			Message::success(msg);
			cout << "Rank: " << result->element->rank << endl;
		}
	}
	else
	{
		msg = msg + institution + " no found";
		Message::warning(msg);
	}
}

