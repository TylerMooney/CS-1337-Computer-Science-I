/*
Author: Tyler Mooney
Date: February 27th, 2019
Professor: Khiem Le
Compiler: GNU GCC

Purpose: Program will manage bank accounts. Users can either enter
in data for a specific account, search for a specific account, or
display all accounts' information in a list

Notes:
Functions:
    int main:
        Purpose:
            Prompt the user to enter the maximum number of Accounts
            Perform input validation (valid value is an integer > 0)
            Dynamically allocate an array of Accounts of the size entered
            by the user.
            List choices and have user choose one and perform necessary actions
            Choices:
                1: Enter data for specific account
                2: Display data for specific account
                3: Display data for all accounts
                4: Quit
    void populateAccount:
        Parameters: Array of Accounts(pass by reference), Number of Accounts populated(pass by reference),
            Size of the array (pass by value)
        Purpose:
            Prompt user for data and populate the next available element
            of the array. Check input validation. Print error if no space left.
    void printAccount:
        Parameters: Account structure variable (pass by reference)
        Purpose: Prints the content of the structure variable acquired
    bool isValidSize:
        Parameters: Char array (pass by value)
        Purpose: Makes sure that the input is a digit, and is not zero
    bool isValidChoice:
        Parameters: Char array (pass by value)
        Purpose: Makes sure that the input is a digit, and is either 1,2,3, or 4
    bool isValidBalance:
        Parameters: Char array (pass by value)
        Purpose: Makes sure that the input is just digits and has only one '.', and is not 0
    int convertToInt:
        Parameters: String (pass by value)
        Purpose: converts string into an integer
    double convertToDouble:
        Parameters: String (pass by value)
        Purpose: converts string into a double
    void duplicate:
        Parameters: Array of Accounts(pass by reference), Number of Accounts populated(pass by reference),
        Number of attempts (pass by reference), inputted string (pass by reference)
*/


#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

//Structure initializations
struct Person
{
    string name;
    string address;
};

struct Account
{
    int accountNumber;
    Person ownerInfo;
    double balance;
};

//Function Prototypes
void populateAccount(Account *, int &, int);
void printAccount(const Account &);
bool isValidSize(string);
bool isValidChoice(string);
bool isValidBalance(string);
int convertToInt(string);
double convertToDouble(string);
void duplicate(Account *, int &, int &, string &);

int main()
{
    //Variable initialization
    bool valid = false;
    string strHold;
    int arrSize = 0, choice = 0, numAcc = 0;

    cout << "Enter max number of accounts: ";
    getline(cin, strHold);

    //input validation, 4 attempts to correct
    valid = isValidSize(strHold);
    for(int i = 0; valid != true; i++)
    {
        if(i == 4)
        {
            cout << "Too many unsuccessful attempts, exiting";
            exit(EXIT_FAILURE);
        }
        cout << "Invalid value, please reenter: ";
        getline(cin, strHold);
        valid = isValidSize(strHold);
    }

    //Dynamic allocation of an array of Account
    arrSize = convertToInt(strHold);
    Account * accPtr = new Account[arrSize];

    //Display list of choices and then execute choice chosen
    while(choice != 4)
    {
        cout << endl << "Menu:" << endl;
        cout << "1->Enter data for specific account, 2->Display data for specific account" << endl;
        cout << "3->Display data for all accounts  , 4->Quit:" << endl;
        getline(cin, strHold);


        //input validation, 4 attempts to correct
        valid = isValidChoice(strHold);
        for(int i = 0; valid != true; i++)
        {
            if(i == 4)
            {
                cout << "Too many unsuccessful attempts, exiting";
                exit(EXIT_FAILURE);
            }
            cout << "Invalid choice, please reenter: ";
            getline(cin, strHold);
            valid = isValidChoice(strHold);
        }

        //If 4 is chosen, the loop will just end
        choice = convertToInt(strHold);
        switch(choice)
        {
        case 1:
            //Populates an account, if the array is not full
            populateAccount(accPtr, numAcc, arrSize);
            break;
        case 2:
            //prints out a specific account
            if(numAcc <= arrSize)
            {
                int entry = 0;
                cout << "Enter account number: ";
                getline(cin, strHold);

                //input validation, 4 attempts to correct
                //We use isValidSize because it still accomplishes the check we need
                valid = isValidSize(strHold);
                for(int i = 0; valid != true; i++)
                {
                    if(i == 4)
                    {
                        cout << "Too many unsuccessful attempts, exiting";
                        exit(EXIT_FAILURE);
                    }
                    cout << "Invalid value, please reenter: ";
                    getline(cin, strHold);
                    valid = isValidSize(strHold);
                }

                //checking to find the account index
                entry = convertToInt(strHold);
                int index = 0;
                while (index < numAcc)
                {
                    if (accPtr[index].accountNumber == entry)
                        break;
                    index++;
                }
                if(index == numAcc)
                    cout << "Account not found" << endl;
                else
                    printAccount(accPtr[index]);
            }
            break;
        case 3:
            //prints out all accounts
            for(int i = 0; i < numAcc; i++)
                printAccount(accPtr[i]);
            break;
        }
    }

    //clearing memory and exiting program
    delete[] accPtr;
    accPtr = nullptr;
    exit(EXIT_SUCCESS);
}

