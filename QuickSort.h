#pragma once
#include "Structure.h"
#include "StatusContainer.h"
#include <iostream>
#include <string>

class QuickSort
{
private:
    static int sortBy;
    static void swap(UniversityStruct*, UniversityStruct*);
    static UniversityNode* partition(UniversityNode*, UniversityNode*);
    static void _quickSort(UniversityNode*, UniversityNode*);
public:
    static void quickSort(UniversityNode*, UniversityNode*, int);
};

int QuickSort::sortBy;

void QuickSort::swap(UniversityStruct* a, UniversityStruct* b)
{
    UniversityStruct temp = *a;
    *a = *b;
    *b = temp;
};

UniversityNode* QuickSort::partition(UniversityNode* head, UniversityNode* last)
{
    //set pivot as last element
    UniversityNode* pivot = last;

    UniversityNode* i = head->prev;

    auto compare = [&](const UniversityStruct& a, const UniversityStruct& b)
    {
        if (sortBy == 0)
            return a.institution < b.institution;
        else if (sortBy == 3)
            return a.ArScore < b.ArScore;
        else if (sortBy == 4)
            return a.FsrScore < b.FsrScore;
        else if (sortBy == 5)
            return a.ErScore < b.ErScore;
        else
            return a.rank < b.rank;
    };

    for (UniversityNode* j = head; j != last; j = j->next)
    {
        if (compare(j->university, pivot->university))
        {
            i = (i == NULL) ? head : i->next;
            swap(&(i->university), &(j->university));
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

void QuickSort::quickSort(UniversityNode* head, UniversityNode* tail, int type)
{
    sortBy = type;
    //Call the recursive QuickSort
    _quickSort(head, tail);
};