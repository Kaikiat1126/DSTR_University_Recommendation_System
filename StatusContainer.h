#pragma once
#include "User.h"
#include "UserList.h"
#include "UniversityList.h"
#include "IsUnorderedMap.h"
#include "BTree.h"
#include "UniversityBTree.h"
#include "UserBTree.h"

class StatusContainer
{
public:
	static User* currentUser;
	static UserList userList;
	static UserBTree userBTree;
	static UniversityList universityList;
	static IsUnorderedMap<std::string, std::string, 29> accentLettersMap;
	static UniversityBTree universityBTree;
protected:
	
};

//User* StatusContainer::currentUser = new User("", "");
User* StatusContainer::currentUser = nullptr;
UserList StatusContainer::userList = UserList();
UserBTree StatusContainer::userBTree = UserBTree();
UniversityList StatusContainer::universityList = UniversityList();
IsUnorderedMap<std::string, std::string, 29> StatusContainer::accentLettersMap = IsUnorderedMap<std::string, std::string, 29>();
UniversityBTree StatusContainer::universityBTree = UniversityBTree();