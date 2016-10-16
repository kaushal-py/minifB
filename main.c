#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* This structure stores all the data of a user
* in a linked list.
*/
struct UserData
{
    int sysID;
    char name[50];
    char dob;
    char email[30];
    char password[20];
    char status[140];
    struct UserData * next;
};

/*
* A UserTable structure stores the start pointers
* of the UserData linked List.
*/
struct UserTable
{
    struct UserData * startUser;
};

/*
* 26 start pointers each storing data of one alphabet
*/
struct UserTable Users[26];

/*
* Graph using Adjacency list
*/

//Structure for Vertex of the Graph
struct User
{
    int sysID;
    struct Friend * startFriend;
    struct User * next;
};

//Structure for Edge of the Graph
struct Friend
{
    struct User * Friend;
    struct Friend * next;
};

void main()
{
    printf("\nSuccessful");
}
