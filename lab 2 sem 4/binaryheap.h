#pragma once
#ifndef BINARYTREEH
#define BINARYTREEH

#include <iostream>

#include "iterator.h"
#include "stack.h"
#include "huffmanalgorithm.h"

bool operator < (const HuffmanNode& node1, const HuffmanNode& node2)
{
	return node1.count < node2.count;
}

bool operator > (const HuffmanNode& node1, const HuffmanNode& node2)
{
	return node1.count > node2.count;
}

bool operator == (const HuffmanNode& node1, const HuffmanNode& node2)
{
	return node1.count == node2.count;
}

template <class T>
class BinaryHeap
{
private:
	class ElemList
	{
	public:
		friend class BinaryHeap;
		friend class HeapIterator;

		ElemList* parent;
		ElemList* left;
		ElemList* right;

		T data;

		ElemList(T data)
		{
			this->left = NULL;
			this->right = NULL;
			this->parent = NULL;
			this->data = data;
		}
	};



	void Heapify(ElemList* node)
	{
		if (node->parent == NULL)
		{
			siftDown(node);
		}
		else
			if (node->data < node->parent->data)
			{
				//cout << "PROC1" << endl;
				siftUp(node);
			}
			else
			{
				//cout << "PROC2" << endl;
				siftDown(node);
			}
	}

	void siftDown(ElemList* node)
	{
		if (node->left == NULL && node->right == NULL)
		{
			return;
		}

		ElemList* maxNode = node; //node to swap with

		if (node->right == NULL)  //Means LEFT is not NULL
		{
			if (node->data > node->left->data)
			{
				maxNode = node->left;
			}
			else
			{
				return;
			}
		}

		if (node->left != NULL && node->right != NULL)
		{
			if (node->data > node->right->data || node->data > node->left->data)
			{
				if (node->left->data < node->right->data)
				{
					maxNode = node->left;
				}
				else
				{
					maxNode = node->right;
				}
			}
			else
			{
				return;
			}
		}

		T temp = node->data;
		node->data = maxNode->data;
		maxNode->data = temp;
		siftDown(maxNode);

	}

	void siftUp(ElemList* node)
	{
		if (node->parent == NULL)
		{
			return;
		}
		else
		{
			if (node->data < node->parent->data)
			{
				T temp = node->data;
				node->data = node->parent->data;
				node->parent->data = temp;
				siftUp(node->parent);
			}
			else
			{
				return;
			}
		}
	}

	ElemList* findParentOfLast(int lastLineSize)
	{
		ElemList* parentNode = root;

		int tempLastLineSize = lastLineSize;
		int tempLastLineNodesCount = lastLineNodesCount;

		if (lastLineNodesCount > lastLineSize)
		{
			tempLastLineSize *= 2;
		}

		while (tempLastLineSize != 2)
		{
			if (tempLastLineNodesCount <= tempLastLineSize / 2)
			{
				parentNode = parentNode->left;
				tempLastLineSize /= 2;
			}
			else
			{
				parentNode = parentNode->right;
				tempLastLineNodesCount = tempLastLineNodesCount - tempLastLineSize / 2;
				tempLastLineSize /= 2;
			}
		}

		return parentNode;
	}
public:
	ElemList* root;
	int lastLineNodesCount;

	int height;

	BinaryHeap()
	{
		root = NULL;
		height = 0;
		lastLineNodesCount = 0;
	}

	~BinaryHeap()
	{
		Iterator<ElemList*>* newiterator = create_iterator();
		while (newiterator->has_next())
		{
			ElemList* next = newiterator->next();
			delete next;
		}
		delete newiterator;
	}

	bool empty()
	{
		return root == NULL;
	}

	void insert(T data)
	{
		ElemList* newNode = new ElemList(data);

		if (root == NULL)
		{
			root = newNode;
			height = 1;
			lastLineNodesCount = 1;


		}
		else
		{
			ElemList* parentNode = root;

			int lastLineSize = 1;

			for (int i = 0; i < height - 1; i++) //Counting last line MAX size
			{
				lastLineSize *= 2;
			}

			lastLineNodesCount++;
			if (lastLineNodesCount > lastLineSize)
			{
				height++;
				lastLineNodesCount = 1;
				lastLineSize *= 2;
			}

			parentNode = findParentOfLast(lastLineSize);

			if (parentNode->left == NULL)
			{
				parentNode->left = newNode;
				newNode->parent = parentNode;
			}
			else
			{
				parentNode->right = newNode;
				newNode->parent = parentNode;
			}



			Heapify(newNode);

			return;
		}
	}

	ElemList* findNode(T data)
	{
		auto newiterator = create_iterator();
		while (newiterator->has_next())
		{
			ElemList* next = newiterator->next();
			if (next->data == data)
			{
				delete newiterator;
				return next;
			}
		}
		delete newiterator;
		throw invalid_argument("Element not found!");
	}

	void remove(T data)
	{
		ElemList* nodeToRemove = findNode(data);

		if (height == 1)
		{
			delete root;
			root = NULL;
			height = 0;
			lastLineNodesCount = 0;
			return;
		}

		int lastLineSize = 1;

		for (int i = 0; i < height - 1; i++) //Counting last line MAX size
		{
			lastLineSize *= 2;
		}

		ElemList* lastNode = findParentOfLast(lastLineSize);

		if (lastNode->right != NULL) //Cut last node from tree
		{
			lastNode = lastNode->right;
			lastNode->parent->right = NULL;
		}
		else
		{
			lastNode = lastNode->left;
			lastNode->parent->left = NULL;
		}

		lastLineNodesCount--; //height change
		if (lastLineNodesCount == 0)
		{
			height--;
			lastLineNodesCount = 1;
			for (int i = 0; i < height - 1; i++)
			{
				lastLineNodesCount *= 2;
			}
		}

		if (lastNode == nodeToRemove)
		{
			delete lastNode;
		}
		else
		{
			T temp = lastNode->data;
			lastNode->data = nodeToRemove->data;
			nodeToRemove->data = temp;

			delete lastNode;

			Heapify(nodeToRemove);
		}
	}

	T getRoot()
	{
		return root->data;
	}

	T pop()
	{
		T temp = getRoot();
		remove(temp);
		return temp;
	}

	void printHeap()
	{
		Iterator<ElemList*>* newiterator = create_iterator();
		while (newiterator->has_next())
		{
			cout << "Node: ";
			ElemList* next = newiterator->next();
			cout << next->data << endl;
		}
	}


	class HeapIterator : public Iterator<ElemList*>
	{
	public:
		friend class BinaryHeap;

		HeapIterator(ElemList* root)
		{
			cur = root;
			stack = new Stack<ElemList*>();
		}

		~HeapIterator()
		{
			delete stack;
		}

		bool has_next()
		{
			return cur != NULL;
		}

		ElemList* next()
		{
			if (!has_next())
			{
				throw out_of_range("No more elements");
			}

			ElemList* temp = cur;



			if (cur->right != NULL)
			{
				stack->push(cur->right);
			}

			if (cur->left != NULL)
			{
				cur = cur->left;
			}
			else
			{
				if (!stack->empty())
				{
					cur = stack->top();
					stack->pop();
				}
				else
				{
					cur = NULL;
				}
			}

			return temp;
		}
	private:
		Stack<ElemList*>* stack;

		ElemList* cur;
	};

	HeapIterator* create_iterator()
	{
		return new HeapIterator(root);
	}
};

#endif