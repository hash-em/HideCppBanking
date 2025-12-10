#include "../headers/employee.h"
#include "../headers/helpers.h"
#include "../headers/customer_lists.h"
#include "../headers/statstics.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>



void displayEmployeesAlphabetical(const EmployeeArray& arr);
void displayEmployeesByBranch(const EmployeeArray& arr);
void displayEarliestLatestEmployees(const EmployeeArray& arr);



static void emp_skipWhitespace(const char*& c) {
    while (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r') c++;
}

static std::string emp_parseKey(const char*& c) {
    std::string key;
    if (*c != '\"') return key;
    c++; 
    while (*c && *c != '"') {
        key += *c;
        c++;
    }
    if (*c == '"') c++; 
    return key;
}

static std::string emp_parseStringValue(const char*& c) {
    std::string value;
    emp_skipWhitespace(c);
    if (*c != '\"') return value;
    c++; // skip opening quote
    while (*c && *c != '"') {
        // handle simple escape of \" (not a full JSON escape implementation)
        if (*c == '\\' && *(c + 1) == '"') { c++; value += '"'; c++; continue; }
        value += *c;
        c++;
    }
    if (*c == '"') c++; // skip closing quote
    return value;
#include "../headers/employee.h"
#include "../headers/helpers.h"
#include "../headers/customer_lists.h"
#include "../headers/statstics.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


void displayEmployeesAlphabetical(const EmployeeArray& arr);
void displayEmployeesByBranch(const EmployeeArray& arr);
void displayEarliestLatestEmployees(const EmployeeArray& arr);



static void emp_skipWhitespace(const char*& c) {
    while (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r') c++;
}

static std::string emp_parseKey(const char*& c) {
    std::string key;
    if (*c != '"') return key;
    c++;
    while (*c && *c != '"') {
        key += *c;
        c++;
    }
    if (*c == '"') c++;
    return key;
}

static std::string emp_parseStringValue(const char*& c) {
    std::string value;
    emp_skipWhitespace(c);
    if (*c != '"') return value;
    c++;
    while (*c && *c != '"') {
        if (*c == '\\' && *(c + 1) == '"') { c++; value += '"'; c++; continue; }
        value += *c;
        c++;
    }
    if (*c == '"') c++;
    return value;
}

static double emp_parseFloatValue(const char*& c) {
    emp_skipWhitespace(c);
    std::string num;
    while (*c && ((*c >= '0' && *c <= '9') || *c == '-' || *c == '+' || *c == '.' || *c == 'e' || *c == 'E')) {
        num += *c;
        c++;
    }
    if (num.empty()) return 0.0;
    try {
        return std::stod(num);
    }
    catch (...) {
        return 0.0;
    }
}

static Employee emp_parseEmployeeObject(const char*& c) {
    Employee emp;
    emp.id = "";
    emp.name = "";
    emp.lastName = "";
    emp.address = "";
    emp.salary = 0.0;
    emp.hireDate = "";
    emp.branchCode = "";

    emp_skipWhitespace(c);
    if (*c != '{') {
        while (*c && *c != '{') c++;
        if (*c != '{') return emp;
    }
    c++;

    while (*c && *c != '}') {
        emp_skipWhitespace(c);
        if (*c == '"') {
            std::string key = emp_parseKey(c);
            emp_skipWhitespace(c);
            if (*c == ':') c++;
            emp_skipWhitespace(c);

            if (key == "id") {
                emp.id = emp_parseStringValue(c);
            }
            else if (key == "name") {
                emp.name = emp_parseStringValue(c);
            }
            else if (key == "lastName" || key == "last_name" || key == "lname") {
                emp.lastName = emp_parseStringValue(c);
            }
            else if (key == "address") {
                emp.address = emp_parseStringValue(c);
            }
            else if (key == "salary") {
                emp.salary = emp_parseFloatValue(c);
            }
            else if (key == "hireDate" || key == "hire_date") {
                emp.hireDate = emp_parseStringValue(c);
            }
            else if (key == "branchCode" || key == "branch_code") {
                emp.branchCode = emp_parseStringValue(c);
            }
            else {
                emp_skipWhitespace(c);
                if (*c == '"') { (void)emp_parseStringValue(c); }
                else if ((*c >= '0' && *c <= '9') || *c == '-') { (void)emp_parseFloatValue(c); }
                else if (*c == '{') {
                    int depth = 0;
                    while (*c) {
                        if (*c == '{') depth++;
                        else if (*c == '}') {
                            depth--;
                            if (depth == 0) { c++; break; }
                        }
                        c++;
                    }
                }
                else if (*c == '[') {
                    int depth = 0;
                    while (*c) {
                        if (*c == '[') depth++;
                        else if (*c == ']') {
                            depth--;
                            if (depth == 0) { c++; break; }
                        }
                        c++;
                    }
                }
                else {
                    while (*c && *c != ',' && *c != '}') c++;
                }
            }
        }
        else {
            c++;
        }

        emp_skipWhitespace(c);
        if (*c == ',') c++;
    }

    if (*c == '}') c++;
    return emp;
}

EmployeeArray createEmployeeArray() {
    EmployeeArray arr;
    arr.capacity = 10;
    arr.size = 0;
    arr.employees = new Employee[arr.capacity];
    return arr;
}
int employeeInterface(const Employee& emp)
{
    printLine("Employee Portal - " + emp.name + " " + emp.lastName);

    string options[15] = {
        "Add Employee",
        "Delete Employee",
        "Modify Employee",
        "Display Employees (Alphabetical)",
        "Display Employees by Branch",
        "Earliest & Latest Recruited",
        "Add Customer Account",
        "Display Accounts",
        "Change Account Status",
        "Archive Closed Accounts",
        "Display Loans for Customer",
        "View Pending Loans",
        "Change Loan Status",
        "statsics","Logout"
    };

    printOptions(options, 15);

    EmployeeArray arr = loadEmployeesFromFile("../data/employees.json");
    int choice;
    cin >> choice;

    if (choice < 1 || choice > 15)
    {
        printLine("Invalid choice");
        return employeeInterface(emp);
    }
    int res;
    switch (choice)
    {
    case 1:
        do {
            res = addEmployeeMenu();
        } while (res == 8); break;
    case 2: deleteEmployeeMenu(); break;
    case 3: modifyEmployeeMenu(); break;
    case 4: displayEmployeesAlphabetical(arr); break;
    case 5: displayEmployeesByBranch(arr); break;
    case 6: displayEarliestLatestEmployees(arr); break;
    case 7: addAccountMenu(); break;
    case 8: displayAccountsMenu(); break;
    case 9: changeAccountStatusMenu(); break;
    case 10: archiveClosedAccountsMenu(); break;
    case 11: displayCustomerLoansMenu(); break;
    case 12: pendingLoansMenu(); break;
    case 13: changeLoanStatusMenu(); break;
    case 14: stats();break ;
    case 15: return 67;
    }
    return employeeInterface(emp);
}

int addEmployeeMenu() {
    clearScreen();
    printLine("Add New Employee");
    Employee emp;
    std::cout << "ID: ";
    std::cin >> emp.id;
    std::cout << "First name: ";
    std::cin >> emp.name;
    std::cout << "Last name: ";
    std::cin >> emp.lastName;
    std::cin.ignore();
    std::cout << "Address: ";
    std::getline(std::cin, emp.address);
    std::cout << "Salary: ";
    std::cin >> emp.salary;
    std::cout << "Branch code: ";
    std::cin >> emp.branchCode;
    emp.hireDate = DateNow();

    EmployeeArray arr = loadEmployeesFromFile("../data/employees.json");
    return addEmployee(arr, emp);
    saveEmployeesToFile(arr, "../data/employees.json");
}

void deleteEmployeeMenu() {
    clearScreen();
    printLine("Delete Employee");
    std::string id;
    std::cout << "Enter employee ID to delete: ";
    std::cin >> id;
    EmployeeArray arr = loadEmployeesFromFile("../data/employees.json");
    if (deleteEmployee(arr, id)) {
        saveEmployeesToFile(arr, "../data/employees.json");
    }
    else {
        std::cout << "Delete failed or employee not found." << std::endl;
    }
}

void modifyEmployeeMenu() {
    clearScreen();
    printLine("Modify Employee");
    std::string id;
    std::cout << "Enter employee ID to modify: ";
    std::cin >> id;

    EmployeeArray arr = loadEmployeesFromFile("../data/employees.json");
    int idx = -1;
    for (int i = 0; i < arr.size; ++i) {
        if (arr.employees[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        std::cout << "Employee not found." << std::endl;
        return;
    }

    Employee updated = arr.employees[idx];
    std::cout << "Leave input empty to keep current value." << std::endl;
    std::cin.ignore();

    std::string input;
    std::cout << "First name (" << updated.name << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) updated.name = input;

    std::cout << "Last name (" << updated.lastName << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) updated.lastName = input;

    std::cout << "Address (" << updated.address << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) updated.address = input;

    std::cout << "Salary (" << updated.salary << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) updated.salary = std::stod(input);

    std::cout << "Branch code (" << updated.branchCode << "): ";
    std::getline(std::cin, input);
    if (!input.empty()) updated.branchCode = input;

    modifyEmployee(arr, id, updated);
    saveEmployeesToFile(arr, "../data/employees.json");
}

void addAccountMenu() {
    clearScreen();
    printLine("Add Customer Account (Employee Action)");
    customer cust;
    std::cout << "Account number: ";
    std::cin >> cust.acc_num;
    std::cout << "Account type: ";
    std::cin >> cust.acc_type;
    std::cout << "IBAN: ";
    std::cin >> cust.iban;
    std::cout << "Branch code: ";
    std::cin >> cust.branch_code;
    std::cin.ignore();
    std::cout << "Customer name: ";
    std::getline(std::cin, cust.name);
    cust.opening_date = DateNow();
    cust.status = "active";
    std::cout << "Initial balance: ";
    std::cin >> cust.balance;
    cust.loans = newLoanList();
    cust.transactions = newTranStack();

    customerList customers = parseCustomers();
    addCustomer(customers, cust);
    dumpCustomers(customers);
    std::cout << "Customer account created and saved." << std::endl;
}

void displayAccountsMenu() {
    clearScreen();
    printLine("Display Accounts");
    customerList customers = parseCustomers();
    customerNode* curr = customers.head;
    if (!curr) {
        std::cout << "No accounts found." << std::endl;
        return;
    }
    while (curr) {
        std::cout << "Acc#: " << curr->data.acc_num
            << " | Name: " << curr->data.name
            << " | Branch: " << curr->data.branch_code
            << " | Status: " << curr->data.status
            << " | Balance: " << curr->data.balance
            << std::endl;
        curr = curr->next;
    }
}

void changeAccountStatusMenu() {
    clearScreen();
    printLine("Change Account Status");
    std::string accnum, newStatus;
    std::cout << "Account number: ";
    std::cin >> accnum;
    std::cout << "New status (active/closed/suspended): ";
    std::cin >> newStatus;

    customerList customers = parseCustomers();
    customerNode* curr = customers.head;
    bool found = false;
    while (curr) {
        if (curr->data.acc_num == accnum) {
            curr->data.status = newStatus;
            found = true;
            break;
        }
        curr = curr->next;
    }
    if (found) {
        dumpCustomers(customers);
        std::cout << "Account status updated." << std::endl;
    }
    else {
        std::cout << "Account not found." << std::endl;
    }
}

void archiveClosedAccountsMenu() {
    clearScreen();
    printLine("Archive Closed Accounts");
    customerList customers = parseCustomers();
    customerList kept = newCustomerList();
    customerNode* curr = customers.head;
    bool anyArchived = false;

    while (curr) {
        if (curr->data.status == "closed") {
            anyArchived = true;
        }
        else {
            addCustomer(kept, curr->data);
        }
        curr = curr->next;
    }

    if (anyArchived) {
        dumpCustomers(kept);
        std::cout << "Closed accounts archived (removed from active list)." << std::endl;
    }
    else {
        std::cout << "No closed accounts found to archive." << std::endl;
    }
}

void displayCustomerLoansMenu() {
    clearScreen();
    printLine("Display Customer Loans");
    std::string accnum;
    std::cout << "Account number: ";
    std::cin >> accnum;
    customerList customers = parseCustomers();
    customerNode* curr = customers.head;
    while (curr) {
        if (curr->data.acc_num == accnum) {
            viewLoans(curr->data);
            return;
        }
        curr = curr->next;
    }
    std::cout << "Account not found." << std::endl;
}

void changeLoanStatusMenu() {
    clearScreen();
    printLine("Change Loan Status");
    std::string accnum, loanid, newStatus;
    std::cout << "Account number: ";
    std::cin >> accnum;
    std::cout << "Loan ID: ";
    std::cin >> loanid;
    std::cout << "New status: ";
    std::cin >> newStatus;

    customerList customers = parseCustomers();
    customerNode* curr = customers.head;
    bool changed = false;
    while (curr) {
        if (curr->data.acc_num == accnum) {
            LoanNode* ln = curr->data.loans.head;
            while (ln) {
                if (ln->data.id == loanid) {
                    ln->data.status = newStatus;
                    changed = true;
                    break;
                }
                ln = ln->next;
            }
            if (changed) {
                dumpCustomers(customers);
                std::cout << "Loan status updated." << std::endl;
            }
            else {
                std::cout << "Loan not found for that account." << std::endl;
            }
            return;
        }
        curr = curr->next;
    }
    std::cout << "Account not found." << std::endl;
}

void resizeEmployeeArray(EmployeeArray& arr) {
    int newCapacity = arr.capacity * 2;
    Employee* newEmployees = new Employee[newCapacity];
    for (int i = 0; i < arr.size; i++) {
        newEmployees[i] = arr.employees[i];
    }
    delete[] arr.employees;
    arr.employees = newEmployees;
    arr.capacity = newCapacity;
}

int addEmployee(EmployeeArray& arr, const Employee& emp) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.employees[i].id == emp.id) {
            printLine("Error: Employee ID already exists!");
            return 8;
        }
    }

    if (arr.size >= arr.capacity) {
        resizeEmployeeArray(arr);
    }

    arr.employees[arr.size] = emp;
    arr.size++;
    return 0;
}

