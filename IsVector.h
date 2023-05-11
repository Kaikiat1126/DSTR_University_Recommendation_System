#pragma once

#include <string>

// self implement a vector class
template <class T>
class IsVector
{
private:
	T* arr;
	int capacity;
	int size;
public:
	IsVector();
	IsVector(int capacity);
	~IsVector();
	void push_back(T element);
	void pop_back();
	void insert(int index, T element);
	void erase(int index);
	void clear();
	int getSize();
	T at(int index);
	bool empty();
};

template <class T>
IsVector<T>::IsVector()
{
	arr = new T[10];
	capacity = 10;
	size = 0;
}

template <class T>
IsVector<T>::IsVector(int capacity)
{
	arr = new T[capacity];
	this->capacity = capacity;
	size = 0;
}

template <class T>
IsVector<T>::~IsVector()
{
	delete[] arr;
}

template <class T>
void IsVector<T>::push_back(T element)
{
	if (size == capacity)
	{
		T* temp = new T[capacity * 2];
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
		capacity *= 2;
	}
	arr[size] = element;
	size++;
}

template <class T>
void IsVector<T>::pop_back()
{
	if (size > 0)
	{
		size--;
	}
}

template <class T>
void IsVector<T>::insert(int index, T element)
{
	if (index < 0 || index > size)
	{
		return;
	}
	if (size == capacity)
	{
		T* temp = new T[capacity * 2];
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
		capacity *= 2;
	}
	for (int i = size; i > index; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[index] = element;
	size++;
}

template <class T>
void IsVector<T>::erase(int index)
{
	if (index < 0 || index >= size)
	{
		return;
	}
	for (int i = index; i < size - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	size--;
}

template <class T>
void IsVector<T>::clear()
{
	size = 0;
}

template <class T>
int IsVector<T>::getSize()
{
	return size;
}

template <class T>
T IsVector<T>::at(int index)
{
	if (index < 0 || index >= size)
	{
		return T();
	}
	return arr[index];
}

template <class T>
bool IsVector<T>::empty()
{
	return size == 0;
}