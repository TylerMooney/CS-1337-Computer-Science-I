#ifndef PREMIUMACCOUNT_H
#define PREMIUMACCOUNT_H

#include "Account.h"

class PremiumAccount : public Account
{
    private:
        static const double MIN_BALANCE;

    public:
        PremiumAccount(string, double, Date);
        bool withdraw(double, Date);
        double getMinBalance();
        virtual void print() const override;
};

#endif // PREMIUMACCOUNT_H
