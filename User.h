#pragma once
#include <iostream>
#include "IsVector.h"

class User
{
private:
    std::string username;
    std::string password;
    std::string email;
    std::string contactNum;
    std::string role;
	//std::string role = "user";
    //std::string role = "admin";

	IsVector<std::string> favourite;
    
public:
    User(std::string username, std::string password);
    User(std::string username, std::string password, std::string email, std::string contactNum, std::string role);
    std::string getUsername();
    std::string getPassword();
    std::string getEmail();
    std::string getContactNum();
    std::string getRole();
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setEmail(std::string email);
    void setContactNum(std::string contactNum);
    void setRole(std::string role);
    void setDetails(std::string username, std::string password, std::string email, std::string contactNum);
};

User::User(std::string username, std::string password)
{
    this->username = username;
    this->password = password;
}

User::User(std::string username, std::string password, 
    std::string email, std::string contactNum, std::string role)
{
    this->username = username;
    this->password = password;
    this->email = email;
    this->contactNum = contactNum;
    this->role = role;
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
