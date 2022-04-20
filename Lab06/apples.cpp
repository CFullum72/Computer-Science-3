// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 09/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl; using std::string;
using std::vector; using std::deque; using std::generate; using std::for_each;
using std::accumulate; using std::count_if; using std::find_if; using std::remove_if;
using std::max_element; using std::sort; using std::transform;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   
   // assign random weight and color to apples in the crate
   // replace with generate()
   generate(crate.begin(), crate.end(), [=]() { 
      Apples a;
      a.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      a.color = rand()% 2 == 1 ? "green" : "red";

      return a;
      });
   
   //printing crate
   cout << "Printing Apples: \nColor:   Weight:\n";
   for_each(crate.begin(), crate.end(), [](Apples a){ a.print();} );


   

   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()

   int cnt = count_if(crate.begin(), crate.end(), [toFind](Apples a){ return a.weight > toFind; });
   
  // for(auto it = crate.cbegin(); it != crate.cend(); ++it) 
  //    if(it->weight > toFind) ++cnt;
   

   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz ";
   
   // find_if()
   auto it = find_if(crate.begin(), crate.end(), [toFind](Apples a){ return a.weight > toFind; });
   if(it!=crate.end()){
      cout << "Found at positions: ";
      do{
         cout << it - crate.begin() << ' ';
         it = find_if(++it, crate.end(), [toFind](Apples a){ return a.weight > toFind; });
      }while(it != crate.end());
   }

   
   

   // max_element()
   auto heaviest = max_element(crate.begin(), crate.end(), [](Apples a, Apples b){return a.weight < b.weight;});
   cout << "\nHeaviest apple weighs: " << heaviest->weight << " oz" << endl;


   // for_each() or accumulate()
   double sum = 0;
   for_each(crate.begin(), crate.end(), [&sum](Apples a) {sum += a.weight; });
  
   cout << "Total apple weight is: " << sum << " oz" << endl;


   // transform();
   //vector<Apples> crate2;
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   transform(crate.begin(), crate.end(), crate.begin(), [=](Apples a){
      Apples tmp;
      tmp.weight = a.weight + toGrow; 
      tmp.color = a.color;
      return tmp; 
   });



   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
   crate.erase(remove_if(crate.begin(), crate.end(), [minAccept](Apples &a){return a.weight < minAccept; }));

   // bubble sort, replace with sort()
   sort(crate.begin(), crate.end(), [](Apples a, Apples b){return a.weight < b.weight;});

   cout << "Printing Apples: \nColor:   Weight:\n";
   for_each(crate.begin(), crate.end(), [](Apples a){ a.print();} );

}

