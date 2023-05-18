#pragma once

#include <string>
#include "UniversityList.h"
#include "Structure.h"

class LinearSearch
{
private:
	/*void filterUniversityWithRank(UniversityNode* head, int* rank, UniversityList* list);
	void filterUniversityWithLocation(UniversityNode* head, std::string& value, UniversityList* list);
	void filterUniversityByValue(UniversityNode* head, int* type, int* range, UniversityList* list);
	void deleteNode(UniversityNode* node);*/
	
public:
	LinearSearch();
	~LinearSearch();

	//void filterUniversityByValue(int* type, int* range, std::string* value, UniversityList* list);
};

LinearSearch::LinearSearch()
{
}

LinearSearch::~LinearSearch()
{
}

// type: "0 = rank", "1 = name", "2 = locationCode", "3 = ar score", "4 = fsr score", "5 = er score"
// name need to been remove spaces
// range: "1 = 0-20" , "2 = 21-40", "3 = 41-60", "4 = 61-80", "5 = 81-100"
//UniversityList* LinearSearch::filterUniversityByValue(int* type, int* range, std::string* value, UniversityList* list)
//{
//	std::cout << "Filtering with linear search..." << std::endl;
//	if (*type == 1)
//	{
//		int rank = std::stoi(*value);
//		filterUniversityWithRank(list->head, &rank, list);
//	}
//}