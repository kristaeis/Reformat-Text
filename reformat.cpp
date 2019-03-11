/********************************************************************
 * Author: Krista Eis
 * Last updated: 12/9/18
 * *****************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <dirent.h>

bool searchDirectory(std::string fileName); 
std::string openFile(std::string fileName);
std::string reformat(std::string line);

int main(int argc, char *argv[]){
    std::string fileName = argv[1]; // get file name

    // search cwd 
    if(!searchDirectory(fileName)){ // file name not found in current fir
        std::cout << "File not found" << std::endl;
    }
    else{ // file name found in current dir - open file
	std::string newFile = openFile(fileName); // opens file, re-formats it, and writss to new file
        std::cout << "Reformatting complete - new file '" << newFile << "' created" << std::endl;
    }

    return 0;
}

/********************************************************
 * Searches cwd for file that matches the name given. 
 * Input: string
 * Return: bool (true if match found, false otherwise)
 * *****************************************************/

bool searchDirectory(std::string fileName){
    DIR* dirToCheck;
    struct dirent *fileInDir;
    FILE* file;
    bool foundFile = false;
    dirToCheck = opendir("."); // open dir currently in
    if(dirToCheck > 0) { // if dir can be opened
        while((fileInDir = readdir(dirToCheck)) != NULL){
	    if((char*)fileInDir->d_name ==  fileName){ 
	        foundFile = true; // file was found
	    }
        }
    }
    closedir(dirToCheck); // close dir
    return foundFile;
}


/***********************************************************************
 * Opens file, reformats it by caling reformat, and writes to new file. 
 * Input: file name
 * Return: new file name
 * *********************************************************************/

std::string openFile(std::string fileName){
    std::string line;
    std::string newFileName = fileName;
    newFileName.erase(newFileName.end()-4, newFileName.end()); // remove extension from file name
    newFileName += "_new.txt"; // create new file name (fileName_new.txt)
    std::ofstream newFile(newFileName.c_str()); // create new file and open it (write only)

    std::ifstream dataFile(fileName.c_str()); // open file (read only)
    while(dataFile >> line){ // read entire file line by line
        line = reformat(line); // re-formats line
        newFile << line; // write line to new file
        newFile << " "; // write line to new file
    }

    dataFile.close();
    newFile.close();

    return newFileName;
}


/***********************************************************************
 * Re-formats line by removing chars 
 * Input: line of file
 * Return: re-formatted line
 * *********************************************************************/

std::string reformat(std::string line){
    size_t pos = std::string::npos;
    std::string toReplace = "|||xx|||";
    while((pos = line.find(toReplace)) != std::string::npos){ // replace all chars
	line.replace(pos, 8, 1, '\n');
    }
    toReplace = "xx";
    while((pos = line.find(toReplace)) != std::string::npos){ // remove all chars 
        line.erase(pos, toReplace.length());
    }
    toReplace = "\n\n\n\n";
    while((pos = line.find(toReplace)) != std::string::npos){ // replace all chars 
	line.replace(pos, 4, 2, '\n');
    }

    return line;
}
