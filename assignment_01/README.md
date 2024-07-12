# DSA Assignment 01 - Social Media Platform ADT

## Details of the Student
- Name - Vishak Kashyap K
- Roll No. - 2023113012
- Branch - CND
- Group - 09

## ADTs (Abstract Data Types)

- Post ADT: Represents a post with title, content, and author information.
- Comment ADT: Represents a comment with username and text information.
- Reply ADT: Represents a reply with username and text information.
- All of the ADTs are implemented using Doubly Linked Lists.


## Declarations made for convenience
- Reply.h -> None
- Comment.h -> lastReply and replyCount.
- Post.h -> lastComment and commentCount.
- Platform.h -> lastPost, postCount and viewedPostFlag.


## Files

#### main.c
- This file contains the main entry point of the program.
- It initializes the platform and handles user interactions.
- It calls the necessary whenever the choice of operation is given.

#### platform.h & platform.c
- These files implement the platform functionality.
- It declares and defines functions for managing posts, comments, and replies.

#### post.h & post.c
- These files implement the post functionality.
- It defines the Post ADT and provides functions for creating, deleting, and retrieving posts and also to manage comments to the post.

#### comment.h & comment.c
- These files implement the comment functionality.
- It defines the Comment ADT and provides functions for creating, deleting, and retrieving comments and also to manage replies to the comment.

#### reply.h & reply.c
- These files implement the reply functionality.
- It defines the Reply ADT and provides functions for creating, deleting, and retrieving replies.


## Assumptions
- Each operation has a maximum character limit of 50.
- The operation naming conventioned defined at the beginning is followed.
- The create_platform function is given only in all input set and only at the beginning of the input.
- A single word is entered for username in all cases with a character limit of 50.
- The character limit for caption of posts is 250 and the content of comments and replies is 200.
- Whenever an integer input is seeked, only positive inputs are given.
- The input format is always followed.


