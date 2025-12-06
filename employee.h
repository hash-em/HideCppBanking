#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
using namespace std;




struct Employee {
    string id;
    string name;
    string lastName;
    string address;
    double salary;
    string hireDate;
    string branchCode;
};
struct EmployeeArray {
    Employee* employees;
    int size;
    int capacity;
};
struct LoanRequestNode {
    Loan data;
    LoanRequestNode *next;
};

struct LoanRequestQueue {
    LoanRequestNode *front = nullptr;
    LoanRequestNode *tail = nullptr;
};



#endif
