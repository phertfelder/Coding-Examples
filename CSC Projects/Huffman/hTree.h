/***************************************************************************//**
@file
@brief <DESCRIPTION>
*******************************************************************************/

#ifndef __HTREE_H
#define __HTREE_H

#include "utilities.h"

#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <unordered_map>
#include <stack>
#include <string>
#include <cstdint>

using namespace std;

const int ChunkSize = 1024;

struct Node
{
   int data;
   int freq;
   Node* left;
   Node* right;
};

//comparison class
struct Compare
{

    bool operator()(Node *left, Node *right)
    {
        return left->freq > right->freq;
    }
};

//decoding function prototypes
void organizeHuffman(ifstream &fin, ofstream &fout, vector<histo> &histoItems, string decode);
void traverseTree_Codes(Node *root, vector<histo> &histoItems, string s);
void beginEncodeTree(ifstream &fin, ofstream &fout);
void HuffmanFreq(ifstream &fin, ofstream &fout);
Node *createNode(char d, int frequency, Node*l, Node*r);
int huffDecodeFrequency(ifstream &fin, ofstream &fout);
void beginDecodeTree(ifstream &fin, ofstream &fout, Node *root,int item);
char* binaryconversion(unsigned char c);
int count();



#endif
