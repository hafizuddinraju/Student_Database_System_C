#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct student{
    char name[20];
    char ID[15];
    char dept[30];
    char intake[10];
    char section[10];
    long unsigned int phone_no;
};
struct log_in
{
    char usr[15];
    char pass[15];
};
struct log_in a;
struct log_in t;
struct log_in s;
float cgpa;
struct student stu;

///This will set the forground color for printing in a console window.
void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0};///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y;/// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 25);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWin(){
    int i,j;
    for(i = 2; i < 35; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

void clearWindow(){
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}


void window(){
    drawRectangle();
    gotoxy(28,2);
    SetColor(1);
    printf("STUDENT RECORD SYSTEM");
    gotoxy(17,3);
    printf("Bangladesh University of Business and Technology");
    gotoxy(17,4);
    printf("Plot #77-78 Road #9, Rupnagar,Mirpur-2, Dhaka-1216");
    gotoxy(25,24);
    SetColor(17);

}


void print_heading(const char st[]){
    ///SetColorAndBackground(17,15);
    gotoxy(45,8);printf("SRS : %s",st);
    SetColorAndBackground(17,15);
}


void add_student(){
    clearWindow();
    print_heading("Add Record");
    int print = 37;
    FILE *fp;
    fp = fopen("record.txt","ab+");
    //SetColor(1);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        ///here you can confirms the ID
        gotoxy(print,10);printf("Name: ");gets(stu.name);
        gotoxy(print,12);printf("ID: ");gets(stu.ID);
        gotoxy(print,14);printf("Department: ");gets(stu.dept);
        gotoxy(print,16);printf("Intake: ");scanf("%s",&stu.intake);
        gotoxy(print,18);printf("Section: ");scanf("%s",&stu.section);
        gotoxy(print,20);printf("Phone Number: ");scanf("%ld",&stu.phone_no);
        fwrite(&stu, sizeof(stu), 1, fp);
        gotoxy(40,22); printf("The record is sucessfully added");
    }
    SetColor(1);
    fclose(fp);
    return;
}

