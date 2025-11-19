#include "iostream"
using namespace std;
#include "customer_activities.h"

struct customer {
    string acc_num;
    string acc_type;
    string iban;
    string branch_code;
    string name;
    string opening_date;
    string status;
    float balance;
    loanList loans;
    tranStack transactions;
};
