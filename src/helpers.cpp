#include "../headers/helpers.h"
#include "../headers/customer_lists.h"
#include <cmath>
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
    for (int i = 0; i < 50-ceil(text.length()/2) ; i++) cout << ' ';
    cout << text <<endl;
    for (int i = 0 ; i < 100 ; i++) cout << '-'; cout << endl;

}

void printOptions(string* texts,int size){
    for (int i = 0 ; i < 100 ; i++) cout << '-'; cout << endl;
    for (int i = 0; i < size ; i++)
    {
        for (int i = 0; i < 100-floor(texts[i].length()/2) ; i++) cout << ' ';
        cout << i+1 << " - "<<texts[i] << endl;
    }
    for (int i = 0 ; i < 100 ; i++) cout << '-'; cout << endl;

}

string DateNow(){
    char today[11];
        time_t t=std::time(NULL);
        strftime(today, sizeof(today), "%d/%m/%Y", localtime(&t));
        return today;
}
