#include "functions.h"


/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function opens the folder that will be used to parse files in
 the folder chosen. It will check if directories did change or did not change
 correctly. It will return 0 if program is finished parsing the folder in 
 another function or will return 0 due to failing. Either result will allow
 program to move onto another argument. 


*
* @param[in]      *dirpath - The path that is location of folder being used.
* 
*
*
* @returns 0   Finished parsing the folder or could not open the folder.
* 
* 
*
*****************************************************************************/
int openfolder(char *dirpath)
{
    //check if program can open directory if so go to next function
    if (_chdir(dirpath) == 0)
    {
        parsefile((dirpath));

    }
    // cannot open folder
    else if (_chdir(dirpath) != 0)
    {
        cout << "Unable to locate folder" << endl;
        return 0;
    }
    return 0;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function returns the program to the starting folder. This is so that
 it allows ease to the user by just typing out the the folder names into
 the arguments and searching the starting folder with ease and without the need
 of the direct path. 


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
int start(char *dirpath)
{
    // Switching back to the starting dir
    if (_chdir(dirpath) == 0)
    {
        return 0;

    }
    //cant open starting directory
    else if (_chdir(dirpath) != 0)
    {

        return 1;
    }
    return 0;

}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function searches through the folder looking for files 
 once a file is found the name of the file is saved as string for future
 use. After the file is found and the name is saved it is sent to another
 function. This continues until no other files are found. 

*
* @param[in]      *dirpath - The path that is location of folder being used.
* 
*
*
* 

* 
*
*****************************************************************************/
void parsefile(char(*dirpath))
{
    //io.h items
    _finddata_t a_file;
    intptr_t dir_handle;
    string name;
    //mask
    unsigned int number = 16;
    unsigned int file;
    

    dir_handle = _findfirst("*.*", &a_file);
    if (dir_handle == -1)
        return;

    // Search through files then if it is a file and not a directory send to
    // next function.
    do
    {
        if (strcmp(".", a_file.name) != 0 && strcmp("..", a_file.name) != 0)
        {
            //compare the 5th bit.
            file = file&number;
            
            //if the file has a 1 in 5th bit it means it is a folder
            // and thus equal to the number of 16a
            //if the number is not equal it is a file. 
            if (file==0)
            {
                
                name = a_file.name;
                openfile(a_file.name, name);

            }
        }

    } while (_findnext(dir_handle, &a_file) == 0);
    _findclose(dir_handle);
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 * This function opens the file. Then send the file to other functions
 to check for what file type it is. If the file cannot be opened and error
 is outputed and returns 1. Else if the file does open it is checked to see
 if it is jpg, gif, png, bmp. After this task it returns to the previous function.



*
* @param[in]      *file - The file name.
* @param[in]       name - The file name in a string.
* 
*
*
* @returns 0    Program finished opening the file and searching through it.
* @returns 1    Unable to open the file. 
* 
*
*****************************************************************************/
int  openfile(char *file, string name)
{
    ifstream fin;
    int x;
    //open file in binary mode.
    fin.open(file, ios::in | ios::binary);
    if (!fin)
    {
        
        return 1;
    }

    x = isgif(fin, name);
    //If the return value is 0 this means one of the image types have been
    // chosen so if a jpg is found there is no need to search if its a gif
    // or bmp. Return value tells what needs to be done. 

    //go to bmp
    if (x == 1)
    {
        x = isbmp(fin, name);
    }
    //go to jpg
    if (x == 2)
    {
        x = isjpg(fin, name);
    }
    //go to png
    if (x == 3)
    {
        x = ispng(fin, name);
    }

    //close file
    fin.close();


    return 0;
}
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function gains the opened file it then searches through the file 
* looking for details that can be attributed to gif image types. If the file
* does contain information that shows it is a gif type image. It is sent
* to the next function. And returns 0 if the image was a gif. Else
* The function returns 1 and returns to the previous function. 

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
*
* @returns 0    The file is a gif.
* @returns 1    The file is not a gif.

* 
*
*****************************************************************************/
int isgif(ifstream &file, string name)
{
    //create variables
    char*read;
    int size;
    //seek then read in the required bits
    file.seekg(6, ios::beg);
    size = file.tellg() / sizeof(char);
    file.seekg(0, ios::beg);
    //create dynamic array
    read = new(nothrow)char[size];
    //read in the bits
    file.read((char*)read, 6);

    // check if the first 6 bits are what is needed to be a gif
    if (read[0] == 'G'&&read[1] == 'I'&&read[2] == 'F'&&read[3] == '8'
        &&read[4] == '7'&&read[5] == 'a' || read[0] == 'G'&&read[1] == 'I'
        &&read[2] == 'F'&&read[3] == '8'&&read[4] == '9'&&read[5] == 'a')
    {

        gifchange(file, name);


        //delete the dynamic array
        delete[]read;
        //return for success 
        return 0;
    }
    //delete dynamic array return that this is not a gif
    else
    {

        delete[]read;
        return 1;

    }




}
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function is only opened when the file is proven to be a gif type.
* The opened file is searched through to find the height and width of the
* image after the details are found the function send the information
* to the next function. This functions only purpose is to extract the 
* height and width then combine it into a short int using bitwise operators. 

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
*

* 
*
*****************************************************************************/
void gifchange(ifstream &file, string name)
{
    //creation of variables
    unsigned char *widthlow, *widthhigh, *heighthigh, *heightlow;
    unsigned short int height = 0;
    unsigned short int width = 0;
    //creation of dynamic arrays
    widthlow = new(nothrow)unsigned char[1];
    widthhigh = new(nothrow)unsigned char[1];
    heighthigh = new(nothrow)unsigned char[1];
    heightlow = new(nothrow)unsigned char[1];
    //seek to the width portion of binary file
    file.seekg(6, ios::beg);
    //read in the characters
    file.read((char*)widthlow, 1);

    //read in the required bits
    file.seekg(7, ios::beg);
    file.read((char*)widthhigh, 1);
    file.seekg(8, ios::beg);
    file.read((char*)heightlow, 1);
    file.seekg(9, ios::beg);
    file.read((char*)heighthigh, 1);
    //using bitwise save the information to form the width
    // and then do the same for height.
    width = (short int)widthhigh[0];
    width = (short int)width << 8;
    width = width | (short int)widthlow[0];
    height = (short int)heighthigh[0];
    height = height << 8;
    height = height | (short int)heightlow[0];
    //delete the dynamic arrays
    delete[]widthlow;
    delete[]widthhigh;
    file.close();
    // go to name change.
    gifnamechange(name, height, width);
    return;

}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function gains the opened file it then searches through the file
* looking for details that can be attributed to bmp image types. If the file
* does contain information that shows it is a bmp type image. It is sent
* to the next function. And returns 0 if the image was a bmp. Else
* The function returns 2 and returns to the previous function.

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
*
* @returns 0    The file is a bmp.
* @returns 2    The file is not a bmp.

* 
*
*****************************************************************************/

int isbmp(ifstream &file, string name)
{
    char*read;
    int size;
    //seek and read in the required bits
    file.seekg(2, ios::beg);
    size = file.tellg() / sizeof(char);
    file.seekg(0, ios::beg);
    read = new(nothrow)char[size];
    file.read((char*)read, 2);

    //after reading in the required bits
    //find out if BM is in the file.
    if (read[0] == 'B'&&read[1] == 'M')
    {
        bmpchange(file, name);



        delete[]read;
        return 0;
    }
    delete[]read;
    return 2;

}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function is only opened when the file is proven to be a bmp type.
* The opened file is searched through to find the  width of the
* image after the details are found the function send the information
* to the next function. This functions only purpose is to extract the 
*  width then combine it into a  int using bitwise operators. 

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
*

* 
*
*****************************************************************************/
void bmpchange(ifstream &file, string name)
{
    unsigned char *byte19, *byte20, *byte21, *byte22;

    unsigned int width = 0;
    //create the dynamic arrays
    byte19 = new(nothrow)unsigned char[1];
    byte20 = new(nothrow)unsigned char[1];
    byte21 = new(nothrow)unsigned char[1];
    byte22 = new(nothrow)unsigned char[1];
    //seek then read in the required bits to the dynamic
    //arrays
    file.seekg(18, ios::beg);
    file.read((char*)byte19, 1);
    file.seekg(19, ios::beg);
    file.read((char*)byte20, 1);
    file.seekg(20, ios::beg);
    file.read((char*)byte21, 1);
    file.seekg(21, ios::beg);
    file.read((char*)byte22, 1);
    //after reading and seeking use bitwise
    //to create the int for width
    width = byte22[0];
    width = width << 8;
    width = width | byte21[0];
    width = width << 8;
    width = width | byte20[0];
    width = width << 8;
    width = width | byte19[0];

    //delete the dynamic arrays
    delete[]byte19;
    delete[]byte20;
    delete[]byte21;
    delete[]byte22;
    //move to the function that find the height.
    bmpchangeh(width, file, name);
}
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function is only opened when the file is proven to be a bmp type.
* The opened file is searched through to find the  height of the
* image after the details are found the function send the information
* to the next function. This functions only purpose is to extract the 
*  height then combine it into a  int using bitwise operators. 

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
* @param[in]       width- the width of the bmp image. 

* 
*
*****************************************************************************/
void bmpchangeh(int width, ifstream  &file, string name)
{
    unsigned char *byte23, *byte24, *byte25, *byte26;

    unsigned int height = 0;
    //create dynamic arrays for the required bytes.
    byte23 = new(nothrow)unsigned char[1];
    byte24 = new(nothrow)unsigned char[1];
    byte25 = new(nothrow)unsigned char[1];
    byte26 = new(nothrow)unsigned char[1];
    //seek and read in the required bits to the dynamic arrays
    file.seekg(22, ios::beg);
    file.read((char*)byte23, 1);
    file.seekg(23, ios::beg);
    file.read((char*)byte24, 1);
    file.seekg(24, ios::beg);
    file.read((char*)byte25, 1);
    file.seekg(25, ios::beg);
    file.read((char*)byte26, 1);
    //combine the bits to form an unsigned int
    height = (unsigned int)byte26[0];
    height = height << 8;
    height = height | (unsigned int)byte25[0];
    height = height << 8;
    height = height | (unsigned int)byte24[0];
    height = height << 8;
    height = height | (unsigned int)byte23[0];
    //delete the dynamic arrays that were used to free up memory
    delete[]byte23;
    delete[]byte24;
    delete[]byte25;
    delete[]byte26;
    file.close();
    namechangebmp(width, height, name);


    return;
}


/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function gains the opened file it then searches through the file
* looking for details that can be attributed to jpg image types. If the file
* does contain information that shows it is a jpg type image. It is sent
* to the next function. And returns 0 if the image was a jpg. Else
* The function returns 2 and returns to the previous function.

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
*
* @returns 0    The file is a bmp.
* @returns 3    The file is not a bmp.

* 
*
*****************************************************************************/
int isjpg(ifstream &file, string name)
{
    //create the required variables
    unsigned char*read;
    unsigned char*ending;
    int size;
    file.seekg(0, ios::end);
    size = file.tellg() / sizeof(char);
    //create dynamic array
    read = new(nothrow)unsigned char[2];
    //seek then read the required bits for the information
    file.seekg(0, ios::beg);
    file.read((char*)read, 2);
    ending = new(nothrow)unsigned char[size];
    file.seekg((size - 2), ios::beg);
    file.read((char*)ending, 2);

    //see if the bits match what is required
    if ((unsigned short int)read[0] == 255 && (unsigned short int) read[1] == 216 && (unsigned short int)ending[1] == 217 && (unsigned short int)ending[0] == 255)
    {
        delete[]read;
        delete[]ending;
        file.close();
        namejpg(name);

        return 0;
    }
    return 3;
}
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function takes the name of the filetype and saves it to change it to
a new name. This function then adds the .jpg image extension 
at the end of the new name. This function only appends the extension to the 
name.
* 

*

* @param[in]      name- The name of the file in string form. 

*


* 
*
*****************************************************************************/
int namejpg(string name)
{

    int result;
    string newname;

    newname = name;
    //append .jpg to the new name
    newname += ".jpg";
    




    result = rename(name.c_str(), newname.c_str());
    //if error occurs to renaming output the error
    if (result != 0)
    {
        cout << "Error renaming file " <<name<<" to "<<newname<< endl;
    }

    


    return 0;

}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function gains the opened file it then searches through the file
* looking for details that can be attributed to png image types. If the file
* does contain information that shows it is a png type image. It is sent
* to the next function. And returns 0 if the image was a png or the search did
not show it was png as this is the last type of image searched for. 

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
*
* @returns 0    The task was completed. 
* 

* 
*
*****************************************************************************/

int ispng(ifstream &file, string name)
{
    unsigned char*read;
    //create an array with the proper values to find if it is png
    unsigned int arr[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    int size;
    file.seekg(0, ios::end);
    //find the size
    size = file.tellg() / sizeof(char);
    //create a dynamic array
    read = new(nothrow)unsigned char[8];
    //seek then read in the proper bits
    file.seekg(0, ios::beg);
    file.read((char*)read, 8);
    //if the certain bits are equal to the result go to the next function
    if ((unsigned short int)read[0] == 137 && (unsigned short int) read[1] == 80 && (unsigned short int)read[2] == 78 && (unsigned short int)read[3] == 71 && (unsigned short int)read[4] == 13 && (unsigned short int)read[5] == 10 && (unsigned short int)read[6] == 26 && (unsigned short int)read[7] == 10)
    {
        pngw(file, name);
    }
    //delete the dynamic array
    delete[]read;
    return 0;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function gains the height, the width and the name of the bmp image.
* The function then appends details of the image to the name. This function
* then adds the .bmp image extension at the end of the new name. The new name
* that is created appends the height and the width to the files name and adds
* the extension. 

*
* @param[in]      width - The width of the image
* @param[in]      name- The name of the file in string form. 
* @param[in]      height- the height of the image
*


* 
*
*****************************************************************************/
void namechangebmp(unsigned int width, unsigned int height, string name)
{
    int result;
    string newname;
    //append the newname from the old name.
    newname = name;
    newname += "_";
    newname += to_string(width);
    newname += "_x_";
    newname += to_string(height);
    newname += ".bmp";
    
    result = rename(name.c_str(), newname.c_str());
    //return if there is an error renaming the file
    if (result != 0)
    {
        cout << "Error renaming file of: " << name << " to " << newname << endl;
    }

    





    return;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function is only opened when the file is proven to be a png type.
* The opened file is searched through to find the  width of the
* image after the details are found the function send the information
* to the next function. This functions only purpose is to extract the 
*  width then combine it into a  int using bitwise operators. 

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
*

* 
*
*****************************************************************************/
void pngw(ifstream &file, string name)
{
    //creation of variables
    unsigned char *byte17, *byte18, *byte19, *byte20;
    unsigned int width = 0;
    //create new dynamic arrays.
    byte17 = new(nothrow)unsigned char[1];
    byte18 = new(nothrow)unsigned char[1];
    byte19 = new(nothrow)unsigned char[1];
    byte20 = new(nothrow)unsigned char[1];

    //seek and read in the proper bits
    file.seekg(16, ios::beg);
    file.read((char*)byte17, 1);
    file.seekg(17, ios::beg);
    file.read((char*)byte18, 1);
    file.seekg(18, ios::beg);
    file.read((char*)byte19, 1);
    file.seekg(19, ios::beg);
    file.read((char*)byte20, 1);
    //combine the bits to create the int
    //using bitwise operations
    width = byte17[0];
    width = width << 8;
    width = width | byte18[0];
    width = width << 8;
    width = width | byte19[0];
    width = width << 8;
    width = width | byte20[0];
    //delete the dynamic arrays
    delete[]byte17;
    delete[]byte18;
    delete[]byte19;
    delete[]byte20;
    //go to the next function
    pngh(file, name, width);
    return;
}
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function is only opened when the file is proven to be a png type.
* The opened file is searched through to find the  height of the
* image after the details are found the function send the information
* to the next function. This functions only purpose is to extract the 
*  height then combine it into a  int using bitwise operators. 

*
* @param[in]      &file - The opened file. 
* @param[in]      name- The name of the file in string form. 
*@param[in]       width- The width of the png image. 

* 
*
*****************************************************************************/
void pngh(ifstream &file, string name, unsigned int width)
{
    unsigned char *byte21, *byte22, *byte23, *byte24;

    unsigned int height = 0;

    //create new dynamic arrays
    // to hold information on width and height
    byte21 = new(nothrow)unsigned char[1];
    byte22 = new(nothrow)unsigned char[1];
    byte23 = new(nothrow)unsigned char[1];
    byte24 = new(nothrow)unsigned char[1];
    file.seekg(20, ios::beg);

    //seek and read the correct bytes
    file.read((char*)byte21, 1);
    file.seekg(21, ios::beg);
    file.read((char*)byte22, 1);
    file.seekg(22, ios::beg);
    file.read((char*)byte23, 1);
    file.seekg(23, ios::beg);
    file.read((char*)byte24, 1);
    //using bitwise operations store 
    //the information needed to create the int.
    height = byte21[0];
    height = height << 8;
    height = height | byte22[0];
    height = height << 8;
    height = height | byte23[0];
    height = height << 8;
    height = height | byte24[0];
    //close file so we can name change
    file.close();
    pngnamechange(name, width, height);
    //delete all dynamic arrays
    delete[]byte21;
    delete[]byte22;
    delete[]byte23;
    delete[]byte24;
    return;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function gains the height, the width and the name of the png image.
* The function then appends details of the image to the name. This function
* then adds the .png image extension at the end of the new name. The new name
* that is created appends the height and the width to the files name and adds
* the extension. 

*
* @param[in]      width - The width of the image
* @param[in]      name- The name of the file in string form. 
* @param[in]      height- the height of the image
*


* 
*
*****************************************************************************/
void pngnamechange(string name, unsigned int width, unsigned int height)
{
    int result;
    string newname;
    // Appending to create the new name.
    // with width and height information added. 
    newname = name;
    newname += "_";
    newname += to_string(width);
    newname += "_x_";
    newname += to_string(height);
    newname += ".png";





    result = rename(name.c_str(), newname.c_str());
    //if there is an error in renaming show error message
    //output error message
    if (result != 0)
    {
        cout << "Error renaming file " << name << " to " << newname << endl;
    }

    return;

}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function gains the height, the width and the name of the gif image.
* The function then appends details of the image to the name. This function
* then adds the .gif image extension at the end of the new name. The new name
* that is created appends the height and the width to the files name and adds
* the extension. 

*
* @param[in]      width - The width of the image
* @param[in]      name- The name of the file in string form. 
* @param[in]      height- the height of the image
*


* 
*
*****************************************************************************/
void gifnamechange(string name, unsigned int height, unsigned width)
{
    int result;
    string newname;
    // Appending to create the new name.
    // with width and height information added. 
    newname = name;
    newname += "_";
    newname += to_string(width);
    newname += "_x_";
    newname += to_string(height);
    newname += ".gif";
    //get the result if a 0 then rename failed. 
    result = rename(name.c_str(), newname.c_str());
    
  
    
    //if there is an error in renaming show error message
    //output error message
    if (result != 0)
    {
        cout << "Error renaming file " << name << " to " << newname << endl;
    }

    return;
}