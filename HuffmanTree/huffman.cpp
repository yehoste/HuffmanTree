#include "huffman.h"
#include <queue>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;


/**
 * @brief Function to count occurrences of a specific character in a string
 * @param stam The character to count occurrences of
 * @param word The string to search for occurrences in
 * @return The count of occurrences of the character in the string
 */
int check_how_many_t(char stam, string word) {
	int i = 0, amount = 0;
	for (; i < word.length(); i++) {
		if (word[i] == stam) {
			amount++;
		}
	}
	return amount;
}

/**
 * @brief Function to count the number of unique characters in a string
 * @param list1 Pointer to a character array containing the unique characters
 * @param word The string to search for unique characters in
 * @return The number of unique characters in the string
 */
int amount_of_chf(char* list1, string word) {
	int amount = 0;
	for (int i = 0; list1[i] != NULL && i < word.size(); i++) {
		amount++;
	}
	return amount;
}

/**
 * @brief Function to create a list of unique characters from a string
 * @param word The string to extract unique characters from
 * @return A pointer to a dynamically allocated character array containing unique characters
 */
char* list_of_dif_char(string word) {
	int num = 0;
	bool check = true;
	char* list1 = new char[word.size()];
	for (int i = 0; i < word.size(); i++) {
		list1[i] = NULL;
	}
	list1[0] = word[0];
	for (int i = 1; i < word.size(); i++) {
		check = true;
		for (int j = 0; j < i; j++) {
			if (word[i] == word[j]) {
				check = false;
				break;
			}
		}
		if (check) {
			num++;
			list1[num] = word[i];
		}
	}
	return list1;
}

/**
 * @brief Function to build the Huffman tree
 * @param word The string to generate the Huffman tree from
 */
void HuffmanTree::build(string word) {
	// Create a list of unique characters
	char* list1 = list_of_dif_char(word);
	// Calculate the number of unique characters
	int amount_of_ch = amount_of_chf(list1, word);
    // print amount of special chars
    cout << amount_of_ch << endl;
    // Priority queue to store nodes of the Huffman tree
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, compareNode> pQueue;
	// Create nodes for each unique character and push them to the priority queue
	HuffmanNode* list2 = new HuffmanNode[amount_of_ch];
	for (int i = 0; i < amount_of_ch; i++) {
		list2[i].str = list1[i];
		list2[i].frequency = check_how_many_t(list1[i], word);
		pQueue.push(&list2[i]);
	}
	// Build the Huffman tree from the priority queue
	// Continue until only one node is left in the priority queue
	HuffmanNode* list3 = new HuffmanNode[amount_of_ch - 1];
	HuffmanNode* HuffmanNode1, * HuffmanNode2;
	for (int i = 0; i < amount_of_ch - 1; i++) {
		// Extract two nodes with the lowest frequency from the priority queue
		HuffmanNode1 = pQueue.top();
		pQueue.pop();
		HuffmanNode2 = pQueue.top();
		pQueue.push(HuffmanNode1);
		// Combine the two nodes to create a new internal node
		list3[i].frequency = HuffmanNode1->frequency + HuffmanNode2->frequency;
		// Check if the two nodes have equal frequency and non-empty strings
		if (HuffmanNode1->frequency == HuffmanNode2->frequency && HuffmanNode1->str != "" && HuffmanNode2->str != "") {
			// Assign children to the new internal node
			list3[i].right = pQueue.top();
			pQueue.pop();
			list3[i].left = pQueue.top();
			pQueue.pop();
			pQueue.push(&list3[i]);
		}
		else {
			// Assign children to the new internal node
			list3[i].left = pQueue.top();
			pQueue.pop();
			list3[i].right = pQueue.top();
			pQueue.pop();
			pQueue.push(&list3[i]);
		}
	}
	// Assign the root of the Huffman tree
	this->head = &list3[amount_of_ch - 2];
}

/**
 * @brief Function to print the Huffman tree
 * @param stam The root node of the Huffman tree
 */
