/***************************************************************************//**
@file
@brief <DESCRIPTION>
*******************************************************************************/

#include "hTree.h"
//#include "utilities.h"

/***************************************************************************//**
@author <AUTHOR>

@par Description:
<DESCRIPTION>

@param[in] <VAR> - <DESCRIPTION>
*******************************************************************************/
//function definitions


/*Notes: decoding takes in binary tree:
  Example: root
          /    \     if 0 take left if 1 take right
         A      B    
        / \    / 
       C  D    E            to get to D binary code would be 01

struct Node
{
   int data;
   Node* left;
   Node* right;
}

Notes: 1. take in buffer 1024 bytes as unsigned char is each one byte in size.
2. Find amount of certain char frequency. store these in a heap
3. compare these frequencies to build tree
Need to hold these values
*/
//Frequency instead of building everything in one function.

//From www.cplusplus.com
//Unordered maps implement the direct access operator
//(operator[]) which allows for direct access of the mapped value using its key value as argument.
//map<int,unsigned char> frequency;
//so mapped value would be the amount of the byte.
//maps chapter 4.
unordered_map<signed char, int> frequency;
unordered_map<signed char, int>::iterator it1;
map <signed char, string> huffcode;
map <signed char, string>::iterator it;
map <string, char> decHuff;
//map <unsigned char, string> huffcode;
// with codes and character.
//create output buffer
// store the 1s&0s till buffer is full
//output buffer
/*
string s = "10101010";
uint8_t byte = strtoul(s.c_str(), NULL, 2);
myfile << byte;
*/

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function outputs the huffman code to the output file.
 * It reads in the full character and compares it to the character
 * stored in huffman code. This function then creates a long string
 of 0's and 1's of the fully encoded bits. These bits are then converted
 * to the actual binary representation by CHAR_SIZE which is 8 bits are 
 * converted then stored into the output file. Once completed the
 function returns. 
* @param[in]      &fin - input file
* @param[in]      &fout - output file

