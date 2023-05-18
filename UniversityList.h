#pragma once
#include "Structure.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std::chrono;

class UniversityList
{
private:
	UniversityNode* head = NULL;
	UniversityNode* tail = NULL;
	int size = 0;
	void filterUniversiyWithRank(UniversityNode* head, int* rank);
	void filterUniversityWithLocation(UniversityNode* head, std::string& value);
	void filterUniversityByValue(UniversityNode* head, int* type, int* range);
	void deleteNode(UniversityNode* node);
	
public:
	UniversityList();
	UniversityList(const UniversityList& copy);
	~UniversityList();
	UniversityNode* createNewNode(UniversityStruct university);
	void insertToEndOfList(UniversityStruct university);
	UniversityNode* searchByRank(int rank);
	UniversityNode* searchByInstitution(std::string institution);
	void displayUniversityList();
	void displayUniversityListDesc();
	void quicksortAll();
	void mergesortAll();
	void mergeSort(int, bool);
	int getSize();
	void destroyList();
	bool checkRankExist(int rank);
	//void filterUniversityByValue(int* type, int* range, std::string* value);
	UniversityList* filterUniversityByValue(int* type, int* range, std::string* value);
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

void UniversityList::displayUniversityList()
{
	UniversityNode* temp = head;

	// Print header
	std::cout << std::setw(4) << "Rank" << "\t"
		<< std::left << std::setw(83) << "Institution" << "\t"
		<< std::right << std::setw(2) << "Loc" << "\t"
		<< std::setw(4) << "AR" << "\t"
		<< std::setw(4) << "FSR" << "\t"
		<< std::setw(4) << "ER" << std::endl;

	while (temp != NULL)
	{
		//std::cout << temp->university.rank << "\t" << temp->university.institution << "\t" << temp->university.locationCode << "\t" << temp->university.ArScore<< "\t" << temp->university.FsrScore<< "\t" << temp->university.ErScore << std::endl;
		std::cout << std::setw(4) << temp->university.rank << "\t"
			<< std::left << std::setw(85) << temp->university.institution << "\t"
			<< std::right << std::setw(2) << temp->university.locationCode << "\t"
			<< std::setw(4) << temp->university.ArScore << "\t"
			<< std::setw(4) << temp->university.FsrScore << "\t"
			<< std::setw(4) << temp->university.ErScore << std::endl;
		temp = temp->next;
	}
}

void UniversityList::displayUniversityListDesc()
{
	UniversityNode* temp = tail;

	while (temp != NULL)
	{
		std::cout << std::setw(4) << temp->university.rank << "\t"
			<< std::left << std::setw(85) << temp->university.institution << "\t"
			<< std::right << std::setw(2) << temp->university.locationCode << "\t"
			<< std::setw(4) << temp->university.ArScore << "\t"
			<< std::setw(4) << temp->university.FsrScore << "\t"
			<< std::setw(4) << temp->university.ErScore << std::endl;
		temp = temp->prev;
	}
}

void UniversityList::quicksortAll()
{
	UniversityList* copyList = new UniversityList(*this);

	auto start = high_resolution_clock::now();
	QuickSort::quickSort(copyList->head, copyList->tail, 0);
	auto stop = high_resolution_clock::now();

	system("cls");
	copyList->displayUniversityList();

	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Time taken by quick sort algorithm: ";
	std::cout << duration.count() << " microseconds. " << std::endl;

	delete copyList;
}

// type: "institution", "ar_score", "fsr_score", "er_score"
void UniversityList::mergesortAll()
{
	UniversityList* copyList = new UniversityList(*this);

	auto start = high_resolution_clock::now();
	UniversityNode* sortedMerge = MergeSort::mergeSort(copyList->head, 0);
	auto stop = high_resolution_clock::now();
	
	copyList->head = sortedMerge;

	system("cls");
	copyList->displayUniversityList();

	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Time taken by merge sort algorithm: ";
	std::cout << duration.count() << " microseconds. " << std::endl;

	delete copyList;
}

void UniversityList::mergeSort(int type, bool isAsc)
{
	UniversityNode* sortedMerge = MergeSort::mergeSort(head, type);
	head = sortedMerge;

	system("cls");

	if(isAsc)
		displayUniversityList();
	else
	{
		displayUniversityListDesc();
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
//void UniversityList::filterUniversityByValue(int* type, int* range, std::string* value)
//{
//	std::cout << "Filtering..." << std::endl;
//	if (*type == 1)
//	{
//		int rank = std::stoi(*value);
//		filterUniversiyWithRank(head, &rank);
//	}
//	else if (*type == 2)
//		filterUniversityWithLocation(head, *value);
//	else
//		filterUniversityByValue(head, type, range);
//}

UniversityList* UniversityList::filterUniversityByValue(int* type, int* range, std::string* value)
{
	UniversityList* copyList = new UniversityList(*this);
	//std::cout << copyList << ":" << copyList->getSize() << std::endl;
	if (*type == 1)
	{
		int rank = std::stoi(*value);
		copyList->filterUniversiyWithRank(copyList->head, &rank);
	}
	else if (*type == 2)
		copyList->filterUniversityWithLocation(copyList->head, *value);
	else
		copyList->filterUniversityByValue(copyList->head, type, range);
	
	//std::cout << copyList << " " << copyList->getSize() << std::endl;
	return copyList;
}

void UniversityList::filterUniversiyWithRank(UniversityNode* head, int* rank)
{
	// search with linear search, when found the rank then record the address,
	// destroy the list and create new list with the address
	bool found = false;
	UniversityNode* temp = head;
	UniversityNode* target = NULL;
	while (temp != NULL)
	{
		if (temp->university.rank == *rank)
		{
			found = true;
			target = temp;
			break;
		}
		temp = temp->next;
	}

	if (found)
	{
		destroyList();
		insertToEndOfList(target->university);
	}
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
		if (*type == 3)
		{
			match = temp->university.ArScore >= minScore && temp->university.ArScore <= maxScore;
		}
		else if (*type == 4)
		{
			match = temp->university.FsrScore >= minScore && temp->university.FsrScore <= maxScore;
		}
		else if (*type == 5)
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
	if (node == head)
	{
		head = head->next;
		head->prev = NULL;
	}
	else if (node == tail)
	{
		tail = tail->prev;
		tail->next = NULL;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	delete node;
	size--;
}