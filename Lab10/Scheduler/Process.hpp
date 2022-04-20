// Process.hpp
// Colin Fullum
// 4-8-2022
#ifndef PROCESS_HPP_
#define PROCESS_HPP_


#include <string>

class State;

//Process class
class Process{
public: 
    Process();
    void dispatch(); //ready to running
    void suspend();//running to ready
    void block();  //running to blocked
    void unblock();//blocked to ready
    void exit(); //running to done

    Process* clone();

    void changeState(State* state) { state_ = state; } //changes state of process 

    State* getState() const { return state_; }
    std::string getProcessName()const { return "Process " + std::to_string(id); }
    void report() const;
private: 
    State* state_; //reference to state of object
    static int number; //keeps track of how many processes there are
    int id; 
};

//Base state class with default implementation
class State{
public:
    virtual void dispatch(Process*){} //ready to running
    virtual void suspend(Process*){} //running to ready
    virtual void block(Process*){} //running to blocked
    virtual void unblock(Process*){} //blocked to ready
    virtual void exit(Process*){} //running to done
    virtual std::string report()=0;  

    void changeState(Process* p, State* s){ p->changeState(s); }
};

//Ready state singleton
class Ready : public State{
public:
    static State* instance(){
        static State* onlyInstance = new Ready;
        return onlyInstance;
    }
    // state change to running
    void dispatch(Process* p) override; 
    std::string report() override { return "Ready "; }
private:
    Ready(){}
};

//Running state singleton
class Running : public State{
public:
    static State* instance(){
        static State* onlyInstance = new Running;
        return onlyInstance;
    }
    // State changes to:
    // Ready
    void suspend(Process* p) override;
    // Blocked
    void block  (Process* p) override;
    // Terminated
    void exit   (Process* p) override;
    std::string report()   override { return "Running "; }
private:
    Running(){}

};
//Blocked state singleton
class Blocked : public State{
public:
    static State* instance(){
        static State* onlyInstance = new Blocked;
        return onlyInstance;
    }
    //state change to Ready
    void unblock(Process* p) override;
    std::string report()   override { return "Blocked "; }
private:
    Blocked(){}

};



#endif