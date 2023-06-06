#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include "Message.h"
#include "Menu.h"
#include "DateTime.h"
#include "StatusContainer.h"
#include "Structure.h"
#include "IsVector.h"

#define NAME_REGEX "^[a-zA-Z0-9]{4,}$"
#define EMAIL_REGEX "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$"
#define CONTACT_NUM_REGEX "^[0-9]{8}$"
#define PASSWORD_REGEX "^[a-zA-Z0-9]{6,}$"

std::string validInput(std::string, std::string, std::string);
bool registrationForm();
bool proceedNext(std::string);
std::string searchUniByName();
std::string searchUniByLocationCode();

std::string validateInput(const std::string& prompt, const std::string& hint,const std::string& regexStr) {
    std::string input;
    std::regex regex(regexStr);

    while (true) {
        std::cout << prompt;
        if (!hint.empty()) 
            Message::notice(" (" + hint + ") ");
        if(prompt == "Email") std::cout << std::endl;
        std::cout << "> ";
        std::cin.ignore();
        std::cin >> input;

        if (input == "Q" || input == "quit" || input == "q" || input == "Quit" || input == "QUIT") {
            Message::notice("You have quit the registration process...");
            Sleep(1000);
            system("cls");
            Menu::registerPage();
            return "";
        }

        if (!std::regex_match(input, regex)) {
            Message::error("Invalid input. Please try again.");
        } else {
            return input;
        }
    }
}

bool registrationForm()
{      
	std::cout << "Please fill up the form below and ";
	Message::warning("you may quit at any time by entering 'Q/quit'");
    std::cout << std::endl;

	//username, email, contact number, password
	std::string username = validateInput("Username", "Don't include punctuations in your username",NAME_REGEX);
    if (username.empty()) {
        return false;
    }

    std::string email = validateInput("Email", "",EMAIL_REGEX);
    if (email.empty()) {
        return false;
    }

    std::string contactNum = validateInput("Contact Number", "only 8 digits allowed",CONTACT_NUM_REGEX);
    if (contactNum.empty()) {
        return false;
    }

	std::string password = validateInput("Password", "at least 6 characters",PASSWORD_REGEX);
	if (password.empty()) {
		return false;
	}

	Message::success("Registration successful!");
    std::cout << std::endl;
    
	/*std::cout << "************************************" << std::endl;
	std::cout << "Name            : " << username << std::endl;
	std::cout << "Email           : " << email << std::endl;
	std::cout << "Contact Number  : " << contactNum << std::endl;
	std::cout << "Password        : " << password << std::endl;
    std::cout << "************************************" << std::endl;
    std::cout << std::endl;*/

    UserStruct newUser;
    newUser.userID = (StatusContainer::userBTree.getTreeNodeCount() + 1);
	newUser.username = username;
	newUser.email = email;
	newUser.contactNum = contactNum;
	newUser.password = password;
	newUser.role = "user";
	newUser.lastModifyDate = DateTime::getCurrentDateTime();
    IsVector<std::string>* vector = new IsVector<std::string>;
    newUser.favourite = *vector;
    
    //store data
	StatusContainer::userBTree.insertValueInBTree(newUser);

    if(proceedNext("Proceed to login")) {      
        StatusContainer::currentUser = new Customer(newUser.userID, newUser.username, newUser.password, newUser.email, newUser.contactNum, newUser.role, newUser.favourite);       
        return true;
    } 
    else 
        return false;
}

bool proceedNext(std::string message) {
    std::string input;
    while (true) {
        Message::notice(message + "? (Y/N)");
        std::cout << "> ";
        std::cin >> input;
        if (input == "Y" || input == "y" || input == "Yes" || input == "yes" || input == "YES") {
            return true;
        } else if (input == "N" || input == "n" || input == "No" || input == "no" || input == "NO") {
            return false;
        } else {
            Message::error("Invalid input. Please try again.");
        }
    }
}

std::string searchUniByName()
{
	std::string institution;
    std::cout << "Please enter the university institution: " << std::endl;
    while (true)
    {
        std::cout << "> ";
		std::cin.ignore();
		std::getline(std::cin, institution);
        if (institution.empty()) {
            Message::warning("Don't leave empty input!");
        }
        else
        {
			break;
        }
    }
	//std::cout << institution << std::endl;
	std::cout << std::endl;
	return institution;
}

void printTable(IsVector<std::string> data, int columns, int rows) {
    int dataSize = data.getSize();
    int tableSize = columns * rows;

    // Adjust the table size if it exceeds the available data
    if (tableSize > dataSize) {
        tableSize = dataSize;
    }

    int columnWidth = 4; // Assuming a maximum of 4-character location codes

    // Print top border
    std::cout << std::string((columnWidth + 1) * columns + 1, '-') << std::endl;

    // Print table rows
    for (int i = 0; i < tableSize; i++) {
        if (i % columns == 0 && i != 0) {
            std::cout << '|' << std::endl;
        }
        std::cout << '|' << std::left << std::setw(columnWidth) << data.at(i);
    }
    std::cout << '|' << std::endl;

    // Print bottom border
    std::cout << std::string((columnWidth + 1) * columns + 1, '-') << std::endl;
}

std::string searchUniByLocationCode()
{
	std::string locationCode;

    //print location code table
    IsVector<std::string> location = StatusContainer::universityBTree.getUniversityLocationCode();
    printTable(location, 10, 10);

	std::cout << "Please enter the university location code ";
    Message::notice("(Location code display on table)");

	while (true)
	{
        std::cout << "> ";
        std::cin.ignore();
        std::cin >> locationCode;
		if (locationCode.empty()) {
			Message::warning("Don't leave empty input!");
		}
		if (locationCode.length() != 2) {
			Message::warning("Location code must be 2 characters!");
		}
        
		if (location.contains(locationCode)) {
			break;
		}
		else
		{
			Message::error("Location code not found! Please try again.");
		}
	}
	std::cout << std::endl;
	std::transform(locationCode.begin(), locationCode.end(), locationCode.begin(), ::toupper);
	locationCode.erase(std::remove(locationCode.begin(), locationCode.end(), ' '), locationCode.end());
	return locationCode;
}