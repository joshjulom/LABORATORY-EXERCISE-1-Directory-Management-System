#include <iostream>
#include <cstdio>     // For system("pause")
#include <direct.h>   // For _mkdir and _chdir

void displayFiles() {
    system("dir");  // Lists files in the current directory (Windows command)
    system("pause");  // Waits for user to press a key
}
