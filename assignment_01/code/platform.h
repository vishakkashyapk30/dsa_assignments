#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "reply.h"
#include "comment.h"
#include "post.h"
#include <stdbool.h>

typedef struct Platform
{
    Post *posts;
    Post *lastViewedPost;
    int postCount; // Declared by me
    Post *lastPost; // Declared by me
    bool viewedPostFlag; // Declared by me
} Platform;

Platform *createPlatform();
bool addPost(char *username, char *caption);
bool deletePost(int n);
void deleteComments(Comment *comment); // Declared by me
void deleteReplies(Reply *reply);      // Decalred by me
Post *viewPost(int n);
Post *currPost();
Post *nextPost();
Post *previousPost();
bool addComment(char *username, char *content);
bool deleteComment(int n);
Comment *viewComments();
bool addReply(char *username, char *content, int n);
bool deleteReply(int n, int m);

#endif