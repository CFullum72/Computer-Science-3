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

Process* Process::clone() {
    Process *p = new Process();
    return p;
}

void Process::report() const { std::cout <<  getProcessName() + " is " + state_->report() << '\n' ; }

//Ready class implementation
void Ready::dispatch(Process *p) { std::cout<< "Dispatching " << p->getProcessName() <<"... \n"; p->changeState(Running::instance()); } //to running

//Running class implementation
void Running::suspend(Process *p){ std::cout<< "Suspending " << p->getProcessName() <<"... \n"; p->changeState(Ready::instance()); } //to ready
void Running::block(Process *p){ std::cout << "Blocking " << p->getProcessName() <<"... \n"; p->changeState(Blocked::instance()); }  //to blocked
void Running::exit(Process *p){ std::cout << "Terminating " << p->getProcessName() <<"... \n"; delete p;  }  //exit

//Blocked Class implementation
void Blocked::unblock(Process *p){ std::cout << "Unblocking " << p->getProcessName() <<"... \n"; p->changeState(Ready::instance()); } //to ready

