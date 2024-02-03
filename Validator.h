#pragma once
#include <iostream>

using namespace std;

bool MyValidator(int num, int Val)
{
    if (num < 1 || num > Val)
    {
        return false;
    }
    return true;
}

//* Checking if the Username is Valid
bool UserNameVerifier(string s)
{
    if (s.length() < 5)
    {
        return false;
    }

    bool hasLetter = false;
    bool hasNumber = false;
    for (int i = 0; i < s.length(); i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            hasLetter = true;
        }
        // Check if the character is a digit
        else if (s[i]>= '0' && s[i] <= '9')
        {
            hasNumber = true;
        }
    }

     return hasLetter && hasNumber;
}