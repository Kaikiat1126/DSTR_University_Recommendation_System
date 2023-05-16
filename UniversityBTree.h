#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "Structure.h"
#include "Message.h"
#include "BTree.h"
#include "Timer.h"
#include "IsVector.h"

#define MAX 4
#define MIN 2


class UniversityBTree : public BTree
{
private:
	IsVector<UniversityStruct> universityList;
	void traversal(UniversityBTreeNode* node);
	void preOrder(UniversityBTreeNode* node);
	void postOrder(UniversityBTreeNode* node);
	UniversityBTreeNode* createNode(UniversityStruct university, UniversityBTreeNode* child);
	void addValueToNode(UniversityStruct university, int pos, UniversityBTreeNode* node, UniversityBTreeNode* child);
	void splitNode(UniversityStruct university, UniversityStruct* pval, int pos, UniversityBTreeNode* node, UniversityBTreeNode* child, UniversityBTreeNode** newNode);
	int setValueIntoNode(UniversityStruct university, UniversityStruct* pval, UniversityBTreeNode* node, UniversityBTreeNode** child);
	void copySuccessor(UniversityBTreeNode* node, int pos);
	void rightShift(UniversityBTreeNode* node, int pos);
	void leftShift(UniversityBTreeNode* node, int pos);
	void mergeLeaves(UniversityBTreeNode* node, int pos);
	void adjustNode(UniversityBTreeNode* node, int pos);
	void traversalSearchName(UniversityBTreeNode* node, std::string name);
		
public:
	UniversityBTreeNode* root;
	UniversityBTree();
	~UniversityBTree();
	void insertValueInBTree(UniversityStruct university);
	void searchValueInBTree(int rank, int* pos, UniversityBTreeNode* node);
	void searchUniversityByName(std::string institution);
	void traversal();
	void preOrder();
	void postOrder();
};


UniversityBTree::UniversityBTree()
{
	root = nullptr;
}

UniversityBTree::~UniversityBTree() {}

void UniversityBTree::traversal()
{
	auto start = Timer::getCurrentTime();
	traversal(root);
	auto end = Timer::getCurrentTime();
	std::cout << "Traversal time: " << Timer::getRunTime(start, end) << std::endl;
}

void UniversityBTree::traversal(UniversityBTreeNode* node)
{
	int i;
	if (node)
	{
		for (i = 0;i < node->count;i++)
		{
			traversal(node->child[i]);
			//std::cout << node->university[i + 1].rank << " " << node->university[i + 1].institution << std::endl;
		}
		traversal(node->child[i]);
	}
}

void UniversityBTree::preOrder()
{
	auto start = Timer::getCurrentTime();
	preOrder(root);
	auto end = Timer::getCurrentTime();
	std::cout << "Preorder time: " << Timer::getRunTime(start, end) << std::endl;
}

void UniversityBTree::preOrder(UniversityBTreeNode* node)
{
	int i;
	if (node)
	{
		for (i = 0; i < node->count; i++)
		{
			//std::cout << node->university[i + 1].institution << " ";
			preOrder(node->child[i]);
		}
		preOrder(node->child[i]);
	}
}

void UniversityBTree::postOrder()
{
	auto start = Timer::getCurrentTime();
	postOrder(root);
	auto end = Timer::getCurrentTime();
	std::cout << "Postorder time: " << Timer::getRunTime(start, end) << std::endl;
}

void UniversityBTree::postOrder(UniversityBTreeNode* node)
{
	int i;
	if (node)
	{
		for (i = 0; i < node->count; i++)
		{
			postOrder(node->child[i]);
			//std::cout << node->university[i + 1].institution << " ";
		}
		postOrder(node->child[i]);
	}
}

UniversityBTreeNode* UniversityBTree::createNode(UniversityStruct university, UniversityBTreeNode* child)
{
	UniversityBTreeNode* newNode = new UniversityBTreeNode;
	newNode->university[1] = university;
	newNode->count = 1;
	newNode->child[0] = root;
	newNode->child[1] = child;
	return newNode;
}

