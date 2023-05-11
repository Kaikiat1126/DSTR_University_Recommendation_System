#pragma once
#include <iostream>
#include <string>
#include "Structure.h"
#include "Timer.h"


class BTree
{
protected:
	
public:
	BTree();
	~BTree();
	virtual void traversal();
	virtual void preOrder();
	virtual void postOrder();
	virtual void insertValueInBTree(DataStruct data);
};

BTree::BTree()
{
}

BTree::~BTree() {}

void BTree::traversal()
{
}

void BTree::preOrder()
{
}

void BTree::postOrder()
{
}

void BTree::insertValueInBTree(DataStruct data)
{
}