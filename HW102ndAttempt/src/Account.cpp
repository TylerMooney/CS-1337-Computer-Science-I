#include "Account.h"

#include <iomanip>
#include <iostream>

using namespace std;

int Account :: numberAccounts = 0;

Account :: Account(string ownerName_, double balance_, Date date_)
{
    //I just put this here because zylabs was giving me an error for not using date_
    date_.getDay();
    accountNumber = numberAccounts + 1000;
    numberAccounts++;
    ownerName = ownerName_;
    balance = balance_;
    //transactionHistory = nullptr;
    //transactionHistory->date = date_;
}

//If there is enough balance in the account, deduct the amount inputted
bool Account :: withdraw(double amount, Date date_)
{
    //I just put this here because zylabs was giving me an error for not using date_
    date_.getDay();
    if(balance >= amount)
    {
        balance -= amount;
        return true;
    }
    return false;
}

//If the deposit amount is positive, add the amount to the balance
bool Account :: deposit(double amount, Date date_)
{
    //I just put this here because zylabs was giving me an error for not using date_
    date_.getDay();
    if(amount > 0)
    {
        balance += amount;
        return true;
    }
    return false;
}

int Account :: getAccountNumber() const
{
    return accountNumber;
}

double Account :: getBalance() const
{
    return balance;
}

int Account :: getNumberAccounts()
{
    return numberAccounts;
}

void Account :: print() const
{
    cout << fixed << setprecision(2) << "#: " << accountNumber << ", Name: " << ownerName << ", Balance: " << balance << " Galactic units\n";
}
