#include <iostream>
#include <fstream>
#include "Customer.h"
using namespace std;

Customer::Customer()
{
    bankVal = -0.01;
    name="NONE";
    for(int i=0; i<3;i++)
    {
        favorites[i]="NONE";
    }
};
Customer::Customer(string newName, double newBankVal, string newFavorites[])
{
    bankVal = newBankVal;
    name= newName;
    for(int i=0; i<3;i++)
    {
        favorites[i]=newFavorites[i];
    }
}
double Customer::getBankVal()
{
    return bankVal;
}
void Customer::addMoney(double addedMoney)
{
    bankVal+=addedMoney;
}

string Customer::getName()
{
    return name;
}
void Customer::setName(string newName)
{
    name = newName;
}


bool Customer::setFavoriteAtIndex(unsigned int index, string newFavorite)
{
    if(index<3 && index>=0)
        {favorites[index]=newFavorite;}
    else{return false;}
    return true;
}
string Customer::getFavoriteAtIndex(unsigned int index)
{
    return favorites[index];
}

Customer::~Customer()
{
    bankVal = -0.01;
    name="NONE";
    for(int i=0; i<3;i++)
    {
        favorites[i]="NONE";
    }
};