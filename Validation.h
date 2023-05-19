#pragma once
#include <iostream>
#include <string>
#include <regex>
#include "Message.h"

#define NAME_REGEX "^[a-zA-Z0-9]{4,}$"
#define EMAIL_REGEX "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$"
#define CONTACT_NUM_REGEX "^[0-9]{8}$"
#define PASSWORD_REGEX "^[a-zA-Z0-9]{6,}$"
#define USER_ID_REGEX "^[0-9]+$"
#define NUM_REGEX "^[0-9]+$"

std::string validation(const std::string& prompt, const std::string& hint, const std::string& regexStr) {
    std::string input;
    std::regex regex(regexStr);

    while (true) {
        std::cout << prompt;
        if (!hint.empty())
            Message::notice(" (" + hint + ") ");
        else
            std::cout << std::endl;

        std::cout << "> ";
        std::cin.ignore();
        std::cin >> input;

        if (!std::regex_match(input, regex)) {
            Message::error("Invalid input. Please try again.");
        }
        else {
            return input;
        }
    }
}


std::string encrypPassword()
{
    std::string password;
    char c;
    while ((c = _getch()) != '\r') // Read characters until Enter (carriage return) is pressed
    {
        if (c == '\b') // Handle backspace
        {
            if (!password.empty())
            {
                std::cout << "\b \b"; // Move cursor back, overwrite the character with a space, move cursor back again
                password.pop_back(); // Remove the last character from the password string
            }
        }
        else
        {
            std::cout << '*'; // Display asterisks instead of the actual characters
            password += c; // Append the character to the password string
        }
    }
    std::cout << std::endl; // Move to the next line after the password input
    return password;
}
