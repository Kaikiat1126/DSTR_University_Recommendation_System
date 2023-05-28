#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "Structure.h"
#include "Message.h"
#include "BTree.h"
#include "Timer.h"
#include "IsVector.h"
#include "UniversityList.h"

#define MAX 4
#define MIN 2


class UniversityBTree : public BTree
{
private:
	UniversityBTreeNode* root;
	void traversal(UniversityBTreeNode* node);
	void preOrder(UniversityBTreeNode* node);
	void postOrder(UniversityBTreeNode* node);
	UniversityBTreeNode* createNode(UniversityStruct university, UniversityBTreeNode* child);
	void addValueToNode(UniversityStruct university, int pos, UniversityBTreeNode* node, UniversityBTreeNode* child);
	void splitNode(UniversityStruct university, UniversityStruct* pval, int pos, UniversityBTreeNode* node, 
		UniversityBTreeNode* child, UniversityBTreeNode** newNode);
	int setValueIntoNode(UniversityStruct university, UniversityStruct* pval, UniversityBTreeNode* node, UniversityBTreeNode** child);
	void copySuccessor(UniversityBTreeNode* node, int pos);
	void rightShift(UniversityBTreeNode* node, int pos);
	void leftShift(UniversityBTreeNode* node, int pos);
	void mergeLeaves(UniversityBTreeNode* node, int pos);
	void adjustNode(UniversityBTreeNode* node, int pos);
	void traversalSearchName(UniversityBTreeNode* node, const std::string& name, IsVector<UniversityStruct>& university);
	void traversalSearchNameOnly(UniversityBTreeNode* node, const std::string& name);
	void searchByRankInBTree(int rank, int* pos, UniversityBTreeNode* node);
	std::string searchNameByRank(UniversityBTreeNode* node, int rank, int* pos);
	
	// for returning vector
	void getUniversityByRank(UniversityBTreeNode* node, int rank, int* pos, IsVector<UniversityStruct>& university);
	void getUniversityByValue(UniversityBTreeNode* node, int* type, int* range, IsVector<UniversityStruct>& universities);
	void getUniversityWithStr(UniversityBTreeNode* node, int* type, std::string& value, IsVector<UniversityStruct>& universities);

	// for returning linkedlist
	void filterUniversityByValue(UniversityBTreeNode* node,int* type, int* range, UniversityList* list);
	void filterUniversityWithLocation(UniversityBTreeNode* node, std::string& value, UniversityList* list);
	void filterUniversityWithRank(UniversityBTreeNode* node, int rank, int* pos, UniversityList* list);

	void filterSpecificUniverstiyLocation(UniversityBTreeNode* node, IsVector<std::string>* location);

	void displayUniveristies(IsVector<UniversityStruct>& universities);
		
public:
	UniversityBTree();
	void insertValueInBTree(UniversityStruct university);
	void searchUniversityByRank(int rank);
	IsVector<UniversityStruct> getUniversityByRank(int rank);
	IsVector<UniversityStruct> getUniversityByValue(int* type, int* range, std::string* value);
	UniversityList* filterUniversityByValue(int* type, int* range, std::string* value);
	void searchUniversityByName(const std::string& institution);
	void traversal();
	void preOrder();
	void postOrder();
	std::string getUniversityNameByRank(int rank);
	IsVector<std::string> getUniversityLocationCode();
};


UniversityBTree::UniversityBTree()
{
	root = nullptr;
}

