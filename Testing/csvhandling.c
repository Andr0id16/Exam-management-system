//csv files
//contains information about cricket matches between 2008 and 16
//first row is the column headers
//577 rows with commas in between data
#include<stdio.h>
#include<string.h>
int main()
{
    // char c;
    // int count=0;
    // //getchar will always wait for the buffer
    // while(c=getchar()!=EOF)
    // {
    //     // fflush(stdin);
    //     // c=getchar();//will wait for \n to send the buffer
    //     count++;
    // }//this will count including newline
    // printf("%d",count);
    char sentence[10];
    FILE* fp=fopen("text.txt","r");
    //fputs("This is line 1",fp);//fputs does not include a newline in the end it will just start writing fromthe location where fp is.
    //fputs("This is line 2",fp);


    // fgets(sentence,100,fp);
    // printf("\n%d",strlen(sentence));
    // printf("%s",sentence);
    // fgets(sentence,100,fp);
    // printf("\n%d",strlen(sentence));
    // printf("\n%s",sentence);
    // fgets(sentence,100,fp);
    // printf("\n%d",strlen(sentence));
    // printf("\n%s",sentence);
    // char *s=fgets(sentence,100,fp);
    // printf("\n%s",sentence);

    // fgets(sentence,1,fp);
    //fgets(sentence,2,fp);//
    fgets(sentence,8,fp);
    rewind(fp);
    fseek(fp,10,0);
    int pos=ftell(fp);
    char c=fgetc(fp);
    printf("%c",c);

    printf("%ld",pos);






    return 0;
}
