#include "customer.h"
#include "helpers.h"
#include "fstream"
#include <string>
#include "ctime"
using namespace std;
struct customerNode {
    customer data;
    customerNode * next;
};

struct customerList {
    customerNode *head;
    int size;
};



int submitNewLoan(customer & cust);//DONE//HASH
void displayCustomer(customer cust);//DONE//HASH
int withdraw(customer &cust);//DONE//HASH
int deposit(customer &cust);//DONE//HASH
void viewDay(customer cust);//DONE//HASH
void popTran(tranStack &tr);
void addUndone(tran tr);
int undoLast(customer &cust); //DONE//HASH
void viewLoans(customer cust);//DONE//HASH
customerList newCustomerList();//DONE//HASH
void addTran(tranStack &stack, tran object);//DONE//HASH
void addLoan(loanList &loans, Loan object);//DONE//HASH
void addCustomer(customerList &customers, customer object);//DONE//HASH
tranStack newTranStack();//DONE//HASH
tranStack parseTransStackFromFile();
loanList newLoanList();//DONE//HASH
loanList parseLoansFile();
int userInterface(customer &cust);//DONE//HASH
customerList parseCustomers();//DONE//HASH
void updateData(customer cust);//DONE//HASH
void dumpCustomers(customerList customers);//DONE//HASH
TransactionHistory newHistoryList();
TransactionHistory parsetransactionhistory();
CompLoan newCompLoanList();
CompLoan parseCompLoans();

