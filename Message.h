#pragma once
#include<iostream>
#include<windows.h>


class Message {
private:
	static void setColor(int fore, int back);
public:
	static void error(std::string message);
	static void success(std::string message);
	static void warning(std::string meesage);
	static void notice(std::string message);
};

void Message::setColor(int fore = 7, int back = 0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (back << 4) + fore);
}

void Message::error(std::string message) {
	setColor(4, 0);
	std::cout << message << std::endl;
	setColor();
}

void Message::success(std::string message) {
	setColor(2, 0);
	std::cout << message << std::endl;
	setColor();
}

void Message::warning(std::string message) {
	setColor(6, 0);
	std::cout << message << std::endl;
	setColor();
}

void Message::notice(std::string message) {
	setColor(3, 0);
	std::cout << message << std::endl;
	setColor();
}