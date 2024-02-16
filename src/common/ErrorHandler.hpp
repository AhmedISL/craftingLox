
#ifndef ERROR_HANDLER_HPP
#define STORAGE_ADAPTER_HPP


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>

const char REPORTED_ERRORS_FILE[] = "../../error_log.txt";
const std::fstream fs;

// namespace ErrorHandler {
//     inline void reportError(std::string fileName, int lineNumber, std::string  errorMessage) {

//     }

//     inline void printReeorFile(){
        
//     }
// }

//// other way of implemnation using class


//TODO: ADD FUNCTION TO CHECK THE ERRORS PRIORITY
class  ErrorHandler{  
    public:
    void reportError(const std::string &fileName, const int lineNumber, const std::string& errorMessage);
    void printErrorFile();
    void clearErrorFile();
    private:
    ErrorHandler(ErrorHandler&) = delete;
    ErrorHandler& operator=(ErrorHandler&) = delete;
    ErrorHandler();
    static ErrorHandler& getInstance(){
        static ErrorHandler instance;
        return  instance;
    }
    bool is_empty(std::fstream& pFile);
};

#endif  /* ERRORHANDLER_HPP__ */
