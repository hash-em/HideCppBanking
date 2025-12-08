#ifndef EMPLOYEEARR_H
#define EMPLOYEEARR_H

#include <string>
#include "employee.h"
#include "customer_activities.h"
#include "customer_lists.h"

/*
 * employeearr.h
 *
 * Declarations for employee-related data structures and operations.
 * This header is intended to align the function signatures used across
 * the project with the existing source implementations while preserving
 * the project's pointer-based data structures (no STL containers).
 *
 * Ensure this header remains consistent with the implementations in
 * src/employee.cpp and other .cpp files that operate on these types.
 */

/* --- Employee array helpers (raw-pointer dynamic array) --- */

/* Create an empty EmployeeArray with an initial capacity. */
EmployeeArray createEmployeeArray();

/* Resize the employee array (grow capacity). */
void resizeEmployeeArray(EmployeeArray& arr);

/* Add, delete, modify employee records in the EmployeeArray. */
int addEmployee(EmployeeArray& arr, const Employee& emp);
bool deleteEmployee(EmployeeArray& arr, const std::string& id);
bool modifyEmployee(EmployeeArray& arr, const std::string& id, const Employee& newData);

/* Query helpers */
int numberOfEmployees(const EmployeeArray& arr);
int numEmployeesByBranch(EmployeeArray& arr, int branch);

/* Persistence */
void saveEmployeesToFile(const EmployeeArray& arr, const std::string& filename);
EmployeeArray loadEmployeesFromFile(const std::string& filename);

/* --- Employee UI entry points --- */

/* High-level employee menu driven by an EmployeeArray pointer (interactive). */
void EmployeeInterface(EmployeeArray* arr);

/* Older-style interface used in some source files (kept for compatibility)
 * linkage surprises if either form is referenced.
 */
int employeeInterface(const Employee& emp);
void EmployeeInterfaceMenu(EmployeeArray* arr); /* alias-style declaration */

/*
 * Employee menu function stubs used by the interactive Employee UI.
 * These are declarations only (matching the project's existing methodology).
 * Implementations are simple stubs / thin wrappers and will be provided
 * in source files where the UI logic lives.
 */
int addEmployeeMenu();
void deleteEmployeeMenu();
void modifyEmployeeMenu();
void showEarliestLatest();

void addAccountMenu();
void displayAccountsMenu();
void changeAccountStatusMenu();
void archiveClosedAccountsMenu();

void displayCustomerLoansMenu();
void changeLoanStatusMenu();

/* --- Loan & request queue operations --- */

/* Move completed loans from a loanList into a CompLoan collection. */
void DeleteCompletedLoans(CompLoan &completedList, loanList &list);

/* Loan request queue operations (singly-linked queue of Loan requests). */
void enqueueRequest(LoanRequestQueue &q, const Loan &req);
bool dequeueRequest(LoanRequestQueue &q, Loan &out);

/* Accept/decline and insert processed requests into a customer's loan list. */
void processNextRequest(LoanRequestQueue &q, loanList &customerLoans);

/* --- Transaction & history helpers --- */

/* Finalize a day's transactions: move all transactions from tranStack into TransactionHistory. */
void finalizeDay(tranStack &st, TransactionHistory &history);

/* Print or otherwise display transaction history. */
void displayHistory(const TransactionHistory &hist);

/* Add a transaction into a permanent history list. */
void addHistoryTransaction(TransactionHistory &hist, const tran &t);

/* --- Account & loan management helper functions --- */

/* Print or display all customer accounts contained in a customerList. */
void displayAccounts(const customerList &list);

/* Change status of a customer account (identified by account number string). */
void changeStatus(customerList &list, const std::string &accNum, const std::string &newStatus);

/* Archive closed accounts into an ArchiveArray and remove them from the active list. */
void archiveClosedAccounts(customerList &list, ArchiveArray &archive);

/* Change the status of a loan identified by its ID string. */
void changeLoanStatus(loanList &list, const std::string &LoanID, const std::string &newstatus);

#endif // EMPLOYEEARR_H
