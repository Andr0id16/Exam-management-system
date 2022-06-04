#include<stdio.h>
#include<limits.h>
#include<stddef.h>
#include<string.h>
#include<stdlib.h>

int func(int x , int y)
{
    printf("in func");
    return 5;
    printf("after return");
}

int main(int argc,char* argv[])
{
    // int i=1;
    // int sum=0;
    // while(i<argc)
    // {
    //     sum+=atoi(argv[i++]);
    // }
    // printf("%d",sum);
    // printf("\n%d",argv[]);


    // printf("%d\n",CHAR_MIN);
    // char a = 1024;
    // printf("%d",a);
    printf("%d\n",sizeof(char));
    // printf("%d\n",sizeof(unsigned char));
    // printf("%d\n",sizeof(signed char));
    // printf("%d\n",sizeof(short));
    // printf("%d\n",sizeof(unsigned short));
    // printf("%d\n",sizeof(signed short));
    // printf("%d\n",sizeof(int));
    // printf("%d\n",sizeof(unsigned int));
    // printf("%d\n",sizeof(signed int));\
    // printf("%d\n",sizeof(long));
    // printf("%d\n",sizeof(double));
    // printf("%d\n",sizeof(long double));
    // printf("%d\n",sizeof(long long int));

    func(5,10);
    printf("%d\n",SHRT_MAX);
    //printf("%f",FLT_MAX);



     return 0;
}

