#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Comment *createComment(char *username, char *content)
{
    Comment *comment = (Comment *)malloc(sizeof(Comment));
    strcpy(comment->username, username);
    strcpy(comment->content, content);
    comment->replies = NULL;
    comment->lastReply = NULL;
    comment->replyCount = 0;
    comment->next = NULL;
    comment->prev = NULL;
    
    return comment;
}