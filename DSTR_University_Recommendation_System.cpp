// DSTR_University_Recommendation_System.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "Message.h"
#include "DateTime.h"
#include "Menu.h"
#include "Form.h"

using namespace std;

void go_to_main_menu();
void go_to_search_university();
void go_to_register();
void go_to_login();

int main()
{
    //std::cout << "Hello University Recommendation System!\n";
    // go_to_main_menu();
	go_to_register();
}

void go_to_main_menu()
{
    int option = Menu::mainMenu();
    // cout << "You choose: " << option << endl;
    system("cls");
    if(option == 1)
    {
        go_to_search_university();
    }
    else if(option == 2)
    {
        go_to_register();
    }
    else if(option == 3)
    {
        // TODOs
        go_to_login();
    }
    else if(option == 4)
    {
        cout << "Thank you for using University Recommendation System!" << endl;
        exit(0);
    }
}

void go_to_search_university()
{
    cout << "This is search university page" << endl;
}

void go_to_register()
{
	int option = Menu::registerPage();
	system("cls");
    if (option == 1)
    {
        //TODOs -> direct register form
		registrationForm();
    }
    else if (option == 2)
    {
		go_to_main_menu();
    }
}

void go_to_login()
{
    cout << "This is login page" << endl;
}

