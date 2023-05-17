#include "Structure.h"
#include "StatusContainer.h"
#include <iostream>
#include <string>

class MergeSort
{
private:
	static UniversityNode* split(UniversityNode*);
	static UniversityNode* merge(UniversityNode*, UniversityNode*);
public:
	static UniversityNode* mergeSort(UniversityNode*);
};

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

	if (first->university.institution < second->university.institution)
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

UniversityNode* MergeSort::mergeSort(UniversityNode* head)
{
	if (!head || !head->next)
		return head;
	UniversityNode* second = split(head);

	// Recur the left and right halves
	head = mergeSort(head);
	second = mergeSort(second);

	// Merge the two sorted halves
	return merge(head, second);
}
