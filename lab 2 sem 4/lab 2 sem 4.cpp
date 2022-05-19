#include "pair.h"
#include "huffmanalgorithm.h"

#include <string>
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	string quote;
	quote = "it is test string";

	
	cout << quote << ":" << endl;

	Map<char, int> symbolsMap;
	for (char character : quote)
		symbolsMap.Add(character, 1);

	cout << "\nFreqency:" << endl;
	PrintFreqency(symbolsMap);

	HuffmanTree huffmantree;
	huffmantree = buildHuffmanTree(symbolsMap);

	Map<char, List<bool>*> haffmanCode = CreateHuffmanCode(huffmantree);
	cout << "\nCodes:" << endl;
	PrintCodes(haffmanCode);

	List<bool> encodedLine = EncodeByHuffman(quote, haffmanCode);
	cout << "\nEncoded line:" << endl;
	cout << bitSequanceToString(encodedLine);

	try
	{
		string decodedLine = DecodeByHaffman(encodedLine, huffmantree);
		cout << "\n\nDecoded line: " << decodedLine << endl;
	}
	catch (out_of_range& expection)
	{
		cout << expection.what() << endl;
	}

	int sizeBeforeEncode = quote.length() * sizeof(char) * 8;
	int sizeAferEncode = encodedLine.size;

	cout << "Size before encode: " << sizeBeforeEncode << " bits" << endl;
	cout << "Size after encode: " << sizeAferEncode << " bits" << endl;
	cout << "Compression coefficient: " << (sizeAferEncode * 1.0) / (sizeBeforeEncode * 1.0) << endl;

	// Deleting List<bool>* in Map<char, List<bool>*> huffmanCode
	auto itr = haffmanCode.create_iterator();
	while (itr->has_next())
	{
		auto pair = itr->next();
		delete pair.second;
	}
}