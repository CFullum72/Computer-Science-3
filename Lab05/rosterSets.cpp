// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

/*
   this map uses the same student class as Lab04, but implements the program
   using a map.

   the map pair is <student, list of courses>
   student is the key
*/



#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>
#include <set>

using std::ifstream;
using std::string; using std::getline;
using std::list;   using std::vector;
using std::cout;   using std::endl;
using std::move;   using std::map;
using std::pair;   using std::set;

class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {return firstName_ + ' ' + lastName_;}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
};




// reading a list from a fileName
void readRoster(set<Student>& roster, string fileName);  
// printing a list out
void printRoster(const set<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

    set<Student> students;

   for(int i = 1; i < argc; ++i)
      readRoster(students, argv[i]);
   
   printRoster(students);

}


void readRoster(set<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last, courseName;
   courseName = fileName.substr(0, fileName.size() - 4); //get rid of the last 4 characters, sicne it is ".txt"
   while(course >> first >> last){
       if(courseName == "dropouts"){
          //remove person
          auto itr = roster.find(Student(first,last));
          roster.erase(itr);
       }
       else{
          //add person
          roster.insert(Student(first,last));
       }
   }
   course.close();
}

// printing a list out
void printRoster(const set<Student>& roster){
   for(const auto& student : roster){
      cout << student.print() << endl;
   }
}
