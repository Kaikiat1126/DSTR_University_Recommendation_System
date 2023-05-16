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
void go_to_customer_sort();
void go_to_feedback_page();
void go_to_user_feedback();
void go_to_user_favourites();
void go_to_logout();

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
    initUserData();
    //StatusContainer::userList.displayUserList();
	//StatusContainer::userBTree.traversal();
    
    //IsVector<UserStruct>* users = new IsVector<UserStruct>();
    //StatusContainer::userBTree.searchUserMatch(users, "John");

	initUniversityData();
	//StatusContainer::universityList.displayUniversityList();
 
    /*int* type = new int;
    *type = 1;
    int* range = new int;
    *range = 0;
    string* value = new string;
    *value = "University of Cambridge";
    IsVector<UniversityStruct> universities = StatusContainer::universityBTree.getUniversityByValue(type, range, value);

    for (int i = 0; i < universities.getSize(); i++)
    {
        cout << universities.at(i).rank << " " << universities.at(i).institution << endl;
    }*/

	//StatusContainer::universityBTree.traversal();
    //StatusContainer::universityBTree.searchUniversityByRank(867);   //1-2ms 
    //StatusContainer::universityBTree.preOrder();
	//StatusContainer::universityBTree.postOrder();
}

void go_to_main_menu()
{
	system("cls");
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
    cout << endl;
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
    string role = StatusContainer::currentUser->getRole();
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

    Visitor::chooseSearchAlgo(uniName);

    cout << endl;
    bool again = proceedNext("Continue searching for university details");
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
	bool again = proceedNext("Continue sorting university details");
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
    system("cls");
    int option = Menu::userPage();

    system("cls");
    if (option == 1) 
    {
        cout << "Search University" << endl;
    }
    else if (option == 2) 
    {
        go_to_user_favourites();
    }
    else if (option == 3) 
    {
        Menu::feedbackPage();
        
        go_to_feedback_page();
    }
    else if (option == 4)
	{
		go_to_logout();
	}
}

void go_to_admin_menu()
{
    int option = Menu::adminPage();

    system("cls");
    if (option == 1) {
        go_to_manage_user();
    }
    else if (option == 2) {
        go_to_feedback_page();
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
    bool again = true;

    system("cls");
    if (option == 1)
    {
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
        while (again)
        {
            system("cls");
            Menu::inactiveUserPage();
            again = proceedNext("Continue delete user?");
        }

        system("cls");
        go_to_manage_user();
    }
    else if (option == 3)
    {
        go_to_admin_menu();
    }
}

void go_to_feedback_page()
{
    string role = StatusContainer::currentUser->getRole();
    if (role == "admin")
    {
        go_to_manage_feedback();
    }
    else if (role == "user")
    {
        go_to_user_feedback();
    }
    else
    {
        Message::error("Unknown role!");
    }
}

//void go_to_manage_feedback()
//{
//    cout << "Manage feedback page" << endl;
//
//    while (true) {
//        int option = Menu::manageFeedbackPage();
//        system("cls");
//        if (option == 1) {
//            std::cout << "Reply: ~~~~~~~~~~~~~~~~" << std::endl;
//        }
//        else if (option == 2) {
//            std::cout << "Next: :)))))))))))))))" << std::endl;
//        }
//        else if (option == 3) {
//            std::cout << "Previous: :((((((((((((((" << std::endl;
//        }
//        else if (option == 4) {
//            break;
//        }
//    } 
//    go_to_admin_menu();
//}

// TODO
void go_to_manage_feedback()
{
    while (true)
    {
        int option = Menu::manageFeedbackPage();
        if (option == 1)
        {
            cout << "Reply Feedback" << endl;
        }
        else if (option == 2)
        {
            cout << "Move Forward" << endl;
        }
        else if (option == 3)
        {
            cout << "Move Backward" << endl;
        }
        else if (option == 4)
        {
            break;
        }
    }
    go_to_admin_menu();
}

// TODO
void go_to_user_feedback()
{
    while (true)
    {
        int option = Menu::userFeedbackPage();
        if (option == 1)
        {
			cout << "Move Forward" << endl;
		}
		else if (option == 2)
		{
			cout << "Move Backward" << endl;
		}
		else if (option == 3)
		{
			break;
        }
    }
	go_to_user_menu();
}

void go_to_user_favourites() 
{
    int option = Menu::userFavouritePage();
    
	if (option == 1) 
    {
        int index = Menu::deleteFavourite();
        if (index != -1)
        {
            StatusContainer::currentUser->removeFavourite(index);

            int userID = StatusContainer::currentUser->getUserID();
		    StatusContainer::userBTree.removeUserFavourite(userID, index);
        }
        
        if (index == -1)
        {
			Message::warning("No favourite can be deleted!");
            Sleep(2000);
        }
		
		system("cls");
        go_to_user_favourites();
	}
	else if (option == 2) 
    {
		go_to_user_menu();
	}
}

void go_to_generate_report()
{
    cout << "Generate report page" << endl;
}

void go_to_customer_sort()
{
    // TODO
}

void go_to_logout()
{
	bool logout = proceedNext("Do you want to logout");

    if (logout)
    {
        StatusContainer::currentUser = nullptr;
		go_to_main_menu();
    }
    else
		verify_second_menu();	
}
