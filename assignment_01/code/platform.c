#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Platform *platform;

Platform *createPlatform()
{
    platform = (Platform *)malloc(sizeof(Platform));
    platform->posts = NULL;
    platform->lastViewedPost = NULL;
    platform->postCount = 0;
    platform->lastPost = NULL;
    platform->viewedPostFlag = false;
    return platform;
}

bool addPost(char *username, char *caption)
{
    bool added = false;
    if (platform == NULL)
        return added;

    Post *newPost = createPost(username, caption);
    if (newPost == NULL)
        return NULL;

    if (platform->posts == NULL)
    {
        newPost->next = NULL;
        newPost->prev = NULL;
        platform->posts = newPost;
        platform->lastPost = newPost;
        platform->postCount++;

        if (!platform->viewedPostFlag)
            platform->lastViewedPost = newPost;

        added = true;
        return added;
    }

    else
    {
        platform->lastPost->next = newPost;
        newPost->prev = platform->lastPost;
        newPost->next = NULL;
        platform->lastPost = newPost;
        platform->postCount++;

        if (!platform->viewedPostFlag)
            platform->lastViewedPost = newPost;

        added = true;
        return added;
    }
}

bool deletePost(int n)
{
    bool deleted = false;
    if (platform == NULL || platform->postCount == 0)
        return deleted;

    if (n > platform->postCount)
        return deleted;

    if (n == 1)
    {
        Post *temp = platform->lastPost;
        platform->lastPost = platform->lastPost->prev;

        deleteComments(temp->comments);
        free(temp);
        platform->postCount--;

        if (platform->lastViewedPost == temp)
            platform->lastViewedPost = platform->lastPost;

        if (platform->lastPost != NULL)
            platform->lastPost->next = NULL;

        platform->posts = NULL;
        deleted = true;
        return deleted;
    }

    else if (n == platform->postCount)
    {
        Post *temp = platform->posts;
        platform->posts = platform->posts->next;
        deleteComments(temp->comments);
        free(temp);
        platform->postCount--;
        deleted = true;

        if (platform->lastViewedPost == temp)
            platform->lastViewedPost = platform->lastPost;

        return deleted;
    }

    else
    {
        Post *temp = platform->lastPost;
        for (int i = 1; i < n - 1; i++)
            temp = temp->prev;

        Post *temp2 = temp->prev;
        temp->prev = temp->prev->prev;
        temp2->prev->next = temp;

        if (platform->lastViewedPost == temp2)
            platform->lastViewedPost = temp;

        deleteComments(temp2->comments);
        free(temp2);
        platform->postCount--;
        deleted = true;

        return deleted;
    }
}

