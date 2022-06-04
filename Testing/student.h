#ifndef student_h
#define student_h
#include <time.h>
typedef struct student{
    char name[30];
    char gender;
    int regno;
    int grade;
    struct tm DOB;
    char f_name[30];
    char m_name[30];
    char f_occupation[30];
    char m_occupation[30];
    char add_line1[30];
    char add_line2[30];
    char city[20];
    int pin;


}student;
void initialize_student(student* s);
void get_details(student* s);
void get_date(student* s);
int checkname(const char* name);
void check_date(student* s);
int search(int reg_no);
void view();
void add_student();
void delete_student();

#endif
