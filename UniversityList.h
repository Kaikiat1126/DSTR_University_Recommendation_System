#pragma once
#include "Structure.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "Timer.h"
#include "Menu.h"
#include "Message.h"
#include <iostream>
#include <string>
#include <iomanip>

class UniversityList
{
private:
	UniversityNode* head = NULL;
	UniversityNode* tail = NULL;
	int size = 0;
	void filterUniversityWithLocation(UniversityNode* head, std::string& value);
	void filterUniversityByValue(UniversityNode* head, int* type, int* range);
	void deleteNode(UniversityNode* node);
	void displayHeader();
	
public:
	UniversityList();
	UniversityList(const UniversityList& copy);
	~UniversityList();
	UniversityNode* createNewNode(UniversityStruct university);
	void insertToEndOfList(UniversityStruct university);
	UniversityNode* searchByRank(int rank);
	UniversityNode* searchByInstitution(std::string institution);
	void displayCompleteUniversityList();
	void displayUniversityList();
	void displayUniversityListDesc();
	void displayTop10Uni();
	void quickSort();
	void mergeSort();
	void mergeSort(int);
	int getSize();
	void destroyList();
	bool checkRankExist(int rank);
	UniversityList* filterUniversityByValue(int* type, int* range, std::string* value);
	void updateFavourite(const std::string&, int);
	void displayInPagination();
};

UniversityList::UniversityList()
{
}

 //implementation of the copy constructor
UniversityList::UniversityList(const UniversityList& copy)
{

	// initialize the new list
	head = NULL;
	tail = NULL;
	size = 0;

	// iterate through the other list and copy each node
	UniversityNode* temp = copy.head;
	while (temp != NULL)
	{
		insertToEndOfList(temp->university);
		temp = temp->next;
	}
}

UniversityList::~UniversityList()
{
	//destroy
}

UniversityNode* UniversityList::createNewNode(UniversityStruct university)
{
	UniversityNode* newNode = new UniversityNode;
	newNode->university = university;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void UniversityList::insertToEndOfList(UniversityStruct university)
{
	UniversityNode* newNode = createNewNode(university);
	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		UniversityNode* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->prev = temp;
		tail = newNode;
	}
	size++;
}

UniversityNode* UniversityList::searchByRank(int rank)
{
	//TODOs: enhance with BinarySearch
	if (rank > size / 2)
	{
		UniversityNode* temp = tail;
		while (temp != NULL)
		{
			if (temp->university.rank == rank)
			{
				return temp;
			}
			temp = temp->prev;
		}
	}
	else
	{
		UniversityNode* temp = head;
		while (temp != NULL)
		{
			if (temp->university.rank == rank)
			{
				return temp;
			}
			temp = temp->next;
		}
	}
	return NULL;
}

