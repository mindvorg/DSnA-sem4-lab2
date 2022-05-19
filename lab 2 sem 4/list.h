#pragma once
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "iterator.h"
using namespace std;

template <class T>
class List
{
public:
	T& operator[](const int index);
	class ElemList
	{
	public:
		friend class ListIterator;

		ElemList(T value, ElemList* next, ElemList* prev)
		{
			this->next = next;
			this->prev = prev;
			this->value = value;
		}

		ElemList(T value) : ElemList(value, NULL, NULL) {}

		~ElemList() {};

		ElemList* next;

		ElemList* prev;

		T value;

	};

	ElemList* last;

	int size = 0;

	ElemList* head;

	List()
	{
		head = NULL;
		last = NULL;
	}

	~List()
	{
		while (!isEmpty())
		{
			//cout << "popping " << this->last << endl;
			pop_back();
		}
	}

	void push_back(T elem)
	{
		size++;

		ElemList* newElem = new ElemList(elem, NULL, last);
		if (isEmpty())
		{
			head = newElem;
		}
		else
		{
			last->next = newElem;
		}
		last = newElem;
	}

	void push_front(T elem)
	{
		size++;

		ElemList* newElem = new ElemList(elem, head, NULL);;
		if (isEmpty())
		{
			last = newElem;
		}
		else
		{
			head->prev = newElem;
		}
		head = newElem;
	}

	void pop_back()
	{
		if (isEmpty())
		{
			throw invalid_argument("Nothin to pop");
		}
		else if (head->next == NULL)
		{
			size = 0;
			pop_only();
		}
		else
		{
			size--;
			ElemList* currNode = last->prev;
			delete last;
			last = currNode;
			currNode->next = NULL;
		}
	}

	void pop_front()
	{
		if (isEmpty())
		{
			throw invalid_argument("Nothin to pop");
		}
		else if (head->next == NULL)
		{
			size = 0;
			pop_only();
		}
		else
		{
			size--;
			ElemList* currNode = head->next;
			delete head;
			head = currNode;
			currNode->prev = NULL;
		}
	}

	void clear()
	{
		size = 0;
		this->~List();
		return;
	}

	bool isEmpty()
	{
		return head == NULL;
	}



	class ListIterator : public Iterator<T>
	{

	public:
		friend class List;

		ElemList* cur;

		ListIterator(List<T>* list)
		{
			cur = list->head;
		}

		~ListIterator()
		{
		}

		bool has_next()
		{
			return cur != NULL;
		}

		T next()
		{
			T temp = cur->value;
			cur = cur->next;
			return temp;
		}
	};

	ListIterator* create_iterator()
	{
		ListIterator* iter = new ListIterator(this);
		return iter;
	}
private:
	void pop_only()
	{
		delete head;
		head = NULL;
		last = NULL;
	}

};
template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	ElemList* elem = this->head;
	//ElemList* cur = this->head;
	/*while (elem->next != NULL)
	{
		if (counter == index)
		{
			return elem->data;
		}
	//	cur = cur->next;
		elem=elem->next;
		counter++;t
	}*/
	for (int i = 0; i < index; i++) { elem = elem->next; }
	return elem->data;


}
#endif