#ifndef EMPLOYEEARR_H
#define EMPLOYEEARR_H

#include "employee.h"
#include "customer_activities.h"



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
void DeleteCompletedLoans(CompLoan &Clist,loanList &list);
void enqueueRequest(LoanRequestQueue &q, const Loan &req);
bool dequeueRequest(LoanRequestQueue &q, Loan &out);
void processNextRequest(LoanRequestQueue &q, loanList &customerLoans);
void finalizeDay(tranStack &st, TransactionHistory &history);
void displayHistory(const TransactionHistory &hist);
void EmployeeInterface(EmployeeArray *arr);
void displayAccounts(const customerList &list);
void changeStatus(customerList &list, int accNum, const string &newStatus);
void archiveClosedAccounts(customerList &list, ArchiveArray &archive);
void changeLoanStatus(loanList &list,int LoanID,const string &newstatus);

#endif