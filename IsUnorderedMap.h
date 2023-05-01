#pragma once

#include <string>

template <typename KeyType, typename ValueType, size_t Capacity>
class IsUnorderedMap
{
private:
	struct Slot
	{
		KeyType key;
		ValueType value;
		bool used = false;
		Slot* next;
		Slot(KeyType key, ValueType value)
		{
			this->key = key;
			this->value = value;
			next = NULL;
		}
	};

	Slot* table[Capacity];
	int size;
public:
	IsUnorderedMap();
	~IsUnorderedMap();
	int hash(KeyType key);
	void insert(KeyType key, ValueType value);
	void remove(KeyType key);
	ValueType getValue(KeyType key);
	ValueType getValue(int index);
	KeyType getKey(ValueType value);
	KeyType getKey(int index);
	bool empty();
	int getSize();
	void clear();
	void print();
};

template <typename KeyType, typename ValueType, size_t Capacity>
IsUnorderedMap<KeyType, ValueType, Capacity>::IsUnorderedMap()
{
	size = 0;
	for (int i = 0; i < Capacity; i++)
	{
		table[i] = NULL;
	}
}

template <typename KeyType, typename ValueType, size_t Capacity>
IsUnorderedMap<KeyType, ValueType, Capacity>::~IsUnorderedMap()
{
	for (int i = 0; i < Capacity; i++)
	{
		if (table[i] != NULL)
		{
			Slot* current = table[i];
			while (current != NULL)
			{
				Slot* temp = current;
				current = current->next;
				delete temp;
			}
		}
	}
}

template <typename KeyType, typename ValueType, size_t Capacity>
int IsUnorderedMap<KeyType, ValueType, Capacity>::hash(KeyType key)
{
	std::hash<KeyType> hash;
	return hash(key) % Capacity;
}

template <typename KeyType, typename ValueType, size_t Capacity>
void IsUnorderedMap<KeyType, ValueType, Capacity>::insert(KeyType key, ValueType value)
{
	int index = hash(key);
	if (table[index] == NULL)
	{
		table[index] = new Slot(key, value);
	}
	else
	{
		Slot* current = table[index];
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new Slot(key, value);
	}
	size++;
}

template <typename KeyType, typename ValueType, size_t Capacity>
void IsUnorderedMap<KeyType, ValueType, Capacity>::remove(KeyType key)
{
	int index = hash(key);
	if (table[index] != NULL)
	{
		Slot* current = table[index];
		Slot* previous = NULL;
		while (current != NULL)
		{
			if (current->key == key)
			{
				if (previous == NULL)
				{
					table[index] = current->next;
				}
				else
				{
					previous->next = current->next;
				}
				delete current;
				size--;
				return;
			}
			previous = current;
			current = current->next;
		}
	}
}

template <typename KeyType, typename ValueType, size_t Capacity>
ValueType IsUnorderedMap<KeyType, ValueType, Capacity>::getValue(KeyType key)
{
	int index = hash(key);
	if (table[index] != NULL)
	{
		Slot* current = table[index];
		while (current != NULL)
		{
			if (current->key == key)
			{
				return current->value;
			}
			current = current->next;
		}
	}
	return ValueType();
}

template <typename KeyType, typename ValueType, size_t Capacity>
ValueType IsUnorderedMap<KeyType, ValueType, Capacity>::getValue(int index)
{
	if (index >= 0 && index < size)
	{
		int count = 0;
		for (int i = 0; i < Capacity; i++)
		{
			if (table[i] != NULL)
			{
				Slot* current = table[i];
				while (current != NULL)
				{
					if (count == index)
					{
						return current->value;
					}
					current = current->next;
					count++;
				}
			}
		}
	}
	return ValueType();
}

template <typename KeyType, typename ValueType, size_t Capacity>
KeyType IsUnorderedMap<KeyType, ValueType, Capacity>::getKey(ValueType value)
{
	for (int i = 0; i < Capacity; i++)
	{
		if (table[i] != NULL)
		{
			Slot* current = table[i];
			while (current != NULL)
			{
				if (current->value == value)
				{
					return current->key;
				}
				current = current->next;
			}
		}
	}
	return KeyType();
}

template <typename KeyType, typename ValueType, size_t Capacity>
KeyType IsUnorderedMap<KeyType, ValueType, Capacity>::getKey(int index)
{
	if (index >= 0 && index < size)
	{
		int count = 0;
		for (int i = 0; i < Capacity; i++)
		{
			if (table[i] != NULL)
			{
				Slot* current = table[i];
				while (current != NULL)
				{
					if (count == index)
					{
						return current->key;
					}
					current = current->next;
					count++;
				}
			}
		}
	}
	return KeyType();
}

template <typename KeyType, typename ValueType, size_t Capacity>
bool IsUnorderedMap<KeyType, ValueType, Capacity>::empty()
{
	return size == 0;
}

template <typename KeyType, typename ValueType, size_t Capacity>
int IsUnorderedMap<KeyType, ValueType, Capacity>::getSize()
{
	return size;
}

template <typename KeyType, typename ValueType, size_t Capacity>
void IsUnorderedMap<KeyType, ValueType, Capacity>::clear()
{
	for (int i = 0; i < Capacity; i++)
	{
		if (table[i] != NULL)
		{
			Slot* current = table[i];
			while (current != NULL)
			{
				Slot* temp = current;
				current = current->next;
				delete temp;
			}
		}
	}
	size = 0;
}

template <typename KeyType, typename ValueType, size_t Capacity>
void IsUnorderedMap<KeyType, ValueType, Capacity>::print()
{
	for (int i = 0; i < Capacity; i++)
	{
		if (table[i] != NULL)
		{
			Slot* current = table[i];
			while (current != NULL)
			{
				std::cout << current->key << " " << current->value << std::endl;
				current = current->next;
			}
		}
	}
}