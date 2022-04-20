// figures: class adapter pattern
// Mikhail Nesterenko
// 2/16/2014

#include <iostream>

using std::cout; using std::endl;

// base interface
class Figure {
public:
   virtual void draw()=0;
   virtual int size() = 0;
   virtual void resize(int newSize) =0;
   virtual ~Figure(){}
};

// adaptee/implementer
class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, 
		   int topLeftY, 
		   int bottomRightX, 
		   int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}

   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
      topLeftX_ = topLeftX;
      topLeftY_ = topLeftY;
      bottomRightX_ = bottomRightX;
      bottomRightY_ = bottomRightY;
   }

   void oldDraw(){
      for(int i=0; i < bottomRightY_; ++i){
	 for(int j=0; j < bottomRightX_; ++j)
	    if(i >= topLeftY_  && j >= topLeftX_ )
	       cout << '*';
	    else
	       cout << ' ';
	 cout << endl;
      }
   }
//accessors
int getTopLeftX()     const { return topLeftX_; }
int getTopLeftY()     const { return topLeftY_; }
int getBottomRightX() const { return bottomRightX_; }
int getBottomRightY() const { return bottomRightY_; }


// defining top/left and bottom/right coordinates 
private: 
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter: public Figure, private LegacyRectangle {
public:
   SquareAdapter(int size): 
      LegacyRectangle(0,0,size,size){};
   void draw() override {
      oldDraw();
   }

   int size() override{
      return getBottomRightX() - getTopLeftX();
   }

   void resize(int newSize) override{ 
      move(getTopLeftX(), getTopLeftY(), newSize, newSize);
   }
};


int main(){
   Figure *square = new SquareAdapter(5);
   square->draw();

   cout << "The current size is: " <<square->size() << ". Enter a new size: ";
   int input; std::cin >> input;

   square->resize(input);

   square->draw();
}
