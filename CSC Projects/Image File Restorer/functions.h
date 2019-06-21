#ifndef __FUNCTIONS__H_
#define __FUNCTIONS__H_

#include <string>
#include <iostream>
#include <direct.h>
#include <io.h>
#include <fstream>
#include <stdlib.h> 
using namespace std;
int openfolder(char(*dirpath));
int isjpg(ifstream &file, string name);
int isgif(ifstream &file, string name);
int ispng(ifstream &file);
int isbmp(ifstream &file, string name);
void bmpchange(ifstream &file, string name);
void parsefile(char(*dirpath));
int  openfile(char *file, string name);
void gifchange(ifstream &file, string gif);
void bmpchangeh(int width, ifstream  &file, string name);
int namejpg(string name);
int start(char(*dirpath));
int ispng(ifstream &file, string name);
void pngw(ifstream &file, string name);
void namechangebmp(unsigned int width, unsigned int height, string name);
void pngh(ifstream &file, string name, unsigned int width);
void pngnamechange(string name, unsigned int width, unsigned int height);
void gifnamechange(string name, unsigned int height, unsigned width);
#endif