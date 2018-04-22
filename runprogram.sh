#!/bin/bash
chmod +x ./storeDriver.cpp
chmod +x ./Clothing.cpp
chmod +x ./Store.cpp
chmod +x ./Customer.cpp
chmod +x ./Electronic.cpp
chmod +x ./Item.cpp
chmod +x ./Inventory.cpp
chmod +x ./Food.cpp
g++ -std=c++11 storeDriver.cpp Store.cpp Inventory.cpp Customer.cpp Electronic.cpp Clothing.cpp Food.cpp Item.cpp -o ./test.o
chmod +x ./test.o
./test.o
exit 0

