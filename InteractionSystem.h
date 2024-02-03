#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include "User.h"
#include "Group.h"
#include "Validator.h"
#include "Page.h"
#include "Date.h"

using namespace std;

// The Main Driver Class
class InteractionSystem
{
    int UserCount;
    int MaxUser;
    User *MyUsers;

    Group *MyGroups;
    int GroupCount;
    int MaxGroupCount;

    Page *MyPages;
    int PageCount;
    int PageMaxCount;

public:
    // Constructor
    InteractionSystem()
    {
        MyUsers = NULL;
        this->UserCount = 0;
        this->MaxUser = 0;
        this->MyGroups = NULL;
        this->GroupCount = 0;
        this->MaxGroupCount = 0;
        this->MyPages = NULL;
        this->PageCount = 0;
        this->PageMaxCount = 0;
    }

    // A Function to Write in the File
    void serialize(ofstream &ofs) const
    {
        // * Done
        ofs.write(reinterpret_cast<const char *>(this), sizeof(InteractionSystem));
        if (this->MyUsers != NULL)
            for (int i = 0; i < UserCount; ++i)
            {
                MyUsers[i].serialize(ofs);
            }

        // * Done
        if (this->MyGroups != NULL)
            for (int i = 0; i < GroupCount; ++i)
            {
                MyGroups[i].serialize(ofs);
            }

        if (this->MyPages != NULL)
            for (int i = 0; i < PageCount; i++)
            {
                MyPages[i].serialize(ofs);
            }
    }

    // A Function to read from the class
    void deserialize(ifstream &ifs)
    {
        ifs.read(reinterpret_cast<char *>(this), sizeof(InteractionSystem));
        MyUsers = new User[MaxUser];

        // * Done ->Messages->Users->Other Users
        for (int i = 0; i < UserCount; ++i)
        {
            MyUsers[i].deserialize(ifs);
        }

        // * Done
        MyGroups = new Group[this->MaxGroupCount];

        for (int i = 0; i < GroupCount; ++i)
        {
            MyGroups[i].deserialize(ifs);
        }

        //* Done
        MyPages = new Page[this->PageMaxCount];

        for (int i = 0; i < this->PageCount; i++)
        {
            MyPages[i].deserialize(ifs);
        }
    }

    // A Main Function to initiate runing
    InteractionSystem readObjectFromFile(const char *filename, InteractionSystem &obj)
    {
        ifstream file(filename, ios::binary);
        if (file.peek() == ifstream::traits_type::eof())
        {
            return obj;
        }

        if (file.is_open())
        {
            obj.deserialize(file);

            if (this->MaxUser == this->UserCount && this->MaxUser != 0)
            {
                User *NewArr = new User[MaxUser * 2];
                this->MaxUser *= 2;

                for (int i = 0; i < UserCount; i++)
                {
                    NewArr[i] = MyUsers[i];
                }

                delete[] MyUsers;
                MyUsers = NewArr;
            }
            file.close();
        }
        else
        {
            cout << "Error opening file for reading." << endl;
        }
        return obj;
    }

    // A Main function to initiatre reading
    void writeObjectToFile(const char *filename, const InteractionSystem &obj)
    {
        ofstream file(filename, ios::binary);
        if (file.is_open())
        {
            obj.serialize(file);
            file.close();
        }
        else
        {
            cerr << "Error opening file for writing." << endl;
        }
    }

    // A logic to verify Email
    bool EmailVerifier(string email)
    {
        size_t atPosition = email.find('@');
        size_t dotPosition = email.rfind('.');

        // Ensure '@' comes before '.'
        if (atPosition != string::npos &&
            dotPosition != string::npos &&
            atPosition < dotPosition)
        {
            // Ensure there is at least one character before '@' and '.' in the email
            if (atPosition > 0 && dotPosition < email.length() - 1)
            {
                return true;
            }
        }

        return false;
    }

