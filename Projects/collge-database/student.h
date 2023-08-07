
using namespace std;

struct DateOfBirth
{
    int year;
    int month;
    int day;
};
class Student
{
    // Variables of Student
    int rollNo, age, studentId;
    string name, mobileNo, address, email, Class;
    DateOfBirth dob;

    float percentage;


    // Variables of Database
    MYSQL* con;
    MYSQL_RES* res;
    MYSQL_ROW row;
    stringstream s;
    string temp;
    const char* query;


    // Connects to Database


    // Executes the query given to it and returns result of query.
    MYSQL_RES* executeQuery(MYSQL* con, const char* query)
    {
        if (mysql_query(con, query))
        {

            cout<<endl<<"Error:- "<<mysql_error(con);
            exit(1);
        }

        return mysql_store_result(con);
    }

    // shows all details about student
    void showDetails()
    {
            cout<<"\n\n***********************************";
            cout<<"\nStudent Id = "<<row[0];
            cout<<"\nRoll Number = "<<row[1];
            cout<<"\nName = "<<row[2];
            cout<<"\nEmail Id = "<<row[3];
            cout<<"\nMobile Number = "<<row[4];
            cout<<"\nPercentage = "<<row[5];
            cout<<"\nAge = "<<row[6];
            cout<<"\nAddress = "<<row[7];
            cout<<"\nDate Of Birth = "<<row[8];
    }

public:
    // constructor checks for connection is successful or not.
    Student()
    {
        if (connectToDB())
        {
            cout<<endl<<"Connected...";
        }
        else
        {
            cout<<endl<<"Error: "<<mysql_error(con);
            return;
        }
    }

    bool connectToDB()
    {

        con = mysql_init(0);
        con = mysql_real_connect(con, "localhost", "root", "", "database", 0, NULL, 0);
        return con;
    }

