#include "TokenFactory.hpp"
#include <iostream>

void TokenFactory::registerToken(std::string lexem, std::function<void (std::string,TokenType)> cbk){
    
    

}

std::shared_ptr<Token> TokenFactory::createToken(std::string lexem, int lineNo, TokenType type){
    if(m_TokenMap.find(lexem) != m_TokenMap.end()){
        std::cout << "Token is already registered" <<std::endl;
        return m_TokenMap[lexem](lexem,type);
        // return;
    }
    else {
        std::cout << "Registered token: "<< lexem << std::endl;  
        // registerToken(lexem, );
    }
}

