#pragma once
#include "Structure.h"
#include "StatusContainer.h"
#include <iostream>
#include <string>

class QuickSort
{
private:
    static void swap(UniversityStruct*, UniversityStruct*);
    static UniversityNode* partition(UniversityNode*, UniversityNode*);
    static void _quickSort(UniversityNode*, UniversityNode*);
public:
    static void quickSort(UniversityNode*, UniversityNode*, std::string);
};

std::string sortBy;

void QuickSort::swap(UniversityStruct* a, UniversityStruct* b)
{
    UniversityStruct temp = *a;
    *a = *b;
    *b = temp;
};

 //sortBy: "institution", "ar_score", "fsr_score", "er_score"
UniversityNode* QuickSort::partition(UniversityNode* head, UniversityNode* last)
{
    //set pivot as last element
    UniversityStruct pivot = last->university;

    UniversityNode* i = head->prev;

    for (UniversityNode* j = head; j != last; j = j->next)
    {
        if (sortBy == "institution")
        {
            if (j->university.institution <= pivot.institution)
            {
                i = (i == NULL) ? head : i->next;

                swap(&(i->university), &(j->university));
            }
        }
        else if (sortBy == "ar_score")
        {
            if (j->university.ArScore <= pivot.ArScore)
            {
                i = (i == NULL) ? head : i->next;

                swap(&(i->university), &(j->university));
            }
        }
        else if (sortBy == "fsr_score")
        {
            if (j->university.FsrScore <= pivot.FsrScore)
            {
                i = (i == NULL) ? head : i->next;

                swap(&(i->university), &(j->university));
            }
        }
        else if (sortBy == "er_score")
        {
            if (j->university.ErScore <= pivot.ErScore)
            {
                i = (i == NULL) ? head : i->next;

                swap(&(i->university), &(j->university));
            }
        }

        
    }
    i = (i == NULL) ? head : i->next;
    /*if (i == NULL) {
        i = head;
    }
    else {
        i = i->next;
    }*/

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

void QuickSort::quickSort(UniversityNode* head, UniversityNode* tail, std::string type)
{
    sortBy = type;
    //Call the recursive QuickSort
    _quickSort(head, tail);
};