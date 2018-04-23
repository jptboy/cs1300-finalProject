#ifndef ELECTRONIC_H
#define ELECTRONIC_H
#include "Item.h"
#include <iostream>
using namespace std;
class Electronic: public Item
{
    public:
        Electronic();
        Electronic(string newName, double newPrice, double newQuantity, string newDeviceType, int newWarrantyLength);

        string getName();
        int getWarrantyLength();
        string getdeviceType();

        void setName(string newName);
        void setWarrantyLength(int newWarrantyLength);
        void setDeviceType(string newDeviceType);

        ~Electronic();
    private:
        string name;
        int warrantyLength;
        string deviceType;
};
#endif//ELECTRONIC_H