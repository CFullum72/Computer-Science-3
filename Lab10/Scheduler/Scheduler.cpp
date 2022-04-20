#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <deque>
#include "Process.hpp"




class Scheduler {
public:
    Scheduler() {
        prototype = new Process();
    }

    void report();
    void createProcess();
    void run(int);

private:
   Process* prototype;
   std::deque<Process*> processes;
   std::queue<Process*> ready;
   std::queue<Process*> blocked;
};

void Scheduler::report() {
    for(Process* p : processes) {
        if(p != nullptr){
            std::cout << ' ';
            p->report();
        }
    }
    std::cout << '\n';
}

void Scheduler::createProcess() {
    Process* tmp = prototype->clone();
    ready.push(tmp);
    processes.push_back(tmp);
}

void Scheduler::run(int number) {
    srand(time(nullptr));
    //populate ready with processes via protoype
    for(int i = 0; i < number; ++i)
        createProcess();

    report(); 
    
    for(int i = 0; i < number; ++i) {
        
        //There is a 50% chance that a process will unblock
        if(rand() % 2 && !blocked.empty()){ 
            Process* p = blocked.front();
            blocked.pop();
            p->unblock();
            ready.push(p);
            std::cout << p->getProcessName() << " is has unblocked\n";
        }


        Process* p = ready.front(); //get a pointer to front of queue
        ready.pop(); 
        p->dispatch(); //set to running state
        p->report();

        //pick the transition randomly
        int random = rand() % 3;
        switch (random) {
        case 0: //exit
            std::cout << "Exiting . . .\n";
            processes.erase(remove(processes.begin(), processes.end(), p), processes.end());
            delete p;
            break;
        case 1: //block
            std::cout << "Blocking . . .\n";
            p->block();
            blocked.push(p);
            break;
        case 2: //suspend
            std:: cout << "Suspending . . .\n";
            p->suspend();
            ready.push(p);
            break;
        default:
            break;
        }

        report();
    }



}



////////////////////////  MAIN FUNCTION //////////////////////////////

int main() {    
    Scheduler s;
    
    s.run(4);

    return 0;
}