void UniversityBTree::addValueToNode(UniversityStruct university, int pos, UniversityBTreeNode* node, UniversityBTreeNode* child)
{
	int j = node->count;
	while (j > pos)
	{
		node->university[j + 1] = node->university[j];
		node->child[j + 1] = node->child[j];
		j--;
	}
	node->university[j + 1] = university;
	node->child[j + 1] = child;
	node->count++;
}

void UniversityBTree::splitNode(UniversityStruct university, UniversityStruct* pval, int pos,
	UniversityBTreeNode* node, UniversityBTreeNode* child, UniversityBTreeNode** newNode)
{
	int median, j;
	if (pos > MIN)
		median = MIN + 1;
	else
		median = MIN;

	*newNode = new UniversityBTreeNode;
	j = median + 1;
	while (j <= MAX)
	{
		(*newNode)->university[j - median] = node->university[j];
		(*newNode)->child[j - median] = node->child[j];
		j++;
	}

	node->count = median;
	(*newNode)->count = MAX - median;

	if (pos <= MIN)
	{
		addValueToNode(university, pos, node, child);
	}
	else
	{
		addValueToNode(university, pos - median, *newNode, child);
	}
	*pval = node->university[node->count];
	(*newNode)->child[0] = node->child[node->count];
	node->count--;
}

int UniversityBTree::setValueIntoNode(UniversityStruct university, UniversityStruct* pval, UniversityBTreeNode* node, UniversityBTreeNode** child)
{
	int pos;
	if (!node)
	{
		*pval = university;
		*child = nullptr;
		return 1;
	}

	if (university.rank < node->university[1].rank)
	{
		pos = 0;
	}
	else
	{
		for (pos = node->count; (university.rank < node->university[pos].rank && pos > 1); pos--);
		if (university.rank == node->university[pos].rank)
		{
			Message::error("Duplicates not allowed");
			return 0;
		}
	}

	if (setValueIntoNode(university, pval, node->child[pos], child))
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
	return 0;
}

void UniversityBTree::insertValueInBTree(UniversityStruct university)
{
	int flag;
	UniversityStruct i;
	UniversityBTreeNode* child;

	flag = setValueIntoNode(university, &i, root, &child);
	if (flag)
		root = createNode(i, child);
}

void UniversityBTree::copySuccessor(UniversityBTreeNode* node, int pos)
{
	UniversityBTreeNode* dummy;
	dummy = node->child[pos];

	while (dummy->child[0])
		dummy = dummy->child[0];
	node->university[pos] = dummy->university[1];
}

void UniversityBTree::rightShift(UniversityBTreeNode* node, int pos)
{
	UniversityBTreeNode* x = node->child[pos];
	int j = x->count;

	while (j > 0)
	{
		x->university[j + 1] = x->university[j];
		x->child[j + 1] = x->child[j];
	}
	x->university[1] = node->university[pos];
	x->child[1] = x->child[0];
	x->count++;

	x = node->child[pos - 1];
	node->university[pos] = x->university[x->count];
	node->child[pos]->child[0] = x->child[x->count];
	x->count--;
	return;
}

void UniversityBTree::leftShift(UniversityBTreeNode* node, int pos)
{
	int j = 1;
	UniversityBTreeNode* x = node->child[pos - 1];

	x->count++;
	x->university[x->count] = node->university[pos];
	x->child[x->count] = node->child[pos]->child[0];

	x = node->child[pos];
	node->university[pos] = x->university[1];
	x->child[0] = x->child[1];
	x->count--;

	while (j <= x->count)
	{
		x->university[j] = x->university[j + 1];
		x->child[j] = x->child[j + 1];
		j++;
	}
	return;
}

void UniversityBTree::mergeLeaves(UniversityBTreeNode* node, int pos)
{
	int j = 1;
	UniversityBTreeNode* x1 = node->child[pos], * x2 = node->child[pos - 1];

	x2->count++;
	x2->university[x2->count] = node->university[pos];
	x2->child[x2->count] = x1->child[0];

	while (j <= x1->count)
	{
		x2->count++;
		x2->university[x2->count] = x1->university[j];
		x2->child[x2->count] = x1->child[j];
		j++;
	}

	j = pos;
	while (j < node->count)
	{
		node->university[j] = node->university[j + 1];
		node->child[j] = node->child[j + 1];
		j++;
	}
	node->count--;
	free(x1);
}

