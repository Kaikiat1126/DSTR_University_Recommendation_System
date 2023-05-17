#pragma once
#include "User.h"
#include "UserList.h"
#include "UniversityList.h"
#include "IsUnorderedMap.h"
#include "BTree.h"
#include "UniversityBTree.h"
#include "UserBTree.h"
#include "RBTree.h"

class StatusContainer
{
public:
	static User* currentUser;
	static UserList userList;
	static UserBTree userBTree;
	static UniversityList universityList;
	static UniversityList* cacheUniList;
	static IsUnorderedMap<std::string, std::string, 29> accentLettersMap;
	static UniversityBTree universityBTree;
	static UniversityRBTree universityRBTree;
};

User* StatusContainer::currentUser = nullptr;
UserList StatusContainer::userList = UserList();
UserBTree StatusContainer::userBTree = UserBTree();
UniversityList StatusContainer::universityList = UniversityList();
UniversityList* StatusContainer::cacheUniList = nullptr;
IsUnorderedMap<std::string, std::string, 29> StatusContainer::accentLettersMap = IsUnorderedMap<std::string, std::string, 29>();
UniversityBTree StatusContainer::universityBTree = UniversityBTree();
UniversityRBTree StatusContainer::universityRBTree = UniversityRBTree();