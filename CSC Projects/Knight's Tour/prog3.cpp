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
 * @details This program is the knight's tour. Which is a game that
 * is used with a knight of the game chess. In chess the knight may only
 * move in an L shape and 3 spaces. So 2 spaces up 1 space to the right 
 * or left. Or 1 space up and 2 over. In the knight's tour this game is 
 * to find a solution for a knight to move in all available spaces. So 
 * for a 4x4 board there would be 16 squares. So the knights must 
 * complete a tour to all spaces without entering
 * a space the knight has already entered. 
 *
 *  This progam follows the rules that were given instead of a user 
 * entering the details of what is needed a file is read with the size
 *  of the board & and the position the knight. The program checks
 * to make sure there is the proper amount of arguments and then saves
 * the data to make the correct board size and starting position.
 * After creating the board using a dynamic 2D array the knight goes
 * through his tour. If the knight is unable to find a tour that enters
 * all available spots the solution is no solution.
 * If the knight does make it to all available solutions the solution
 * is printed into a new created txt file. The name of the new txt file
 * will be puzzle_nameout.txt . Once all puzzles are completed
 * the program returns 0 and ends. 
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
   c:\> prog3.exe puzzle_file.extension
   
   
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
   4/08/2016        Started with arguments and pseudocode 
   4/10/2016        Finished recursion on knight's tour
   4/14/2016        Finished renaming the file. 
   4/14/2016        Doxygen
   @endverbatim
 *
 *****************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
void pad0(int**arr, int n);
bool move(int **arr, int startrow, int startcol, int n, int count);
void createarr(int size, int startrow, int startcol, string name, 
    int amount);
void printsol(string name, int **arr, int size, int startpos, int startcol, 
    bool result, int amount);
void del(int **arr, int n);
void pad(int **arr, int row, int col);
void naming(string name, string *newname);

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function is main it is the start of the program it takes in arguments
that will tell it to open which file to open to solve the puzzles for the
knights tour.
It connects to all other functions.
It will end once the other functions have completed their tasks.




