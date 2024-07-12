#ifndef _COMMENT_H_
#define _COMMENT_H_

#include "reply.h"

#define MAX_USERNAME_SIZE 50
#define MAX_CONTENT_SIZE 200

typedef struct Comment
{
    char username[MAX_USERNAME_SIZE];
    char content[MAX_CONTENT_SIZE];
    Reply *replies;
    Reply *lastReply; //Declared by me
    int replyCount; //Declared by me
    struct Comment *next;
    struct Comment *prev;
} Comment;

Comment *createComment(char *username, char *content);

#endif