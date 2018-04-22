#include <iostream>
#include <fstream>
#include "Manager.h"
using namespace std;

Manager::Manager()
{
    name="None";
};
Manager::Manager(string newName)
{
    name=newName;
};
string Manager::getName()
{
    return name;
}
void Manager::setName(string newName)
{
    name=newName;
}
Manager::~Manager()
{
    name="None";
};

