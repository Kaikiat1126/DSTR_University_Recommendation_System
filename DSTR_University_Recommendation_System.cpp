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
#include "Validation.h"
#include "UniversityList.h"
#include "IsUnorderedMap.h"

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
void go_to_feedback_page();
void go_to_user_feedback();
void go_to_user_favourites();
void go_to_user_search();
bool go_to_end_search();
void go_to_logout();

int main()
{    
    readFiletoStruture();
    go_to_main_menu();
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
        Menu::searchUniPage();
        
        go_to_user_search();
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
        go_to_logout();
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

void go_to_manage_feedback()
{
    FeedbackNode* latest = StatusContainer::feedbackList.getLatestFeedback();
    while (true)
    {
        string user = StatusContainer::currentUser->getUsername();
        int option = Menu::manageFeedbackPage();
        system("cls");
        if (option == 1)
        {
            string comment = "";
            cout << "Reply: ";
            cin.ignore();
            getline(cin, comment);
            
            StatusContainer::feedbackList.replyFeedback(comment, user);
            Message::success("Reply Successfully");
        }
        else if (option == 2)
        {
            StatusContainer::feedbackList.getNextFeedback();
        }
        else if (option == 3)
        {
            StatusContainer::feedbackList.getPrevFeedback(); 
        }
        else if (option == 4)
        {
            StatusContainer::feedbackList.display();
            system("pause");
            system("cls");
        }
        else if (option == 5)
        {
            break;
        }
    }
    go_to_admin_menu();
}

void go_to_user_feedback()
{
    StatusContainer::feedbackList.getLatestFeedback();
    StatusContainer::feedbackList.displayCurrent();
    while (true)
    {
        int option = Menu::userFeedbackPage();
        system("cls");
        if (option == 1)
        {
			//cout << "Move Forward" << endl;
            StatusContainer::feedbackList.getNextFeedback();
            StatusContainer::feedbackList.displayCurrent();
		}
		else if (option == 2)
		{
			//cout << "Move Backward" << endl;
            StatusContainer::feedbackList.getPrevFeedback();
            StatusContainer::feedbackList.displayCurrent();
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
            //StatusContainer::currentUser->removeFavourite(index);

            int userID = StatusContainer::currentUser->getUserID();
		    StatusContainer::userBTree.removeUserFavourite(userID, index);

			Message::success("Delete Successfully");
			Sleep(2000);
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

void go_to_user_search()
{
	UniversityList* list = StatusContainer::cacheUniList;
    
    int type = Menu::searchUniOption();
    int range = 0;
    string value = "";
    cout << endl;

    if (type == 5)
        go_to_user_menu();


    if (type == 1)
        value = searchUniByLocationCode();
    else
        range = Menu::selectScoreRange();

	system("cls");

    if (list == nullptr)
    {
		//cout << "nullptr" << endl;
        list = new UniversityList();
		StatusContainer::cacheUniList = list;
		//cout << StatusContainer::cacheUniList << endl;
        list = StatusContainer::universityBTree.filterUniversityByValue(&type, &range, &value);
		StatusContainer::cacheUniList = list;
		//cout << "Size: " << list->getSize() << endl;
    }
    else
    {
		list = StatusContainer::cacheUniList->filterUniversityByValue(&type, &range, &value);
    }

	if (list->getSize() == 0)
	{
		Message::warning("No search result found!");
		Sleep(1000);
		system("cls");
		list = nullptr;
        Menu::searchUniPage();
        go_to_user_search();
	}
	else
	{
		//cout << "Merge Sort" << endl;
        list->mergeSort(type);
		//cout << "Size: " << list->getSize() << endl;
        //StatusContainer::cacheUniList->displayUniversityList();
        //list->displayUniversityList();
        list->displayUniversityListDesc();
        StatusContainer::cacheUniList = list;
	}

    cout << endl;   
    bool next = proceedNext("Continue search university with these result");
    
    system("cls");
	if (next)
	{
		go_to_user_search();
	}
	else
	{
        while (true)
        {
            bool end = go_to_end_search();
			if (end)
			{
				break;
			}
        }
        system("cls");

        list->destroyList();  // destroy list
        list = nullptr;    // clear
		StatusContainer::cacheUniList = nullptr;
		Message::notice("Search university ended, back to previous menu!");
		Sleep(1000);

        Menu::searchUniPage();
        go_to_user_menu();  // back to menu or back to user_search
	}
}

bool go_to_end_search()
{
    if (StatusContainer::cacheUniList == nullptr)
    {
        //cout << "Error" << endl;
        return false;
    }

    StatusContainer::cacheUniList->displayUniversityList();

    int option = Menu::optionBeforeEndSearch();

    if (option == 1 || option == 2)
    {
        string num = validation("Enter university ranking: ", "From result above", NUM_REGEX);
        bool isExist = StatusContainer::cacheUniList->checkRankExist(stoi(num));
        string name = StatusContainer::universityBTree.getUniversityNameByRank(stoi(num));
        bool isFavourite = StatusContainer::currentUser->checkFavouriteExist(name);

        if (!isExist)
        {
            Message::error("Input's University ranking does not exist!");
            Sleep(1000);
        }
        else if (isFavourite && option == 1)
        {
            Message::notice("This university is already in your favourite list!");
            Sleep(1000);
        }
        else
        {
            if (option == 1)
            {
                StatusContainer::userBTree.addUserFavourite(StatusContainer::currentUser->getUserID(), name);

                Message::success("Add favourite successfully!");
                Sleep(1000);
            }
            else
            {
                string feedback = "";
                FeedbackNode* node = new FeedbackNode;
                cout << "Write Feedback: ";
                cin.ignore();
                getline(cin, feedback);
                time_t now = time(0);
                node->feedback.FeedbackID = now;
                node->feedback.UserName = StatusContainer::currentUser->getUsername();
                node->feedback.ReplyTo = -1;
                node->feedback.Content = feedback;
                node->feedback.Institution = name;
                StatusContainer::feedbackList.InsertToFrontOfList(node);

                Message::success("Write Feedback Successfully");
                Sleep(1000);
            }
			system("cls");
        }
        return false;
    }
    else if (option == 3)
    {
        return true;
    }
}

void go_to_generate_report()
{
    IsVector<std::string> fav = StatusContainer::userBTree.getUsersFavourites();
    int count = 0;

    for (int i = 0; i < fav.getSize(); i++)
    {
        for (int j = 0; j < fav.getSize(); j++)
        {
            if (fav.at(i) == fav.at(j))
                count++;
        }
        StatusContainer::universityList.updateFavourite(fav.at(i), count);
        //cout << fav.at(i) << " " << count << endl;
        count = 0;
    }

    cout << string(101, '*') << endl;
    cout << string(40, ' ') << "Top 10 University" << string(40, ' ') << endl;
    cout << string(101, '*') << endl;
    StatusContainer::universityList.displayTop10Uni();
    cout << endl;
    
    system("pause");
    system("cls");
    go_to_admin_menu();
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

