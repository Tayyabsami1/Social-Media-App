#pragma once
#include <iostream>
#include <ctime>
#include "User.h"

using namespace std;

class Messager
{
public:
    string Name;
};

class Message
{
    int messageID;
    Messager sender;
    string content;
    time_t timestamp;

public:
    Message()
    {
        this->messageID = 0;
        this->content = "";
    }

    Message(int messageID, const string &content)
    {
        this->messageID = messageID;
        this->content = content;
        this->timestamp = time(0);
    }

    // Serialization for User
    void serialize(ofstream &ofs) const
    {
        ofs.write(reinterpret_cast<const char *>(this), sizeof(Message));
    }

    void deserialize(ifstream &ifs)
    {
        ifs.read(reinterpret_cast<char *>(this), sizeof(Message));
    }

    // Getters
    int getMessageID() const
    {
        return messageID;
    }

    Messager getSender() const
    {
        return sender;
    }

    string getContent() const
    {
        return content;
    }

    time_t getTimestamp() const
    {
        return timestamp;
    }

    string getTimestampString() const
    {
        char buffer[26]; // Sufficient size to hold the formatted time
        ctime_s(buffer, sizeof(buffer), &timestamp);

        buffer[26 - 1] = '\0';

        return string(buffer);
    }

    void setMessageID(int id)
    {
        messageID = id;
    }

    void setSender(string name)
    {
        this->sender.Name = name;
    }

    void setContent(const string &c)
    {
        content = c;
    }

    void setTimestamp(time_t ts)
    {
        timestamp = ts;
    }

    void DisplayMessages()
    {
        cout << sender.Name << " : " << this->content << endl;
    }
};

class GroupMessage : public Message
{
    Messager *GroupMessagers;

public:
    GroupMessage()
    {
        this->GroupMessagers = NULL;
    }
};