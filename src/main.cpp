#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include "Adapters/FileManagerAdapter.hpp"
#include "Factories/TokenFactory.hpp"
#include "Scanner/Scanner.hpp"
int main(int argc, char *argv[])
{
    try{
        if(argc != 1){
            throw "arguments count is  not correct!";
        }
        else {
            std::string mainDir = argv[0];
            FileManagerAdapter::getInstance().getNeededSourceFiles(mainDir);
            std::shared_ptr<std::string> code = FileManagerAdapter::getInstance().parseFiles();
            std::shared_ptr<TokenFactory>  tokenFactory = std::make_shared<TokenFactory>();
            Scanner scanner(std::move(code),tokenFactory);
        }
    }
    catch (std::exception e) {
        std::cout << "Error: "<<e.what()<<std::endl;
    }
    
}


