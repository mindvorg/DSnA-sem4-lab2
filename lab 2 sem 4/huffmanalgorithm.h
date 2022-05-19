#pragma once
#ifndef HAFFMANALGORITHM_H
#define HAFFMANALGORITHM_H

#include "map.h"



class HuffmanNode
{
public:
	string symbols;
	int count;
	bool code;

	HuffmanNode* parent;
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(string, int);

	HuffmanNode();
};

class HuffmanTree
{
public:
	HuffmanNode* root;

	List<HuffmanNode*>* leafsList;

	HuffmanTree();
};

inline string const BoolToString(bool);

void PrintFreqency(Map<char, int>&);

void PrintCodes(Map<char, List<bool>*>&);

string bitSequanceToString(List<bool>&);

List<bool> EncodeByHuffman(string, Map<char, List<bool>*>&);

string DecodeByHaffman(List<bool>&, HuffmanTree&);

Map<char, List<bool>*> CreateHuffmanCode(HuffmanTree&);

HuffmanTree buildHuffmanTree(Map<char, int>&);
#include"huffmanalgorithm.cpp"
#endif
