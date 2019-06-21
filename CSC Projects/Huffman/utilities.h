/***************************************************************************//**
@file
@brief <DESCRIPTION>
*******************************************************************************/

#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct histo
{
    int asciiCode;
    string code = "";
    int timesRepeated = 1;
    double freq;
    char item;
};

//utility function prototypes
//void makeHistogram(ifstream &fin, ofstream &fout, vector<histo> &histoItems, string inFile);
void writeHistogram(ofstream &fout, vector<histo> &histoItems);
bool cmpFreqs(const histo &lhs, const histo &rhs);

#endif
