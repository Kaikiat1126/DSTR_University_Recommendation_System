#pragma once
#include <iostream>
#include <string>
#include <regex>
#include "Message.h"
#include "DateTime.h"

#define NAME_REGEX "^[a-zA-Z ]+$"
#define EMAIL_REGEX "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$"
#define CONTACT_NUM_REGEX "^[0-9]{8}$"
#define PASSWORD_REGEX "^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*])(?=.{8,})"

std::string validateInput(const std::string& prompt, const std::string& regexStr) {
    std::string input;
    std::regex regex(regexStr);

    while (true) {
        std::cout << prompt << ": ";
        std::cin >> input;
		// std::getline(std::cin, input);

        if (input == "Q" || input == "quit" || input == "q" || input == "Quit" || input == "QUIT") {
            Message::notice("You have quit the registration process");
            return "";
        }

        if (!std::regex_match(input, regex)) {
            Message::error("Invalid input. Please try again.");
        } else {
            return input;
        }
    }
}

void registrationForm()
{
	std::cout << "Please fill up the form below and ";
	Message::warning("you may quit at any time by entering 'Q/quit'");
    std::cout << std::endl;

	//name, email, contact number, password
	std::string name = validateInput("Name", NAME_REGEX);
    if (name.empty()) {
        return;
    }

    std::string email = validateInput("Email", EMAIL_REGEX);
    if (email.empty()) {
        return;
    }

    std::string contactNum = validateInput("Contact Number", CONTACT_NUM_REGEX);
    if (contactNum.empty()) {
        return;
    }

	std::string password = validateInput("Password", PASSWORD_REGEX);
	if (password.empty()) {
		return;
	}

	Message::success("Registration successful!");
	std::cout << "Name: " << name << std::endl;
	std::cout << "Email: " << email << std::endl;
	std::cout << "Contact Number: " << contactNum << std::endl;
	std::cout << "Password: " << password << std::endl;

}