    // Verify that a password meet all the needs
    bool PasswordVerifier(string s)
    {
        bool ans = false, condition1 = false, condition2 = false, condition3 = false, condition4 = false;

        for (int i = 0; i < s.length(); i++)
        {
            if (((s[i] >= 33 && s[i] <= 47) || (s[i] >= 58 && s[i] <= 64) || (s[i] >= 91 && s[i] <= 96)) && s.length() >= 8)
            {
                condition1 = true;
            }
        }
        for (int i = 0; i < s.length(); i++) // Checking for lowercase letter
        {
            if (s[i] >= 97 && s[i] <= 122)
            {
                condition2 = true;
            }
        }

        for (int i = 0; i < s.length(); i++) // checking for upper case
        {
            if (s[i] >= 65 && s[i] <= 90)
            {
                condition3 = true;
            }
        }

        for (int i = 0; i < s.length(); i++) // checking for numeric
        {
            if (s[i] >= 48 && s[i] <= 57)
            {
                condition4 = true;
            }
        }
        if (condition1 && condition2 && condition3 && condition4)
        {
            ans = true;
        }

        if (!ans)
            cout << "Password don't match the Criteria \n";
        return ans;
    }

    // A Logic to Input password while hiding it and returning the password
    string PasswordInputter()
    {
        int ch;
        string temppass;
        cout << "Enter your Password\n";
        ch = _getch();
        while (ch != 13)
        {
            if (ch == '\b')
            {
                if (!temppass.empty())
                {
                    temppass.pop_back();
                    cout << "\b \b";
                }
            }
            else
            {
                temppass.push_back(ch);
                cout << "*";
            }
            ch = _getch();
        }
        cout << "\n";

        return temppass;
    }

    // To Display Animation
    void printLoadingBar(int width, int percent)
    {
        int progress = width * percent / 100;
        cout << "[";

        for (int i = 0; i < width; ++i)
        {
            if (i < progress)
                cout << "=";
            else
                cout << " ";
        }

        cout << "] "
             << "  " << percent << "%\r";
    }

    /*
    -> Function helps add friends
    -> Send Message to friends
    -> View Friends Time Line
    */
    void SearchUser(int pos, string tofind)
    {
        int Opt;

        for (int i = 0; i < UserCount; i++)
        {
            if (i != pos)
            {
                if (MyUsers[i].getName() == tofind)
                {
                    cout << "User Found \n";
                    for (int j = 0; j < MyUsers[pos].FriendCount; j++)
                    {
                        if (MyUsers[pos].ConfirmedFriends[j].getName() == MyUsers[i].getName())
                        {
                            cout << "This User is in your friend list \n";
                            cout << "1. View TimeLine \n";
                            cout << "2. View Messages \n";
                            cout << "3. Send Message \n";
                            cout << "4. Go Back\n";
                            cin >> Opt;
                            while (!MyValidator(Opt, 4))
                            {
                                cout << "Incorrect Option\n";
                                cout << "Enter Again\n";
                                cin >> Opt;
                            }
                            if (Opt == 1)
                            {
                                MyUsers[i].TimeLinePrinterVisitor(MyUsers[pos]);
                                return;
                            }

                            if (Opt == 2)
                            {
                                bool c2 = MyUsers[pos].MessageViewer();
                                if (c2)
                                {

                                    cout << "Do you want to reply \n";
                                    cout << "1 for Yes   2 for No\n";
                                    int opt3;
                                    cin >> opt3;
                                    while (!MyValidator(opt3, 2))
                                    {
                                        cout << "Incorrect option\n";
                                        cout << "Enter again\n";
                                        cin >> opt3;
                                    }

                                    if (opt3 == 1)
                                    {
                                        MyUsers[i].MessageMaker(MyUsers[pos].getName());
                                        cout << "Reply sent successful\n";
                                    }

                                    if (opt3 == 2)
                                    {
                                        cout << "Going Back..\n";
                                        return;
                                    }
                                }

                                return;
                            }

                            if (Opt == 3)
                            {
                                MyUsers[i].MessageMaker(MyUsers[pos].getName());
                                cout << "Message sent successful\n";
                                return;
                            }
                            if (Opt == 4)
                            {
                                cout << "Returning\n";
                                return;
                            }
                        }
                    }

                    cout << "Do you want to add this user as a friend\n";
                    cout << "1 for Yes\n2 for No\n";
                    cin >> Opt;
                    while (!MyValidator(Opt, 2))
                    {
                        cout << "Incorrect Option\n";
                        cout << "Enter Again\n";
                        cin >> Opt;
                    }

                    if (Opt == 1)
                    {
                        MyUsers[i].AddFriendRequest(MyUsers[pos]);
                        return;
                    }
                    if (Opt == 2)
                    {
                        cout << "Going Back\n";
                        return;
                    }
                }
            }
        }
        cout << "This User is not present in the system sorry\n";
    }

