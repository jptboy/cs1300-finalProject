#ifndef STORE_H
#define STORE_H
#include "Inventory.h"
#include "Customer.h"
#include "Manager.h"
#include <vector>
#include <iostream>
using namespace std;
struct orderSchedule
{
    int dayTillOrder;
    int itemQuantity;
    int currDay;
    string itemType;
    int itemPos;
};
class Store
{
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
        void createOrder(string itemType, int itemPos);
        bool doesItemExist(string whatItem);
        int whereDoesItemExist(string whatItem);
        void setDaysOpen(int newDaysOpen);
        int getDaysOpen();
        void makeOrders();
        template <class PsuedoObject>
        PsuedoObject findObject(string itemType, int itemPos)
        {
            if(itemType=="food")
            {
                return storeInventory.foods[itemPos];
            }
            else if(itemType=="electronic")
            {
                return storeInventory.electronics[itemPos];
            }
            else if(itemType=="clothing")
            {
                return storeInventory.clothes[itemPos];
            }
        }
        Customer getCustomerAtIndex(unsigned int index);
        ~Store();
    private:
        vector <Customer> customers;
        int Split(string s, char a, string word[], int size);//split function from recitation 7
        Inventory storeInventory;
        int daysOpen;
        vector <orderSchedule> orders;
};





#endif//STORE_H