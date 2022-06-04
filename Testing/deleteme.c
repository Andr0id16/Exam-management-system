#include<stdio.h>
#include<string.h>
int main()
{
    char student[100]={};
    printf("enter the name: ");
    scanf("%s",student);
    printf("%s",student);
    printf("--");
    char student2[2]={'\0'};
    if(strcmp(student,student2)==0)
    {
        printf("found");
    }
    return 0;
}
