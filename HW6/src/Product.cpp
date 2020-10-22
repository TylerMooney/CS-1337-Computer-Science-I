#include <iostream>
#include "Product.h"

using namespace std;

void Product :: setProductAttributes(string tempPLU, string tempName, int tempType, double tempPrice, int tempInventory)
{
    PLU = tempPLU;
    name = tempName;
    type = tempType;
    price = tempPrice;
    inventory = tempInventory;
}

void Product :: setInventory(int tempInventory)
{
    inventory = tempInventory;
}

string Product :: getPLU() const
{
    return PLU;
}

string Product :: getName() const
{
    return name;
}

int Product :: getType() const
{
    return type;
}

double Product :: getPrice() const
{
    return price;
}

int Product :: getInventory() const
{
    return inventory;
}
