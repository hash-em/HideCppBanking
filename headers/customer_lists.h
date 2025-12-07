#ifndef CUSTOMER_LISTS_H
#define CUSTOMER_LISTS_H

#include "customer.h"
#include "helpers.h"
#include <string>
#include <fstream>
#include <ctime>

// Note: This header intentionally avoids `using namespace std;`
// and keeps the project's original pointer-based data structures.

struct customerNode {
    customer data;
    customerNode *next;
};

struct customerList {
    customerNode *head;
    int size;
};

// Factory / constructors
customerList newCustomerList();
loanList newLoanList();
tranStack newTranStack();
// Basic in-memory mutators (signatures match implementations)
void addCustomer(customerList &customers, customer object);
void addLoan(loanList &loans, Loan object);
void addTran(tranStack &stack, tran object);

// Customer-facing operations
int userInterface(customer &cust);
int submitNewLoan(customer &cust);
void displayCustomer(customer cust);
int withdraw(customer &cust);
int deposit(customer &cust);
void viewDay(customer cust);
void viewLoans(customer cust);
int undoLast(customer &cust);

// Transaction helpers
void popTran(tranStack &tr);
void addUndone(tran tr);

// Parsing / file IO
customerList parseCustomers();
loanList parseLoansFile();
tranStack parseTransStackFromFile();

// Data persistence
void updateData(customer cust);
void dumpCustomers(customerList customers);


#endif // CUSTOMER_LISTS_H