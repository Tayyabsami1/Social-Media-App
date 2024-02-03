#pragma once
#include <iostream>
using namespace std;

class Comment
{
    string content;

public:

    void CommentIncrease(string s)
    {
        this->content=s;
    }

    string getContent() const
    {
        return content;
    }

    void setContent(string c)
    {
        this->content=c;
    }
};