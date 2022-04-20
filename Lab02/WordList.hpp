#ifndef WORDLIST_HPP_
#define WORDLIST_HPP_
 
#include <string>

 using std::string;
 
class WordOccurrence {
public:
    WordOccurrence(const string& word="", int num=0){
      word_ = word;
      num_ = num;
    };
    
    //used in addword()
    bool matchWord(const string& rhs){ return word_ == rhs; } // returns true if word matches stored
    void increment() { ++num_; }; // increments number of occurrences
    string getWord() const { return word_; }
    int getNum() const { return num_; }
private:
    string word_;
    int num_;
};

class WordList{
public:
  WordList() {
    size_ = 0;
    wordArray_ = new WordOccurrence [size_];
  }
  //copy constructor
  WordList(const WordList&);
  //destructor
  ~WordList() { delete [] wordArray_; }
  //overloaded assignment
  WordList& operator=(WordList rhs){ //call by value to create copy
    swap(*this, rhs); //use swap friend function to swap the member variables
    return *this;
  }
  friend void swap(WordList& a, WordList& b){
    std::swap(a.size_, b.size_);
    std::swap(a.wordArray_, b.wordArray_);
  }
  // implement comparison as friend
  friend bool equal(const WordList& a, const WordList& b){ return (a == b); }
  friend bool operator== (const WordList&, const WordList&);

  void addWord(const string &); //adds a word to the array
  void print(); //prints array and number of occurances
  void sort(); //sort the array based on the number of occurences
private:
  WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
  // may or may not be sorted
  int size_;
};


//copy constructor
WordList::WordList(const WordList& w) {
  size_ = w.size_;
  if(size_ > 0) wordArray_ = new WordOccurrence[size_];
  else wordArray_ = nullptr;
  for(int i = 0; i < size_ ; ++i) {
    wordArray_[i] = w.wordArray_[i];
  }
}

bool operator== (const WordList& lhs, const WordList& rhs){
  if(lhs.size_ != rhs.size_) return false;
  for(int i = 0; i < lhs.size_; ++i){
    if(lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord()) return false;
  } 
  return true;
}

void WordList::addWord(const string& str){
  bool isFound = false; //flag to see if the word is already in the array
  for(int i = 0; i < size_; ++i){
    if(wordArray_[i].matchWord(str)){ //use matchword() to check
      wordArray_[i].increment(); //use increment to increase the count
      isFound = true; //set flag 
    }  
  }
  //if it is not found create new array of size [size + 1], copy the 
  //element over, add the word to the list, and then delete the old array.
  if(!isFound){
    WordOccurrence *temp = new WordOccurrence[size_ + 1];
    for(int i = 0; i < size_; ++i){
      temp[i] = wordArray_[i];
    }
    WordOccurrence w(str, 1);
    temp[size_] = w;
    delete[] wordArray_;
    wordArray_ = temp;
    ++size_;
  }
}
void WordList::print(){
  sort();
  std::cout << "Word" << "\t\t" << "Occurence" << std::endl;
  for(int i = 0; i < size_; ++i){
    std::cout << wordArray_[i].getWord() << "\t\t" << wordArray_[i].getNum() << std::endl;
  }
}

//sorts the array by order of occurance, with rarest being first
void WordList::sort(){
  for(int i = 0; i < size_; ++i){
    int min = i; //stores the element of the rarest occurenfce

    //loop through the rest of the occurences
    for(int j = i + 1; j < size_; ++j){
      if(wordArray_[min].getNum() > wordArray_[j].getNum()) //check min against rest of elements
        min = j; //if min is greater than j, assign j to min
    }
      WordOccurrence temp = wordArray_[i];
      wordArray_[i] = wordArray_ [min];
      wordArray_[min] = temp;  
  }  
}


#endif
