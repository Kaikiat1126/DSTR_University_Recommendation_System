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
#include "Visitor.h"
#include "Admin.h"

using namespace std;

void go_to_main_menu();
void go_to_search_university();
void go_to_register();
void go_to_login();
void go_to_user_menu();
void go_to_admin_menu();
void verify_second_menu();
void landing_search();
void landing_sort();
void go_to_manage_user();
void go_to_manage_feedback();
void go_to_generate_report();

void testInitData();

int main()
{
    testInitData();
    //std::cout << "Hello University Recommendatio0n System!\n";
    go_to_main_menu();
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

void go_to_search_university()  //Landing page's search university (Vistor Function)
{
    // cout << "This is search university page" << endl;
	Visitor::displayAllUniversity();
	int option = Menu::landingUniMenu();
	//system("cls");
    if (option == 1)
    {
        landing_search();
    }
    else if (option == 2)
    {
        landing_sort();
    }
    else if (option == 3)
    {
		go_to_main_menu();
    }
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

void landing_search()
{
    string uniName = searchUniByName();

    Visitor::chooseSearchAlgo();

    cout << endl;
    bool again = proceedNext("Continue searching for university details?");
	if (again)
	{
		landing_search();
	}
	else
	{
		go_to_main_menu();
	}
}

void landing_sort()
{
    Visitor::chooseSortAlgo();
    
	cout << endl;
	bool again = proceedNext("Continue sorting university details?");
	if (again)
	{
		landing_sort();
	}
	else
	{
		go_to_main_menu();
	}
}

void go_to_user_menu()
{
    cout << "This is user menu page" << endl;
}

void go_to_admin_menu()
{
    int option = Menu::adminPage();

    system("cls");
    if (option == 1) {
        go_to_manage_user();
    }
    else if (option == 2) {
        go_to_manage_feedback();
    }
    else if (option == 3) {
        go_to_generate_report();
    }
    else if (option == 4) {
        go_to_login();
    }
}

void go_to_manage_user()
{
    int option = Menu::manageUserPage();

    system("cls");
    if (option == 1)
    {
        bool again = true;
        while (again) 
        {
            system("cls");
            Menu::modifyUserPage();
            again = proceedNext("Continue modify user detail");
        }

        system("cls");
        go_to_manage_user();
    }
    else if (option == 2)
    {
        //TODOs
        //Display Inactive User (Delete)
    }
    else if (option == 3)
    {
        go_to_admin_menu();
    }
}

void go_to_manage_feedback()
{
    cout << "Manage feedback page" << endl;
}

void go_to_generate_report()
{
    cout << "Generate report page" << endl;
}