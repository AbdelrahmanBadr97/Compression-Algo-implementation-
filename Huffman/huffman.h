#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <vector>
#include <iostream>
#include<bitset>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
// Define the tree node struct here ...
struct Node {
	unsigned char val;
	Node* left=NULL;
	Node* right=NULL;
	long double prob;

  // ...
};

// Define a symbol struct here to hold the symbol (grayscale value)
// and its probability/frequency
struct Symbol {
  // Grayscale value of the symbol
  unsigned char val;
  double pro;
  // ...
};

class Huffman {
public:
  // Constructor and destructor

  // A function to compute the entropy of the input message and
  // stores the probabilities of the different symbols in
  // the input array.
  float compute_entropy(const vector<unsigned char>& msg,
                        vector<Symbol>* prob);
  
  // A function to build the Huffman tree given the computed
  // symbol probabilities.
  void build_tree(const vector<Symbol>& prob);
  
  // A function to print the code table computed from the build_tree above.
  void print_code_table();
  
  // A function to encode the input message using the computed tree 
  // and store the output in the output array, where each entry
  // corresponds to the codeword for an input symbol in the message.
  //
  // The function should return the number of bits in the encoded 
  // message.
  int encode(const vector<unsigned char>& msg,vector<unsigned int>* encoded_msg);
  
  void tableCode( Node* x, string Code);
 
private:
  // Data members here ... for example to store the tree and the codeword 
  // hash table
  Node* tree;
  vector<pair<unsigned char,string>> Alphabet;
  // ...
};

#endif