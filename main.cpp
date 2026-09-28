#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

class Student
{
public:
    char rollNo[30];
    char name[50];
    char fatherName[50];
    char motherName[50];
    char branch[20];
    int semester;
    char mobileNo[15];
    char address[100];

    void getData()
    {
        cout << "\n====================================" << endl;
        cout << "       ENTER STUDENT DETAILS        " << endl;
        cout << "====================================" << endl;

        cin.ignore();
        cout << "Enter Roll Number     : ";
        cin.getline(rollNo, 30);

        cout << "Enter Student Name    : ";
        cin.getline(name, 50);

        cout << "Enter Father's Name   : ";
        cin.getline(fatherName, 50);

        cout << "Enter Mother's Name   : ";
        cin.getline(motherName, 50);

        cout << "Enter Branch          : ";
        cin.getline(branch, 20);

        cout << "Enter Semester        : ";
        cin >> semester;
        cin.ignore();

        cout << "Enter Mobile Number   : ";
        cin.getline(mobileNo, 15);

        cout << "Enter Full Address    : ";
        cin.getline(address, 100);
    }

    void showDataTabular() const
    {
        cout << left << setw(18) << rollNo
             << setw(18) << name
             << setw(12) << branch
             << setw(6) << semester
             << setw(14) << mobileNo
             << setw(20) << address << endl;
    }

    void showDataDetailed() const
    {
        cout << "\n------------------------------------" << endl;
        cout << "          STUDENT PROFILE           " << endl;
        cout << "------------------------------------" << endl;
        cout << "Roll Number   : " << rollNo << endl;
        cout << "Student Name  : " << name << endl;
        cout << "Father's Name : " << fatherName << endl;
        cout << "Mother's Name : " << motherName << endl;
        cout << "Branch        : " << branch << endl;
        cout << "Semester      : " << semester << endl;
        cout << "Mobile Number : " << mobileNo << endl;
        cout << "Address       : " << address << endl;
        cout << "------------------------------------" << endl;
    }
};

void addStudent();
void displayAll();
void searchStudent(const char r[]);
void deleteStudent(const char r[]);

int main()
{
    int choice;
    char roll[30];

    while (true)
    {
        cout << "\n========================================" << endl;
        cout << "     STUDENT MANAGEMENT SYSTEM (C++)    " << endl;
        cout << "========================================" << endl;
        cout << "1. Add New Student Record" << endl;
        cout << "2. Display All Student Records" << endl;
        cout << "3. Search Student by Roll Number" << endl;
        cout << "4. Delete Student Record" << endl;
        cout << "5. Exit" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            cout << "\nEnter Roll Number to Search: ";
            cin >> roll;
            searchStudent(roll);
            break;
        case 4:
            cout << "\nEnter Roll Number to Delete: ";
            cin >> roll;
            deleteStudent(roll);
            break;
        case 5:
            cout << "\nExiting Program. Thank you!" << endl;
            return 0;
        default:
            cout << "\nInvalid choice! Please try again." << endl;
        }
    }
    return 0;
}

void addStudent()
{
    Student st;
    ofstream outFile("students.dat", ios::binary | ios::app);
    st.getData();
    outFile.write(reinterpret_cast<char *>(&st), sizeof(Student));
    outFile.close();
    cout << "\n[SUCCESS] Student Record Added Successfully!" << endl;
}

void displayAll()
{
    Student st;
    ifstream inFile("students.dat", ios::binary);

    if (!inFile)
    {
        cout << "\n[ERROR] No records found! File does not exist." << endl;
        return;
    }

    cout << "\n==========================================================================================" << endl;
    cout << left << setw(18) << "Roll No"
         << setw(18) << "Name"
         << setw(12) << "Branch"
         << setw(6) << "Sem"
         << setw(14) << "Mobile"
         << setw(20) << "Address" << endl;
    cout << "==========================================================================================" << endl;

    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        st.showDataTabular();
    }
    cout << "==========================================================================================" << endl;
    inFile.close();
}

void searchStudent(const char r[])
{
    Student st;
    ifstream inFile("students.dat", ios::binary);
    bool found = false;

    if (!inFile)
    {
        cout << "\n[ERROR] File could not be opened!" << endl;
        return;
    }

    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        if (strcmp(st.rollNo, r) == 0)
        {
            st.showDataDetailed();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found)
    {
        cout << "\n[ERROR] Student with Roll Number '" << r << "' not found!" << endl;
    }
}

void deleteStudent(const char r[])
{
    Student st;
    ifstream inFile("students.dat", ios::binary);

    if (!inFile)
    {
        cout << "\n[ERROR] File could not be opened!" << endl;
        return;
    }

    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        if (strcmp(st.rollNo, r) != 0)
        {
            outFile.write(reinterpret_cast<char *>(&st), sizeof(Student));
        }
        else
        {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
    {
        cout << "\n[SUCCESS] Record Deleted Successfully!" << endl;
    }
    else
    {
        cout << "\n[ERROR] Record Not Found!" << endl;
    }
}