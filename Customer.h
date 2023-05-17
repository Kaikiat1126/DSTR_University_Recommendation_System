#pragma once

#include<iostream>
#include <string>
#include "User.h"
#include "IsVector.h"
#include "Validation.h"
#include "Menu.h"

class Customer : public User
{
private:
	IsVector<std::string> favourite;
	//static int validOption(std::string, int);
public:
	Customer(std::string username, std::string password);
	Customer(int userID, std::string username, std::string password, std::string email, std::string contactNum, std::string role, IsVector<std::string> favourite);
	IsVector<std::string> getFavourite();
	void setFavourite(IsVector<std::string> favourite);
	void removeFavourite(int index) override;
	void addFavourite(std::string favourite) override;
};

Customer::Customer(std::string username, std::string password) : User(username, password)
{
}

Customer::Customer(int userID, std::string username, std::string password, 
	std::string email, std::string contactNum, std::string role,
	IsVector<std::string> favourite) : User (userID, username, password, email, contactNum, role, favourite)
{
}

//int Customer::validOption(std::string input, int maxOption)
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

IsVector<std::string> Customer::getFavourite()
{
	return IsVector<std::string>();
}

void Customer::setFavourite(IsVector<std::string> favourite)
{
	this->favourite = favourite;
}

void Customer::removeFavourite(int index)
{
	favourite.erase(index);
}

void Customer::addFavourite(std::string favourite)
{
	this->favourite.push_back(favourite);
}