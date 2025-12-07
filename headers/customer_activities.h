#ifndef CUSTOMER_ACTIVITIES_H
#define CUSTOMER_ACTIVITIES_H

#include <string>

// Forward declare customer to avoid circular includes between customer.h and this header
struct customer;

struct tran{
    std::string id;
    std::string acc_num;
    std::string type;
    float amount;
    std::string date;
    bool undone;
};

struct Loan{
    std::string id;
    std::string acc_num;
    std::string type;
    float amount;
    float remain_balance;
    float interest;
    std::string start;
    std::string end;
    std::string status;
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
struct loanList {
    LoanNode * head ;
    int size;
};

/* Simple ArchiveArray used to store archived customers while preserving
 * the original methodology of raw pointers and capacity/size fields.
 * The array element type is `customer` (forward-declared above).
 */
struct ArchiveArray {
    customer *arr;
    int size;
    int capacity;
};

#endif // CUSTOMER_ACTIVITIES_H
