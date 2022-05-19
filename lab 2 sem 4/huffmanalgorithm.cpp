#ifndef HUFFMANALGORITHM_CPP
#define HUFFMANALGORITHM_CPP



#include <iostream>

#include "huffmanalgorithm.h"
#include "binaryheap.h"
#include "pair.h"
#include "list.h"
#include "string"

using namespace std;

inline string const BoolToString(bool b)
{
	return b ? "1" : "0";
}

HuffmanNode::HuffmanNode()
{
	this->symbols = "Err";
	this->count = -1;

	code = false;
	parent = NULL;
	left = NULL;
	right = NULL;
}

HuffmanNode::HuffmanNode(string symbols, int count) : HuffmanNode()
{
	this->symbols = symbols;
	this->count = count;
}

HuffmanTree::HuffmanTree()
{
	root = NULL;
	leafsList = new List<HuffmanNode*>();
}

void PrintCodes(Map<char, List<bool>*>& codesMap)
{
	auto codes_itr = codesMap.create_iterator();

	while (codes_itr->has_next())
	{
		Pair<char, List<bool>*> newPair = codes_itr->next();
		cout << newPair.first << ": ";

		auto list_itr = newPair.second->create_iterator();

		while (list_itr->has_next())
		{
			cout << BoolToString(list_itr->next());
		}

		cout << endl;
	}
}

void PrintFreqency(Map<char, int>& symbolsMap)
{
	auto sym_itr = symbolsMap.create_iterator();

	while (sym_itr->has_next())
	{
		Pair<char, int> newPair = sym_itr->next();
		cout << newPair.first << ": " << newPair.second << endl;
	}
}

string bitSequanceToString(List<bool>& bitLine)
{
	string line;
	auto list_itr = bitLine.create_iterator();
	while (list_itr->has_next())
		line += BoolToString(list_itr->next());
	delete list_itr;
	return line;
}

List<bool> EncodeByHuffman(string line, Map<char, List<bool>*>& haffmanCode)
{
	List<bool>* encodedLine = new List<bool>();

	for (char character : line)
	{
		List<bool>* code = haffmanCode.Find(character);

		auto list_itr = code->create_iterator();
		while (list_itr->has_next())
		{
			encodedLine->push_back(list_itr->next());
		}
	}
	return *encodedLine;
}

string DecodeByHaffman(List<bool>& encodedLine, HuffmanTree& tree)
{
	string decodedLine;
	HuffmanNode* cur = tree.root;

	auto encodedLineBitIterator = encodedLine.create_iterator();
	while (encodedLineBitIterator->has_next())
	{
		bool bit = encodedLineBitIterator->next();

		if (bit) //bit == 1
		{
			cur = cur->left;

			if (cur->left == NULL) // cur is leaf
			{
				decodedLine += cur->symbols;
				cur = tree.root;
			}
			else if (!(encodedLineBitIterator->has_next()))
			{
				throw out_of_range("Appropriate decoding sequance was not found");
			}
		}
		else //bit == 0 
		{
			cur = cur->right;

			if (cur->left == NULL) // cur is leaf
			{
				decodedLine += cur->symbols;
				cur = tree.root;
			}
			else if (!(encodedLineBitIterator->has_next()))
			{
				throw out_of_range("Appropriate decoding sequance was not found");
			}
		}
	}
	return decodedLine;
}

Map<char, List<bool>*> CreateHuffmanCode(HuffmanTree& tree)
{
	auto bufferItr = tree.leafsList->create_iterator();

	Map<char, List<bool>*>* haffcode = new Map<char, List<bool>*>();

	while (bufferItr->has_next())
	{
		HuffmanNode* cur = bufferItr->next();

		List<bool>* symbolCode = new List<bool>();

		char currSymbol = (cur->symbols)[0];

		while (cur->parent != NULL)
		{
			symbolCode->push_front(cur->code);

			cur = cur->parent;
		}

		haffcode->Insert(currSymbol, symbolCode);
	}

	return *haffcode;
}

HuffmanTree buildHuffmanTree(Map<char, int>& symbolsMap)
{
	HuffmanTree* tree = new HuffmanTree();

	BinaryHeap<HuffmanNode>* heap = new BinaryHeap<HuffmanNode>();

	auto itr = symbolsMap.create_iterator();
	while (itr->has_next())
	{
		Pair<char, int> newPair = itr->next();
		HuffmanNode newNode(string(1, newPair.first), newPair.second);
		heap->insert(newNode);
	}

	List<HuffmanNode*>* leafsList = new List<HuffmanNode*>();

	while (heap->height != 1)
	{
		HuffmanNode n1 = heap->pop();
		HuffmanNode n2 = heap->pop();

		HuffmanNode* minNode1 = &n1;
		HuffmanNode* minNode2 = &n2;

		if (minNode1->left == NULL)
		{
			HuffmanNode* realminNode1 = new HuffmanNode(minNode1->symbols, minNode1->count);
			leafsList->push_front(realminNode1);
			minNode1 = realminNode1;
		}
		else
		{
			minNode1 = minNode1->left->parent;
		}

		if (minNode2->left == NULL)
		{
			HuffmanNode* realminNode2 = new HuffmanNode(minNode2->symbols, minNode2->count);
			leafsList->push_front(realminNode2);
			minNode2 = realminNode2;
		}
		else
		{
			minNode2 = minNode2->left->parent;
		}

		string combinedSymbols = minNode1->symbols + minNode2->symbols;
		int combinedCount = minNode1->count + minNode2->count;

		HuffmanNode* newNode = new HuffmanNode(combinedSymbols, combinedCount);
		tree->root = newNode;
		minNode1->code = 0;
		minNode2->code = 1;
		newNode->right = minNode1;
		newNode->left = minNode2;

		minNode1->parent = newNode;
		minNode2->parent = newNode;
		heap->insert(*newNode);
	}

	delete heap;
	tree->leafsList = leafsList;
	return *tree;
}
#endif // !HUFFMANALGORITHM_CPP
