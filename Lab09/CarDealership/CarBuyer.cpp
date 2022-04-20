// needed for lab
// Mikhail Nesterenko
// 3/18/2022

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <string>
#include "CarFactory.hpp"

using std::array;
using std::cout;
using std::endl;
using std::generate;
using std::string;
using std::vector;

class CarLot{
public:
   CarLot();
   Car *testDriveCar() { return carLot_[currentCar_]; }

   // if a car is bought, requests a new one
   Car *buyCar(){
      // return the current car
      Car *bought = carLot_[currentCar_];
      // erase that car and add a new one in its place
      carLot_.erase(carLot_.begin() + currentCar_);
      carLot_.push_back(factories_[rand() % factories_.size()]->requestCar());
      return bought;
   }

   // returns next car in lot
   Car *nextCar(){
      currentCar_ = ++currentCar_ % LOTSIZE_;
      return carLot_[currentCar_];
   }
   int getLotSize() { return LOTSIZE_; }

private:
   static const int LOTSIZE_ = 10; // size of lot
   static int currentCar_;         // current car that the customer is looking at
   vector<CarFactory *> factories_;
   vector<Car *> carLot_ = vector<Car*> (LOTSIZE_); // vector of the cars in the lot
};

int CarLot::currentCar_ = -1;

CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // fill carLot_ with cars from random factories
   generate(carLot_.begin(), carLot_.end(), [&]() { return factories_[rand() % factories_.size()]->requestCar(); });
}

// lists of possible models that a buy could see
static const array<string, 5> ToyotaModels{"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
static const array<string, 4> FordModels{"Focus", "Mustang", "Explorer", "F-150"};

CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota and is right model
void toyotaLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   string desiredModel = ToyotaModels[rand() % ToyotaModels.size()];
   
   // go through each car in the lot
   for (int i = 0; i < carLotPtr->getLotSize(); ++i){
      Car *toBuy = carLotPtr->nextCar();

      cout << "Jill Toyoter number " << id << endl;
      cout << "is test driving a " << toBuy->getMake() << " " << toBuy->getModel();

      if (toBuy->getMake() == "Toyota" && toBuy->getModel() == desiredModel)
      {
         cout << " They love it! They are buying it!" << endl;
         carLotPtr->buyCar();
      }
      else
         cout << "They did not like it!" << endl;
   }
}

// test-drives a car
// buys it if Ford and if is right model
void fordLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   string desiredModel = FordModels[rand() % FordModels.size()];
   for (int i = 0; i < carLotPtr->getLotSize(); ++i){
      Car *toBuy = carLotPtr->nextCar();

      cout << "Jack Fordman number " << id << endl;
      cout << " is test driving a " << toBuy->getMake() << " " << toBuy->getModel();

      if (toBuy->getMake() == "Ford" && toBuy->getModel() == desiredModel){
         cout << " They love it! They are buying it!" << endl;
         carLotPtr->buyCar();
      }
      else
         cout << " They did not like it!" << endl;
   }
}

int main(){
   srand(time(nullptr));
   const int numBuyers = 10;

   for (int i = 0; i < numBuyers; ++i)
      if (rand() % 2 == 0)
         toyotaLover(i);
      else
         fordLover(i);

}
