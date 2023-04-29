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

const std::string UNIVERSITYFILE = "University.csv";
const std::string USERFILE = "User.csv";

void readFiletoStruture();
void initUserList();
void initUniversityList();
IsVector<std::string> splitComma(std::string rowStr);
std::string replaceAccentLetters(std::string rowStr);

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
		IsVector<std::string> row = splitComma(str);
		university.rank = stoi(row.at(0));
		university.institution = row.at(1);
		university.locationCode = row.at(2);
		university.location = row.at(3);

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
            if (row.at(j + 4) != "")
                scoreValues[j] = stod(row.at(j + 4));
            else
                scoreValues[j] = NULL;
            
            if (row.at(j + 5) != "")
                if(row.at(j + 5).find("+") != std::string::npos)
                    rankValues[j] = stoi(row.at(j + 5).substr(0, row.at(j + 5).length() - 1));
                else
                    rankValues[j] = stoi(row.at(j + 5));
			else
				rankValues[j] = NULL;
        }

		if (row.at(20) != "" && row.at(20) != "-")
			university.ScoreScaled = stod(row.at(20));
		else
			university.ScoreScaled = NULL;
            
        StatusContainer::universityList.insertToEndOfList(university);
	}
}

IsVector<std::string> splitComma(std::string rowStr)
{
    std::string cleanStr = replaceAccentLetters(rowStr);
    IsVector<std::string> row;
    std::string field = "";

	bool inQuotes = false;
	for (char& c : cleanStr)
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

std::string replaceAccentLetters(std::string rowStr)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(rowStr);
    std::wstring result = L"";
    for (wchar_t c : wstr)
    {
        if (c == L'á' || c == L'ã' || c == L'à' || c == L'ä' || c == L'â' || c == L'ä' || c == L'ã')
            result += L"a";
        else if (c == L'ç')
            result += L"c";
        else if (c == L'é' || c == L'è')
            result += L"e";
        else if (c == L'ó')
            result += L"o";
        else if (c == L'ü')
            result += L"u";
        else if (c == L'š')
            result += L"s";
        else if (c == L'É')
            result += L"E";
        else if (c == L'Ž')
            result += L"Z";
        else if (c == L'Ü')
            result += L"U";
        else
            result += c;
    }
    return converter.to_bytes(result);
}