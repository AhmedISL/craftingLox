#include "ErrorHandler.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

/*
ofstream: Stream class to write on files
ifstream: Stream class to read from files
fstream: Stream class to both read and write from/to files.
*/

ErrorHandler::ErrorHandler(){
    std::cout << "initializing ErrorHandler" << std::endl;
    //creating error file if  it doesn't exist yet
    // fs.open(REPORTED_ERRORS_FILE, std::ios::in | std::ios::out | std::ios::app);
    // fs.close();
}

void ErrorHandler::reportError(const std::string &fileName, const int lineNumber, const std::string& errorMessage){
    std::stringstream reportedErrorMsg;
    reportedErrorMsg << fileName << ":" << lineNumber << "\n"
                        << "error: " << errorMessage  << ";\n";
    std::fstream reportFile(REPORTED_ERRORS_FILE, std::ios::out | std::ios_base::app);
    if (!reportFile) {
        std::cerr << "Could not open/append to the errors log file." << std::endl;
        return;
    }
    reportFile << reportedErrorMsg.str() << std::endl;
    reportFile.close();
    std::cout << reportedErrorMsg.str() << std::endl;
        
}

void ErrorHandler::printErrorFile(){
    std::fstream reportFile(REPORTED_ERRORS_FILE, std::ios_base::in);
    std::string lineContent;
    if(is_empty(reportFile)){
        std::cout << "No errors have been reported so far." << std::endl;
    } 
    else {
        std::cout << "Errors that have been reported so far:\n";
        while(std::getline(reportFile,lineContent)){

            std::cout << lineContent << std::endl;

        }
    }
    clearErrorFile();
}

bool ErrorHandler::is_empty(std::fstream& stream){
    return stream.peek() == std::ifstream::traits_type::eof();
}

void ErrorHandler::clearErrorFile(){
    if( std::remove( REPORTED_ERRORS_FILE ) != 0 ){
        std::cout << "Could not delete the previous error report" << std::endl;
    }
    else{
        std::cout << "Previous error report deleted successfully!" << std::endl;
    }
}