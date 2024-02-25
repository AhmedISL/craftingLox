#include "FileManagerAdapter.hpp"
#include <iostream>
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

std::shared_ptr<std::string>  FileManagerAdapter::parseFiles(){
    std::shared_ptr<std::string> parseString(new std::string);

    for(auto file : filePaths){
        std::stringstream filebuffer;
        std::ifstream readFileIndex (file);

        if(readFileIndex.is_open()){
            if (readFileIndex) {
                // ToDo : Add line number ?
                //Current used one is not working correctl
                //need to add a closure for file end to  get the last line and restart the line counting
                filebuffer << readFileIndex.rdbuf();
                filebuffer <<  "\n";
                *parseString += filebuffer.str();
                readFileIndex.close();

            }
        }
    }
    return  std::move(parseString);
}

void FileManagerAdapter::getNeededSourceFiles(std::string mainSourceDirectoryPath){

    //this function is based on: https://www.tutorialspoint.com/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-cplusplus
    DIR *dh;
    dh = opendir ( mainSourceDirectoryPath.c_str() );
    
    if ( !dh )
    {
        std::cout << "The given directory is not found";
        return;
    }
    struct dirent * contents;

    while ( ( contents = readdir ( dh ) ) != NULL )
    {
        std::string filename = contents->d_name;
        if(filename != "." && filename != ".."){
            std::string name = std::string(mainSourceDirectoryPath) + "/" + contents->d_name;
            /*check if currently read file is directory
                yes ->  read the file names inside this diectory 
                no ->   add file path to the filepaths vector
            */
            if (contents->d_type == DT_DIR) {
                getNeededSourceFiles(name);
            }
            else{
                std::cout << name << std::endl;
                if(name.find(".hpp") != std::string::npos || name.find(".cpp") != std::string::npos)
                {
                    std::cout << "a file .hpp or .cpp was found, file will be added to list" << std::endl;
                    filePaths.push_back(name);
                }
                else {
                    std::cout << "a file is not .hpp or .cpp, file will be discarded" << std::endl;
                }
                
            }
        }
    }

    closedir ( dh );
}