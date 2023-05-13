#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


class DateTime {
public:
	static std::string getCurrentDateTime();
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

std::string DateTime::changeDateFormat(std::string date) {
	//turn string to time_t
	
	std::tm tm;
	std::istringstream ss(date);
	ss >> std::get_time(&tm, "%m/%d/%Y %H:%M");
	if (ss.fail()) {
		std::cout << "Error parsing time\n";
	}
	std::time_t time = mktime(&tm);
	
	//turn time_t to string
	std::stringstream newStr;
	newStr << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return newStr.str();
}