// #pragma once
#include <iostream>
#include <string>
#include "Validator.h"
#include "Post.h"
#include "User.h"

using namespace std;

class Profile
{
    string firstName;
    string dob;
    string email;
    string lastName;
    string phoneNumber;
    string location;
    bool isStudent;
    string organization;

public:
    int MaxPost;
    int numPosts;
    Post *MyPosts;

    Profile()
    {
        // this->MyUser3 = NULL;
        this->firstName = "";
        this->lastName = "";
        this->dob = "";
        this->email = "";
        this->location = "";
        this->isStudent = false;
        this->organization = "";
        MyPosts = NULL;
        this->numPosts = 0;
        this->phoneNumber = "";
        this->MaxPost = 0;
    }

    void PostUploader()
    {
        string c;
        cout << "Enter the Content You want to Post\n";
        cin.ignore();
        getline(cin, c);

        if (MyPosts == NULL)
        {
            MaxPost = 10;
            MyPosts = new Post[MaxPost];
        }

        if (numPosts == MaxPost)
        {
            MaxPost *= 2;
            Post *Temp = new Post[MaxPost];

            for (int i = 0; i < numPosts; i++)
            {
                Temp[i] = MyPosts[i];
            }
            delete[] MyPosts;
            MyPosts = Temp;
        }
        MyPosts[numPosts].setContent(c);
        MyPosts[numPosts].setPostID(numPosts + 1);
        cout << "Post uploaded successfully\n";
        numPosts++;
    }

    int MyPostSelector()
    {
        if (this->numPosts == 0)
        {
            cout << "The Time Line is empty\n";
            return 0;
        }
        int Opt;
        cout << "Enter the Post ID you want to Select\n";
        cin >> Opt;

        while (!MyValidator(Opt, numPosts))
        {
            cout << "Incoorect selection\n";
            cout << "Enter again\n";
            cin >> Opt;
        }

        return Opt;
    }

    void MyPostInteractionLike(int position)
    {
        cout << "Post Liked Successfully\n";
        MyPosts[position - 1].LikeIncreaser();
        return;
    }

    void MyPostInteractionComment(int position)
    {
        cout << "Enter the content of the comment you want to post\n";
        string c;
        cin.ignore();
        getline(cin, c);
        MyPosts[position - 1].CommmentIncrease(c);

        return;
    }

    // Display All the Posts of the User
    bool MyTimeLineDisplayer()
    {
        if (numPosts == 0)
        {
            cout << "The Time Line is empty\n";
            return false;
        }

        int count = 1;
        for (int i = numPosts - 1; i >= 0; i--)
        {
            cout << count << ".\n";
            MyPosts[i].PostDisplayer();
            cout << endl;
            count++;
        }
        return true;
    }

    // Customize Profile Data
    void ProfileCustomizer()
    {
        cout << "Enter your last name: ";
        cin.ignore();
        getline(cin, lastName);

        cout << "Enter your phone number: ";
        cin.ignore();
        getline(cin, phoneNumber);

        cout << "Enter your location: ";
        cin.ignore();
        getline(cin, location);

        cout << "Are you a student? (1 for Yes, 0 for No): ";
        cin >> isStudent;

        cout << "Enter your Organization name \n";
        cin.ignore();
        getline(cin, organization);

        cout << "Profile Information Updated successful\n";
    }
    // // Getters
    string getFirstName() const
    {
        return firstName;
    }

    string getLastName() const
    {
        return lastName;
    }

    string getDob() const
    {
        return dob;
    }

    string getPhoneNumber() const
    {
        return phoneNumber;
    }

    string getEmail() const
    {
        return email;
    }

    string getLocation()
    {
        return location;
    }

    bool GetisStudent()
    {
        return isStudent;
    }

    string getOrganization() const
    {
        return organization;
    }

    int getNumPosts() const
    {
        return numPosts;
    }

    // Setters
    void setFirstName(const string &fName)
    {
        firstName = fName;
    }

    void setLastName(const string &lName)
    {
        lastName = lName;
    }

    void setDob(const string &dateOfBirth)
    {
        dob = dateOfBirth;
    }

    void setPhoneNumber(const string &phone)
    {
        phoneNumber = phone;
    }

    void setEmail(const string &userEmail)
    {
        email = userEmail;
    }

    void setLocation(const string &userLocation)
    {
        location = userLocation;
    }

    void setStudent(bool studentStatus)
    {
        isStudent = studentStatus;
    }

    void setOrganization(const string &org)
    {
        organization = org;
    }

    // Virtual function for polymorphism
    virtual void readProfile() const
    {
        cout << "Reading profile organization: " << this->organization << endl;
    }
};

class PersonalProfile : public Profile
{
public:
    string hobbies;

    PersonalProfile(const string &n) : Profile()
    {
        this->hobbies = n;
    }

    void displayPersonalProfile()
    {
        cout << "Hobbies: " << hobbies << endl;
    }

    void readProfile() const
    {
        cout << "Reading profile hobbies: " << this->hobbies << endl;
    }
};

class BusinessProfile : public Profile
{
public:
    string companyName;
    int NumberOfPeople;

    BusinessProfile(const string &n, int a) : Profile()
    {
        this->companyName = n;
        this->NumberOfPeople = a;
    }

    // Function to display business profile information
    void displayBusinessProfile() const
    {
        cout << "Company: " << companyName << endl;
    }

    void readProfile() const
    {
        cout << "Reading Profile Company Name " << this->companyName<< endl;
    }
};