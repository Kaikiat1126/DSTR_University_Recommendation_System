#pragma once

#include <string>
#include "User.h"
#include "IsVector.h"

class Customer : public User
{
private:
	IsVector<std::string> favourite;
public:
	Customer(std::string username, std::string password);
	Customer(int userID, std::string username, std::string password, std::string email, std::string contactNum, std::string role, IsVector<std::string> favourite);
	IsVector<std::string> getFavourite();
	void setFavourite(IsVector<std::string> favourite);
};

Customer::Customer(std::string username, std::string password) : User(username, password)
{
}

Customer::Customer(int userID, std::string username, std::string password, 
	std::string email, std::string contactNum, std::string role,
	IsVector<std::string> favourite) : User (userID, username, password, email, contactNum, role, favourite)
{
}

IsVector<std::string> Customer::getFavourite()
{
	return IsVector<std::string>();
}

void Customer::setFavourite(IsVector<std::string> favourite)
{
	this->favourite = favourite;
}