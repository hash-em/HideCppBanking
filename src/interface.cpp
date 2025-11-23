#include "../headers/interface.h"
#include "../headers/helpers.h"
using namespace std;


int ini()
{
    clearScreen();
    printLine("Welcome to Cpp Banking");
    string options[3] = {"Customer Login","Employee login","Exit"};
    printOptions(options, 3);
    int choice,next_choice;
    cin >> choice;
    switch (choice) {
        case 1:{
            customer cust = customer_login();
            next_choice = userInterface(cust);
            while (next_choice == 8)
            {
                printLine("Invalid Input");
                customer cust = customer_login();
                next_choice = userInterface(cust);
            }
            if (next_choice == 67) logout();
            return 0;
        };
        case 2 : {
            cerr << "Not implemented";
            return 1;
        }
        case 3 : return 0;
    }
    return choice;
}
customer customer_login()
{
    string acc_num,branch_code;
    printLine("Input Acc_num");
    cin >> acc_num;
    printLine("Input branch_code");
    cin >> branch_code;
    clearScreen();
    bool found = false;
    customerList custs = parseCustomers();
    customerNode *curr = custs.head;
    while(curr && !found)
    {
        if (curr->data.acc_num == acc_num) {
            found = true;
            if (curr->data.branch_code == branch_code) {
                printLine("Welcome "+curr->data.name);
                return curr->data;
            }
            else {
                printLine("Invalid Branch Code");
                return customer{"0","0","0","0","0","0","0",0.0,newLoanList(),newTranStack()};
            }
        }
        curr = curr->next;
    }
    printLine("Invalid Acc_num");
    return customer{"0","0","0","0","0","0","0",0.0,newLoanList(),newTranStack()};
}
int logout()
{
    clearScreen();
    ini();
    return 0;
}

int createAccount()
{
    clearScreen();

    //TODO
    return 1;
}
