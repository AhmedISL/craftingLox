#include "TokenFactory.hpp"
#include "Token.hpp"
#include <iostream>
#include <memory>
#include <string>

void TokenFactory::registerToken(std::string lexem, std::function<std::shared_ptr<Token> (int, std::string)> cbk)
{
    if(m_TokenMap.find(lexem) != m_TokenMap.end()){
        std::cout << "Token is already registered" <<std::endl;
    }
    else{
        m_TokenMap.insert({lexem,cbk}); 
    }
    
}

std::shared_ptr<Token> TokenFactory::createToken(std::string lexem, int lineNo, TokenType type){
    auto newToken =  std::make_shared<Token>(type,lineNo,lexem,lexem);
    return newToken;
}


