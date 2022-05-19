#pragma once
#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
	class ElemList
	{
	public:
		ElemList(T node, ElemList* prev)
		{
			this->node = node;
			this->prev = prev;
		}

		ElemList(T node) : ElemList(node, NULL) {}

		T node;
		ElemList* prev;
	};

	ElemList* head;
public:
	Stack()
	{
		head = NULL;
	}

	~Stack()
	{
		while (!empty())
		{
			pop();
		}
	}

	void pop()
	{
		if (empty())
		{
			throw out_of_range("No more elements");
		}
		else
		{
			ElemList* temp = head;
			head = head->prev;
			delete temp;
		}
	}

	void push(T node)
	{
		ElemList* newNode = new ElemList(node, head);
		head = newNode;
	}

	bool empty()
	{
		return head == NULL;
	}

	T top()
	{
		if (empty())
		{
			throw out_of_range("Empty");
		}
		else
		{
			return head->node;
		}
	}
};

#endif