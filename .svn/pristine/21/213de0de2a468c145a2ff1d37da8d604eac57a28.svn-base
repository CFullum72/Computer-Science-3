// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 9/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include<algorithm>
#include <functional>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string; using std::vector; using std::deque;
using std::bind; 

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};

//to add
class JamIt{
   public:
      JamIt(double weight = 0): jamWeight(weight) {}
      void operator() (vector<Peaches> myPeaches, double MaxJam){
         Peaches toAdd;
         Peaches temp = std::accumulate(myPeaches.begin(), myPeaches.end(), toAdd, [](Peaches p, Peaches q){   
            Peaches tmp;
            tmp.weight = p.weight + q.weight;
            tmp.ripe = p.ripe && q.ripe;
            return tmp;
         });
         jamWeight = temp.weight;
         if(jamWeight > MaxJam) jamWeight = MaxJam;
         cout << "The weight of Jam is: " << jamWeight;

      }
   private:
      double jamWeight = 0;
};

int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   std::generate(basket.begin(), basket.end(),[=](){
      Peaches tmp;
      tmp.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      tmp.ripe = rand() % 2;
      return tmp;
   });

   // for_each() possibly
   cout << "all peaches"<< endl;
   for_each(basket.begin(), basket.end(), [](Peaches a){ a.print(); });   
   


   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;
   std::remove_copy_if(basket.begin(),basket.end(), peck.begin(), [](Peaches &p){return p.ripe; });


   // for_each() possibly
   cout << "peaches remainng in the basket"<< endl;
   for_each(basket.begin(), basket.end(), [](Peaches a){ a.print(); });   


   cout << endl;

   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
   for_each(peck.begin(), peck.end(), [](Peaches a){ a.print(); });   



   // prints every "space" peach in the peck
   // 
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no iterator arithmetic
   auto it=peck.cbegin(); int i = 0;   
   while(it != peck.cend()){
      if(i == space) it->print();
      std::advance(it, 1);
      ++i; 
   }


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 20.0;
   
   JamIt myJam;

   auto JamTime = bind(myJam, basket, std::placeholders::_1);

   JamTime(weightToJam);

   //cout << "Weight of jam is: " << myJam.getJamWeight() << endl;

}



