#pragma once

#include "StatusContainer.h"
#include "IsVector.h"
#include "Structure.h"
#include "User.h"
#include "Admin.h"
#include "Customer.h"

int login(std::string username, std::string password);
void setLoginStatus(UserStruct user);

// user found => 200
// username found but password wrong => 300
// user not found => 404
// unknown error => 500

int login(std::string username, std::string password)
{
    bool found = false;
    bool passwordMatch = false;

	IsVector<UserStruct>* users = new IsVector<UserStruct>();
	StatusContainer::userBTree.searchUserMatch(users, username);

	if (users->getSize() == 0)
	{
		return 404;
	}

    for (int i = 0; i < users->getSize(); i++)
    {
        if (users->at(i).username == username)
        {
            found = true;
            if (users->at(i).password == password)
            {
                passwordMatch = true;
				
				StatusContainer::userBTree.updateValueByID(users->at(i).userID, "date", DateTime::getCurrentDateTime());
				setLoginStatus(users->at(i));
                break;
            }
        }
    }
    
	if (found && passwordMatch)
	{
		return 200;
	}
	else if (found && !passwordMatch)
	{
		return 300;
	}
	else
	{
		return 500;
	}
}

void setLoginStatus(UserStruct user)
{
	if (user.role == "user")
		StatusContainer::currentUser = new Customer(user.userID, user.username, user.password, user.email, user.contactNum, user.role, user.favourite);
	else
		StatusContainer::currentUser = new Admin(user.userID, user.username, user.password, user.email, user.contactNum, user.role);
}