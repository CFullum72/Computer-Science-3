// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
   Fill(char borderChar, char internalChar):borderChar_(borderChar), internalChar_(internalChar){}
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char borderChar_;
   char internalChar_;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char fillChar):Fill(fillChar, ' '){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return internalChar_;}
   ~Hollow(){}
};


// another concrete body
class Filled: public Fill {
public:
   Filled(char fillChar):Fill(fillChar, fillChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return internalChar_;}
   ~Filled(){}
};

class FullyFilled: public Fill{
public:
   FullyFilled(char fillChar, char internalChar): Fill(fillChar, internalChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return internalChar_;}
   ~FullyFilled(){}
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};

void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}

int main(){
   Figure* userBox;
   int size = 6;
   //Draw a Hollow Square
   cout << "Hollow Square\n";
   userBox = new Square(size, new Hollow('*'));
   userBox->draw();
   //Draw a filled square
   cout << "Filled Square\n";
   userBox = new Square(size, new Filled('/'));
   userBox->draw();
   //Draw a fully Filled square
   cout << "Fully FIlled Square\n";
   userBox = new Square(size, new FullyFilled('~', 'o'));
   userBox->draw();
}
