#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
typedef struct student
{
    struct tm DOB;
    char add_line1[50];
    char add_line2[50];
    char name[30];
    char f_name[30];
    char m_name[30];
    char f_occupation[30];
    char m_occupation[30];
    char city[20];
    int regno;
    int grade;
    int pin;
    char gender;

} student;
void initialize_student(student *s);
void get_details(student *s);
void get_date(student *s);
int checkname(const char *name);
void check_date(student *s);
int search(int reg_no);
void view();
void delete_student();
void add_student();

void initialize_student(student *s)
{
    memset(s->name, '\0', 30);
    memset(s->f_name, '\0', 30);
    memset(s->m_name, '\0', 30);
    memset(s->f_occupation, '\0', 30);
    memset(s->m_occupation, '\0', 30);
    memset(s->add_line1, '\0', 50);
    memset(s->add_line2, '\0', 50);
    memset(s->city, '\0', 20);
    s->pin = 0;
    s->gender = '\0';
    s->regno = 0;
    s->grade = 0;
}

//function to get details....only limitation on student details is the number of characters no other checking is done
void get_details(student *s)
{
    int valid = 0;
    while (!valid)
    {
        printf("Enter name of student: ");
        scanf("%s", s->name);
        valid = checkname(s->name);
    }

    printf("Enter register no: ");
    scanf("%d", &(s->regno));
    valid = 0;
    while (!valid)
    {
        printf("Enter Father's name: ");
        scanf("%s", s->f_name);
        valid = checkname(s->name);
    }
    while (!valid)
    {
        printf("Enter Mother's name: ");
        scanf("%s", s->m_name);
    }
    fflush(stdin);
    printf("Enter Gender M/F/O: ");
    scanf("%c", &(s->gender));
    fflush(stdin);
    printf("Enter Father's occupation: ");
    scanf("%[^\n]s", s->f_occupation);
    fflush(stdin);
    printf("Enter Mother's occupation: ");
    scanf("%[^\n]s", s->m_occupation);
    fflush(stdin);
    printf("Enter address line 1: ");
    scanf("%[^\n]s", s->add_line1);
    fflush(stdin);
    printf("Enter Address line 2: ");
    scanf("%[^\n]s", s->add_line2);
    fflush(stdin);
    printf("Enter city: ");
    scanf("%s", s->city);
    printf("Enter pincode: ");
    scanf("%d", &(s->pin));
}
//seperate function since if date is wrong only date needs to be asked again
void get_date(student *s)
{
    printf("Enter Date of Birth dd/mm/yyyy: ");
    scanf("%d/%d/%d", &(s->DOB.tm_mday), &(s->DOB.tm_mon), &(s->DOB.tm_year));
    printf("Enter grade: ");
    scanf("%d", &(s->grade));
}

//fuction to check date     if date is invalid it calls get_date by itself
void check_date(student *s)
{
    //program to check date
    time_t current;
    time(&current);
    struct tm current_time = *(localtime(&current));
    int this_year = current_time.tm_year + 1900; // year starts from 1900

    int valid = 1;

    int year = s->DOB.tm_year;
    int month = s->DOB.tm_mon;
    int day = s->DOB.tm_mday;
    int age = this_year - year;

    // age of student cannot be too big/small compared to the grade
    //so max difference allowed is 2......also usually grade+6 is age of student
    //so a 1st grader is usually 1+6 = 7 years old
    if (abs(s->grade + 6 - age) > 2)
        valid = 0;
    else if (day > 0 && day < 32)
    {
        if (month == 2)
        {
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            {
                if (day > 29)
                    valid = 0;
            }
            else if (day > 28)
                valid = 0;
        }

        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (day > 30)
                valid = 0;
        }
        else if (day > 31 || (month < 1 && month > 12))
        {
            valid = 0;
        }
    }
    else
        valid = 0;
    if (!valid)
    {
        printf("Entered details are invalid...\n");
        printf("please re-enter details...\n");
        get_date(s);
        check_date(s);
    }
}
int checkname(const char *name)
{
    while (*name)
    {
        if (!isalpha(*name) && !isspace(*name))
            return 0;
        name++;
    }
    return 1;
}

