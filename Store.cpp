#include <iostream>
#include <fstream>
#include <cstdlib>
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
    loadDays();
    loadOrders();
    loadCustomers();
};
void Store::loadDays()
{
    try
    {   ifstream dayloader("day.txt");
        string dayline;
        dayloader >> dayline;
        daysOpen=stoi(dayline);
        return;
    }
    catch(...)
    {
        cout << "Error loading days file. Program terminated." << endl;
        exit(0);
    }
}
void Store::loadOrders()
{
    string orderLine;
    string orderHolder[5];
    int orderHolderSize=5;
    
    ifstream loadOrderfromFile("orders.txt");
    if(!loadOrderfromFile.is_open())
    {
        cout << "Error loading orders! Program terminated!" << endl;
        exit(0);
    }
    
    try
    {
        while(getline(loadOrderfromFile,orderLine))
        {
            Split(orderLine,',',orderHolder,orderHolderSize);
            
            orderSchedule newOrder;
            newOrder.dayTillOrder=stoi(orderHolder[0]);
            newOrder.itemQuantity=stoi(orderHolder[1]);
            newOrder.currDay=stoi(orderHolder[2]);//giving instantiated struct members values
            newOrder.itemType=orderHolder[3];
            newOrder.itemPos=stoi(orderHolder[4]);
            
            orders.push_back(newOrder);
        }
    }
    catch(...)
    {
        cout << "Error loading orders! Program terminated!" << endl;
        exit(0);
    }
}
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
    cout << "Welcome to the store, this system will aid you through searching for items, making purchases, adding money to your store account,and a variety of other things." << endl;
    searchUsers();
    return;
}
void Store::menu(int whoIs)//a menu asking customers what they want to do
{
    makeOrders();
    string userChoice;
    cout << customers[whoIs].getName() << ", what would you like to do? You can: (b)rowse the inventory, make a (p)urchase, (g)et item recomendations, (v)iew or add money to your store credit balance, (l)eave the store, (s)earch for and favorite items, view (f)avorite items, or (q)uit this system." << endl;
    
    getline(cin,userChoice);
    
    
    while(!(userChoice=="b"||userChoice=="p"||userChoice=="g"||userChoice=="v"||userChoice=="l"||userChoice=="q"||userChoice=="s" || userChoice=="f"))
    {
        cout << "Please enter a valid lowercase choice " << customers[whoIs].getName() << ". You can: (b)rowse the inventory, make a (p)urchase, (g)et item recomendations, (v)iew or add money to your store credit balance, (l)eave the store, (s)earch for and favorite items, view (f)avorite items, or (q)uit this system." << endl;
        getline(cin,userChoice);
    }
    
    if(userChoice=="b")
    {
        viewItems(whoIs);
    }
    else if(userChoice=="p")
    {
        buyItem(whoIs,1);
    }
    else if(userChoice=="g")
    {
        getReccomendations(whoIs);
    }
    else if(userChoice=="v")
    {
        viewBalance(whoIs);
    }
    else if(userChoice=="l")
    {
        leaveStore(whoIs);
    }
    else if(userChoice=="q")
    {
        daysOpen++;
        quit();
    }
    else if(userChoice=="f")
    {
        viewFavorites(whoIs);
    }
    else if(userChoice=="s")
    {
        searchItems(whoIs,1);
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
    int yeller=0;
    
    
    cout << "Please enter your first name into this system, so that we may serve you properly. (Input is case-sensitive)" << endl;
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
        cout << "You appear to be a new customer. If this is not correct please type (n) to enter your name in again otherwise please type in (y)." << endl;
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
            
            cout << "Add money to your store account: (y)es or (n)o?" << endl;
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
                        yeller=1;
                    }
                    if(addedMoney<=0 && yeller!=1)
                    {
                        cout << "Please enter a amount above $0.00!" << endl;
                        yeller=0;
                    }
                    else if(yeller==1)
                    {
                        cout <<"Please enter a valid numerical amount above 0.00!" << endl;
                    }
                }
                customers[customers.size()-1].addMoney(addedMoney);
                cout << "Success!, you added " << addedMoney << " dollars to your store account!" << endl;
                cout << "Your store credit balance is now " << customers[customers.size()-1].getBankVal() << " dollars." << endl;
                cin.ignore();
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
        cout << flush;
        cin.ignore();
        menu(indexAtFound);
    }

}
void Store::buyItem(int whoIs,int errorNuller)//self explanitory
{
    string whatItem;
    bool exists=false;
    string returnChoice="p";
    int positionInVec=-1;
    string itemType;
    int itemQuan=-1;
    string managerReq;
    string favOrNot;
    
    if(errorNuller!=1)
    {
        cout << "Would you like to return to the (m)ain menu or would you like to (p)urchase an item?" << endl;
        getline(cin, returnChoice);
        
        while(!(returnChoice=="m"||returnChoice=="p"))
        {
            cout << "Would you like to return to the (m)ain menu or would you like to (p)urchase an item? (Input is case-sensitive)" << endl;
            getline(cin,returnChoice);
        }
    }
    if(returnChoice=="m")
    {
        menu(whoIs);
    }
    else if(returnChoice=="p")
    {
        cout << "What item would you like to buy? Please browse the store or search for the item if you don't know!" << endl;
        getline(cin, whatItem);
        
        exists=doesItemExist(whatItem);
        
        if(!exists)
        {
            cout << "We do not have " << whatItem <<"(s) in our inventory. You can only purchase what we have!" << endl;
            buyItem(whoIs,0);
        }
        else if(exists)
        {
            positionInVec= whereDoesItemExist(whatItem);
            
            try
            {
                if(storeInventory.foods[positionInVec].getName()==whatItem)
                {
                    itemType="food";
                }
                else if(storeInventory.electronics[positionInVec].getName()==whatItem)
                {
                    itemType="electronic";
                }
                else if(storeInventory.clothes[positionInVec].getType()==whatItem)
                {
                    itemType="clothing";
                }
            }
            catch(...)
            {
                cout << "Error determining what type of item user tried to purchase. Program terminated." << endl;
                exit(0);
            }
            
            if(itemType=="food")
            {
                itemQuan=storeInventory.foods[positionInVec].getQuantity();
                if(itemQuan<=0)
                {
                    cout << "There are no " << storeInventory.foods[positionInVec].getName() << "(s) left. You can (s)end a request to a manager to order more or you can (p)urchase something else." << endl;
                    getline(cin, managerReq);
                    
                    while(!(managerReq=="p"||managerReq=="s"))
                    {
                        cout << "Please enter a valid lower case option." << endl;
                        getline(cin, managerReq);
                    }
                    if(managerReq=="p")
                    {
                        buyItem(whoIs,0);
                    }
                    else if(managerReq=="s")
                    {
                        
                        cout << "The manager ordered more quantity of the item, 5 more will come in " << createOrder(itemType,positionInVec) << " day(s)." << endl;
                        buyItem(whoIs,0);
                    }
                }
                else
                {
                    if(customers[whoIs].getBankVal() < storeInventory.foods[positionInVec].getPrice())
                    {
                        cout << "You do not have enough store credit to purchase this item. Please input in the main menu that you wish to add money to your store account if you wish to attempt make this purchase again." << endl;
                        menu(whoIs);
                    }
                    else
                    {
                        cout << "You purchased a " << whatItem << "for " << storeInventory.foods[positionInVec].getPrice() << " dollars."<< endl;
                        customers[whoIs].addMoney(-1*(storeInventory.foods[positionInVec].getPrice()));//decreasing the store credit value of the person who just purchased the item
                        storeInventory.foods[positionInVec].setQuantity(itemQuan-1);//decreasing the number of the item just purchased
                        cout << "Your store credit balance is now: " << customers[whoIs].getBankVal() << " dollars." << endl;
                        
                        favOrNot="z";
                        cout << "Would you like to favorite this item?: (y)es or (n)o?" << endl;
                        getline(cin, favOrNot);
                        while(!(favOrNot=="n"||favOrNot=="y"))
                        {
                            cout <<"Please enter a valid option from these choices : (y)es or (n)o" << endl;
                            getline(cin,favOrNot);
                        }
                        if(favOrNot=="y")
                        {
                            setCustFavs(whatItem,whoIs);
                        }
                        
                        buyItem(whoIs,0);
                    }
                        
                }
            }
            else if(itemType=="electronic")
            {
                itemQuan=storeInventory.electronics[positionInVec].getQuantity();
                if(itemQuan<=0)
                {
                    cout << "There are no " << storeInventory.electronics[positionInVec].getName() << "(s) left. You can (s)end a request to a manager to order more or you can (p)urchase something else." << endl;
                    getline(cin, managerReq);
                    
                    while(!(managerReq=="p"||managerReq=="s"))
                    {
                        cout << "Please enter a valid lower case option." << endl;
                        getline(cin, managerReq);
                    }
                    if(managerReq=="p")
                    {
                        buyItem(whoIs,0);
                    }
                    else if(managerReq=="s")
                    {
                        cout << "The manager ordered more quantity of the item, 5 more will come in " << createOrder(itemType,positionInVec) << " day(s)."<< endl;//change back to bad way if errors
                        buyItem(whoIs,0);
                    }
                }
                else
                {
                    if(customers[whoIs].getBankVal() < storeInventory.electronics[positionInVec].getPrice())
                    {
                        cout << "You do not have enough store credit to purchase this item. Please input in the main menu that you wish to add money to your store account if you wish to attempt make this purchase again." << endl;
                        menu(whoIs);
                    }
                    else
                    {
                        cout << "You purchased a " << whatItem << "for " << storeInventory.electronics[positionInVec].getPrice() << " dollars."<< endl;
                        customers[whoIs].addMoney(-1*(storeInventory.electronics[positionInVec].getPrice()));//decreasing the store credit value of the person who just purchased the item
                        storeInventory.electronics[positionInVec].setQuantity(itemQuan-1);//decreasing the number of the item just purchased
                        cout << "Your store credit balance is now: " << customers[whoIs].getBankVal() << " dollars." << endl;
                        
                        favOrNot="z";
                        cout << "Would you like to favorite this item?: (y)es or (n)o?" << endl;
                        getline(cin, favOrNot);
                        while(!(favOrNot=="n"||favOrNot=="y"))
                        {
                            cout <<"Please enter a valid option from these choices : (y)es or (n)o" << endl;
                            getline(cin,favOrNot);
                        }
                        if(favOrNot=="y")
                        {
                            setCustFavs(whatItem,whoIs);
                        }
                        
                        buyItem(whoIs,0);
                        
                    }
                }
            }
            else if(itemType=="clothing")
            {
                itemQuan=storeInventory.clothes[positionInVec].getQuantity();
                if(itemQuan<=0)
                {
                    cout << "There are no " << storeInventory.clothes[positionInVec].getType() << "(s) left. You can (s)end a request to a manager to order more or you can (p)urchase something else." << endl;
                    getline(cin, managerReq);
                    
                    while(!(managerReq=="p"||managerReq=="s"))
                    {
                        cout << "Please enter a valid lower case option." << endl;
                        getline(cin, managerReq);
                    }
                    if(managerReq=="p")
                    {
                        buyItem(whoIs,0);
                    }
                    else if(managerReq=="s")
                    {
                        cout << "The manager ordered more quantity of the item, 5 more will come in " << createOrder(itemType,positionInVec) << " day(s)."<< endl;
                        buyItem(whoIs,0);
                    }
                }
                else
                {
                    
                    if(customers[whoIs].getBankVal() < storeInventory.clothes[positionInVec].getPrice())
                    {
                        cout << "You do not have enough store credit to purchase this item. Please input in the main menu that you wish to add money to your store account if you wish to attempt make this purchase again." << endl;
                        menu(whoIs);
                    }
                    else
                    {
                        cout << "You purchased a " << whatItem << "for " << storeInventory.clothes[positionInVec].getPrice() << " dollars."<< endl;
                        customers[whoIs].addMoney(-1*(storeInventory.clothes[positionInVec].getPrice()));//decreasing the store credit value of the person who just purchased the item
                        storeInventory.clothes[positionInVec].setQuantity(itemQuan-1);//decreasing the number of the item just purchased
                        cout << "Your store credit balance is now: " << customers[whoIs].getBankVal() << " dollars." << endl;
                        
                        favOrNot="z";
                        cout << "Would you like to favorite this item?: (y)es or (n)o?" << endl;
                        getline(cin, favOrNot);
                        while(!(favOrNot=="n"||favOrNot=="y"))
                        {
                            cout <<"Please enter a valid option from these choices : (y)es or (n)o" << endl;
                            getline(cin,favOrNot);
                        }
                        if(favOrNot=="y")
                        {
                            setCustFavs(whatItem,whoIs);
                        }
                        
                        buyItem(whoIs,0);
                    }
                    
                           
                }
            }
            
        }
    }
    else 
    {
        cout << "Major error when trying to purchase an item. This program will now terminate!" << endl;
        exit(0);
    }
    
}

