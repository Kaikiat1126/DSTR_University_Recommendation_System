#pragma once

#include "StatusContainer.h"

// user found => 200
// username found but password wrong => 300
// user not found => 404
// unknown error => 500

int login(std::string username, std::string password)
{
    //TODOs
    //check username and password
    std::string name = "user123";
    std::string pass = "123456";

    bool found = false;
    bool passwordMatch = false;

    // TODOs
    // traversal the user list, find the username, password, role
    // update last modify date

    if(name == username)
    {
        found = true;
        if(pass == password)
        {
            passwordMatch = true;
        }
    }

    if (found)
    {
        if (passwordMatch)
        {
            return 200;
        }
        else
        {
            return 300;
        }
    }
    else
    {
        return 404;
    }
    return 500;
}