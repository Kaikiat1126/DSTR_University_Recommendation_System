#pragma once

#include <iostream>
#include <string>
#include <chrono>

class Visitor
{
public:
	static void displayAllUniversity();
	static void quickAscOrder();
	static void mergeAscOrder();
	static void algo1Search();
	static void algo2Search();
};


void Visitor::displayAllUniversity()
{
	std::cout << "Display all university" << std::endl;
	// TODOs
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