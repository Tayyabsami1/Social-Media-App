#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "User.h"
#include "Comment.h"
#include "Likes.h"

using namespace std;

class Post
{
    int postID;
    string content;
    time_t timestamp;

    Like *PostLikes;
    Comment *PostComments;
    int LikeCount;
    int MaxLikeCount;
    int CommentCount;
    int MaxCommentCount;

public:

    Post()
    {
        postID = 0;
        this->content = "";
        timestamp = time(0);

        this->LikeCount = 0;
        this->MaxLikeCount = 0;
        this->CommentCount = 0;
        this->MaxCommentCount=0;
        PostLikes = NULL;
        PostComments=NULL;
    }

    Post(int postID, string content)
    {
        this->postID = postID;
        this->content = content;
        timestamp = time(0);
        this->LikeCount = 0;
        this->MaxLikeCount = 0;
        this->CommentCount = 0;
        this->MaxCommentCount=0;
        PostLikes = NULL;
        PostComments=NULL;
    }

    void LikeIncreaser()
    {
        if (this->LikeCount == 0)
        {
            this->MaxLikeCount = 10;
            PostLikes = new Like[this->MaxLikeCount];
        }

        if (this->LikeCount == this->MaxLikeCount)
        {
            this->MaxLikeCount *= 2;
            Like *temp = new Like[this->MaxLikeCount];

            for (int i = 0; i < this->LikeCount; i++)
            {
                temp[i] = PostLikes[i];
            }
            delete PostLikes;
            PostLikes = temp;
        }
        PostLikes[this->LikeCount].LikeIncreaser();
        LikeCount++;
    }

    void CommmentIncrease(string s)
    {
        if (this->CommentCount == 0)
        {
            this->MaxCommentCount = 10;
            PostComments = new Comment[this->MaxCommentCount];
        }

        if (this->CommentCount == this->MaxCommentCount)
        {
            this->MaxCommentCount *= 2;
            Comment*temp = new Comment[this->MaxCommentCount];

            for (int i = 0; i < this->CommentCount; i++)
            {
                temp[i] = PostComments[i];
            }
            delete PostComments;
            PostComments = temp;
        }
        PostComments[this->CommentCount].CommentIncrease(s);
        CommentCount++;
    }

    // Getters
    int getPostID() const
    {
        return postID;
    }

    string getContent() const
    {
        return content;
    }

    time_t getTimeStamp() const
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

    void PostDisplayer()
    {
        cout << "Post Id : " << this->postID << " Time : " << this->getTimestampString() << endl;
        cout << "Content : " << this->content << endl;
        cout << "Likes : " << LikeCount << " Comments : " << this->CommentCount << endl;
        if(CommentCount!=0)
        {
        cout<<"Comments : \n";
        for (int i = 0; i < CommentCount; i++)
        {
            cout<<PostComments->getContent()<<endl;
        }
        }
        
    }

    // Setters
    void setPostID(int id)
    {
        postID = id;
    }

    void setContent(const string &c)
    {
        content = c;
    }

    void setTimestamp(time_t ts)
    {
        timestamp = ts;
    }
};