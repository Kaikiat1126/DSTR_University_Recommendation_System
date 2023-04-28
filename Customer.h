#pragma once

#include <string>
#include "User.h"

class Customer : public User
{
private:
	std::string favourite[];
public:
	Customer(std::string username, std::string password);
	Customer(std::string username, std::string password, std::string email, std::string contactNum, std::string role);
	/*std::string getFavourite();
	void setFavourite(std::string favourite);*/
};

Customer::Customer(std::string username, std::string password) : User(username, password)
{
}

Customer::Customer(std::string username, std::string password,
	std::string email, std::string contactNum,
	std::string role) : User(username, password, email, contactNum, role)
{
}