void UniversityBTree::adjustNode(UniversityBTreeNode* node, int pos)
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

void UniversityBTree::traversalSearchName(UniversityBTreeNode* node, std::string institution)
{
	bool found = false;
	if (!node) return;

	for (int i = 1; i <= node->count; i++)
	{
		std::string data = node->university[i].institution;

		//std::cout << node->university[i].institution << std::endl;
		if (data == institution)
		{
			//std::cout << node->university[i].institution << " " << node->university[i].rank << std::endl;
			found = true;
			universityList.push_back(node->university[i]);
			//std::cout << "Size of list: " << universityList.getSize() << std::endl;
			break;
		}
	}

	if (found) return;
	
	for (int i = 0; i <= node->count; i++)
		traversalSearchName(node->child[i], institution);
}

void UniversityBTree::searchValueInBTree(int rank, int* pos, UniversityBTreeNode* node)
{
	if (!node)
		return;

	if (rank < node->university[1].rank)
		*pos = 0;
	else
	{
		std::string msg = "UniversityStruct with ID ";
		for (*pos = node->count; (rank < node->university[*pos].rank && *pos > 1); (*pos)--);
		if (rank == node->university[*pos].rank)
		{
			msg = msg + std::to_string(rank) + " found";
			Message::notice(msg);
			return;
		}
		msg = msg + std::to_string(rank) + " not found";
		Message::warning(msg);
	}
	searchValueInBTree(rank, pos, node->child[*pos]);
	return;
}

void UniversityBTree::searchUniversityByName(std::string institution)
{
	universityList.clear();
	UniversityBTreeNode* cursor = root;

	traversalSearchName(cursor, institution);

	std::string msg = "University with name ";
	
	if (universityList.getSize() == 0)
	{
		msg = msg + institution + " not found!";
		Message::warning(msg);
		return;
	}
	else
	{
		msg = msg + institution + " found!";
		Message::success(msg);

		UniversityStruct university = universityList.at(0);
		std::cout << std::endl;
		std::cout << "Rank \tInstitution \t\tLocationCode \tLocation \tArScore ArRank " <<
			" ErScore ErRank FsrScore FsrRank CpfScore CpfRank IfrScore IfrRank IsrScore IsrRank IrnScore IrnRank GerScore GerRank ScoreScaled" << std::endl;

		//check each of the rank of the university is Null or not, if null then fill with '-'
		/*std::string IfrScore = university.IfrScore == NULL ? "-" : std::to_string(university.IfrScore);
		std::string IfrRank = university.IfrRank == NULL ? "-" : std::to_string(university.IfrRank);
		std::string IsrScore = university.IsrScore == NULL ? "-" : std::to_string(university.IsrScore);
		std::string IsrRank = university.IsrRank == NULL ? "-" : std::to_string(university.IsrRank);
		std::string IrnScore = university.IrnScore == NULL ? "-" : std::to_string(university.IrnScore);
		std::string IrnRank = university.IrnRank == NULL ? "-" : std::to_string(university.IrnRank);
		std::string GerScore = university.GerScore == NULL ? "-" : std::to_string(university.GerScore);
		std::string GerRank = university.GerRank == NULL ? "-" : std::to_string(university.GerRank);*/
		std::string ScoreScaled = university.ScoreScaled == NULL ? "-" : std::to_string(university.ScoreScaled);
		
		
		std::cout << university.rank << "\t" << university.institution << "\t" << university.locationCode << "\t\t"
			<< university.location << "\t\t" << university.ArScore << "\t" << university.ArRank << "\t" << university.ErScore
			<< "\t" << university.ErRank << "\t" << university.FsrScore << "\t" << university.FsrRank << "\t" << university.CpfScore << "\t" << university.CpfRank
			<< "\t" << university.IfrScore << "\t" << university.IfrRank << "\t" << university.IsrScore << "\t" << university.IsrRank << "\t" << university.IrnScore
			<< "\t" << university.IrnRank << "\t" << university.GerScore << "\t" << university.GerRank << "\t" << ScoreScaled << std::endl;
	}
}
