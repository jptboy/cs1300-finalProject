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
struct itemDescriber
{
  int itemPos;
  string itemName;
};
class Store
{
    public:
        Store();
        void loadCustomers();
        void menu(int whoIs);
        void searchUsers();
        void buyItem(int whoIs,int errorNuller);
        void searchItems(int whoIs,int errorNuller);
        void addItemtoFavorite();
        void shopLift();
        void quit();
        void viewBalance(int whoIs);
        void getReccomendations(int whoIs);
        void requestOrder();
        void viewItems(int whoIs);
        void addNewCustomer();
        int createOrder(string itemType, int itemPos);
        bool doesItemExist(string whatItem);
        int whereDoesItemExist(string whatItem);
        void setDaysOpen(int newDaysOpen);
        int getDaysOpen();
        void makeOrders();
        void loadDays();
        void leaveStore(int whoIs);
        void setCustFavs(string itemName, int whoIs);
        string getItemType(string itemName);
        void viewFavorites(int whoIs);
        string findObject(string itemType, int itemPos);
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