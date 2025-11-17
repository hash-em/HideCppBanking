#include "iostream"
using namespace std;

int submitNewLoan();//TODO
int withdraw();//TODO
int deposit();//TODO
int viewDay();//TODO
int undoLast(); //TODO


struct loan{
    string id;
    string type;
    float principal_amount;
    float remain_balance;
    string sart;
    string end;
    string loan_status;
};
struct trans{
    string id;
    string acc_num;
    string type;
    float amount;
    string date;
    bool undone;
};

struct customer {
    string acc_num;
    string acc_type;
    string iban;
    string branch_code;
    string name;
    string opening_date;
    string status;
    float balance;
    Stack *transactions;
    LoanList * loans;
};
