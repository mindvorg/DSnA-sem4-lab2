#include "pch.h"
#include "CppUnitTest.h"
#include"..\lab 2 sem 4\huffmanalgorithm.h"
#include"..\lab 2 sem 4\pair.h"
#include<iostream>
#include<string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		inline string const BoolToString(bool b)
		{
			return b ? "1" : "0";
		}

		TEST_METHOD(HuffmanCode1)
		{
			string quote = "Huffmann doesn't have own quotes";

			Map<char, int> symbolsMap;
			for (char character : quote)
				symbolsMap.Add(character, 1);

			HuffmanTree huffmantree;
			huffmantree = buildHuffmanTree(symbolsMap);
			Map<char, List<bool>*> huffmanCode = CreateHuffmanCode(huffmantree);
			List<bool> encodedLine = EncodeByHuffman(quote, huffmanCode);
			string EncodedString = bitSequanceToString(encodedLine);
			string decodedLine = DecodeByHaffman(encodedLine, huffmantree);
			string ExpectedCode = "00110011010001000010110111110110101111011111000010011011100001010101010011110010000101111110011110101001110110111100100000100";
			Assert::AreEqual(ExpectedCode, EncodedString);//check for code equality
			Assert::AreEqual(quote, decodedLine);//check for decode equality
		}
		TEST_METHOD(HuffmanCode2)
		{
			string quote = "Scientists are sitting in glasses... Not with glasses, but with glasses. And not scientists, but who is."; //bad translated quote of D.N. Butusov 

			Map<char, int> symbolsMap;
			for (char character : quote)
				symbolsMap.Add(character, 1);

			HuffmanTree huffmantree;
			huffmantree = buildHuffmanTree(symbolsMap);
			Map<char, List<bool>*> huffmanCode = CreateHuffmanCode(huffmantree);
			List<bool> encodedLine = EncodeByHuffman(quote, huffmanCode);
			string EncodedString = bitSequanceToString(encodedLine);
			string decodedLine = DecodeByHaffman(encodedLine, huffmantree);
			string ExpectedCode = "01010101010010010100011010000111110011111010110010100010011011100110010000101101010111000101101101010101111101101111110100111000000000000110010101101110100110010110011000001111010101011111011011111101001111011101100001010111110011001011001100000111101010101111101101111110100111000011010100000110101000111001100111010011011110100100101000110100001111100111101110110000101011111001100101100011011101100011110000";
			Assert::AreEqual(ExpectedCode, EncodedString);//check for code equality
			Assert::AreEqual(quote, decodedLine);//check for decode equality
		}
		TEST_METHOD(HuffmanCode3)
		{
			setlocale(LC_ALL, "rus");
			string quote = "Если у вас произошло событие с вероятностью ноль, то вы полный неудачник."; //quote of A.S. Kolpakov

			Map<char, int> symbolsMap;
			for (char character : quote)
				symbolsMap.Add(character, 1);

			HuffmanTree huffmantree;
			huffmantree = buildHuffmanTree(symbolsMap);
			Map<char, List<bool>*> huffmanCode = CreateHuffmanCode(huffmantree);
			List<bool> encodedLine = EncodeByHuffman(quote, huffmanCode);
			string EncodedString = bitSequanceToString(encodedLine);
			string decodedLine = DecodeByHaffman(encodedLine, huffmantree);
			string ExpectedCode = "001000101100010100111011011111101000110101111111000011001000100001001100000000000110011110111000111111101101010100110011111011111110101100101100100001111010110101001011010100001011100111101010000010000101111011101011001111101011011111110001000001101011011001011111101011001011010010100011000000110100100001110011101";
			Assert::AreEqual(ExpectedCode, EncodedString);//check for code equality
			Assert::AreEqual(quote, decodedLine);//check for decode equality
		}
	};
}
