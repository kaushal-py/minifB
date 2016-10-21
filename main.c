#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**Global Variable Declarations**/
int CurrentUserIndex = 0;
int UserCounter = 1;
struct UserData * startUser = NULL;
struct User * startGraph = NULL;
struct User * currentUserPointer = NULL;

/*
* This structure stores all the data of a user
* in a linked list.
*/
struct UserData
{
    int sysID;
    char name[50];
    char dob[10];
    char password[20];
    char status[140];
    struct UserData * next;
};

/*
* Graph using Adjacency list
*/

//Structure for Vertex of the Graph
struct User
{
    struct UserData * UserPointer;
    struct Friend * startFriend;
    struct User * next;
};

//Structure for Edge of the Graph
struct Friend
{
    struct UserData * Friend;
    struct Friend * next;
};

//CREATE A NEW ACCOUNT
void createAccount()
{
    struct UserData * temp, * ptr;
    char password[20],c;
    int index = 0;
    char name[50];


    temp = (struct  UserData * )malloc(sizeof(struct UserData));

    /** Get Email and Password Input **/

    //-------------- Email ---------------//

    do
    {
        printf("Enter a Username : ");
        scanf("%s",(temp->name));
    }while(checkEmailValidity(temp->name)==0);

    //-------------- Password ---------------//
    while(1)
    {
        index = 0;
        printf("\nEnter Password : ");
        /* 13 is ASCII value of Enter key */
        while((c = getch()) != 13){
           if(index < 0)
               index = 0;
           /* 8 is ASCII value of BACKSPACE character */
           if(c == 8){
               putch('\b');
               putch(NULL);
               putch('\b');
               index--;
           continue;
           }
           password[index++] = c;
           putch('*');
        }
        password[index] = '\0';

        index = 0;

        printf("\nRe-Enter Password : ");
        /* 13 is ASCII value of Enter key */
        while((c = getch()) != 13){
           if(index < 0)
               index = 0;
           /* 8 is ASCII value of BACKSPACE character */
           if(c == 8){
               putch('\b');
               putch(NULL);
               putch('\b');
               index--;
           continue;
           }
           temp->password[index++] = c;
           putch('*');
        }
        temp->password[index] = '\0';

        if(strcmp(temp->password,password)==0)
            break;
        else
            printf("\nPasswords did not match. Please enter again.");
    }

    //-------------- Entering Bio Data --------------//
    printf("\n* Enter your BioData *");


    printf("\nEnter you Date of Birth (YYYY-MM-DD): ");
    scanf("%s",temp->dob);

    fflush(stdin);
    printf("\nEnter a status : (140 characters)");
    scanf ("%[^\n]%*c", temp->status);

    addToUserData(temp);
    addToUserGraph(temp);

    fileRefresh();

    printf("\nAccount Created Successfully!");
}

int checkEmailValidity(char name[50])
{
    struct UserData * ptr;

    //For first User
    if(startUser == NULL)
    {
        return 1;
    }

    //If Users already Exist
    ptr = startUser;

    while(ptr != NULL)
    {
        if((strcmp(ptr ->name,name)==0))
        {
            printf("\nUsername already Exists. Please enter a different email id.");
            return 0;
        }

        ptr = ptr ->next;
    }
    return 1;
}

void addToUserData(struct UserData * temp)
{
    //Adding the data to the linked List
    struct UserData * ptr;

    temp->sysID = UserCounter;
    UserCounter++;
    temp->next = NULL;

    if(startUser == NULL)
    {
        startUser = temp;
    }
    else
    {
        ptr = startUser;
        while(ptr ->next != NULL)
            ptr = ptr-> next;
        ptr ->next = temp;
    }
}

void addToUserGraph(struct UserData * temp)
{
    struct User * tempUser, * ptrUser;

    tempUser = (struct User *)malloc(sizeof(struct User));

    tempUser -> UserPointer = temp;
    tempUser -> next = NULL;
    tempUser -> startFriend = NULL;

    if(startGraph == NULL)
    {
        startGraph = tempUser;
    }
    else
    {
        ptrUser = startGraph;

        while(ptrUser->next != NULL)
        {
            ptrUser = ptrUser -> next;
        }

        ptrUser-> next = tempUser;
    }
}

