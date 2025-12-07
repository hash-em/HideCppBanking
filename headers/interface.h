#ifndef INTERFACE_H
#define INTERFACE_H

#include "helpers.h"
#include "customer_lists.h"

/*
 * Main application interface declarations.
 *
 * Notes:
 * - This header provides declarations used by the CLI entry point and menus.
 * - It intentionally avoids `using namespace std;` to keep headers clean.
 */

/* Show initial menu and drive main program flow.
 * Returns:
 *   0 on normal exit, other codes for specific flows (as used by implementation).
 */
int ini();

/* Generic login entry (implementation may dispatch to customer or employee flows). */
int login();

/* Logout and return to the initial menu. */
int logout();

/* Create a new customer account (interactive). */
int createAccount();

/* Prompt for customer credentials and return a `customer`.
 * On failure the implementation returns a sentinel `customer` with `acc_num == "0"`.
 */
customer customer_login();

#endif // INTERFACE_H