#include "Token.hpp"
#include <variant>

Token::Token(TokenType type, int line, std::string& lexem, litralOptions litral=std::monostate() )
                        :m_type(type),m_line(line),m_lexem(lexem),m_litral(litral) 
{ 
}