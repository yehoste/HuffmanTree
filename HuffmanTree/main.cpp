/**
 * @file main.cpp
 * @brief Huffman coding algorithm implementation for text encoding and decoding
 */

#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <cmath>
#include "huffman.h"
using namespace std;

/**
 * @brief Main function to execute Huffman coding algorithm for text encoding and decoding
 * @return 0 upon successful execution
 */
int main() {
    char choice; // Variable to store user's choice
    string word; // Variable to store original text input
    int* list2; // Array to store binary representation of characters
    string encoded_text; // Variable to store encoded text
    int enc, s = 0; // Variables for encryption
    char* letters; // Array to store characters
    string encoded_text1; // Variable to store encoded text structure
    int n; // Variable to store number of characters

    // Create a new Huffman tree instance
    HuffmanTree* t = new HuffmanTree();

    // Prompt user for choice
    cout << "Enter E to encode a text\n";
    cout << "Enter D to decode a text\n";
    cout << "Enter X to exit\n";

    // Main menu loop
    do {
        cin >> choice; // Read user's choice
        switch (choice) {
            case 'E': // Encode a text
                cout << "Enter the original text" << endl;
                cout << "The encoded string is" << endl;
                cin >> word; // Read original text
                cout << "Encryption parameters: " << endl;
                // Build Huffman tree and print its structure
                t->build(word);
                t->print_tree(*t->head);
                cout << endl;
                t->print_struct(*t->head);
                cout << endl;
                // Initialize list2 array and print binary representation of each character
                list2 = new int[2 * word.length() - 1];
                for (int j = 0; j < 2 * word.length() - 1; j++) {
                    list2[j] = -1;
                }
                for (int i = 0; i < word.length(); i++) {
                    t->print_b_tree(*t->head, word[i], list2, word.length(), 0);
                    for (int j = 0; j < 2 * word.length() - 1; j++) {
                        list2[j] = -1;
                    }
                }
                cout << endl;
                cout << endl;
                break;
            case 'D': // Decode an encoded text
                cout << "Enter n: ";
                cin >> n; // Read the number of characters
                cout << endl << "Enter the letters: ";
                letters = new char[n];
                // Read the characters
                for (int i = 0; i < n; i++) {
                    cin >> letters[i];
                }
                cout << endl << "Enter the encoded structure: ";
                cin >> encoded_text; // Read the encoded text structure
                cout << endl << "Enter the encoded text: ";
                cin >> encoded_text1; // Read the encoded text
                cout << endl;
                int num_of_1 = 0, first_1 = 0;
                // Count the number of '1's in the encoded text
                for (;; num_of_1++) {
                    if (encoded_text1[num_of_1] == NULL) {
                        break;
                    }
                }
                // Find the position of the first '1' in the encoded text structure
                for (int i = 0;; i++) {
                    if (encoded_text[i] == '1') {
                        break;
                    }
                    first_1++;
                }
                // Check if the number of '1's in the encoded text is less than the position of the first '1' in the encoded text structure
                if (num_of_1 < first_1) {
                    cout << "ERROR" << endl;
                    break;
                }
                cout << "The decoded string is: ";
                // Decode the encoded text
                t->decode(encoded_text, letters, encoded_text1, n);
                cout << endl;
                break;
        }
        // Prompt user for choice again
        cout << "Enter E to encode a text\n";
        cout << "Enter D to decode a text\n";
        cout << "Enter X to exit\n";
    } while (choice != 'X'); // Continue loop until user chooses to exit
    cout << "bye" << endl;
    return 0;
}
