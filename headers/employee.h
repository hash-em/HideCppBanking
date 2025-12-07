#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

// Forward declarations for types that are defined elsewhere but referenced
// by employee-related data structures in this header.
struct Loan; // declared in customer_activities.h

// Employee core structure
struct Employee {
    std::string id;
    std::string name;
    std::string lastName;
    std::string address;
    double salary;
    std::string hireDate;
    std::string branchCode;
};

// Simple dynamic array container for Employee objects (keeps original
// methodology: raw pointer + size/capacity; avoids introducing STL containers)
struct EmployeeArray {
    Employee* employees = nullptr;
    int size = 0;
    int capacity = 0;
};

// Node and queue types for loan requests (used by employee-side logic).
// These intentionally mirror the singly-linked queue approach used elsewhere.
struct LoanRequestNode {
    Loan* data;            // pointer to a Loan (Loan is defined in customer_activities.h)
    LoanRequestNode* next;
};

struct LoanRequestQueue {
    LoanRequestNode* front = nullptr;
    LoanRequestNode* tail = nullptr;
};

#endif // EMPLOYEE_H