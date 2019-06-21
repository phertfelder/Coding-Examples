/*************************************************************************//**
 * @file
 *
 * @mainpage Program 3- DIR.xml file
 *
 * @section M001 CSC 250
 *
 * @author Paul Hertfelder
 *
 *
 *
 * @par Professor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 250
 *
 * @par Location:
 *         McLaury - Room 204 W
 *
 * @section program_section Program Information
 *
 * @details This program takes a folder and displays the information that the
 * folder contains into an dir.xml file. If the folder contains multiple
 * folders it will be organized by main then subdirectories. If an argument
 * is passed that is after the folder being sorted like *.* It will display
 * all file types. Depending on arguments sent is how the files will be shown
 * in xml file. 
 *
 * 
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\> prog3.exe folder *.*
   c:\> -M prog3.exe folder *.*
   c:\> -C prog3.exe folder p*.cpp
   c:\> -C -M prog3.exe folder *.*
                        -M Modified date will be shown
                        -C Creation date will be shown
                        *.* can be changed to find which files to place into
                        xml file.
                        -M -C Modified first created after in xml
                        -C -M created first then modified. 
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug None that I can find.
 *
 * @todo none
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date           Modification
   -------------  -------------------------------------------------------------
   April  8, 2015  Started Program learning functions in file.
   April 9, 2015   Organizing folders displaying in Command prompt
   April 11, 2015  Creation of xml file with contents
   April 12, 2015  Doxygen checking bugs. 
   

   @endverbatim
 *
 *****************************************************************************/


#include <direct.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <ctime>


using namespace std;

int openfolder(char *dirpath);
char *getpath(char *cstr, int size, ofstream &out, char *prob, char *home);
void getfolders(char *dirpath, ofstream &out, char *prob, char *home);
void getfoldersC2(char *dirpath, ofstream &out, char *prob, char *C, 
    char *home);
char *getpathC2(char *cstr, int size, ofstream &out, char *prob, char *C, 
    char *home);
void printfolder1(char *full, char *home, ofstream &out);
char *getpathC3(char *cstr, int size, ofstream &out, char *C, char *M, char *prob, 
    char *home);
void getfoldersC3(char *dirpath, ofstream &out, char *prob, char *C, char *M, 
    char* home);

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function is main it is the start of the program it takes in arguments
that will tell it to open which folder to place into xml file. 
It connects to all other functions.
It will end once it has completed the task or fails due to errors like not
enough arguments. It will open file and place file in location located where
XML File is located: (location of file). Main will call other functions 
depending on arguments. There are no loops present recursion will be used in



*
* @param[in]      argc  - argument count from program startiing
* @param[in]      argv  - contains the arguments
*
*
* @returns 0 program ran successful.
* @returns 1 Error arguments not enough.
* 
*
*****************************************************************************/
int main(int argc, char *argv[])
{
    ofstream fout;
    char *begin;
    char start[_MAX_PATH];
    char fold[_MAX_PATH];
    fout.open("dir.xml", ios::trunc);
    fout << "<?xml version = \"1.0\"?>" << endl;
    begin = _getcwd(NULL, 0);
    strcpy_s(start, begin);
    
    
    cout << "XML File is located: " << start <<endl;
    if (argc == 3)
    {
        openfolder(argv[1]);
        begin = _getcwd(NULL, 0);
        strcpy_s(fold, begin);
        cout << "The Folder is: "<<fold << endl;
        printfolder1(fold, start, fout);
        
        openfolder(fold);
        getpath(fold, _MAX_PATH, fout, argv[2], start);
        
    }
    
    if (argc == 4)
    {
    openfolder(argv[2]);
    begin = _getcwd(NULL, 0);
    strcpy_s(fold, begin);
    printfolder1(fold, start, fout);
    openfolder(fold);
    
    getpathC2(fold, _MAX_PATH, fout, argv[3], argv[1],start);
    }

    if (argc == 5)
    {
        openfolder(argv[3]);
        begin = _getcwd(NULL, 0);
        strcpy_s(fold, begin);
        printfolder1(fold, start, fout);
        openfolder(fold);

        getpathC3(fold, _MAX_PATH, fout, argv[2], argv[1], argv[4], start);
    }
    else if (argc !=3&&argc!=4 && argc!=5)
    {
        cout << "Not enough arguments." << endl;
        exit(1);
    }
    fout.close();

    delete[]begin;
    return 0;
}