    // searches record in database and return the result
    bool searchRecord()
    {
        s.str("");

        cout<<endl<<"Enter Roll Number = ";
        cin>>rollNo;

        s<<"SELECT * FROM students WHERE rollNo = "<<rollNo<<";";
        temp = s.str();
        query = temp.c_str();

        res = executeQuery(con, query);
        row = mysql_fetch_row(res);
        if (row!=NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

     void searchRecordDetails()
    {
        s.str("");

        if (searchRecord())
        {
            showDetails();
        }
        else
        {
            cout<<endl<<"No Record Found!";
        }
    }


    void addRecord()
    {
        s.str("");

        do
        {

            if (searchRecord())
            {
                cout<<endl<<"This Roll Number Already Exist!";
                cout<<endl<<"Enter Another Mobile Number!";
                cout<<endl<<endl;system("pause");
                system("cls");
            }
            else
            {
                if (rollNo<0)
                {
                    cout<<"Enter Valid Mobile Number!";
                    cout<<endl;system("pause");
                    system("cls");
                    continue;
                }
                else
                {
                    break;
                }
            }

        }while(true);

        do
        {
            bool flag=false;
            cout<<"Enter Name = ";
            cin.ignore();
            getline(cin, name);

            for (unsigned int i=0; i<name.size(); i++)
            {
                if ((name[i]>='a' && name[i]<='z') || (name[i]>='A' && name[i]<='Z') || name[i] == ' ')
                {
                    flag=true;
                    continue;
                }
                else
                {
                    flag=false;
                    break;
                }
            }

            if (flag)
            {
                break;
            }
            else
            {
                cout<<"Enter Correct Name!";
                cout<<endl<<endl;system("pause");
                system("cls");
            }

        }while(true);

        do
        {
            cout<<"Enter Email ID = ";
            cin>>email;

            unsigned int pos = email.find("@gmail.com");
            if (pos==string::npos)
            {
                cout<<"Enter Correct Email Id!"<<endl;
                cout<<endl<<endl<<system("pause");
                system("cls");
            }
            else
            {
                break;
            }

        }while(true);

        do
        {
            bool flag = true;
            cout<<"Enter Mobile Number = ";
            cin>>mobileNo;

            for (unsigned int i=0; i<mobileNo.size(); i++)
            {
                if (mobileNo[i]>='0'&&mobileNo[i]<='9')
                {
                    continue;
                }
                flag = false;
            }

            if (mobileNo.size()==10 && flag)
            {
                 break;
            }
            else
            {
                cout<<"Enter Valid Mobile Number!"<<endl;
                cout<<endl<<endl<<system("pause");
                system("cls");
            }

        }while(true);

        do
        {
            cout<<"Enter Percentage = ";
            cin>>percentage;

            if (percentage>=1 && percentage<=100)
            {
                  break;
            }
            else
            {
                cout<<"Enter Valid Percentage!"<<endl;
                cout<<endl<<endl<<system("pause");
                system("cls");
            }
        }while(true);

        cout<<"Enter Class = ";
        cin.ignore();
        getline(cin, Class);

        cout<<"Enter Address = ";
        cin.ignore();
        getline(cin, address);

        do
        {
            cout<<"Enter Date of Birth (DD/MM/YYYY) = ";
            cin>>dob.day>>dob.month>>dob.year;

            time_t t = time(0);
            tm* now = localtime(&t);

            if ((dob.year > (now->tm_year + 1900)) || dob.year<1910)
            {
                cout<<"Enter Valid Year of Birth!"<<endl;
                system("pause");
                system("cls");
                continue;
            }
            else if (dob.month>12||dob.month<0)
            {
                cout<<"Enter Valid Month of Birth!"<<endl;
                system("pause");
                system("cls");
                continue;
            }
            else if (dob.day<0&&dob.day>31)
            {
                cout<<"Enter Valid Day of Birth!"<<endl;
                system("pause");
                system("cls");
                continue;
            }
            else
            {
                break;
            }
        }while(true);

        s.str("");
        s<<"INSERT INTO students (rollNo, name, email, mobileNo, percentage, age, class, address, dob) values("<<
        rollNo<<", '"<<name<<"', '"<<email<<"', '"<<mobileNo<<"', "<<percentage<<", FLOOR(DATEDIFF(CURRENT_DATE, STR_TO_DATE('"<<
        dob.year<<"-"<<dob.month<<"-"<<dob.day<<"', '%Y-%m-%d')) / 365)"<<", '"<<Class<<"', '"<<
        address<<"', '"<<dob.year<<"-"<<dob.month<<"-"<<dob.day<<"');";

        temp = s.str();
        query = temp.c_str();

        res = executeQuery(con, query);

        if (res==NULL)
        {
            cout<<endl<<"Record Saved Successfully...";
        }
    }

    void deleteRecord()
    {
        char choice;

        if (searchRecord())
        {

            showDetails();
            cout<<endl<<"Are Your Sure To Delete This Record (y/n) = ";
            cin>>choice;


            if (choice=='y'||choice=='Y')
            {
                s.str("");
                s<<"DELETE FROM students WHERE students.rollNo = "<<rollNo<<";";
                temp = s.str();
                query = temp.c_str();

                res = executeQuery(con, query);

                if (res==NULL)
                {
                    cout<<endl<<"Record Deleted Successfully...";
                }
            }
            else
            {
                cout<<endl<<"Record Not Deleted";
            }
        }
        else
        {
            cout<<endl<<"No Record Found!";
        }
    }

    void updateRecord()
    {
        char choice;

        if (searchRecord())
        {
            showDetails();

            cout<<endl<<"Are Your Sure To Update Mobile Number (y/n) = ";
            cin>>choice;

            if (choice=='y'||choice=='Y')
            {

                do
                {
                    bool flag=true;
                    cout<<endl<<"Enter Mobile Number = ";
                    cin>>mobileNo;

                    for (unsigned int i=0; i<mobileNo.size(); i++)
                    {
                        if (mobileNo[i]>='0'&&mobileNo[i]<='9')
                        {
                            continue;
                        }
                        flag = false;
                    }

                    if (flag && mobileNo.size()==10)
                    {
                        break;
                    }
                    else
                    {
                        cout<<endl<<"Enter Valid Mobile Number!";
                    }
                }while(true);

                s.str("");
                s<<"UPDATE students SET mobileNo = '"<<mobileNo<<"' WHERE rollNo = "<<rollNo<<";";
                temp = s.str();
                query = temp.c_str();

                res = executeQuery(con, query);

                if (res==NULL)
                {
                    cout<<endl<<"Mobile Number Updated Successfully...";
                }
            }
            else
            {
                cout<<endl<<"Mobile Number Not Updated";
            }
        }
        else
        {
            cout<<endl<<"No Record Found!";
        }
    }

    void showAllRecords()
    {
        s.str("");
        s<<"SELECT * FROM students;";
        temp = s.str();
        query = temp.c_str();

        res = executeQuery(con, query);

        while((row = mysql_fetch_row(res)))
        {
            showDetails();
        }
    }

    void Menu()
    {
        int choice;

        do
        {
            system("cls");

            cout<<"\nEnter the choice given below";
            cout<<"\n1.Add Student Record";
            cout<<"\n2.Delete Student Record";
            cout<<"\n3.Search Student Record";
            cout<<"\n4.Update Mobile Number";
            cout<<"\n5.Show All Records";
            cout<<"\n0.Main Menu\n";
            cin>>choice;
            system("cls");

            switch(choice)
            {
            case 1:
                addRecord();
                break;
            case 2:
                deleteRecord();
                break;
            case 3:
                searchRecordDetails();
                break;
            case 4:
                updateRecord();
                break;
            case 5:
                showAllRecords();
                break;
            case 0:
                break;
            default:
                cout<<endl<<"Enter Correct Choice!";
            }

            if (choice!=0)
            {
                cout<<endl<<endl;
                system("pause");
            }

        }while(choice!=0);

    }
};

