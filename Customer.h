#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
using namespace std;
class Customer
{
    public:
        
        Customer();
        Customer(string newName, double newBankVal, string newFavorites[]);
        
        double getBankVal();//returns the amount of money that the customer has in their bank
        void addMoney(double addedMoney);//allows the user to add money to their bank account

        string getName();
        void setName(string newName);

        bool setFavoriteAtIndex(unsigned int index, string newFavorite);
        string getFavoriteAtIndex(unsigned int index);
    
        ~Customer();
    private:
        
        double bankVal;
        string name;
        string favorites[3];
};

#endif//CUSTOMER_H