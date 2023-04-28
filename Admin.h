#pragma once

#include "User.h"

class Admin : public User
{
public:
    Admin(std::string username, std::string password);
    Admin(std::string username, std::string password, std::string email, std::string contactNum, std::string role);
};

Admin::Admin(std::string username, std::string password) : User(username, password)
{
}

Admin::Admin(std::string username, std::string password,
    std::string email, std::string contactNum,
    std::string role) : User(username, password, email, contactNum, role)
{
}