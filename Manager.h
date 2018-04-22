#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
using namespace std;
class Manager
{
    public:
        Manager();
        Manager(string newName);
        
        string getName();
        void setName(string newName);


        ~Manager();
    private:
        string name;
};
#endif// MANAGER_H