void fileRefresh()
{
    FILE *fp;
    struct UserData * ptr;

    if((fp = fopen("User_Data.kbs","wb"))==NULL)
    {
        printf("\nFile Error");
        return;
    }

    ptr = startUser;

    while(ptr != NULL)
    {
        fwrite(ptr,sizeof(struct UserData),1,fp);
        ptr = ptr->next;
    }
    fclose(fp);
}

void fileLoad()
{
    FILE *fp;
    struct UserData * ptr;
    int i = 0;

    ptr = (struct UserData * )malloc(sizeof(struct UserData));

    if((fp = fopen("User_Data.kbs","rb"))==NULL)
    {
        printf("\nFile Error");
        return;
    }

    fread(ptr,sizeof(struct UserData),1,fp);


    while(1)
    {

        addToUserData(ptr);
        addToUserGraph(ptr);
        ptr = (struct UserData * )malloc(sizeof(struct UserData));
        if(!(fread(ptr,sizeof(struct UserData),1,fp)))
            break;
    }
    fclose(fp);
}

void displayUserData()
{
    struct UserData * ptr;

    ptr = startUser;

    printf("\nUsers are : ");
    while(ptr != NULL)
    {
        printf("\n%s",ptr->name);
        ptr = ptr->next;
    }
}


void Login(char name[50])
{
    struct UserData * ptr;
    char password[20],c;
    int index;

    ptr = startUser;

    while(ptr != NULL)
    {
        if(strcmp(ptr->name,name)==0)
        {
            printf("\nEmail Id Obtained");

            index = 0;
            printf("\nEnter Password : ");
            /* 13 is ASCII value of Enter key */
            while((c = getch()) != 13){
               if(index < 0)
                   index = 0;
               /* 8 is ASCII value of BACKSPACE character */
               if(c == 8){
                   putch('\b');
                   putch(NULL);
                   putch('\b');
                   index--;
               continue;
               }
               password[index++] = c;
               putch('*');
            }
            password[index] = '\0';

            if(strcmp(ptr->password,password)==0)
            {
                currentUserPointer = ptr;
                break;
            }
            else
            {
                printf("\n* Login failed *\nInvalid Password! Please try again!");
                break;
            }
        }

        ptr = ptr->next;
    }
    if(ptr == NULL)
        printf("\n* Login failed *\nInvalid UserName");
    else
    {
        printf("\n* Login Success! *\nHello %s! Welcome to FacebookMini",ptr->name);
    }
}

void addFriend(struct UserData * UserPointer,struct UserData * friend)
{
    struct User * ptr;
    struct Friend * temp;
    struct Friend * ptrFriend;

    temp = (struct Friend *)malloc(sizeof(struct Friend));

    ptr = startGraph;

    while(ptr != NULL)
    {
        if(ptr->UserPointer == UserPointer)
            break;
        ptr = ptr->next;
    }

    temp->Friend = friend;
    temp->next = NULL;

    if(ptr->startFriend == NULL)
    {
        ptr->startFriend = temp;
    }
    else
    {
        ptrFriend = ptr->startFriend;

        while(ptrFriend -> next != NULL)
        {
            ptrFriend = ptrFriend->next;
        }

        ptrFriend->next = temp;
    }

}

struct UserData * searchUserData(char name[50])
{
    struct UserData * ptr;

    ptr = startUser;

    while(ptr != NULL)
    {
        if(strcmp(ptr->name,name)==0)
            break;
        ptr = ptr ->next;
    }

    return ptr;
}

struct User * searchUser(struct UserData * temp)
{
    struct User * ptr;

    ptr = startGraph;

    while(ptr != NULL)
    {
        if(ptr->UserPointer==temp)
            break;
        ptr = ptr ->next;
    }

    return ptr;
}

