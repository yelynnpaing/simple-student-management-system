#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class User
{
private:
    char stdFirstName[50], stdLastName[50], fatherName[50], address[200];
    long int stdId, phoneNumber;

public:

     void showStd()
    {
        cout << "\nStudent ID : " << stdId << endl;
        cout << "Name : " << stdFirstName << " " << stdLastName << endl;
        cout << "Father Name : " << fatherName << endl;
        cout << "Address : " << address << endl;
        cout << "Phone Number : " << phoneNumber << endl;
    }

    void searchWithId()
    {
        ifstream studentFile;
        long int id;
        cout << "\nEnter Student ID : ";
        cin >> id;

        studentFile.open("SSMS.dat", ios::binary);

        while(!studentFile.eof())
        {
            if(studentFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(id == stdId)
                {
                    cout << "\nStudent Information\n";
                    cout << "- - - - - - - - - - - \n";

                    showStd();
                    return;
                }
            }
        }

        cout << "\nNo records found.\n";
        studentFile.close();
    }

    void searchWithPhone()
    {
        long int phone;
        ifstream studentFile;
        cout << "\nEnter Student Phone Number : ";
        cin >> phone;

        studentFile.open("SSMS.dat", ios::binary);

        while(!studentFile.eof())
        {
            if(studentFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(phone == phoneNumber)
                {
                    cout << "\nStudent Information\n";
                    cout << "- - - - - - - - - - - \n";
                    showStd();
                    return;
                }
            }
        }
        cout << "\nNo records found.";
        studentFile.close();
    }

};


void userPanel()
{
    User normalUser;
    system("Color 0A");
    int code2;

    while(code2 != 3)
    {
        cout << "\n\n\t\t\tSimple Student Management System\n";
        cout << "\t\t\t= = = = = = = = = = = = = = = = \n";
        cout << "\n\nUser Dashboard\n";
        cout << "- - - - - - - -\n\n";
        cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n";
        cout << "[1] Student ID\n\n";
        cout << "[2] Student Phone Number\n\n";
        cout << "[3] Exit\n\n";
        cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
        cout << "\n\nSearch for Student Detail Enter code (1 to 3) : ";
        cin >> code2;

        switch(code2)
        {
        case 1:
            system("cls");
            normalUser.searchWithId();
            break;
        case 2:
            system("cls");
            normalUser.searchWithPhone();
            break;
        case 3:
            system("cls");
            break;
        }

        int option;
        if(code2 != 3)
        {
            cout << "\n\n=> Enter the Choice\n\n";
            cout << "[1] User Menu" << "\t\t[0] Main Menu";
            cout << "\nEnter a number : ";
            cin >> option;

            switch(option)
            {
            case 0:
                system("cls");
                code2 = 3;
                break;
            default:
                system("cls");
                continue;
            }
        }
    }
}


class Admin
{
private:
    char stdFirstName[50], stdLastName[50], fatherName[50], address[200];
    long int stdId, phoneNumber;

public:

    void createStudent()
    {
        cout << "\nEnter Student Id : ";
        cin >> stdId;
        cout << "\nEnter Student First Name : ";
        cin >> stdFirstName;
        cout << "\nEnter Student Last Name : ";
        cin >> stdLastName;
        cout << "\nEnter Father Name : ";
        cin >> fatherName;
        cout << "\nEnter Student Address : ";
        cin >> address;
        cout << "\nEnter Phone Number : ";
        cin >> phoneNumber;
    }

    void showStudent()
    {
        cout << "\nStudent ID : " << stdId << endl;
        cout << "Name : " << stdFirstName << " " << stdLastName << endl;
        cout << "Father Name : " << fatherName << endl;
        cout << "Address : " << address << endl;
        cout << "Phone Number : " << phoneNumber << endl;
    }


    void writeOnFile()
    {
        char statement;
        ofstream studentFile;
        studentFile.open("SSMS.dat", ios::binary | ios::app);

        do
        {
            createStudent();
            studentFile.write(reinterpret_cast<char*>(this), sizeof(*this));

            cout << "\nDo you want to create next .... (y/n) : ";
            cin >> statement;
        }while(statement == 'y');

        cout << "\nStudent data is successfully save.";
        studentFile.close();
    }


    void readOnFile()
    {
        ifstream studentFile;
        studentFile.open("SSMS.dat", ios::binary);

        cout << "\nStudent List";
        cout << "\n- - - - - - -\n\n";
        cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";

        while(!studentFile.eof())
        {
            if(studentFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                showStudent();
                cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
            }

        }

        studentFile.close();
    }


    void editOnFile()
    {
        long int id;
        fstream studentFile;

        cout << "\nEdit Student Datas\n";
        cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
        cout << "\nEnter student ID : ";
        cin >> id;

        studentFile.open("SSMS.dat", ios::binary | ios::out | ios::in);

        while(!studentFile.eof())
        {
            if(studentFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(id == stdId)
                {
                    cout << "\n* Rewrite Update Student Data *\n";
                    createStudent();

                    int position = -1*sizeof(*this);
                    studentFile.seekp(position, ios::cur);
                    studentFile.write(reinterpret_cast<char*>(this), sizeof(*this));

                    cout << "\n\n* * Student data updating is successful......";
                    return;
                }
            }
        }
        cout <<"\nNo record found!";
        studentFile.close();
    }

