/*
Title: Find a file
File Name : findFile
Programmer : Brion Blais
Date : 11 / 2024
Requirements :
This program takes a path to a directory from the user and then asks for a file name to search for.  
It responds when it has found it with the full path.
 */

#include <iostream>
#include <filesystem>
using namespace std;

//funct prototypes
const char* stringToCStr(string localStringName);
string getFileName();
int searchForFile(string, filesystem::path);



int main()
{
    string newpath;
    string fileName;

    filesystem::path currentFolder = filesystem::current_path();
    cout << "You are currently working in the following directory: " << currentFolder.string() << endl;
    cout << "Please enter the path of the directory you would like to search:\t";
    getline(cin, newpath);
    filesystem::path newFolder{ newpath };
    cout << "The search directory is: " << newFolder.string() << endl;
    cout << "Enter a filename to search for:\t";
    fileName = getFileName();
    searchForFile(fileName, newFolder);
    return 0;
}

string getFileName() {
    string localName;
    getline(cin, localName);
    return localName;
}

const char* stringToCStr(string localStringName) {
    const char* cString = localStringName.c_str();
    return cString;
}

int searchForFile(string stringName, filesystem::path localPath) {
    const char* cStrFileName = stringToCStr(stringName);
    int arraysize =  strlen(cStrFileName);
    bool match = 0;
    while (match == 0) {
        int count = 0;
        for (const auto& entry : filesystem::recursive_directory_iterator(localPath)) {
            if (entry.is_regular_file()) {
                count++;
                filesystem::path entryPath = entry.path();
                filesystem::path entryName = entryPath.filename();
                const char* tempCStr = stringToCStr(entryName.string());
                if (strlen(cStrFileName) == strlen(tempCStr)) {
                    bool charMatch = 0;
                    int j = 0;
                    for (int i = 0; i < (strlen(cStrFileName)); i++) {
                        char searchChar = cStrFileName[i];
                        char entryChar = tempCStr[j];
                        if (searchChar != entryChar) {
                            charMatch = 0;
                            break;
                        }
                        else {
                            j++;
                            charMatch = 1;
                            continue;
                        }
                    }                
                    if ((charMatch == 1) && ((cStrFileName[(strlen(cStrFileName) - 1)]) == (tempCStr[strlen(tempCStr) - 1]))) {
                            match = 1;
                            cout << "Searched " << count << " files ... ";
                            cout << "\nfound the file at the following path:\n" << entry.path() << endl;
                            return 0;
                        }
                    }
                }
            }
            
        }
}
