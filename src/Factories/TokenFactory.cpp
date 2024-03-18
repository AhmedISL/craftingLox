#include "TokenFactory.hpp"
#include "Token.hpp"
#include <iostream>
#include <memory>
#include <string>

std::unordered_map<TokenType, tokenCallback> TokenFactory::m_TokenMap;

void TokenFactory::registerToken(TokenType type, tokenCallback cbk)
{
    if(m_TokenMap.find(type) != m_TokenMap.end()){
        std::cout << "Token is already registered" <<std::endl;
    }
    else{
        m_TokenMap.insert({type,cbk}); 
    }
    
}

void TokenFactory::unregisterToken(TokenType type)
{
    if(m_TokenMap.find(type) != m_TokenMap.end()){
        m_TokenMap.erase(type); 
    }
    else{
        std::cout << "Token is not registered" <<std::endl;
    }
}

std::unique_ptr<Token> TokenFactory::getToken(std::string lexem, int lineNo, TokenType type){
    auto  it = m_TokenMap.find(type);
    return std::move(it->second(lineNo, lexem));
}