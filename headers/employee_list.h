#ifndef EMPLOYEE_LIST_H
#define EMPLOYEE_LIST_H

#include <string>
#include "employee.h"

/*
 * employee_list.h
 *
 * Simple singly-linked list container for Employee objects.
 * This header defines `employeeList` and related node type and
 * declares list operations used by the rest of the project.
 *
 * Design notes:
 * - Keeps the original pointer-based methodology (no std::vector/std::list).
 * - Avoids `using namespace std;` to prevent leaking names into includers.
 * - Function signatures use `const std::string&` for employee id parameters
 *   to match the `Employee::id` type.
 */

/* Node for the employee singly-linked list */
struct employeeNode {
    Employee data;
    employeeNode* next;
};

/* The employee list container */
struct employeeList {
    employeeNode* head;
    int size;
};

/* Create a new empty employee list */
employeeList newEmployeeList();

/* Add an employee to the end of the list */
int addEmployee(employeeList& list, const Employee& emp);

/* Delete the first employee matching the given id.
 * Returns true if deletion happened, false otherwise.
 */
bool deleteEmployee(employeeList& list, const std::string& id);

/* Modify the first employee matching `id` by replacing its data.
 * Returns true if modification happened, false otherwise.
 */
bool modifyEmployee(employeeList& list, const std::string& id, const Employee& newData);

/* Display employees in alphabetical order (by lastName).
 * Implementations may allocate temporary arrays as needed but should
 * not change the list's storage methodology.
 */
void displayEmployeesAlphabetically(const employeeList& list);

/* Display employees grouped by branch (simple grouped iteration). */
void displayEmployeesByBranch(const employeeList& list);

/* Display the earliest and latest hired employees. */
void displayEarliestAndLatest(const employeeList& list);

/* Find an employee by id. Returns pointer to the Employee in the list
 * or nullptr if not found. The returned pointer refers to memory owned
 * by the list; do not delete it.
 */
Employee* findEmployeeById(const employeeList& list, const std::string& id);

/* Free all nodes in the list and reset it to an empty state. */
void freeEmployeeList(employeeList& list);

#endif // EMPLOYEE_LIST_H
