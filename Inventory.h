#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#include <vector>
#include "Item.h"
#include "Food.h"
#include "Electronic.h"
#include "Clothing.h"
using namespace std;
class Inventory
{
    public:
        Inventory();
        void loadInventory(string inventoryFile);
        void addItem();
        void deleteItem();
        void getItem();
        ~Inventory();
        
        vector <Food> foods;
        vector <Clothing> clothes;
        vector <Electronic> electronics;
};
#endif//INVENTORY_H