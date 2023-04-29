#pragma once
#include "Structure.h"
#include <iostream>
#include <string>

class UserList
{
	UserNode* head = NULL;
	int size = 0;
public:
	UserList();
	~UserList();
	UserNode* createNewNode(UserStruct user);
	void insertToEndOfList(UserStruct user);
	void deleteByUserID(int userID);
	UserNode* searchByUserID(int userID);
	void displayUserList();
};

UserList::UserList()
{
}

UserList::~UserList()
{
	//destroy
}

UserNode* UserList::createNewNode(UserStruct user)
{
	UserNode* newNode = new UserNode;
	newNode->user = user;
	newNode->next = NULL;
	return newNode;
}

void UserList::insertToEndOfList(UserStruct user)
{
	UserNode* newNode = createNewNode(user);
	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		UserNode* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	size++;
}

void UserList::deleteByUserID(int userID)
{
	if (head == NULL)
	{
		std::cout << "User list is empty." << std::endl;
	}
	else
	{
		UserNode* temp = head;
		UserNode* prev = NULL;
		while (temp != NULL)
		{
			if (temp->user.userID == userID)
			{
				if (prev == NULL)
				{
					head = temp->next;
				}
				else
				{
					prev->next = temp->next;
				}
				delete temp;
				size--;
				return;
			}
			prev = temp;
			temp = temp->next;
		}
		std::cout << "User with ID " << userID << " not found." << std::endl;
	}
}

UserNode* UserList::searchByUserID(int userID)
{
	if (head == NULL)
	{
		std::cout << "User list is empty." << std::endl;
		return NULL;
	}
	else
	{
		UserNode* temp = head;
		while (temp != NULL)
		{
			if (temp->user.userID == userID)
			{
				return temp;
			}
			temp = temp->next;
		}
		std::cout << "User with ID " << userID << " not found." << std::endl;
		return NULL;
	}
}

void UserList::displayUserList()
{
	if (head == NULL)
	{
		std::cout << "User list is empty." << std::endl;
	}
	else
	{
		UserNode* temp = head;
		while (temp != NULL)
		{
			if (temp->user.role == "admin")
			{
				temp = temp->next;
				continue;
			}
			std::cout << temp->user.userID << "\t";
			std::cout << temp->user.username << "\t";
			std::cout << temp->user.email << "\t\t";
			std::cout << temp->user.contactNum << "\t\t";
			std::cout << temp->user.lastModifyDate << "\t\t";
			std::cout << std::endl;
			temp = temp->next;
		}
	}
}