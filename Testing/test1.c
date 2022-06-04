void login()
{
    char options1[][20]={"1.Login","2.Create New User Account","Exit"};

    int selected=options(options1);
    if(selected==3)
    {
        printf("Thankyou for using the examination management system");
        sleep(1);
        exit();
    }
    else if(selected==1)
    {
        printf("Login as:\n");
        user current_user=get_user();
        if(check_user(current user))
        {
            printf("Logging in");
            sleep(1);
            printf("...");
        }
        else
        {
            printf("Login unsuccessful...\n");
            printf("Reenter details or create new account...\n");
            del current_user;
            getch();
            fflush(stdin);
            login();
        }
    }
    else
    {
        create_new_user();
    }

}
