#pragma once
#include <string>

struct UniversityStruct
{
	int rank;
	std::string institution;
	std::string locationCode;
	std::string location;
	double ArScore, ErScore, FsrScore, CpfScore,
		IfrScore, IsrScore, IrnScore, GerScore, ScoreScaled;
	int ArRank, ErRank, FsrRank, CpfRank, IfrRank,
		IsrRank, IrnRank, GerRank;
};

struct UniversityNode
{
	UniversityNode* prev;
	UniversityStruct university;
	UniversityNode* next;
} *uniHead, *tail;