    // Login a User
    bool LoginVerifier(string name, string pass, int &id)
    {
        for (int i = 0; i < UserCount; i++)
        {
            if (name == MyUsers[i].getName())
            {
                if (pass == MyUsers[i].getPassword())
                {
                    id = i;
                    cout << "Login Successful\n";
                    return true;
                }
            }
        }
        return false;
    }

    // View all the groups in the system
    void GroupViewer(int p)
    {
        if (this->GroupCount == 0)
        {
            cout << "No Groups are made so far..\n";
            return;
        }
        cout << "Following are the groups in the System\n";

        for (int i = 0; i < this->GroupCount; i++)
        {
            cout << i + 1 << ".\n";
            cout << "Group Name : " << MyGroups[i].GroupName << endl;
            cout << "Members : " << MyGroups[i].MemberCount << endl;
        }
        cout << "Do you want to join any group\n";
        int Ans;
        cout << "1. Yes     2. No\n";
        cin >> Ans;

        while (!MyValidator(Ans, 2))
        {
            cout << "Incorrect try again\n";
            cin >> Ans;
        }

        if (Ans == 1)
        {
            cout << "Enter the Number of Group you want to add\n";
            int Ans2;
            cin >> Ans2;
            while (!MyValidator(Ans2, this->GroupCount))
            {
                cout << "Incorrect try again\n";
                cin >> Ans2;
            }

            bool c4 = MyGroups[Ans2 - 1].AddMember(MyUsers[p].getName());
            if (c4)
                cout << "Group joined successfully\n";
        }
        if (Ans == 2)
        {
            cout << "Going Back\n";
            return;
        }
    }

    // Add a group in the system
    void GroupMaker(int p)
    {
        if (this->MaxGroupCount == 0)
        {
            this->MaxGroupCount = 10;
            MyGroups = new Group[this->MaxGroupCount];
        }
        if (this->GroupCount == this->MaxGroupCount)
        {
            this->MaxGroupCount *= 2;
            Group *tempG = new Group[this->MaxGroupCount];
            ;

            for (int i = 0; i < this->GroupCount; i++)
            {
                tempG[i] = MyGroups[i];
            }
            delete[] MyGroups;
            MyGroups = tempG;
        }
        cout << "Enter the name of the Group\n";
        string temps;
        cin.ignore();
        getline(cin, temps);

        MyGroups[this->GroupCount].GroupName = temps;
        MyGroups[this->GroupCount].AddMember(MyUsers[p].getName());
        this->GroupCount++;
    }

    // Add a new page in the system
    void PageMaker(int pos)
    {
        if (this->PageMaxCount == 0)
        {
            this->PageMaxCount = 10;
            MyPages = new Page[PageMaxCount];
        }

        if (this->PageMaxCount == this->PageCount)
        {
            this->PageMaxCount *= 2;
            Page *tempP = new Page[this->PageMaxCount];
            for (int i = 0; i < this->PageCount; i++)
            {
                tempP[i] = MyPages[i];
            }
            delete[] MyPages;
            MyPages = tempP;
        }
        cout << "Enter the Page Name\n";
        string s;
        cin.ignore();
        getline(cin, s);
        MyPages[PageCount].PageName = s;
        MyPages[PageCount].AddFollower(this->MyUsers[pos].getName());
        this->PageCount++;
    }

