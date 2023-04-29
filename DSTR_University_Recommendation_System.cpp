// DSTR_University_Recommendation_System.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "Message.h"
#include "DateTime.h"
#include "Menu.h"
#include "Form.h"
#include "StatusContainer.h"
#include "Authentication.h"
#include "DataHandler.h"

using namespace std;

void go_to_main_menu();
void go_to_search_university();
void go_to_register();
void go_to_login();
void go_to_user_menu();
void go_to_admin_menu();
void verify_second_menu();

void testInitData();

int main()
{
    testInitData();
    //std::cout << "Hello University Recommendatio0n System!\n";
    //go_to_main_menu();
	// go_to_register();
}

void testInitData()
{
    //initUserList();
    //StatusContainer::userList.displayUserList();

	initUniversityList();
	StatusContainer::universityList.displayUniversityList();
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
		bool res = registrationForm();
        if (res)
        {
            system("cls");
            go_to_user_menu();
        }
        else
        {
            go_to_main_menu();
        }
    }
    else if (option == 2)
    {
		go_to_main_menu();
    }
}

void go_to_login()
{
    int option = Menu::loginPage();
    system("cls");
    if (option == 1)
    {
        int login_code = Menu::loginProcess();
        if(login_code == 200)
        {
            Sleep(1000);
            verify_second_menu();
        }
        else
        {
            Sleep(1000);
            system("cls");
            go_to_login();
        }
    }
    else if (option == 2)
    {
        go_to_main_menu();
    }
}

void verify_second_menu()
{
    system("cls");
    string role = StatusContainer::currentUser.getRole();
    if(role == "admin")
    {
        go_to_admin_menu();
    }
    else if(role == "user")
    {
        go_to_user_menu();
    }
    else
    {
        Message::error("Unknown role!");
    }
}

void go_to_user_menu()
{
    cout << "This is user menu page" << endl;
}

void go_to_admin_menu()
{
    cout << "This is admin menu page" << endl;
}