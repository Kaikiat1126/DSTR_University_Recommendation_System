#pragma once
#include <iostream>
#include <string>
#include <regex>
#include "Message.h"
#include "Menu.h"
#include "DateTime.h"
#include "StatusContainer.h"
#include "User.h"
#include "Visitor.h"

#define NAME_REGEX "^[a-zA-Z0-9]{4,}$"
#define EMAIL_REGEX "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$"
#define CONTACT_NUM_REGEX "^[0-9]{8}$"
#define PASSWORD_REGEX "^[a-zA-Z0-9]{6,}$"

std::string validInput(std::string, std::string, std::string);
bool registrationForm();
bool proceedNext(std::string);
std::string searchUniByName();

std::string validateInput(const std::string& prompt, const std::string& hint,const std::string& regexStr) {
    std::string input;
    std::regex regex(regexStr);

    while (true) {
        std::cout << prompt;
        if (!hint.empty()) 
            Message::notice(" (" + hint + ") ");
        if(prompt == "Email") std::cout << std::endl;
        std::cout << "> ";
        //std::cin >> input;
        std::cin.ignore();
		std::getline(std::cin, input);

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

	//institution, email, contact number, password
	std::string institution = validateInput("Username", "Don't include punctuations in your institution",NAME_REGEX);
    if (institution.empty()) {
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
	// std::cout << "Name: " << institution << std::endl;
	// std::cout << "Email: " << email << std::endl;
	// std::cout << "Contact Number: " << contactNum << std::endl;
	// std::cout << "Password: " << password << std::endl;

    // TODOs: store data
    if(proceedNext("Proceed to login")) {
        // TODOs: set data to StatusContainer
        StatusContainer::currentUser.setDetails(institution, email, contactNum, password);
        // TODOs: login
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
	std::string uniName;
    std::cout << "Please enter the university institution: " << std::endl;
    while (true)
    {
        std::cout << "> ";
		std::cin.ignore();
		std::getline(std::cin, uniName);
        if (uniName.empty()) {
            Message::warning("Don't leave empty input!");
        }
        else
        {
			break;
        }
    }
	std::cout << uniName << std::endl;
	std::cout << std::endl;
	return uniName;
}