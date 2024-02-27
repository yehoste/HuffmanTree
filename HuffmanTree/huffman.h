#pragma once
#include <iostream>
#include <string>
using namespace std;

class HuffmanTree
{
	class HuffmanNode
	{
	public:
		string str;
		int frequency;
		HuffmanNode* left;
		HuffmanNode* right;
		friend class comapreNode;
	};

	class compareNode
	{
	public:
		bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2)
		{
			return n1->frequency > n2->frequency;
		}
	};



public:
	void build(string word);
	void print_tree(HuffmanNode stam);
	void print_struct(HuffmanNode stam);
	void print_b_tree(HuffmanNode stam, char letter, int* list1, int length, int count);
	void decode(string encoded_text, char* letters, string encoded_text1, int l_length);
	void decode2(HuffmanNode* ptr, string encoded_structure, int& i, char* letters, int& j);
	HuffmanNode* head;
};