//main.c
#include "user.h"
#include "student.h"
#include "pagemanager.h"

int main()
{

    printf("Welcome to examination management system");
    sleep(1);
    char options1[20]={"1.Login","2.create account","3.exit"};
    int selected=options(options1);

     if(selected==3)
    {
        printf("\nthankyou for using the examination management system...");
        sleep(2);
        exit(0);

    }
    else
        {

        user current_user=get_user();
        if(selected==1)
        {
            if(check_user(current_user))
        {
            printf("\nyou can continue..");
        }
        else
        {
            printf("\nuser not found");
            printf("Please reenter the details or create new account");
        }
        }

    else if(selected==2)
    {

        printf("please enter the details for your new account:")
        create_new_user();
    }
}


return 0;
}

