#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Structure.h"
#include "UserList.h"
#include "UniversityList.h"
#include "StatusContainer.h"

const std::string UNIVERSITYFILE = "University.csv";
const std::string USERFILE = "User.csv";

void readFiletoStruture();
void initUserList();

void readFiletoStruture()
{
    //TODOs
}

void initUserList()
{
	std::ifstream file(USERFILE);
    if(!file.is_open())
    {
        std::cout << "Unable to open file" << std::endl;
        return;
    }

	UserStruct user;
    std::string str;
    getline(file, str); //get the header line
    
    while (getline(file, str))
    {
        std::istringstream iss(str);
        std::string field;

        getline(iss, field, ',');
        user.userID = stoi(field);
        getline(iss, user.username, ',');
        getline(iss, user.email, ',');
        getline(iss, user.contactNum, ',');
        getline(iss, user.password, ',');
        getline(iss, user.lastModifyDate, ',');
        getline(iss, user.role, ',');
        getline(iss, user.favourite);
        if(field != "")
            StatusContainer::userList.insertToEndOfList(user);
    }
	file.close();
}

void initUniversityList()
{
    std::ifstream file(UNIVERSITYFILE);
    if (!file.is_open())
    {
        std::cout << "Unable to open file" << std::endl;
        return;
    }

	UniversityStruct university;
    std::string str;
    getline(file, str); //get the header line
    
	while (getline(file, str))
	{
		std::istringstream iss(str);
		std::string field;

		getline(iss, field, ',');
		university.rank = stoi(field);
		getline(iss, university.institution, ',');
		getline(iss, university.locationCode, ',');
		getline(iss, university.location, ',');
		
		/*getline(iss, field, ',');
		university.ArScore = stod(field);
		getline(iss, field, ',');
		university.ArRank = stoi(field);
		getline(iss, field, ',');
		university.ErScore = stod(field);
		getline(iss, field, ',');
		university.ErRank = stoi(field);
		getline(iss, field, ',');
		university.FsrScore = stod(field);
		getline(iss, field, ',');
		university.FsrRank = stoi(field);
		getline(iss, field, ',');
		university.CpfScore = stod(field);
		getline(iss, field, ',');
		university.CpfRank = stoi(field);
		getline(iss, field, ',');
		university.IfrScore = stod(field);
		getline(iss, field, ',');
		university.IfrRank = stoi(field);
		getline(iss, field, ',');
		university.IsrScore = stod(field);
		getline(iss, field, ',');
		university.IsrRank = stoi(field);
		getline(iss, field, ',');
		university.IrnScore = stod(field);
		getline(iss, field, ',');
		university.IrnRank = stoi(field);
		getline(iss, field, ',');
		university.GerScore = stod(field);
		getline(iss, field, ',');
		university.GerRank = stoi(field);*/

        double scoreValues[] = { 
            university.ArScore, university.ErScore, university.FsrScore, 
            university.CpfScore, university.IfrScore, university.IsrScore, 
            university.IrnScore, university.GerScore 
        };
        
        int rankValues[] = { university.ArRank, university.ErRank,
            university.FsrRank, university.CpfRank, university.IfrRank,
            university.IsrRank, university.IrnRank, university.GerRank
        };

        for (int j = 0; j < 8; j++) {
            getline(iss, field, ',');
			if (field != "")
				scoreValues[j] = stod(field);
            else
				scoreValues[j] = NULL;
            
            getline(iss, field, ',');
			if (field != "" && field != "-")
				rankValues[j] = stoi(field);
			else
				rankValues[j] = NULL;
        }

        university.ArScore = scoreValues[0];
        university.ErScore = scoreValues[1];
        university.FsrScore = scoreValues[2];
        university.CpfScore = scoreValues[3];
        university.IfrScore = scoreValues[4];
        university.IsrScore = scoreValues[5];
        university.IrnScore = scoreValues[6];
        university.GerScore = scoreValues[7];

        university.ArRank = rankValues[0];
        university.ErRank = rankValues[1];
        university.FsrRank = rankValues[2];
        university.CpfRank = rankValues[3];
        university.IfrRank = rankValues[4];
        university.IsrRank = rankValues[5];
        university.IrnRank = rankValues[6];
        university.GerRank = rankValues[7];
		
		getline(iss, field);
		if (field != "" && field != "-")
		    university.ScoreScaled = stod(field);
        else {
			university.ScoreScaled = NULL;
        }
        
		if (field != "")
			StatusContainer::universityList.insertToEndOfList(university);
	}
}