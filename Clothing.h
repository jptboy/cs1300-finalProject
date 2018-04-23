#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include "Item.h"
class Clothing: public Item
{
    public:
    
        Clothing();
        Clothing(string new_Type, int new_Size, string new_Color, double newPrice, double newQuantity);
        
        string getType();
        string getColor();
        int getSize();

        void setType(string new_Type);
        void setColor(string new_Color);
        void setSize(int new_Size);

        ~Clothing();
    
    private:
    
        string type;
        int size;
        string color;

};

#endif//CLOTHING_H