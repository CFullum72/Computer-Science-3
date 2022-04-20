// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014
/*
takes lists of students from .txt files and puts them into a list of lists
LIST<LIST<STRING>>
ROSTER
[
LIST 1  ["Mike Smith", "cs1" , "cs2", "cs3"]
LIST 2  ["Susan Sue", "cs1" , "cs2", "dropouts"]
LIST 3  ["Bobby Roberts", "cs1"]
]
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(list<list<string>>& roster, string fileName);  

// printing a list out
void printRoster(const list<list<string>>& roster); 

//removes dropouts from list
void dropoutRemover(list<list<string>>& roster);

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl; exit(1);
   }

   //list, containing lists of strings of student's names and courses
   list<list<string>> students; 

   for(int i = 1; i < argc; ++i){
      readRoster(students, argv[i]);
   }
   students.sort();
   printRoster(students);

}

// places in a file of names into a list of strings
void readRoster(list<list<string>>& roster, string fileName){

   ifstream course(fileName); //create an input stream

   string firstname, lastname, courseName;

   //delete the last four chars of the string to get rid of the file extension
   courseName = fileName.erase(fileName.size() - 4);
   
   while(course >> firstname >> lastname){
      bool nameFound = false; //flag to see weather or not to continue search through roster for name
      string studentName = firstname + ' ' + lastname;
      //loop through the list with range base for to compare name with lists. 
      for(auto &l :roster){
         //l is type list<student>, l.front will return student (see format at top of file)
         if(l.front() == studentName){ //if names match
            l.push_back(courseName);   //add name to list
            nameFound = true;          //set flag to true
            break;                     //break from loop
         }                   
      }
      //if not in the roster, add student and course to a new list
      if(!nameFound){
         list<string> temp; //create list 
         temp.push_back(studentName); //add student and course to list
         temp.push_back(courseName);
         roster.push_back(temp); //push the new list into the main list
      }
   }     
   course.close();
}

// printing a list out
void printRoster(const list<list<string>>& roster){
   int i = 1;
   //for each string in the list print it out
   for(const auto & l : roster){
      cout << i << ".) ";
      for(const auto& str : l)
         cout << str << " ";
      cout << endl;
      ++i;
      }
}

