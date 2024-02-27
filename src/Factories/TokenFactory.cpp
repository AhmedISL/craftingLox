#include "TokenFactory.hpp"
#include "Token.hpp"
#include <iostream>
#include <memory>
#include <string>

std::unordered_map<std::string, tokenCallback> TokenFactory::m_TokenMap;

void TokenFactory::registerToken(std::string lexem, tokenCallback cbk)
{
    if(m_TokenMap.find(lexem) != m_TokenMap.end()){
        std::cout << "Token is already registered" <<std::endl;
    }
    else{
        m_TokenMap.insert({lexem,cbk}); 
    }
    
}

std::unique_ptr<Token> TokenFactory::getToken(std::string lexem, int lineNo, TokenType type){
    auto newToken =  std::make_unique<Token>(type,lineNo,lexem,lexem);
    return std::move(newToken);
}

std::unique_ptr<Token> TokenFactory::createToken(std::string lexem, int lineNo, TokenType type){
    if  (m_TokenMap.find(lexem) == m_TokenMap.end()) {
        registerToken(lexem, [&](int lineNo_cbk,std::string lexem_cbk){return getToken(lexem_cbk,lineNo_cbk,type);});
        
    }
    else {
    }
    return std::move(m_TokenMap[lexem](lineNo, lexem));
}