int checkFriendship(struct UserData * tempUser, struct UserData * friendUser)
{
    struct User * temp;
    struct Friend * ptr;
    if(tempUser == friendUser)
    {
        return 0;
    }


    temp = searchUser(tempUser);

    ptr = temp->startFriend;

    while(ptr!= NULL)
    {
        if(ptr->Friend == friendUser)
            return 0;
        ptr = ptr->next;
    }

    if(ptr == NULL)
    {
        return 1;
    }
}

void makeConnection(char name[50])
{
    struct UserData * temp;

    if(currentUserPointer == NULL)
    {
        printf("\n* Login Error *\nYou aren't Logged in! Please login with a valid userName!");
        return;
    }

    if((temp=searchUserData(name))==NULL)
    {
        printf("\n* Username Error *\nInvalid Username!Please try again");
        return;
    }

    if(checkFriendship(currentUserPointer,temp)==0)
    {
        printf("\n* Connection Error *\n%s is Already your Friend",name);
        return;
    }

    addFriend(currentUserPointer,temp);
    addFriend(temp,currentUserPointer);

    printf("\n* Connection Successful *\nFriend Added");

}
////////////////////////////////////////////////////

void displayFriends(char name[50])
{
    struct UserData * tempUser;
    struct User * temp;
    struct Friend * ptr;

    if(currentUserPointer == NULL)
    {
        printf("\n* Login Error *\nYou aren't Logged in! Please login with a valid userName!");
        return;
    }

    if((tempUser=searchUserData(name))==NULL)
    {
        printf("\n* Username Error *\nInvalid Username!Please try again");
        return;
    }

    temp = searchUser(tempUser);

    ptr = temp->startFriend;

    if(ptr = NULL)
    {
        printf("\n%s has no Friends.",tempUser->name);
    }

    printf("\nThe Friend List of %s is : ",tempUser->name);
    while(ptr != NULL)
    {
        printf("\n%s",ptr->Friend->name);
        ptr = ptr->next;
    }

}

void main()
{
    char cmd1[10],cmd2[10], parameter[50];

    fileLoad();

    do
    {
        printf("\n>>>");

        fflush(stdin);
        scanf("%s",cmd1);

        if(strcmp(strupr(cmd1),"CREATE") == 0)
        {
            scanf("%s",cmd2);

            if(strcmp(strupr(cmd2),"ACCOUNT") == 0)
            {
                createAccount();
            }

            else
            {
                printf("\n* Invalid Command *\nType 'HELP?' for Command Docs");
            }
        }

        else if(strcmp(strupr(cmd1),"VIEW") == 0)
        {
            scanf("%s",cmd2);

            if(strcmp(strupr(cmd2),"USERS") == 0)
            {
                displayUserData();
            }

            else if(strcmp(strupr(cmd2),"FRIENDS") == 0)
            {
                scanf("%s",parameter);
                displayFriends(parameter);
            }

            else
            {
                printf("\n* Invalid Command *\nType 'HELP?' for Command Docs");
            }
        }

        else if(strcmp(strupr(cmd1),"LOGIN") == 0)
        {
            scanf("%s",cmd2);

            if(strcmp(strupr(cmd2),"AS") == 0)
            {
                scanf("%s",parameter);
                Login(parameter);
            }

            else
            {
                printf("\n* Invalid Command *\nType 'HELP?' for Command Docs");
            }
        }

        else if(strcmp(strupr(cmd1),"ADD") == 0)
        {
            scanf("%s",cmd2);

            if(strcmp(strupr(cmd2),"FRIEND") == 0)
            {
                scanf("%s",parameter);
                makeConnection(parameter);
            }

            else
            {
                printf("\n* Invalid Command *\nType 'HELP?' for Command Docs");
            }
        }

        if(strcmp(strupr(cmd1),"LOGOUT") == 0)
        {
            currentUserPointer = NULL;
        }


        else
        {
            printf("\n* Invalid Command *\nType 'HELP?' for Command Docs");
        }


    }while(strcmp(strupr(cmd1),"QUIT") != 0);
}
