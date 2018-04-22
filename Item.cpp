#include <iostream>
#include <fstream>
#include "Item.h"
using namespace std;


Item::Item()
{
    price=-1;
    quantity=-1;
};

Item::Item(double newPrice, double newQuantity)
{
    price=newPrice;
    quantity=newQuantity;
};

double Item::getPrice()
{
    return price;
}
double Item::getQuantity()
{
    return quantity;
}
void Item::setPrice(double newPrice)
{
    price=newPrice;
}
void Item::setQuantity(double newQuantity)
{
    quantity=newQuantity;
}

Item::~Item()
{
    price=-1;
    quantity=-1;
};