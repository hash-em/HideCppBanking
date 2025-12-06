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
    string acc_num;
    string type;
    float amount;
    float remain_balance;
    float interest;
    string start;
    string end;
    string status;
};


struct tranNode
{
    tran data;
    tranNode *prev;
};

struct tranStack {
    tranNode * last;
    int size;
};

struct LoanNode {
    Loan data;
    LoanNode * prev;
    LoanNode * next;
};
struct CLoanNode{
    Loan data;
    CLoanNode * next;
};

struct HistoryNode {
    tran data;
    HistoryNode *next;
};
struct loanList {
    LoanNode * head ;
    int size;
};
struct CompLoan{
    CLoanNode * head;
    int size;
};
struct TransactionHistory {
    HistoryNode *head = nullptr;  
    int size;
};
struct ArchiveArray {
    customer *arr;
    int size;
    int capacity;
};


