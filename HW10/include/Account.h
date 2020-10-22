#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Date.h"
#include <string>

using namespace std;

struct Transaction
{
    Date date;
    int transactionType; // 0, 1, 2 for account creation, deposit and withdrawal respectively
    double amount;
};

class Account
{
    private:
        int accountNumber;
        string ownerName;

    protected:
        double balance;
        static int numberAccounts;
        Transaction * transactionHistory;
        int numberTransactions;

    public:
        Account(string, double, Date);
        virtual bool withdraw(double, Date);
        bool deposit(double, Date);
        int getAccountNumber() const;
        double getBalance() const;
        int getNumberAccounts();
        virtual void print() const;
};

#endif // ACCOUNT_H
