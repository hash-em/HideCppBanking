#include "customer.h"

struct customerNode {
    customer data;
    customerNode * next;
};

struct customerList {
    customerNode *head;
    int size;
};



int submitNewLoan();//TODO
int withdraw();//TODO
int deposit();//TODO
int viewDay();//TODO
int undoLast(); //TODO
customerList newCustomerList();
void addTran(tranStack &stack, tran object);
void addLoan(loanList &loans, Loan object);
void addCustomer(customerList &customers, customer object);
customerList parseCustomers();
