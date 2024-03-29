#pragma once
#include <iostream>
#include <string>
#include "Message.h"
#include "DateTime.h"
#include "Authentication.h"
#include "Admin.h"
#include "Validation.h"
#include "StatusContainer.h"
#include "Feedback.h"

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
	static int manageFeedbackPage();
	static void modifyUserPage();
	static void inactiveUserPage();
	
	static int userPage();
	static void feedbackPage();
	static int userFeedbackPage();
	static void searchUniPage();
	static int searchUniOption();
	static int chooseSearchMethod();
	static int selectScoreRange();
	static int selectRankingRange();
	static int userFavouritePage();
	static int deleteFavourite();
	static int optionBeforeEndSearch();
	static int choosePage(int size);
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
	std::cout << "Welcome to the University Recommendation System" << std::endl;
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

		password = encrypPassword();
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

	std::cout << "**************************************************************" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "******                 Manage User Page                 ******" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
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

	std::cout << "              Existing User                " << std::endl;
	std::cout << "*******************************************" << std::endl;
	Admin::displayAllUser();
	std::cout << "*******************************************" << std::endl;

	userId = validation("Modify Existing User Detail", "Enter User ID", USER_ID_REGEX);
	User user = Admin::searchUser(userId);

	if (user.getUsername() != "") {
		system("cls");
		std::cout << "          User details            " << std::endl;
		std::cout << "**********************************" << std::endl;
		Admin::displaySelectedUser(user);
		int option = Admin::chooseModify();
		Admin::modifyUser(user, option);
	}
	
}

void Menu::inactiveUserPage()
{
	std::string userId = "";

	std::cout << "               Inactive User               " << std::endl;
	std::cout << "*******************************************" << std::endl;
	Admin::displayInactiveUser();
	std::cout << "********************************************" << std::endl;

	userId = validation("Delete Inactive User", "Enter User ID", USER_ID_REGEX);

	int id = stoi(userId);
	Admin::deleteUser(id);
}

int Menu::userPage()
{
	std::string input = "";
	std::cout << "**************************************************************" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "******                     User Page                    ******" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Search University" << std::endl;
	std::cout << "2. Favourite University" << std::endl;
	std::cout << "3. Feedback" << std::endl;
	std::cout << "4. Logout" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 4);
		if (option != -1)
			return option;
	}
}

void Menu::feedbackPage()
{
	std::cout << "**************************************************************" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "******                   Feedback Page                  ******" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "**************************************************************" << std::endl;
}

int Menu::manageFeedbackPage() {
	std::string input = "";
	feedbackPage();
		
	StatusContainer::feedbackList.displayCurrent();
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Reply" << std::endl;
	std::cout << "2. Move Forward" << std::endl;
	std::cout << "3. Move Backward" << std::endl;
	std::cout << "4. Display All Feedback" << std::endl;
	std::cout << "5. Back to Admin Menu" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 5);
		if (option != -1)
			return option;
	}
}

int Menu::userFeedbackPage()
{
	std::string input = "";

	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Move Forward" << std::endl;
	std::cout << "2. Move Backward" << std::endl;
	std::cout << "3. Back to User Menu" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 3);
		if (option != -1)
			return option;
	}
}

int Menu::userFavouritePage()
{
	std::string input = "";
	//IsVector<string> favs = StatusContainer::currentUser->getFavourite();
	IsVector<string> favs = StatusContainer::userBTree.getUserFavouritesByID(StatusContainer::currentUser->getUserID());
	
	std::cout << "                     Favourite Universities                   " << std::endl;
	std::cout << "**************************************************************" << std::endl;
	if (favs.getSize() == 0)
		std::cout << "\t\tNo result can display" << std::endl;
	for (int i = 0; i < favs.getSize(); i++)
	{
		std::cout << i+1 << "\t" << favs.at(i) << std::endl;
	}
	std::cout << "**************************************************************" << std::endl;
	std::cout << std::endl;

	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Remove Favourite By ID" << std::endl;
	std::cout << "2. Back to User Menu" << std::endl;
	
	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 2);
		// if favs.size is 0 and option is 1, return -2(no favourite can remove)
		// if favs.size not 0 and option is 1, return option
		// if option is 2, return option
		if (option != -1 && option == 2 || option == 1 && favs.getSize() != 0)
			return option;
		else if (option == 1 && favs.getSize() == 0)
			return -2;
	}
}

int Menu::deleteFavourite()
{
	std::cout << std::endl;
	std::string num;
	std::cout << "Please enter the number of the favourite you want to remove: " << std::endl;
	while (true)
	{
		std::cout << "> ";
		std::cin >> num;
		int option = validOption(num, StatusContainer::currentUser->getFavourite().getSize());
		if (option != -1)
			return option-1;
	}
}

int Menu::chooseSearchMethod() {
	std::string input = "";
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Recursive Search" << std::endl;
	std::cout << "2. Iterative Search" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 2);
		if (option != -1)
			return option;
	}
}

void Menu::searchUniPage()
{
	std::cout << "**************************************************************" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "******                 Search University                ******" << std::endl;
	std::cout << "******                                                  ******" << std::endl;
	std::cout << "**************************************************************" << std::endl;
}

int Menu::searchUniOption()
{
	std::string input = "";
	std::cout << "Please select an option below:" << std::endl; 
	std::cout << "1. University Location" << std::endl; 
	std::cout << "2. Academic Reputation Score (AR Score)" << std::endl;
	std::cout << "3. Faculty Student Score (FSR Score)" << std::endl;
	std::cout << "4. Employer Reputation Score (ER Score)" << std::endl;
	std::cout << "5. Back to User Page" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 5);
		if (option != -1)
			return option;
	}
}

int Menu::selectScoreRange()
{
	std::string input = "";
	std::cout << std::endl;
	std::cout << "Please select a score range below:" << std::endl;
	std::cout << "1. 0 - 20" << std::endl;
	std::cout << "2. 21 - 40" << std::endl;
	std::cout << "3. 41 - 60" << std::endl;
	std::cout << "4. 61 - 80" << std::endl;
	std::cout << "5. 81 - 100" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 5);
		if (option != -1)
			return option;
	}
}

int Menu::selectRankingRange()
{
	std::string input = "";
	std::cout << std::endl;
	std::cout << "Please select a ranking range below:" << std::endl;
	std::cout << "1. 1 - 100" << std::endl;
	std::cout << "2. 101 - 300" << std::endl;
	std::cout << "3. 301 - 500" << std::endl;
	std::cout << "4. 501 - 800" << std::endl;
	std::cout << "5. 801 - 1200" << std::endl;
	std::cout << "6. 1201+" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 6);
		if (option != -1)
			return option;
	}
}

int Menu::optionBeforeEndSearch()
{
	std::string input = "";
	std::cout << std::endl;
	std::cout << "Please select an option below:" << std::endl;
	std::cout << "1. Save Favourite University" << std::endl;
	std::cout << "2. Send Feedback for Futher Information" << std::endl;
	std::cout << "3. Quit" << std::endl;

	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, 3);
		if (option != -1)
			return option;
	}
}

int Menu::choosePage(int size)
{
	int item = size / 50;
	std::string input = "";
	
	if (item > 0) {
		cout << "Choose Page: ( 1 ~ " << item+1 << " )";
	}
	else {
		Message::warning("No item found");
		return 0;
	}
	while (true) {
		std::cout << "> ";
		std::cin >> input;
		int option = validOption(input, item+1);
		if (option != -1)
			return option;
	}
}