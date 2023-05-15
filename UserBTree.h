#pragma once

#include "BTree.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Structure.h"
#include "Message.h"
#include "Timer.h"
#include "IsVector.h"
#include "DateTime.h"

#define MAX 4
#define MIN 2

class UserBTree : public BTree
{
private:
	int nodeCount;
	IsVector<UserStruct> userList;
	void traversal(UserBTreeNode* node);
	void preOrder(UserBTreeNode* node);
	void postOrder(UserBTreeNode* node);
	UserBTreeNode* createNode(UserStruct user, UserBTreeNode* child);
	void addValueToNode(UserStruct user, int pos, UserBTreeNode* node, UserBTreeNode* child);
	void splitNode(UserStruct user, UserStruct* pval, int pos, UserBTreeNode* node, UserBTreeNode* child, UserBTreeNode** newNode);
	int setValueIntoNode(UserStruct user, UserStruct* pval, UserBTreeNode* node, UserBTreeNode** child);
	void copySuccessor(UserBTreeNode* node, int pos);
	void removeValue(UserBTreeNode* node, int pos);
	void rightShift(UserBTreeNode* node, int pos);
	void leftShift(UserBTreeNode* node, int pos);
	void mergeLeaves(UserBTreeNode* node, int pos);
	void adjustNode(UserBTreeNode* node, int pos);
	int deleteValueFromNode(int id, UserBTreeNode* node);
	void traversalSearchUserMatch(UserBTreeNode* node, IsVector<UserStruct>* users, const std::string& username);
	void updateValueByID(UserBTreeNode* node, int id, int* pos, std::string type, std::string value);
	void traversalGetUserList(UserBTreeNode* node, IsVector<UserStruct>* users);
	void traversalGetUsersFavourites(UserBTreeNode* node, IsVector<IsVector<std::string>>* favourites);
	void selectUserByID(UserBTreeNode* node, IsVector<UserStruct>* users, int id, int* pos);
	void selectUserByName(UserBTreeNode* node, IsVector<UserStruct>* users, const std::string& username);
	
public:
	UserBTreeNode* root;
	UserBTree();
	~UserBTree();
	void insertValueInBTree(UserStruct user);
	void deleteValueFromBTree(int id);
	void searchUserMatch(IsVector<UserStruct>* users, const std::string& username);
	void traversal();
	void preOrder();
	void postOrder();
	int getTreeNodeCount();
	void updateValueByID(int id, std::string type, std::string value);
	IsVector<UserStruct> getUserList();
	IsVector<std::string> getUsersFavourites();
	IsVector<UserStruct> getUserByKey(std::string type, std::string key);
};

UserBTree::UserBTree()
{
	root = nullptr;
	nodeCount = 0;
}

UserBTree::~UserBTree() {}

void UserBTree::traversal()
{
	auto start = Timer::getCurrentTime();
	traversal(root);
	auto end = Timer::getCurrentTime();
	std::cout << "Traversal time: " << Timer::getRunTime(start, end) << std::endl;
}

void UserBTree::traversal(UserBTreeNode* node)
{
	int i;
	if (node)
	{
		for (i = 0;i < node->count;i++)
		{
			traversal(node->child[i]);
			UserStruct user = node->user[i + 1];
			std::cout << user.userID << " " << user.username << " " << user.email << " " << user.contactNum << " " << user.password << " " << user.lastModifyDate << " " << user.role << " ";
			
			for (int j = 0;j < user.favourite.getSize();j++)
			{
				std::cout << user.favourite.at(j) << " ";
			}
			std::cout << std::endl;
		}
		traversal(node->child[i]);
	}
}

void UserBTree::preOrder()
{
	auto start = Timer::getCurrentTime();
	preOrder(root);
	auto end = Timer::getCurrentTime();
	std::cout << "Preorder time: " << Timer::getRunTime(start, end) << std::endl;
}

void UserBTree::preOrder(UserBTreeNode* node)
{
	int i;
	if (node)
	{
		for (i = 0; i < node->count; i++)
		{
			preOrder(node->child[i]);
		}
		preOrder(node->child[i]);
	}
}

void UserBTree::postOrder()
{
	auto start = Timer::getCurrentTime();
	postOrder(root);
	auto end = Timer::getCurrentTime();
	std::cout << "Postorder time: " << Timer::getRunTime(start, end) << std::endl;
}

