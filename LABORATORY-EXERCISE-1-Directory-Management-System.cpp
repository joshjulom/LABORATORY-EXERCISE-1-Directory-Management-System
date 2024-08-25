#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using namespace std;

void listFiles(const string& path) {
    cout << "Listing files in Directory: " << path << endl;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            cout << entry.path().filename().string() << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void createDirectory(const string& path) {
    cout << "Creating Directory: " << path << endl;
    try {
        if (fs::create_directory(path)) {
            cout << "Directory created successfully." << endl;
        } else {
            cout << "Failed to create directory. It may already exist." << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}
