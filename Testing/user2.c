//user.c
//a c program with functions for user login/creation
//uses memset for setting some default values 

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef struct user{
    char username[21];//max length of username is 20
    char password[11];//max length of password is 10
    int access_level;
}user;
void initialize_user(user* u);
void get_password(char* password);
user get_user();
int check_user(const user current_user);
void create_new_user();



//A neccesary function to make default values of username,password as '\0\0...\0' for insurance
//Just to avoid undefined values..also some functions may not work without this
void initialize_user(user* u)
{
    memset(u->username,'\0',21);
    memset(u->password,'\0',11);
    access_level=0;

}



//since the password part involves loops for printing star instead of letters  -seperate function to get password
//There are no restrictions on the password as long as it is maximum of 10 characters long
void get_password(char* password)
{
    char c;
    char* p=password;

    // runs 10 times so max length is 10 characters.....if user presses extra letters it just takes first 10
    while((c=getch())!='\r' && (p-password)<10)
    {   *p=c;
        p++;
        printf("*");
    }
    fflush(stdin);//just in case
}



//to get current user       calls get_password
user get_user()
{
    user current_user;
    initialize_user(&current_user);

    char* p=current_user.password;
    printf("Enter username: " );
    scanf("%s",current_user.username);
    fflush(stdin);
    printf("Enter password: ");
    // scanf("%s",current_user.password);
    get_password(current_user.password);
    return current_user;
}



//for existing users
int check_user(const user current_user)
{
    int user_exists=0;
    //reads existing user data from file
    //returns 1 if found else returns 0;
    //if not found redirect to page1 to reenter

    return user_exists;

}



//create a new user
void create_new_user()
{   
    create_new_options[][20]={"1.Admin","2.Teacher","3.Student","4.Exit"};
    int selected=options(create_new_options);

    if(selected==4)
    {
        printf("Thankyou for using the examination management system");
        sleep(1);
        exit();

    }
    else
    {
        user new_user=get_user();
        if(selected==1)
        {
            printf("Enter Key:");
            char key[6];
            char admin[]="admin";
            scanf("%s",key);
            if(!strcmp(key,admin))
            {
                new_user.access_level=1;
            }
            else
            {
                printf("key does not match...\n");
                create_new_user();
            }


        }
        else if(selected==2)
        {
            printf("Enter Key:");
            char key[6];
            char teach[]="teach";
            scanf("%s",key);
            if(!strcmp(key,teach))
            {
                new_user.access_level=2;
            }
            else
            {
                printf("key does not match...\n");
                create_new_user();
            }


        }
        else if(selected==3)
        {
            new_user.access_level=3;
        }


        printf("Confirm password: ");
        char confirmation[11]={};
        get_password(confirmation);
        //confirmation and password are both 11 character arrays so simple strcmp works 
        if(!strcmp(confirmation,new_user.password))
        {
            //write to file/database

            printf("New user successfully created....");
            printf("Please Login to continue....");
        }
        else
            {
                printf("password does not match...\n");
                create_new_user();
            }

}

//simple function to give hash of the user's password
//This number is stored in the database
//not highly secure but better than storing and comparing plaintext passwords
int hash_password(char* password)
{   char fh[5];
    char lh[5];
    int f=0;
    int l=0;
    strncpy(fh,password,5);
    strncpy(lh,password+5,5);
    for(int i=0;i<5;i++)
    {
        f+=((7*(int)(fh[i]))%43)*7;
        l+=(int)(lh[i])%17;

    }

    return (l%(f+1))*(f%(l+1));

}


void give_permission(user* guser)
{
    create_new_options[][20]={"1.Admin","2.Teacher","3.Student","4.Exit"};
    int selected=options(create_new_options);

    if(selected==4)
    {
        printf("Thankyou for using the examination management system");
        sleep(1);
        exit();

    }
    else
    {
        
        if(selected==1)
        {
            printf("Enter Key:");
            char key[6];
            char admin[]="admin";
            scanf("%s",key);
            if(!strcmp(key,admin))
            {
                guser->access_level=1;
            }
            else
            {
                printf("key does not match...\n");
                give_permission();
            }


        }
        else if(selected==2)
        {
            printf("Enter Key:");
            char key[6];
            char teach[]="teach";
            scanf("%s",key);
            if(!strcmp(key,teach))
            {
                guser->access_level=2;
            }
            else
            {
                printf("key does not match...\n");
                give_permission();
            }


        }
        else if(selected==3)
        {
            guser->access_level=3;
        }

}




























