#include<stdio.h>
typedef struct student{
int rollno;
char name[10];
int marks;
}student;
// basically when you use student[2].rollno consider the return as the variable rollno so whatever i can do with the actual variable name rollno i can do with this so
// &rollno is fine,rollno++ etc;
int main()
{
    student students[1000];
    printf("enter the info\n");


    // for(int i=0;i<3;i++)// can be changed to accept any number of students
    // {
    //     printf("Enter roll no\n");
    //     scanf("%d",&students[i].rollno);

    //     printf("Enter name\n");
    //     scanf("%s",students[i].name);

    //     printf("Enter marks\n");
    //     scanf("%d",&students[i].marks);
    // }


   //student *p=students;

   //array elemts can be accessed using pointer
   //p is a pointer which points to the first element of the array of students
   //so the first element is a structure
   //dereferencing the pointer will give the value of the structures which happens to be the roll no since it is stored first
   // on incrementing the pointer it will point to the next student(structure)  int he array of students
   // once a pointer points to the address of a structure...
   // *p gives first element by default even though *p is a struct like how *p is an int if p is of type int
   // (*p).rollno gives roll no (*p).name gives name and so on
   // p->rollno gives rollno IT GIVES THE VARIABLE ROLL NUMBER WHICH IS SIMILAR TO OBJECT.VARIABLE
   // &(p->rollno) gives address of rollno kinda like - &rollno of the structure this can be used in scanf
   // p->name gives the variable name which by itself is has an address so it need not be used with &

   // int a[5]={};
   // scanf("%d",a);// works  since its the same as &a[0];
   // printf("%d",a[0]);



}



