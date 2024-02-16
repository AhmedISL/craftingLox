
#ifndef SFILE_MANAGER_ADAPTER_HPP
#define SFILE_MANAGER_ADAPTER_HPP

#include "iostream"
#include "vector"
#include <memory>
#include <string>

class FileManagerAdapter{
    ///  @brief A class that provides a way to interact with the file system.
    
    public:
    /**
     * @brief Construct a new File Manager Adapter object
     * 
     */
    FileManagerAdapter(FileManagerAdapter const&) = delete;

    void operator=(FileManagerAdapter const&) = delete;

    /**
     * @brief Get the Instance object
     * 
     * @return FileManagerAdapter& 
     */
    static FileManagerAdapter& getInstance(){
        static  FileManagerAdapter instance;
        return instance;
    }
    
    /**
     * @brief ParseFiles  uses a vector of strings, where each string is a path to a file. 
     * It reads all the files and returns their contents as one big string.
     * 
     * @return std::string 
     */
    std::unique_ptr<std::string> parseFiles();
    
    /**
     * @brief Get the File Name given filepath
     * 
     * @param filePath 
     * @return std::string 
     */
    std::string getFileName(std::string filePath);
    
    /**
     * @brief Get the Needed Source Files object
     * 
     * @param mainSourceDirectoryPathe 
     */
    void getNeededSourceFiles(char* mainSourceDirectoryPath);

    private:
    FileManagerAdapter();
    std::vector<std::string> filePaths;
    // static FileManagerAdapter* instance;
};

#endif /* FILEMANAGERADAPTER_HPP__ */