UniversityNode* UniversityList::searchByInstitution(std::string institution)
{
	UniversityNode* temp = head;
	while (temp != NULL)
	{
		if (temp->university.institution == institution)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void UniversityList::displayCompleteUniversityList()
{
	UniversityNode* temp = head;
	
	while (temp != NULL)
	{
		std::cout << "Rank           :" << temp->university.rank << '\t';
		std::cout << "Institution    :" << temp->university.institution << '\n';
		std::cout << "Location code  :" << temp->university.locationCode << '\t';
		std::cout << "Location       :" << temp->university.location << '\n';
		std::cout << "ArScore        :" << temp->university.ArScore << '\t';
		std::cout << "ArRank         :" << temp->university.ArRank << '\t';
		std::cout << "ErScore        :" << temp->university.ErScore << '\t';
		std::cout << "ErRank         :" << temp->university.ErRank << '\t';
		std::cout << "FsrScore       :" << temp->university.FsrScore << '\t';
		std::cout << "FsrRank        :" << temp->university.FsrRank << '\n';
		std::cout << "CpfScore       :" << temp->university.CpfScore << '\t';
		std::cout << "CpfRank        :" << temp->university.CpfRank << '\t';
		std::cout << "IfrScore       :" << temp->university.IfrScore << '\t';
		std::cout << "IfrRank        :" << temp->university.IfrRank << '\t';
		std::cout << "IsrScore       :" << temp->university.IsrScore << '\t';
		std::cout << "IsrRank        :" << temp->university.IsrRank << '\n';
		std::cout << "IrnScore       :" << temp->university.IrnScore << '\t';
		std::cout << "IrnRank        :" << temp->university.IrnRank << '\t';
		std::cout << "GerScore       :" << temp->university.GerScore << '\t';
		std::cout << "GerRank        :" << temp->university.GerRank << '\t';
		std::cout << "ScoreScaled    :" << temp->university.ScoreScaled << std::endl;
		std::cout<<std::endl;
		
		temp = temp->next;
	}
}

void UniversityList::displayHeader()
{
	// Print header
	std::cout << std::setw(4) << "Rank" << "\t"
		<< std::left << std::setw(90) << "Institution" << "\t"
		<< std::right << std::setw(2) << "Loc" << "\t"
		<< std::setw(4) << "AR" << "\t"
		<< std::setw(4) << "FSR" << "\t"
		<< std::setw(4) << "ER" << std::endl;
}

void UniversityList::displayUniversityList()
{
	UniversityNode* temp = head;

	displayHeader();

	while (temp != NULL)
	{
		//std::cout << temp->university.rank << "\t" << temp->university.institution << "\t" << temp->university.locationCode << "\t" << temp->university.ArScore<< "\t" << temp->university.FsrScore<< "\t" << temp->university.ErScore << std::endl;
		std::cout << std::setw(4) << temp->university.rank << "\t"
			<< std::left << std::setw(90) << temp->university.institution << "\t"
			<< std::right << std::setw(2) << temp->university.locationCode << "\t"
			<< std::setw(4) << temp->university.ArScore << "\t"
			<< std::setw(4) << temp->university.FsrScore << "\t"
			<< std::setw(4) << temp->university.ErScore << std::endl;
		temp = temp->next;
	}
}

void UniversityList::displayUniversityListDesc()
{
	UniversityNode* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	displayHeader();

	while (temp != NULL)
	{
		std::cout << std::setw(4) << temp->university.rank << "\t"
			<< std::left << std::setw(90) << temp->university.institution << "\t"
			<< std::right << std::setw(2) << temp->university.locationCode << "\t"
			<< std::setw(4) << temp->university.ArScore << "\t" 
			<< std::setw(4) << temp->university.FsrScore << "\t"
			<< std::setw(4) << temp->university.ErScore << std::endl;
		temp = temp->prev;
	}
}

void UniversityList::displayTop10Uni()
{
	UniversityList* copyList = new UniversityList(*this);
	copyList->mergeSort(5);

	UniversityNode* temp = copyList->head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	int count = 0;

	std::cout << std::setw(4) << "Rank" << "\t"
		<< std::left << std::setw(50) << "Institution" << "\t"
		<< std::right << std::setw(2) << "Loc" << "\t"
		<< std::setw(4) << "AR" << "\t"
		<< std::setw(4) << "FSR" << "\t"
		<< std::setw(4) << "ER" << "\t"
		<< std::setw(5) << "Count" << std::endl;

	while (temp != NULL && count <10)
	{
		std::cout << std::setw(4) << temp->university.rank << "\t"
			<< std::left << std::setw(50) << temp->university.institution << "\t"
			<< std::right << std::setw(2) << temp->university.locationCode << "\t"
			<< std::setw(4) << temp->university.ArScore << "\t"
			<< std::setw(4) << temp->university.FsrScore << "\t"
			<< std::setw(4) << temp->university.ErScore << "\t"
			<< std::setw(5) << temp->university.count << std::endl;
		temp = temp->prev;
		count++;
	}

	copyList->destroyList();
}

void UniversityList::quickSort()
{
	UniversityList* copyList = new UniversityList(*this);

	auto start = Timer::getCurrentTime();
	QuickSort::quickSort(copyList->head, copyList->tail, 0);
	auto end = Timer::getCurrentTime();

	system("cls");
	copyList->displayUniversityList();

	std::string runTime = Timer::getRunTime(start, end);
	std::cout << "Time taken by quick sort algorithm: ";
	std::cout << runTime << std::endl;

	copyList->destroyList();
}

void UniversityList::mergeSort()
{
	UniversityList* copyList = new UniversityList(*this);

	auto start = Timer::getCurrentTime();
	UniversityNode* sortedMerge = MergeSort::mergeSort(copyList->head, 0);
	auto end = Timer::getCurrentTime();
	
	copyList->head = sortedMerge;

	system("cls");
	copyList->displayUniversityList();

	std::string runTime = Timer::getRunTime(start, end);
	std::cout << "Time taken by merge sort algorithm: ";
	std::cout << runTime << std::endl;

	copyList->destroyList();
}

// type: "0:institution", "1:rank", "2:ar_score", "3:fsr_score", "4:er_score", "5:count
void UniversityList::mergeSort(int type)
{
	if (head != NULL)
	{
		UniversityNode* sortedMerge = MergeSort::mergeSort(head, type);
		head = sortedMerge;
	}
}

int UniversityList::getSize()
{
	return size;
}

void UniversityList::destroyList()
{
	UniversityNode* temp = head;
	while (temp != NULL)
	{
		UniversityNode* next = temp->next;
		delete temp;
		temp = next;
	}
	head = NULL;
	tail = NULL;
	size = 0;
}

bool UniversityList::checkRankExist(int rank)
{
	UniversityNode* temp = head;
	while (temp != NULL)
	{
		if (temp->university.rank == rank)
		{
			return true;
		}
		temp = temp->next;
	}
	return false;
}

// type: "0 = rank", "1 = name", "2 = locationCode", "3 = ar score", "4 = fsr score", "5 = er score"
// name need to been remove spaces
// range: "1 = 0-20" , "2 = 21-40", "3 = 41-60", "4 = 61-80", "5 = 81-100"
UniversityList* UniversityList::filterUniversityByValue(int* type, int* range, std::string* value)
{
	UniversityList* copyList = new UniversityList(*this);
	//std::cout << copyList << ":" << copyList->getSize() << std::endl;
	if (*type == 1)
		copyList->filterUniversityWithLocation(copyList->head, *value);
	else
		copyList->filterUniversityByValue(copyList->head, type, range);
	
	//std::cout << copyList << " " << copyList->getSize() << std::endl;
	this->destroyList();
	return copyList;
}

void UniversityList::filterUniversityWithLocation(UniversityNode* head, std::string& value)
{
	UniversityNode* temp = head;
	while (temp != NULL)
	{
		if (temp->university.locationCode != value)
		{
			UniversityNode* next = temp->next;
			deleteNode(temp);
			temp = next;
		}
		else
		{
			temp = temp->next;
		}
	}
}

// range: "1 = 0-20" , "2 = 21-40", "3 = 41-60", "4 = 61-80", "5 = 81-100"
void UniversityList::filterUniversityByValue(UniversityNode* head, int* type, int* range)
{
	// remove the node that not in the range
	UniversityNode* temp = head;
	int minScore = (*range - 1) * 20;
	int maxScore = *range * 20;
	
	while (temp != NULL)
	{
		bool match = false;
		if (*type == 2)
		{
			match = temp->university.ArScore >= minScore && temp->university.ArScore <= maxScore;
		}
		else if (*type == 3)
		{
			match = temp->university.FsrScore >= minScore && temp->university.FsrScore <= maxScore;
		}
		else if (*type == 4)
		{
			match = temp->university.ErScore >= minScore && temp->university.ErScore <= maxScore;
		}

		if (!match)
		{
			UniversityNode* next = temp->next;
			deleteNode(temp);
			temp = next;
		}
		else
		{
			temp = temp->next;
		}
	}
}

void UniversityList::deleteNode(UniversityNode* node)
{
	if (node == nullptr)
		return; // Handle the case when the node is null

	if (node == head)
	{
		head = head->next;
		head->prev = nullptr;
	}
	else if (node == tail)
	{
		tail = tail->prev;
		tail->next = nullptr;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	delete node;
	size--;
}

void UniversityList::updateFavourite(const std::string& institution, int count)
{
	UniversityNode* current = head;
	while (current != nullptr)
	{
		if (current->university.institution == institution)
		{
			current->university.count = count;
			break;
		}
		current = current->next;
	}
}

void UniversityList::displayInPagination() 
{
	
	UniversityNode* temp = head;

	int count = 1;
	
	//int page = Menu::choosePage(getSize()); //Problem ::'Menu' is not a class or namespace name and 'choosePage' identifier not found
	int page = 28;

	if (!page)
		return;

	while (count++ != page * 50 + 1) {
		temp = temp->next;
	}
	count = 0;

	while (temp != NULL)
	{
		std::cout << "Rank           :" << temp->university.rank << '\t';
		std::cout << "Institution    :" << temp->university.institution << '\n';
		std::cout << "Location code  :" << temp->university.locationCode << '\t';
		std::cout << "Location       :" << temp->university.location << '\n';
		std::cout << "ArScore        :" << temp->university.ArScore << '\t';
		std::cout << "ArRank         :" << temp->university.ArRank << '\t';
		std::cout << "ErScore        :" << temp->university.ErScore << '\t';
		std::cout << "ErRank         :" << temp->university.ErRank << '\t';
		std::cout << "FsrScore       :" << temp->university.FsrScore << '\t';
		std::cout << "FsrRank        :" << temp->university.FsrRank << '\n';
		std::cout << "CpfScore       :" << temp->university.CpfScore << '\t';
		std::cout << "CpfRank        :" << temp->university.CpfRank << '\t';
		std::cout << "IfrScore       :" << temp->university.IfrScore << '\t';
		std::cout << "IfrRank        :" << temp->university.IfrRank << '\t';
		std::cout << "IsrScore       :" << temp->university.IsrScore << '\t';
		std::cout << "IsrRank        :" << temp->university.IsrRank << '\n';
		std::cout << "IrnScore       :" << temp->university.IrnScore << '\t';
		std::cout << "IrnRank        :" << temp->university.IrnRank << '\t';
		std::cout << "GerScore       :" << temp->university.GerScore << '\t';
		std::cout << "GerRank        :" << temp->university.GerRank << '\t';
		std::cout << "ScoreScaled    :" << temp->university.ScoreScaled << std::endl;
		std::cout << std::endl;

		++count;

		temp = temp->next;
		if (!temp)
			Message::warning("You reach the bottom");
		if (count == 50) {
			break;
		}
	}
	
}