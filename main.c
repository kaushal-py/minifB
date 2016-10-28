#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

/**Global Variable Declarations**/
int CurrentUserIndex = 0;
int UserCounter = 1;
struct UserData * startUser = NULL;
struct User * startGraph = NULL;
struct UserData * currentUserPointer = NULL;

/*
* This structure stores all the data of a user
* in a linked list.
*/
struct UserData
{
    int sysID;
    char name[50];
    char password[20];
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
    char password[20],passwordRepeat[20],c;
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

        //printf("%s",password);

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
           passwordRepeat[index++] = c;
           putch('*');
        }
        passwordRepeat[index] = '\0';

        //printf("%s",temp->password);

        if(strcmp(passwordRepeat,password)==0)
        {
            strcpy(temp->password,password);
            break;
        }
        else
            printf("\nPasswords did not match. Please enter again.");
    }

    //-------------- Entering Bio Data --------------//
    /*
    printf("\n* Enter your BioData *");
    printf("\nEnter your NickName (less than 7 characters) : ");
    scanf("%s",temp->nickName);

    printf("\nEnter your Age : ");
    scanf("%d",&temp->age);

    fflush(stdin);
    printf("\nEnter your Contact Number : ");
    scanf ("%d",&temp->contact);*/

    addToUserData(temp);
    addToUserGraph(temp);

    credRefresh();

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

void credRefresh()
{
    FILE *fp;
    struct UserData * ptr;

    if((fp = fopen("UserCredentials.kbs","wb"))==NULL)
    {
        printf("\nFile Error");
        return;
    }

    ptr = startUser;

    while(ptr != NULL)
    {
        fwrite(ptr->name,50*sizeof(char),1,fp);
        fwrite(ptr->password,20*sizeof(char),1,fp);
        ptr = ptr->next;
    }
    fclose(fp);
}

/*
void bioRefresh()
{
    FILE *fp;
    struct UserData * ptr;

    if((fp = fopen("UserBio.kbs","wb"))==NULL)
    {
        printf("\nFile Error");
        return;
    }

    ptr = startUser;

    while(ptr != NULL)
    {
        fwrite(ptr->age,sizeof(int),1,fp);
        fwrite(ptr->contact,sizeof(int),1,fp);
        fwrite(ptr->password,6*sizeof(char),1,fp);
        ptr = ptr->next;
    }
    fclose(fp);
}*/

void credLoad()
{
    FILE *fp;
    struct UserData * ptr;
    int i = 0;

    ptr = (struct UserData * )malloc(sizeof(struct UserData));

    if((fp = fopen("UserCredentials.kbs","rb"))==NULL)
    {
        printf("\nFile Error");
        return;
    }

    fread(ptr->name,50*sizeof(char),1,fp);
    fread(ptr->password,20*sizeof(char),1,fp);

    while(1)
    {

        addToUserData(ptr);
        addToUserGraph(ptr);
        ptr = (struct UserData * )malloc(sizeof(struct UserData));
        if(!(fread(ptr->name,50*sizeof(char),1,fp)) || !(fread(ptr->password,20*sizeof(char),1,fp)))
            break;
    }
    fclose(fp);
}

/*
void bioLoad()
{
    FILE *fp;
    struct UserData * ptr;

    if((fp = fopen("UserBio.kbs","rb"))==NULL)
    {
        printf("\nFile Error");
        return;
    }

    ptr = startUser;

    while(ptr != NULL)
    {
        fread(ptr->age,sizeof(int),1,fp);
        fread(ptr->contact,sizeof(int),1,fp);
        fread(ptr->password,6*sizeof(char),1,fp);
        ptr = ptr->next;
    }
    fclose(fp);
}*/

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

void viewGraph()
{
    struct User * ptrUser;
    struct Friend * ptrFriend;

    ptrUser = startGraph;

    while(ptrUser!=NULL)
    {
        ptrFriend = ptrUser->startFriend;
        printf("\n%s -> ",ptrUser->UserPointer->name);
        while(ptrFriend!=NULL)
        {
            printf("%s, ",ptrFriend->Friend->name);
            ptrFriend = ptrFriend->next;
        }
        ptrUser = ptrUser->next;
    }
}

