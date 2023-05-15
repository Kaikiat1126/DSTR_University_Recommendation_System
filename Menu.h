#pragma once
#include <iostream>
#include <string>
#include "Message.h"
#include "DateTime.h"
#include "Authentication.h"
#include "Admin.h"
#include "Validation.h"
#include "StatusContainer.h"

class Menu
{
private:
	static int validOption(std::string input, int maxOption);
public:
	static int mainMenu();
	static int registerPage();
	static int loginPage();
	static int loginProcess();
	static int landingUniMenu();
	static int adminPage();
	static int manageUserPage();
	static void modifyUserPage();
	static void inactiveUserPage();
	static int userPage();
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

int Menu::loginProcess(){
	std::string password = "";
	std::string username = "";

	std::cout << "Enter your username: " << std::endl;
    while(true)
    {
        std::cout << "> ";
        std::cin >> username;
        if(username == "")
        {
            Message::warning("Username cannot be empty!");
        }
        else
        {
            break;
        }
    }

    std::cout << "Enter your password: " << std::endl;
    while(true)
    {
        std::cout << "> ";
        std::cin >> password;
        if(password == "")
        {
            Message::warning("Password cannot be empty!");
        }
        else
        {
            break;
        }
    }

	int login_code = login(username, password);

	if(login_code == 200)
	{
		Message::success("Login successfully!");
	}
	else if(login_code == 300)
	{
		Message::warning("Wrong password!");
	}
	else if(login_code == 404)
	{
		Message::error("User not found!");
	}
	else
	{
		Message::error("Unknown error!");
	}

	return login_code;
}

int Menu::landingUniMenu() {
	std::string input = "";
	std::cout << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Search Individual University Details by Universtiy Name" << std::endl;
	std::cout << "2. Display Sorting Result in Ascending Order by University Name" << std::endl;
	std::cout << "3. Back to Main Menu" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 3);
		if (option != -1)
			return option;
	}
}

int Menu::adminPage() {
	std::string input = "";
	std::cout << "**************************************************************" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "******                     Admin Page                   ******" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Manage User" << std::endl;
	std::cout << "2. Manage Feedback" << std::endl;
	std::cout << "3. Generate Report" << std::endl;
	std::cout << "4. Logout" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 4);
		if (option != -1)
			return option;
	}
}

int Menu::manageUserPage() {
	std::string input = "";

	Admin::displayAllUser();
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Modify User Details" << std::endl;
	std::cout << "2. Display Inactive User" << std::endl;
	std::cout << "3. Back to Admin Page" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 3);
		if (option != -1)
			return option;
	}
}

void Menu::modifyUserPage() {
	std::string userId = "";

	Admin::displayAllUser();
	std::cout << "**************************************************************" << std::endl;

	userId = validation("Modify Existing User Detail", "Enter User ID", USER_ID_REGEX);

	//TODO: search user
	//if user found
	bool found = true;
	//User user("user123","123456","user@mail.com","0123456789","user");

	if (found) {
		system("cls");
		//displaySelectedUserDetail
		std::cout << std::endl;
		std::cout << "          User Details            " << std::endl;
		std::cout << "**********************************" << std::endl;
		std::cout << "Username  : " << StatusContainer::currentUser->getUsername() << std::endl;
		std::cout << "Contact   : " << StatusContainer::currentUser->getContactNum() << std::endl;
		std::cout << "Email     : " << StatusContainer::currentUser->getEmail() << std::endl;
		std::cout << std::endl;

		int option = Admin::chooseModify();
		//Admin::modifyUser(user, option);
	}
	else
	{
		Message::error("User not found!");
	}
}

void Menu::inactiveUserPage()
{
	std::string userId = "";

	std::cout << "                        Inactive User                         " << std::endl;
	std::cout << "**************************************************************" << std::endl;
	Admin::displayInactiveUser();
	std::cout << "**************************************************************" << std::endl;

	userId = validation("Delete Inactive User", "Enter User ID", USER_ID_REGEX);

	int id = stoi(userId);
	Admin::deleteUser(id);
}

int Menu::userPage()
{
	string input = "";
	std::cout << "**************************************************************" << endl;
	std::cout << "******                                                  ******" << endl;
	std::cout << "******                     User Page                    ******" << endl;
	std::cout << "******                                                  ******" << endl;
	std::cout << "**************************************************************" << endl;
	std::cout << "Please select an option below:" << endl;
	std::cout << "1. Search University" << endl;
	std::cout << "2. Favourite University" << endl;
	std::cout << "3. Feedback" << endl;
	std::cout << "4. Logout" << endl;
	
	while (true) {
		std::cout << "> ";
		cin >> input;
		int option = validOption(input, 4);
		if (option != -1)
			return option;
	}
}
