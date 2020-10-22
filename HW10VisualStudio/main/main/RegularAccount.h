#ifndef REGULARACCOUNT_H
#define REGULARACCOUNT_H

#include "Account.h"

class RegularAccount : public Account
{
public:
    RegularAccount(string, double, Date);
    virtual void print() const override;
};

#endif // REGULARACCOUNT_H
