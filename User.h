#pragma once
#include <iostream>

class User
{
private:
    std::string username;
    std::string password;
    std::string email;
    std::string contactNum;
public:
    User(std::string username, std::string password);
    std::string getUsername();
    std::string getPassword();
    std::string getEmail();
    std::string getContactNum();
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setEmail(std::string email);
    void setContactNum(std::string contactNum);
    void setDetails(std::string username, std::string password, std::string email, std::string contactNum);
};

User::User(std::string username, std::string password)
{
    this->username = username;
    this->password = password;
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

void User::setDetails(std::string username, std::string password, std::string email, std::string contactNum)
{
    this->username = username;
    this->password = password;
    this->email = email;
    this->contactNum = contactNum;
}