void UserBTree::postOrder(UserBTreeNode* node)
{
	int i;
	if (node)
	{
		for (i = 0; i < node->count; i++)
		{
			postOrder(node->child[i]);
		}
		postOrder(node->child[i]);
	}
}

UserBTreeNode* UserBTree::createNode(UserStruct user, UserBTreeNode* child)
{
	UserBTreeNode* newNode = new UserBTreeNode;
	newNode->user[1] = user;
	newNode->count = 1;
	newNode->child[0] = root;
	newNode->child[1] = child;
	return newNode;
}

void UserBTree::addValueToNode(UserStruct user, int pos, UserBTreeNode* node, UserBTreeNode* child)
{
	int j = node->count;
	while (j > pos)
	{
		node->user[j + 1] = node->user[j];
		node->child[j + 1] = node->child[j];
		j--;
	}
	node->user[j + 1] = user;
	node->child[j + 1] = child;
	node->count++;
}

void UserBTree::splitNode(UserStruct user, UserStruct* pval, int pos,
	UserBTreeNode* node, UserBTreeNode* child, UserBTreeNode** newNode)
{
	int median, j;
	if (pos > MIN)
		median = MIN + 1;
	else
		median = MIN;

	*newNode = new UserBTreeNode;
	j = median + 1;
	while (j <= MAX)
	{
		(*newNode)->user[j - median] = node->user[j];
		(*newNode)->child[j - median] = node->child[j];
		j++;
	}

	node->count = median;
	(*newNode)->count = MAX - median;

	if (pos <= MIN)
	{
		addValueToNode(user, pos, node, child);
	}
	else
	{
		addValueToNode(user, pos - median, *newNode, child);
	}
	*pval = node->user[node->count];
	(*newNode)->child[0] = node->child[node->count];
	node->count--;
}

int UserBTree::setValueIntoNode(UserStruct user, UserStruct* pval, UserBTreeNode* node, UserBTreeNode** child)
{
	int pos;
	if (!node)
	{
		*pval = user;
		*child = nullptr;
		return 1;
	}

	if (user.userID < node->user[1].userID)
	{
		pos = 0;
	}
	else
	{
		for (pos = node->count; (user.userID < node->user[pos].userID && pos > 1); pos--);
		if (user.userID == node->user[pos].userID)
		{
			Message::error("Duplicates not allowed");
			return 0;
		}
	}

	if (setValueIntoNode(user, pval, node->child[pos], child))
	{
		if (node->count < MAX)
		{
			addValueToNode(*pval, pos, node, *child);
		}
		else
		{
			splitNode(*pval, pval, pos, node, *child, child);
			return 1;
		}
	}
	nodeCount++;
	return 0;
}

void UserBTree::insertValueInBTree(UserStruct user)
{
	int flag;
	UserStruct i;
	UserBTreeNode* child;

	flag = setValueIntoNode(user, &i, root, &child);
	if (flag)
		root = createNode(i, child);
}

void UserBTree::copySuccessor(UserBTreeNode* node, int pos)
{
	UserBTreeNode* dummy;
	dummy = node->child[pos];

	while (dummy->child[0])
		dummy = dummy->child[0];
	node->user[pos] = dummy->user[1];
}

void UserBTree::removeValue(UserBTreeNode* node, int pos)
{
	int i = pos + 1;
	while (i <= node->count)
	{
		node->user[i - 1] = node->user[i];
		node->child[i - 1] = node->child[i];
		i++;
	}
	node->count--;
}

void UserBTree::rightShift(UserBTreeNode* node, int pos)
{
	UserBTreeNode* x = node->child[pos];
	int j = x->count;

	while (j > 0)
	{
		x->user[j + 1] = x->user[j];
		x->child[j + 1] = x->child[j];
	}
	x->user[1] = node->user[pos];
	x->child[1] = x->child[0];
	x->count++;

	x = node->child[pos - 1];
	node->user[pos] = x->user[x->count];
	node->child[pos]->child[0] = x->child[x->count];
	x->count--;
	return;
}

