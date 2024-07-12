#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Post *createPost(char *username, char *caption)
{
    Post *post = (Post *)malloc(sizeof(Post));
    strcpy(post->username, username);
    strcpy(post->caption, caption);
    post->comments = NULL;
    post->lastComment = NULL;
    post->commentCount = 0;
    post->next = NULL;
    post->prev = NULL;
    
    return post;
}
