#ifndef _QUEUE_H__
#define _QUEUE_H__

#include <iostream>
#include <fstream>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

struct document
{
    int pages; // number of pages in the document
    int time_arrived; // number of seconds from the start of day
    int time_dequeued; // unknown
    int time_started_print; // unknown
    int time_end_printing; // unknown
};

struct fileio
{
    ifstream arrival;
    ifstream pages;
};

struct printData
{
    int printTime;
    int avgArriva;
    int avgPrint;
    int amountPrinted;
    int idle;
};

template<class TY>
class queue
{

public:
    queue();
    ~queue();
    bool enque(TY item);
    bool deque(TY &item);
    TY front(TY &item);
    bool isEmpty();
    int size();


private:
    struct node
    {
        TY item;
        node *next;
    };

    node *headptr;
    node *tailptr;

};

void simulation(fileio &files, queue<document> &printer, printData &data, bool random);
void simulationf(fileio &files, queue<document> &printer, printData &data, bool random);

void printUsage();
bool correctUsage(string load, string printTime, string mode);
bool openFile(fileio &files);
bool closeFile(fileio &files);
void printError(int error);
void printResults(printData &docs, int size);
//void printResults(printData &docs, queue<int> &queue);
int getArrival(int arrival, int seed);
int getPage(int pages);


#endif