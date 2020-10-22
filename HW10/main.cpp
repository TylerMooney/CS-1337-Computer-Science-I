/*
Author: Tyler Mooney
Date: April 26th, 2020
Professor: Khiem Le
Compiler: GNU GCC

Purpose: Display a menu of options. The user will choose
one option at a time. The options primarily revolve around
managing bank accounts (Regular or Premium).

Notes:
Print all money outputs up to two digits after the decimal point
Only need to use cin for strings
There is extra credit that revolves around the Transaction structure in Account.h
Input Validation Criteria:
    - Show error message if withdrawal amount is excessive.
    - Show error if deposit or withdrawal amount is not larger than 0
    - Show error if account is not created when trying to deposit or withdraw
    - Do not create more accounts past cap of MAX_NUM_ACCOUNTS
    - Show error message if the user does not meet the minimum required amount
    for a balance to create an account with
*/


#include <iostream>
#include <iomanip>
#include "Date.h"
#include "PremiumAccount.h"
#include "RegularAccount.h"

using namespace std;

//function prototype
bool accountExist(int, int, int &);

int main()
{
    //variable and pointer initialization
    int choice = 0, numAccounts = 0, accountNumber = 0, index = 0;
    double amount = 0;
    string name, date;
    bool check;
    const int MAX_NUM_ACCOUNTS = 5;
    Account * accountArray[MAX_NUM_ACCOUNTS];
    //Setting it to zero in order to complete base program and debug
    Date * tempDate = new Date;
    tempDate->set(0,0,0,0);


    while(choice != 6)
    {
        //Display menu and acquire user choice
        cout << "\n1->Create regular accnt, 2->Create premium accnt, 3->Deposit to accnt\n";
        cout << "4->Withdraw from accnt, 5->Print info accnts, 6->Quit\n";
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
                //prompt user for name, date, and amount
                cout << "Enter owner's name: ";
                cin >> name;
                cout << "Enter date, in the mm/dd/yyyy/hh format: ";
                cin >> date;
                cout << "Enter amount: ";
                cin >> amount;

                if(amount <= 0)
                {
                    cout << "Amount must be larger than 0\n";
                    break;
                }

                //For tokenization of the date string to set the date pointer
                //Setting it to zero in order to complete base program and debug
                Date * tempDate = new Date;
                tempDate->set(0,0,0,0);

                //We use a temporary Account pointer to allow transfer of data into array
                accountArray[numAccounts] = new RegularAccount(name, amount, *tempDate);

                //Printing out the acquired data
                cout << "Account created: \n";
                accountArray[numAccounts]->print();
                numAccounts++;
            }
            break;
        case 2:
            //Prompting user for number of owners and amount
            if(numAccounts >= MAX_NUM_ACCOUNTS)
            {
                cout << "Max number of accounts reached, cannot add a new account\n";
            }
            else
            {
                //prompt user for name, date, and amount
                cout << "Enter owner's name: ";
                cin >> name;
                cout << "Enter date, in the mm/dd/yyyy/hh format: ";
                cin >> date;
                cout << "Enter amount: ";
                cin >> amount;

                if(amount < 1000)
                {
                    cout << "Insufficient amount, you need at least 1000.00 Galactic units to open a premium account\n";
                    break;
                }

                //For tokenization of the date string to set the date pointer
                /*
                insert code here
                */


                //We use a temporary Account pointer to allow transfer of data into array
                accountArray[numAccounts] = new PremiumAccount(name, amount, *tempDate);

                //Printing out the acquired data
                cout << "Account created: \n";
                accountArray[numAccounts]->print();
                numAccounts++;
            }
            break;
        case 3:
            cout << "Enter account number: ";
            cin >> accountNumber;

            //input validation
            //linear search to determine whether account inputted exists
            for(int i = 0; i < numAccounts; i++)
            {
                if(accountNumber == accountArray[i]->getAccountNumber())
                {
                    index = i;
                    check = true;
                    break;
                }
                else
                {
                    check = false;
                }
            }

            if(check)
            {
                //proceeds with code if check comes back true
                cout << "Enter date, in the mm/dd/yyyy/hh format: ";
                cin >> date;
                cout << "Enter amount: ";
                cin >> amount;

                //Checking to see if withdrawal went through
                if(accountArray[index]->deposit(amount, *tempDate))
                    cout << "Withdraw executed: \n" << accountArray[index]->print();
                else
                    cout << "Amount cannot be negative, deposit not executed\n";
            }
            else
                cout << "No such account\n";
            break;
        case 4:
            cout << "Enter account number: ";
            cin >> accountNumber;

            //input validation
            //linear search to determine whether account inputted exists
            for(int i = 0; i < numAccounts; i++)
            {
                if(accountNumber == accountArray[i]->getAccountNumber())
                {
                    index = i;
                    check = true;
                    break;
                }
                else
                {
                    check = false;
                }
            }

            if(check)
            {
                //proceeds with code if check comes back true
                cout << "Enter date, in the mm/dd/yyyy/hh format: ";
                cin >> date;
                cout << "Enter amount: ";
                cin >> amount;
                cout << "Enter date, in the mm/dd/yyyy/hh format: ";
                cin >> date;

                //Checking to see if withdrawal went through
                if(accountArray[index]->withdraw(amount, *tempDate))
                    cout << "Withdraw executed: \n" << accountArray[index]->print();
                else
                    cout << "Amount cannot be negative, withdraw not executed\n";
            }
            else
                cout << "No such account\n";
            break;
        case 5:
            break;
        }
    }

    delete tempDate;
    tempDate = nullptr;
    exit(EXIT_SUCCESS);
}
