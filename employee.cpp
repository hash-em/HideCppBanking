#include "../headers/employeearr.h"
#include "../headers/interface.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

void EmployeeInterface(EmployeeArray *arr)
{
    string Menu[6] = {
        "Employee Management",
        "Customer Accounts Management",
        "Loan Management",
        "Transaction Management",
        "Statistics",
        "Log Out"
    };

    int choice;
    printOptions(Menu, 6);
    cin >> choice;

    if (choice < 1 || choice > 6)
    {
        printLine("Invalid Option");
        EmployeeInterface(arr);
        return;
    }

    switch (choice)
    {
        case 1: EmployeeManagement(arr); break;
        case 2: CustomerAccountManagement(); break;
        case 3: LoanManagement(); break;
        case 4: TransactionManagement(); break;
        case 5: StatisticsMenu(arr); break;
        case 6: logout(); break;
    }

    // return to the menu when finished
    EmployeeInterface(arr);
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

void addEmployee(EmployeeArray& arr, const Employee& emp) {
    // Check if ID already exists
    for (int i = 0; i < arr.size; i++) {
        if (arr.employees[i].id == emp.id) {
            cout << "Error: Employee ID already exists!" << endl;
            return;
        }
    }

    if (arr.size >= arr.capacity) {
        resizeEmployeeArray(arr);
    }

    arr.employees[arr.size] = emp;
    arr.size++;
    cout << "Employee added successfully!" << endl;
}

bool deleteEmployee(EmployeeArray& arr, const string& id) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.employees[i].id == id) {
            // Shift elements to remove the employee
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
    if (arr.size == 0) {
        cout << "No employees to display!" << endl;
        return;
    }

    // Create a temporary array for sorting
    Employee* temp = new Employee[arr.size];
    for (int i = 0; i < arr.size; i++) {
        temp[i] = arr.employees[i];
    }

    // Bubble sort by last name
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
    if (arr.size == 0) {
        cout << "No employees to display!" << endl;
        return;
    }

    cout << "Employees grouped by branch:" << endl;

    // Simple grouping by branch
    for (int i = 0; i < arr.size; i++) {
        string currentBranch = arr.employees[i].branchCode;
        bool branchPrinted = false;

        // Check if we already printed this branch
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
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "No existing employee file found. Starting fresh." << endl;
        return arr;
    }

    string line;
    while (getline(file, line)) {
        Employee emp;
        size_t pos = 0;
        size_t lastPos = 0;

        // Parse CSV line
        pos = line.find(',', lastPos);
        emp.id = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.name = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.lastName = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.address = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.salary = stod(line.substr(lastPos, pos - lastPos));

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.hireDate = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        emp.branchCode = line.substr(lastPos);

        addEmployee(arr, emp);
    }

    file.close();
    cout << "Employees loaded from file successfully!" << endl;
    return arr;
}
void DeleteCompletedLoans(CompLoan &Clist, loanList &list){
        LoanNode *curr = list.head;

    while (curr != nullptr) {

        if (curr->data.status == "completed") {

            CLoanNode *cNode = new CLoanNode;
            cNode->data = curr->data;
            cNode->next = Clist.head;
            Clist.head = cNode;

            LoanNode *toDelete = curr;

            // removing head
            if (curr->prev == nullptr) {
                list.head = curr->next;
                if (list.head != nullptr)
                    list.head->prev = nullptr;
            }
            // middle element
            else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            curr = curr->next;
            delete toDelete;
        }

        else {
            curr = curr->next;
        }
    }

    cout << "All completed loans moved to completed_loans list.\n";
}
void enqueueRequest(LoanRequestQueue &q, const Loan &req)
{
    LoanRequestNode *node = new LoanRequestNode{req, nullptr};

    if (q.tail == nullptr) {
        q.front = q.tail = node;
        return;
    }

    q.tail->next = node;
    q.tail = node;
}

