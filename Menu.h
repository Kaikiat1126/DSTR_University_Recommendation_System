#pragma once
#include <iostream>
#include <string>
#include "Message.h"
#include "DateTime.h"

class Menu
{
private:
	static int validOption(std::string input, int maxOption);
public:
	static int mainMenu();
	static int registerPage();
	static int loginPage();
};


// return -1 is error
int Menu::validOption(std::string input, int maxOption)
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

int Menu::mainMenu() {
	std::string input = "";
	std::cout << "**************************************************************" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "******         University Recommendation System         ******" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Welecome to the University Recommendation System" << std::endl;
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. View University Details" << std::endl;
	std::cout << "2. Register" << std::endl;
	std::cout << "3. Login" << std::endl;
	std::cout << "4. Exit" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 4);
		if (option != -1) 
			return option;
	}
}

int Menu::registerPage() {
	std::string input = "";
	std::cout << "**************************************************************" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "******                 Registration Page                ******" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Register as User" << std::endl;
	std::cout << "2. Back to Main Menu" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 2);
		if (option != -1)
			return option;
	}
}

int Menu::loginPage(){
	std::string input = "";
	std::cout << "**************************************************************" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "******                     Login Page                   ******" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Proceed Login" << std::endl;
	std::cout << "2. Back to Main Menu" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 2);
		if (option != -1)
			return option;
	}
}