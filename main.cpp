// cpp program for student login system and giving access to student's file

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <string.h>
#include <process.h>
#include <iomanip>
#include <stdio.h>

void y_n_checker(char);
void portal_login();
void portal_reg();

// class starts now
class student
{
    // defining instance variables for class
private:
    int u_id;
    char password[30];
    char name[100];
    int marks_ENG, marks_NEP, marks_MATH, marks_PHY, marks_CHEM;
    double average;
    char grade;

public:
    void get_data_set();
    void get_data_log();
    void get_data_after();
    void display_data() const;
    void calculate();
    int retroll()
    {
        return u_id;
    }
    char *retpass()
    {
        return password;
    }
};

void student::get_data_set()
{
    char repassword[60];
    std::cout << "ENTER A USER ID PROVIDED BY THE COLLEGE:\t";
    std::cin >> u_id;
    std::cin.ignore();
    std::cout << "SET A PASSWORD: \t";
    std::cin >> password;
    std::cout << " RE-ENTER THE ABOVE PASSWORD: \t";
    std::cin >> repassword;
    while (strcmp(password, repassword))
    {
        std::cout << " PASSWORDS DO NOT MATCH! ReENTER\n";
        std::cin.ignore();
        std::cout << " SET A PASSWORD: \t";
        std::cin.getline(password, 30);
        std::cout << " RE-enter the above password: \t";
        std::cin.getline(repassword, 60);
        strcmp(password, repassword);
    }
    if (!strcmp(password, repassword))
    {
        std::cout << "\n\n\n\n \t\t\t\tOUR PASSWORD HAS BEEN SET\n\n\n";
        std::cin.ignore();
    }
}
void student::calculate()
{
    average = (marks_CHEM + marks_ENG + marks_MATH + marks_NEP + marks_PHY) / 5;
    if (average >= 90)
    {
        grade = 'A';
    }
    else if (average >= 75)
    {
        grade = 'B';
    }
    else if (average >= 50)
    {
        grade = 'C';
    }
    else
    {
        grade = 'F';
    }
}
void student::get_data_after()
{

    std::cout << " ENTER THE NAME OF STUDENT  :\t";
    std::cin.getline(name, 100);
    std::cout << "CAUTION!!ALL THE MARKS SHOULD BE OUT OF 100 \t \n\n\n";
    std::cin.ignore();
    system("Pause");
    std::cout << " ENTER MARKS FOR ENGLISH : \t";
    std::cin >> marks_ENG;
    std::cout << " ENTER MARKS FOR NEPALI : \t";
    std::cin >> marks_NEP;
    std::cout << " ENTER MARKS FOR MATHEMATICS : \t";
    std::cin >> marks_MATH;
    std::cout << " ENTER MARKS FOR PYSICS : \t";
    std::cin >> marks_PHY;
    std::cout << " ENTER MARKS FOR CHEMISTRY : \t";
    std::cin >> marks_CHEM;
    std::cout << std::endl;
    calculate();
}
// function to fetch data from the user

void student::display_data() const
{
    std::cout << " NAME:\t" << name << std::endl;
    std::cout << " USER ID:\t" << u_id << std::endl;
    std::cout << " THE MARKS FOR ENGLISH IS : \t" << marks_ENG << std::endl;
    std::cout << " THE MARKS FOR NEPALI IS : \t" << marks_NEP << std::endl;
    std::cout << " THE MARKS FOR MATHEMATICS IS : \t" << marks_NEP << std::endl;
    std::cout << " THE MARKS FOR PHYSICS IS : \t" << marks_PHY << std::endl;
    std::cout << " THE MARKS FOR CHEMISTRY IS : \t" << marks_CHEM << std::endl;
    std::cout << " THE AGERAGE IS : \t\t" << average;
    std::cout << " THE GRADE IS : \t\t" << grade;
}

int main()
{
    char ch;
    std::cout << "\n\n\n\t\t\t\t\t\t\tWELCOME TO THE LOGIN/REGESTRATION PORTAL!! \n";
    std::cout << "\n\n\n ARE YOU A NEW USER?\n(Hit Y/y for Yes and N/n for No) \n";
    std::cin >> ch;
    y_n_checker(ch);
    if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n')
    {
        char ch1;
        if (ch == 'Y' || ch == 'y')
        {
            system("cls");
            std::cout << "\n\n\n \t\t\t\t\t\t\tWELCOME TO THE REGESTRATION PORTAL FOR NEW USERS!!! \n";
            portal_reg();
        }
        if (ch == 'N' || ch == 'n')
        {
            int id;
            char pass[60];
            system("cls");
            std::cout << "\n\n\n\t\t\t\t\t\t\tWELCOME TO THE LOGIN PORTAL: \n";
            portal_login();
        }
    }
    return 0;
}
// function to check correct yes/no answer
void y_n_checker(char ch)
{
    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
    {
        system("cls");
        std::cout << "\n Re-enter your choice:\t";
        std::cin >> ch;
    }
}

// functions for login and regestration

void portal_reg()
{
    student stud;
    std::ofstream outfile;
    outfile.open("data.dat", std::ios::app | std::ios::binary);
    stud.get_data_set();
    stud.get_data_after();
    outfile.write((char *)&stud, sizeof(stud));
    outfile.close();
    std::cout << "\n\n\n\n \t\t\t\tYOUR STUDENT PORTAL HAS BEEN CREATED\n";
    std::cin.ignore();
}

void portal_login()
{
    student stud;
    int id;
    char pass[60];
    std::cout << "ENTER YOUR USER ID PROVIDED BY THE COLLEGE:\t";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "ENTER YOUR PASSWORD: \t";
    std::cin >> pass;
    std::ifstream infile;
    infile.open("data.dat", std::ios::in | std::ios::binary);
    infile.read((char *)&stud, sizeof(stud));
    bool check;
    check = false;
    while (!infile.eof())
    {

        if (stud.retroll() == id && !strcmp(stud.retpass(), pass))
        {
            std::cout << "\t\t\t\t\t\tACCESS GRANTED\n\n\n";
            stud.display_data();
            check = true;
        }
        infile.read((char *)&stud, sizeof(stud));
    }
    if (check == false)
    {
        std::cout << "INVALID CREDENTIALS\n RE RUN THE PROGRAM";
    }
    else
    {
        std::cout << "\n\nYOUR DATA HAS BEEN SHOWN";
    }
    infile.close();
    std::cin.ignore();
    std::cin.get();
}
