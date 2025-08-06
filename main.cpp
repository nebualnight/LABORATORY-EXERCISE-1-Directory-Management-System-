#include <iostream>
#include <direct.h>
#include <string>
#include <filesystem>

using namespace std; 

namespace fs = std::filesystem;

void DisplayMenu() {
    cout << "Directory Manager Menu:" << endl;
    std::cout << "1. List files";
    std::cout << "2. Create a new directory";
    std::cout << "3. Change directory";
    std::cout << "4. Show current directory";
    std::cout << "5. Exit";
    std::cout << "--------------------------------";
    