void deleteComments(Comment *comment)
{
    if (comment == NULL)
        return;

    deleteReplies(comment->replies);

    Comment *temp = comment;
    Comment *next;

    while (temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
}

void deleteReplies(Reply *reply)
{
    if (reply == NULL)
        return;

    Reply *temp = reply;
    Reply *next;

    while (temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
}

Post *viewPost(int n)
{
    if (platform == NULL)
        return NULL;

    if (platform->postCount == 0)
        return NULL;

    if (n > platform->postCount)
        return NULL;

    int count = n;
    Post *temp = platform->lastPost;
    for (int i = 1; i < count; i++)
        temp = temp->prev;

    platform->lastViewedPost = temp;
    platform->viewedPostFlag = true;
    return temp;
}

Post *currPost()
{
    if (platform == NULL)
        return NULL;

    if (platform->lastViewedPost == NULL)
        return NULL;

    return platform->lastViewedPost;
}

Post *nextPost()
{
    if (platform == NULL)
        return NULL;

    if (platform->lastViewedPost == NULL)
        return NULL;

    if (platform->lastViewedPost->prev == NULL)
        return platform->lastViewedPost;
    

    Post *temp = platform->lastViewedPost->prev;
    platform->lastViewedPost = temp;
    return platform->lastViewedPost;
}

Post *previousPost()
{
    if (platform == NULL)
        return NULL;

    if (platform->lastViewedPost == NULL)
        return NULL;

    if (platform->lastViewedPost->next == NULL)
        return platform->lastViewedPost;

    Post *temp = platform->lastViewedPost->next;
    platform->lastViewedPost = temp;

    return platform->lastViewedPost;
}

bool addComment(char *username, char *content)
{
    bool added = false;
    if (platform == NULL)
        return added;

    if (platform->lastViewedPost == NULL)
        return added;

    Comment *newComment = createComment(username, content);
    if (newComment == NULL)
        return added;

    if (platform->lastViewedPost->comments == NULL)
    {
        newComment->next = NULL;
        newComment->prev = NULL;
        platform->lastViewedPost->comments = newComment;
        platform->lastViewedPost->commentCount++;
        platform->lastViewedPost->lastComment = newComment;

        added = true;
        return added;
    }

    else
    {
        platform->lastViewedPost->lastComment->next = newComment;
        newComment->prev = platform->lastViewedPost->lastComment;
        newComment->next = NULL;
        platform->lastViewedPost->lastComment = newComment;
        platform->lastViewedPost->commentCount++;

        added = true;
        return added;
    }
}

bool deleteComment(int n)
{
    bool deleted = false;
    if (platform == NULL || platform->lastViewedPost == NULL)
        return deleted;

    if (platform->lastViewedPost->commentCount == 0 || n > platform->lastViewedPost->commentCount)
        return deleted;

    if (n == 1)
    {
        Comment *temp = platform->lastViewedPost->lastComment;
        platform->lastViewedPost->lastComment = platform->lastViewedPost->lastComment->prev;

        deleteReplies(temp->replies);
        free(temp);
        platform->lastViewedPost->commentCount--;

        if (platform->lastViewedPost->lastComment != NULL)
            platform->lastViewedPost->lastComment->next = NULL;

        platform->lastViewedPost->comments = NULL;

        deleted = true;
        return deleted;
    }

    else if (n == platform->lastViewedPost->commentCount)
    {
        Comment *temp = platform->lastViewedPost->comments;
        platform->lastViewedPost->comments = platform->lastViewedPost->comments->next;

        deleteReplies(temp->replies);
        free(temp);
        platform->lastViewedPost->commentCount--;

        deleted = true;
        return deleted;
    }

    else
    {
        Comment *temp = platform->lastViewedPost->lastComment;
        for (int i = 1; i < n - 1; i++)
            temp = temp->prev;
        Comment *temp2 = temp->prev;
        temp->prev = temp->prev->prev;

        deleteReplies(temp2->replies);
        free(temp2);
        platform->lastViewedPost->commentCount--;

        deleted = true;
        return deleted;
    }
}

Comment *viewComments()
{
    if (platform == NULL || platform->lastViewedPost == NULL || platform->lastViewedPost->comments == NULL)
        return NULL;
    else
        return platform->lastViewedPost->comments;
}

bool addReply(char *username, char *content, int n)
{
    bool added = false;
    if (platform == NULL || platform->lastViewedPost == NULL)
        return added;

    if (n > platform->lastViewedPost->commentCount)
        return added;

    if (n == 0)
        return added;

    Comment *tempC = platform->lastViewedPost->lastComment;
    int count = 1;
    while (tempC != NULL && count < n)
    {
        tempC = tempC->prev;
        count++;
    }

    if (tempC != NULL)
    {
        Reply *newReply = createReply(username, content);
        if (tempC->replies == NULL)
        {
            newReply->next = NULL;
            newReply->prev = NULL;
            tempC->replies = newReply;
            tempC->replyCount++;

            added = true;
            return added;
        }

        else
        {
            Reply *temp = tempC->replies;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newReply;
            newReply->prev = temp;
            tempC->replyCount++;

            added = true;
            return added;
        }
    }
    return added;
}

bool deleteReply(int n, int m)
{
    bool deleted = false;
    if (platform == NULL || platform->lastViewedPost == NULL || platform->lastViewedPost->commentCount == 0)
        return deleted;

    if (n > platform->lastViewedPost->commentCount)
        return deleted;

    Comment *tempC = platform->lastViewedPost->lastComment;
    for (int i = 1; i < n; i++)
        tempC = tempC->prev;
    if (tempC != NULL)
    {
        Reply *tempR = tempC->replies;
        if (tempR != NULL)
        {
            if (m == 1)
            {
                tempC->replies = tempC->replies->next;
                free(tempR);
                tempC->replyCount--;

                if (tempC->replies != NULL)
                    tempC->replies->prev = NULL;

                if (tempC->replyCount == 0)
                    tempC->replies = NULL;

                deleted = true;
                return deleted;
            }

            else if (m == tempC->replyCount)
            {
                while (tempR->next != NULL)
                    tempR = tempR->next;
                Reply *tempR2 = tempR->prev;
                tempR2->next = NULL;

                free(tempR);
                tempC->replyCount--;

                deleted = true;
                return deleted;
            }

            else
            {
                Reply *tempR = tempC->lastReply;
                for (int i = 1; i < m; i++)
                    tempR = tempR->prev;
                Reply *tempR2 = tempR->prev;
                tempR->prev = tempR->prev->prev;
                free(tempR2);
                tempC->replyCount--;

                deleted = true;
                return deleted;
            }
        }
    }

    return deleted;
}
