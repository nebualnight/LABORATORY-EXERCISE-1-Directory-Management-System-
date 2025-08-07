#include <iostream>
#include <filesystem>
#include <string>

#ifdef _WIN32
#include <direct.h>
#endif

namespace fs = std::filesystem;

int getValidatedChoice(int minOption, int maxOption) {
    int choice;
    while (true) {
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < minOption || choice > maxOption) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between "
                      << minOption << " and " << maxOption << "." << std::endl;
        } else {
            std::cin.ignore(10000, '\n');
            return choice;
        }
    }
}

void listFiles() {
    std::cout << "[1] List All Files" << std::endl;
    std::cout << "[2] List Files by Extensions" << std::endl;
    std::cout << "[3] List Files by Pattern" << std::endl;

    int choice = getValidatedChoice(1, 3);
    std::string extension;

    switch (choice) {
        case 1:
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (fs::is_regular_file(entry.path())) {
                    std::cout << entry.path().filename() << std::endl;
                }
            }
            break;

        case 2:
            std::cout << "Enter file extension (e.g., .txt): ";
            std::cin >> extension;
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.path().extension() == extension) {
                    std::cout << entry.path().filename() << std::endl;
                }
            }
            break;

        case 3:
            std::cout << "Pattern matching not supported in this version." << std::endl;
            break;
    }
}

void createDirectory() {
    std::string dirName;
    std::cout << "Enter directory name to create: ";
    std::cin >> dirName;

    if (!fs::exists(dirName)) {
        fs::create_directory(dirName);
        std::cout << "Directory \"" << dirName << "\" created successfully." << std::endl;
    } else {
        std::cout << "Directory \"" << dirName << "\" already exists." << std::endl;
    }
}

void changeDirectory() {
    std::cout << "[1] Move to Parent Directory" << std::endl;
    std::cout << "[2] Move to Root Directory" << std::endl;
    std::cout << "[3] Enter Custom Path (e.g., \"C:\\Users\\Documents\")" << std::endl;

    int choice = getValidatedChoice(1, 3);
    std::string path;

    switch (choice) {
        case 1:
            fs::current_path(fs::current_path().parent_path());
            std::cout << "Moved to parent directory: " << fs::current_path() << std::endl;
            break;

        case 2:
            fs::current_path(fs::current_path().root_path());
            std::cout << "Moved to root directory: " << fs::current_path() << std::endl;
            break;

        case 3:
            std::cout << "Enter directory path to move to: ";
            std::getline(std::cin >> std::ws, path);
            if (fs::exists(path) && fs::is_directory(path)) {
                fs::current_path(path);
                std::cout << "Current Directory changed to: " << fs::current_path() << std::endl;
            } else {
                std::cout << "Error: Directory \"Invalid path\" not found!" << std::endl;
            }
            break;
    }
}


void mainMenu() {
    int option;
    do {
        std::cout << "DIRECTORY MANAGEMENT SYSTEM" << std::endl;
        std::cout << "[1] List Files" << std::endl;
        std::cout << "[2] Create Directory" << std::endl;
        std::cout << "[3] Change Directory" << std::endl;
        std::cout << "[4] Exit List Files" << std::endl;

        option = getValidatedChoice(1, 4);

        switch (option) {
            case 1: listFiles(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: std::cout << "Exiting program..." << std::endl; break;
        }
    } while (option != 4);
}

int main() {
    mainMenu();
    return 0;
}