int search(int reg_no)
{
    FILE *fp = fopen("/students.bin", "rb");
    int loc = 0;
    student s;
    student *sp = &s;
    initialize_student(&s);

    if (fp == NULL)
    {
        printf("Error opening database...\n");
    }
    // else
    // {
    //     while(fread(sp,sizeof(student),1,fp)!=0 && !flag)
    //     {
    //         if(s.regno==reg_no)
    //             flag=1;
    //     }
    // }
    //fclose(fp);
    //return s;
    else
    {
        while (fread(sp, sizeof(student), 1, fp) != 0 && loc == 0)
        {

            if (s.regno == reg_no)
                loc = ftell(fp);
        }
    }
    fclose(fp);
    printf("%d", loc);
    return loc;
}
void view()
{
    int reg_no;
    printf("register no: ");
    scanf("%d", &reg_no);

    int loc = search(reg_no);
    if (loc)
    {
        student s;
        initialize_student(&s);
        FILE *fp = fopen("/students.bin", "rb");
        printf("1");
        fseek(fp, loc - sizeof(student), SEEK_SET);
        printf("2");
        fread(&s, sizeof(student), 1, fp);
        printf("Name: %s\n", s.name);
        printf("register no: %d\n", s.regno);
        printf("Date of Birth: %d/%d/%d\n", s.DOB.tm_mday, s.DOB.tm_mon, s.DOB.tm_year);
        printf("Grade: %d\n", s.grade);
        printf("father's name: %s\n", s.f_name);
        printf("Father's occupation: %s\n", s.f_occupation);
        printf("Mother's occupation: %s\n", s.m_occupation);
        printf("Address: %s, %s\n", s.add_line1, s.add_line2);
        printf("City: %s\n", s.city);
        printf("pincode: %d\n", s.pin);

        fclose(fp);

        FILE *printer = fopen("print.txt", "w");
        if (printer == NULL)
        {
            printf("printer not found");
        }
        else
        {
            fprintf(printer, "Name: %s\n", s.name);
            fprintf(printer, "register no: %d\n", s.regno);
            fprintf(printer, "father's name: %s\n", s.f_name);
        }
        printf("                                          Press P to print\n");
        char c = getch();
        if (c == 'P')
        {
            char error[20] = {'\0'};
            system("print printer.txt 2>stdin");
            scanf("%s", error);
            if (error[0])
                printf("%s", error);
        }
        fclose(printer);
    }
    else
    {
        printf("error while searching for student");
    }
}
void add_student()
{
    FILE *fp = fopen("/students.bin", "ab");
    student s;
    initialize_student(&s);
    get_details(&s);
    int student_exists = search(s.regno);
    printf("%d", student_exists);
    if (student_exists)
    {
        printf("student already in database...");
    }
    else
    {
        get_date(&s);
        check_date(&s);
        fwrite(&s, sizeof(student), 1, fp);
        fclose(fp);
    }
}
void delete_student()
{
    int reg_no;
    printf("Enter the register no: ");
    scanf("%d", &reg_no);
    FILE *fp = fopen("/students.bin", "rb+"); //ab sets filepointer to eof on write operations
    if (fp == NULL)
    {
        printf("Error opening student file");
    }
    else
    {
        int pos = search(reg_no);
        if (!pos)
        {
            printf("student not found");
        }
        else
        {
            student deleted;
            initialize_student(&deleted);
            pos = pos - sizeof(student);
            fseek(fp, pos, SEEK_SET);
            //fwrite(&deleted,sizeof(student),1);
        }
    }
    fclose(fp);
}
void update_student()
{
    delete_student();
    add_student();
}
