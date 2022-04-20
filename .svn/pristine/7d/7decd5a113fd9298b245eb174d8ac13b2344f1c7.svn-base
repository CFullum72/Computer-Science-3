#include <iostream>
#include <vector>
#include "Process.hpp"

int Process::number = 0;

//Process Class implementation
Process::Process(){
    //increase the number of Processes, set that id to the number
    ++number; id = number; 
    //initialize the state to Ready;
    state_ = Ready::instance();
}

//changing state functions
void Process::dispatch() { state_->dispatch(this); }
void Process::suspend()  { state_->suspend(this); }
void Process::block()    { state_->block(this); }
void Process::unblock()  { state_->unblock(this); }
void Process::exit()     { state_->exit(this); }

void Process::report() const { std::cout <<  getProcessName() + " is " + state_->report() << '\n' ; }

//Ready class implementation
void Ready::dispatch(Process *p) { std::cout<< "Dispatching " << p->getProcessName() <<"... \n"; p->changeState(Running::instance()); } //to running

//Running class implementation
void Running::suspend(Process *p){ std::cout<< "Suspending " << p->getProcessName() <<"... \n"; p->changeState(Ready::instance()); } //to ready
void Running::block(Process *p){ std::cout << "Blocking " << p->getProcessName() <<"... \n"; p->changeState(Blocked::instance()); }  //to blocked
void Running::exit(Process *p){ std::cout << "Terminating " << p->getProcessName() <<"... \n"; delete p;  }  //exit

//Blocked Class implementation
void Blocked::unblock(Process *p){ std::cout << "Unblocking " << p->getProcessName() <<"... \n"; p->changeState(Ready::instance()); } //to ready

////////////////////////////// MAIN FUNCTION ////////////////////////////////////// 

int main() {
    //vector of processes
    std::vector<Process*> processes;
    std::cout << "How many processes do you want to run? ";
    int num; std::cin >> num;

    //populate vector
    for(int i =0; i < num; ++i) 
        processes.push_back(new Process);

    bool isDeleted;
    for(auto p : processes) {
        isDeleted = false;
        while (!isDeleted) {
            p->report();

            std::cout << "What would you like to do?\nDisptach, Suspend, Block, Unblock or exit [d/s/b/u/e]: ";
            char userInput; std::cin >> userInput; //get input and make it lower case

            switch (userInput) {
            case 'd':
                p->dispatch(); break;
            case 's':
                p->suspend(); break;                
            case 'b':
                p->block(); break;
            case 'u':
                p->unblock(); break;
            case 'e':
                p->exit(); isDeleted = !isDeleted; break;
            default:
                break;
            }
        }
    }
    return 0;
}