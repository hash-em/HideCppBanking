#include "../headers/interface.h"
#include "../headers//statistics.h"
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
            EmployeeArray *arr;
            printLine("EMPLOYEE MANAGEMENT MENU");
            //next_choice = EmployeeInterface(arr);
            return 0;
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


Employee readEmployee()
{
    Employee emp;

    cout << "Enter Employee ID: ";
    cin >> emp.id;

    cout << "Enter First Name: ";
    cin >> emp.name;

    cout << "Enter Address: ";
    cin >> emp.address;

    cout << "Enter Branch Code: ";
    cin >> emp.branchCode;

    cout << "Enter Hire Date (DD/MM/YYYY): ";
    cin >> emp.hireDate;

    cout << "Enter Salary: ";
    cin >> emp.salary;

    return emp;
}



void EmployeeManagement(EmployeeArray *arr)
{
    string EmpM[6] = {
        "Add New Employee",
        "Delete Employee",
        "Modify Employee Information",
        "Display Employees (Alphabetical Order)",
        "Display Employees by Branch",
        "Show Earliest and Latest Recruited Employees"
    };

    int opt;
    printOptions(EmpM, 6);
    cin >> opt;

    if (opt < 1 || opt > 6)
    {
        printLine("Invalid Option");
        return EmployeeManagement(arr);
    }

    switch (opt)
    {
        case 1: {
            Employee emp=readEmployee() ; // you have this function
            addEmployee(*arr, emp);
            break;
        }
        case 2: {
            string id;
            cin >> id;
            deleteEmployee(*arr, id);
            break;
        }
        case 3: {
            string id;
            Employee newData = readEmployee() ;
            cin >> id;
            modifyEmployee(*arr, id, newData);
            break;
        }
        case 4:
            displayEmployeesAlphabetical(*arr);
            break;

        case 5:
            displayEmployeesByBranch(*arr);
            break;

        case 6:
            displayEarliestLatestEmployees(*arr);
            break;
    }
}
void CustomerAccountManagement()
{
    string CusAM[4] = {
        "Add New Customer Account",
        "Display List of Accounts",
        "Change Account Status (Active / Inactive / Closed)",
        "Archive Closed Accounts"
    };

    int opt;
    printOptions(CusAM, 4);
    cin >> opt;

    if (opt < 1 || opt > 4)
    {
        printLine("Invalid Option");
        return CustomerAccountManagement();
    }
    customerList custs=parseCustomers();
    ArchiveArray archive = {};

    switch (opt)
    {
        case 1: {
            customer c ;
            addCustomer(custs, c);
            break;
        }
        case 2:
            displayAccounts(custs);
            break;

        case 3: {
            string  newStatus;
            int accNum;
            cin >> accNum >> newStatus;
            changeStatus(custs, accNum, newStatus);
            break;
        }
        case 4:
            archiveClosedAccounts(custs,archive);
            break;
    }
}

void LoanManagement()
{
    string LoanM[4] = {
        "Display Loans of a Customer",
        "Change Loan Status",
        "Delete Completed Loans (store in completed_loans list)",
        "Process Loan Requests (FIFO Queue)"
    };

    int opt;
    printOptions(LoanM, 4);
    cin >> opt;

    if (opt < 1 || opt > 4)
    {
        printLine("Invalid Option");
        return LoanManagement();
    }

    customerList custs=parseCustomers();
    loanList loans = parseLoansFile();
    CompLoan cloan= parseCompLoans();
    


    switch (opt)
    {
        case 1: {
            customerNode *curr=custs.head;
            string accNum;
            cin >> accNum;
            while(curr){
                if (curr->data.acc_num == accNum){
                    viewLoans(curr->data);
                }
            }
            break;
        }
        case 2: {
            int id;
            string status;
            cin >> id >> status;
            changeLoanStatus(loans, id, status);
            break;
        }
        case 3:
            DeleteCompletedLoans(cloans, loans);
            break;

        case 4:
            //processNextRequest(q, loans);
            break;
    }
}
void TransactionManagement()
{
    string TranM[2] = {
        "View Daily Transaction Log (for all accounts)",
        "Finalize Day (move stack to history list)"
    };

    int opt;
    printOptions(TranM, 2);
    cin >> opt;

    if (opt < 1 || opt > 2)
    {
        printLine("Invalid Option");
        return TransactionManagement();
    }
    TransactionHistory hist = parsetransactionhistory();
    tranStack st = parseTransStackFromFile();
    switch (opt)
    {
        case 1:
            displayHistory(hist);
            break;

        case 2:
            finalizeDay(st,hist);
            break;
    }
}
void StatisticsMenu(EmployeeArray *arr)
{
    customerList custs=parseCustomers();
    string Stat[9] = {
        "Total Number of Loans",
        "Number of Loans by Type",
        "Number of Loans by Status",
        "Active Loans in Date Range",
        "Customer With Highest Number of Loans",
        "Customer With Highest Balance",
        "Customer With Lowest Balance",
        "Total Number of Employees",
        "Employees per Branch"
    };

    int opt;
    printOptions(Stat, 9);
    cin >> opt;

    if (opt < 1 || opt > 9)
    {
        printLine("Invalid Option");
        return StatisticsMenu(arr);
    }

    switch (opt)
    {
        case 1: numberOfLoans(custs); break;
        case 2: { string t; cin>>t; loansType(custs, t);} break;
        case 3: { string s; cin>>s; loansStatus(custs, s);} break;
        case 4: { string a,b; cin>>a>>b; activeLoans(custs,a,b);} break;
        case 5: highestNbLoans(custs); break;
        case 6: highestBalance(custs); break;
        case 7: lowestBalance(custs); break;
        case 8: numberOfEmployees(*arr); break;
        case 9: { string br; cin>>br; numEmployeesByBranch(*arr, br);} break;
    }
}
