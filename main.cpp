#include <iostream>
#include <direct.h>
#include <string>
#include <filesystem>

using namespace std; 

namespace fs = std::filesystem;

void DisplayMenu();
void listFiles();
void CreateDirectory();
void ChangeDirectory();

int main() {
    int choice;
    do {
        cout << "Current Directory: "; << fs::current_path() << endl;
        DisplayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        
        cin .ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                CreateDirectory();
                break;
            case 3:
                ChangeDirectory();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;

        }
        cout << endl;
    } while (choice != 4);

    return 0;

}

void DisplayMenu() {
    cout << "    File System Menu    " << endl;
    cout << "1. List Files" << endl;
    cout << "2. Create Directory" << endl;
    cout << "3. Change Directory" << endl;
    cout << "4. Exit" << endl;
    cout << "-------------------" << endl;
}

void listFiles() {
    cout << "Files and directories in the current path:" << endl;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (fs::is_directory(entry.status())) {
            cout << "[DIR]  " << entry.path().filename().string() << endl;
        } else if (fs::is_regular_file(entry.status())) {
            cout << "[FILE] " << entry.path().filename().string() << endl;
        }
    }
}
void CreateDirectory() {
    string dirName;
    cout << "Enter directory name to create: ";
    getline(cin, dirName);

    if (fs::create_directory(dirName)) {
        cout << "Directory '" << dirName << "' created successfully." << endl;
    } else {
        if (fs::exists(dirName)) {
            cout << "Directory '" << dirName << "' already exists." << endl;
        } else {
            cout << "Error could not create directory '" << dirName << "'." << endl;
        }
    }
}

void ChangeDirectory() {
    string newPath;
    cout << "Enter new directory path: ";
    getline(cin, newPath);  
    try {
        fs::current_path(newPath);
        cout << "Changed current directory to: " << fs::current_path() << endl;
    } catch (const fs::filesystem_error& e) {
        cout << "Error changing directory: " << e.what() << endl;
    }
}


