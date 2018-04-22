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
        //friend class Inventory;
    public:
        Store();
        void loadCustomers();
        void menu(int whoIs);
        void searchUsers();
        void buyItem(int whoIs);
        void searchItems(int whoIs);
        void addItemtoFavorite();
        void shopLift();
        void quit();
        void viewBalance();
        void getReccomendations();
        void requestOrder();
        void viewItems(int whoIs);
        void addNewCustomer();
        bool doesItemExist(string whatItem);
        int whereDoesItemExist(string whatItem);
        Customer getCustomerAtIndex(unsigned int index);
        ~Store();
    private:
        vector <Customer> customers;
        int Split(string s, char a, string word[], int size);//split function from recitation 7
        Inventory storeInventory;

};



#endif//STORE_H