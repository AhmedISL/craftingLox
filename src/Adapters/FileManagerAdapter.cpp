#include "FileManagerAdapter.hpp"
#include <memory>
#include <sstream>
#include <fstream>
# include <dirent.h>
#include <string>
#include <utility>

FileManagerAdapter::FileManagerAdapter(){
    std::cout << "Creating File Manager Adapter" << std::endl;
}

std::string FileManagerAdapter::getFileName(std::string filePath){

    return filePath.substr(filePath.find_last_of("/\\") + 1);
}

std::unique_ptr<std::string>  FileManagerAdapter::parseFiles(){
    std::stringstream filebuffer;
    std::unique_ptr<std::string> parseString(new std::string);

    for(auto file : filePaths){
        std::ifstream readFileIndex (file);

        if(readFileIndex.is_open()){
            int i = 0;
            while (readFileIndex) {
                // ToDo : Add line number ?
                //Current used one is not working correctl
                filebuffer << readFileIndex.rdbuf();
                *parseString += filebuffer.str();
                readFileIndex.close();

            }
        }
    }
    return  std::move(parseString);
}

void FileManagerAdapter::getNeededSourceFiles(char* mainSourceDirectoryPath){

    //this function is based on: https://www.tutorialspoint.com/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-cplusplus
    DIR *dh;
    struct dirent * contents; 
    
    dh = opendir ( mainSourceDirectoryPath );
    
    if ( !dh )
    {
        std::cout << "The given directory is not found";
        return;
    }

    while ( ( contents = readdir ( dh ) ) != NULL )
    {
        std::string name = contents->d_name;
        std::cout << name << std::endl;
        filePaths.push_back(name);
        
        // If the file is a directory, recursively call this function to get all
    }

    closedir ( dh );
}