void HuffmanTree::print_tree(HuffmanNode stam) {
    // If the node is not a leaf node, recursively print its left and right subtrees
    if (stam.str == "") {
        print_tree(*stam.left);
    }
    // Print the character stored in the node
    cout << stam.str;
    // If the node is not a leaf node, recursively print its left and right subtrees
    if (stam.str == "") {
        print_tree(*stam.right);
    }
}

/**
 * @brief Function to print the Huffman tree structure
 * @param stam The root node of the Huffman tree
 */
void HuffmanTree::print_struct(HuffmanNode stam) {
    // If the node is not a leaf node, recursively print '0' and traverse its left subtree
    if (stam.str == "") {
        cout << '0';
        print_struct(*stam.left);
    }
    // If the node is not a leaf node, recursively traverse its right subtree
    if (stam.str == "") {
        print_struct(*stam.right);
    }
    // If the node is a leaf node, print '1'
    else
        cout << '1';
    return;
}

/**
 * @brief Function to print the binary representation of a character in the Huffman tree
 * @param stam The root node of the Huffman tree
 * @param letter The character to find in the tree
 * @param list1 Array representing the binary path to the character
 * @param length Length of the binary path array
 * @param count Current position in the binary path array
 */
void HuffmanTree::print_b_tree(HuffmanNode stam, char letter, int* list1, int length, int count) {
    // Get the first character of the node's string
    char see_bug = stam.str[0];
    // If the character matches the desired character, print the binary path
    if (see_bug == letter) {
        for (int i = 0; list1[i] == 1 || list1[i] == 0; i++) {
            cout << list1[i];
        }
    }
    // If the node is not a leaf node, traverse its left subtree
    if (stam.str == "") {
        for (int i = 0; ; i++) {
            // Mark the end of the path
            if (list1[i] != 0 && list1[i] != 1) {
                list1[i] = 0;
                break;
            }
        }
        print_b_tree(*stam.left, letter, list1, length, count + 1);
    }
    // Reset the path after traversing the left subtree
    for (int j = count; j < length; j++) {
        list1[j] = -1;
    }
    // If the node is not a leaf node, traverse its right subtree
    if (stam.str == "") {
        for (int i = 0; ; i++) {
            // Mark the end of the path
            if (list1[i] != 0 && list1[i] != 1) {
                list1[i] = 1;
                break;
            }
        }
        print_b_tree(*stam.right, letter, list1, length, count + 1);
    }
    return;
}

/**
 * @brief Recursive helper function to decode the encoded text structure and build the Huffman tree
 * @param ptr Pointer to the current node in the Huffman tree
 * @param structure The encoded text structure
 * @param i Current position in the encoded text structure
 * @param letters The characters represented in the tree
 * @param j Current position in the characters array
 */
void HuffmanTree::decode2(HuffmanNode* ptr, string structure, int& i, char* letters, int& j) {
    // If the structure represents a character, assign the character to the current node
    if (structure[i] == '1') {
        ptr->str = letters[j];
        j++;
        return;
    }
    // If the structure represents an internal node, create left and right children and recursively decode
    ptr->left = new HuffmanNode;
    ptr->right = new HuffmanNode;
    decode2(ptr->left, structure, ++i, letters, j);
    decode2(ptr->right, structure, ++i, letters, j);
}

/**
 * @brief Function to decode the encoded text using the Huffman tree
 * @param encoded_text The encoded text to decode
 * @param letters The characters represented in the tree
 * @param encoded_text1 The encoded text structure
 * @param l_length Length of the encoded text structure
 */
void HuffmanTree::decode(string encoded_text, char* letters, string encoded_text1, int l_length) {
    int stam = 0;
    int count = 0;
    HuffmanNode stam1;
    head = &stam1;
    // Decode the encoded text structure and build the Huffman tree
    this->decode2(&stam1, encoded_text, stam, letters, count);
    HuffmanNode stam5 = *this->head;
    for (int i = 0; encoded_text1[i] != NULL; i++) {
        // Traverse the Huffman tree using the encoded text and print the decoded characters
        if (stam5.str != "") {
            cout << stam5.str;
            stam5 = *this->head;
        }
        if (encoded_text1[i] == '0') {
            stam5 = *stam5.left;
        }
        if (encoded_text1[i] == '1') {
            stam5 = *stam5.right;
        }
    }
    cout << endl;
}



