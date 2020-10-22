#include "PremiumAccount.h"
#include <iostream>

const double PremiumAccount::MIN_BALANCE = 1000;

PremiumAccount::PremiumAccount(string name, double amount, Date date_) : Account(name, amount, date_)
{

}

bool PremiumAccount::withdraw(double amount, Date date_)
{
    //I just put this here because zylabs was giving me an error for not using date_
    date_.getDay();
    if (balance >= (amount + 1000))
    {
        balance -= amount;
        return true;
    }
    return false;
}

double PremiumAccount::getMinBalance()
{
    return MIN_BALANCE;
}

void PremiumAccount::print() const
{
    cout << "Premium account, ";
    this->Account::print();
}
