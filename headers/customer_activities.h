#include "iostream"
using namespace std;

struct tran{
    string id;
    string acc_num;
    string type;
    float amount;
    string date;
    bool undone;
};

struct Loan{
    string id;
    string type;
    float amount;
    float remain_balance;
    string start;
    string end;
    string status;
};

struct tranStack {
    tran * last;
    int size;
};
struct loanList {
    Loan loan ;
    Loan * prev;
    Loan * next;
};
