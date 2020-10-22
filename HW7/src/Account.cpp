#include "Account.h"
#include<iostream>

using namespace std;

int Account::accountCounter = 1000;

Account::Account(int numberOwners, double amount)
{

    accountNumber = accountCounter;
    numOwners = numberOwners;
    ownerPtr = new Person[numberOwners];
    balance = amount;
    accountCounter++;
}

int Account::withdraw(double amount)
{
    //input validation
    if(amount > balance)
        return 1;
    else if(amount <= 0)
        return 2;
    else
        balance -= amount;

    return 0;
}

int Account::deposit(double amount)
{
    //input validation
    if(amount <= 0)
    {
        return 1;
    }

    balance += amount;

    return 0;
}

//extra credit
void Account::addOwner(Person p)
{
    /*
    Person * tempArr = new Person[numOwners++];

    while(int i = 0; i < numOwners - 1; i++)
    {
        tempArr[i] = ownerPtr[i];
    }

    delete [] ownerPtr;
    ownerPtr = new Person[numOwners];
    */
}

//extra credit
int Account::delOwner(Person p)
{
    return 0;
}

void Account::setOwner(int ind, Person p)
{
    ownerPtr[ind] = p;
}

Person Account::getOwner(int ind) const
{
    return ownerPtr[ind];
}

int Account::getAccountNumber() const
{
    return accountNumber;
}

double Account::getBalance()const
{
    return balance;
}

int Account::getNumOwners() const
{
    return numOwners;
}

Account::~Account()
{
    delete [] ownerPtr;
}
