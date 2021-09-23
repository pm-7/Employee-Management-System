/* WELCOME TO THE EMPLOYEE ATTENDANCE MANAGEMENT SYSTEM
   HERE IS THE SOURCE CODE FOR THE EMPLOYEE ATTENDANCE MANAGEMENT SYSTEM . INCASE YOU HAVEN'T READ THE "READ_ME" FILE, THEN READ IT FIRST AND THEN IMPLEMENT THE CODE
   THANK YOU */
 
 
#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include <string.h>  


COORD coord = {0,0}; /// top-left corner of window


void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/** Main function started */

int main()
{
    FILE *fp, *ft; /// file pointers
    system("color 5f");
    char another, choice;

    /** structure that represent a employee */
    struct emp
    {
        char name[40]; ///name of employee
        int age; /// age of employee
        float bs; /// basic salary of employee
        int id; //employee id
        int noh; // no. of holidays
        int nopd; // no. of days present
        int noad; // no. of days absent
    };

    struct emp e; /// structure variable creation

    char empname[40]; /// string to store name of the employee

    long int recsize; /// size of each record of employee

   
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot Open File");
            exit(1);
        }
    }

    /// sizeo of each record i.e. size of structure variable e
    recsize = sizeof(e);

    // infinite loop continues until the break statement is encountered//
    while(1)
    {
        system("cls"); ///clear the console window 
        printf(" Project made by Abhilipsa, Pratik, Amisha and Yashmin.");
        printf("\n\n\n\n\n\n\n");
        printf("                              EMPLOYEE ATTENDANCE MANAGEMENT SYSTEM");
        gotoxy(30,10); /// move the cursor to postion 30, 10 from top-left corner
        printf("1. Add Records"); /// option for add record
        gotoxy(30,12);
        printf("2. List Records"); /// option for showing existing record
        gotoxy(30,14);
        printf("3. Modify Records"); // option for editing record//
        gotoxy(30,16);
        printf("4. Delete Records"); // option for deleting record//
        gotoxy(30,18);
        printf("5. Exit"); // exit from the program//
        gotoxy(30,20);
        printf("Enter Your Choice: "); // enter the choice 1, 2, 3, 4, 5//
        fflush(stdin); /// flush the input buffer
        choice  = getche(); /// get the input from keyboard
        switch(choice)
        {
        case '1':  /// if user press 1
            system("cls");
            fseek(fp,0,SEEK_END); 
            

            another = 'y';
            while(another == 'y')  ///  add record
            {
                printf("\nEnter Name: ");
                scanf("%s",e.name);
                printf("\nEnter Age: ");
                scanf("%d", &e.age);
                printf("\nEnter Basic Salary: ");
                scanf("%f", &e.bs);
                printf("\nEnter No. of Holidays: ");
                scanf("%d", &e.noh);
                printf("\nEnter No. of Present Days: ");
                scanf("%d", &e.nopd);
                printf("\nEnter No. of Absent Days: ");
                scanf("%d", &e.noad);
                printf("\nEnter Employee ID: ");
                scanf("%d", &e.id);

                fwrite(&e,recsize,1,fp); 

                printf("\nAdd Another Record(y/n) ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':// list record 
            system("cls");
            rewind(fp); 
            while(fread(&e,recsize,1,fp)==1)  
            {
				printf("DETAILS FOR A SINGLE MONTH\n");
				printf("\n Employee ID:        %d",e.id);
				printf("\n Employee NAME:      %s",e.name);
				printf("\n Employee AGE:       %d",e.age);
				printf("\n BASIC SALARY :      %f",e.bs);
				printf("\n\n ATTENDANCE DETAILS");
				printf("\n NO OF DAYS PRESENT: %d",e.nopd);
				printf("\n NO OF DAYS ABSENT:  %d",e.noad);
				printf("\n NO OF HOLIDAYS:     %d",e.noh);
				printf("\n NO OF WORKING DAYS: %d\n\n\n",e.nopd+e.noad);
				printf("------------------------------------------------\n");
                
            }
            getch();
            break;

        case '3':  /// Editing existing record
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the Employee Name To Modify: ");
                scanf("%s", empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)  
                {
                    if(strcmp(e.name,empname) == 0)  
                    {
                        printf("\nEnter New Name, Age, Basic Salary, No. of holidays, No of days Present, No of days absent and employee id: ");
                        scanf("%s%d%f%d%d%d%d",e.name,&e.age,&e.bs,&e.noh,&e.nopd,&e.noad,&e.id);
                        fseek(fp,-recsize,SEEK_CUR); 
                        fwrite(&e,recsize,1,fp); 
                        break;
                    }
                }
                printf("\nModify Another Record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':// delete an employee
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter Name of the Employee to Delete: ");
                scanf("%s",empname);
                ft = fopen("Temp.dat","wb");  
                rewind(fp); 
                while(fread(&e,recsize,1,fp) == 1)  
                {
                    if(strcmp(e.name,empname) != 0)  
                    {
                        fwrite(&e,recsize,1,ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); 
                rename("Temp.dat","EMP.DAT"); 
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete Another Record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5':
			printf("THANK YOU FOR VISITING" );
            fclose(fp);  
            exit(0); 
        }
    }
    return 0;
}
