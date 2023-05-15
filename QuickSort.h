#pragma once
#include "Structure.h"
#include <iostream>
#include <string>

class QuickSort
{
private:
    void swap(UniversityStruct*, UniversityStruct*);
    UniversityNode* lastNode(UniversityNode*);
    UniversityNode* partition(UniversityNode*, UniversityNode*);
    void _quickSort(UniversityNode*, UniversityNode*);
public:
    void quickSort(UniversityNode*);
    void displayUniversityList(UniversityNode*);
};

void QuickSort::swap(UniversityStruct* a, UniversityStruct* b)
{
    UniversityStruct temp = *a;
    *a = *b;
    *b = temp;
};

UniversityNode* QuickSort::lastNode(UniversityNode* root)
{
    while (root && root->next)
        root = root->next;
    return root;
};

UniversityNode* QuickSort::partition(UniversityNode* head, UniversityNode* last)
{
    //set pivot as last element
    std::string pivot = last->university.institution;

    UniversityNode* i = head->prev;

    for (UniversityNode* j = head; j != last; j->next)
    {
        if (j->university.institution <= pivot)
        {
            i = (i == NULL) ? head : i->next;

            swap(&(i->university), &(last->university));
        }
    }
    i = (i == NULL) ? head : i->next;
    swap(&(i->university), &(last->university));
    return i;
};

void QuickSort::_quickSort(UniversityNode* head, UniversityNode* last)
{
    if (last != NULL && head != last && head != last->next)
    {
        UniversityNode* p = partition(head, last);
        _quickSort(head, p->prev);
        _quickSort(p->next, last);
    }
};

void QuickSort::quickSort(UniversityNode* head)
{
    //Find last node
    UniversityNode* last = lastNode(head);

    //Call the recursive QuickSort
    _quickSort(head, last);
};

void QuickSort::displayUniversityList(UniversityNode* head)
{
    while(head)
    {
        std::cout << head->university.rank << "\t" << head->university.institution << std::endl;
        head = head->next;
    }
}