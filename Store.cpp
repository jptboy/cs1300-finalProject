#include <iostream>
#include <fstream>
#include <vector>
#include "Store.h"
#include <stdlib.h>
using namespace std;
int Store::Split(string s, char a, string word[], int size)//split function from recitation 7
{
    int ctilchar = 0;//counts the number of chars until the seperator character
    int arrayindex = 0;//keeps position in the string
    int initseprs = 0;// the initial amount of seperators
    int subs = 0;// used to count the number of substrings
    int seprs = 0;// if there is actually a seperator then we increment initseprs by 1 to get seprs otherwise seprs stays 0
    int ctilcharreal = 0;//is used to see if we are at the end of the string 
    
    for(int i=0; i<s.length();i++)
    {
        if(s[i] == a)
        {
            initseprs++;//if there are seperators then increment init seprs by that amount
        }
    }

    if(initseprs > 0)
    {
        seprs = initseprs + 1;//if init seprs is more than 0 than the real amount of seperators needs to be one more than that for my algorithim
    }



    if(initseprs == 0 && s.length() > 0)//if init seprs is 0 and the string has a length then we just put the string into the 0th index of the  array so we return one subsection
    {
        word[0] = s;
        return 1;
    }
    else
    {
        for(int o = 0; o < seprs; o++)//repeat the outer for loop until the number of seperators is reached
        {
                for(int i = arrayindex; i <= s.length(); i++)
                    {
                        if(s[i] != a)
                        {
                            ctilchar++;//if the ith char of the string isnt the seperator increase the count till char value because thats the purpose of that var
                            ctilcharreal++;//we always increase this to determine our position in the string
                        }
                        
                        if(ctilcharreal==s.length())
                        {
                            word[o] = s.substr(arrayindex, ctilcharreal-arrayindex);//if we reach the end of the string then we put whatever was before that into the array
                            subs++;//increment the number of substrings put into the array
                            break;
                        }
                        
                        if(s[i] == a)
                        {
                            word[o] = s.substr(arrayindex, ctilchar);//if the ith character is the seperator then we make whatever was before that a substring and put it into the array
                            subs++;//increment the amount of substrings put into the array
                            arrayindex += ctilchar + 1;//increment this; its like the cutters arm that would hold your arm while the cutters other arm used a sword to cut it idk how else to explain this
                            ctilchar = 0;//reset the counter till the seperator to 0
                            ctilcharreal++;//we always increase this
                            break;
                        }
                    }
        }
    }
    return subs;// return the number of substrings put into the array
}
Store::Store()
{   
    loadCustomers();
};
void Store::loadCustomers()
{
    string custLine;//variable to hold the lines from the text file
    string custHolderArray[3];//array where stuff gets splitted into
    string custFavs[3];//^
    string custFavsL;

    ifstream lC("customerfile.txt");
    if(!lC.is_open())
    {
        cout << "Error loading files! Program aborted!" << endl;
        exit(0);
    }

    while(getline(lC,custLine))
    {
        Split(custLine,' ',custHolderArray,3);//split by spaces 
        custFavsL=custHolderArray[2];
        Split(custFavsL,',',custFavs,3);//split the third element of the array by commas to get favorite items
        
        //Customer newCustomer(custHolderArray[0], stoi(custHolderArray[1]),custFavs);//creating a new customer object and adding it to the vector
        //customers.push_back(newCustomer);
        //cout << custHolderArray[1] << endl;
        try
        {   
            Customer newCustomer(custHolderArray[0], stoi(custHolderArray[1]),custFavs);//creating a new customer object and adding it to the vector
            customers.push_back(newCustomer);
        }
        catch(...)
        {
            cout << "Error creating a new customer object and placing in the vector." << endl;
            exit(0);
        }
         
        
    }
    cout << "Success! Customers have been loaded." << endl;
    cout << "Welcome to the store, this computerized system will aid you through searching for items, making purchases, adding money to your store account,and a variety of other things." << endl;
    searchUsers();
    return;
}
void Store::menu(int whoIs)//a menu asking customers what they want to do
{
    string userChoice;
    cout << customers[whoIs].getName() << ", what would you like to do? You can: (b)rowse the inventory, make a (p)urchase, (g)et item recomendations, (v)iew or add money to your store credit balance, (o)rder an item, (l)eave the store, (s)earch for an item, or (q)uit this system." << endl;
    
    cin.ignore();//character streams in c++ are a mystic art I guess and this fixes a problem but it also causes a problem
    getline(cin,userChoice);
    
    
    while(!(userChoice=="b"||userChoice=="p"||userChoice=="g"||userChoice=="v"||userChoice=="o"||userChoice=="l"||userChoice=="q"||userChoice=="s"))
    {
        cout << "Please enter a valid lowercase choice " << customers[whoIs].getName() << ". You can: (b)rowse the inventory, make a (p)urchase, (g)et item recomendations, (v)iew or add money to your store credit balance, (o)rder an item, (l)eave the store, (s)earch for an item, or (q)uit this system." << endl;
        getline(cin,userChoice);
    }
    
    if(userChoice=="b")
    {
        viewItems(whoIs);
    }
    else if(userChoice=="p")
    {
        
    }
    else if(userChoice=="g")
    {
        
    }
    else if(userChoice=="v")
    {
        
    }
    else if(userChoice=="o")
    {
        
    }
    else if(userChoice=="l")
    {
        
    }
    else if(userChoice=="q")
    {
        
    }
    else if(userChoice=="s")
    {
        searchItems(whoIs);
    }
    else
    {
        cout << "An error happened please enter a choice again!" << endl;
        menu(whoIs);
    }
}
void Store::addNewCustomer()
{

}
void Store::searchUsers()//this is for the  store to search users the customer wont be seeing this or using it
{
    string enteredName;
    bool found;
    string addMChoice;
    string addedMoneyS;
    double addedMoney=-1;
    int indexAtFound=-1;
    
    cout << "Please enter your first name into this system, so that we may serve you properly. Input is case-sensitive." << endl;
    cin >> enteredName;
    
    while(enteredName.length()==0)
    {
        cout << "You cannot enter an empty name. Please try again!" << endl;
        cin >> enteredName;
    }

    for(int i=0; i<customers.size();i++)
    {
        if(enteredName==customers[i].getName())
        {
            found=true;
            indexAtFound=i;
        }
    }
    if(!found)
    {
        string error="z";
        cout << "You appear to be a new user. If this is not correct please type (n) to enter your name in again otherwise please type in (y)." << endl;
        cin.ignore();
        getline(cin,error);
        while(!(error=="n"||error=="y"))
        {
            cout <<"Please enter a valid option!" << endl;
            getline(cin,error);
        }
        if(error=="n")
        {
            searchUsers();
        }
        else if(error=="y")
        {
            Customer newCustomer;
            newCustomer.setName(enteredName);
            newCustomer.addMoney(0.01);
            customers.push_back(newCustomer);
            
            indexAtFound=customers.size()-1;
            
            cout << "Add money to your store account: (y)es or (no)?" << endl;
            cout << "Your current balance is " << customers[customers.size()-1].getBankVal()  << " dollars." << endl;
            getline(cin,addMChoice);
            
            while(!(addMChoice=="n"||addMChoice=="y"))
            {
                cout <<"Please enter a valid lowercase option: (y)es or (no)?" << endl;
                getline(cin,addMChoice);
            }
            
            if(addMChoice=="y")
            {
                cout << "How much money would you like to add to your account?" << endl;
                while(addedMoney<=0)
                {
                    try
                    {
                        cin>>addedMoneyS;
                        addedMoney=stod(addedMoneyS);//this while try catch block keeps prompting for the user to enter a proper numerical value until the added money double is more than 0, this wont happen if there is a stod error
                    }
                    catch(...)
                    {
                        cout <<"Please enter a valid numerical amount!" << endl;
                    }
                }
                customers[customers.size()-1].addMoney(addedMoney);
                cout << "Success!, you added " << addedMoney << " dollars to your store account!" << endl;
                cout << "Your store credit balance is now " << customers[customers.size()-1].getBankVal() << " dollars." << endl;
                menu(indexAtFound);
            }
            else if(addMChoice=="n")
            {
                menu(indexAtFound);
            }
        }
    }
    
    else if(found)
    {
        cout << "Welcome back to the store " << enteredName << ". You have " << customers[indexAtFound].getBankVal() << " dollars in your store account." << endl;
        menu(indexAtFound);
    }

}
void Store::buyItem()//self explanitory
{

}
void Store::addItemtoFavorite()//customers can add items to their favorites
{

}
void Store::shopLift()//customers can try to steal things if they dont have enough money to pay for them
{

}
void Store::viewBalance()//customers can see how much money they have before they pay for things
{

}
void Store::getReccomendations()//customers can get recomendations for foods clothing and electronics if they don't know what to buy
{

}
void Store::viewItems(int whoIs)//for the customer to view the inventory of the store and search it, they can narrow down to types of items and items
{
    string userChoice;
    cout <<"What category of items would you like to browse?: (f)oods, (e)lectronics, or (c)lothing? Or would you like to go back to the (m)ain menu?" << endl;
    
    getline(cin,userChoice);
    while(!(userChoice=="f"||userChoice=="e"||userChoice=="c"||userChoice=="m"))
    {
        cout << "Please enter a valid lowercase choice!" << endl;
        cout << "You can either browse from these selections: (f)oods, (e)lectronics, or (c)lothing or you can go back to the (m)ain menu." << endl;
        getline(cin,userChoice);
    }
    
    if(userChoice=="f")
    {
        cout <<"Foods:"<< endl;
        //the for loops below print out all of the foods electronics and and clothing objects from the stores inventory objects names and quanitities
        for(int i=0; i<storeInventory.foods.size();i++)
        {
            cout << "Name: " << storeInventory.foods[i].getName() <<" | Quantity: " << storeInventory.foods[i].getQuantity() << endl;
        }
        cout <<"----" << endl;
        viewItems(whoIs);
    }
    else if(userChoice=="e")
    {   cout <<"Electronics:"<< endl;
        for(int i=0; i<storeInventory.electronics.size();i++)
        {
            cout << "Name: " << storeInventory.electronics[i].getName() <<" | Quantity: " << storeInventory.electronics[i].getQuantity() << endl;
        }
        cout <<"----" << endl;
        viewItems(whoIs);
    }
    
    else if(userChoice=="c")
    {   cout <<"Clothes:"<< endl;
        for(int i=0; i<storeInventory.clothes.size();i++)
        {
            cout << "Name: " << storeInventory.clothes[i].getType() <<" | Quantity: " << storeInventory.clothes[i].getQuantity() << endl;
        }
        cout <<"----" << endl;
        viewItems(whoIs);
    }
    else if(userChoice=="m")
    {
        menu(whoIs);
    }
}
void Store::requestOrder()
{

}//this is used to ask the manager to order a item if you cant find it
void Store::quit()//I might name this leaveStore
{

}
void Store::searchItems(int whoIs)
{
    bool exists;
    string itemChoice;
    string itemType;
    int itemIndex=-1;
    string returnChoice;
    
    cout << "Would you like to return to the (m)ain menu or would you like to (s)earch for an item?" << endl;
    getline(cin, returnChoice);
    
    while(!(returnChoice=="m"||returnChoice=="s"))
    {
        cout << "Would you like to return to the (m)ain menu or would you like to (s)earch for an item? (Input is case-sensitive)" << endl;
        getline(cin,returnChoice);
    }
    
    if(returnChoice=="m")
    {
        menu(whoIs);
    }
    else if(returnChoice=="s")
    {
        cout << "Enter the name of the item you wish to search for information about:" << endl;
        getline(cin, itemChoice);
        
        for(int i=0; i<storeInventory.clothes.size();i++)
        {
            if(itemChoice==storeInventory.clothes[i].getType())
            {
                exists=true;
                itemType="clothing";
                itemIndex=i;
            }
        }
        for(int i=0; i<storeInventory.electronics.size();i++)
        {
            if(itemChoice==storeInventory.electronics[i].getName())
            {
                exists=true;
                itemType="electronic";
                itemIndex=i;
            }
        }
        for(int i=0; i<storeInventory.foods.size();i++)
        {
            if(itemChoice==storeInventory.foods[i].getName())
            {
                exists=true;
                itemType="food";
                itemIndex=i;
            }
        }
        if(!exists)
        {
            cout <<"Sorry that item does not exist in our inventory." << endl;
        }
        else if(exists)
        {
            if(itemType=="clothing")
            {
                cout << "There are " << storeInventory.clothes[itemIndex].getQuantity() <<" " <<storeInventory.clothes[itemIndex].getType() << "(s) available and they are all size " << storeInventory.clothes[itemIndex].getSize() << " and are " <<storeInventory.clothes[itemIndex].getColor() << "."<< endl;
                cout << "Each " << storeInventory.clothes[itemIndex].getType() << " costs " << storeInventory.clothes[itemIndex].getPrice() <<" dollars." << endl;
            }
            else if(itemType=="electronic")
            {
                cout << "There are " << storeInventory.electronics[itemIndex].getQuantity() <<" " <<storeInventory.electronics[itemIndex].getName() << "(s) available and they are all good " << storeInventory.electronics[itemIndex].getdeviceType() << "(s) and have a " <<storeInventory.electronics[itemIndex].getWarrantyLength() << " day warranty."<< endl;
                cout << "Each " << storeInventory.electronics[itemIndex].getName() << " costs " << storeInventory.electronics[itemIndex].getPrice() <<" dollars." << endl;
            }
            
            else if(itemType=="food")
            {
                cout << "There are " << storeInventory.foods[itemIndex].getQuantity() <<" " <<storeInventory.foods[itemIndex].getName() << "(s) available. The place of origin of "<< storeInventory.foods[itemIndex].getName()<<"(s) is " << storeInventory.foods[itemIndex].getEthnicOrigin() << " and " << storeInventory.foods[itemIndex].getName() <<" tastes " <<storeInventory.foods[itemIndex].getTaste() << "."<< endl;
                cout << "Each " << storeInventory.foods[itemIndex].getName() << " costs " << storeInventory.foods[itemIndex].getPrice() <<" dollars." << endl;
            }
            else
            {
                cout << "Big error in search function when displaying item information." << endl;
                exit(0);
            }
        }
        searchItems(whoIs);
    }
    
}
Customer Store::getCustomerAtIndex(unsigned int index)
{
    return customers[index];
}


Store::~Store()
{
    
};