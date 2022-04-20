// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// 11/15/2016

#include <iostream>
#include <string>

using std::cout; using std::endl; using std::string;

enum class DrinkType {small, medium, large};

class Drink{
public:
   Drink(DrinkType type = DrinkType::small, int price = 0):type_(type), price_(price){}
   virtual int getPrice() const=0;
   virtual std::string getName() const=0;

protected:
   int price_; //price of drink
   DrinkType type_;
};

//Derived Coffee class
class Coffee : public Drink {
public:
   Coffee(DrinkType type = DrinkType::small) : Drink(type) {
      switch (type_) {
      case DrinkType::small :
         price_ = 5;
         name_ = "Small Coffee";
         break;
      case DrinkType::medium : 
         price_ = 7;
         name_ = "Medium Coffee";
         break;
      case DrinkType::large :
         price_ = 10;
         name_ = "Large Coffee";
         break;
      default:
         break;
      }
   }

   int getPrice() const override { return price_; }
   string getName() const override{ return name_ + " with "; }
private:
   string name_;
};

//Decorators
class Sugar : public Drink{
public:
   Sugar(Drink* wrapped) : wrapped_(wrapped) {}

   int getPrice()const override{ return wrapped_->getPrice() + 1; }
   string getName() const override { return wrapped_->getName() + "Sugar, "; }
private:
   Drink* wrapped_;
};

class Cream : public Drink{
public:
   Cream(Drink* wrapped) : wrapped_(wrapped) {}

   int getPrice()const override{ return wrapped_->getPrice() + 2; }
   string getName() const override { return wrapped_->getName() + "Cream, "; }
private:
   Drink* wrapped_;
};

class Milk : public Drink{
public:
   Milk(Drink* wrapped) : wrapped_(wrapped) {}

   int getPrice()const override{ return wrapped_ ->getPrice() + 3; }
   string getName() const override { return wrapped_->getName() + "Milk foam, "; }
private:
   Drink* wrapped_;
};

int main()
{
   Drink* coffee;
   
   cout << "Welcome to Coffee Shack \n";
   cout << "What size coffee would you like? [s]mall, [m]edium, or [l]arge: ";
   char size; std::cin >> size;
   
   //size controller
   if(size == 's') coffee = new Coffee(); //is defaulting to small in constructor
   else if (size == 'm') coffee = new Coffee(DrinkType::medium);
   else if (size == 'l') coffee = new Coffee(DrinkType::large);
   
   //time to decorate
   char topping;
   do {
      cout << "What toppings do you want? [s]ugar, [c]ream, [m]ilk foam, [d]one: ";
      std::cin >> topping;
      if(topping == 's') {coffee = new Sugar(coffee); }
      else if(topping == 'c') { coffee = new Cream(coffee); }
      else if (topping == 'm') { coffee = new Milk(coffee); }

   } while (topping == 's' || topping == 'c' || topping == 'm');
   
   cout << "What is your name? ";
   string name; std::cin >> name;

   cout << name + " ordered a " + coffee->getName() + "it will cost $" + std::to_string(coffee->getPrice()) << endl;
   return 0;
}