    void deleteOnFile()
    {
        long int id;
        int flag = 0;
        ifstream studentFile;
        ofstream tempFile;

        studentFile.open("SSMS.dat", ios::binary);
        tempFile.open("TEMP.dat", ios::binary);

        cout << "\nEnter student ID to delete : ";
        cin >> id;

        while(!studentFile.eof())
        {
            if(studentFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(stdId != id)
                {
                    tempFile.write(reinterpret_cast<char*>(this), sizeof(*this));
                }
                else
                    flag = 1;
            }
        }

        studentFile.close();
        tempFile.close();
        remove("SSMS.dat");
        rename("TEMP.dat", "SSMS.dat");
        flag == 1 ? cout << "\nStudent data delete successfully.\n" : cout << "\nNo records found.";
    }


    void searchOnFile()
    {
        ifstream studentFile;
        long int id;
        cout << "\nEnter Student ID : ";
        cin >> id;

        studentFile.open("SSMS.dat", ios::binary);

        while(!studentFile.eof())
        {
            if(studentFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(id == stdId)
                {
                    cout << "\nStudent Information\n";
                    cout << "- - - - - - - - - - - \n";

                    showStudent();
                    return;
                }
            }
        }

        cout << "\nNo records found.\n";
        studentFile.close();
    }

};


void adminPanel()
{
    Admin adminUser;
    system("Color 0A");
    char userName[50];
    long int password;
    int code3;
    cout << "\n\n\t* * To Enter Admin Panel, fill correctly.\n\n";
    cout << "\nEnter Admin user name : ";
    cin >> userName;
    cout << "\nEnter password : ";
    cin >> password;
    while(code3 != 6)
        {
            system("cls");
            cout << "\n\n\t\t\tWelcome Simple Student Management System\n";
            cout << "\t\t\t= = = = = = = = = = = = = = = = = = = = =\n";
            cout << "\n\nAdmin Dashboard\n";
            cout << "- - - - - - - -\n\n";
            cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n";
            cout << "[1] Add New Student\n";
            cout << "[2] Show All Students\n";
            cout << "[3] Edit Student Detail\n";
            cout << "[4] Delete Student\n";
            cout << "[5] Search Student\n";
            cout << "[6] Exit Admin Dashboard\n\n";
            cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
            cout << "\nEnter code (1 to 6) : ";
            cin >> code3;

            switch(code3)
            {
            case 1:
                system("cls");
                adminUser.writeOnFile();
                break;
            case 2:
                system("cls");
                adminUser.readOnFile();
                break;
            case 3:
                system("cls");
                adminUser.editOnFile();
                break;
            case 4:
                system("cls");
                adminUser.deleteOnFile();
                break;
            case 5:
                system("cls");
                adminUser.searchOnFile();
                break;
            case 6:
                system("cls");
                break;
            default:
                continue;
            }

            int choice;
            if(code3 != 6)
            {
                cout << "\n\n\n\n => Enter the choice\n";
                cout << "\n[1] Admin Menu" << "\t\t[0] Main Menu\n";
                cout << "\nEnter a number : ";
                cin >> choice;

                switch(choice)
                {
                case 0:
                    system("cls");
                    code3 = 6;
                    break;
                default:
                    system("cls");
                    continue;

                }
            }

        }

}


int main()
{
    system("cls");
    system("Color 5A");

    cout << endl << endl << endl << endl << endl;
    cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    cout << "\t\t* *                                                                         * *\n";
    cout << "\t\t* *                                                                         * *\n";
    cout << "\t\t* *            Welcome to Simple Student Management System                  * * \n";
    cout << "\t\t* *                                                                         * *\n";
    cout << "\t\t* *                                                                         * *\n";
    cout << "\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n\n\n\n";

    system("pause");

    while(1)
    {
        system("cls");
        system("Color 1A");
        int code1;

        cout << "\n\n\t\t\tSimple Student Management System\n";
        cout << "\t\t\t= = = = = = = = = = = = = = = = \n";
        cout << "\n\n\tMain Menu\n";
        cout << "\t= = = = = \n\n";
        cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n";
        cout << "[1] User\n\n";
        cout << "[2] Admin\n\n";
        cout << "[0] Exit Application\n";
        cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
        cout << "\n\n\nEnter code (0 to 2) : ";
        cin >> code1;

        switch(code1)
        {
        case 1:
            system("cls");
            userPanel();
            break;
        case 2:
            system("cls");
            adminPanel();
            break;
        case 0:
            system("cls");
            cout << "\n\n\n\t\tThanks for using Simple Student Management System.....!!!\n\n\n";
            exit(0);
            break;
        default:
            continue;
        }
    }
    return 0;
}
