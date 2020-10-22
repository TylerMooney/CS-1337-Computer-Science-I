/*
Author: Tyler Mooney
Date: February 6th, 2020
Professor: Khiem Le
Compiler: GNU GCC

Purpose: Read in grocery product records from a file, then store the information in
parallel arrays. The user will have the ability to checkout multiple products and
print out the current inventory level of all products.

Notes:
Store each product record in parallel arrays.
Functions:
    readInventory: Populates the arrays with the information from the file
    printInventory: Prints out the current inventory
    checkout: Has the user enter PLU of a product and the quantity they
    wish to purchase for at least one product. Returns the total purchase price.
    linearSearchPLU: A linear search that checks if the PLU exists within the array
*/


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//Function Prototypes
bool readInventory(string,string *,string *,int *,double *,int *,const int);
void printInventory(string *,string *,int *,double *,int *,const int);
double checkout(string *, double *, int *,const int);
int linearSearchPLU(string *,const int, string);

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
    while(inFile >> line >> line >> line >> line >> line)
        numRecords++;
    cout << "There are " << numRecords << " records in the file\n";

    inFile.close();

    //Array pointers and constant int initializations
    const int ARR_SIZE = numRecords;
    double * priceArrPtr = new double[ARR_SIZE];
    string * PLUArrPtr = new string[ARR_SIZE];
    string * nameArrPtr = new string[ARR_SIZE];
    int * typeArrPtr = new int[ARR_SIZE];
    int * invenArrPtr = new int[ARR_SIZE];

    //populating the arrays and checking if file opens
    bool openSuccess = false;
    openSuccess = readInventory(fileName, PLUArrPtr, nameArrPtr, typeArrPtr, priceArrPtr, invenArrPtr, ARR_SIZE);

    //Checks if file opened unsuccessfully in the function, ends program if so
    if (!openSuccess)
    {
        cout << "Could not open file\nExiting" << endl;
        inFile.close();
        exit(EXIT_FAILURE);
    }

    //print out inventory read from file
    cout << "\nInventory read from file\n------------------------\n";
    printInventory(PLUArrPtr, nameArrPtr, typeArrPtr, priceArrPtr, invenArrPtr, ARR_SIZE);

    //Establishing loop where user chooses to checkout, print current inventory, or quit the program
    int choice = 0;
    double total = 0;

    while(choice != 3)
    {
        cout << "1 - Checkout\n2 - Print current inventory\n3 - Quit\n";
        cin >> choice;

        //Checks if the user has chosen a valid choice, if not loops
        //until they choose a valid option
        while(choice != 1 && choice != 2 && choice != 3)
        {
            cout << "Invalid choice, reenter: \n";
            cin >> choice;
        }

        /*
        checks which choice is chosen and proceeds accordingly
        1 - activates the checkout function, and prints total
        2 - activates the printInventory function
        3 - has the loop end and the program closes
        */
        if(choice == 1)
        {
            total = checkout(PLUArrPtr, priceArrPtr, invenArrPtr, ARR_SIZE);
            cout << "Total is: $" << total << endl << endl;
        }
        else if(choice == 2)
        {
            cout << "Current inventory\n-----------------\n";
            printInventory(PLUArrPtr, nameArrPtr, typeArrPtr, priceArrPtr, invenArrPtr, ARR_SIZE);
        }
    }

    //Printing out the final updated inventory
    cout << "Updated inventory\n-----------------\n";
    printInventory(PLUArrPtr, nameArrPtr, typeArrPtr, priceArrPtr, invenArrPtr, ARR_SIZE);

    //releasing all of the memory and setting them null
    delete [] priceArrPtr;
    delete [] PLUArrPtr;
    delete [] nameArrPtr;
    delete [] typeArrPtr;
    delete [] invenArrPtr;

    priceArrPtr = nullptr;
    PLUArrPtr = nullptr;
    nameArrPtr = nullptr;
    typeArrPtr = nullptr;
    invenArrPtr = nullptr;

    cout << "Exiting\n";
    exit(EXIT_SUCCESS);
}

//Function populates the arrays with the products' information from the file
bool readInventory(string fileName,string * PLUArrPtr,string * nameArrPtr,int * typeArrPtr,double * priceArrPtr,int * invenArrPtr, const int ARR_SIZE)
{
    //open file
    ifstream inFile;
    inFile.open(fileName);

    //checks if file opened incorrectly, if so returns false
    if (inFile.fail())
    {
        inFile.close();
        return false;
    }

    //Variable initialization
    string PLU, name;
    int type = 0, inven = 0;
    double price = 0;

    //loops which populate the arrays
    for(int i = 0; i < ARR_SIZE; i++)
    {
        inFile >> PLU >> name >> type >> price >> inven;
        PLUArrPtr[i] = PLU;
        nameArrPtr[i] = name;
        typeArrPtr[i] = type;
        priceArrPtr[i] = price;
        invenArrPtr[i] = inven;
    }
    inFile.close();
    return true;
}


//Function prints out the current inventory
void printInventory(string * PLUArrPtr,string * nameArrPtr,int * typeArrPtr,double * priceArrPtr,int * invenArrPtr,const int ARR_SIZE)
{
    //loops through each record and prints out the details
    for(int i = 0; i < ARR_SIZE; i++)
    {
        cout << "PLU: " << PLUArrPtr[i] << ", " << left << setw(17) << nameArrPtr[i] << right << ", type: " << typeArrPtr[i]
             << ", unit price: " << setw(5) << priceArrPtr[i] << ", inventory: " << invenArrPtr[i] << endl;
    }
}

//Function has user input a PLU and quantity for at least one item
//to give them a purchase total and updates the current inventory
//Uses the linearSearch
double checkout(string * PLUArrPtr, double * priceArrPtr, int * invenArrPtr,const int ARR_SIZE)
{
    //variable initialization
    string PLU;
    int quantity = 0, index = 0;
    double total = 0;

    //Prompt user for PLU
    while(PLU != "0")
    {
        cout << "Enter PLU, 0 if done: ";
        cin >> PLU;

        //if PLU is not zero, proceed to ask for quantity
        if(PLU != "0")
        {
            cout << "Enter quantity: ";
            cin >> quantity;

            //loops asking for a correct quantity if quantity isn't valid
            while(quantity <= 0)
            {
                cout << "Quantity must be positive, reenter: ";
                cin >> quantity;
            }

            //checks to see if PLU is valid through linear search
            index = linearSearchPLU(PLUArrPtr, ARR_SIZE, PLU);
            if(index == -1)
                cout << "PLU not found\n";
            else
            {
                //checks if quantity inputted is greater than current inventory
                //if so gives user the the entire amount left in inventory
                if(quantity > invenArrPtr[index])
                {
                    total += (priceArrPtr[index] * invenArrPtr[index]);
                    invenArrPtr[index] = 0;
                }
                else
                {
                    total += (priceArrPtr[index] * quantity);
                    invenArrPtr[index] -= quantity;
                }
            }

            cout << endl;
        }
    }

    return total;
}

//Function that does a linear search of an array
//returns -1 if the inputted PLU is not found within the array
int linearSearchPLU(string * PLUArrPtr, const int ARR_SIZE, string PLU)
{
    int index = 0;

    while (index < ARR_SIZE)
    {
        if (PLUArrPtr[index] == PLU)
            return index;
        index++;
    }

    return -1;
}
