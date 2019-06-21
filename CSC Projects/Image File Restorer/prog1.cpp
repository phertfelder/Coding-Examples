/*************************************************************************//**
 * @file
 *
 * @mainpage Program 1- Image File restorer
 *
 * @section M002 CSC 250
 *
 * @author Paul Hertfelder
 *
 * @date 2/26/2016
 *
 * @par Professor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 250
 *
 * @par Location:
 *         McLaury - Room 313 
 *
 * @section program_section Program Information
 *
 * @details This program opens up files in binary and searches for details in binary
 * on whether it is a jpg, bmp,png or gif file type. All other types of files are ignored
 * and are not processed for renaming. After the file is found to be an image the program then
 * sends it to the necessary functions depending on if it is a jpeg, png etc. For certain file types
 * the program extracts the height and width of the image and adds it to the restored name. For example
 * File: "Frog" could become "Frog_45_x_50.gif". This is done to bmp, png and gif images. JPEG files do not 
 * have the height and width added to it. After the program searches through the folder it returns back to the folder
 * that the program was opened in and looks at the next argument then the program moves directories and searches
 * or fails opening that folder and moves on to the next argument. This continues until no arguments are left.
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
   c:\> prog1.exe folder folder folder
   c:\> prog1.exe folder c:/folder
   
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
   
   

   @endverbatim
 *
 *****************************************************************************/



#include "functions.h"
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function is main it is the start of the program it takes in arguments
that will tell it to open which folder to search for files and find out what
image types it may be. 
It connects to all other functions.
It will end once it has completed the task with using all the arguments. Other
functions check for if the arguments work. So main always succedes and returns
0. Main also stores the starting directory so it may return to complete the 
folders that maybe located in the starting directory. 



*
* @param[in]      argc  - argument count from program starting
* @param[in]      argv  - contains the arguments
*
*
* @returns 0 program ran successful.
* 
* 
*
*****************************************************************************/
int main(int argc, char *argv[])
{
    int arguments = 1;
    int _chdir(char *dirpath);
    char *_getcwd(char *cstr, int size);
    char *begin;
    char h[_MAX_PATH];
    begin = _getcwd(NULL, 0);
    strcpy_s(h, begin);
    //allow the use of multiple arguments
    while (arguments < argc)
    {
        //go to the function for arguments
        openfolder(argv[arguments]);

        //go to next argument
        arguments++;
        //return to start location
        start(h);
        //continue until there is no more arguments. 
    }

    return 0;
}