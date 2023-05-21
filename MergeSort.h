#include "Structure.h"
#include "StatusContainer.h"
#include <iostream>
#include <string>

class MergeSort
{
private:
	static int sortBy;
	static UniversityNode* split(UniversityNode*);
	static UniversityNode* merge(UniversityNode*, UniversityNode*);
public:
	static UniversityNode* mergeSort(UniversityNode*, int);
};

int MergeSort::sortBy;

UniversityNode* MergeSort::split(UniversityNode* head)
{
	UniversityNode* fast = head, * slow = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	UniversityNode* temp = slow->next;
	slow->next = NULL;
	return temp;
}

UniversityNode* MergeSort::merge(UniversityNode* first, UniversityNode* second)
{
	if (!first)
		return second;

	if (!second)
		return first;

	auto compare = [&](const UniversityStruct& a, const UniversityStruct& b)
	{
		if (sortBy == 0)
			return a.institution < b.institution;
		else if (sortBy == 1)
			return a.rank < b.rank;
		else if (sortBy == 2)
			return a.ArScore < b.ArScore;
		else if (sortBy == 3)
			return a.FsrScore < b.FsrScore;
		else if (sortBy == 4)
			return a.ErScore < b.ErScore;
		else if (sortBy == 5)
			return a.count < b.count;
		else
			return a.rank < b.rank;
	};

	if (compare(first->university, second->university))
	{
		first->next = merge(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return first;
	}
	else
	{
		second->next = merge(first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return second;
	}
}

// type: "0:institution", "1:rank", "2:ar_score", "3:fsr_score", "4:er_score", "5:count
UniversityNode* MergeSort::mergeSort(UniversityNode* head, int type)
{
	sortBy = type;
	if (!head || !head->next)
		return head;
	UniversityNode* second = split(head);

	// Recur the left and right halves
	head = mergeSort(head, type);
	second = mergeSort(second, type);

	// Merge the two sorted halves
	return merge(head, second);
}
