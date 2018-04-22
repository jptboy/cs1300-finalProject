#include <iostream>
#include <fstream>
#include "Inventory.h"
#include <vector>
#include <stdlib.h>
//#include "Split.h"
using namespace std;
int Split(string s, char a, string word[], int size)//split function from recitation 7
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

Inventory::Inventory()
{
    loadInventory("inventoryfile.txt");
};

void Inventory::loadInventory(string inventoryFile)
{
    ifstream loadInvent(inventoryFile);
    
    string wholeLineFromFile;
    
    vector <string> holdEl;
    vector <string> holdCl;//vectors to hold raw strings from the inventory file
    vector <string> holdFd;
    
    int iterationCounter=0;//this variable tracks if there has been a break in the inventory file
    int fdCount=0;//this variable tracks the number of food strings loaded from the inventory file and so on for clothes and electronics in the next 2 variables
    int elCount=0;
    int clCount=0;

    string fooDHolderArr[5];
    string eLHolderArr[5];
    string cLHolderArr[6];

    //int lineNum=0;//debugging variable

    if(!loadInvent.is_open())
    {
        cout << "Error loading inventory file!" << endl;
        exit(0);
    }

    while(getline(loadInvent, wholeLineFromFile))
    {
        if(wholeLineFromFile.length()==0)
        {
            iterationCounter++;//if it detects that the line length is equal to zero then the program knows there has been a break in the text file
        }
        else if(iterationCounter==0 && wholeLineFromFile.length()!=0)
        {
            holdFd.push_back(wholeLineFromFile);
            fdCount++;
        }
        else if(iterationCounter==1 && wholeLineFromFile.length()!=0)
        {
            holdEl.push_back(wholeLineFromFile);
            elCount++;
        }
        else if(iterationCounter==2 && wholeLineFromFile.length()!=0)
        {
            holdCl.push_back(wholeLineFromFile);
            clCount++;
        }
        else
        {
            cout << "Bug with loading the vectors with the raw strings for parsing for creating inventory!" << endl;
            //cout << wholeLineFromFile.length() << " " << lineNum<< endl;
        }
        //lineNum++;
    }
    try
    {
        for(int i=0; i<holdFd.size(); i++)
        {
            Split(holdFd[i],',',fooDHolderArr,5);
            Food newFoodItem(fooDHolderArr[0],stod(fooDHolderArr[1]),stod(fooDHolderArr[2]),fooDHolderArr[3],fooDHolderArr[4]);  //loading each of the vectors for clothes and electronics and foods with objects
            foods.push_back(newFoodItem);
        }

        for(int i=0; i<holdEl.size(); i++)
        {
            Split(holdEl[i],',',eLHolderArr,5);
            Electronic newElectronicItem(eLHolderArr[0],stod(eLHolderArr[1]),stod(eLHolderArr[2]),eLHolderArr[3],stoi(eLHolderArr[4]));
            electronics.push_back(newElectronicItem);
        }

        for(int i=0; i<holdCl.size(); i++)
        {
            Split(holdCl[i],',',cLHolderArr,6);
            Clothing newClothing(cLHolderArr[0],stoi(cLHolderArr[4]),cLHolderArr[3],stod(cLHolderArr[1]),stod(cLHolderArr[2]));
            clothes.push_back(newClothing);
        }

        //cout << "Success! The inventory has been loaded!" << endl;
    }
    catch(...)
    {
        cout << "Error loading inventory!" << endl;
    }
    
    
}
void Inventory::addItem()
{

}
void Inventory::deleteItem()
{

}
void Inventory::getItem()
{

}
Inventory::~Inventory()
{
    
};