#include "Date.h"
#include <iostream>

using namespace std;

void Date::set(int month_, int day_, int year_, int hour_)
{
    month = month_;
    day = day_;
    year = year_;
    hour = hour_;
}

//Prints out the date
void Date::print() const
{
    cout << month << ' ' << day << ", " << year << ", " << hour << ":00\n";
}

int Date::getMonth() const
{
    return month;
}

int Date::getDay() const
{
    return day;
}

int Date::getYear() const
{
    return year;
}

int Date::getHour() const
{
    return hour;
}
