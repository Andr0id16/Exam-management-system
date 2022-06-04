//loading_bar.c
#include<stdio.h>
#include<time.h>
int fact(int n);
int main()
{
    int n;
    printf("Enter the number");
    scanf("%d",&n);
    int time1=clock_t;
    printf("%d\n",time1);
    n=fact(n);
    int time2=clock_t;
    printf("%d",time2);
    int time=(time2-time1);
    while((clock()-time)<=(time*10))
    {
        printf("|");

    }
    printf("factorial is %d",n);




}



int fact(int n)
{
    if (n==0)
        return 1;
    else return n*fact(n-1);
}