bool deleteEmployee(EmployeeArray& arr, const string& id) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.employees[i].id == id) {
            for (int j = i; j < arr.size - 1; j++) {
                arr.employees[j] = arr.employees[j + 1];
            }
            arr.size--;
            cout << "Employee deleted successfully!" << endl;
            return true;
        }
    }
    cout << "Error: Employee not found!" << endl;
    return false;
}

bool modifyEmployee(EmployeeArray& arr, const string& id, const Employee& newData) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.employees[i].id == id) {
            arr.employees[i] = newData;
            cout << "Employee modified successfully!" << endl;
            return true;
        }
    }
    cout << "Error: Employee not found!" << endl;
    return false;
}

void displayEmployeesAlphabetical(const EmployeeArray& arr) {
    clearScreen();
    if (arr.size == 0) {
        cout << "No employees to display!" << endl;
        return;
    }

    Employee* temp = new Employee[arr.size];
    for (int i = 0; i < arr.size; i++) {
        temp[i] = arr.employees[i];
    }

    for (int i = 0; i < arr.size - 1; i++) {
        for (int j = 0; j < arr.size - i - 1; j++) {
            if (temp[j].lastName > temp[j + 1].lastName) {
                Employee tempEmp = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = tempEmp;
            }
        }
    }

    cout << "Employees sorted by last name:" << endl;
    for (int i = 0; i < arr.size; i++) {
        cout << "ID: " << temp[i].id
            << ", Name: " << temp[i].name
            << " " << temp[i].lastName
            << ", Branch: " << temp[i].branchCode << endl;
    }

    delete[] temp;
}

