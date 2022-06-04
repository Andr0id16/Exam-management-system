#include <stdio.h>
int main()
{
    char username[10];
    FILE *fp;
    fp = fopen("login_data.txt", "a");

    printf("Enter your username\n");
    scanf("%[^\n]s", username);
    fprintf(fp, "username:\n%s\n", username);
}