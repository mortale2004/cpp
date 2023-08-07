#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <string>
#include <time.h>
#include "student.h"
#include "teacher.h"

int main()
{

    Student sObj;
    Teacher tObj;
    int choice;
    do
    {
        system("cls");

        cout<<"Enter Choice Given Below";
        cout<<"\n1.Student";
        cout<<"\n2.Teacher";
        cout<<"\n0.Exit\n";
        cin>>choice;

        system("cls");

        switch(choice)
        {
        case 1:
            sObj.Menu();
            break;
        case 2:
            tObj.Menu();
        case 0:
            cout<<endl<<"Thank You For Using This Software";
            break;
        default:
            cout<<endl<<"Enter Correct Choice!";
            break;
        }

        if (choice!=0)
        {
           cout<<endl<<endl;
           system("pause");
        }
    }while(choice!=0);

    return 0;
}

