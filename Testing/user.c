//user.c
//a c program with functions for user login/creation
//uses memset for setting some default values 

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "pagemanager.h"
#include "student.h"
typedef struct user{
    char username[21];//max length of username is 20
    char password[11];//max length of password is 10
    int access_level;
}user;
void initialize_user(user* u);
void get_password(char* password);
void give_permission(user* guser);
user get_user();
int check_user(const user current_user);
user create_new_user();
user login();
void present_menu_to(user current_user);




//A neccesary function to make default values of username,password as '\0\0...\0' for insurance
//Just to avoid undefined values..also some functions may not work without this
void initialize_user(user* u)
{
    memset(u->username,'\0',21);
    memset(u->password,'\0',11);
    u->access_level=0;

}



//since the password part involves loops for printing star instead of letters  -seperate function to get password
//There are no restrictions on the password as long as it is maximum of 10 characters long
void get_password(char* password)
{
    char c;
    char* p=password;

    // runs 10 times so max length is 10 characters.....if user presses extra letters it just takes first 10
    while((c=getch())!='\r' && (p-password)<10)
    {
        *p=c;
        p++;
        printf("*");

    }
    printf("\n");
    fflush(stdin);//just in case
}

void give_permission(user* guser)
{
    char create_new_options[][20]={"1.Admin","2.Teacher","3.Student","4.Exit"};
    int selected=options(create_new_options,4);

    if(selected==4)
    {
        printf("Thankyou for using the examination management system");
        sleep(1);
        system("exit");

    }
    else
    {

        if(selected==1)
        {
            printf("Enter Key:");
            char key[11]={};
            char admin[11]="admin";
            //scanf("%s",key);
            get_password(key);
            if(!strcmp(key,admin))
            {
                guser->access_level=1;
            }
            else
            {
                printf("key does not match...\n");
                getch();
                give_permission(guser);
            }


        }
        else if(selected==2)
        {
            printf("Enter Key:");
            char key[11]={};
            char teach[11]="teach";
            //scanf("%s",key);
            get_password(key);
            if(!strcmp(key,teach))
            {
                guser->access_level=2;
            }
            else
            {
                printf("key does not match...\n");
                getch();
                give_permission(guser);
            }


        }
        else if(selected==3)
        {
            guser->access_level=3;
        }

    }
}


//to get current user       calls get_password
user get_user()
{
    user current_user;
    initialize_user(&current_user);
    give_permission(&current_user);
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
    FILE* userfile=fopen("users.bin","rb");
    user user_in_db;
    while(fread(&user_in_db,sizeof(user),1,userfile)&&!user_exists)
    {
        if(!strcmp(user_in_db.username,current_user.username) && !strcmp(user_in_db.password,current_user.password))
        {
            user_exists=1;
        }
    }

    return user_exists;

}



//create a new user
user create_new_user()
{   
    printf("\e[1;1H\e[2J");
    user new_user=get_user();
    printf("Confirm password: ");
    char confirmation[11]={};
    get_password(confirmation);
    //confirmation and password are both 11 character arrays so simple strcmp works
    if(!strcmp(confirmation,new_user.password))
    {
        FILE* userfile=fopen("users.bin","ab");
        if(userfile==NULL)
        {
            printf("Error opening user file");
        }
        else
        {
            int success=fwrite(&new_user,sizeof(user),1,userfile);
            fclose(userfile);
            if(success)
            {   printf("New user successfully created....\n");
                printf("Please Login to continue....");
            }
            else
            {
                printf("Error creating new user....\n");
                printf("Please try again....\n");
            }
                getch();
                printf("\e[1;1H\e[2J");
                login();
            }
        }
    else
        {
            printf("password does not match...\n");
            printf("Reenter details...");
            getch();
            new_user=create_new_user();
        }

        return new_user;
}

//simple function to give hash of the user's password
//This number is stored in the database
//not highly secure but better than storing and comparing plaintext passwords
// int hash_password(char* password)
// {   char fh[5];
//     char lh[5];
//     int f=0;
//     int l=0;
//     strncpy(fh,password,5);
//     strncpy(lh,password+5,5);
//     for(int i=0;i<5;i++)
//     {
//         f+=((7*(int)(fh[i]))%43)*7;
//         l+=(int)(lh[i])%17;

//     }

//     return (l%(f+1))*(f%(l+1));

// }





user login()
{
    char options1[][20]={"1.Login","2.Create New User","3.Exit"};
    user current_user;
    int selected=options(options1,3);
    if(selected==3)
    {
        printf("\e[1;1H\e[2J");
        printf("Thankyou for using the examination management system");
        sleep(1);
        exit(0);
    }

    else if(selected==1)
    {
        printf("\e[1;1H\e[2J");
        current_user=get_user();
        if(check_user(current_user))
        {
            printf("Logging in");
            sleep(1);
            printf("...\n");

        }
        else
        {
            printf("User not found...\n");
            printf("Reenter details or create new account...\n");
            getch();
            fflush(stdin);
            current_user=login();
        }
    }
    else
    {
        current_user=create_new_user();
    }
    return current_user;
}





int main()
{
    user current_user=login();
    present_menu_to(current_user);







    return 0;
}


void present_menu_to(user current_user)
{
    while(1)
    {
        if(current_user.access_level==1)
        {
            char admin_options[][20]={"1.View","2.Add","3.Delete","4.Update","5.Exit"};
            int selected=options(admin_options,5);
            switch(selected)
            {
                case 5:
                {   printf("Thankyou for using the management system");
                    exit(0);
                }
                case 1:
                {
                    view();
                    break;
                }
                case 2:
                {
                    add_student();
                    break;
                }
                case 3:
                {
                    delete_student();
                    break;
                }
            }

        }
        else if(current_user.access_level==2)
        {
            char teacher_options[][20]={"1.Add","2.Delete","3.Update","4.Exit"};
            int selected=options(teacher_options,4);
            switch(selected)
            {
                case 4:
                {   printf("Thankyou for using the management system");
                    exit(0);
                }
                case 1:
                {
                    add_student();
                    break;
                }
                case 2:
                {
                    //delete_student();
                    break;
                }
            }

        }
        else
        {
           view();
        }
        printf("Enter any key to continue...");
        getch();
    }
}



















