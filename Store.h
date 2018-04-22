#ifndef STORE_H
#define STORE_H
#include "Inventory.h"
#include "Customer.h"
#include "Manager.h"
#include <vector>
#include <iostream>
using namespace std;
class Store
{
    public:
        Store();
        void loadCustomers();
        void menu(int whoIs);
        void searchUsers();
        void buyItem();
        void addItemtoFavorite();
        void shopLift();
        void quit();
        void viewBalance();
        void getReccomendations();
        void requestOrder();
        void viewItems();
        void addNewCustomer();
        Customer getCustomerAtIndex(unsigned int index);
        ~Store();
    private:
        vector <Customer> customers;
        int Split(string s, char a, string word[], int size);//split function from recitation 7
};



#endif//STORE_H