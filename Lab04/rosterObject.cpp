// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

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

   string getName(){return firstName_ + " " + lastName_; }

   void addCourse(string class_name){ courses_.push_back(class_name); }

   void print() const { 
      cout << firstName_ + ' ' + lastName_ << ": ";
      for(const string& course : courses_)
         cout << course << " ";
      cout << endl;
   }

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
   list<string> courses_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);
   }

   // list of courses of students
   list<Student> students;

   for(int i = 1; i < argc - 1; ++i){
      readRoster(students, argv[i]);
   }
   
   students.sort();
   printRoster(students);

}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last, courseName;
   courseName = fileName.substr(0, fileName.size() - 4); //get rid of the last 4 characters, since it is ".txt"
   while (course >> first >> last) {
      bool isFound = false; //check if student is already in the list
      for (auto& student : roster) {
         if (student.getName() == first + " " + last) { //if it is then add the course
            isFound = true;
            student.addCourse(courseName);
         }
      }
      if (!isFound) { //if the student is not in the course create a new student with the name
         Student newStud(first, last); 
         newStud.addCourse(courseName); 
         roster.push_back(newStud);
      }
   }
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
   cout << "printing roster: " << endl;
   for(const auto& student : roster)     
      student.print();
}
