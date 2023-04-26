#pragma once
#include "User.h"

class StatusContainer
{
public:static User currentUser;
};

User StatusContainer::currentUser = User("", "");