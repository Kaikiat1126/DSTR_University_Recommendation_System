#pragma once

#include <string>

//self implement a hashmap class
// TODOs: redo

template <typename K, typename V>
class IsHashMap
{
private:
	struct Node
	{
		K key;
		V value;
		Node* next;
		Node(K key, V value)
		{
			this->key = key;
			this->value = value;
			next = NULL;
		}
	};
	Node** table;
	int capacity;
	int size;
public:
	IsHashMap();
	IsHashMap(int capacity);
	~IsHashMap();
	int hash(K key);
	void insert(K key, V value);
	void remove(K key);
	V getValue(K key);
	V getValue(int index);
	K getKey(V value);
	K getKey(int index);
	bool empty();
	int getSize();
};

template <typename K, typename V>
IsHashMap<K, V>::IsHashMap()
{
	capacity = 100;
	size = 0;
	table = new Node * [capacity];
	for (int i = 0; i < capacity; i++)
	{
		table[i] = NULL;
	}
}

template <typename K, typename V>
IsHashMap<K, V>::IsHashMap(int capacity)
{
	this->capacity = capacity;
	size = 0;
	table = new Node * [capacity];
	for (int i = 0; i < capacity; i++)
	{
		table[i] = NULL;
	}
}

template <typename K, typename V>
IsHashMap<K, V>::~IsHashMap()
{
	for (int i = 0; i < capacity; i++)
	{
		Node* temp = table[i];
		while (temp != NULL)
		{
			Node* next = temp->next;
			delete temp;
			temp = next;
		}
	}
	delete[] table;
}

template <typename K, typename V>
int IsHashMap<K, V>::hash(K key)
{
	int hashcode = 0;
	for (int i = 0; i < key.length(); i++)
	{
		hashcode += key[i];
	}
	return hashcode % capacity;
}

template <typename K, typename V>
void IsHashMap<K, V>::insert(K key, V value)
{
	int index = hash(key);
	Node* temp = table[index];
	while (temp != NULL)
	{
		if (temp->key == key)
		{
			temp->value = value;
			return;
		}
		temp = temp->next;
	}
	Node* newNode = new Node(key, value);
	newNode->next = table[index];
	table[index] = newNode;
	size++;
}

template <typename K, typename V>
void IsHashMap<K, V>::remove(K key)
{
	int index = hash(key);
	if (table[index] != NULL)
	{
		Node* temp = table[index];
		Node* prev = NULL;
		while (temp != NULL && temp->key != key)
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
		{
			return;
		}
		else
		{
			if (prev == NULL)
			{
				table[index] = temp->next;
			}
			else
			{
				prev->next = temp->next;
			}
			delete temp;
			size--;
		}
	}
}

template <typename K, typename V>
V IsHashMap<K, V>::getValue(K key)
{
	int index = hash(key);
	if (table[index] != NULL)
	{
		Node* temp = table[index];
		while (temp != NULL && temp->key != key)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			return NULL;
		}
		else
		{
			return temp->value;
		}
	}
	else
	{
		return NULL;
	}
}

template <typename K, typename V>
V IsHashMap<K, V>::getValue(int index)
{
	if (index < 0 || index >= capacity)
	{
		return NULL;
	}
	else
	{
		Node* temp = table[index];
		while (temp != NULL)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			return NULL;
		}
		else
		{
			return temp->value;
		}
	}
}

template <typename K, typename V>
K IsHashMap<K, V>::getKey(V value)
{
	for (int i = 0; i < capacity; i++)
	{
		Node* temp = table[i];
		while (temp != NULL)
		{
			if (temp->value == value)
			{
				return temp->key;
			}
			temp = temp->next;
		}
	}
	return NULL;
}

template <typename K, typename V>
K IsHashMap<K, V>::getKey(int index)
{
	if (index < 0 || index >= capacity)
	{
		return NULL;
	}
	else
	{
		Node* temp = table[index];
		while (temp != NULL)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			return NULL;
		}
		else
		{
			return temp->key;
		}
	}
}

template <typename K, typename V>
bool IsHashMap<K, V>::empty()
{
	return size == 0;
}

template <typename K, typename V>
int IsHashMap<K, V>::getSize()
{
	return size;
}