#include <iostream>
#include <string>
#include <windows.h>
#include <direct.h>

using namespace std;

void listFiles(const string& path) {
    cout << "Listing files in directory: " << path << endl;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((path + "/*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "Error: Could not open directory." << endl;
        return;
    }

    do {
        cout << findFileData.cFileName << endl;
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void createDirectory(const string& path) {
    cout << "Creating directory: " << path << endl;
    if (_mkdir(path.c_str()) == 0) {
        cout << "Directory created successfully." << endl;
    } else {
        cout << "Error: Could not create directory. It may already exist or another error occurred." << endl;
    }
}

void changeDirectory(string& currentPath, const string& newPath) {
    cout << "Changing directory to: " << newPath << endl;
    if (_chdir(newPath.c_str()) == 0) {
        currentPath = newPath;
        cout << "Current working directory: " << currentPath << endl;
    } else {
        cout << "Error: Could not change directory." << endl;
    }
}

void showMenu() {
    cout << "\nMenu:\n";
    cout << "1. List Files\n";
    cout << "2. Create Directory\n";
    cout << "3. Change Directory\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}
