#pragma once
#include <iostream>
#include <string>
#include "Message.h"
#include "DateTime.h"

class Menu
{
public:
	static int mainMenu();
	static int registerPage();
	static int loginPage();
};