void UserBTree::leftShift(UserBTreeNode* node, int pos)
{
	int j = 1;
	UserBTreeNode* x = node->child[pos - 1];

	x->count++;
	x->user[x->count] = node->user[pos];
	x->child[x->count] = node->child[pos]->child[0];

	x = node->child[pos];
	node->user[pos] = x->user[1];
	x->child[0] = x->child[1];
	x->count--;

	while (j <= x->count)
	{
		x->user[j] = x->user[j + 1];
		x->child[j] = x->child[j + 1];
		j++;
	}
	return;
}

void UserBTree::mergeLeaves(UserBTreeNode* node, int pos)
{
	int j = 1;
	UserBTreeNode* x1 = node->child[pos], * x2 = node->child[pos - 1];

	x2->count++;
	x2->user[x2->count] = node->user[pos];
	x2->child[x2->count] = x1->child[0];

	while (j <= x1->count)
	{
		x2->count++;
		x2->user[x2->count] = x1->user[j];
		x2->child[x2->count] = x1->child[j];
		j++;
	}

	j = pos;
	while (j < node->count)
	{
		node->user[j] = node->user[j + 1];
		node->child[j] = node->child[j + 1];
		j++;
	}
	node->count--;
	free(x1);
}

void UserBTree::adjustNode(UserBTreeNode* node, int pos)
{
	if (!pos)
	{
		if (node->child[1]->count > MIN)
		{
			leftShift(node, 1);
		}
		else
		{
			mergeLeaves(node, 1);
		}
	}
	else
	{
		if (node->count != pos)
		{
			if (node->child[pos - 1]->count > MIN)
			{
				rightShift(node, pos);
			}
			else
			{
				if (node->child[pos + 1]->count > MIN)
				{
					leftShift(node, pos + 1);
				}
				else
				{
					mergeLeaves(node, pos);
				}
			}
		}
		else
		{
			if (node->child[pos - 1]->count > MIN)
				rightShift(node, pos);
			else
				mergeLeaves(node, pos);
		}
	}
}

int UserBTree::deleteValueFromNode(int id, UserBTreeNode* node)
{
	int pos, flag = 0;
	if (node)
	{
		if (id < node->user[1].userID)
		{
			pos = 0;
			flag = 0;
		}
		else
		{
			for (pos = node->count; (id < node->user[pos].userID && pos > 1); pos--);
			if (id == node->user[pos].userID)
			{
				flag = 1;
			}
			else
			{
				flag = 0;
			}
		}
		if (flag)
		{
			if (node->child[pos - 1])
			{
				copySuccessor(node, pos);
				flag = deleteValueFromNode(node->user[pos].userID, node->child[pos]);
				if (flag == 0)
				{
					Message::warning("Given data is not present in B-Tree");
				}
			}
			else
			{
				removeValue(node, pos);
			}
		}
		else
		{
			flag = deleteValueFromNode(id, node->child[pos]);
		}
		if (node->child[pos])
		{
			if (node->child[pos]->count < MIN)
				adjustNode(node, pos);
		}
	}
	return flag;
}

int UserBTree::getTreeNodeCount()
{
	return nodeCount;
}

void UserBTree::deleteValueFromBTree(int id)
{
	UserBTreeNode* temp;
	if (!deleteValueFromNode(id, root))
	{
		Message::error("Value not found");
		return;
	}
	else
	{
		if (root->count == 0)
		{
			temp = root;
			root = root->child[0];
			free(temp);
		}
	}
}

void UserBTree::searchUserMatch(IsVector<UserStruct>* users, const std::string& username)
{
	traversalSearchUserMatch(root, users, username);
}

void UserBTree::traversalSearchUserMatch(UserBTreeNode* node, IsVector<UserStruct>* users, const std::string& username)
{
	bool found = false;
	if (!node) return;
	
	for (int i = 1; i <= node->count; i++)
	{
		std::string data = node->user[i].username;
		data.erase(std::remove(data.begin(), data.end(), ' '), data.end());

		if (data == username)
		{
			found = true;
			users->push_back(node->user[i]);
			break;
		}
	}

	if (found) return;

	for (int i = 0; i <= node->count; i++)
		traversalSearchUserMatch(node->child[i], users, username);
}

// type: "date", "contact", "email"
void UserBTree::updateValueByID(int id, std::string type, std::string value)
{
	if (type != "date" && type != "contact" && type != "email")
	{
		Message::error("Invalid update type");
		return;
	}
	//start time
	updateValueByID(root, id, &id, type, value);
	//end time
}