    // View ALl pages in the system
    void PageViewer(int pos)
    {
        if (this->PageCount == 0)
        {
            cout << "No Page exists at the moment\n";
            return;
        }
        cout << "The System has the following pages\n";

        for (int i = 0; i < this->PageCount; i++)
        {
            cout << i + 1 << ". ";
            MyPages[i].PageDisplayer();
        }

        cout << "Do you want to follow any page\n";
        cout << "1. Yes    2. No\n";
        int opt3;
        cin >> opt3;

        while (!MyValidator(opt3, 2))
        {
            cout << "Incorrect Option Enter again\n";
            cin >> opt3;
        }

        if (opt3 == 1)
        {
            cout << "Enter the Page Number you want to follow\n";
            int opt4;
            cin >> opt4;

            while (!MyValidator(opt4, this->PageCount))
            {
                cout << "Incorrect Option Enter again\n";
                cin >> opt4;
            }

            bool check = MyPages[opt4 - 1].AddFollower(MyUsers[pos].getName());
            if (check)
                cout << "You have successfully followed this page\n";
        }

        if (opt3 == 2)
        {
            cout << "Going Back\n";
            return;
        }
    }

    // The Main Profile of the User
    void InterfaceMenue(int pos)
    {
        bool check = true;
        int Option;
        while (check)
        {
            cout << "\nWelcome to your Profile " << MyUsers[pos].getName() << endl;
            cout << "\nWhat do you want to do\n";
            cout << "1. Customize your Profile\n";
            cout << "2. Search for Users\n";
            cout << "3. View Your Friend Request Box\n";
            cout << "4. Create Post\n";
            cout << "5. View My TimeLine\n";
            cout << "6. Make a new Group\n";
            cout << "7. View all groups and join one \n";
            cout << "8. Make a Page\n";
            cout << "9. View all Pages and follow one\n";
            cout << "10. Exit \n";
            cin >> Option;
            while (!MyValidator(Option, 10))
            {
                cout << "Incorrect Option\n";
                cout << "Enter Again\n";
                cin >> Option;
            }

            if (Option == 1)
            {
                MyUsers[pos].ProfileCustomizer();
            }

            if (Option == 2)
            {
                string s;
                cout << "Enter the User Name of the Person you want to search\n";
                cin.ignore();
                getline(cin, s);
                this->SearchUser(pos, s);
            }

            if (Option == 3)
            {
                MyUsers[pos].ShowFriendRequest(MyUsers, UserCount);
            }
            if (Option == 4)
            {
                MyUsers[pos].PostMaker();
            }
            if (Option == 5)
            {
                MyUsers[pos].TimeLinerPrinterOwn();
            }

            if (Option == 6)
            {
                this->GroupMaker(pos);
                cout << "Group created successfully\n";
            }

            if (Option == 7)
            {
                this->GroupViewer(pos);
            }

            if (Option == 8)
            {
                PageMaker(pos);
                cout << "Page created successfully\n";
            }

            if (Option == 9)
            {
                PageViewer(pos);
            }

            if (Option == 10)
            {
                cout << "Redirecting to main menue \n";
                check = false;
            }

            Sleep(600);
            system("cls");
        }
    }

    // Takes the Information to Login
    void LoginMaker()
    {
        string Name;
        int Loc;
        cout << "Enter your UserName\n";
        cin.ignore();
        getline(cin, Name);
        string Password;
        Password = this->PasswordInputter();

        if (LoginVerifier(Name, Password, Loc))
        {
            InterfaceMenue(Loc);
        }
        else
        {
            cout << "Incorrect credentials\n";
            return;
        }
    }

