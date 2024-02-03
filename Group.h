#pragma once
#include <iostream>
#include "Message.h"

class GroupMembers
{
public:
    string name;

    void serialize(ofstream &ofs) const
    {
        ofs.write(reinterpret_cast<const char *>(this), sizeof(GroupMembers));
    }

    void deserialize(ifstream &ifs)
    {
        ifs.read(reinterpret_cast<char *>(this), sizeof(GroupMembers));
    }
};

class Group
{
public:
    string GroupName;
    GroupMembers *MyGroupMembers;
    int MemberCount;
    int MaxMemberCount;

    Group()
    {
        GroupName = "";
        MyGroupMembers = NULL;
        MemberCount = 0;
        MaxMemberCount = 0;
    }

    // Serialization for User
    void serialize(ofstream &ofs) const
    {
        ofs.write(reinterpret_cast<const char *>(this), sizeof(Group));
        for (int i = 0; i < MemberCount; i++)
        {
            MyGroupMembers[i].serialize(ofs);
        }
    }

    void deserialize(ifstream &ifs)
    {
        ifs.read(reinterpret_cast<char *>(this), sizeof(Group));
        MyGroupMembers = new GroupMembers[this->MaxMemberCount];
        for (int i = 0; i < this->MemberCount; i++)
        {
            MyGroupMembers[i].deserialize(ifs);
        }
    }

    // Adds a member 
    bool AddMember(string Name)
    {
        if (this->MemberCount == 0)
        {
            this->MaxMemberCount = 10;
            MyGroupMembers = new GroupMembers[this->MaxMemberCount];
        }
        if (this->MemberCount == this->MaxMemberCount)
        {
            this->MaxMemberCount *= 2;
            GroupMembers *tempG = new GroupMembers[this->MaxMemberCount];

            for (int i = 0; i < this->MemberCount; i++)
            {
                tempG[i] = MyGroupMembers[i];
            }
            delete[] MyGroupMembers;
            MyGroupMembers = tempG;
        }
        for (int i = 0; i < this->MemberCount; i++)
        {
            if (MyGroupMembers[i].name == Name)
            {
                cout << "You have already joined this group\n";
                return false;
            }
        }

        MyGroupMembers[this->MemberCount].name = Name;
        this->MemberCount++;
        return true;
    }
};