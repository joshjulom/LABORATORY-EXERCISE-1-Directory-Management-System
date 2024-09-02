#include <iostream>
#include <string>
#include <windows.h>
#include <direct.h>

using namespace std;

void listFiles(const string& path, const string& pattern = "*.*") {
    cout << "Listing files in directory: " << path << endl;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((path + "\\" + pattern).c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "Error: Could not open directory." << endl;
        return;
    }

    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            cout << "[DIR] " << findFileData.cFileName << endl;
        } else {
            cout << findFileData.cFileName << endl;
        }
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
    cout << "\nMain Menu:\n";
    cout << "1. List Files\n";
    cout << "2. Create Directory\n";
    cout << "3. Change Directory\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void showListFilesMenu() {
    cout << "\nList Files Menu:\n";
    cout << "1. List all files\n";
    cout << "2. List files by extension\n";
    cout << "3. List files by pattern\n";
    cout << "4. Back to main menu\n";
    cout << "Enter your choice: ";
}

void showChangeDirectoryMenu() {
    cout << "\nChange Directory Menu:\n";
    cout << "1. Move one step back (to the parent directory)\n";
    cout << "2. Move to the root directory\n";
    cout << "3. Move to a specific directory\n";
    cout << "4. Back to main menu\n";
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
            int listChoice;
            do {
                showListFilesMenu();
                cin >> listChoice;

                switch (listChoice) {
                case 1:
                    listFiles(currentPath);
                    break;
                case 2: {
                    string extension;
                    cout << "Enter the file extension (e.g., .txt): ";
                    cin >> extension;
                    listFiles(currentPath, "*"+extension);
                    break;
                }
                case 3: {
                    string pattern;
                    cout << "Enter the file pattern (e.g., moha*.*): ";
                    cin >> pattern;
                    listFiles(currentPath, pattern);
                    break;
                }
                case 4:
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            } while (listChoice != 4);
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
            int changeChoice;
            do {
                showChangeDirectoryMenu();
                cin >> changeChoice;

                switch (changeChoice) {
                case 1: {
                    string parentDir = currentPath.substr(0, currentPath.find_last_of("\\"));
                    changeDirectory(currentPath, parentDir.empty() ? "." : parentDir);
                    break;
                }
                case 2:
                    changeDirectory(currentPath, "C:\\"); // Root directory
                    break;
                case 3: {
                    string newPath;
                    cout << "Enter the path to change to: ";
                    cin >> newPath;
                    changeDirectory(currentPath, newPath);
                    break;
                }
                case 4:
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            } while (changeChoice != 4);
            break;
        }
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != 4);

    return 0;
}
