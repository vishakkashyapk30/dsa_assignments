#include "post.h"
#include "comment.h"
#include "reply.h"
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Reply *createReply(char *username, char *content)
{
    Reply *reply = (Reply *)malloc(sizeof(Reply));
    strcpy(reply->username, username);
    strcpy(reply->content, content);
    reply->next = NULL;
    reply->prev = NULL;
    
    return reply;
}