//Prompts user for each individual component of an account,
//and assigns it to the next array component available
void populateAccount(Account * accPtr, int & numAcc, int arrSize)
{

    //checks if array is full or not
    if(numAcc < arrSize)
    {
        //Variable initialization
        bool valid = false;
        string strHold;

        cout << "Enter account number: ";
        getline(cin, strHold);

        //input validation
        //We use isValidSize because it performs the proper check
        valid = isValidSize(strHold);
        for(int i = 0; valid != true; i++)
        {
            if(i == 4)
            {
                cout << "Too many unsuccessful attempts, exiting";
                exit(EXIT_FAILURE);
            }
            cout << "Invalid value, please reenter: ";
            getline(cin, strHold);
            valid = isValidSize(strHold);
        }

        //checking for a duplicate account
        int attempts = 0;
        duplicate(accPtr, numAcc, attempts, strHold);

        //Program proceeds as normal and asks for remaining information
        cout << "Enter balance: ";
        getline(cin, strHold);
        //input validation
        valid = isValidBalance(strHold);
        for(int i = 0; valid != true; i++)
        {
            if(i == 4)
            {
                cout << "Too many unsuccessful attempts, exiting";
                exit(EXIT_FAILURE);
            }
            cout << "Invalid value, please reenter: ";
            getline(cin, strHold);
            valid = isValidBalance(strHold);
        }
        accPtr[numAcc].balance = convertToDouble(strHold);

        cout << "Enter owner's name: ";
        getline(cin, accPtr[numAcc].ownerInfo.name);

        cout << "Enter owner's address: ";
        getline(cin, accPtr[numAcc].ownerInfo.address);

        numAcc++;
    }
    else
        cout << "Cannot execute, array is full" << endl;

}

//Prints out all the information for a specified account
void printAccount(const Account & acc)
{
    cout << "Account #: " << acc.accountNumber << endl;
    cout << "Owner's name: " << acc.ownerInfo.name << endl;
    cout << "Owner's address: " << acc.ownerInfo.address << endl;
    cout << "Balance: " << acc.balance << endl;
}

// Returns true if the string is just a digit
bool isValidSize(string strHold)
{
    for(unsigned int i = 0; i < strHold.length(); i++)
        if(!isdigit(strHold[i]))
            return false;

    //checks to make sure the string isn't 0
    string check = "0";
    if(strHold == check)
        return false;

    return true;
}

// Returns true if the string is just a digit, and is a valid choice
bool isValidChoice(string strHold)
{
    for(unsigned int i = 0; i < strHold.length(); i++)
        if(!isdigit(strHold[i]))
            return false;

    //checks to make sure the string is 1,2,3, or 4
    string check1 = "1", check2 = "2", check3 = "3", check4 = "4";
    if(strHold != check1 && strHold != check2 && strHold != check3 && strHold != check4)
        return false;

    return true;
}

//Returns true if the string is just a valid double
bool isValidBalance(string strHold)
{
    for(unsigned int i = 0; i < strHold.length(); i++)
        if(!isdigit(strHold[i]) && strHold[i] != '.')
            return false;

    //checks to make sure the string isn't 0
    string check = "0";
    if(strHold == check)
        return false;

    return true;
}

//converts string into an integer
int convertToInt(string strHold)
{
    int num = 0;
    char * charArr = new char[strHold.length()];

    for(unsigned int i = 0; i < strHold.length(); i++)
        charArr[i] = strHold[i];

    num = atoi(charArr);
    delete[] charArr;
    charArr = nullptr;
    return num;
}

//converts string into a double
double convertToDouble(string strHold)
{
    double num = 0;
    char * charArr = new char[strHold.length()];

    for(unsigned int i = 0; i < strHold.length(); i++)
        charArr[i] = strHold[i];

    num = atof(charArr);
    delete[] charArr;
    charArr = nullptr;
    return num;
}

//A function that checks whether or not the inputted account number is a duplicate
//Is recursive in order to check if the new input is not a duplicate too
void duplicate(Account * accPtr, int & numAcc, int & attempts, string & strHold)
{
    //checking to see if there is a duplicate account name
    int index = 0;
    int valid = false;

    accPtr[numAcc].accountNumber = convertToInt(strHold);
    while (index < numAcc)
    {
        if (accPtr[index].accountNumber == accPtr[numAcc].accountNumber)
        {
            attempts++;
            cout << "Duplicate account number" << endl;
            getline(cin, strHold);

            //input validation
            valid = isValidSize(strHold);
            while(valid != true)
            {
                attempts++;
                if(attempts == 4)
                {
                    cout << "Too many unsuccessful attempts, exiting";
                    exit(EXIT_FAILURE);
                }
                cout << "Invalid value, please reenter: ";
                getline(cin, strHold);
                valid = isValidSize(strHold);
                duplicate(accPtr, numAcc, attempts, strHold);
            }
            if(attempts == 4)
                {
                    cout << "Too many unsuccessful attempts, exiting";
                    exit(EXIT_FAILURE);
                }
            duplicate(accPtr, numAcc, attempts, strHold);
        }
        index++;
    }

}
