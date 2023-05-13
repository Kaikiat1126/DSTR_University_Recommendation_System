#pragma once
#include <string>
#include "IsVector.h"

#define MAX 4
#define MIN 2

struct DataStruct
{
	
};

struct UserStruct
{
	int userID;
	std::string username;
	std::string email;
	std::string contactNum;
	std::string password;
	std::string lastModifyDate;
	std::string role;
	IsVector<std::string> favourite;
};

struct UserNode
{
	UserStruct user;
	UserNode* next;
} *head;

struct UniversityStruct : public DataStruct
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
} *uniHead, * tail;

struct BTreeNode
{
	int count;
};

struct UniversityBTreeNode : public BTreeNode
{
	//int count; 
	UniversityStruct university[MAX + 1];
	UniversityBTreeNode* child[MAX + 1];
};

struct UserBTreeNode : public BTreeNode
{
	//int count;
	UserStruct user[MAX + 1];
	UserBTreeNode* child[MAX + 1];
};