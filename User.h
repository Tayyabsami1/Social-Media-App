#pragma once
#include <iostream>
#include <fstream>
#include "Profile.h"
#include "Validator.h"
#include "Message.h"
#include "Group.h"
using namespace std;

class User
{
    int userID;
    string name;
    string email;
    string password;
    string birthdate;

    Message *YourMessages;
    int MessageCount;
    int MaxMessageCount;

    Profile MyProfile;
    string PicPath;

public:
    User *ConfirmedFriends;
    int FriendCount;
    int FriendMaxCount;

    User *FriendRequests;
    int RequestCount;
    int MaxCount;
    // Constructors
    User()
    {
        this->userID = 0;
        this->name = "";
        this->email = "";
        this->password = "";
        this->birthdate = "";
        this->PicPath = "";
        ConfirmedFriends = NULL;
        FriendRequests = NULL;
        this->RequestCount = 0;
        this->FriendCount = 0;
        this->MaxCount = 0;
        this->FriendMaxCount = 0;
        this->YourMessages = NULL;
        this->MessageCount = 0;
        this->MaxMessageCount = 0;
    }

    // Parameterized Constructor
    User(int id, string name, string email, string pass, string bd)
    {
        this->userID = id;
        this->name = name;
        this->email = email;
        this->password = pass;
        this->birthdate = bd;
        MyProfile.setFirstName(name);
        MyProfile.setEmail(email);
        MyProfile.setDob(birthdate);
        ConfirmedFriends = NULL;
        FriendRequests = NULL;
        this->RequestCount = 0;
        this->FriendCount = 0;
        this->FriendMaxCount = 0;
        this->MessageCount = 0;
        this->MaxCount = 0;
        this->MaxMessageCount = 0;
        this->MessageCount = 0;
        this->YourMessages = NULL;
    }

    // Serialization for User
    void serialize(ofstream &ofs) const
    {
        ofs.write(reinterpret_cast<const char *>(this), sizeof(User));

        if(this->YourMessages!=NULL)
        for (int i = 0; i < MessageCount; i++)
        {
            YourMessages[i].serialize(ofs);
        }

        if (this->ConfirmedFriends != NULL)
        for (int i = 0; i < FriendCount; i++)
        {
            ConfirmedFriends[i].serialize(ofs);
        }

        if (this->FriendRequests != NULL)
        for (int i = 0; i < RequestCount; i++)
        {
            FriendRequests[i].serialize(ofs);
        }
    }

    void deserialize(ifstream &ifs)
    {
        ifs.read(reinterpret_cast<char *>(this), sizeof(User));
        if(this->MaxMessageCount!=0)
        YourMessages = new Message[this->MaxMessageCount];

        for (int i = 0; i < MessageCount; i++)
        {
            YourMessages[i].deserialize(ifs);
        }
        if(this->FriendMaxCount!=0)
        ConfirmedFriends=new User[this->FriendMaxCount];

        for (int i = 0; i < this->FriendCount; i++)
        {
            ConfirmedFriends[i].deserialize(ifs);
        }

        if(this->MaxCount!=0)
        FriendRequests=new User[this->MaxCount];

        for (int i = 0; i < this->FriendCount; i++)
        {
            FriendRequests[i].deserialize(ifs);
        }
        MyProfile.MaxPost=0;
        MyProfile.numPosts=0;
        MyProfile.MyPosts=NULL;
    }

    // Create A New Post
    void PostMaker()
    {
        MyProfile.PostUploader();
    }

    // Prints the Time Line for you
    void TimeLinerPrinterOwn()
    {
        MyProfile.MyTimeLineDisplayer();
        system("pause");
    }

    bool MessageViewer()
    {
        if (this->MessageCount == 0)
        {
            cout << "You have no messages\n";
            return false;
        }

        for (int i = 0; i < this->MessageCount; i++)
        {
            YourMessages[i].DisplayMessages();
        }
        return true;
    }

    void MessageMaker(string s)
    {
        string n;
        cout << "Enter the message content you want to send \n";
        cin.ignore();
        getline(cin, n);

        if (this->MaxMessageCount == 0)
        {
            this->MaxMessageCount = 10;
            YourMessages = new Message[MaxMessageCount];
        }

        if (this->MaxCount == this->MaxMessageCount)
        {
            this->MaxMessageCount *= 2;
            Message *temp = new Message[MaxMessageCount];

            for (int i = 0; i < this->MessageCount; i++)
            {
                temp[i] = YourMessages[i];
            }

            delete[] YourMessages;
            YourMessages = temp;
        }

        YourMessages[this->MessageCount].setContent(n);
        YourMessages[this->MessageCount].setSender(s);
        this->MessageCount++;
    }

    // Prints the Time Line for the visitor
    void TimeLinePrinterVisitor(User MLiker)
    {
        bool check = MyProfile.MyTimeLineDisplayer();

        if (check)
        {
            int postnum = MyProfile.MyPostSelector();
            cout << "What do you want to do with this Post \n";
            cout << "1.Like    2.Comment     3.Ignore\n";
            int opt2;
            cin >> opt2;

            while (!MyValidator(opt2, 3))
            {
                cout << "Incoorect selection\n";
                cout << "Enter again\n";
                cin >> opt2;
            }

            if (opt2 == 1)
            {
                MyProfile.MyPostInteractionLike(postnum);
            }

            if (opt2 == 2)
            {
                MyProfile.MyPostInteractionComment(postnum);
                cout << "Comment posted successful\n";
            }
            if (opt2 == 3)
            {
                cout << "Going Back..\n";
                return;
            }
        }
    }

