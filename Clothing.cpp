#include <iostream>
#include <fstream>
#include "Clothing.h"
#include "Item.h"
using namespace std;

Clothing::Clothing()
{
    type = "NONE";
    size=-1;
    color="NONE";
    price=-1;
    quantity=-1;
};

Clothing::Clothing(string new_Type, int new_Size, string new_Color, double newPrice, double newQuantity)
{
    type = new_Type;
    size=new_Size;
    color=new_Color;
    price=newPrice;
    quantity=newQuantity;
};

string Clothing::getType()
{
    return type;
}
string Clothing::getColor()
{
    return color;
}
int Clothing::getSize()
{
    return size;
}

void Clothing::setType(string new_Type)
{
    type = new_Type;
}
void Clothing::setColor(string new_Color)
{
    color=new_Color;
}
void Clothing::Clothing::setSize(int new_Size)
{
    size=new_Size;
}
Clothing::~Clothing()
{
    type = "NONE";
    size=-1;
    color="NONE";
    price=-1;
    quantity=-1;
};