    // Takes  the information to Sign up
    void SignUpMaker()
    {
        if (MyUsers == NULL)
        {
            MyUsers = new User[10];
            this->MaxUser = 10;
        }

        // If Users Get full
        if (this->MaxUser == this->UserCount)
        {
            User *NewArr = new User[MaxUser * 2];
            MaxUser *= 2;

            for (int i = 0; i < UserCount; i++)
            {
                NewArr[i] = MyUsers[i];
            }

            delete[] MyUsers;
            MyUsers = NewArr;
        }

        string UserName;
        cout << "Enter a User-Name\n";
        cin.ignore();
        getline(cin, UserName);
        bool c2 = true;
        for (int i = 0; i < UserCount; i++)
        {
            if (UserName == MyUsers[i].getName())
            {
                cout << "Please Enter a unique username \n";
                c2 = false;
                break;
            }
        }
        while (!UserNameVerifier(UserName) || !c2)
        {
            cout<<"The User-name must be atleast 5 characters containing number and alphabet\n";
            cout << "Enter a User-Name\n";
            cin >> UserName;

            for (int i = 0; i < UserCount; i++)
            {
                if (UserName == MyUsers[i].getName())
                {
                    cout << "Please Enter a unique username \n";
                    c2 = false;
                    break;
                }
                c2 = true;
            }
        }
        string Password;
        Password = this->PasswordInputter();

        // ! Uncomment it
        // while (!PasswordVerifier(Password))
        // {
        //     Password = this->PasswordInputter();
        // }
        string Email;
        cout << "Enter your Email\n";
        cin >> Email;

        // while (!EmailVerifier(Email))
        // {
        //     cout << "Wrong Email format\n";
        //     cout << "Enter your Email\n";
        //     cin >> Email;
        // }
        string DOB;
        cout << "Enter you Date of Birth in format : DD-MM-YY\n";
        cin >> DOB;
        MyUsers[UserCount].setName(UserName);
        MyUsers[UserCount].setBirthdate(DOB);
        MyUsers[UserCount].setEmail(Email);
        MyUsers[UserCount].setPassword(Password);
        MyUsers[UserCount].setUserID(UserCount + 1);
    }

    // Login or SignUp
    bool SecondMenue()
    {
        int Option;
        cout << "What do you want to do \n";
        cout << "1. Login    2. SignUp    3.Exit\n";
        cin >> Option;
        if (!MyValidator(Option, 3))
        {
            cout << "Incorrect Option Selected !!\n";
            return true;
        }
        if (Option == 1)
        {
            if (this->MyUsers == 0)
            {
                cout << "No Accounts exist in the system\n";
                return true;
            }
            this->LoginMaker();
        }

        if (Option == 2)
        {
            this->SignUpMaker();
            this->InterfaceMenue(UserCount++);
        }

        if (Option == 3)
        {
            cout << "Program Exit Successful\n";
            this->writeObjectToFile("MyData.txt", *this);
            return false;
        }
        return true;
    }

    void PrintAllUser()
    {
        for (int i = 0; i < UserCount; i++)
        {
            cout << MyUsers[i].getName() << " ";
        }
    }

    void MainMenue()
    {
        cout << "\nWelcome to Interaction App!" << endl;
        *this = readObjectFromFile("MyData.txt", *this);
        int animationFrames = 10;
        int loadingWidth = 20;

        // cout << "\nLoading... \n";
        // for (int frame = 0; frame < animationFrames; ++frame)
        // {
        //     printLoadingBar(loadingWidth, frame * 10);
        //     // ! Uncomment it
        //     Sleep(500);
        // }
        system("cls");

        bool ExitCheck = true;

        while (ExitCheck)
        {
            ExitCheck = SecondMenue();
            Sleep(700);
            system("cls");
        }
    }
};