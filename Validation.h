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