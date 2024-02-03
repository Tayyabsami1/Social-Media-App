#pragma once
#include <iostream>

using namespace std;

class Friend
{
public:
    string name;
    int age;

    Friend(const string &n, int a)
    {
        this->name = n;
        this->age = a;
    }

    void displayFriend()
    {
        cout << "Friend Name: " << name << ", Age: " << age << endl;
    }

    // Function to perform a generic friend action
    virtual void performFriendAction() const
    {
        cout << "Friend is performing a generic action." << endl;
    }
};

class BestFriend : public Friend
{
public:
    string secretHandshake;

    // Constructor for initializing BestFriend attributes
    BestFriend(const string &n, int a, const string &handshake)
        : Friend(n, a)
    {
    }

    // Function to display BestFriend information
    void displayBestFriend() const
    {
        cout << "Secret Handshake: " << secretHandshake << endl;
    }

    // Overriding the base class function to perform a specific friend action
    void performFriendAction()
    {
        cout << "BestFriend is performing a special action!" << endl;
    }

    void performFriendAction() const
    {
        cout << "BestFriend is performing a special action!" << endl;
    }
};
