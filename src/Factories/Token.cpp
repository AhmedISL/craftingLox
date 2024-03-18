#include "Token.hpp"
#include <variant>

Token::Token(std::string lexem, int line, TokenType type, litralOptions litral = std::monostate())
                        :m_type(type),m_line(line),m_lexem(lexem),m_litral(litral) 
{ 
}

TokenType Token::getTokenType(){
    return  m_type;
}