#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <time.h>
#include <string.h>
#include<Windows.h>
//Used macro

void changecolor()
{
    system("color 7A");
}
void revertcolor()
{
    system("color ");
}
void __attribute__((constructor)) changecolor();
void __attribute__((destructor)) revertcolor();
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "studentRecordSystem.bin"
#define USER_FILE_NAME  "userRecord.bin"
// Macro related to the students info
#define MAX_FATHER_NAME 50
#define MAX_STUDENT_NAME 50
#define MAX_STUDENT_ADDRESS 300
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
    int access_level;

} sFileHeader;
//Elements of structure
typedef struct// to call in program
{
    unsigned int student_id; // declare the integer data type
    char fatherName[MAX_FATHER_NAME];// declare the charecter data type
    char studentName[MAX_STUDENT_NAME];// declare the character data type
    char studentAddr[MAX_STUDENT_ADDRESS];// declare the character data type
    Date studentJoiningDate;// declare the integer data type
} s_StudentInfo;
//Align the message
void Exit()
{
    system("cls");
    system("color 0F");
    exit(1);
}
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
int searchUser(const char* username,const char* password);
//Head message
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############   Student Record Management System Project in C   ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
//Display message
void welcomeMessage()
{
    system("cls");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  WELCOME                  =");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =               Student Record              =");
    printf("\n\t\t\t        =                 MANAGEMENT                =");
    printf("\n\t\t\t        =                   SYSTEM                  =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
    
}
//Validate name
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len-1 ; ++index)
    {
        if((name[index] == '\n') || (name[index] == ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
// Add student in list
void addStudentInDataBase()
{
    s_StudentInfo addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        Exit();
    }
    headMessage("ADD NEW Students");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tStudent ID  = ");
    fflush(stdin);
    scanf("%u",&addStudentInfoInDataBase.student_id);
    do
    {
        printf("\n\t\t\tFather Name  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.fatherName,MAX_FATHER_NAME,stdin);
        status = isNameValid(addStudentInfoInDataBase.fatherName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tStudent Name  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.studentName,MAX_STUDENT_NAME,stdin);
        status = isNameValid(addStudentInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tStudent Address  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.studentAddr,MAX_FATHER_NAME,stdin);
        status = isNameValid(addStudentInfoInDataBase.studentAddr);
        if (status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(status);
    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&addStudentInfoInDataBase.studentJoiningDate.dd,&addStudentInfoInDataBase.studentJoiningDate.mm,&addStudentInfoInDataBase.studentJoiningDate.yyyy);
        //check date validity
        status = isValidDate(&addStudentInfoInDataBase.studentJoiningDate);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, fp);
    fclose(fp);
}
// search student
void searchStudent()
{
    int found = 0;
    int studentId =0;
    s_StudentInfo addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        Exit();
    }
    headMessage("SEARCH STUDENTS");
    //put the control on student detail
    // if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    // {
    //     fclose(fp);
    //     printf("\n\t\t\tFacing issue while reading file\n");
    //     Exit();
    // }
    printf("\n\n\t\t\tEnter Student ID NO to search:");
    fflush(stdin);
    scanf("%u",&studentId);
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if(addStudentInfoInDataBase.student_id == studentId)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tStudent id = %d\n",addStudentInfoInDataBase.student_id);
        printf("\n\t\t\tStudent name = %s",addStudentInfoInDataBase.studentName);
        printf("\t\t\tFather Name = %s",addStudentInfoInDataBase.fatherName);
        printf("\n\t\t\tStudent Address = %s",addStudentInfoInDataBase.studentAddr);
        printf("\t\t\tStudent Admission Date(day/month/year) =  (%d/%d/%d)",addStudentInfoInDataBase.studentJoiningDate.dd,
               addStudentInfoInDataBase.studentJoiningDate.mm, addStudentInfoInDataBase.studentJoiningDate.yyyy);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// view students function
void viewStudent()
{
    int found = 0;
    s_StudentInfo addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    unsigned int countStudent = 1;
    headMessage("VIEW STUDENT DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        Exit();
    }
    // if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    // {
    //     fclose(fp);
    //     printf("Facing issue while reading file\n");
    //     Exit();
    // }
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        printf("\n\t\t\tStudent Count = %d\n\n",countStudent);
        printf("\t\t\tStudent id = %u\n",addStudentInfoInDataBase.student_id);
        printf("\t\t\tStudent Name = %s",addStudentInfoInDataBase.studentName);
        printf("\t\t\tFather Name = %s",addStudentInfoInDataBase.fatherName);
        printf("\t\t\tStudent Address = %s",addStudentInfoInDataBase.studentAddr);
        printf("\t\t\tStudent Admission Date(day/month/year) =  (%d/%d/%d)\n\n",addStudentInfoInDataBase.studentJoiningDate.dd,
               addStudentInfoInDataBase.studentJoiningDate.mm, addStudentInfoInDataBase.studentJoiningDate.yyyy);
        found = 1;
        ++countStudent;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// Delete student entry
void deleteStudent()
{
    int found = 0;
    int studentDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    s_StudentInfo addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("Delete Student Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        Exit();
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        Exit();
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEnter Student ID NO. for delete:");
    scanf("%d",&studentDelete);
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if(addStudentInfoInDataBase.student_id != studentDelete)
        {
            fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
//function to update credential
void updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        Exit();
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        Exit();
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again:");
    fflush(stdin);
    getchar();
    Exit();
}
//Display menu
void adminmenu()
{
    int choice = 0;
    do
    {
        headMessage("ADMIN MENU");
        printf("\n\n\n\t\t\t1.Add Student");
        printf("\n\t\t\t2.Search Student");
        printf("\n\t\t\t3.View Student");
        printf("\n\t\t\t4.Delete Student");
        printf("\n\t\t\t5.Update Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        fflush(stdin);
        switch(choice)
        {
        case 1:
            addStudentInDataBase();break;
        case 2:
            searchStudent();break;
        case 3:
            viewStudent();break;
        case 4:
            deleteStudent();break;
        case 5:
            updateCredential();break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            Exit();
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
void teachermenu()
{
    int choice = 0;
    do
    {
        headMessage("TEACHER MENU");
        printf("\n\n\n\t\t\t1.Add Student");
        printf("\n\t\t\t2.Search Student");
        printf("\n\t\t\t3.Update Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        fflush(stdin);
        switch(choice)
        {
        case 1:
            addStudentInDataBase();break;
        case 2:
            searchStudent();break;
        case 3:
            updateCredential();break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");Exit();break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                //Loop Ended
}

//login password
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    // sFileHeader fileHeaderInfo = {0};
    // FILE *fp = NULL;
    // headMessage("Login");
    // fp = fopen(FILE_NAME,"rb");
    // if(fp == NULL)
    // {
    //     printf("File is not opened\n");
    //     Exit();
    // }
    // fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    // fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        //fgets(userName,MAX_SIZE_USER_NAME,stdin);
        scanf("%s",userName);
        fflush(stdin);

        printf("\n\t\t\t\tPassword:");
        scanf("%s",password);
        // if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        // {
        //     menu();
        // }
        int pos;
        if(pos=searchUser(userName,password))
        {
            FILE* fp=fopen(USER_FILE_NAME,"rb");
            fseek(fp,pos-FILE_HEADER_SIZE,SEEK_SET);
            sFileHeader current_user={0};
            fread(&current_user,FILE_HEADER_SIZE,1,fp);
            switch(current_user.access_level)
            {
                case 1:
                {
                    adminmenu();
                    break;
                }
                case 2:
                {
                    teachermenu();
                    break;
                }
                case 3:
                {   int choice =0;
                    do
                    {
                        headMessage("STUDENT MENU");

                        printf("\n\t\t\t1.View Student");
                        printf("\n\n\n\t\t\t0.Exit");
                        printf("\n\n\n\t\t\tEnter choice => ");
                        scanf("%d",&choice);
                        fflush(stdin);
                        switch(choice)
                        {
                            case 1:
                            searchStudent();break;
                            case 0:
                            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");Exit();break;
                            default:
                            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");

                        }
                    }while(choice!=0);
                    break;

                    }

                }


        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Username & Password Again \n\n");
            L++;
        }

    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        
        system("cls");
    }
}
//Check file exist or not
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
void init()
{   system("cls");
    FILE *fp = NULL;
    int status = 0;

    const char defaultUsername[] ="davidlaid";
    const char defaultPassword[] ="davidlaid";
    sFileHeader fileHeaderInfo;
    strcpy(fileHeaderInfo.username,defaultUsername);
    strcpy(fileHeaderInfo.password,defaultPassword);
    fileHeaderInfo.access_level=1;

    status = isFileExists(USER_FILE_NAME);

    if(!status)
    {   printf("creating user database...");
        loading_bar();
        sleep(2);
        system("cls");
        //create the binary file
        fp = fopen(USER_FILE_NAME,"wb");
        if(fp != NULL)
        {
            if(!searchUser(defaultUsername,defaultPassword))
                fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

int searchUser(const char* username,const char* password)
{
    int loc=0;
    if(isFileExists(USER_FILE_NAME))
    {
        FILE* fp=fopen(USER_FILE_NAME,"rb");
        sFileHeader search={0};

        while(fread(&search,FILE_HEADER_SIZE,1,fp) && loc==0)
        {
            if(!strcmp(username,search.username) && !strcmp(password,search.password))
                loc=ftell(fp);
        }

    }
    else
    {
        printf("File cannot be opened");
        Exit();
    }
    return loc;
}
int Usertypemenu()
{
    int choice = 0;
    do
    {
        headMessage("CREATE NEW ACCOUNT MENU");
        printf("\n\n\n\t\t\t1.Admin");
        printf("\n\t\t\t2.Teacher");
        printf("\n\t\t\t3.Student");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        if(choice==0)
            Exit();
        else if(choice>0 && choice<4 )
            return choice;

        else
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
                                           //Switch Ended
    }
    while(choice!=0);
                                           //Loop Ended
}

void createUser()
{


    int choice=Usertypemenu();

    sFileHeader new_user;
    if(choice==1)
    {
        int try=1;
        int keymatch=0;
        char key[6]={};
        while(try<=3 && !keymatch)
        {
            printf("Enter key:");
            scanf("%s",key);
            fflush(stdin);
            if(!strcmp(key,"admin"))
            keymatch=1;
        try++;
        }
        if(!keymatch)
        {
            printf("User creation failed");
            Exit();
        }
        else
        {
            new_user.access_level=1;
        }

    }
    if(choice==2)
    {
        int try=1;
        int keymatch=0;
        char key[6]={};
        while(try<=3 && !keymatch)
        {
            printf("Enter key:");
            scanf("%s",key);
            fflush(stdin);
            if(!strcmp(key,"teach"))
            keymatch=1;
        try++;
        }
        if(!keymatch)
        {
            printf("User creation failed");
            Exit();
        }
        else
        {
            new_user.access_level=2;
        }

    }

    if(choice==3)
    {
        new_user.access_level=3;
    }
        printf("\n\n\n\t\t\t\tUsername:");
        scanf("%s",new_user.username);
        fflush(stdin);
        printf("\n\t\t\t\tPassword:");
        scanf("%s",new_user.password);
        if(isFileExists(USER_FILE_NAME))
        {

            if(!searchUser(new_user.username,new_user.password))
                {
                    printf("Creating account...");
                    sleep(1);
                    FILE* fp=fopen(USER_FILE_NAME,"ab");
                fwrite(&new_user,FILE_HEADER_SIZE,1,fp);
                fclose(fp);
                }
            else
            {
                printf("Username already taken. Try different username");
                Exit();
            }

        }

}
void Mainmenu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Login");
        printf("\n\t\t\t2.Create New Account");
        printf("\n\t\t\t3.Delete account");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        fflush(stdin);
        switch(choice)
        {
        case 1:
        login();break;
        case 2:
        createUser();break;

        case 3:
            //deleteUser();break;

        case 0:
           printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");Exit();

        default:
        printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");

        }                                            //Switch Ended
    }
    while(choice!=0);                                //Loop Ended
}
void loading_bar()
{
    printf("\e[?25l");
    for(int i=1;i<=20;i++)
    {

        printf("\r\t\t\t\t\t");
        printf("[");

        for(int j=1;j<=i;j++)
        {
            printf("#");

        }
        for(int k=i;k<20;k++)
        {
            printf(" ");

        }
        printf("]");
        fflush(stdout);
        Sleep(50);

    }
    printf("\e[?25h");

}

int main()
{
    init();
    printf("Loading Existing Database...");
    loading_bar();
    // welcomeMessage();
    // sleep(2);
    Mainmenu();
    system("color 07");
    return 0;
}
