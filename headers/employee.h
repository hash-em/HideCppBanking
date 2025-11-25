#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
using namespace std ;

#include "employee_list.h"

struct Employee {
    int id;
    string firstName;
    string lastName;
    string address;
    double salary;
    string hireDate;
    string branchCode;
    Employee* next;
    Employee() : id(0), next(nullptr) {}
};

struct employeeList {
    Employee* head;
    int size;
};


void initEmployeeSystem();
bool employeeLogin(int& employeeId);
int employeeInterface(int employeeId);
void saveEmployeesToFile();
void loadEmployeesFromFile();

#endif