    // Add a Friend Request from a user in the box
    void AddFriendRequest(User &u)
    {
        // Check 1
        for (int i = 0; i < FriendCount; i++)
        {
            if (this->ConfirmedFriends[i].getName() == u.getName())
            {
                cout << "This User is Already your friend\n";
                return;
            }
        }

        // Check 2
        for (int i = 0; i < RequestCount; i++)
        {
            if (this->FriendRequests[i].getName() == u.getName())
            {
                cout << "Please Wait till this user accepts your request\n";
                return;
            }
        }

        // Check 4
        for (int i = 0; i < u.RequestCount; i++)
        {
            if (u.FriendRequests[i].getName() == this->getName())
            {
                cout << "This User has sent you a friend request already \n";
                cout << "Check your Request Inbox\n";
                Sleep(200);
                return;
            }
        }

        if (MaxCount == 0)
        {
            MaxCount = 10;
            FriendRequests = new User[MaxCount];
        }

        if (MaxCount == RequestCount)
        {
            MaxCount = MaxCount * 2;
            User *Temp = new User[MaxCount];

            for (int i = 0; i < RequestCount; i++)
            {
                Temp[i] = FriendRequests[i];
            }
            delete[] FriendRequests;
            FriendRequests = Temp;
        }

        FriendRequests[RequestCount] = u;
        RequestCount++;
        cout << "Friend Request send successful\n";
        return;
    }

    // Accept a Friend Request
    void AddFriend(User &u)
    {
        if (this->FriendCount == 0)
        {
            FriendMaxCount = 10;
            ConfirmedFriends = new User[FriendMaxCount];
        }

        if (FriendMaxCount == FriendCount)
        {
            FriendMaxCount = FriendMaxCount * 2;
            User *Temp = new User[FriendMaxCount];

            for (int i = 0; i < FriendCount; i++)
            {
                Temp[i] = ConfirmedFriends[i];
            }
            delete[] ConfirmedFriends;
            ConfirmedFriends = Temp;
        }
        ConfirmedFriends[FriendCount] = u;
        FriendCount++;
    }

    // Accepts or Decline Friend Request
    void ShowFriendRequest(User *UserArr, int n)
    {
        if (RequestCount == 0)
        {
            cout << "Your Request Box is empty\n";
            return;
        }
        int opt;
        cout << "You have the following Friend Requests \n";
        int i;
        for (i = 0; i < RequestCount; i++)
        {
            cout << i + 1 << ". " << FriendRequests[i].getName() << "\n";
        }
        cout << "Enter the Number of Request you want to Add or Decline\n";
        cin >> opt;
        while (!MyValidator(opt, i))
        {
            cout << "Incorrect Option\n";
            cout << "Enter the Number of Request you want to Add or Decline\n";
            cin >> opt;
        }
        cout << "What you you want to Do \n";
        cout << "1. Accept \n";
        cout << "2. Reject\n";
        cout << "3. Ignore\n";
        int opt2;
        cin >> opt2;
        while (!MyValidator(opt2, 3))
        {
            cout << "Incorrect option\n";
            cout << "What you you want to Do \n";
            cout << "1. Accept \n";
            cout << "2. Reject\n";
            cin >> opt2;
        }
        if (opt2 == 3)
        {
            cout << "Going Back\n";
            return;
        }

        if (opt2 == 2)
        {
            RequestCount--;
            cout << "Friend Request Declined \n";
        }

        if (opt2 == 1)
        {
            this->AddFriend(FriendRequests[opt - 1]);
            this->RequestCount--;
            for (int i = 0; i < n; i++)
            {
                if (FriendRequests[opt - 1].getName() == UserArr[i].getName())
                {
                    opt = i;
                    break;
                }
            }
            UserArr[opt].AddFriend(*this);
            cout << "Friend Added successful\n";
        }
    }

    void ProfileCustomizer()
    {
        int opt;
        cout << "What do you want to Customize\n";
        cout << "1. Picture\n";
        cout << "2. Personal Information\n";
        cin >> opt;
        MyValidator(opt, 2);

        if (opt == 1)
        {
            cout << "Enter the path to the picture (dont enter space in path)\n";
            cin >> this->PicPath;
            cout << "Picture path added successful\n";
            return;
        }

        if (opt == 2)
        {
            MyProfile.ProfileCustomizer();
        }
    }

    // Getters
    int getUserID() const
    {
        return userID;
    }

    string getName() const
    {
        return name;
    }

    string getEmail() const
    {
        return email;
    }

    string getPassword() const
    {
        return password;
    }

    string getBirthdate() const
    {
        return birthdate;
    }

    Profile GetProfile()
    {
        return this->MyProfile;
    }
    // // Setters
    void setUserID(int id)
    {
        userID = id;
    }

    void setName(const string &n)
    {
        name = n;
    }

    void setEmail(const string &email)
    {
        this->email = email;
    }

    void setPassword(const string &pass)
    {
        password = pass;
    }

    void setBirthdate(const string &bd)
    {
        birthdate = bd;
    }
};