void storeGraph()
{
    struct User * ptrUser;
    struct Friend * ptrFriend;
    FILE * fp;

    if((fp=fopen("Graph.txt","w"))==NULL)
    {
        printf("\nFile Error");
    }

    ptrUser = startGraph;

    while(ptrUser!=NULL)
    {
        ptrFriend = ptrUser->startFriend;
        fprintf(fp,"%s",ptrUser->UserPointer->name);
        while(ptrFriend!=NULL)
        {
            fprintf(fp,"%s",ptrFriend->Friend->name);
            ptrFriend = ptrFriend->next;
        }
        ptrUser = ptrUser->next;
    }

    fclose(fp);
}

void readGraph()
{
    struct User * ptrUser;
    struct Friend * ptrFriend;
    FILE * fp;

    if((fp=fopen("Graph.txt","r"))==NULL)
    {
        printf("\nFile Error");
    }

    ptrUser = (struct User *)malloc(sizeof(struct User));

    ptrUser = startGraph;

    while(ptrUser!=NULL)
    {
        ptrFriend = ptrUser->startFriend;
        fscanf(fp,"%s",ptrUser->UserPointer->name);
        currentUserPointer = ptrUser->UserPointer;
        while(ptrFriend!=NULL)
        {
            fscanf(fp,"%s",ptrFriend->Friend->name);
            makeConnection(ptrFriend->Friend->name);
        }

        ptrUser = (struct User *)malloc(sizeof(struct User));
        ptrUser = ptrUser->next;
    }

    currentUserPointer = NULL;
}

void Login(char name[50])
{
    struct UserData * ptr;
    char password[20],c;
    int index;

    ptr = startUser;

    while(ptr != NULL)
    {
        if(strcmp(strupr(ptr->name),strupr(name))==0)
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

void addFriend(struct UserData * UserPointer,struct UserData * friend1)
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

    temp->Friend = friend1;
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
        if(strcmp(strupr(ptr->name),strupr(name))==0)
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

    storeGraph();
    printf("\n* Connection Successful *\nFriend Added");

}

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

    if(ptr == NULL)
    {
        printf("\n%s has no Friends.",tempUser->name);
        return;
    }

    printf("\nThe Friend List of %s is : ",tempUser->name);
    while(ptr != NULL)
    {
        printf("\n%s",ptr->Friend->name);
        ptr = ptr->next;
    }

}

void headerLoad()
{
    FILE * fp;
    char c;

    if((fp=fopen("header.txt","r"))==NULL)
    {
        printf("\nFile Error");
    }

    while((c=fgetc(fp))!=EOF)
    {
        printf("%c",c);
    }
}

void help()
{
    FILE * fp;

    if((fp=fopen("Documentation.txt","r"))==NULL)
    {
        printf("\nFile Error");
    }

    readFile(fp);
}

void readFile(FILE * fp)
{
    char ch,c;

    while((c=fgetc(fp))!=EOF)
    {
        if(c == '+')
        {
            printf("\nContinue reading?(c/q): ");
            ch=getch();
            if (ch=='c' || ch=='C')
            {
                continue;
            }
            else
                break;

        }
        printf("%c",c);
    }
    fclose(fp);
}

void loadingScreen()
{
    char load[70]="|/-\\|/-\\|/-\\|/-\\|/-\\|/-\\|/-\\|/-\\|/-\\\0";
    int i;
    printf("LOADING ");

    for(i=0;load[i]!='\0';i++)
    {
        printf("%c",load[i]);
        Sleep(120);
        putch('\b');

    }
    Sleep(200);
    system("cls");
}

/*
void displayBio(char name[50])
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

    printf("\n*****   %s's PROFILE   *****",temp->name);
    printf("Hello Friends, I am popularly known as %s. I am %d years old.\n",temp->nickName,temp->age);
    printf("Contact me on : %d",temp->contact);
}*/

void createPostFile()
{
    FILE * fp;

    if((fp=fopen("ADD_POST.txt","w"))==NULL)
    {
        printf("\nFile Error");
    }

    fprintf(fp,"\n");
    fprintf(fp,"\n++++++++++++++ Add the status Post in the above space ++++++++++");
    fprintf(fp,"\n++ Your post can be of any length. No limitation on post size.");
    fprintf(fp,"\n++ Anything written after the '+' sign will be ignored.");
    fprintf(fp,"\n++ Make sure your Post does not have any plus sign, or else");
    fprintf(fp,"\n++ even that will be ignored.");
    fprintf(fp,"\n++ Save the File after the Post is ready.");
    fprintf(fp,"\n++ Close notepad.exe after the Post will be Posted.");


    fclose(fp);
}

