#include "../headers/helpers.h"
#include "../headers/customer_lists.h"
#include <cmath>
#include <iostream>
#include <ctime>

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void printLine(const std::string& text){
    for (int i = 0 ; i < 100 ; i++) std::cout << '-'; std::cout << std::endl;
    for (int i = 0; i < 50 - (int)(std::ceil(text.length() / 2.0)); i++) std::cout << ' ';
    std::cout << text << std::endl;
    for (int i = 0 ; i < 100 ; i++) std::cout << '-'; std::cout << std::endl;
}

void printOptions(const std::string* texts,int size){
    for (int i = 0 ; i < 100 ; i++) std::cout << '-'; std::cout << std::endl;
    for (int idx = 0; idx < size ; idx++)
    {
        for (int j = 0; j < 48 - (int)(std::floor(texts[idx].length() / 2.0)) ; j++) std::cout << ' ';
        std::cout << idx + 1 << " - " << texts[idx] << std::endl;
    }
    for (int i = 0 ; i < 100 ; i++) std::cout << '-'; std::cout << std::endl;
}

std::string DateNow(){
    char today[11] = {0};
    std::time_t t = std::time(nullptr);
    std::tm* tm_ptr = std::localtime(&t);
    if (tm_ptr) {
        std::strftime(today, sizeof(today), "%d/%m/%Y", tm_ptr);
        return std::string(today);
    }
    return std::string("");
}
