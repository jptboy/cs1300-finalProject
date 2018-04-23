Author: Ayush Khanal CS1300 Fall 2017
Recitation: 204- Chelsea Chandler
Cloud9 Workspace Editor Link: https://ide.c9.io/ayushkhanal/ayushkhanalcsci1300
Hmwk8/Final Project

Sources:
1.
Atul showed me how to generate random numbers

2.
I pretty much knew everything else and I learned structs by messing with them

I wrote a shell script that is supposed to compile and run my output file
So you can give it a go 

$ chmod +x ./runprogram.sh
$ ./runprogram.sh

The bash command to compile my program is here though:

g++ -std=c++11 storeDriver.cpp Store.cpp Inventory.cpp Customer.cpp Electronic.cpp Clothing.cpp Food.cpp Item.cpp -o ./test.o

My program is basically like a Inventory managment/backend system interfaced with a front-end CLI interface for customers to purchase items, view items, favorite items, and get reccomendations for items. 
They can only purchase items with store credit and they can add store credit.
The main cool thing about my program is the createOrder() function and the makeOrders() function which make orders for items that ran out of stock and these functions even work when the user quits the program(everything else also persists with file IO obviously).

I don't really know if we were to include a file like this with our project, but I feel like I would go crazy without some sort of guide having to grade 40 projects.

Most of my code is in the Store class which does pretty much everything and the Inventory class which manages the inventory. The flow of the program is somewhat like the library program but the scope and functionality of this is as if the Library program took steroids.

The steps to my program are as follow:
    Load Files
    Prompt Customer to ask them what they want to do
    Customer has an option to leave the store to simulate something that happens in real life
    Customer does things like search, buy, and browse
    Customer quits
    The program writes data to files.
    
A lot of my code is boring and unintresting and just normal stuff but what I am proud of is the order system.
There is a struct for a order that has all the information related to the order and there is a vector of these structs as a member of the Store Class.
When the customer tries to buy a out of stock thing they are prompted to ask the manager to order it and he does.
A instance of a order struct is generated and placed in the order vector and every time the customer goes back to the main menu the main menu checks if any orders have came in.
Also loadFiles also checks this because orders persist in the orders.txt file if the user quits.
