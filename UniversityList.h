#pragma once
#include "Structure.h"
#include "QuickSort.h"
#include <iostream>
#include <string>

class UniversityList
{
private:
	UniversityNode* head = NULL;
	UniversityNode* tail = NULL;
	int size = 0;
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
	void quicksort(std::string, bool);
	int getSize();
	void destroyList();
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
	while (temp != NULL)
	{
		std::cout << temp->university.rank << "\t" << temp->university.institution << std::endl;
		temp = temp->next;
	}
}

void UniversityList::displayUniversityListDesc()
{
	UniversityNode* temp = tail;

	while (temp != NULL)
	{
		std::cout << temp->university.rank << "\t" << temp->university.institution << std::endl;
		temp = temp->prev;
	}
}

// type: "institution", "ar_score", "fsr_score", "er_score"
void UniversityList::quicksort(std::string type, bool isAsc)
{
	UniversityList* copyList = new UniversityList(*this);
	QuickSort::quickSort(copyList->head, copyList->tail, type);
	system("cls");

	if (isAsc)
		copyList->displayUniversityList();
	else
		copyList->displayUniversityListDesc();
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