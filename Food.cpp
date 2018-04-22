#include <iostream>
#include <fstream>
#include "Food.h"
using namespace std;

Food::Food()
{
    taste="NONE";
    name="None";
    ethnicOrigin="None";
    price=-1;
    quantity=-1;
};

Food::Food(string newName, double newPrice, double newQuantity, string newTaste, string newEthnicOrigin)
{
    taste=newTaste;
    name=newName;
    ethnicOrigin=newEthnicOrigin;
    price=newPrice;
    quantity=newQuantity;
};


string Food::getTaste()
{
    return taste;
}
string Food::getName()
{
    return name;
}
string Food::getEthnicOrigin()
{
    return ethnicOrigin;
}

void Food::setTaste(string newTaste)
{
    taste=newTaste;
}
void Food::setName(string newName)
{
    name=newName;
}
void Food::setEthnicOrigin(string newEthnicOrigin)
{
    ethnicOrigin=newEthnicOrigin;
}


Food::~Food()
{
    taste="NONE";
    name="None";
    ethnicOrigin="None";
    price=-1;
    quantity=-1;
};