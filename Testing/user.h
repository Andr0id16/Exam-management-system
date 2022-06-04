#ifndef user_h
#define user_h
typedef struct user{
    char username[21];//max length of username is 20
    char password[11];//max length of password is 10

}user;
void initialize_user(user* u);
void get_password(char* password);
user get_user();
int check_user(const user current_user);
void create_new_user();
#endif
