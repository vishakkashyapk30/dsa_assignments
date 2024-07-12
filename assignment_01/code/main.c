#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "reply.h"
#include "comment.h"
#include "post.h"
#include "platform.h"

#define MAX_PROMPT_SIZE 50
#define MAX_USERNAME_SIZE 50
#define MAX_CAPTION_SIZE 250
#define MAX_CONTENT_SIZE 200

typedef Platform *globalPlatform;

int main()
{
    printf("The Following Operations are avaialable in the Social Media Platform:\n");
    printf("To create a platform - create_platform\n");
    printf("To add a post - add_post\n");
    printf("To delete a post - delete_post\n");
    printf("To view a post - view_post\n");
    printf("To view the the last viewed post - current_post\n");
    printf("To view the post previous to the last viewed post - next_post\n");
    printf("To view the post next to the last viewed post - previous_post\n");
    printf("To add comment to a post - add_comment\n");
    printf("To delete comment from a post - delete_comment\n");
    printf("To view a comment to a post - view_comments\n");
    printf("To add a reply to a comment of a post - add_reply\n");
    printf("To delete reply from a comment to a post - delete_reply\n");
    printf("To exit - exit\n");

    globalPlatform platform = NULL;

    while (true)
    {
        char prompt[MAX_PROMPT_SIZE];
        printf("Enter the operation you want to perform: ");
        scanf("%s", prompt);

        if (strcmp(prompt, "create_platform") == 0)
        {
            platform = createPlatform();
            if (platform == NULL)
                printf("Platform not created\n");
            else
                printf("Platform created successfully\n");
        }

        else if (strcmp(prompt, "add_post") == 0)
        {
            char username[MAX_USERNAME_SIZE];
            char caption[MAX_CAPTION_SIZE];
            printf("Enter username and caption: ");
            scanf("%s %[^\n]s", username, caption);
            if (addPost(username, caption))
                printf("Post added successfully\n");
            else
                printf("Post not added\n");
        }

        else if (strcmp(prompt, "delete_post") == 0)
        {
            int n;
            printf("Enter the post number: ");
            scanf("%d", &n);
            if (deletePost(n))
                printf("Post deleted successfully\n");
            else
                printf("Post not deleted\n");
        }

        else if (strcmp(prompt, "view_post") == 0)
        {
            int n;
            printf("Enter the post number: ");
            scanf("%d", &n);
            Post *post = viewPost(n);
            if (post == NULL)
                printf("Post does not exist\n");
            else
                printf("%s %s\n", post->username, post->caption);
        }

        else if(strcmp(prompt, "current_post") == 0)
        {
            Post *post = currPost();
            if (post == NULL)
                printf("Current Post does not exist\n");
            else
                printf("%s %s\n", post->username, post->caption);
        }

        else if (strcmp(prompt, "next_post") == 0)
        {
            Post *post = nextPost();
            if (post == NULL)
                printf("Next Post does not exist\n");
            else
                printf("%s %s\n", post->username, post->caption);
        }

        else if (strcmp(prompt, "previous_post") == 0)
        {
            Post *post = previousPost();
            if (post == NULL)
                printf("Previous Post does not exist\n");
            else
                printf("%s %s\n", post->username, post->caption);
        }

        else if (strcmp(prompt, "add_comment") == 0)
        {
            char username[MAX_USERNAME_SIZE];
            char content[MAX_CONTENT_SIZE];
            printf("Enter username and content: ");
            scanf("%s %[^\n]s", username, content);
            if (addComment(username, content))
                printf("Comment added successfully\n");
            else
                printf("Comment not added\n");
        }

        else if (strcmp(prompt, "delete_comment") == 0)
        {
            int n;
            printf("Enter the comment number: ");
            scanf("%d", &n);
            if (deleteComment(n))
                printf("Commented deleted successfully\n");
            else
                printf("Comment not deleted\n");
        }

        else if (strcmp(prompt, "view_comments") == 0)
        {
            Post *lastViewedPost = currPost();
            if (lastViewedPost == NULL)
                printf("No post has been viewed yet\n");
            
            else
            {
                Comment *comment = lastViewedPost->comments;
                if (comment != NULL)
                {
                    while (comment != NULL)
                    {
                        printf("%s %s\n", comment->username, comment->content);
                        Reply *reply = comment->replies;
                        while (reply != NULL)
                        {
                            printf("\t%s %s\n", reply->username, reply->content);
                            reply = reply->next;
                        }
                        comment = comment->next;
                    }
                }
                else
                    printf("No comments exist for the last viewed post\n");

            }
        }

        else if (strcmp(prompt, "add_reply") == 0)
        {
            char username[MAX_USERNAME_SIZE];
            char content[MAX_CONTENT_SIZE];
            int n;
            printf("Enter username and content: ");
            scanf("%s %[^\n]s", username, content);
            printf("Enter the comment number: ");
            scanf("%d", &n);
            if (addReply(username, content, n))
                printf("Reply added successfuly\n");
            else
                printf("Reply not added\n");
        }

        else if (strcmp(prompt, "delete_reply") == 0)
        {
            int n, m;
            printf("Enter the comment number: ");
            scanf("%d", &n);
            printf("Enter the reply number: ");
            scanf("%d", &m);
            if (deleteReply(n, m))
                printf("Reply deleted succesfully\n");
            else
                printf("Reply not deleted\n");
        }

        else if (strcmp(prompt, "exit") == 0)
        {
            printf("Exiting from the platform..\n");
            break;
        }

        else
            printf("Oops! Invalid operation\n");
    }
    return 0;
}
