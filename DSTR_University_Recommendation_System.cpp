// DSTR_University_Recommendation_System.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "Message.h"
#include "DateTime.h"
#include "Menu.h"

using namespace std;

void runTest();

void runTest()
{
    int option = Menu::mainMenu();
    cout << "You choose: " << option << endl;
}

int main()
{
    //std::cout << "Hello University Recommendation System!\n";
	runTest();
}

