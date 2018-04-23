#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;
class Item
{
    
    public:
        Item();
        Item(double newPrice, double newQuantity);
        double getPrice();
        double getQuantity();
        void setPrice(double newPrice);
        void setQuantity(double newQuantity);
        ~Item();
    protected:
        double price;
        double quantity;
        
};
#endif//ITEM_H