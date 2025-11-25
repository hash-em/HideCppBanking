#ifndef EMPLOYEE_LIST_H
#define EMPLOYEE_LIST_H

#include <string>
using namespace std;
#include "../headers/employee.h"
employeeList newEmployeeList();
void addEmployee(employeeList& list, Employee emp);
bool deleteEmployee(employeeList& list, int id);
bool modifyEmployee(employeeList& list, int id);
void displayEmployeesAlphabetically(const employeeList& list);
void displayEmployeesByBranch(const employeeList& list);
void displayEarliestAndLatest(const employeeList& list);
Employee* findEmployeeById(const employeeList& list, int id);
void freeEmployeeList(employeeList& list);

#endif
