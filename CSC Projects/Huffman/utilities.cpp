/***************************************************************************//**
@file
@brief <DESCRIPTION>
*******************************************************************************/

#include "utilities.h"

/***************************************************************************//**
@author <AUTHOR>

@par Description:
<DESCRIPTION>

 @param[in] <VAR> - <DESCRIPTION>
*******************************************************************************/
//function definitions
bool cmpFreqs(const histo &lhs, const histo &rhs)
{
     return lhs.freq > rhs.freq;
}

/*void makeHistogram(ifstream &fin, ofstream &fout, vector<histo> &histoItems, string inFile)
{
vector<int> chars;
unsigned char buffer;
int prevNum = -1;
int i = 0;
int uniqueVals = 0;
int valRepeats;

//read in the file
while(fin.read((char *)&buffer, 1))
chars.push_back(buffer);

sort(chars.begin(), chars.end());

//find the ascii codes and instances of unique characters
for(auto j : chars)
{
if(prevNum != j)
{
prevNum = j;
uniqueVals++;
histoItems.resize(uniqueVals);
histoItems[uniqueVals-1].asciiCode = prevNum;
histoItems[uniqueVals-1].item = int(prevNum);
}
else
histoItems[uniqueVals-1].timesRepeated++;
}

//store the probability of each character
for(i = 0; i < histoItems.size(); i++)
{
histoItems[i].freq = double(histoItems[i].timesRepeated) / chars.size();
histoItems[i].freq = histoItems[i].freq * 100;
}

//output notification of first pass
cout << "Huffman Encoder Pass 1\n----------------------\nRead " << chars.size()
<< " bytes from " << inFile << ", found " << uniqueVals << " code words\n\n";

/*
//vvvvvTESTINGvvvvv
cout << "##########TESTING##########\n";
cout << histoItems.size() << " unique items\n";
cout << chars.size() << " many characters\n\n";
for(i = 0; i < histoItems.size(); i++)
{
cout << "ascii: " << histoItems[i].asciiCode << endl;
cout << "item: " << histoItems[i].item << endl;
cout << "times repeated: " << histoItems[i].timesRepeated << endl;
cout << "probability: " << fixed << setprecision(2) << histoItems[i].freq << endl << endl;
}
cout << "Read in values: ";
for(i = 0; i < chars.size(); i++)
cout << chars[i] << " ";
cout << endl;

return;
}*/

void writeHistogram(ofstream &fout, vector<histo> &histoItems)
{
     int i = 0;
     int sum = 0;

     for (i = 0; i < histoItems.size(); i++)
          sum += histoItems[i].timesRepeated;

     //write histogram info to beginning of encoded file
     for (i = 0; i < histoItems.size(); i++)
          histoItems[i].freq = (histoItems[i].timesRepeated / double(sum)) * 100;

     sort(histoItems.begin(), histoItems.end(), cmpFreqs);

     for (i = 0; i < histoItems.size(); i++)
          fout << fixed << setprecision(2) << histoItems[i].asciiCode << histoItems[i].freq;

     fout << '\n';

     return;
}