void displayEmployeesByBranch(const EmployeeArray& arr) {
    clearScreen();
    if (arr.size == 0) {
        cout << "No employees to display!" << endl;
        return;
    }

    cout << "Employees grouped by branch:" << endl;

    for (int i = 0; i < arr.size; i++) {
        string currentBranch = arr.employees[i].branchCode;
        bool branchPrinted = false;

        for (int j = 0; j < i; j++) {
            if (arr.employees[j].branchCode == currentBranch) {
                branchPrinted = true;
                break;
            }
        }

        if (!branchPrinted) {
            cout << "\nBranch " << currentBranch << ":" << endl;
            for (int k = 0; k < arr.size; k++) {
                if (arr.employees[k].branchCode == currentBranch) {
                    cout << "  - " << arr.employees[k].name
                        << " " << arr.employees[k].lastName
                        << " (ID: " << arr.employees[k].id << ")" << endl;
                }
            }
        }
    }
}

void displayEarliestLatestEmployees(const EmployeeArray& arr) {
    clearScreen();
    if (arr.size == 0) {
        cout << "No employees to display!" << endl;
        return;
    }

    int earliestIndex = 0;
    int latestIndex = 0;

    for (int i = 1; i < arr.size; i++) {
        if (arr.employees[i].hireDate < arr.employees[earliestIndex].hireDate) {
            earliestIndex = i;
        }
        if (arr.employees[i].hireDate > arr.employees[latestIndex].hireDate) {
            latestIndex = i;
        }
    }

    cout << "Earliest recruited employee:" << endl;
    cout << "ID: " << arr.employees[earliestIndex].id
        << ", Name: " << arr.employees[earliestIndex].name
        << " " << arr.employees[earliestIndex].lastName
        << ", Hire Date: " << arr.employees[earliestIndex].hireDate << endl;

    cout << "Most recently recruited employee:" << endl;
    cout << "ID: " << arr.employees[latestIndex].id
        << ", Name: " << arr.employees[latestIndex].name
        << " " << arr.employees[latestIndex].lastName
        << ", Hire Date: " << arr.employees[latestIndex].hireDate << endl;
}
void pendingLoansMenu() {
    clearScreen();
    printLine("Pending Loans Menu");

    loanList pendingLoans = parseLoansFile();

    if (pendingLoans.size == 0) {
        std::cout << "No pending loans to process." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    std::cout << "\n=== Pending Loan Requests ===" << std::endl;
    LoanNode* curr = pendingLoans.head;
    int loanNum = 1;

    while (curr) {
        std::cout << "\n" << loanNum << ". Loan ID: " << curr->data.id 
                  << " | Account: " << curr->data.acc_num
                  << " | Type: " << curr->data.type
                  << " | Amount: " << curr->data.amount
                  << " | Interest: " << curr->data.interest << "%" << std::endl;
        curr = curr->next;
        loanNum++;
    }

    std::cout << "\n0. Exit" << std::endl;
    std::cout << "Select loan number to process (or 0 to exit): ";
    int choice;
    std::cin >> choice;

    if (choice == 0) {
        return;
    }

    if (choice < 1 || choice > pendingLoans.size) {
        std::cout << "Invalid choice." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return;
    }

    curr = pendingLoans.head;
    int count = 1;
    while (curr && count != choice) {
        curr = curr->next;
        count++;
    }

    if (!curr) {
        std::cout << "Loan not found." << std::endl;
        return;
    }

    Loan selectedLoan = curr->data;

    std::cout << "\n=== Loan Details ===" << std::endl;
    std::cout << "ID: " << selectedLoan.id << std::endl;
    std::cout << "Account: " << selectedLoan.acc_num << std::endl;
    std::cout << "Type: " << selectedLoan.type << std::endl;
    std::cout << "Amount: " << selectedLoan.amount << std::endl;
    std::cout << "Interest Rate: " << selectedLoan.interest << "%" << std::endl;
    std::cout << "Start Date: " << selectedLoan.start << std::endl;
    std::cout << "End Date: " << selectedLoan.end << std::endl;

    std::cout << "\nAccept loan? (1=Yes, 0=No): ";
    int approval;
    std::cin >> approval;

    if (approval == 1) {
        selectedLoan.status = "active";
        selectedLoan.start = DateNow();

        customerList customers = parseCustomers();
        customerNode* custNode = customers.head;
        bool found = false;

        while (custNode) {
            if (custNode->data.acc_num == selectedLoan.acc_num) {
                addLoan(custNode->data.loans, selectedLoan);
                found = true;

                custNode->data.balance += selectedLoan.amount;

                updateData(custNode->data);

                LoanNode* toRemove = pendingLoans.head;
                if (toRemove && toRemove->data.id == selectedLoan.id) {
                    pendingLoans.head = toRemove->next;
                    delete toRemove;
                    pendingLoans.size--;
                } else {
                    while (toRemove && toRemove->next) {
                        if (toRemove->next->data.id == selectedLoan.id) {
                            LoanNode* temp = toRemove->next;
                            toRemove->next = temp->next;
                            delete temp;
                            pendingLoans.size--;
                            break;
                        }
                        toRemove = toRemove->next;
                    }
                }

                std::ofstream loansFile("../data/loans.json");
                if (loansFile.is_open()) {
                    loansFile << "{\n  \"loans\":[\n";
                    LoanNode* ln = pendingLoans.head;
                    bool first = true;
                    while (ln) {
                        if (!first) loansFile << ",\n";
                        loansFile << "\t{\n"
                                  << "\t  \"id\":\"" << ln->data.id << "\",\n"
                                  << "\t  \"acc_num\":\"" << ln->data.acc_num << "\",\n"
                                  << "\t  \"type\":\"" << ln->data.type << "\",\n"
                                  << "\t  \"amount\":" << ln->data.amount << ",\n"
                                  << "\t  \"interest\":" << ln->data.interest << ",\n"
                                  << "\t  \"remain_balance\":" << ln->data.remain_balance << ",\n"
                                  << "\t  \"start\":\"" << ln->data.start << "\",\n"
                                  << "\t  \"end\":\"" << ln->data.end << "\",\n"
                                  << "\t  \"status\":\"" << ln->data.status << "\"\n"
                                  << "\t}";
                        first = false;
                        ln = ln->next;
                    }
                    loansFile << " ]\n}\n";
                    loansFile.close();
                }

                clearScreen();
                printLine("Loan Approved");
                std::cout << "Loan ID: " << selectedLoan.id << " has been approved and added to customer account." << std::endl;               
                return;
            }
            custNode = custNode->next;
        }

        if (!found) {
            std::cout << "Customer account not found!" << std::endl;
        }
    } else {
        std::cout << "Loan rejected." << std::endl;
    }

    std::cin.ignore();
    std::cin.get();
}

void saveEmployeesToFile(const EmployeeArray& arr, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file for writing!" << endl;
        return;
    }

    for (int i = 0; i < arr.size; i++) {
        file << arr.employees[i].id << ","
            << arr.employees[i].name << ","
            << arr.employees[i].lastName << ","
            << arr.employees[i].address << ","
            << arr.employees[i].salary << ","
            << arr.employees[i].hireDate << ","
            << arr.employees[i].branchCode << "\n";
    }

    file.close();
    cout << "Employees saved to file successfully!" << endl;
}

