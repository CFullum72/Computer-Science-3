#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include "list.hpp"
#include <iostream>

using std::cout; using std::endl;

template <typename T>
class Collection;

template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
    Collection() : head(nullptr) {}
    void add(T);
    void remove(T);
    T last(){ return head->getData(); }
    void print();
    friend bool equal<T>(const Collection&, const Collection&);
private:
    node<T> *head;
};

//the add function adds an item to the list
//the way I have implemented it is in a first in last out implementation
template <typename T>
void Collection<T>::add(T item){
    node<T> *newNode = new node<T>; //allocate memory for a newNode
    newNode->setData(item); //store item in the data in newNode
    newNode->setNext(head); //set next node to nullptr
    head = newNode; //head then takes on the attributes of newNode.
}

//prints out a list
template <typename T>
void Collection<T>::print(){

    //tracker node pointer
    node<T> *current;

    //start at the head
    current = head;

    //navigate the list until at the end
    while (current != nullptr){
        cout << current->getData() << endl;
        current = current -> getNext();
    }
}

//removes a node fromt the list containing 'item'
template <typename T>
void Collection<T>::remove(T item){
    node<T> *current = head; //keeps track of current node while traversing list, used to compare to item
    node<T> *prevNode = nullptr; //keeps track of the node before current, in order to point to the node after current after deleting current

    //navigate throught the list to find item
    while(current != nullptr){
        if(current == head){
            //if current node is equal to item
            if(current->getData() == item){
                head = head->getNext(); //move head to next node
                delete current;  //delete current node
                current = head; //current and prev(?) to head
            }
        }
        else{
            //if current.data == item increase
            if(current->getData() == item){
                //have prev->current break and point to current.next
                prevNode->setNext(current->getNext());
                //delete current
                delete current;
                //current=prev.next
                current = prevNode->getNext();
            }
        }
        prevNode = current;
        current = current->getNext();
    }
}

template <typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs){

    //use two variables to navigate and compare instead of just one
    node<T> *leftCurrent = lhs.head;
    node<T> *rightCurrent = rhs.head;


    //navigate through loop until either one is null
    while(leftCurrent != nullptr && rightCurrent != nullptr){
        //check if data is different
        if(leftCurrent->getData() != rightCurrent->getData()) return false;
        //navigate to next node in list
        leftCurrent  = leftCurrent->getNext();
        rightCurrent = rightCurrent->getNext();
    }
    
    //check if only one one is null (false)
    if((leftCurrent != nullptr && rightCurrent == nullptr) || 
       (leftCurrent == nullptr && rightCurrent != nullptr)) return false;


    //if all of these tests were pasted, they are equal!
    return true;
}


#endif