/*
Author: Tyler Mooney
Date: March 12, 2020
Professor: Khiem Le
Compiler: GNU GCC

Purpose: Acquire a list of products and fill an array of objects
with the each products' information.

Notes:
Used as reference: 2_25_seperate Exo, HW2
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Product.h"

using namespace std;


int main()
{
    //Variable initialization
    string fileName, line;
    int numRecords = 0;

    //prompt user for file name
    cout << "Enter the file name: ";
    cin >> fileName;

    //open file and reads the number of records
    ifstream inFile;
    inFile.open(fileName);

    //Checks if file will open, if it doesn't it will close the program
    if (inFile.fail())
    {
        cout << "Could not open file\nExiting" << endl;
        inFile.close();
        exit(EXIT_FAILURE);
    }

    //counting the amount of records and printing it out
    while(getline(inFile, line))
        numRecords++;
    cout << "There are " << numRecords << " records in the file\n";
    inFile.close();

    //Creating array of objects and populating it
    const int ARR_SIZE = numRecords;
    Product * productList= new Product[ARR_SIZE];

    //opening file again, and variable initialization
    inFile.open(fileName);
    string PLU, name;
    int type = 0, inven = 0;
    double price = 0;

    //loop which populates the array
    for(int i = 0; i < ARR_SIZE; i++)
    {
        inFile >> PLU >> name >> type >> price >> inven;
        productList[i].setProductAttributes(PLU, name, type, price, inven);

    }
    inFile.close();

    //Printing out information of all objects
    cout << "\nContent of object array\n-----------------------\n";
    for(int i = 0; i < ARR_SIZE; i++)
    {
        cout << "PLU: " << productList[i].getPLU() << ", " << left << setw(17) << productList[i].getName()
             << right << ", type: " << productList[i].getType() << ", unit price: " << setw(5)
             << productList[i].getPrice() << ", inventory: " << productList[i].getInventory() << endl;
    }

    //Establishing loop where user chooses to checkout, print current inventory, or quit the program
    int choice = 0;
    while(choice != 4)
    {
        cout << "\nMenu\n----\n1->Add to inventory           , 2->Subtract from inventory\n";
        cout << "3->Print info for all products, 4->Exit\n";
        cin >> choice;

        //Checks if the user has chosen a valid choice, if not loops
        //until they choose a valid option
        while(choice != 1 && choice != 2 && choice != 3 && choice != 4)
        {
            cout << "Invalid choice, reenter: \n";
            cin >> choice;
        }

        /*
        checks which choice is chosen and proceeds accordingly
        1 - Adds to the inventory of the inputted item
        2 - Subtracts to the inventory of the inputted item
        3 - Prints out information for all products
        */
        bool isValid = false;
        int element = 0;
        switch(choice)
        {
        case 1:
            //Acquire PLU and it's location if valid
            cout << "Enter the PLU: ";
            cin >> PLU;

            //Checking if input is a valid PLU
            for(int i = 0; i < ARR_SIZE; i++)
                if(productList[i].getPLU() == PLU)
                {
                    isValid = true;
                    element = i;
                }

            //if Input is valid proceed to prompt user to add inventory, else print out an error
            if(!isValid)
                cout << "PLU not found\n";
            else
            {
                int amount = 0;
                cout << "Enter amount to add: ";
                cin >> amount;

                if(amount > 0)
                {
                    amount += productList[element].getInventory();
                    productList[element].setInventory(amount);
                }
                else
                    cout << "Amount must be > 0\n";
            }
            break;
        case 2:
            //Acquire PLU and it's location if valid
            cout << "Enter the PLU: ";
            cin >> PLU;

            //Checking if input is a valid PLU
            for(int i = 0; i < ARR_SIZE; i++)
            {
                if(productList[i].getPLU() == PLU)
                {
                    isValid = true;
                    element = i;
                }
            }

            //if Input is valid proceed to prompt user to subtract inventory, else print out an error
            if(!isValid)
                cout << "PLU not found\n";
            else
            {
                int amount = 0;
                cout << "Enter amount to subtract: ";
                cin >> amount;

                if(amount > 0)
                {
                    //checks to make sure whether or not the amount entered
                    //will make the inventory less than zero, sets to zero if so
                    if((amount > productList[element].getInventory()))
                       productList[element].setInventory(0);
                    else
                    {
                        //multiply by -1 in order to set it as a positive integer after
                        // the subtraction
                        amount -= productList[element].getInventory();
                        productList[element].setInventory((amount * (-1)));
                    }
                }
                else
                    cout << "Amount must be > 0\n";
            }
            break;
        case 3:
            cout << "Current inventory\n-----------------\n";
            for(int i = 0; i < ARR_SIZE; i++)
            {
                cout << "PLU: " << productList[i].getPLU() << ", " << left << setw(17) << productList[i].getName()
                     << right << ", type: " << productList[i].getType() << ", unit price: " << setw(5)
                     << productList[i].getPrice() << ", inventory: " << productList[i].getInventory() << endl;
            }
            break;
        }
    }

    delete [] productList;
    exit(EXIT_SUCCESS);
}