EmployeeArray loadEmployeesFromFile(const string& filename) {
    EmployeeArray arr = createEmployeeArray();
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        cout << "No existing employee file found. Creating default admin 'rihab' (ID 101)." << endl;
        Employee admin;
        admin.id = "101";
        admin.name = "rihab";
        admin.lastName = "admin";
        admin.address = "Head Office";
        admin.salary = 0.0;
        admin.hireDate = DateNow();
        admin.branchCode = "001";
        addEmployee(arr, admin);

        std::ofstream outf(filename, std::ios::binary);
        if (outf.is_open()) {
            outf << "[\n";
            outf << "  {\n";
            outf << "    \"id\":\"" << admin.id << "\",\n";
            outf << "    \"name\":\"" << admin.name << "\",\n";
            outf << "    \"lastName\":\"" << admin.lastName << "\",\n";
            outf << "    \"address\":\"" << admin.address << "\",\n";
            outf << "    \"salary\":" << admin.salary << ",\n";
            outf << "    \"hireDate\":\"" << admin.hireDate << "\",\n";
            outf << "    \"branchCode\":\"" << admin.branchCode << "\"\n";
            outf << "  }\n";
            outf << "]\n";
            outf.close();
        }
        else {
            saveEmployeesToFile(arr, filename);
        }
        return arr;
    }

    std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    const char* c = buffer.c_str();
    emp_skipWhitespace(c);

    if (*c == '[' || *c == '{') {
        if (*c == '[') { c++; }
        while (*c) {
            emp_skipWhitespace(c);
            if (*c == '{') {
                Employee emp = emp_parseEmployeeObject(c);
                if (!emp.id.empty() || !emp.name.empty()) {
                    addEmployee(arr, emp);
                }
            }
            else if (*c == ']') {
                c++;
                break;
            }
            else {
                c++;
            }
        }
    }
    else {
        std::istringstream ss(buffer);
        std::string line;
        while (std::getline(ss, line)) {
            if (line.empty()) continue;
            Employee emp;
            size_t pos = 0;
            size_t lastPos = 0;
            pos = line.find(',', lastPos);
            if (pos == std::string::npos) continue;
            emp.id = line.substr(lastPos, pos - lastPos);

            lastPos = pos + 1;
            pos = line.find(',', lastPos);
            if (pos == std::string::npos) continue;
            emp.name = line.substr(lastPos, pos - lastPos);

            lastPos = pos + 1;
            pos = line.find(',', lastPos);
            if (pos == std::string::npos) continue;
            emp.lastName = line.substr(lastPos, pos - lastPos);

            lastPos = pos + 1;
            pos = line.find(',', lastPos);
            if (pos == std::string::npos) continue;
            emp.address = line.substr(lastPos, pos - lastPos);

            lastPos = pos + 1;
            pos = line.find(',', lastPos);
            if (pos == std::string::npos) {
                emp.hireDate = line.substr(lastPos);
                emp.branchCode = "";
            }
            else {
                emp.hireDate = line.substr(lastPos, pos - lastPos);
                lastPos = pos + 1;
                emp.branchCode = line.substr(lastPos);
            }
            addEmployee(arr, emp);
        }
    }
    return arr;
}

