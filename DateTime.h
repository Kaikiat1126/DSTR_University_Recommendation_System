#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


class DateTime {
private:
	static std::string getCurrentTime();
	static std::string getCurrentDate();
public:
	static std::string getCurrentDateTime();
};

std::string DateTime::getCurrentTime() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss;
	ss << std::put_time(localtime(&in_time_t), "%X");
	return ss.str();
}

std::string DateTime::getCurrentDate() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss;
	ss << std::put_time(localtime(&in_time_t), "%Y-%m-%d");
	return ss.str();
}

std::string DateTime::getCurrentDateTime() {
	return getCurrentDate() + " " + getCurrentTime();
}