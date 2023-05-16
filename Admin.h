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
	//static int validOption(std::string, int);
public:
    Admin(std::string username, std::string password);
	Admin(int userID, std::string username, std::string password, std::string email, std::string contactNum, std::string role);

	static void displayAllUser();
	static void displayInactiveUser();
	static int chooseModify();
	static void modifyUser(User, int);
	static void deleteUser(int);
	static User searchUser(std::string);
	static void displaySelectedUser(User user);
};

Admin::Admin(std::string username, std::string password) : User(username, password)
{
}

Admin::Admin(int userID, std::string username, std::string password, std::string email, std::string contactNum, std::string role) 
	: User(userID, username, password, email, contactNum, role)
{
}

//int Admin::validOption(std::string input, int maxOption)
//{
//	//if input not a number
//	if (input.find_first_not_of("0123456789") != std::string::npos)
//	{
//		Message::error("Invalid input!");
//		return -1;
//	}
//
//	//convert string to int
//	int option = std::stoi(input);
//
//	//if option is not in range
//	if (option < 1 || option > maxOption)
//	{
//		Message::warning("Input option out of range!");
//		return -1;
//	}
//
//	return option;
//}

void Admin::displayAllUser()
{
	IsVector<UserStruct> userList = StatusContainer::userBTree.getUserList();
	for (int i = 0; i < userList.getSize(); i++) {
		std::cout << userList.at(i).userID << " " << userList.at(i).username << std::endl;
	}
	std::cout << "******************************" << std::endl;
}

void Admin::displayInactiveUser()
{
	//TODO
	std::cout << "User list is empty." << std::endl;
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

void Admin::modifyUser(User user, int option)
{
	if (option == 1)
	{
		std::string email = validation("Enter new email", "", EMAIL_REGEX);
		if (!email.empty()) {
			StatusContainer::userBTree.updateValueByID(user.getUserID(), "email", email);
			user.setEmail(email);
		}
	}
	else if (option == 2)
	{
		std::string contact = validation("Enter new contact number", "only 8 digits allowed", CONTACT_NUM_REGEX);
		if (!contact.empty()) {
			StatusContainer::userBTree.updateValueByID(user.getUserID(), "contact", contact);
			user.setContactNum(contact);
		}
	}
	//Display updated user data
	std::cout << std::endl;
	std::cout << "         Updated User Details       " << std::endl;
	std::cout << "************************************" << std::endl;
	displaySelectedUser(user);
		
}

User Admin::searchUser(std::string username) {
	IsVector<UserStruct>* users = new IsVector<UserStruct>();
	StatusContainer::userBTree.searchUserMatch(users, username);

	if (users->getSize() != 0)
	{
		for (int i = 0; i < users->getSize(); i++)
		{
			if (users->at(i).username == username)
			{
				User user(users->at(i).userID, users->at(i).username, users->at(i).password, users->at(i).email, users->at(i).contactNum, users->at(i).role);
				return user;
			}
		}
	}
	else {
		Message::error("User not found");
		User user("", "");
		return user;
	}

}

void Admin::displaySelectedUser(User user) 
{
	//Display updated user data
	std::cout << "Username  : " << user.getUsername() << std::endl;
	std::cout << "Contact   : " << user.getContactNum() << std::endl;
	std::cout << "Email     : " << user.getEmail() << std::endl;
	std::cout << std::endl;
}

void Admin::deleteUser(int userId)
{
	StatusContainer::userList.deleteByUserID(userId);
}