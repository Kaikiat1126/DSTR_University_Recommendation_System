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

using namespace std;

void go_to_main_menu();
void go_to_search_university();
void go_to_register();
void go_to_login();
void login_process();
void go_to_user_menu();

int main()
{
    //std::cout << "Hello University Recommendation System!\n";
    go_to_main_menu();
	// go_to_register();
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
            system("cls");
            go_to_user_menu();
        else
		    go_to_main_menu();
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
        login_process();
    }
    else if (option == 2)
    {
        go_to_main_menu();
    }
}

void login_process()
{
    string username, password;

    cout << "Enter your username: " << endl;
    while(true)
    {
        cout << "> ";
        cin >> username;
        if(username == "")
        {
            Message::warning("Username cannot be empty!");
        }
        else
        {
            break;
        }
    }

    cout << "Enter your password: " << endl;
    while(true)
    {
        cout << "> ";
        cin >> password;
        if(password == "")
        {
            Message::warning("Password cannot be empty!");
        }
        else
        {
            break;
        }
    }

    // TODOs -> check login
    // int login_code = login(username, password);
}

void go_to_user_menu()
{
    cout << "This is user menu page" << endl;
}