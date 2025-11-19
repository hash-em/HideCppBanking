#include "../headers/helpers.h"
#include "../headers/customer_lists.h"
int userInterface()
{
    clearScreen();
    // TODO
    return 1;
}

void addCustomer(customerList customers , customer cust)
{
    customerNode * new_c = new customerNode{cust,customers.head};
    customers.head = new_c;


};
void addLoan(loanList loans , Loan loan);
void addTran(tranStack trans , tran transaction);

int submitNewLoan()
{
    //TODO (do addLoan(...,...) then write loan in files) for HASHEM
    return 1;
};

int withdraw(){
    //TODO
    return 1;
}

int deposit(){
    //TODO
    return 1;
}

int viewDay(){
    // TODO
    return 1;
}

int undoLast(){
    // TODO
    return 1;
}
