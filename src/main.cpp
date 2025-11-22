#include "../headers/interface.h"
#include "../headers/helpers.h"
#include "../headers/customer_lists.h"
int main(void){

    customerList customers;
    customers = parseCustomers();
    cout << customers.head->next->data.name << endl;

    return 0;
    //TODO

}
