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

using std::ifstream;
using std::string; using std::getline;
using std::list;   using std::vector;
using std::cout;   using std::endl;
using std::move;   using std::map;
using std::pair;

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
void readRoster(map<Student, list<string>>& roster, string fileName);  
// printing a list out
void printRoster(const map<Student, list<string>>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   map<Student, list<string>> students;

   for(int i = 1; i < argc -1; ++i)
      readRoster(students, argv[i]);
   
   printRoster(students);

}


void readRoster(map<Student, list<string>>& roster, string fileName){
   ifstream course(fileName);
   string first, last, courseName;
   courseName = fileName.substr(0, fileName.size() - 4); //get rid of the last 4 characters, sicne it is ".txt"
   while(course >> first >> last){
      auto itr = roster.find(Student(first, last)); //find the student, with itr
      if(itr == roster.end()){
         auto result = roster.insert(std::make_pair(Student(first, last), list<string> {courseName}));
      }
      else{
         itr->second.push_back(courseName);
      }
   }
   course.close();
}

// printing a list out
void printRoster(const map<Student, list<string>>& roster){
   for(const auto& student : roster){
      cout << student.first.print() << ' ';
      for(auto const &str : student.second) cout << str << ' ';
      cout << endl;
   }
}
