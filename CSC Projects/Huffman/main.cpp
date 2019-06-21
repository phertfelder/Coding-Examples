/***************************************************************************//**
 * @file main.cpp
 * @mainpage CSC 315 - Fall 2018
 *
 * @brief Main function for project 1 - Huffman Coding
 *
 * @section course_section Course Information
 *
 * @authors Ben Sjoberg, Paul Hertfelder
 * 
 * @date Oct. 4, 2018
 * 
 * @par Professor: Dr. Qiao
 *
 * @par Course: CSC 315 - Section 1 - Fall 2018
 *
 * @section program_section Program Description
 *
 * @par Description
 *   <DESCRIPTION>
 *
 * @section compile_section Compile Section
 *s
 * @par Build
   @verbatim
% make
   @endverbatim
 * @par Run
 * @verbatim
% ./paint
   @endverbatim
 * @par Usage
 *
 *    This program takes a file in and is decided on what the user would like
 *    for encoding a file into huffman code for compression or to decode a huffman
 *    coded file. This program can only decode files it has previously encocded.
 *    
 *    colors along the left side of the paint window.
 *  * Fill color is chosen by clicking with the right mouse on the palette 
 *    colors along the left side of the paint window.
 *  * The shape tool is selected using the left or right mouse button on the 
 *    shape tools in the upper left corner of the paint window.
 *  * Etc.
 *
 * @section todo_bugs_modification_section To Do, Bugs, and Modifications
 *   Bugs: At certain times the program has had difficulty saving to the encode file.
 *   This is due to the user having that file open but it has happened when the file
 *   was not open. This will cause a crash of the program since it presumes data will
 *   always be entered. 2. Large files as in MBs have been previously crashing the program.
 *   3. An issue that is fixed now when decoding from characters to a binary string leading
 *   0's would be added to the front of a small binary number. This should be fixed but
 *   decoding may add characters that were not previously in that order may not be present.
 *   4. Issues when only one of each character is present.
 *
 * @par Revision History
 * <a href="https://gitlab.mcs.sdsmt.edu/7415734/csc315_fall2018_project1/commits/master">git commit history</a>
 *
 *****************************************************************************/

#include "utilities.h"
#include "hTree.h"

using namespace std;

/***************************************************************************//**
 * @brief Main function for the Huffman Coding program
 ******************************************************************************/
int main(/*int argc, char *argv[]*/)
{
    ifstream fin;
    ofstream fout;
    string inFile;
    string outFile;
    string codeType;
    vector<histo> histoItems;
    codeType = "-d";
    outFile = "example";
    inFile = "converted";
    
    
 /*codeType = "-e";

    outFile = "converted";
    inFile = "testtext";*/
    //check for proper arguments
    /*if(argc != 4)
    {
        cout << "Usage: " << argv[0] << "-[de] inputfile outputfile\n";
        return -1;
    }
    codeType = argv[1];
    inFile = argv[2];
    outFile = argv[3];*/
    fin.open(inFile, ios::binary | ios::in);
    if(!fin)
    {
        cout << "Input file could not be opened\n";
        return -1;
    }
    if(codeType != "-d" && codeType != "-e")
    {
       // cout << "Usage: " << argv[0] << "-[de] inputfile outputfile\n";
        return -1;
    }
    fout.open(outFile, ios::binary | ios::out | ios::trunc);
    //encode
    if(codeType == "-e")
    {
    //pass 1:
        //open input file
        //determine frequency distribution of symbols (build histogram)
        //write histogram to beginning of output (encoded) files
        //build Huffman coding tree from histogram
        //generate Huffman code table from coding tree
    //pass 2:
        //reposition input file pointer to start of input file
        //repeat:
            //read chunk (1024 bytes) of input file into input buffer (example file on webpage)
            //for each byte in input buffer:
                //encode byte using Huffman code table
                //store encoded value in output buffer, using binary operators
                //when output buffer is full, write buffer to output (encoded) file
    //standard output (statistics)
         
        HuffmanFreq(fin, fout);
        organizeHuffman(fin, fout, histoItems, "-e");
        beginEncodeTree(fin, fout);
        
        //##########TESTING##########
        cout << "\nSIZE OF HISTO: " << histoItems.size() << "\n\n";
        for(int i = 0; i < histoItems.size(); i++)
        {
            cout << "HISTO CHAR: " << histoItems[i].asciiCode << "\n";
            cout << "HISTO CODE: " << histoItems[i].code << "\n";
            cout << "HISTO times repeated: " << histoItems[i].timesRepeated << "\n\n";
        }
    }
    //decode
    else
    {fin.seekg(0, fin.end);
         int length = fin.tellg();
         fin.clear();
         fin.seekg(0, fin.beg);
         int i= huffDecodeFrequency(fin, fout);

         organizeHuffman(fin, fout, histoItems, "-d");

    //read in histogram
    //build Huffman coding tree from histogram
    //repeat:
        //read chunk of input (encoded) into input buffer
        //while encoded bits remain in input buffer
            //for each encoded byte in input buffer
                //decode bits using Huffman code tree
                //when leaf node hit, store devoded symbol in ouput buffer
                //when output buffer is full, write buffer to output (decoded) file
    //standard output (statistics)
    }
    
    
    fin.close();
    fout.close();
    return 0;
}
