#!/bin/bash
chmod +x ./storeDriver.cpp
chmod +x ./Clothing.cpp
chmod +x ./Store.cpp
chmod +x ./Customer.cpp
g++ -std=c++11 storeDriver.cpp Store.cpp Customer.cpp Clothing.cpp Item.cpp -o test.o
chmod +x ./test.o
./test.o
exit 0

