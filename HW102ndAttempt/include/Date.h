#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

class Date
{
    private:
        int month, day, year, hour;
    public:
        void set(int, int, int, int);
        void print() const;
        int getMonth() const;
        int getDay() const;
        int getYear() const;
        int getHour() const;
};

#endif // DATE_H