void Store::viewFavorites(int whoIs)
{
    string favEl=customers[whoIs].getFavoriteAtIndex(2);
    string favFd=customers[whoIs].getFavoriteAtIndex(0);
    string favCl=customers[whoIs].getFavoriteAtIndex(1);
    string favArrs[]={favEl,favFd,favCl};
    string types[]={"Electronic","Food","Clothing"};
    
    int foodQ=-1;
    int elQ=-1;
    int clQ=-1;
    string foodQS;
    string elQS;
    string clQS;
    
    if(favFd!="NONE")
        {
            foodQ=finderForItemQuantity(favFd);
        }
    if(favEl!="NONE")
        {
            elQ=finderForItemQuantity(favEl);
        }
    if(favCl!="NONE")
        {
            clQ=finderForItemQuantity(favCl);
        }
    
    int quantsBfrStrCnv[]={elQ,foodQ,clQ};
    string quants[]={elQS,foodQS,clQS};
    
    for(int i=0; i<3;i++)
    {
        if(quantsBfrStrCnv[i]!=-1)
        {
            quants[i]=to_string(quantsBfrStrCnv[i]);
        }
        else
        {
            quants[i]="Not applicable";
        }
    }
    
    for(int i=0; i<3;i++)
    {
        if(favArrs[i]=="NONE")
        {
            favArrs[i]="No favorite set.";
        }
    }
    
    
    
    cout << "Your favorite items are:" << endl;
    for(int i=0; i<3;i++)
        {cout << "Favorite "<< types[i]<< ": " << favArrs[i] << " Quantity: "<< quants[i] << endl;}
    
    menu(whoIs);
}
void Store::addItemtoFavorite()//customers can add items to their favorites
{

}
void Store::shopLift()//customers can try to steal things if they dont have enough money to pay for them
{

}
int Store::finderForItemQuantity(string itemName)
{
    bool exists=doesItemExist(itemName);
    string itemChoice=itemName;
    int itemIndex=-1;
    int itemQuantityFromName=-1;
    if(exists)    
    {   for(int i=0; i<storeInventory.clothes.size();i++)
        {
            if(itemChoice==storeInventory.clothes[i].getType())
            {
                exists=true;
                itemIndex=i;
                itemQuantityFromName=storeInventory.clothes[i].getQuantity();
            }
        }
        for(int i=0; i<storeInventory.electronics.size();i++)
        {
            if(itemChoice==storeInventory.electronics[i].getName())
            {
                exists=true;
                itemIndex=i;
                itemQuantityFromName=storeInventory.electronics[i].getQuantity();
            }
        }
        for(int i=0; i<storeInventory.foods.size();i++)
        {
            if(itemChoice==storeInventory.foods[i].getName())
            {
                exists=true;
                itemIndex=i;
                itemQuantityFromName=storeInventory.foods[i].getQuantity();
            }
        }
    }
    else if(!exists)
    {
        cout << "A major error was about to be caused returning the quantity of an item from its name so the program was terminated" << endl;
        exit(0);
    }
    else
    {
        cout << "A major error was about to be caused returning the quantity of an item from its name so the program was terminated" << endl;
        exit(0);
    }
    
    return itemQuantityFromName;
}
void Store::viewBalance(int whoIs)//customers can see how much money they have before they pay for things
{
    string addMChoice;
    string addedMoneyS;
    double addedMoney=-1;
    int yeller=0;
    cout << "Your current balance is " << customers[whoIs].getBankVal()  << " dollars." << endl;
    cout << "Add money to your store account: (y)es or (n)o? Input (n) to return to the main menu." << endl;
    getline(cin,addMChoice);
    
    while(!(addMChoice=="n"||addMChoice=="y"))
    {
        cout <<"Please enter a valid lowercase option: (y)es or (n)o? Input (n) to return to the main menu." << endl;
        getline(cin,addMChoice);
    }
    
    if(addMChoice=="y")
    {
        cout << "How much money would you like to add to your account?" << endl;
        while(addedMoney<=0)
        {
            try
            {
                cin >> addedMoneyS;
                addedMoney=stod(addedMoneyS);//this while try catch block keeps prompting for the user to enter a proper numerical value until the added money double is more than 0, this wont happen if there is a stod error
            }
            catch(...)
            {
                yeller=1;
            }
            if(addedMoney<=0 && yeller!=1)
            {
                cout << "Please enter a amount above $0.00!" << endl;
                yeller=0;
            }
            else if(yeller==1)
            {
                cout <<"Please enter a valid numerical amount above 0.00!" << endl;
            }
        }
        customers[whoIs].addMoney(addedMoney);
        cout << "Success!, you added " << addedMoney << " dollars to your store account!" << endl;
        cout << "Your store credit balance is now " << customers[whoIs].getBankVal() << " dollars." << endl;
        //cin.ignore();
        menu(whoIs);
    }
    else if(addMChoice=="n")
    {
        menu(whoIs);
    }
}
void Store::getReccomendations(int whoIs)//customers can get recomendations for foods clothing and electronics if they don't know what to buy
{
    double similarityScore=0;
    vector <itemDescriber> alreadyFavs;
    vector <string> stopsRepeat;
    bool isRepeated=false;
    bool isinVec=false;
    for(int i=0; i<customers.size();i++)
    {
        if(customers[i].getFavoriteAtIndex(0)==customers[whoIs].getFavoriteAtIndex(0))
        {
            similarityScore++;
        }
        else if(customers[i].getFavoriteAtIndex(1)==customers[whoIs].getFavoriteAtIndex(1))
        {
            similarityScore++;
        }
        else if(customers[i].getFavoriteAtIndex(2)==customers[whoIs].getFavoriteAtIndex(2))
        {
            similarityScore++;
        }
        
        
        for(int k=0; k<2; k++)
        {
            
            if(customers[i].getFavoriteAtIndex(k)==customers[whoIs].getFavoriteAtIndex(k))
            {
                isinVec=true;
            }
            
            for(int j=0; j<alreadyFavs.size();j++)
            {
                if(customers[whoIs].getFavoriteAtIndex(k)==alreadyFavs[j].itemName)
                {
                    isinVec=true;
                }
            }
            
            if(!isinVec && (similarityScore >0 && similarityScore < 3))
            {
                itemDescriber newItemtoAdd;
                newItemtoAdd.itemName=customers[i].getFavoriteAtIndex(k);
                newItemtoAdd.itemPos=whereDoesItemExist(newItemtoAdd.itemName);
                alreadyFavs.push_back(newItemtoAdd);
            }
        }
    }
    
    if(alreadyFavs.size()>0)
    {
        cout << "Reccomended items based on people with similar favorite items to you are: " << endl;
        for(int i=0; i<alreadyFavs.size(); i++)
        {
            isRepeated=false;
            for(int j=0; j<stopsRepeat.size();j++)
            {
                if(stopsRepeat[j]==alreadyFavs[i].itemName)
                    {isRepeated=true;}
            }
            if(!isRepeated)
            {
                cout << alreadyFavs[i].itemName << endl;
            }
            
            stopsRepeat.push_back(alreadyFavs[i].itemName);
        }
        
    }
    else
    {
        cout << "You have no item reccomendations at this time." << endl;
    }
    
    menu(whoIs);
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
            cout << "Name: " << storeInventory.foods[i].getName() <<" | Quantity: " << storeInventory.foods[i].getQuantity() << " | Price: " << storeInventory.electronics[i].getPrice() << endl;
        }
        cout <<"----" << endl;
        viewItems(whoIs);
    }
    else if(userChoice=="e")
    {   cout <<"Electronics:"<< endl;
        for(int i=0; i<storeInventory.electronics.size();i++)
        {
            cout << "Name: " << storeInventory.electronics[i].getName() <<" | Quantity: " << storeInventory.electronics[i].getQuantity() << " | Price: " << storeInventory.electronics[i].getPrice() << endl;
        }
        cout <<"----" << endl;
        viewItems(whoIs);
    }
    
    else if(userChoice=="c")
    {   cout <<"Clothes:"<< endl;
        for(int i=0; i<storeInventory.clothes.size();i++)
        {
            cout << "Name: " << storeInventory.clothes[i].getType() <<" | Quantity: " << storeInventory.clothes[i].getQuantity() << " | Price: " << storeInventory.clothes[i].getPrice() << endl;
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
void Store::quit()
{
    ofstream updateDays("day.txt");
    updateDays << daysOpen << endl;
    updateDays.close();
    
    ofstream updateOrders("orders.txt");
    for(int i=0; i<orders.size(); i++)
    {
        updateOrders << orders[i].dayTillOrder << "," << orders[i].itemQuantity<< "," << orders[i].currDay<< "," << orders[i].itemType<< "," << orders[i].itemPos; 
    }
    if(orders.size()==0)
    {
        updateOrders <<"";
    }
    updateOrders.close();
    
    ofstream updateCustomers("customerfile.txt");
    for(int i=0; i<customers.size();i++)
    {
        updateCustomers << customers[i].getName() <<" " << customers[i].getBankVal()<<" " << customers[i].getFavoriteAtIndex(0) <<","<< customers[i].getFavoriteAtIndex(1) <<","<< customers[i].getFavoriteAtIndex(2)<<endl;
    }
    updateCustomers.close();
    
    ofstream updateInventory("inventoryfile.txt");
    
    for(int i=0; i<storeInventory.foods.size(); i++)
    {
        updateInventory << storeInventory.foods[i].getName() <<","<< storeInventory.foods[i].getPrice()<<","<< storeInventory.foods[i].getQuantity()<<","<< storeInventory.foods[i].getTaste()<<"," <<storeInventory.foods[i].getEthnicOrigin() <<endl;
    }
    updateInventory<<endl;
    for(int i=0; i<storeInventory.electronics.size(); i++)
    {
        updateInventory << storeInventory.electronics[i].getName()<<","<< storeInventory.electronics[i].getPrice()<<","<< storeInventory.electronics[i].getQuantity()<<","<< storeInventory.electronics[i].getdeviceType()<<"," <<storeInventory.electronics[i].getWarrantyLength()<<endl;
    }
    updateInventory<<endl;
    for(int i=0; i<storeInventory.clothes.size(); i++)
    {
        updateInventory << storeInventory.clothes[i].getType()<<","<< storeInventory.clothes[i].getPrice()<<","<< storeInventory.clothes[i].getQuantity()<<","<< storeInventory.clothes[i].getColor()<<"," <<storeInventory.clothes[i].getSize() <<","<<"PLACEHOLDER"<<endl;
    }
    updateInventory.close();
    exit(0);
}
void Store::leaveStore(int whoIs)
{
    cout << "You leave the store for the day" << endl;
    daysOpen++;
    searchUsers();
}
void Store::setDaysOpen(int newDaysOpen)
{
    daysOpen=newDaysOpen;
}
int Store::getDaysOpen()
{
    return daysOpen;
}
int Store::createOrder(string itemType, int itemPos)
{
    
    int randDay=-1;
    int lowQuantity=-1;
    srand((int) time(0));//random number generation from 1 to 5, here we seed value to start with which is the time so that we get actual random runs
    randDay= (rand()%5) + 1;
    //randDay=1;
    Electronic possibleEl;
    Clothing possibleCl;
    Food possibleFd;
    if(itemType=="food")
    {
        possibleFd=storeInventory.foods[itemPos];
        lowQuantity= 5;
        
    }
    else if(itemType=="clothing")
    {
        possibleCl=storeInventory.clothes[itemPos];
        lowQuantity=5;
        
    }
    else if(itemType=="electronic")
    {
        possibleEl=storeInventory.electronics[itemPos];
        lowQuantity= 5;
        
    }
    
    orderSchedule newOrder;
    newOrder.dayTillOrder=randDay+daysOpen;
    newOrder.currDay=daysOpen;//giving instantiated struct members values
    newOrder.itemQuantity=lowQuantity;
    newOrder.itemType=itemType;
    newOrder.itemPos=itemPos;
    
    orders.push_back(newOrder);
    return randDay;
    
}

void Store::makeOrders()
{
    for(int i=0; i<orders.size();i++)
    {
        if(daysOpen>=orders[i].dayTillOrder)
        {
            if(orders[i].itemType=="food")
            {
                storeInventory.foods[orders[i].itemPos].setQuantity((storeInventory.foods[orders[i].itemPos].getQuantity()+5));
                orders.pop_back();
            }
            else if(orders[i].itemType=="electronic")
            {
                storeInventory.electronics[orders[i].itemPos].setQuantity((storeInventory.electronics[orders[i].itemPos].getQuantity()+5));
                orders.pop_back();
            }
            else if(orders[i].itemType=="clothing")
            {
                storeInventory.clothes[orders[i].itemPos].setQuantity((storeInventory.clothes[orders[i].itemPos].getQuantity()+5));//unwanted behavior may appear here
                orders.pop_back();
            }
        }
    }
   
   // cout << orders.size() << endl;
}
void Store::searchItems(int whoIs,int errorNuller)
{
    bool exists;
    string itemChoice;
    string itemType;
    string favOrNot;
    int itemIndex=-1;
    string returnChoice="s";
    if(errorNuller!=1)
    {
        cout << "Would you like to return to the (m)ain menu or would you like to (s)earch for an item?" << endl;
        getline(cin, returnChoice);
        
        while(!(returnChoice=="m"||returnChoice=="s"))
        {
            cout << "Would you like to return to the (m)ain menu or would you like to (s)earch for another item? (Input is case-sensitive)" << endl;
            getline(cin,returnChoice);
        }
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
                
                cout << "Would you like to favorite this item?: (y)es or (n)o?" << endl;
                getline(cin, favOrNot);
                while(!(favOrNot=="n"||favOrNot=="y"))
                {
                    cout <<"Please enter a valid option from these choices : (y)es or (n)o" << endl;
                    getline(cin,favOrNot);
                }
                if(favOrNot=="y")
                {
                    setCustFavs(storeInventory.clothes[itemIndex].getType(),whoIs);
                }
                
                
            }
            else if(itemType=="electronic")
            {
                cout << "There are " << storeInventory.electronics[itemIndex].getQuantity() <<" " <<storeInventory.electronics[itemIndex].getName() << "(s) available and they are all good " << storeInventory.electronics[itemIndex].getdeviceType() << "(s) and have a " <<storeInventory.electronics[itemIndex].getWarrantyLength() << " day warranty."<< endl;
                cout << "Each " << storeInventory.electronics[itemIndex].getName() << " costs " << storeInventory.electronics[itemIndex].getPrice() <<" dollars." << endl;
                
                cout << "Would you like to favorite this item?: (y)es or (n)o?" << endl;
                getline(cin, favOrNot);
                while(!(favOrNot=="n"||favOrNot=="y"))
                {
                    cout <<"Please enter a valid option from these choices : (y)es or (n)o" << endl;
                    getline(cin,favOrNot);
                }
                if(favOrNot=="y")
                {
                    setCustFavs(storeInventory.electronics[itemIndex].getName(),whoIs);
                }
            }
            
            else if(itemType=="food")
            {
                cout << "There are " << storeInventory.foods[itemIndex].getQuantity() <<" " <<storeInventory.foods[itemIndex].getName() << "(s) available. The place of origin of "<< storeInventory.foods[itemIndex].getName()<<"(s) is " << storeInventory.foods[itemIndex].getEthnicOrigin() << " and " << storeInventory.foods[itemIndex].getName() <<" tastes " <<storeInventory.foods[itemIndex].getTaste() << "."<< endl;
                cout << "Each " << storeInventory.foods[itemIndex].getName() << " costs " << storeInventory.foods[itemIndex].getPrice() <<" dollars." << endl;
                
                cout << "Would you like to favorite this item?: (y)es or (n)o?" << endl;
                getline(cin, favOrNot);
                while(!(favOrNot=="n"||favOrNot=="y"))
                {
                    cout <<"Please enter a valid option from these choices : (y)es or (n)o" << endl;
                    getline(cin,favOrNot);
                }
                if(favOrNot=="y")
                {
                    setCustFavs(storeInventory.foods[itemIndex].getName(),whoIs);
                }
            }
            else
            {
                cout << "Big error in search function when displaying item information." << endl;
                exit(0);
            }
        }
        searchItems(whoIs,0);
    }
    
}
bool Store::doesItemExist(string whatItem)
{
    bool exists=false;
    string itemChoice=whatItem;
    int itemIndex=-1;
        
    for(int i=0; i<storeInventory.clothes.size();i++)
    {
        if(itemChoice==storeInventory.clothes[i].getType())
        {
            exists=true;
            itemIndex=i;
        }
    }
    for(int i=0; i<storeInventory.electronics.size();i++)
    {
        if(itemChoice==storeInventory.electronics[i].getName())
        {
            exists=true;
            itemIndex=i;
        }
    }
    for(int i=0; i<storeInventory.foods.size();i++)
    {
        if(itemChoice==storeInventory.foods[i].getName())
        {
            exists=true;
            itemIndex=i;
        }
    }
    return exists;
}
int Store::whereDoesItemExist(string whatItem)
{
    bool exists=doesItemExist(whatItem);
    string itemChoice=whatItem;
    int itemIndex=-1;
    if(exists)    
    {   for(int i=0; i<storeInventory.clothes.size();i++)
        {
            if(itemChoice==storeInventory.clothes[i].getType())
            {
                exists=true;
                itemIndex=i;
            }
        }
        for(int i=0; i<storeInventory.electronics.size();i++)
        {
            if(itemChoice==storeInventory.electronics[i].getName())
            {
                exists=true;
                itemIndex=i;
            }
        }
        for(int i=0; i<storeInventory.foods.size();i++)
        {
            if(itemChoice==storeInventory.foods[i].getName())
            {
                exists=true;
                itemIndex=i;
            }
        }
    }
    else if(!exists)
    {
        cout << "A major error was about to be caused returning the position of an item so the program was terminated" << endl;
        exit(0);
    }
    else
    {
        cout << "A major error was about to be caused returning the position of an item so the program was terminated" << endl;
        exit(0);
    }
    
    return itemIndex;
}
Customer Store::getCustomerAtIndex(unsigned int index)
{
    return customers[index];
}
string Store::getItemType(string itemName)
{
    bool exists=doesItemExist(itemName);
    string itemChoice=itemName;
    int itemIndex=-1;
    string whatIsType;
    if(exists)    
    {   for(int i=0; i<storeInventory.clothes.size();i++)
        {
            if(itemChoice==storeInventory.clothes[i].getType())
            {
                exists=true;
                itemIndex=i;
                whatIsType="clothing";
            }
        }
        for(int i=0; i<storeInventory.electronics.size();i++)
        {
            if(itemChoice==storeInventory.electronics[i].getName())
            {
                exists=true;
                itemIndex=i;
                whatIsType="electronic";
            }
        }
        for(int i=0; i<storeInventory.foods.size();i++)
        {
            if(itemChoice==storeInventory.foods[i].getName())
            {
                exists=true;
                itemIndex=i;
                whatIsType="food";
            }
        }
    }
    else if(!exists)
    {
        cout << "A major error was about to be caused returning the type of an item so the program was terminated." << endl;
        exit(0);
    }
    else
    {
        cout << "A major error was about to be caused returning the type of an item so the program was terminated." << endl;
        exit(0);
    }
    
    return whatIsType;
}
string Store::findObject(string itemType, int itemPos)
{
    if(itemType=="food")
    {
        return storeInventory.foods[itemPos].getName();
    }
    else if(itemType=="electronic")
    {
        return storeInventory.electronics[itemPos].getName();
    }
    else if(itemType=="clothing")
    {
        return storeInventory.clothes[itemPos].getType();
    }
}
void Store::setCustFavs(string itemName, int whoIs)
{
    int itemPos = whereDoesItemExist(itemName);
    string ItemType=getItemType(itemName);
    int k=-1;
    string theItem=findObject(ItemType,itemPos);
    
    if(ItemType=="food")
    {
        k=0;
        customers[whoIs].setFavoriteAtIndex(k, theItem);
        cout << "Item has been favorited!" << endl;
    }
    else if(ItemType=="electronic")
    {
        k=2;
        customers[whoIs].setFavoriteAtIndex(k, theItem);
        cout << "Item has been favorited!" << endl;
    }
    else if(ItemType=="clothing")
    {
        k=1;
        customers[whoIs].setFavoriteAtIndex(k, theItem);
        cout << "Item has been favorited!" << endl;
    }
    else
    {
        cout << "Major error setting favorite items! Program terminated." << endl;
        exit(0);
    }
    return;
}

Store::~Store()
{
    
};