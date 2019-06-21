#include "queue.h"

int main(int argc, char *argv[])
{
    fileio files;
    printData data;
    queue<document> documentQueue;


    srand((int)time(nullptr));


    if (argc < 4)
    {
        printUsage();
        return 3;
    }

    data.idle = atoi(argv[1]);
    data.printTime = atoi(argv[2]);
    if (!strcmp(argv[3], "-f"))
        if (!openFile(files))
            printError(1);

    if (!strcmp(argv[3], "-r"))
        simulation(files, documentQueue, data, true);
    else if (!strcmp(argv[3], "-f"))
        simulationf(files, documentQueue, data, false);
    else
    {
        printUsage();
    }
    if (closeFile(files))
        printError(2);

    return 0;
}

void simulation(fileio &files, queue<document> &printer, printData &data, bool random)
{
    document tempIn;
    document tempOut;
    int i = 0;
    int timeCurrent = 0;
    int timeSeed = 0;
    int timeSum = 0;
    int pageSeed = 0;
    int idletime = 0;
    int endTime = 0;
    data.amountPrinted = 0;
    int size = 0;

    while (timeCurrent <= 28800)
    {
        size = printer.size();
        if (random)
        {

            tempIn.time_arrived = timeCurrent + getArrival(data.idle, rand());
            tempIn.pages = getPage(rand());



            //
        }

        if (printer.isEmpty() == true)
        {
            idletime = idletime + (tempIn.time_arrived - timeCurrent);
            timeCurrent = tempIn.time_arrived;
            endTime = tempIn.pages * data.printTime + timeCurrent;
            printer.enque(tempIn);
            size = printer.size();

        }

        else
        {
            size = printer.size();
            if (size > 0)
            {
                tempOut = printer.front(tempOut);
            }

            timeCurrent = tempOut.time_end_printing = tempOut.pages*data.printTime + timeCurrent;
            if (tempOut.time_end_printing > tempIn.time_arrived)
            {
                printer.enque(tempIn);

            }
            else
            {
                while (size != 0 && tempOut.time_end_printing<28800 && timeCurrent<28800)
                {
                    printer.deque(tempOut);
                    data.amountPrinted += 1;
                    size = printer.size();
                    if (size > 0)
                    {
                        tempOut = printer.front(tempOut);
                        timeCurrent = tempOut.time_end_printing = tempOut.pages*data.printTime + timeCurrent;

                    }



                }
                if (tempOut.time_end_printing < tempIn.time_arrived)
                {
                    idletime = (tempIn.time_arrived - tempOut.time_end_printing) + idletime;
                }
                printer.enque(tempIn);
            }
        }


    }



    data.avgPrint = idletime;
    printResults(data, printer.size());
    return;
}

void simulationf(fileio &files, queue<document> &printer, printData &data, bool random)
{
    document tempIn;
    document tempOut;
    int i = 0;
    int timeCurrent = 0;
    int timeSeed = 0;
    int timeSum = 0;
    int pageSeed = 0;
    int idletime = 0;
    int endTime = 0;
    data.amountPrinted = 0;
    int size = 0;

    while (timeCurrent <= 500)
    {
        size = printer.size();
        if (!random)
        {


            files.arrival >> timeSeed;
            files.pages >> pageSeed;

            tempIn.pages = getPage(pageSeed);
            tempIn.time_arrived = timeCurrent + getArrival(data.idle, timeSeed);







        }

        if (printer.isEmpty() == true)
        {
            idletime = idletime + (tempIn.time_arrived - timeCurrent);
            timeCurrent = tempIn.time_arrived;
            endTime = tempIn.pages * data.printTime + timeCurrent;
            printer.enque(tempIn);
            size = printer.size();

        }

        else
        {
            size = printer.size();
            if (size > 0)
            {
                tempOut = printer.front(tempOut);
            }

            timeCurrent = tempOut.time_end_printing = tempOut.pages*data.printTime + timeCurrent;
            if (tempOut.time_end_printing > tempIn.time_arrived)
            {
                printer.enque(tempIn);

            }
            else
            {
                while (size != 0 && tempOut.time_end_printing<500 && timeCurrent<500)
                {
                    printer.deque(tempOut);
                    data.amountPrinted += 1;
                    size = printer.size();
                    if (size > 0)
                    {
                        tempOut = printer.front(tempOut);
                        timeCurrent = tempOut.time_end_printing = tempOut.pages*data.printTime + timeCurrent;

                    }



                }
                if (tempOut.time_end_printing < tempIn.time_arrived)
                {
                    idletime = (tempIn.time_arrived - tempOut.time_end_printing) + idletime;
                }
                printer.enque(tempIn);
            }
        }


    }



    data.avgPrint = idletime;
    printResults(data, printer.size());
    return;
}
void printUsage()
{
    cout << "Printer Idle Time simulation: " << endl
        << "USAGE: prog4.exe [average arrival time seconds] [print time seconds]"
        << " -[flags]" << endl << "Program is fed arrival times in seconds and" <<
        " average times \nfor printing in seconds for simulation." << endl
        << "NOTE: MUST SPECIFY FLAGS FOR PROGRAM TO RUN"
        << endl << endl << "For flags, must specify -r or -f." << endl << endl <<
        "-f reads arrival times and pages from input files named from"
        << endl << "files. Name these files \"arrival.rand\" and \"pages.rand\" "
        << endl << "to be read in correctly." << endl << endl <<
        "-r generates random numbers for arrival and idle times for the simulation.";
    return;
}

