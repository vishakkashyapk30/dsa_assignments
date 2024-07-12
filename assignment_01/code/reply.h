#ifndef _REPLY_H_
#define _REPLY_H_

#define MAX_USERNAME_SIZE 50
#define MAX_CONTENT_SIZE 200

typedef struct Reply
{
    char username[MAX_USERNAME_SIZE];
    char content[MAX_CONTENT_SIZE];
    struct Reply *next;
    struct Reply *prev;
} Reply;

Reply *createReply(char *username, char *content);

#endif