*
* @param[in]      argc  - argument count from program starting
* @param[in]      argv  - contains the arguments
*
* @returns 1 error
* @returns 0 program ran successful.
* 
* 
*
*****************************************************************************/
int main(int argc, char *argv[])
{
    //create variables
    ifstream fin;
    int n;
    int count = 0;
    string name;
    int size = 0;
    int startrow;
    int amount = 0;
    int startcol;
    
    //Not enough or too little arguments
    if (argc != 2 )
    {
        cout << "Please refer to usage." << endl;
        return 1;
    }
    //grab the name of the file to be open
    name = argv[1];
    //open file
    fin.open(name, ios::in);
    //could not open file
    if (!fin)
    {
        cout << "Couldn't open file: " <<name <<endl;
        return 2;
    }
    //grab the details of the board and position
    while (fin >> n)
    {
        if (count == 0)
        {
            size = n;

        }
        if (count == 1)
        {

            startrow = n;
        

        if (count == 2)
        {
            startcol = n;
        }
        count++;
        if (count > 2)
        {
            
            amount++;
            //go to function to create array
            createarr(size, startrow, startcol, name, amount);

            count = 0;
        }


    }

    cout << "done" << endl;
    return 0;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function creates the dynamic 2D array. It adds 4 to the size of the
 * array to pad the array for easier completion of the knights tour.
 * After the array is created 




*
* @param[in]      size  - the amount of rows, columns
* @param[in]      startrow- the starting postion for row
* @param[in]      startcol- the starting position for column
* @param[in]      name - the string name of file
* @param[in]      amount- the puzzle case
*
* 
* 
* 
*
*****************************************************************************/
void createarr(int size, int startrow, int startcol, string name, 
    int amount)
{


    bool result;
    string newname;
    int i;
    int n = size + 4;
    int count = 1;
    //create dynamic 2D array
    int** ary = new int*[size + 4];
    for (i = 0; i < size + 4; ++i)
        ary[i] = new int[size + 4];
    // pad the full 2D array with 0's
    pad0(ary, size + 4);
    //pad the 2D array in certain areas with a -1.
    pad(ary, size + 4, size + 4);
    // go to function that moves the knight using recursion
    result = move(ary, startrow + 2, startcol + 2, size, 1);
    //name the new file
    naming(name, &newname);
    //print the solutions for the puzzle in the new file
    printsol(newname, ary, size, startrow, startcol, result, amount);

    // go to function to delete the array
    del(ary, size + 4);
    return;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function prints the solution to the output file. It does this by
 *opening the file if there is an error  it returns with an error message.
 * else it outputs the case number then the starting position of the knight.
 * after this it outputs the solution that is formatted for easy viewing. If
 * there is no solution it outputs that this case has no solution. 




* @param[in]      name - the string name of file
* @param[in]      arr  - the array holding the solution
* @param[in]      size- the size of the array. 
* @param[in]      startpos- the starting postion for row
* @param[in]      startcol- the starting position for column
* @param[in]      result - the true or false if there is a solution
* @param[in]      amount- the puzzle case
*
* 
* 
* 
*
*****************************************************************************/
void printsol(string name, int **arr, int size, int startpos, int startcol, 
    bool result, int amount)
{
    ofstream fout;
    int n = size + 4;
    int i;
    int count = 0;
    //open the new file
    fout.open(name, ios::app);
    if (!fout)
    {
        cout << "Could not open file: " << name << endl;
        return;
    }
    //print the case the starting row and column of the puzzle
    fout << "Case: " << amount << " - " << size << "x" << size << endl;
    fout << "Starting Row: " << startpos << " Start Column: " << startcol
        << endl;

    if (result == true)
    {
        //Print only the board solution not the included -1's of the array.
        //Only the solution.
        for (i = 2; i < n - 2; i++)
        {


            for (int a = 2; a < n - 2; a++)
            {

                {

                    if (count < n - 2)
                    {
                        fout <<setw(5)<< arr[i][a] << " ";
                        count++;
                    }
                    if (count >= size)
                    {
                        fout << endl;
                        count = 0;
                    }
                }

            }





        }
    }
    else
    {
        fout << "No solutions for this case." << endl;
    }
    fout << endl;
    return;
}
/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function creates the name for the new file to save the solutions to.
 * This function takes the old file name removes the extension which is after
 * the last dot and then appends out.txt to the new name.
 * Example knights.pz would become knightsout.txt.




*
* @param[in]      name  - the old name
* @param[in]      newname- the newname txt format
*
* 
* 
* 
*
*****************************************************************************/
void naming(string name, string *newname)
{
    //find the last dot for the extension
    int firstdot = name.find_last_of(".");
    *newname = name;
    //erase what is after the first .
    name.erase(firstdot);
    //append
    name.append("out.txt");
    //newname gets name
    *newname = name;
    return;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function creates the dynamic 2D array. It adds 4 to the size of the
 * array to pad the array for easier completion of the knights tour.
 * After the array is created it returns to the previous function




*
* @param[in]      **arr  - the array for knights tour
* @param[in]      n      - the amount of rows and columns.
* 
*
* 
* 
* 
*
*****************************************************************************/
//do this first pad all elements in array with 0
void pad0(int**arr, int n)
{
    int i = 0;
    int a = 0;
    int b = 0;
    //pad 0's
    for (i = 0; i < n; i++)
    {
        for (a = 0; a < n; a++)
        {
            arr[i][a] = 0;
        }
    }
    return;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function pads -1 to the surrounding rows and columns that would not be
 * a part of the solution. For example a 6*6 would be an 8*8 and and the
 * portions of the array surrounding the 6*6 portion would contain a -1
 * instead of a 0.




*
* @param[in]      arr  - the array
* @param[in]      row- the amount of rows
* @param[in]      col - the amount of columns
*
* 
* 
* 
*
*****************************************************************************/
//pad certain items with -1
void pad(int **arr, int row, int col)
{
    int i = 0;
    int a = 0;
    int b = 0;
    //Pad the row 0 to 2 with -1
    for (i = 0; i < 2; i++)
    {
        for (a = 0; a < col; a++)
        {
            arr[i][a] = -1;
        }
    }
    //pad all rows but 2 first cols and last 2 cols with -1
    for (i = 2; i < row; i++)
    {
        for (a = 0; a < 2; a++)
        {
            arr[i][a] = -1;

        }
        for (b = col - 2; b < col; b++)
        {
            arr[i][b] = -1;
        }
    }

    //pad last two rows with -1
    for (i = (row - 2); i < row; i++)
    {
        for (a = 0; a < col; a++)
        {
            arr[i][a] = -1;
        }
    }
    return;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
* This function moves the knight to the the correct square. The knight follows
* the strict guideline given in the documentation for the program. The first
* move is up 2 and to the left by one then following a clockwise pattern
* are the next moves. If the knight ever gets stuck it returns to the previous
* move and continues to do so until a solution is found. If no solutions are
* found the function returns false and continues until all moves are given
* a try. If solution is found the function ends and returns true. 



*
* @param[in]      arr  - the array for the board
* @param[in]      startrow- the starting postion for row
* @param[in]      startcol- the starting position for column
* @param[in]      n - the amount of rows/columns for base case
* @param[in]      count- the move the knight is on i.e. 1,2,3etc. 
*
* 
* @returns      true - there is a solution
* @returns      false - there is no solution or there is no solution at this
move
* 
*
*****************************************************************************/
bool move(int **arr, int startrow, int startcol, int n, int count)
{
    bool result = false;
    arr[startrow][startcol] = count;
    //found a solution
    if (count == (n*n))
    {
        return true;
    }
    //first move
    if (arr[startrow - 2][startcol - 1] == 0)
    {

        result = move(arr, startrow - 2, startcol - 1, n, count + 1);
        //if false there was no moves after this move change the 
        //to a 0. Continue on. Each move has this to change the move
        // to 0 if needed. So that a new move can enter that space. 
        if (result == false)
        {
            arr[startrow - 2][startcol - 1] = 0;

        }
    }
    //second move
    if (arr[startrow - 2][startcol + 1] == 0)
    {
        result = move(arr, startrow - 2, startcol + 1, n, count + 1);
        if (result == false)
        {
            arr[startrow - 2][startcol + 1] = 0;
        }
    }
    //third move
    if (arr[startrow - 1][startcol + 2] == 0)
    {

        result = move(arr, startrow - 1, startcol + 2, n, count + 1);
        if (result == false)
        {
            arr[startrow - 1][startcol + 2] = 0;
        }
    }
    //fourth move
    if (arr[startrow + 1][startcol + 2] == 0)
    {
        result = move(arr, startrow + 1, startcol + 2, n, count + 1);
        if (result == false)
        {
            arr[startrow + 1][startcol + 2] = 0;
        }
    }
    //fifth move
    if (arr[startrow + 2][startcol + 1] == 0)
    {
        result = move(arr, startrow + 2, startcol + 1, n, count + 1);
        if (result == false)
        {
            arr[startrow + 2][startcol + 1] = 0;
        }
    }
    //sixth move
    if (arr[startrow + 2][startcol - 1] == 0)
    {
        result = move(arr, startrow + 2, startcol - 1, n, count + 1);
        if (result == false)
        {
            arr[startrow + 2][startcol - 1] = 0;
        }
    }
    //seventh move
    if (arr[startrow + 1][startcol - 2] == 0)
    {
        result = move(arr, startrow + 1, startcol - 2, n, count + 1);
        if (result == false)
        {
            arr[startrow + 1][startcol - 2] = 0;
        }
    }
    //eighth move
    if (arr[startrow - 1][startcol - 2] == 0)
    {
        result = move(arr, startrow - 1, startcol - 2, n, count + 1);
        if (result == false)
        {
            arr[startrow - 1][startcol - 2] = 0;
        }
    }
    return result;
}

/**************************************************************************//**
* @author Paul Hertfelder
*
* @par Description:
 *This function deletes the dynamic array to free up memory. After
 * deleting the array the function returns




*
* @param[in]      arr  - the array that needs to be deleted
* @param[in]      n- the amount of rows/columns

*
* 
* 
* 
*
*****************************************************************************/
void del(int **arr, int n)
{
    //delete the array
    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    //delete
    delete[] arr;
    return;
}




