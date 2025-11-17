#include "../headers/helpers.h"
using namespace std;
void clearScreen() {
#ifdef _WIN32 // For Windows
    system("cls");
#else // For Unix-based systems (Linux, macOS)
    system("clear");
#endif
}

void printLine(string text){
    for (int i = 0 ; i < 100 ; i++) cout << '-'; cout << endl;
    cout << "\t\t\t\t\t\t"<<text <<endl;
    for (int i = 0 ; i < 100 ; i++) cout << '-'; cout << endl;

}
