#include <iostream>
#include <fstream>
#include "Electronic.h"
using namespace std;

Electronic::Electronic()
{
    name="NONE";
    warrantyLength=-1;
    deviceType="NONE";
    price=-1;
    quantity=-1;
};
Electronic::Electronic(string newName, double newPrice, double newQuantity, string newDeviceType, int newWarrantyLength)
{
    name=newName;
    warrantyLength=newWarrantyLength;
    deviceType=newDeviceType;
    price=newPrice;
    quantity=newQuantity;
};

string Electronic::getName()
{
    return name;
}
int Electronic::getWarrantyLength()
{
    return warrantyLength;
}
string Electronic::getdeviceType()
{
    return deviceType;
}

void Electronic::setName(string newName)
{
    name=newName;
}
void Electronic::setWarrantyLength(int newWarrantyLength)
{
    warrantyLength=newWarrantyLength;
}
void Electronic::setDeviceType(string newDeviceType)
{
    deviceType=newDeviceType;
}
Electronic::~Electronic()
{
    name="NONE";
    warrantyLength=-1;
    deviceType="NONE";
    price=-1;
    quantity=-1;
};