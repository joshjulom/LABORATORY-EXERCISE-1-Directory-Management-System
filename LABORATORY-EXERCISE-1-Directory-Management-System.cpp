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

int main() {
    char cwd[1024];
    if (!_getcwd(cwd, sizeof(cwd))) {
        cout << "Error: Could not get current working directory." << endl;
        return 1;
    }
    string currentPath = cwd;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            listFiles(currentPath);
            break;
        }
        case 2: {
            string newDir;
            cout << "Enter the name of the new directory: ";
            cin >> newDir;
            createDirectory(currentPath + "\\" + newDir);
            break;
        }
        case 3: {
            string newPath;
            cout << "Enter the path to change to: ";
            cin >> newPath;
            changeDirectory(currentPath, newPath);
            break;
        }
        case 4: {
            cout << "Exiting..." << endl;
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }

    } while (choice != 4);

    return 0;
}
