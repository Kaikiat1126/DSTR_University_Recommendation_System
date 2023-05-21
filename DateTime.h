#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


class DateTime {
public:
	static std::string getCurrentDateTime();
	static std::string getCurrentMinusMonths(int months);
	static std::string changeDateFormat(std::string date);
};

std::string DateTime::getCurrentDateTime() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::tm tm;
	localtime_s(&tm, &in_time_t);
	
	std::stringstream ss;
	ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	//ss << std::put_time(&tm, "%d/%d/%Y %H:%M");
	return ss.str();
}

std::string DateTime::getCurrentMinusMonths(int months) {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24 * 30 * months)); // subtract months from current time

	std::tm tm;
	localtime_s(&tm, &in_time_t);

	std::stringstream ss;
	ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return ss.str();
}

std::string DateTime::changeDateFormat(std::string date) {

	// create stringstream object and read input string
	std::stringstream ss(date);
	std::tm datetime = {};

	// parse the input string to a tm struct
	ss >> std::get_time(&datetime, "%m/%d/%Y %H:%M");

	// check if parsing was successful
	if (ss.fail()) {
		std::cout << "Error parsing time\n" << std::endl;
	}

	// format the tm struct as a string in the desired format
	std::ostringstream newStr;
	newStr << std::put_time(&datetime, "%Y-%m-%d %H:%M:%S");
	return newStr.str();
}