/*
 * Colin Fullum
 * Diff.cpp
 * Computer Science III
 * Lab 1 
 * 
 * This program takes two text files as arguments and compares them
 * It shows when a difference occurs between the two files
 */

#include <iostream>
#include <string>
#include <fstream>

using std::cout; using std::endl; using std::cin; using std::string;
using std::ifstream;

int main(int argc, char const *argv[])
{
    cout << endl;
    //make sure there is 
    if(argc != 3){
        cout << "please run program with 2 .txt files"; return 0;
    }
    
    //ifstream for each file
    ifstream file1(argv[1]);
    ifstream file2(argv[2]);
    string f1, f2;
    int spacing, line = 1;
    //a variable to follow to the current line in the code

    if(!file1.is_open()){ 
        cout << argv[1] << " was not able to be opened" << endl; return 0;
     }
    if(!file2.is_open()){ 
        cout << argv[2] << " was not able to be opened" << endl; return 0;
     }

    //loop until at the end of both files
     while(!file1.eof() && !file2.eof()){

        //find out the spacing on this line
        //beside the line number the output has 15 characters
        spacing = 15;

        //the has the number of spaces necessary to start the '^' starts in the
        //correct positison. it creates a string of the size of 15 + how ever many
        //digits are in the line number, and ten fills the string with spaces
        string spaces(spacing + std::to_string(line).length(), ' ');

        //if at the end of the file of one file and not the other
        //the comparable string should be empty, other wise just 
        //store the line into the f1 and f2 variable to be compared

        if(file1.eof()) f1 = "";
        else getline(file1, f1);

        if(file2.eof()) f2 = "";
        else getline(file2, f2);

        //first check to see if the files are the same, if they are not
        //then compare each character
        if(f1 != f2){

            //display each line of the text document
            cout << "File 1: Line " << line << ": " << f1 << endl;
            cout << "File 2: Line " << line << ": " << f2 << endl;

            //now find where the '^' goes to determine the character that differs between the two strings
            //use 'i' as a tracker and loop through each string until they are different.
            int i = 0;
            while (f1[i] == f2[i]) {
                ++i;
            }

            string test(i, ' ');

            cout << spaces << test << "^" << endl;
        }
        ++line;
     }

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;


    //close the files
     file1.close();
     file2.close();
     return 0;
}

