#pragma once
#include <iostream>
#include <ctime>

using namespace std;

class Date
{
private:
    tm date;

public:
    // Constructor


    Date(int year, int month, int day)
    {
        date.tm_year = year - 1900; // Years since 1900
        date.tm_mon = month - 1;    // Months are 0-based
        date.tm_mday = day;
        date.tm_hour = 0;
        date.tm_min = 0;
        date.tm_sec = 0;

        mktime(&date); // Normalize the date
    }

    // Getters
    int getYear() const
    {
        return date.tm_year + 1900;
    }

    int getMonth() const
    {
        return date.tm_mon + 1;
    }

    int getDay() const
    {
        return date.tm_mday;
    }

    // Display the date
    void display() const
    {
        cout << getYear() << '-' << getMonth() << '-' << getDay() << endl;
    }
};