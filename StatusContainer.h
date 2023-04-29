#pragma once
#include "User.h"
#include "UserList.h"
#include "UniversityList.h"

class StatusContainer
{
public:
	static User currentUser;
	static UserList userList;
	static UniversityList universityList;
};

User StatusContainer::currentUser = User("", "");
UserList StatusContainer::userList = UserList();
UniversityList StatusContainer::universityList = UniversityList();