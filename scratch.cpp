for(int i=0; i<storeInventory.electronics.size(); i++)
    {
        updateInventory << storeInventory.electronics[i].getName()<<","<< storeInventory.electronics[i].getPrice()<<","<< storeInventory.electronics[i].getQuantity()<<","<< storeInventory.electronics[i].getdeviceType()<<"," <<storeInventory.electronics[i].getWarrantyLength();
    }





for(int i=0; i<storeInventory.clothes.size(); i++)
    {
        updateInventory << storeInventory.clothes[i].getType()<<","<< storeInventory.clothes[i].getPrice()<<","<< storeInventory.clothes[i].getQuantity()<<","<< storeInventory.clothes[i].getColor()<<"," <<storeInventory.clothes[i].getSize() <<","<<"PLACEHOLDER";
    }