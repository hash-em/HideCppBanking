#include "../headers/helpers.h"
void clearScreen() {
#ifdef _WIN32 // For Windows
    system("cls");
#else // For Unix-based systems (Linux, macOS)
    system("clear");
#endif
}
