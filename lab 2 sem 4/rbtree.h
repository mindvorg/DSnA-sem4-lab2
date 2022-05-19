#pragma once
#ifndef RBTREE_H
#define RBTREE_H

#include "stack.h"
#include "iterator.h"
#include "list.h"
#include "pair.h"

using namespace std;

template <class T1, class T2>
class RBTree
{
private:
	enum class color { RED = 0, BLACK = 1 };
	class ElemList
	{
	private:
		ElemList* parent;
		ElemList* left;
		ElemList* right;

		T1* key;
		T2 data;

		color color;
	public:
		friend class RBTree;

		friend class RBTreeIterator;


		ElemList(const T1& key, const T2& data) : ElemList()
		{
			this->key = new T1[1];
			*this->key = key;
			this->data = data;
		}

		ElemList()
		{
			left = NULL;
			right = NULL;
			parent = NULL;
			key = NULL;
			color = color::RED;
		}

		~ElemList()
		{
			if (key != NULL)
				delete[] key;
		}
	};

	ElemList* root;

	ElemList* Nil;
public:
	RBTree()
	{
		Nil = new ElemList();
		Nil->color = color::BLACK;
		root = NULL;
	}

	void LeftSwitch(ElemList* X)
	{
		ElemList* Y = X->right;

		ElemList* B = Y->left;

		X->right = B;

		if (B != Nil)
		{
			B->parent = X;
		}

		ElemList* P = X->parent;
		Y->parent = P;

		if (P == NULL)
		{
			this->root = Y;
		}
		else if (X == P->left)
		{
			P->left = Y;
		}
		else
		{
			P->right = Y;
		}

		Y->left = X;
		X->parent = Y;
	}

	void RightSwitch(ElemList* X)
	{
		ElemList* Y = X->left;

		ElemList* B = Y->right;

		X->left = B;

		if (B != Nil)
		{
			B->parent = X;
		}

		ElemList* P = X->parent;
		Y->parent = P;

		if (P == NULL)
		{
			this->root = Y;
		}
		else if (X == P->right)
		{
			P->right = Y;
		}
		else
		{
			P->left = Y;
		}

		Y->right = X;
		X->parent = Y;
	}

	ElemList* ParentNodeToInsert(T1 key)
	{
		ElemList* currNode = root;

		if (key == *currNode->key)
		{
			return Nil;
		}


		while (true)
		{
			if (key > *currNode->key)
			{
				if (currNode->right != Nil)
				{
					if (*currNode->right->key == key)
						return currNode;
					currNode = currNode->right;
				}
				else
					return currNode;
			}
			else
			{
				if (currNode->left != Nil)
				{
					if (*currNode->left->key == key)
						return currNode;
					currNode = currNode->left;
				}
				else return currNode;
			}
		}
	}

	void Add(const T1& key, const T2& data)
	{
		if (root == NULL)
		{
			ElemList* newNode = new ElemList(key, data);

			root = newNode;
			root->color = color::BLACK;

			newNode->left = Nil;
			newNode->right = Nil;
		}
		else
		{
			ElemList* parentNode = ParentNodeToInsert(key);

			if (parentNode == Nil)
			{
				root->data += data;
				return;
			}


			if (parentNode->left != Nil && *parentNode->left->key == key)
			{
				parentNode->left->data += data;
				return;

			}
			else if (parentNode->right != Nil && *parentNode->right->key == key)
			{
				parentNode->right->data += data;
				return;
			}

			ElemList* newNode = new ElemList(key, data);

			if (key < *parentNode->key)
				parentNode->left = newNode;
			else
				parentNode->right = newNode;

			newNode->parent = parentNode;
			newNode->left = Nil;
			newNode->right = Nil;

			newNode->color = color::RED;

			FixInsert(newNode);
		}
	}



	void Insert(const T1& key, const T2& data)
	{
		if (root == NULL)
		{
			ElemList* newNode = new ElemList(key, data);

			root = newNode;
			root->color = color::BLACK;

			newNode->left = Nil;
			newNode->right = Nil;
		}
		else
		{
			ElemList* parentNode = ParentNodeToInsert(key);

			if (parentNode == Nil)
			{
				throw invalid_argument("Key already exists");
			}

			if (parentNode->left != Nil && *parentNode->left->key == key)
			{
				throw invalid_argument("Key already exists");

			}
			else if (parentNode->right != Nil && *parentNode->right->key == key)
			{
				throw invalid_argument("Key already exists");
			}

			ElemList* newNode = new ElemList(key, data);

			if (key < *parentNode->key)
				parentNode->left = newNode;
			else
				parentNode->right = newNode;

			newNode->parent = parentNode;
			newNode->left = Nil;
			newNode->right = Nil;

			newNode->color = color::RED;

			FixInsert(newNode);
		}
	}

	void FixInsert(ElemList* newNode)
	{
		while (newNode->parent->color == color::RED)
		{
			ElemList* p = newNode->parent;
			ElemList* Gp = p->parent;

			if (p == Gp->left)
			{
				// Case I
				if (Gp->right->color == color::RED)
				{
					Gp->left->color = color::BLACK;
					Gp->right->color = color::BLACK;
					Gp->color = color::RED;
				}
				else // Case II
				{
					if (newNode == p->right)
					{
						newNode = p;
						LeftSwitch(newNode);
						p = newNode->parent;
						Gp = p->parent;
					}
					// Case III
					p->color = color::BLACK;
					Gp->color = color::RED;
					RightSwitch(Gp);
				}
			}
			else
			{
				// Case I
				if (Gp->left->color == color::RED)
				{
					Gp->left->color = color::BLACK;
					Gp->right->color = color::BLACK;
					Gp->color = color::RED;
					newNode = Gp;
				}
				else // Case II
				{
					if (newNode == p->left)
					{
						newNode = p;
						RightSwitch(newNode);
						p = newNode->parent;
						Gp = p->parent;
					}

					// Case III
					p->color = color::BLACK;
					Gp->color = color::RED;
					LeftSwitch(Gp);
				}
			}

			if (newNode == root)
				break;
		}
		// Case IV
		root->color = color::BLACK;
	}

