/*
Author: Tyler Mooney
Date: March 31st, 2020
Professor: Khiem Le
Compiler: GNU GCC

Purpose: Program will have user choice from a menu of options,
all pertaining to managing a bank account(s)

Notes:
Menu options 5, 6, and 7 are extra credit

Menu Options:
    1: Create Account
    2: Deposit
    3: Withdraw
    4: Display All Accounts
    5: Delete Owner
    6: Add owner
    7: Delete Account
    8: Quit
*/

#include "Account.h"
#include <iostream>
#include <iomanip>

using namespace std;

//dynamic array initialization
const int MAX_NUM_ACCOUNTS = 4;
Account * accountArray[MAX_NUM_ACCOUNTS];

//function header
bool accountExist(int, int, int &);

int main()
{
    //variable and pointer initialization
    int choice = 0, numberOwners = 0, numAccounts = 0, accountNumber = 0, index = 0;
    int temp = 0;
    double amount = 0;

    //setting each element to a null pointer as instructed in the homework directions
    accountArray[0] = nullptr;
    accountArray[1] = nullptr;
    accountArray[2] = nullptr;
    accountArray[3] = nullptr;

    while(choice != 8)
    {
        //Display menu and acquire user choice
        cout << "Menu\n----\n";
        cout << "1->Create account 2->Deposit   3->Withdraw     4->Display \n";
        cout << "5->Delete owner   6->Add owner 7->Delete accnt 8->Quit    \n";
        cin >> choice;

        switch(choice)
        {
        case 1:
            //Prompting user for number of owners and amount
            if(numAccounts >= MAX_NUM_ACCOUNTS)
            {
                cout << "Max number of accounts reached, cannot add a new account\n";
            }
            else
            {
                //prompt user for number of owners and account balance
                //We have a cin.ignore here in order to make first name work
                cout << "Enter number of owners: ";
                cin >> numberOwners;
                cout << "Enter amount: ";
                cin >> amount;
                cin.ignore();

                //We use a temporary Account pointer to allow transfer of data into array
                Account * tempAccount = new Account(numberOwners, amount);
                accountArray[numAccounts] = tempAccount;

                //populating the account owner array
                for(int i = 0; i < numberOwners; i++)
                {
                    Person tempPerson;
                    cout << "Enter owner's name: ";
                    getline(cin, tempPerson.name);
                    cout << "Enter owner's DOB, month, day then year: ";
                    cin >> tempPerson.DOB.month >> tempPerson.DOB.day >> tempPerson.DOB.year;
                    cout << "Enter owner's address: ";
                    cin.ignore();
                    getline(cin, tempPerson.address);
                    accountArray[numAccounts]->setOwner(i, tempPerson);

                }

                cout << "Account #" << accountArray[numAccounts]->getAccountNumber() << " created\n";
                numAccounts++;
            }
            break;
        case 2:
            cout << "Enter account number: ";
            cin >> accountNumber;

            //input validation
            if(accountExist(accountNumber, numAccounts, index))
            {
                cout << "Enter amount: ";
                cin >> amount;

                //Checking to see if withdrawal went through
                temp = accountArray[index]->deposit(amount);
                if(temp == 0)
                    cout << "New balance is $" << fixed << setprecision(2) << accountArray[index]->getBalance() << endl;
                else
                    cout << "Amount cannot be negative, deposit not executed\n";
            }
            else
                cout << "No such account\n";

            break;
        case 3:
            cout << "Enter account number: ";
            cin >> accountNumber;

            //input validation
            if(accountExist(accountNumber, numAccounts, index))
            {
                cout << "Enter amount: ";
                cin >> amount;

                //Checking to see if withdrawal went through
                temp = accountArray[index]->withdraw(amount);
                if(temp == 0)
                    cout << "New balance is $" <<  fixed << setprecision(2) << accountArray[index]->getBalance() << endl;
                else if(temp == 1)
                    cout << "Insufficient balance, withdrawal not executed\n";
                else
                    cout << "Amount cannot be negative, withdrawal not executed\n";
            }
            else
                cout << "No such account\n";

            break;
        case 4:
            //Printing out all account information
            for(int i = 0; i < numAccounts; i++)
            {
                cout << "Account Number: " << accountArray[i]->getAccountNumber();
                cout << "\n--------------\n";
                for(int j = 0; j < accountArray[i]->getNumOwners(); j++)
                {
                    cout << "*Name: " << accountArray[i]->getOwner(j).name;
                    cout << ", DOB: " << accountArray[i]->getOwner(j).DOB.month << '/'
                    << accountArray[i]->getOwner(j).DOB.day << '/'
                    << accountArray[i]->getOwner(j).DOB.year << endl;
                    cout << "Address: " << accountArray[i]->getOwner(j).address << endl;
                }
                cout << "*Balance: $" <<  fixed << setprecision(2) <<  accountArray[i]->getBalance() << " \n";
            }
            break;
        case 5:

            break;
        case 6:
            break;
        case 7:
            /*
            cout << "Enter account number: ";
            cin >> accountNumber;

            //input validation
            if(accountExist(accountNumber, numAccounts, index))
            {
                delete accountArray[index];
            }
            else
                cout << "No such account\n";
                */
            break;
        }
    }

    exit(EXIT_SUCCESS);
}

//Function will check whether or not the account entered exists through a linear search
//Records the index at which the account is found
bool accountExist(int accountNumber, int numAccounts, int & index)
{
    for(int i = 0; i < numAccounts; i++)
    {
        if(accountNumber == accountArray[i]->getAccountNumber())
        {
            index = i;
            return true;
        }
    }
    return false;
}
