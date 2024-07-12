#ifndef _POST_H_
#define _POST_H_

#include "reply.h"
#include "comment.h"

#define MAX_USERNAME_SIZE 50
#define MAX_CAPTION_SIZE 250

typedef struct Post
{
    char username[MAX_USERNAME_SIZE];
    char caption[MAX_CAPTION_SIZE];
    Comment *comments; 
    Comment *lastComment; //Declared by me
    int commentCount; //Declared by me
    struct Post *next;
    struct Post *prev;
} Post;

Post *createPost(char *username, char *caption);

#endif