	void Delete(const T1& key)
	{
		ElemList* nodeToDelete = FindNode(key);

		if (nodeToDelete != Nil)
		{
			color originalColor = nodeToDelete->color;

			ElemList* X = NULL;

			if (nodeToDelete->left == Nil)
			{
				X = nodeToDelete->right;
				NodeTransplant(nodeToDelete, X);
			}
			else if (nodeToDelete->right == Nil)
			{
				X = nodeToDelete->left;
				NodeTransplant(nodeToDelete, X);
			}
			else
			{
				ElemList* Y = FindMinimum(nodeToDelete->right);

				originalColor = Y->color;
				X = Y->right;

				if (Y->parent == nodeToDelete)
				{
					X->parent = Y;
				}
				else
				{
					NodeTransplant(Y, Y->right);
					Y->right = nodeToDelete->right;
					Y->right->parent = Y;
				}

				NodeTransplant(nodeToDelete, Y);

				Y->color = originalColor;
				Y->left = nodeToDelete->left;
				Y->left->parent = Y;
				Y->color = nodeToDelete->color;
			}

			delete nodeToDelete;

			if (originalColor == color::BLACK)
			{
				FixDelete(X);
			}
		}
		else
		{
			throw invalid_argument("Node does not exist.");
		}
	}

	void FixDelete(ElemList* X)
	{
		ElemList* W;
		while (X != root && X->color == color::BLACK)
		{
			if (X == X->parent->left)
			{
				W = X->parent->right;
				if (W->color == color::RED)
				{
					W->color = color::BLACK;
					X->parent->color = color::RED;
					LeftSwitch(X->parent);
					W = X->parent->right;
				}

				if (W->left->color == color::BLACK && W->right->color == color::BLACK)
				{
					W->color = color::RED;
					X = X->parent;
				}
				else
				{
					if (W->right->color == color::BLACK) {
						W->left->color = color::BLACK;
						W->color = color::RED;
						RightSwitch(W);
						W = X->parent->right;
					}

					W->color = X->parent->color;
					X->parent->color = color::BLACK;
					W->right->color = color::BLACK;
					LeftSwitch(X->parent);
					X = this->root;
				}
			}
			else
			{
				W = X->parent->left;
				if (W->color == color::RED) {
					W->color = color::BLACK;
					X->parent->color = color::RED;
					RightSwitch(X->parent);
					W = X->parent->left;
				}

				if (W->left->color == color::BLACK && W->right->color == color::BLACK)
				{
					W->color = color::RED;
					X = X->parent;
				}
				else
				{
					if (W->left->color == color::BLACK)
					{
						W->right->color = color::BLACK;
						W->color = color::RED;
						LeftSwitch(W);
						W = X->parent->left;
					}

					W->color = X->parent->color;
					X->parent->color = color::BLACK;
					W->left->color = color::BLACK;
					RightSwitch(X->parent);
					X = this->root;
				}
			}
		}
		X->color = color::BLACK;
	}

	ElemList* FindNode(const T1& key)
	{
		ElemList* currNode = root;

		while (currNode != Nil)
		{
			if (*currNode->key == key)
				return currNode;

			if (*currNode->key < key)
			{
				currNode = currNode->right;
			}
			else if (*currNode->key > key)
			{
				currNode = currNode->left;
			}
		}
		return Nil;
	}

	void NodeTransplant(ElemList* X, ElemList* Y)
	{
		if (X->parent == NULL)
		{
			root = Y;
		}
		else if (X == X->parent->left)
		{
			X->parent->left = Y;
		}
		else
		{
			X->parent->right = Y;
		}
		Y->parent = X->parent;
	}

	ElemList* FindMinimum(ElemList* node)
	{
		while (node->left != Nil)
		{
			node = node->left;
		}
		return node;
	}

	T2 FindData(const T1& key)
	{
		ElemList* node = FindNode(key);
		if (node == Nil)
		{
			throw invalid_argument("Node does not exist.");
		}
		else
		{
			return node->data;
		}
	}

	T1 GetKey(ElemList* node)
	{
		return *node->key;
	}

	T2 GetData(ElemList* node)
	{
		return node->data;
	}

	~RBTree()
	{
		auto itr = create_iterator();

		while (itr->has_next())
		{
			ElemList* temp = itr->cur;
			itr->next();
			delete temp;
		}
		delete itr;

		delete Nil;
	}

	class RBTreeIterator : public Iterator<Pair<T1, T2>>
	{
	public:
		friend class RBTree;

		Stack<ElemList*>* stack;

		ElemList* cur;

		RBTreeIterator(ElemList* root)
		{
			cur = root;
			stack = new Stack<ElemList*>();
		}

		~RBTreeIterator()
		{
			delete stack;
		}

		bool has_next()
		{
			return cur != NULL;
		}

		Pair<T1, T2> next()
		{
			ElemList* temp = cur;

			Pair<T1, T2> pair = makepair(*temp->key, temp->data);

			if (cur->right->key != NULL)
			{
				stack->push(cur->right);
			}

			if (cur->left->key != NULL)
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

			return pair;
		}

	};

	RBTreeIterator* create_iterator()
	{
		return new RBTreeIterator(root);
	}

};

#endif