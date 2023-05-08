#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include "User.h"
#include "StatusContainer.h"
#include "Validation.h"

class Admin : public User
{
private:
	static int validOption(std::string, int);
public:
    Admin(std::string username, std::string password);
    Admin(std::string username, std::string password, std::string email, std::string contactNum, std::string role);

	static void displayAllUser();
	static int chooseModify();
	static void modifyUser(User&, int);
};

Admin::Admin(std::string username, std::string password) : User(username, password)
{
}

Admin::Admin(std::string username, std::string password,
    std::string email, std::string contactNum,
    std::string role) : User(username, password, email, contactNum, role)
{
}

int Admin::validOption(std::string input, int maxOption)
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

void Admin::displayAllUser()
{
	//TODOs
	StatusContainer::userList.displayUserList();
}

int Admin::chooseModify()
{
	std::cout << "Please select which details you would like to modify:" << std::endl;
	std::cout << "1. Email" << std::endl;
	std::cout << "2. Contact Number" << std::endl;

	std::string input = "";
	while (true)
	{
		std::cout << "> ";
		std::cin.ignore();
		std::cin >> input;
		int option = validOption(input, 2);
		if (option != -1)
			return option;
	}
}

void Admin::modifyUser(User& user, int option)
{
	if (option == 1)
	{
		std::string email = validation("Enter new email", "", EMAIL_REGEX);
		if (!email.empty()) {
			user.setEmail(email);
			//update data
			Message::success("Email successfully updated!");
		}
	}
	else if (option == 2)
	{
		std::string number = validation("Enter new contact number", "only 8 digits allowed", CONTACT_NUM_REGEX);
		if (!number.empty()) {
			user.setContactNum(number);
			//update data
			Message::success("Contact Number successfully updated!");
		}
	}
	//Display updated user data
	std::cout << std::endl;
	std::cout << "         Updated User Details       " << std::endl;
	std::cout << "************************************" << std::endl;
	std::cout << "Username  : " << user.getUsername() << std::endl;
	std::cout << "Contact   : " << user.getContactNum() << std::endl;
	std::cout << "Email     : " << user.getEmail() << std::endl;
	std::cout << std::endl;
		
}