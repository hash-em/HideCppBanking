#ifndef HELPERS_H
#define HELPERS_H

#include <cstdlib> // for system()
#include <string>
#include <ctime>

/*
 * Utility helpers used across the project.
 *
 * Notes:
 * - This header avoids `using namespace std;` to prevent global namespace
 *   pollution. Implementations expect the same free functions (no namespace).
 * - Keep signatures stable so existing callers do not need modification.
 */

/* Clear the console screen (platform-aware). */
void clearScreen();

/* Print a centered decorative line with the given text. */
void printLine(const std::string& text);

/* Print a numbered list of options.
 * - texts: pointer to an array of std::string with 'size' entries.
 * - size: number of options.
 */
void printOptions(const std::string* texts, int size);

/* Return current date formatted as DD/MM/YYYY (matching existing code). */
std::string DateNow();

#endif // HELPERS_H