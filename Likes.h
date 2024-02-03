#pragma once
#include <iostream>
#include "User.h"

using namespace std;

class Like
{
    int count;
public:


    void LikeIncreaser()
    {
        this->count++;
    }
};