void UniversityBTree::traversal()
{
	auto start = Timer::getCurrentTime();
	traversal(root);
	auto end = Timer::getCurrentTime();
	std::cout << "BTree Traversal time: " << Timer::getRunTime(start, end) << std::endl;
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

void UniversityBTree::traversalSearchName(UniversityBTreeNode* node, const std::string& institution, IsVector<UniversityStruct>& university)
{
	if (!node) return;

	for (int i = 1; i <= node->count; i++)
	{
		if (node->university[i].institution == institution)
		{
			university.push_back(node->university[i]);
			return;
		}
	}

	for (int i = 0; i <= node->count; i++)
	{
		if (node->child[i])
		{
			traversalSearchName(node->child[i], institution, university);
		}
	}
}

void UniversityBTree::traversalSearchNameOnly(UniversityBTreeNode* node, const std::string& institution)
{
	if (!node) return;

	for (int i = 1; i <= node->count; i++)
	{
		if (node->university[i].institution == institution)
		{
			return;
		}
	}

	for (int i = 0; i <= node->count; i++)
	{
		if (node->child[i])
		{
			traversalSearchNameOnly(node->child[i], institution);
		}
	}
}

void UniversityBTree::searchUniversityByName(const std::string& institution)
{
	IsVector<UniversityStruct> list = IsVector<UniversityStruct>();

	traversalSearchName(root, institution, list);

	std::string msg = "University with name \"";

	if (list.getSize() == 0)
	{
		msg = msg + institution + "\" not found!";
		Message::warning(msg);
		return;
	}
	else
	{
		msg = msg + institution + "\" found!";
		Message::success(msg);
		displayUniveristies(list);
		auto start = Timer::getCurrentTime();
		traversalSearchNameOnly(root, institution);
		auto end = Timer::getCurrentTime();
		std::cout << "BTree search with institution run time: " << Timer::getRunTime(start, end) << std::endl;
	}
}

// used for compare run time
void UniversityBTree::searchUniversityByRank(int rank)
{
	auto start = Timer::getCurrentTime();
	searchByRankInBTree(rank, &rank, root);
	auto end = Timer::getCurrentTime();
	std::cout << "BTree Search By Rank's Time: " << Timer::getRunTime(start, end) << std::endl;
}

void UniversityBTree::searchByRankInBTree(int rank, int* pos, UniversityBTreeNode* node)
{
	bool found = false;
	if (!node)
	{
		//std::string msg = std::to_string(rank) + " not found";
		//Message::warning(msg);
		return;
	}

	if (rank < node->university[1].rank)
		*pos = 0;
	else
	{
		//std::string msg = "University with Rank ";
		for (*pos = node->count; (rank < node->university[*pos].rank && *pos > 1); (*pos)--);
		//UniversityStruct data = node->university[*pos];
		if (rank == node->university[*pos].rank)
		{
			found = true;
			//msg = msg + std::to_string(rank) + " found!";
			//Message::notice(msg);
			/*std::cout << data.rank << "\t" << data.institution << "\t" << data.locationCode << "\t\t"
				<< data.location << "\t\t" << data.ArScore << "\t" << data.ArRank << "\t" << data.ErScore
				<< "\t" << data.ErRank << "\t" << data.FsrScore << "\t" << data.FsrRank << "\t" << data.CpfScore << "\t" << data.CpfRank
				<< "\t" << data.IfrScore << "\t" << data.IfrRank << "\t" << data.IsrScore << "\t" << data.IsrRank << "\t" << data.IrnScore
				<< "\t" << data.IrnRank << "\t" << data.GerScore << "\t" << data.GerRank << "\t" << data.ScoreScaled << std::endl;*/
			return;
		}
	}

	if (found) return;
	searchByRankInBTree(rank, pos, node->child[*pos]);
}

IsVector<UniversityStruct> UniversityBTree::getUniversityByRank(int rank)
{
	IsVector<UniversityStruct> university;
	getUniversityByRank(root, rank, &rank, university);
	return university;
}

void UniversityBTree::getUniversityByRank(UniversityBTreeNode* node, int rank, int* pos, IsVector<UniversityStruct>& university)
{
	bool found = false;
	if (!node)
	{
		return;
	}

	if (rank < node->university[1].rank)
		*pos = 0;
	else
	{
		for (*pos = node->count; (rank < node->university[*pos].rank && *pos > 1); (*pos)--);
		UniversityStruct data = node->university[*pos];
		if (rank == node->university[*pos].rank)
		{
			found = true;
			university.push_back(data);
			return;
		}
	}

	if (found) return;
	getUniversityByRank(node->child[*pos], rank, pos, university);
}

// type: "0 = rank", "1 = name", "2 = locationCode", "3 = ar score", "4 = fsr score", "5 = er score"
// range: "1 = 0-20" , "2 = 21-40", "3 = 41-60", "4 = 61-80", "5 = 81-100"
// type is 0 then range: "1 = 1-100", "2 = 101-300", "3 = 301-500", "4 = 501-800", "5 = 801-1200", "6 = 1201+"
IsVector<UniversityStruct> UniversityBTree::getUniversityByValue(int* type, int* range, std::string* value)
{
	IsVector<UniversityStruct> universities = IsVector<UniversityStruct>();

	/*if (*type == 0)
	{
		int min = 101, max = 300;
		getUniversityByRankRange(root, &min, &max, universities);
	}*/
	if (*type == 1)
	{
		int rank = std::stoi(*value);
		getUniversityByRank(root, rank, &rank, universities);
	}
	else if (*type == 2)
		getUniversityWithStr(root, type, *value, universities);
	else if (*type == 3 || *type == 4 || *type == 5)
		getUniversityByValue(root, type, range, universities);
	
	return universities;
}

// type: "0 = rank", "1 = name", "2 = locationCode", "3 = ar score", "4 = fsr score", "5 = er score"
// name need to been remove spaces
// range: "1 = 0-20" , "2 = 21-40", "3 = 41-60", "4 = 61-80", "5 = 81-100"
void UniversityBTree::getUniversityByValue(UniversityBTreeNode* node, int* type, int* range, IsVector<UniversityStruct>& universities)
{

	if (!node) return;
	
	int minScore = (*range - 1) * 20;
	int maxScore = *range * 20;

	for (int i = 1; i <= node->count; i++)
	{
		bool match = false;
		if (*type == 3)
		{
			match = (node->university[i].ArScore >= minScore && node->university[i].ArScore <= maxScore);
		}
		else if (*type == 4)
		{
			match = (node->university[i].FsrScore >= minScore && node->university[i].FsrScore <= maxScore);
		}
		else if (*type == 5)
		{
			match = (node->university[i].ErScore >= minScore && node->university[i].ErScore <= maxScore);
		}

		if (match)
		{
			universities.push_back(node->university[i]);
		}
	}

	for (int i = 0; i <= node->count; i++)
		getUniversityByValue(node->child[i], type, range, universities);
}

void UniversityBTree::getUniversityWithStr(UniversityBTreeNode* node, int* type, std::string& value, IsVector<UniversityStruct>& universities)
{
	bool found = false;

	if (!node) return;

	for (int i = 1; i <= node->count; i++)
	{
		if (*type == 1)
		{
			std::string institution = node->university[i].institution;
			institution.erase(std::remove(institution.begin(), institution.end(), ' '), institution.end());
			if (institution == value)
			{
				found = true;
				universities.push_back(node->university[i]);
				break;
			}
		}
		else if (*type == 2)
		{
			if (node->university[i].locationCode == value)
			{
				universities.push_back(node->university[i]);
			}
		}
	}

	if (found) return;
	
	for (int i = 0; i <= node->count; i++)
		getUniversityWithStr(node->child[i], type, value, universities);
}

UniversityList* UniversityBTree::filterUniversityByValue(int* type, int* range, std::string* value)
{
	UniversityList* list = new UniversityList();
	if (*type == 1)
		filterUniversityWithLocation(root, *value, list);
	else if (*type == 2 || *type == 3 || *type == 4)
		filterUniversityByValue(root, type, range, list);
	
	return list;
}

void UniversityBTree::filterUniversityByValue(UniversityBTreeNode* node, int* type, int* range, UniversityList* list)
{

	if (!node) return;
	
	int minScore = (*range - 1) * 20;
	int maxScore = *range * 20;

	for (int i = 1; i <= node->count; i++)
	{
		bool match = false;
		if (*type == 2)
		{
			match = (node->university[i].ArScore >= minScore && node->university[i].ArScore <= maxScore);
		}
		else if (*type == 3)
		{
			match = (node->university[i].FsrScore >= minScore && node->university[i].FsrScore <= maxScore);
		}
		else if (*type == 4)
		{
			match = (node->university[i].ErScore >= minScore && node->university[i].ErScore <= maxScore);
		}

		if (match)
		{
			list->insertToEndOfList(node->university[i]);
		}
	}

	for (int i = 0; i <= node->count; i++)
		filterUniversityByValue(node->child[i], type, range, list);
}

void UniversityBTree::filterUniversityWithLocation(UniversityBTreeNode* node, std::string& value, UniversityList* list)
{
	if (!node) return;

	for (int i = 1; i <= node->count; i++)
	{

		if (node->university[i].locationCode == value)
		{
			list->insertToEndOfList(node->university[i]);
		}
	}
	
	for (int i = 0; i <= node->count; i++)
		filterUniversityWithLocation(node->child[i], value, list);
}

void UniversityBTree::filterUniversityWithRank(UniversityBTreeNode* node, int rank, int* pos, UniversityList* list)
{
	bool found = false;
	if (!node)
	{
		return;
	}

	if (rank < node->university[1].rank)
		*pos = 0;
	else
	{
		for (*pos = node->count; (rank < node->university[*pos].rank && *pos > 1); (*pos)--);
		UniversityStruct data = node->university[*pos];
		if (rank == node->university[*pos].rank)
		{
			found = true;
			list->insertToEndOfList(node->university[*pos]);
			return;
		}
	}

	if (found) return;
	filterUniversityWithRank(node->child[*pos], rank, pos, list);
}

std::string UniversityBTree::getUniversityNameByRank(int rank)
{
	return searchNameByRank(root, rank, &rank);
}

std::string UniversityBTree::searchNameByRank(UniversityBTreeNode* node, int rank, int* pos)
{
	bool found = false;
	if (!node) return "";

	if (rank < node->university[1].rank)
		*pos = 0;
	else
	{
		for (*pos = node->count; (rank < node->university[*pos].rank && *pos > 1); (*pos)--);
		UniversityStruct data = node->university[*pos];
		if (rank == node->university[*pos].rank)
		{
			found = true;
			return node->university[*pos].institution;
		}
	}
	
	if (!found)
		return searchNameByRank(node->child[*pos], rank, pos);
}

IsVector<std::string> UniversityBTree::getUniversityLocationCode()
{
	IsVector<std::string> locationCode;
	filterSpecificUniverstiyLocation(root, &locationCode);
	return locationCode;
}

void UniversityBTree::filterSpecificUniverstiyLocation(UniversityBTreeNode* node, IsVector<std::string>* location)
{
	if (!node) return;
	
	for (int i = 1; i <= node->count; i++)
	{
		bool found = false;
		for (int j = 0; j < location->getSize(); j++)
		{
			if (node->university[i].locationCode == location->at(j))
			{
				found = true;
				break;
			}
		}
		if (!found)
			location->push_back(node->university[i].locationCode);
	}
	
	for (int i = 0; i <= node->count; i++)
		filterSpecificUniverstiyLocation(node->child[i], location);
}

void UniversityBTree::displayUniveristies(IsVector<UniversityStruct>& universities)
{
	for (int i = 0; i < universities.getSize(); i++)
	{
		UniversityStruct university = universities.at(i);
		std::cout << std::endl;
		std::cout << "Rank           :" << university.rank << '\t';
		std::cout << "Institution    :" << university.institution << '\n';
		std::cout << "Location code  :" << university.locationCode << '\t';
		std::cout << "Location       :" << university.location << '\n';
		std::cout << "ArScore        :" << university.ArScore << '\t';
		std::cout << "ArRank         :" << university.ArRank << '\t';
		std::cout << "ErScore        :" << university.ErScore << '\t';
		std::cout << "ErRank         :" << university.ErRank << '\t';
		std::cout << "FsrScore       :" << university.FsrScore << '\t';
		std::cout << "FsrRank        :" << university.FsrRank << '\n';
		std::cout << "CpfScore       :" << university.CpfScore << '\t';
		std::cout << "CpfRank        :" << university.CpfRank << '\t';
		std::cout << "IfrScore       :" << university.IfrScore << '\t';
		std::cout << "IfrRank        :" << university.IfrRank << '\t';
		std::cout << "IsrScore       :" << university.IsrScore << '\t';
		std::cout << "IsrRank        :" << university.IsrRank << '\n';
		std::cout << "IrnScore       :" << university.IrnScore << '\t';
		std::cout << "IrnRank        :" << university.IrnRank << '\t';
		std::cout << "GerScore       :" << university.GerScore << '\t';
		std::cout << "GerRank        :" << university.GerRank << '\t';
		std::cout << "ScoreScaled    :" << university.ScoreScaled << std::endl;
		std::cout << std::endl;
	}
}