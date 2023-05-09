#pragma once
#include "User.h"
#include "UserList.h"
#include "UniversityList.h"
#include "IsUnorderedMap.h"
#include "BTree.h"

class StatusContainer
{
public:
	static User currentUser;
	static UserList userList;
	static UniversityList universityList;
	static IsUnorderedMap<std::string, std::string, 29> accentLettersMap;
	static BTree universityBTree;
};

User StatusContainer::currentUser = User("", "");
UserList StatusContainer::userList = UserList();
UniversityList StatusContainer::universityList = UniversityList();
IsUnorderedMap<std::string, std::string, 29> StatusContainer::accentLettersMap = IsUnorderedMap<std::string, std::string, 29>();
BTree StatusContainer::universityBTree = BTree();