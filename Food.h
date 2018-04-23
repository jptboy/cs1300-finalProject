#ifndef FOOD_H
#define FOOD_H
#include "Item.h"
#include <iostream>
using namespace std;
class Food:public Item
{
    public:
        Food();
        Food(string newName, double newPrice, double newQuantity, string newTaste, string newEthnicOrigin);

        string getTaste();
        string getName();
        string getEthnicOrigin();

        void setTaste(string newTaste);
        void setName(string newName);
        void setEthnicOrigin(string newEthnicOrigin);

        ~Food();
    private:
        string name;
        string taste;
        string ethnicOrigin;
};
#endif//FOOD_H