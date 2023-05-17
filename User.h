#pragma once
#include <iostream>
#include "IsVector.h"

class User
{
private:
	int userID;
    std::string username;
    std::string password;
    std::string email;
    std::string contactNum;
    std::string role;
	//std::string role = "user";
    //std::string role = "admin";

	IsVector<std::string> favourite;

protected:
	static int validOption(std::string, int);
    
public:
    User(std::string username, std::string password);
    User(int userID, std::string username, std::string password, std::string email, std::string contactNum, std::string role);
	User(int userID, std::string username, std::string password, std::string email, std::string contactNum, std::string role, IsVector<std::string> favourite);
    int getUserID();
    std::string getUsername();
    std::string getPassword();
    std::string getEmail();
    std::string getContactNum();
    std::string getRole();
	IsVector<std::string> getFavourite();
    void setUserID(int userID);
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setEmail(std::string email);
    void setContactNum(std::string contactNum);
    void setRole(std::string role);
    void setDetails(std::string username, std::string password, std::string email, std::string contactNum);
	void setFavourite(IsVector<std::string> favourite);
    virtual void removeFavourite(int);
    virtual void addFavourite(std::string);
    bool checkFavouriteExist(std::string name);
};

User::User(std::string username, std::string password)
{
    this->username = username;
    this->password = password;
}

User::User(int userID, std::string username, std::string password, std::string email, std::string contactNum, std::string role)
{
	this->userID = userID;
	this->username = username;
	this->password = password;
	this->email = email;
	this->contactNum = contactNum;
	this->role = role;
}

User::User(int userID, std::string username, std::string password, 
    std::string email, std::string contactNum, std::string role, IsVector<std::string> favourite)
{
	this->userID = userID;
    this->username = username;
    this->password = password;
    this->email = email;
    this->contactNum = contactNum;
    this->role = role;
	this->favourite = favourite;
}

int User::getUserID()
{
    return this->userID;
}

std::string User::getUsername()
{
    return this->username;
}

std::string User::getPassword()
{
    return this->password;
}

std::string User::getEmail()
{
    return this->email;
}

std::string User::getContactNum()
{
    return this->contactNum;
}

std::string User::getRole()
{
	return this->role;
}

IsVector<std::string> User::getFavourite()
{
	return this->favourite;
}

void User::setUserID(int userID)
{
    this->userID = userID;
}

void User::setUsername(std::string username)
{
    this->username = username;
}

void User::setPassword(std::string password)
{
    this->password = password;
}

void User::setEmail(std::string email)
{
    this->email = email;
}

void User::setContactNum(std::string contactNum)
{
    this->contactNum = contactNum;
}

void User::setRole(std::string role)
{
	this->role = role;
}

void User::setDetails(std::string username, std::string password, std::string email, std::string contactNum)
{
    this->username = username;
    this->password = password;
    this->email = email;
    this->contactNum = contactNum;
}

void User::setFavourite(IsVector<std::string> favourite)
{
	this->favourite = favourite;
}

int User::validOption(std::string input, int maxOption)
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

void User::removeFavourite(int index)
{
    favourite.erase(index);
}

void User::addFavourite(std::string favourite)
{
    this->favourite.push_back(favourite);
}

bool User::checkFavouriteExist(std::string name)
{
    bool found = false;
    name.erase(std::remove(name.begin(), name.end(), ' '), name.end());

	if (favourite.empty())
        return false;
    else
    {
        for (int i = 0; i < favourite.getSize(); i++)
        {
            std::string value = favourite.at(i);
            value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
            if (value == name)
            {
                found = true;
            }
        }
        return found;
    }
}