void UserBTree::updateValueByID(UserBTreeNode* node, int id, int* pos, std::string type, std::string value)
{
	bool found = false;

	if (!node) 
	{
		std::string msg = "User with ID " + std::to_string(id) + " not found";
		Message::error(msg);
		return;
	}

	if (id < node->user[1].userID)
		*pos = 0;
	else
	{
		for (*pos = node->count; (id < node->user[*pos].userID && *pos > 1); (*pos)--);
		if (id == node->user[*pos].userID)
		{
			std::string msg = "User with ID " + std::to_string(id) + "'s details updated";
			if(type == "date")
				node->user[*pos].lastModifyDate = value;
			else if (type == "contact")
				node->user[*pos].contactNum = value;
			else if (type == "email")
				node->user[*pos].email = value;
			found = true;
			Message::notice(msg);
			std::cout << std::endl;
			return;
		}
	}

	if (found) return;

	updateValueByID(node->child[*pos], id, pos, type, value);
}

IsVector<UserStruct> UserBTree::getUserList()
{
	IsVector<UserStruct>* users = new IsVector<UserStruct>();
	traversalGetUserList(root, users);
	return *users;
}

void UserBTree::traversalGetUserList(UserBTreeNode* node, IsVector<UserStruct>* users)
{
	if (!node) return;

	for (int i = 0; i <= node->count; i++)
	{
		std::string role = node->user[i].role;

		if (role == "user")
		{
			users->push_back(node->user[i]);
		}
		traversalGetUserList(node->child[i], users);
	}
}

IsVector<std::string> UserBTree::getUsersFavourites()
{
	IsVector<IsVector<std::string>>* favourites = new IsVector<IsVector<std::string>>();
	traversalGetUsersFavourites(root, favourites);

	IsVector<std::string>* fav = new IsVector<std::string>();
	
	for (int i = 0; i < favourites->getSize(); i++)
	{
		for (int j = 0; j < favourites->at(i).getSize(); j++)
		{
			fav->push_back(favourites->at(i).at(j));
		}
	}
	
	return *fav;
}

void UserBTree::traversalGetUsersFavourites(UserBTreeNode* node, IsVector<IsVector<std::string>>* favourites)
{
	if (!node) return;

	for (int i = 0; i <= node->count; i++)
	{
		std::string role = node->user[i].role;

		if (role == "user")
		{
			favourites->push_back(node->user[i].favourite);
		}

		traversalGetUsersFavourites(node->child[i], favourites);
	}
}

// type: "username", "id"
IsVector<UserStruct> UserBTree::getUserByKey(std::string type, std::string key)
{
	//TODO
	IsVector<UserStruct>* user = new IsVector<UserStruct>();
	if (type == "id")
	{
		int id = std::stoi(key);
		selectUserByID(root, user, id, &id);
	}
	else if (type == "username")
	{
		selectUserByName(root, user, key);
	}
	else
	{
		Message::error("Invalid search type");
	}
	return *user;
}

void UserBTree::selectUserByID(UserBTreeNode* node, IsVector<UserStruct>* users, int id, int* pos)
{
	bool found = false;
	
	if (!node) return;

	if (id < node->user[1].userID)
		*pos = 0;
	else
	{
		for (*pos = node->count; (id < node->user[*pos].userID && *pos > 1); (*pos)--);
		if (id == node->user[*pos].userID && node->user[*pos].role == "user")
		{
			users->push_back(node->user[*pos]);
			found = true;
			return;
		}
	}
	
	if (found) return;

	selectUserByID(node->child[*pos], users, id, pos);
}

void UserBTree::selectUserByName(UserBTreeNode* node, IsVector<UserStruct>* users, const std::string& username)
{
	bool found = false;
	if (!node) return;

	for (int i = 1; i <= node->count; i++)
	{
		std::string data = node->user[i].username;
		std::string role = node->user[i].role;
		if (data == username && role == "user")
		{
			found = true;
			users->push_back(node->user[i]);
			break;
		}
	}

	if (found) return;

	for (int i = 0; i <= node->count; i++)
		selectUserByName(node->child[i], users, username);
}