bool openFile(fileio &files)
{
    files.arrival.open("arrival.rand");
    files.pages.open("pages.rand");

    if (!files.arrival || !files.pages)
        return false;

    return true;
}

bool closeFile(fileio &files)
{
    files.arrival.close();
    files.pages.close();

    if (files.arrival || files.pages)
        return false;

    return true;
}

void printError(int error)
{
    switch (error)
    {
    case 1:
        cout << "ERROR: input file failed to open, exiting!";
        exit(1);
        break;
    case 2:
        cout << "ERROR: input files failed to close, exiting!";
        exit(1);
        break;
    }
}

void  printResults(printData &docs, int size) //function argument queue<document> should probably be changed later to a pure integer value
{
    cout << "Number of seconds between printing documents (arrival): " << docs.idle << endl;
    cout << "Number of seconds to print a page: " << docs.printTime << endl;
    cout << "Documents Printed: " << docs.amountPrinted << endl;
    cout << "Number of seconds printer idle: " << docs.avgPrint << endl;;
    cout << "Number of documents still in queue:  " << size << endl;
}

int getArrival(int arrival, int seed)
{
    int high = arrival + 30;
    int low = arrival - 30;
    return seed % (high - low + 1) + low;
}

int getPage(int pages)
{
    return (pages % 11) + 10;
}

//QUEUE CLASS FUNCTIONS
template<class TY>
queue<TY>::queue()
{
    headptr = nullptr;
    tailptr = nullptr;
}

template<class TY>
queue<TY>::~queue()
{
    node *temp;

    temp = new (nothrow)node;

    temp = headptr;

    while (temp != nullptr)
    {
        headptr = headptr->next;
        delete(temp);
        temp = headptr;
    }

    tailptr = nullptr;

    delete headptr;
    delete tailptr;
}

template<class TY>
bool queue<TY>::enque(TY item)
{
    node *temp;
    node *curr;
    node *prev;
    temp = new (nothrow)node;

    if (temp == nullptr)
        return false;

    temp->item = item;
    temp->next = nullptr;

    if (headptr == nullptr)
    {
        headptr = temp;

        return true;
    }
    curr = headptr;
    prev = headptr;
    while (curr != nullptr)
    {
        prev = curr;
        curr = curr->next;
    }
    prev->next = temp;
    temp->next = curr;
    return true;

}

template<class TY> int queue<TY>::size()
{
    node *tempptr = headptr;
    int count = 1;
    if (tempptr == NULL)
    {
        return 0;
    }
    while (tempptr->next != NULL)
    {

        count = count + 1;
        tempptr = tempptr->next;
    }
    return count;
}

template<class TY> bool queue<TY> ::isEmpty()
{
    if (headptr == nullptr)
    {
        return true;
    }
    else
        return false;
}

template<class TY > TY queue<TY>::front(TY &item)
{
    return headptr->item;
}

template< class TY> bool queue<TY> ::deque(TY &item)
{
    node *temp;

    if (headptr == nullptr)
    {
        return false;
    }
    temp = headptr;
    headptr = headptr->next;
    delete temp;
    return true;

}