bool dequeueRequest(LoanRequestQueue &q, Loan &out)
{
    if (q.front == nullptr)
        return false;

    LoanRequestNode *temp = q.front;
    out = temp->data;

    q.front = q.front->next;

    if (q.front == nullptr)
        q.tail = nullptr;

    delete temp;
    return true;
}
void processNextRequest(LoanRequestQueue &q, loanList &customerLoans)
{
    Loan req;

    if (!dequeueRequest(q, req)) {
        cout << "No pending requests.\n";
        return;
    }

    cout << "Processing request for Loan ID: " << req.id << endl;
    cout << "Accept loan? (1 = yes, 0 = no): ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        // Create new node
        LoanNode *node = new LoanNode;
        node->data = req;
        node->next = nullptr;

        // Insert into singly linked list
        if (customerLoans.head == nullptr)
        {
            customerLoans.head = node;
        }
        else
        {
            LoanNode *curr = customerLoans.head;
            while (curr->next != nullptr)
                curr = curr->next;

            curr->next = node;
        }

        customerLoans.size++;

        cout << "Loan request ACCEPTED.\n";
    }
    else
    {
        cout << "Loan request DECLINED and permanently removed.\n";
    }
}

void finalizeDay(tranStack &st, TransactionHistory &history)
{
    while (st.last != nullptr)
    {
        tran temp = st.last->data;

        HistoryNode *node = new HistoryNode;
        node->data = temp;
        node->next = history.head;
        history.head = node;

        popTran(st);
    }

    cout << "\nDay finalized successfully.\n";
    cout << "All daily transactions copied to permanent history.\n";
}





void displayHistory(const TransactionHistory &hist)
{
    printLine("TRANSACTION HISTORY");

    HistoryNode *curr = hist.head;

    if (curr == nullptr) {
        cout << "No history available.\n";
        return;
    }

    while (curr != nullptr) {
        cout << "ID: " << curr->data.id
             << " | Type: " << curr->data.type
             << " | Amount: " << curr->data.amount
             << " DT | Date: " << curr->data.date
             << " | Account: " << curr->data.acc_num
             << endl;
        curr = curr->next;
    }
}




void displayAccounts(const customerList &list)
{
    printLine("ACTIVE ACCOUNTS");

    customerNode *curr = list.head;
    while (curr != nullptr) {
        cout << "Account " << curr->data.acc_num
             << " | Holder: " << curr->data.name
             << " | Status: " << curr->data.status
             << " | Balance: " << curr->data.balance << " DT\n";

        curr = curr->next;
    }
}

void changeStatus(customerList &list, string accNum, const string &newStatus)
{
    customerNode *curr = list.head;

    while (curr != nullptr) {
        if (curr->data.acc_num == accNum) {
            curr->data.status = newStatus;
            cout << "Status changed successfully.\n";
            return;
        }
        curr = curr->next;
    }

    cout << "Account not found.\n";
}

void archiveClosedAccounts(customerList &list, ArchiveArray &archive)
{
    customerNode *curr = list.head;
    customerNode *prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->data.status == "closed")
        {
            // =============================
            // 1. Store in ARCHIVE ARRAY
            // =============================
            if (archive.size == archive.capacity)
            {
                cout << "Archive full, cannot store more accounts!\n";
                return;
            }

            archive.arr[archive.size] = curr->data;
            archive.size++;

            // =============================
            // 2. Remove from LINKED LIST
            // =============================
            customerNode *toDelete = curr;

            if (prev == nullptr)
            {
                // deleting head
                list.head = curr->next;
                curr = list.head;
            }
            else
            {
                prev->next = curr->next;
                curr = curr->next;
            }

            delete toDelete;
            list.size--;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }

    cout << "All closed accounts archived.\n";
}

void changeLoanStatus(loanList &list,string LoanID,const string &newStatus)
{
    LoanNode *curr=list.head;
    while(curr!=nullptr){
        if(curr->data.id==LoanID){
            curr->data.status=newStatus;
            cout << "Loan status updated: " << newStatus << "\n";
        }
    }
    curr=curr->next;
    cout<<"Loan not found.\n";
}

