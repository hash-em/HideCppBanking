#ifndef EMPLOYEEARR_H
#define EMPLOYEEARR_H

#include "employee.h"

struct EmployeeArray {
    Employee* employees;
    int size;
    int capacity;
};

// Employee management functions
EmployeeArray createEmployeeArray();
void addEmployee(EmployeeArray& arr, const Employee& emp);
bool deleteEmployee(EmployeeArray& arr, const string& id);
bool modifyEmployee(EmployeeArray& arr, const string& id, const Employee& newData);
void displayEmployeesAlphabetical(const EmployeeArray& arr);
void displayEmployeesByBranch(const EmployeeArray& arr);
void displayEarliestLatestEmployees(const EmployeeArray& arr);
void saveEmployeesToFile(const EmployeeArray& arr, const string& filename);
EmployeeArray loadEmployeesFromFile(const string& filename);

#endif