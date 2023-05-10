#pragma once

#include <string>
#include <chrono>

class Timer
{
public:
	static auto getCurrentTime();
	static std::string getRunTime(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);
};

auto Timer::getCurrentTime()
{
	return std::chrono::high_resolution_clock::now();
}

std::string Timer::getRunTime(std::chrono::high_resolution_clock::time_point startTime,
	std::chrono::high_resolution_clock::time_point endTime)
{
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	return std::to_string(duration) + " ms";
}