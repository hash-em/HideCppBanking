#ifndef EMPLOYEE_LIST_H
#define EMPLOYEE_LIST_H

#include <string>
#include "employee.h"
using namespace std;
EmployeeArray createEmployeeArray();
EmployeeArray loadEmployeesFromFile(const string& filename);
void saveEmployeesToFile(const EmployeeArray& arr, const string& filename);
void resizeEmployeeArray(EmployeeArray& arr);


/* ===============================
   EMPLOYEE CRUD OPERATIONS
   =============================== */

int addEmployee(EmployeeArray& arr, const Employee& emp);
bool deleteEmployee(EmployeeArray& arr, const string& id);
bool modifyEmployee(EmployeeArray& arr, const string& id, const Employee& newData);


/* ===============================
   EMPLOYEE DISPLAY FUNCTIONS
   =============================== */

void displayEmployeesAlphabetical(const EmployeeArray& arr);
void displayEmployeesByBranch(const EmployeeArray& arr);
void displayEarliestLatestEmployees(const EmployeeArray& arr);


/* ===============================
   EMPLOYEE MENU & INTERFACE
   =============================== */

int employeeInterface(const Employee& emp);

// menus (all required by employee.cpp)
int addEmployeeMenu();
void deleteEmployeeMenu();
void modifyEmployeeMenu();

void addAccountMenu();
void displayAccountsMenu();
void changeAccountStatusMenu();
void archiveClosedAccountsMenu();

void displayCustomerLoansMenu();
void changeLoanStatusMenu();

#endif