*****************************************************************************/
void beginEncodeTree(ifstream &fin, ofstream &fout)
{
    fin.seekg(0, fin.end);
    int length = fin.tellg();
    fin.clear();
    fin.seekg(0, fin.beg);
    int byte;
    cout << "Encoding" << endl;
    string bits = "";
    unsigned char buffer[ChunkSize];
    unsigned char character;
    fin.read((char *)buffer, ChunkSize);
    unsigned char b;
    int nbytes = 0;
    int remaining = 0;
    string remainder = "";
    int i;
    int j;
    int k;

//Issues: Need to add a buffer to print to characters. Currently doing only one byte at a time. 
// if 
   
//going to read in bytes compare this unsigned char to the huffcode
    while (fin.gcount() > 1)
    {
        // keep track of how many bytes we've read
        nbytes += fin.gcount();
        //This is probably slow but I am not sure how else to do it.
        
        for (i = 0; i <length; i++)
        {

            //compare byte to saved code.
            character = buffer[i];

            it = huffcode.find(character);
            //saved as a string
            bits.append(it->second);

            if (bits.size() > 8)
            {
                //clear remainder
                remainder.clear();
                remaining = bits.size() - 8;
                //add the bits
                remainder.append(bits, 8, remaining);
                //erase the bits that went to remainder.
                bits.erase(8, remaining);
            }
            if (bits.size() == 8)
            {
                uint_fast8_t byte = strtoul(bits.c_str(), NULL, 2);
                fout << byte;
                cout << bits;
                bits.clear();
            }
            bits.append(remainder);
            remainder.clear();

        }
        
        remainder.clear();
        fin.read((char *)buffer, ChunkSize);

    }
    if (bits.size() < 8)
    {
         uint_fast8_t byte = strtoul(bits.c_str(), NULL, 2);
         fout << byte;
         cout << bits;
         bits.clear();
    }
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function creates a new node for aid in building all known 
 * needed nodes to form the future huffman tree. 


*
* @param[in]      d - character being stored in node
* @param[in]      frequency - frequency of character
* @param[in]        *l - left address
* @param[in]       * r - right address
*                 
* 
*
*
* @returns node - returns the created node to the function that called it. 
* 
* 
*
*****************************************************************************/
Node *createNode(char d, int frequency, Node*l, Node*r)
{
    Node *node = new (nothrow)Node();
    node->left = l;
    node->right = r;
    node->freq = frequency;
    node->data = d;

    return node;

}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function is to find the frequency of characters in the file that needs
 * to be encoded it takes a large chunksize of characters and each byte
 * is then compared to already known chracters or added in and frequency
 * is added by +1. This is then saved to an unordered map as it allows using
 * (operatior[]) to have direct access to the mapped value using its key as
 * the argument. 


*
* @param[in]      &fin - input file
* @param[in]      &fout - output file
* 
*                 
* 
*
*
* 
* 
* 
*
*****************************************************************************/
void HuffmanFreq(ifstream &fin, ofstream &fout)
{
    fin.seekg(0, fin.end);
    int length = fin.tellg();
    fin.seekg(0, fin.beg);
    int nbytes = 0;
    int sumHufftree = 0;
    int i = 0;
    //int j = 0;
    unsigned char buffer[ChunkSize];
    fin.read((char *)buffer, ChunkSize);
    //reading 1024 bytes
    // add to map to store this buffer/frequency
    //Need to save this in the unordered map 
    //we have in buffer possibly 1024 bytes so lets read each byte and count them up
    // Then we keep looping till the end of file.
    //This could probably go into its own function.
    cout << "made it to freq" << endl;
    //mymap.size() gives size of unordered_map.

    while (fin.gcount() > 0)
    {
        // keep track of how many bytes we've read
        nbytes += fin.gcount();

        //This is probably slow but I am not sure how else to do it. 
        for (i = 0; i < nbytes; i++)
        {
            //stores in frequency unordered_map
            frequency[buffer[i]]++;

        }
        
        fin.read((char *)buffer, ChunkSize);
        
    }
    fin.clear();
    fin.seekg(0, ios::beg);
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function organizes the frequency for placement into nodes. These nodes
 * are then combined to form a huffman tree. The root of this tree is then
 * sent to finding the huffman codes which are then saved for easy access. 
 * If decoding is chosen the function sends the root of this newly formed
 * huffman tree to the decoding process if not it returns. 


*
* @param[in]      &fin - input file
* @param[in]      &fout - output file
* @param[in]      &histoItems - histogram items
* @param[in]      decode - decode string
*                 
* 
*
*
* 
* 
* 
*
*****************************************************************************/

void organizeHuffman(ifstream &fin, ofstream &fout, vector<histo> &histoItems,string decode)
{
    //From lecture use a priority queue. priority queue 
    //Priority_queue template:
    //<class T, class Container>
    int sumHufftree = 0;
    Node *root = new Node;
    //create tons of nodes.
    //C+11 auto iterator.
    //priority queue <Class T,vector<Node*> contains vector of nodes.
    //use auto to organize by priority chapter 6.
    //uint_fast8_t byte = strtoul(bits.c_str(), NULL, 2);
    priority_queue<Node*, vector <Node*>, Compare>priorityQ;
    for (auto it : frequency)
    {
         if (decode == "-e")
         {
              fout << it.first;
              sumHufftree = it.second;
              fout.write(reinterpret_cast<const char *>(&sumHufftree),sizeof(short));
         }
        priorityQ.push(createNode(it.first, it.second, nullptr, nullptr));
    }

    if (decode == "-e")
    {
        fout << '\n';  
    }
   
    // create a left node create a right node
    // 
    while (priorityQ.size() != 1)
    {   Node* ll = priorityQ.top();
        priorityQ.pop();

        Node *rr = priorityQ.top();
        priorityQ.pop();
        sumHufftree = ll->freq + rr->freq;
        // top node stores NULL data, stores all frequencies
        priorityQ.push(createNode('\0', sumHufftree, ll, rr));
    }
    root = priorityQ.top();
    //Tree is built.
    // Now traverse tree to build huffman codes.
    //store the amount
    //store the original character
    int item = 0;
    string s = "";
    //need to add the -d -e.
    traverseTree_Codes(root, histoItems, s);
    item = count();
    if (decode == "-d")
    {
         beginDecodeTree(fin, fout, root,item);

    }
    //now we need to actually encode.
}
//void traverseTree_Codes(ifstream &fin, ofstream &fout, Node *root, stack<int>&amount, stack<unsigned char>&original, string s,stack <string>st);
//We need the file
// our root data is NULL so we need the root node.
//(Hint: use a stack to store the current
//code as you traverse the tree.)

// can use string of 0&1 characters but need to be converted to bits.

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function takes in the huffman tree rot and begins to assign the huff
 * code to the characters. If left add a 0 to the string if right add a 1.
 * Continue t his till we have reached nullptr. Recursion is used
 * to go through huffman tree. 


*
* @param[in]      *root - root of huffman tree
* @param[in]      &histoitems - histogram items
* @param[in]      s - the strings of 1's and 0's
* @param[in]      decode - decode string
*                 
* 
*
*
* 
* 
* 
*
*****************************************************************************/
void traverseTree_Codes(Node *root, vector<histo> &histoItems, string s)
{
     
    if (root == nullptr)
    {
        //cout << " Created leaves " << endl;
        
        //cout << " Code: " << s << endl;

         return;
    }
    if (root->data != '\0')
    {
        //cout << root->data << " " << s;
        //histoItems.push_back({root->data, s, root->freq});
        /*item = root->data;
        item = root->freq*s.size();*/

        huffcode[root->data] = s;
    }
    // go right 

    //go left

    traverseTree_Codes(root->left, histoItems, s + "0");
    traverseTree_Codes(root->right, histoItems, s + "1");
    // left is 0 and right is 1

}

//So reading in the encoded file
// All are int representations of the character and frequency.
// 2 bytes for every int.


/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function is to find where the character '\n' is in the first part of
 * file. This function is gathering the histogram items as in char and freq.
 * Example: A2B5'\n'
 * character '\n' appears at position 4 in buffer. 
 *


*
* @param[in]      &fin - input file
* @param[in]      &fout - output file
*                 
* 
*
*
* @returns i - character count for '\n'
* 
* 
*
*****************************************************************************/
int huffDecodeFrequency(ifstream &fin,ofstream &fout)
{

     fin.seekg(0, fin.end);
     int length = fin.tellg();
     fin.clear();
     fin.seekg(0, fin.beg);
     int remainder = 0;
     int nbytes = 0;
     int sumHufftree = 0;
     int i = 0;
     //int j = 0;
     int character = 0;
     int number = 0;
     unsigned char buffer[ChunkSize];
     fin.read((char *)buffer, ChunkSize);

     //reading 1024 bytes
     // add to map to store this buffer/frequency
     //Need to save this in the unordered map 
     //we have in buffer possibly 1024 bytes so lets read each byte and count them up
     // Then we keep looping till the end of file.
     //This could probably go into its own function.
     //mymap.size() gives size of unordered_map.
     //uint_fast8_t byte = strtoul(bits.c_str(), NULL, 2);
     while (fin.gcount() > 0)
     {
          // keep track of how many bytes we've read
          nbytes += fin.gcount();

          //This is probably slow but I am not sure how else to do it. 
          for (i = 0; i < nbytes;i++)
          {
               //found new line 
               if (buffer[i] == '\n')
               {
                    return i;
               }
               
               // add to the frequency map until 
               character = buffer[i];
              // character = character << 4;
              // character = character | buffer[i + 1];
               number = buffer[i + 1];
               
               
              // number = number | buffer[];

                    //stores in frequency unordered_map
               frequency.insert({ character, number });
               i = i + 2;
          }
          fin.read((char *)buffer, ChunkSize);

     }
    
     
     fin.clear();


}


//tree is made. 
// go through tree 
//get the length of the file
// find where histogram ends.
// start decoding at end of histogram.
// begin decoding first take a byte of the data 
//Making a giant string of binary numbers
// go through every number 

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function decodes and outputs the original characters of the encoded
 * file. This function takes in the infile and out file the root of the 
 * huffman tree and the actual amount of bits that were written as
 * encoded file. The actual bits are compared to the new string that is made
 * from encoded file. So if original string of bits would be 256 bits and
 * 258 bits are made 2 of these bits are leading 0s added from conversion
 * from char to binary representation these are then deleted. To get the
 * actual bits used in encoding. 


*
* @param[in]      &fin - input file
* @param[in]      &fout - output file
* @param[in]      *root- root of hufftree
* @param[in]      item - how many actual bits are in the encoded huff code. 
*                 
* 
*
*
* 
* 
* 
*
*****************************************************************************/
void beginDecodeTree(ifstream &fin, ofstream &fout, Node *root,int item)
{
     fin.clear();

     Node*current=new Node;
     fin.seekg(0, ios::beg);

     fin.seekg(0, fin.end);
     int length = fin.tellg();
    
     fin.clear();
     fin.seekg(0, fin.beg);
     int byte;
     int count=0;
     char convert[9];
     convert[8];
     cout << "decoding" << endl;
     string bits = "";
     unsigned char buffer[ChunkSize];
     unsigned char character;
     fin.read((char *)buffer, ChunkSize);
     unsigned char b;
     int nbytes = 0;
     int remaining = 0;
     string remainder = "";
     int i;
     
     int k;
     current = root;
     //Issues: Need to add a buffer to print to characters. Currently doing only one byte at a time. 
     // if 
     //find the byte of new line.
     while (fin.gcount() > 0&& buffer[count]!='\n')
     {
          // keep track of how many bytes we've read
          nbytes += fin.gcount();

          //This is probably slow but I am not sure how else to do it.
          while(count<nbytes&&buffer[count]!='\n')
          {
               count++;
               
          }
          fin.read((char *)buffer, ChunkSize);

     }
     fin.clear();
     fin.seekg(count+1, ios::beg);
     fin.read((char *)buffer, ChunkSize);
     nbytes = 0;

     //going to read in bytes compare this unsigned char to the huffcode
     while (fin.gcount() > 1)
     {
          // keep track of how many bytes we've read
          nbytes += fin.gcount();
          //This is probably slow but I am not sure how else to do it.
          // convert to an int convert int to binary
          for (i = 0; i < nbytes; i++)
          {

               //create a string of 1's and 0's
               if (i < nbytes)

               {
                    /*if (i == nbytes - 1)
                    {
                         remaining = buffer[i];
                         remainder = binaryconversion(buffer[i]);
                         remainder.erase(0,1);
                    }
                    else*/
                    //{
                         remaining = buffer[i];
                         remainder = binaryconversion(buffer[i]);
                    //}
               }

               
               
               

                    bits.append(remainder);

                    remainder.clear();

              
              

          }

          fin.read((char *)buffer, ChunkSize);
         
     }

     if (bits.size() > item)
     {
          i =  bits.length()-item;
          bits.erase(bits.size()-8, i);
     }
     cout<<bits.size()<<endl;
    item=bits.length();
    // int z = bits.length();
     //
     //convert is a large string of "1" and "0"s
     // go through the string.
     for (i = 0; i < item; i++)
     {


          if (bits.at(i) == '0')
          {
	       
              current = current->left;
          }
          //right

          /*if (bits[i] == '1')
          {
               current = current->right;
          }
          if (current->left ==nullptr&&current->right == nullptr)
          {
               
               cout << "cchar : " << current->data << endl;;

                    b = current->data;
                    fout << b;
                    current = root;*/
              
          }
          //left
          
     
     
     

}
// send over character
// convert to binary.
//need to get the total bits.
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function counts how many actual bits were stored in encoded file.
 * Example if char A Frequency 3 00
 *            char B Frequency 4 10 
 * The return value would be 3*2+4*2 which is returned as an int=14
 * This is to aid in the decoding process since converting char to bits
 * resulted in leading 0s that were added this aids in the deletion of them. 
*
*                 
* 
*
*
* @ returns multiplier- the actual amount of bits used in encoding. 
* 
* 
*
*****************************************************************************/
int count()
{
     char character;
     int sum=0;
     int multiplier=0;
     string s;
     for (auto it1 : frequency)
     {

          character = it1.first;
          sum = it1.second;
          it = huffcode.find(character);
          s = it->second;
          multiplier = multiplier+sum * s.size();
     }
     return multiplier;
               
          
     
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function converts a character to its 8 bit representation. 
 * This function takes place of char *  itoa ( int value, char * str, int base );
 * as itoa only certain compilers are able to do as it is not standard in the
 * C++ libraries.


*
* @param[in]      character- the character being converted to binary form. 
*
*                 
* 
*
*@returns binary- the resulting binary form of character. 
* 
* 
* 
*
*****************************************************************************/
char* binaryconversion(unsigned char character)
{
     
     int i;
     static char binary[8];
     for (i = 7; i>=0; i--)
     {
          binary[i] = (character % 2) + '0';
          character /= 2;
     }

     return binary;
}


// Maybe
/*void decodingHuffman(struct Node *root, ifstream &fin, ofstream &fout)
{
     unsigned char *byte;
    // Store the string of characters 
     string answer ="";
     int nbits=0;
    // store size of file. In bytes taken from binfile.cpp in assignments. 
     int nbytes = 0;
    byte=new(nothrow) unsigned char[1];
    fin.read( ( char * ) buffer, ChunkSize );
    while ( fin.gcount() > 0 )
    {
        // keep track of how many bytes we've read
        nbytes += fin.gcount();

        // read next input chunk
        fin.read( ( char * ) buffer, ChunkSize );
    }
    fin.clear();
    
     fin.seekg(0,ios::beg);
     //
     for(int i=0; i<nbytes;i++)
     {    fin.seekg(i,ios::beg);
         fin.read((char*)byte,1);
         // go right

          if (byte=='1')
          {
               current=current->right;
          }

         // go left
          if (byte=='0')
         // hit Null.
          if (current->right=NULL && current ->left =NULL)
         {
	      // store it here for right now.
               fout<<current->data;
               current=root;
         }
return;
}*/
