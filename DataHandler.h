#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include "Structure.h"
#include "UserList.h"
#include "UniversityList.h"
#include "StatusContainer.h"
#include "IsVector.h"
#include "IsUnorderedMap.h"
#include "DateTime.h"

const std::string UNIVERSITYFILE = "University.csv";
const std::string USERFILE = "User.csv";
const std::string FEEDBACKFILE = "Feedback.csv";

const std::string accentLetters[] = { "é","è","É","ā","á","à","â","ä","ã","ó","ò","ö","ô","Ó","Ü","ü","ú","š","Š","ç","í","ý","ğ","ń","ñ","Ž","ø","ʻ"," " };
const std::string replaceLetters[] = { "e","e","E","a","a","a","a","a","a","o","o","o","o","O","U","u","u","s","S","c","i","y","g","n","n","Z","","\'"," " };

IsUnorderedMap<std::string, std::string, 29> map = StatusContainer::accentLettersMap;

void readFiletoStruture();
void initUserData();
void initUniversityData();
void initFeedbackData();
IsVector<std::string> splitComma(std::string rowStr);
void assignValue(double* score, int* rank, const std::string& value, const std::string& rankValue, int index);
std::string replaceAccentLetters(std::string rowStr);

void readFiletoStruture()
{
    initUserData();
    initUniversityData();
    initFeedbackData();
}

void initUserData()
{
	std::ifstream file(USERFILE);
    if(!file.is_open())
    {
        std::cout << "Unable to open file" << std::endl;
        return;
    }

	UserStruct user;
    std::string str, favourites;
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
        getline(iss, field, ',');
        user.lastModifyDate = DateTime::changeDateFormat(field);
        getline(iss, user.role, ',');
		getline(iss, favourites);
        
		favourites.erase(std::remove(favourites.begin(), favourites.end(), '\"'), favourites.end());
        
        IsVector<std::string> favs;
		std::istringstream iss2(favourites);
		std::string item;
		while (getline(iss2, item, ','))
		{
			favs.push_back(item);
		}

        if (favs.at(0) == "null") user.favourite = {};
		else user.favourite = favs;
        
        if(field != "")
        {
            //StatusContainer::userList.insertToEndOfList(user);
			StatusContainer::userBTree.insertValueInBTree(user);
	    }

        favs.clear();
    }
	file.close();
}

void initUniversityData()
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
		//std::cout << str << std::endl;
		IsVector<std::string> row = splitComma(str);
		university.rank = stoi(row.at(0));
		std::string temp = replaceAccentLetters(row.at(1));
		university.institution = temp;
		university.locationCode = row.at(2);
		university.location = row.at(3);

        double* scoreValues[] = { 
            &university.ArScore, &university.ErScore, &university.FsrScore, 
            &university.CpfScore, &university.IfrScore, &university.IsrScore, 
            &university.IrnScore, &university.GerScore 
        };

        int* rankValues[] = { 
            &university.ArRank, &university.ErRank, &university.FsrRank,
            &university.CpfRank, &university.IfrRank, &university.IsrRank,
            &university.IrnRank, &university.GerRank
        };


        for (int j = 0; j < 8; j++) {
            if (row.at(j*2 + 4) != "")
				*scoreValues[j] = stod(row.at(j*2 + 4));
            else
                *scoreValues[j] = NULL;
            
            if (row.at(j*2 + 5) != "")
                if(row.at(j*2 + 5).find("+") != std::string::npos)
                    *rankValues[j] = stoi(row.at(j*2 + 5).substr(0, row.at(j*2 + 5).length() - 1));
                else
                    *rankValues[j] = stoi(row.at(j*2 + 5));               
			else
				*rankValues[j] = NULL;
        }

		if (row.at(20) != "" && row.at(20) != "-")
			university.ScoreScaled = stod(row.at(20));
		else
			university.ScoreScaled = NULL;

        university.count = 0;
        //std::cout << university.rank << " " << university.ScoreScaled << std::endl;
		//std::cout << university.institution << " : " << university.ArScore << std::endl;
        StatusContainer::universityList.insertToEndOfList(university);
		StatusContainer::universityBTree.insertValueInBTree(university);

        UniversityStruct* universityPtr = new UniversityStruct(university);
        StatusContainer::universityRBTree.insert(universityPtr, "Institution");
	}
    file.close();
}

void initFeedbackData() {
    std::ifstream file(FEEDBACKFILE);
    if (!file.is_open())
    {
        std::cout << "Unable to open file" << std::endl;
        return;
    }

    Feedback element;
    std::string str;
    getline(file, str); //get the header line

    while (getline(file, str))
    {
        std::istringstream iss(str);
        std::string field;

        getline(iss, field, ',');
        element.FeedbackID = stol(field);
        getline(iss, element.UserName, ',');
        getline(iss, field, ',');
        element.ReplyTo = stol(field);
        getline(iss, element.Content, ',');
        getline(iss, element.Institution);

        StatusContainer::feedbackList.InsertToFrontOfList(new FeedbackNode(element));
    }
    file.close();
}

IsVector<std::string> splitComma(std::string rowStr)
{
    IsVector<std::string> row;
    std::string field = "";

	bool inQuotes = false;
	for (char& c : rowStr)
	{
		if (c == '\"')
			inQuotes = !inQuotes;
		else if (c == ',' && !inQuotes)
		{
			row.push_back(field);
			field = "";
		}
		else
			field += c;
	}
	row.push_back(field);
	return row;
}

void assignValue(double* score, int* rank, const std::string& value, const std::string& rankValue, int index)
{
    if (value != "")
        score[index] = stod(value);
    else
        score[index] = 0.0;

    if (rankValue != "") {
        if (rankValue.find("+") != std::string::npos)
            rank[index] = stoi(rankValue.substr(0, rankValue.length() - 1));
        else
            rank[index] = stoi(rankValue);
    }
    else
        rank[index] = 0;
}

std::string replaceAccentLetters(std::string institution)
{
    if (map.getSize() == 0)
    {
        for (int i = 0; i < 29; i++)
        {
            map.insert(accentLetters[i], replaceLetters[i]);
        }
    }

	if (institution.at(0) == ' ') institution.erase(0, 1);

	if (institution.at(institution.length() - 1) == ' ') institution.erase(institution.length() - 1, 1);
    
	for (int i = 0; i < map.getSize(); i++)
	{
		size_t pos = institution.find(map.getKey(i));
		while (pos != std::string::npos)
		{
			institution.replace(pos, map.getKey(i).length(), map.getValue(i));
			pos = institution.find(map.getKey(i), pos + 1);
		}
	}
    
	return institution;
}