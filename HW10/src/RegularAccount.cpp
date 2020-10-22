#include "RegularAccount.h"
#include <iostream>

RegularAccount::RegularAccount(string ownerName_, double balance_, Date date_) : Account(ownerName_, balance_, date_)
{

}

void RegularAccount :: print() const
{
    cout << "Regular account, ";
    this->Account::print();
}
