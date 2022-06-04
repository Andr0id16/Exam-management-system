#include<stdio.h>
#include<string.h>
#include<conio.h>
// void page1()
// {
//     printf("1. Log In");
//     printf("2. Create New User");
// }



// void LoggedIn()
// {
//     printf("1. Records");
//     printf("2. Exams");
//     printf("3. Exit\n");

// }
// void NewUser()
// {
//     printf()
// }

// void get_option()
// {
//     char option;
//     printf("Enter option\n");
//     scanf("%c",&option);
//     fflush(stdin);

//     switch(option)
//     {
//     case '1':
//     {
//         break;
//     }
//     case '2':
//     {
//         break;
//     }
//     case '3':
//     {
//         break;
//     }
//     default:
//     {
//         printf("Invalid input Re-enter:\n");
//         get_option();
//     }
//     }
// }



typedef struct User{
    char name[50];
    char password[10];

}User;


void create_new_user()
{   char name[50]={};
    char password[11]={};
    char *p;
    printf("Enter Username");
    scanf("%s",name);
    printf("Enter password");
    fflush(stdin);
    while(p!=&password[10])
    {   *p=getche();
        if (*p=='\n')
            break;
        printf("*");

    }
      printf("*");

}
int main()
{
    create_new_user();
    return 0;

}
