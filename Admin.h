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
	static void displayUser(IsVector<UserStruct>);
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

void Admin::displayUser(IsVector<UserStruct> userList)
{
	if (userList.getSize() == 0)
	{
		std::cout << "                    No user exist                     " << std::endl;
	}

	for (int i = 0; i < userList.getSize(); i++) 
		std::cout << userList.at(i).userID << " " << userList.at(i).username << " " << userList.at(i).lastModifyDate << std::endl;
}

void Admin::displayAllUser()
{
	IsVector<UserStruct> userList = StatusContainer::userBTree.getUserList();
	displayUser(userList);
}

void Admin::displayInactiveUser()
{
	IsVector<UserStruct> userList = StatusContainer::userBTree.getUserByKey("date", DateTime::getCurrentDateTime());
	displayUser(userList);
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

User Admin::searchUser(std::string userId) {
	IsVector<UserStruct> users = StatusContainer::userBTree.getUserByKey("id", userId);
	int id = std::stoi(userId);
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users.at(i).userID == id)
		{
			std::cout << users.at(i).userID;
			User user(users.at(i).userID, users.at(i).username, users.at(i).password, users.at(i).email, users.at(i).contactNum, users.at(i).role);
			return user;
		}
	}

	if (users.getSize() == 0)
	{
		Message::error("User not found");
		User empty_user("", "");
		return empty_user;
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
	bool found = false;
	IsVector<UserStruct> userList = StatusContainer::userBTree.getUserByKey("date", DateTime::getCurrentDateTime());
	for (int i = 0; i < userList.getSize(); i++)
	{
		if (userList.at(i).userID == userId)
		{
			found = true;
			StatusContainer::userBTree.deleteValueFromBTree(userId);
		}
	}

	if (found)
	{
		std::string msg = "User with ID " + std::to_string(userId) + "'s details deleted";
		Message::notice(msg);
	}
	else
	{
		Message::error("Value not found");
	}
}