/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function opens the folder that will be used to parse files/folders in
 the folder chosen. It will check if directories did change or did not change
 correctly. It will return 0 if directories changed correctly. 


*
* @param[in]      *dirpath - The path that is location of folder being used.
* 
*
*
* @returns 0    Program changed directories correctly
* @returns 1       Could not change directory
* 
*
*****************************************************************************/
int openfolder(char *dirpath)
{
    if (_chdir(dirpath) == 0)
    {
        cout << "Program changed directories successfully" << endl;
    }
    else
    {
        cout << "Unable to change to the directory :" << dirpath << endl;
        exit(1);
    }

    return 0;
}
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function finds the folders inside the folder selected parses for file
 types and writes to xml file. This function writes to file location and calls
 multiple functions depending on writing of information. The function takes
 in multiple arguments and uses multiple file location variables to determine
 if the data being searched is either a folder or a file. This function uses
 recursion. 


*
* @param[in]      *dirpath - The path that is location of folder being used.
* @param[in]      &out     -     The xml file for writing information to
* @param[in]      *prob    -    The type of files to find in folders
* @param[in]      *home    -    The location of the file dir.xml
*
*
* 
* 
* 
*
*****************************************************************************/


void getfolders(char *dirpath, ofstream &out, char *prob, char* home)
{
    char full[_MAX_PATH];
    _finddata_t a_file;
    intptr_t  file_handle;
    _finddata_t f_file;
    intptr_t  dir_handle;
    file_handle = _findfirst(prob, &f_file);
    dir_handle = _findfirst("*.*", &a_file);
    if (dir_handle == -1)
    {
        return;
    }
    do
    {
        if (strcmp(".", a_file.name) != 0 && strcmp("..", a_file.name) != 0 
            && a_file.attrib & _A_SUBDIR)
        {
            if (a_file.attrib & _A_SUBDIR)
            {
                strcpy_s(full, dirpath);
                strcat_s(full, "\\");
                strcat_s(full, a_file.name);
                printfolder1(full, home, out);
                openfolder(full);
                getpath(full, _MAX_PATH, out, prob, home);
            }
        }

    } while (_findnext(dir_handle, &a_file) == 0);

    if (file_handle == -1)
    {
        out << "</folder>" << endl;
        return;
    }
    do
    {
        if (strcmp(".", f_file.name) != 0 && strcmp("..", f_file.name) != 0)
        {


            if (f_file.attrib & _A_ARCH || f_file.attrib & _A_HIDDEN ||
                f_file.attrib & _A_NORMAL || f_file.attrib & _A_RDONLY)
            out << "<file name=\"" << f_file.name << "\" />" << endl;
        }

    } while (_findnext(file_handle, &f_file) == 0);


    out << "</folder>" << endl;
    _findclose(file_handle);
    _findclose(dir_handle);
   
    return;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function finds the full path of folder location to write to out.
 * This function uses dynamic memory to write the address to send to folder
 function for opening and writing to out. This functions find the path by
 getting the current working directory.


*
* @param[in]      *cstr - The path that is location of folder being used.
* @param[in]      size - The size of cstr which is _MAX_PATH
* @param[in]      &out  - The xml file for writing information to
* @param[in]      *prob - The type of files to find in folders
* @param[in]      *home - The location of the file dir.xml
*
*
* @returns  buffer returns the path of folder for writing in another function. 
* 
* 
*
*****************************************************************************/
char *getpath(char *cstr, int size, ofstream &out, char *prob, char* home)
{
    char *buffer;
    buffer = _getcwd(NULL, 0);

    getfolders(buffer, out, prob, home);

    delete[] buffer;
    return buffer;

}


/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function writes the path of the  folder to the xml file.
* And returns to main. This output is appended to xml file.  The written text
is formatted for XML files and will display correctly in the browser. It takes
in two parameters out and name. Out being the file to append to and name being
the folder name. 


*
* @param[in]      &out  - The xml file for writing information to
* @param[in]      *name - The name of the file needing to be written to out
*   
*
*
* 
* 
* 
*
*****************************************************************************/


void printfolder(ofstream &out, char *name)
{

    out.open("dir.xml", ios::app);

    out << "<folder name = \"" <<
        name << "\\\">" << endl;
    return;
}

//3 arguments TIME MODIFIED
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function finds the folders inside the folder selected parses for file
 types and writes to xml file. This function writes to file location and calls
 multiple functions depending on writing of information. This function also
 takes in the change in file details. This function will add creation date
 or modified date depending on user. 


*
* @param[in]      *dirpath - The path that is location of folder being used.
* @param[in]      &out     - The xml file for writing information to
* @param[in]      *prob    - The type of files to find in folders
* @param[in]      *C       - The creation or modified command      
* @param[in]      *home    - The location of the file dir.xml
*
*
* 
* 
* 
*
*****************************************************************************/
void getfoldersC2(char *dirpath, ofstream &out, char *prob, char *C, 
    char *home)
{
    time_t result;
    _finddata_t a_file;
    _finddata_t f_file;
    intptr_t  dir_handle;
    intptr_t file_handle;
    char full[_MAX_PATH];
    dir_handle = _findfirst("*.*", &a_file);
    file_handle = _findfirst(prob, &f_file);
    if (dir_handle == -1)
    {
        return;
    }
    do
    {
        if (strcmp(".", a_file.name) != 0 && strcmp("..", a_file.name) != 0 
            && a_file.attrib & _A_SUBDIR)
        {

            strcpy_s(full, dirpath);
            strcat_s(full, "\\");
            strcat_s(full, a_file.name);
            printfolder1(full, home, out);
            openfolder(full);
            getpathC2(full, _MAX_PATH, out, prob, C, home);
        }
    } while (_findnext(dir_handle, &a_file) == 0);

    if (file_handle == -1)
    {
        out << "</folder>" << endl;
        return;
    }
    do
    {
        if (strcmp("-C", C) == 0)
        {
            if (strcmp(".", f_file.name) != 0 && strcmp("..", f_file.name) 
                != 0)
            {
                result = f_file.time_create;
                if (f_file.attrib & _A_ARCH || f_file.attrib & _A_HIDDEN || 
                    f_file.attrib & _A_NORMAL || f_file.attrib & _A_RDONLY)
                    out << "<file name=\"" << f_file.name 
                    << "\" DateCreated=\"" << ctime(&result) << "\"/>" 
                    << endl;
            }
        }
        else if (strcmp("-M", C) == 0 )
        {
            if (strcmp(".", f_file.name) != 0 && strcmp("..", f_file.name) 
                != 0)
            {
                result = f_file.time_write;
                if (f_file.attrib & _A_ARCH || f_file.attrib & _A_HIDDEN ||
                    f_file.attrib & _A_NORMAL || f_file.attrib & _A_RDONLY)
                    out << "<file name=\"" << f_file.name 
                    << "\" DateModified=\"" 
                    << ctime(&result) << "\" />" << endl;

            }
        }

    } while (_findnext(file_handle, &f_file) == 0);
    _findclose(file_handle);
     out << "</folder>" << endl;
    _findclose(dir_handle);
    
    
    return;
}


/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function finds the full path of folder location to write to out.
 * This function uses dynamic memory to write the address to send to folder
 function for opening and writing to out. This functions find the path by
 getting the current working directory.


*
* @param[in]      *cstr    - The path that is location of folder being used.
* @param[in]      size     - The size of _MAX_PATH
* @param[in]      &out     - The xml file for writing information to
* @param[in]      *prob    - The type of files to find in folders
* @param[in]      *C       - The creation or modification depending on user. 
* @param[in]      *home    - The location of the file dir.xml
*
*
* @returns  buffer returns the path of folder for writing in another function. 
* 
* 
*
*****************************************************************************/
char *getpathC2(char *cstr, int size, ofstream &out, char *prob, char *C,
    char *home)
{
    char *buffer;
    buffer = _getcwd(NULL, 0);
    cout << buffer << endl;
    getfoldersC2(buffer, out, prob, C,home);
    delete[] buffer;
    return buffer;

}
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function writes the name of the folder that needs to be
 written to the xml file. It is void and only returns. The name is appended
 to the xml file. it then calls openfolder to open the folder of xml file and
 opens again the original folder that is being searched. This function after
 completing the task returns back to previous function it was called from. 


*
* @param[in]      *full - The path of the folder
* @param[in]      *home  - The path of xml file. 
* @param[in]      &out  - The xml file that needs to be written to. 
*
*
* 
* 
* 
*
*****************************************************************************/
void printfolder1(char *full, char *home,ofstream &out)
{
    cout << "Home: " << home << endl;
    cout << "FULL NAME: " << full << endl;
    openfolder(home);
  
    
    out << "<folder name = \"" <<
        full << "\\\">" << endl;
    openfolder(full);
    return;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function finds the full path of folder location to write to out.
 * This function uses dynamic memory to write the address to send to folder
 function for opening and writing to out. This functions find the path by
 getting the current working directory. The function then will call folders
 to print to XML file. it is using a dynamic char array to store the path
 which is then deleteed after the function has been returned that is has called



*
* @param[in]      *cstr    - The path that is location of folder being used.
* @param[in]      size     - The size of _MAX_PATH
* @param[in]      &out     - The xml file for writing information to
* @param[in]      *prob    - The type of files to find in folders
* @param[in]      *C       - The creation or modification depending on user. 
* @param[in]      *M       - The creation or modification depending on user.
* @param[in]      *home    - The location of the file dir.xml
*
*
* @returns  buffer returns the path of folder for writing in another function. 
* 
* 
*
*****************************************************************************/
char *getpathC3(char *cstr, int size, ofstream &out, char *C, char *M,
    char *prob, char *home)
{
    char *buffer;
    buffer = _getcwd(NULL, 0);
    cout << buffer << endl;
    getfoldersC3(buffer, out, prob, C, M, home);
    delete[] buffer;
    return buffer;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function finds the folders inside the folder selected parses for file
 types and writes to xml file. This function writes to file location and calls
 multiple functions depending on writing of information. This function will
 also add data to the name depending on user. If -M is chosen first modified 
 will be displayed and C- created date is chosen second and vice versa.This
 function does use recursion as it will return to the previous call into all
 folders and files have been displayed. 


*
* @param[in]      *dirpath - The path that is location of folder being used.
* @param[in]      &out     -     The xml file for writing information to
* @param[in]      *prob    -    The type of files to find in folders
* @param[in]      *C       -    Creation/Modified which is chosen first.
* @param[in]      *M       -    Creation/Modified which is chosen second
* @param[in]      *home    -    The location of the file dir.xml
*
*
*  
* 
* 
*
*****************************************************************************/
void getfoldersC3(char *dirpath, ofstream &out, char *prob, char *C, char *M,
    char* home)
{
    time_t result;
    _finddata_t a_file, f_file;
    intptr_t  dir_handle, file_handle;
    char full[_MAX_PATH];
    dir_handle = _findfirst("*.*", &a_file);
    file_handle = _findfirst(prob, &f_file);
    if (dir_handle == -1)
    {
        return;
    }
    do
    {
        if (strcmp(".", a_file.name) != 0 && strcmp("..", a_file.name) != 0
            && a_file.attrib & _A_SUBDIR)
        {

            strcpy_s(full, dirpath);
            strcat_s(full, "\\");
            strcat_s(full, a_file.name);
            printfolder1(full, home, out);
            openfolder(full);
            getpathC3(full, _MAX_PATH, out, C, M,prob, home);
        }
    } while (_findnext(dir_handle, &a_file) == 0);
    if (file_handle == -1)
    {
        out << "</folder>" << endl;
        return;
    }

    do
    {
        if (strcmp("-C", C) == 0 || strcmp("-M", M) == 0)
        {
            if (strcmp(".", f_file.name) != 0 && strcmp("..", f_file.name)
                != 0)
            {
                result = f_file.time_create;
                if (f_file.attrib & _A_ARCH || f_file.attrib & _A_HIDDEN ||
                    f_file.attrib & _A_NORMAL || f_file.attrib & _A_RDONLY)
                {
                    out << "<file name=\"" << f_file.name 
                        << "\" DateCreated=\"" 
                        << ctime(&result)<<"\"";;
                    result = f_file.time_write;
                    out << " DateModified=\"" << ctime(&result) << "\" />" 
                        << endl;
                }
            }
        }
        else if (strcmp("-M", M) == 0 || strcmp("-M", C) == 0)
        {
            if (strcmp(".", f_file.name) != 0 && strcmp("..", f_file.name)
                != 0)
            {
                result = f_file.time_write;
                if (f_file.attrib & _A_ARCH || f_file.attrib & _A_HIDDEN ||
                    f_file.attrib & _A_NORMAL || f_file.attrib & _A_RDONLY)
                    out << "<file name=\"" << f_file.name 
                    << "\" DateModified=\"" << ctime(&result) << "\"";
                result = f_file.time_create;
                out << " DateCreated=\"" << ctime(&result) << "\" />" << endl;

            }
        }

    } while (_findnext(file_handle, &f_file) == 0);
    _findclose(file_handle);
    out << "</folder>" << endl;
    _findclose(dir_handle);
    

    return;

}

