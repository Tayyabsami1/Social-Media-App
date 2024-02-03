#pragma once
#include <iostream>
#include <string>

using namespace std;

class Follower
{
    string name;

public:
    string getName()
    {
        return this->name;
    }

    void setName(string t)
    {
        this->name = t;
    }

    void serialize(ofstream &ofs) const
    {
        ofs.write(reinterpret_cast<const char *>(this), sizeof(Follower));
    }

    void deserialize(ifstream &ifs)
    {
        ifs.read(reinterpret_cast<char *>(this), sizeof(Follower));
    }
};

class Page
{
    Follower *MyFollowers;
    int FollowerCount;
    int MaxFollowerCount;

public:
    string PageName;

    void serialize(ofstream &ofs) const
    {
        ofs.write(reinterpret_cast<const char *>(this), sizeof(Page));

        for (int i = 0; i < FollowerCount; i++)
        {
            MyFollowers[i].serialize(ofs);
        }
    }

    void deserialize(ifstream &ifs)
    {
        ifs.read(reinterpret_cast<char *>(this), sizeof(Page));
        MyFollowers=new Follower [MaxFollowerCount];
        for (int i = 0; i < FollowerCount; i++)
        {
            MyFollowers[i].deserialize(ifs);
        }
    }
   
    Page()
    {
        this->MyFollowers = NULL;
        FollowerCount = 0;
        MaxFollowerCount = 0;
    }

    bool AddFollower(string n)
    {
        if (this->MaxFollowerCount == 0)
        {
            this->MaxFollowerCount = 10;
            MyFollowers = new Follower[MaxFollowerCount];
        }

        if (this->MaxFollowerCount == this->FollowerCount)
        {
            this->MaxFollowerCount *= 2;
            Follower *tempF = new Follower[MaxFollowerCount];

            for (int i = 0; i < this->FollowerCount; i++)
            {
                tempF[i] = MyFollowers[i];
            }
            delete[] MyFollowers;
            MyFollowers = tempF;
        }

        for (int i = 0; i < this->FollowerCount; i++)
        {
            if (MyFollowers[i].getName() == n)
            {
                cout << "You have already followed this page\n";
                return false;
            }
        }

        MyFollowers[FollowerCount].setName(n);
        this->FollowerCount++;
        return true;
    }

    void PageDisplayer()
    {
        cout << "Page Name : " << this->PageName << endl;
        cout << "Followers : " << this->FollowerCount << endl;
    }
};