void search_student(){
    clearWindow();
    print_heading("Search Record");
    SetColor(1);
    char s_id[15];
    int isFound = 0;
    gotoxy(37,10);printf("Enter ID to Search: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb");
    while(fread(&stu,sizeof(stu),1,fp) == 1){
        if(strcmp(s_id,stu.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        gotoxy(37,12);printf("The record is Found");
        gotoxy(37,14);printf("Name: %s",stu.name);
        gotoxy(37,15);printf("ID: %s",stu.ID);
        gotoxy(37,16);printf("Department: %s",stu.dept);
        gotoxy(37,17);printf("Intake: %s",stu.intake);
        gotoxy(37,18);printf("Section: %s",stu.section);
        gotoxy(37,19);printf("Phone No: %ld",stu.phone_no);
    }else{
        gotoxy(37,12);printf("Sorry, No record found in the database");
    }
    SetColor(1);
    fclose(fp);
    return;
}

void mod_student(){
    clearWindow();
    print_heading("Modify Record");
    SetColor(1);
    char s_id[15];
    int isFound = 0, print = 37,p=2,num;
    gotoxy(37,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb+");
    while(fread(&stu, sizeof(stu),1,fp) == 1){
        if(strcmp(s_id, stu.ID) == 0){
                do{
               clearWin();
               gotoxy(p,8); printf("WHAT WOULD YOU LIKE TO EDIT..");
               gotoxy(p,10);printf("1.NAME");
               gotoxy(p,11);printf("2.ID");
               gotoxy(p,12);printf("3.DEPARTMENT");
               gotoxy(p,13);printf("4.INTAKE");
               gotoxy(p,14);printf("5.SECTION");
               gotoxy(p,15);printf("6.PHONE NUMBER");
               gotoxy(p,16);printf("7.WHOLE RECORD.");
               gotoxy(p,17);printf("8.GO BACK TO MAIN MENU.");
               gotoxy(p,19); printf("ENTER YOUR CHOICE:");
               fflush(stdin);
               scanf("%d",&num);
               fflush(stdin);
        switch(num)
        {
        case 1:
            gotoxy(print,12);printf("Name: ");gets(stu.name);
            gotoxy(print,14);printf("Successfully modified.");
            clearWin();
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        case 2:
            gotoxy(print,12);printf("ID: ");gets(stu.ID);
            gotoxy(print,14);printf("Successfully modified.");
            clearWin();
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        case 3:
            gotoxy(print,12);printf("Department: ");gets(stu.dept);
            gotoxy(print,14);printf("Successfully modified.");
            clearWin();
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        case 4:
            gotoxy(print,12);printf("Intake: ");scanf("%s",&stu.intake);
            gotoxy(print,14);printf("Successfully modified.");
            clearWin();
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        case 5:
            gotoxy(print,12);printf("Section: ");scanf("%s",&stu.section);
            gotoxy(print,14);printf("Successfully modified.");
            clearWin();
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        case 6:
            gotoxy(print,12);printf("Phone Number: ");scanf("%ld",&stu.phone_no);
            gotoxy(print,14);printf("Successfully modified.");
            clearWin();
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        case 7:
            fflush(stdin);
            gotoxy(print,12);printf("Name: ");gets(stu.name);
            gotoxy(print,14);printf("ID: ");gets(stu.ID);
            gotoxy(print,16);printf("Department: ");gets(stu.dept);
            gotoxy(print,18);printf("Intake: ");scanf("%s",&stu.intake);
            gotoxy(print,20);printf("Section: ");scanf("%s",&stu.section);
            gotoxy(print,22);printf("Phone Number: ");scanf("%ld",&stu.phone_no);
            gotoxy(print,24);printf("Successfully modified.");
            clearWin();
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        default:
             gotoxy(p,21);printf("YOU TYPED SOMETHING ELSE...");
             gotoxy(p,22);printf("Enter any key to try again...");
             getch();
             break;
        }
                }
               while(num<1||num>7);
        }

    }
    if(!isFound){
        gotoxy(print, 12);printf("No Record Found");
        clearWin();
    }
    fclose(fp);
    SetColor(1);
    return;
}

void delete_student(){
    clearWindow();
    print_heading("Delete Record");
    SetColor(1);
    char s_id[15];
    int print = 37;
    gotoxy(37,10);printf("Enter ID to Delete: ");fflush(stdin);
    gets(s_id);
    if(remove("record.txt")==0)
    {
    gotoxy(37,12);printf("The record is sucessfully deleted");
    }
    else
    {
        gotoxy(37,12);printf("The Data does not exist");
    }
    SetColor(1);
    return;
}
struct marksheet
{
    char id[20];
    char sub1[20],sub2[20],sub3[20],sub4[20];
    int marks1,marks2,marks3,marks4;
};
struct marksheet st;
float gp(int a)
{
    float g;
    if(a>=80&&a<=100)g=4.00;
    else if(a>=75&&a<=79)g=3.75;
    else if(a>=70&&a<=74)g=3.50;
    else if(a>=65&&a<=69)g=3.25;
    else if(a>=60&&a<=64)g=3.00;
    else if(a>=55&&a<=59)g=2.75;
    else if(a>=50&&a<=54)g=2.50;
    else if(a>=80&&a<=100)g=2.25;
    else if(a>=80&&a<=100)g=2.00;
    else
        g=0.00;
    return g;
}
float gpa(int a,int b, int c, int d)
{
    float g;
    g=(gp(a)+gp(b)+gp(c)+gp(c)+gp(d))/4;
    return g;
}
void gen_marksheet(){
    clearWindow();
    int print=37;
    print_heading("Generate Marksheet");
    FILE *fp;
    fp = fopen("Marksheet.txt","ab+");
    SetColor(1);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        gotoxy(print,10);printf("Enter id:");gets(st.id);
        gotoxy(print,12);printf("1st Subject: ");scanf("%s",st.sub1);
        gotoxy(print,13);printf("Marks:");scanf("%d",&st.marks1);
        gotoxy(print,14);printf("2nd Subject: ");scanf("%s",st.sub2);
        gotoxy(print,15);printf("Marks: ");scanf("%d",&st.marks2);
        gotoxy(print,16);printf("3rd Subject: ");scanf("%s",st.sub3);
        gotoxy(print,17);printf("Marks: ");scanf("%d",&st.marks3);
        gotoxy(print,18);printf("4th Subject: ");scanf("%s",st.sub4);
        gotoxy(print,19);printf("Marks: ");scanf("%d",&st.marks4);
        cgpa=gpa(st.marks1,st.marks2,st.marks3,st.marks4);
        fwrite(&st, sizeof(st), 1, fp);
        gotoxy(40,21); printf("Marksheet is successfully generated.");
    }
    SetColor(1);
    fclose(fp);
    return;
}
void show_marksheet(){
    clearWindow();
    print_heading("Show Marksheet");
    SetColor(1);
    char s_id[15];
    int print=37;
    struct marksheet st;
    int isFound = 0;
    gotoxy(37,10);printf("Enter ID: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("marksheet.txt","rb");
    while(fread(&st,sizeof(st),1,fp) == 1){
        if(strcmp(s_id,st.id) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        gotoxy(print,12);printf("1st Subject: %s",st.sub1);
        gotoxy(print,13);printf("Marks: %d",st.marks1);
        gotoxy(print,14);printf("2nd Subject: %s",st.sub2);
        gotoxy(print,15);printf("Marks: %d",st.marks2);
        gotoxy(print,16);printf("3rd Subject: %s",st.sub3);
        gotoxy(print,17);printf("Marks: %d",st.marks3);
        gotoxy(print,18);printf("4th Subject: %s",st.sub4);
        gotoxy(print,19);printf("Marks: %d",st.marks4);
        cgpa=gpa(st.marks1,st.marks2,st.marks3,st.marks4);
        gotoxy(print,21);printf("GPA: %.2f",cgpa);
    }else{
        gotoxy(37,12);printf("Sorry, No record found in the database");
    }
    SetColor(1);
    fclose(fp);
    return;
}
void del_marksheet()
{
    clearWindow();
    print_heading("Delete Record");
    SetColor(1);
    char s_id[15];
    int print = 37;
    gotoxy(37,10);printf("Enter ID to Delete: ");fflush(stdin);
    gets(s_id);
    if(remove("marksheet.txt")==0)
    {
    gotoxy(37,12);printf("The record is sucessfully deleted");
    }
    else
    {
        gotoxy(37,12);printf("The Data does not exist");
    }
    SetColor(1);
    return;
}
void admin_window(){
    clearWin();
    clearWindow();
    int choice;
    int x = 2;
    SetColor(1);
    while(1){
        gotoxy(x,8);printf("1. Add Student");
        gotoxy(x,10);printf("2. Search Student");
        gotoxy(x,12);printf("3. Modify Student Record");
        gotoxy(x,14);printf("4. Delete Student Record ");
        gotoxy(x,16);printf("5. Show marksheet");
        gotoxy(x,18);printf("6. Delete marksheet");
        gotoxy(x,20);printf("7. Back ");
        gotoxy(x,22);printf("8. Exit");
        gotoxy(x,24);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add_student();
                break;
            case 2:
                search_student();
                break;
            case 3:
                mod_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                show_marksheet();
                break;
            case 6:
                del_marksheet();
                break;
            case 7:
                clearWin();
                clearWindow();
                return;
                break;
            case 8:
                exit(0);
                break;
            default:
                break;
        }

    }

}
void teacher_window()
{
    clearWin();
    clearWindow();
    int choice;
    SetColor(1);
    int x = 2;
    while(1){
        gotoxy(x,8);printf("1. Search Student");
        gotoxy(x,10);printf("2. Generate Marksheet");
        gotoxy(x,12);printf("3. Show Marksheet");
        gotoxy(x,14);printf("4. Back");
        gotoxy(x,16);printf("5. Exit");
        gotoxy(x,18);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                search_student();
                break;
            case 2:
                gen_marksheet();
                break;
            case 3:
                show_marksheet();
                break;
            case 4:
                clearWin();
                clearWindow();
                return;
                break;
            case 5:
                exit(0);
                break;
            default:
                break;
        }

    }

}
void student_window()
{

    clearWin();
    clearWindow();
    int choice;
     int x = 2;
    SetColor(1);
    while(1){
        gotoxy(x,8);printf("1. Search Student");
        gotoxy(x,10);printf("2. Show Marksheet");
        gotoxy(x,12);printf("3. Back");
        gotoxy(x,14);printf("4. Exit");
        gotoxy(x,16);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                search_student();
                break;
            case 2:
                show_marksheet();
                break;
            case 3:
                clearWin();
                clearWindow();
                return;
                break;
            case 4:
                exit(0);
                break;
            default:
                break;
        }

    }

}
void registration()
{
    FILE *fp;
    int num,p=2,print=37;
    clearWin();
    clearWindow();
    fp=fopen("Pass.txt","ab+");
    do{
    gotoxy(4,8);printf("Register as");
    gotoxy(p,10);printf("1.Admin");
    gotoxy(p,11);printf("2.Teacher");
    gotoxy(p,12);printf("3.Student");
    gotoxy(p,13);printf("4.Back");
    gotoxy(p,15);printf("Enter your choice:");
    fflush(stdin);
    scanf("%d",&num);

    switch(num)
    {
    case 1:
        clearWindow();
        gotoxy(print,8);printf("Enter username & password to register.");
        fflush(stdin);
        gotoxy(print,10);printf("Username:");scanf("%s",a.usr);
        gotoxy(print,12);printf("Password:");scanf("%s",a.pass);
        fwrite(&a,sizeof(a),1,fp);
         fclose(fp);
        gotoxy(print,14);printf("Registration successfully done.");
        gotoxy(print,16);printf("Enter any key to continue...");
        getch();
        clearWin();
        clearWindow();
        return;
        break;
    case 2:
        clearWindow();
        gotoxy(print,8);printf("Enter username & password to register.");
        fflush(stdin);
        gotoxy(print,10);printf("Username:");scanf("%s",t.usr);
        gotoxy(print,12);printf("Password:");scanf("%s",t.pass);
        fwrite(&t,sizeof(t),1,fp);
         fclose(fp);
        gotoxy(print,14);printf("Registration successfully done.");
        gotoxy(print,16);printf("Enter any key to continue...");
        getch();
        clearWin();
        clearWindow();
        return;
        break;
    case 3:
        clearWindow();
        gotoxy(print,8);printf("Enter username & password to register.");
        fflush(stdin);
        gotoxy(print,10);printf("Username:");scanf("%s",s.usr);
        gotoxy(print,12);printf("Password:");scanf("%s",s.pass);
        fwrite(&s,sizeof(s),1,fp);
         fclose(fp);
        gotoxy(print,14);printf("Registration successfully done.");
        gotoxy(print,16);printf("Enter any key to continue...");
        getch();
        clearWin();
        clearWindow();
        return;
        break;
    case 4:
         clearWin();
         clearWindow();
        return;
        break;
    default:
        gotoxy(print,8);printf("YOU TYPED SOMETHING ELSE...");
        gotoxy(print,10);printf("Enter any key to try again...");
        getch();
        break;

    }

    }
    while(num<1||num>3);


}
int log_in()
{
    FILE *fp;
    int num,p=2,print=37,choice;
    char usr[15],pass[15];
    clearWin();
    clearWindow();
    fp=fopen("Pass.txt","rb+");
    do{
    gotoxy(4,8);printf("Log_in as");
    gotoxy(p,10);printf("1.Admin");
    gotoxy(p,11);printf("2.Teacher");
    gotoxy(p,12);printf("3.Student");
    gotoxy(p,13);printf("4.Back");
    gotoxy(p,15);printf("Enter your choice:");
    scanf("%d",&num);
    fflush(stdin);
    switch(num)
    {
    case 1:
        clearWindow();
        gotoxy(print,8);printf("Enter username & password to Log_in.");
        gotoxy(print,10);printf("Username:");scanf("%s",usr);
        gotoxy(print,12);printf("Password:");scanf("%s",pass);
         rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(strcmp(a.usr,usr)==0&&strcmp(a.pass,pass)==0)
                choice=1;
        }
        break;
    case 2:
        clearWindow();
        gotoxy(print,8);printf("Enter username & password to Log_in.");
        gotoxy(print,10);printf("Username:");scanf("%s",usr);
        gotoxy(print,12);printf("Password:");scanf("%s",pass);
        rewind(fp);
         while(fread(&t,sizeof(t),1,fp)==1)
        {
            if(strcmp(t.usr,usr)==0&&strcmp(t.pass,pass)==0)
                choice=2;
        }
        break;
    case 3:
        clearWindow();
        gotoxy(print,8);printf("Enter username & password to Log_in.");
        gotoxy(print,10);printf("Username:");scanf("%s",usr);
        gotoxy(print,12);printf("Password:");scanf("%s",pass);
         rewind(fp);
         while(fread(&s,sizeof(s),1,fp)==1)
        {
            if(strcmp(s.usr,usr)==0&&strcmp(s.pass,pass)==0)
                choice=3;
        }
        break;
    case 4:
         clearWin();
         clearWindow();
        return;
        break;
    default:
        gotoxy(print,12);printf("YOU TYPED SOMETHING ELSE...");
        gotoxy(print,14);printf("Enter any key to try again...");
        getch();
        break;

    }

    }
    while(num<1||num>3);
    switch(choice)
    {
    case 1:
        admin_window();
        break;
    case 2:
        teacher_window();
        break;
    case 3:
        student_window();
        break;
    default:
        gotoxy(print,14);printf("Invalid Username or Password.");
        gotoxy(print,15);printf("Press a key to try again...");
        getch();
        log_in();

        break;

    }
}


void main_window()
{
    int choice;
    SetColor(1);
    int x = 2,print=37;
    clearWin();
    clearWindow();
    fflush(stdin);
    while(1){
        gotoxy(x,8);printf("1. Register");
        gotoxy(x,10);printf("2. Log_in");
        gotoxy(x,12);printf("3. Exit");
        gotoxy(x,14);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                registration();
                break;
            case 2:
                log_in();
                break;
            case 3:
                exit(0);
                break;
            default:
                gotoxy(print,8);printf("YOU TYPED SOMETHING ELSE...");
                gotoxy(print,10);printf("Press a key to try again...");
                getch();
                clearWin();
                clearWindow();
                main_window();
                break;
        }

    }
}
int main(){
    ClearConsoleToColors(17,15);
    SetConsoleTitle("Student Record System");
    window();
    main_window();
    return 0;
}