void timestamp(FILE * fp)
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    fprintf(fp,"%s",asctime( localtime(&ltime) ) );
}

void readPostFile()
{
    FILE * fpTimeTemp, * fpPost, *fpTime;
    char c;

    if((fpTimeTemp=fopen("TIMELINE_CPY.txt","w"))==NULL)
    {
        printf("\nFile Error");
    }

    if((fpPost=fopen("ADD_POST.txt","r"))==NULL)
    {
        printf("\nFile Error");
    }

    if((fpTime=fopen("TIMELINE.txt","r"))==NULL)
    {
        printf("\nFile Error");
    }

    while((c=fgetc(fpPost))!= EOF)
    {
        if(c=='+')
            break;
        fputc(c,fpTimeTemp);
    }
    fclose(fpPost);

    fprintf(fpTimeTemp," --- Posted by %s on : ",currentUserPointer->name);
    timestamp(fpTimeTemp);
    fprintf(fpTimeTemp,"\n+\n");


    while((c=fgetc(fpTime))!= EOF)
    {
        fputc(c,fpTimeTemp);
    }
    fclose(fpTime);
    fclose(fpTimeTemp);

    remove("TIMELINE.txt");
    remove("ADD_POST.txt");
    rename("TIMELINE_CPY.txt","TIMELINE.txt");
}

void addPost()
{
    if(currentUserPointer == NULL)
    {
        printf("\n* Login Error *\nYou aren't Logged in! Please login with a valid userName!");
        return;
    }

    createPostFile();

    (void)system("ADD_POST.txt");

    readPostFile();

    printf("\n* Post Successful *\nYou can view your post by >>>VIEW TIMELINE");
}

void viewTimeline()
{
    FILE * fp;

    if(currentUserPointer == NULL)
    {
        printf("\n* Login Error *\nYou aren't Logged in! Please login with a valid userName!");
        return;
    }

    if((fp=fopen("TIMELINE.txt","r"))==NULL)
    {
        printf("\nFile Error");
    }

    readFile(fp);
}

////////////////////////////////////////////////////

void main()
{
    char cmd1[10],cmd2[10], parameter[50];

    credLoad();
    //readGraph();
    loadingScreen();
    headerLoad();

    //(void)system("header.txt");

    //readGraph();

    do
    {
        printf("\n>>>");

        fflush(stdin);
        scanf("%s",cmd1);

        if(strcmp(strupr(cmd1),"SIGN") == 0)
        {
            scanf("%s",cmd2);

            if(strcmp(strupr(cmd2),"UP") == 0)
            {
                createAccount();
            }

            else
            {
                printf("\n* Invalid Command *\nType '?HELP' for Command Docs");
            }
        }

        else if(strcmp(strupr(cmd1),"VIEW") == 0)
        {
            scanf("%s",cmd2);

            if(strcmp(strupr(cmd2),"USERS") == 0)
            {
                displayUserData();
            }

            else if(strcmp(strupr(cmd2),"FRIENDLIST") == 0)
            {
                scanf("%s",parameter);
                displayFriends(parameter);
            }

            else if(strcmp(strupr(cmd2),"TIMELINE") == 0)
            {
                viewTimeline();
            }

            else
            {
                printf("\n* Invalid Command *\nType '?HELP' for Command Docs");
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
                printf("\n* Invalid Command *\nType '?HELP' for Command Docs");
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

            else if(strcmp(strupr(cmd2),"POST") == 0)
            {
                addPost();
            }

            else
            {
                printf("\n* Invalid Command *\nType '?HELP' for Command Docs");
            }
        }

        else if(strcmp(strupr(cmd1),"LOGOUT") == 0)
        {
            currentUserPointer = NULL;
            printf("\n* Logout Successful *");
        }

        else if(strcmp(strupr(cmd1),"?HELP") == 0)
        {
            help();
        }

        else if(strcmp(strupr(cmd1),"CLS") == 0)
        {
            system("cls");
            headerLoad();
        }

        else if(strcmp(strupr(cmd1),"QUIT") == 0)
        {
            break;
        }

        else
        {
            printf("\n* Invalid Command *\nType '?HELP' for Command Docs");
        }


    }while(1);
}
