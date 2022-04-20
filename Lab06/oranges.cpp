// selecting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 2/17/2020


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>
#include <utility>

using std::cin; using std::cout; using std::endl;
using std::string;   using std::multimap;
using std::vector;   

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

int main(){
   srand(time(nullptr));
   int randomNum = rand()%100 + 1;
   multimap<Variety, string> tree; 

   for(int i = 0; i < randomNum; ++i)
      tree.emplace(static_cast<Variety>(rand()%3), colors[rand()%3]); //fill tree with random fruit and colors

   cout << "The color of oranges:" << endl;
   for(auto f = tree.lower_bound(Variety::orange); f != tree.upper_bound(Variety::orange); ++f)
      if(f->first == Variety::orange) cout << f->second <<  endl; //only print out oranges


}

