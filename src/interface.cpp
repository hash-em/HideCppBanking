#include "../headers/interface.h"
#include "../headers/helpers.h"
#include "../headers/employee_list.h"
#include <string>
#include <iostream>



int ini()
{
    clearScreen();
    printLine("Welcome to Cpp Banking");
    std::string options[3] = { "Customer Login","Employee login","Exit" };
    printOptions(options, 3);
    int choice, next_choice;
    std::cin >> choice;
    switch (choice) {
    case 1: {
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
    case 2: {
        while (true) {
            clearScreen();
            printLine("Employee Login");
            std::string empid;
            std::cout << "Employee ID: ";
            std::cin >> empid;
            EmployeeArray arr = loadEmployeesFromFile("../data/employees.json");
            bool found = false;
            Employee emp;
            for (int i = 0; i < arr.size; ++i) {
                if (arr.employees[i].id == empid) {
                    emp = arr.employees[i];
                    found = true;
                    break;
                }
            }
            if (!found) {
                printLine("Invalid Employee ID");
                continue;
            }
            int next_choice = employeeInterface(emp);
            if (next_choice == 67) logout();
            break;
        }
        return 0;
    }
    case 3: clearScreen(); return 0;
    }
    return choice;
}
customer customer_login()
{
    std::string acc_num, branch_code;
    printLine("Input Acc_num");
    std::cin >> acc_num;
    printLine("Input branch_code");
    std::cin >> branch_code;
    clearScreen();
    bool found = false;
    customerList custs = parseCustomers();
    customerNode* curr = custs.head;
    customer empty = { "0","0","0","0","0","0","0",0.0,newLoanList(),newTranStack() };
    while (curr && !found)
    {
        if (curr->data.acc_num == acc_num) {
            found = true;
            if (curr->data.branch_code == branch_code) {
                printLine("Welcome " + curr->data.name);
                return curr->data;
            }
            else {
                printLine("Invalid Branch Code");
                return empty;
            }
        }
        curr = curr->next;
    }
    printLine("Invalid Acc_num");
    return empty;
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
