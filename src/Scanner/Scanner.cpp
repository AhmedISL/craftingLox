#include "Scanner.hpp"
#include <memory>
#include <string>
#include <utility>
#include <exception>

Scanner::Scanner(std::unique_ptr<std::string> inputCode, std::shared_ptr<TokenFactory> tokenFactory)
                                        :m_inputCode(std::move(inputCode)),m_tokenFactory(tokenFactory)
{
    std::cout << "initializing Scanner" << std::endl;
    // m_inputCode->substr(m_startIndex,m_currentIndex);
}

char Scanner::advance(){
    return  (*m_inputCode)[++m_currentIndex];
}

char Scanner::peek() const{
    return  (*m_inputCode)[m_currentIndex ];
}

char Scanner::peekNext() const{
    return  (*m_inputCode) [m_currentIndex +1];
}

bool Scanner::match(char expectedChar){
    if( peek() == expectedChar ) {
        m_currentIndex++;
        return true;
    }else{
        return false;
    }
}

bool Scanner::isAtEnd(){
    if(m_currentIndex >= m_inputCode->length())
    {
        return true;   
    }
    else
    {
        return false;
    }
}

bool Scanner::isDigit() const{
    return (peek() >= '0' && peek() <= '9');
}

bool Scanner::isAlpha() const{
    char c = peek();
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

bool Scanner::isAlphaNumeric(){
    return ( isAlpha() || isDigit());
}

std::string Scanner::getString(){
    return m_inputCode->substr(m_startIndex,m_currentIndex);
}

void Scanner::scanTokens(){
    try{
        if(m_inputCode == nullptr || m_inputCode->length() == 0){
            throw  "Input code cannot be empty";
        }
        
        while(!isAtEnd()){
            m_startIndex = m_currentIndex;
            std::string s;
            char c = advance();
            s.push_back(c);
            switch (c) {
                case '(': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::LBRACKET));
                    break;
                case ')': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::RBRACKET)); 
                    break;
                case '{': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::LCURLYBRACKET)); 
                    break;
                case '}': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::LCURLYBRACKET));  
                    break;
                case ',': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::COMMA)); ; break;
                case '.': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::DOT)); ; break;
                case '-': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::SUB));  break;
                case '+': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::ADD));  break;
                case ';': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::SEMICOLON));  break;
                case '*': 
                    addToken(m_tokenFactory->createToken(s, 0,TokenType::POINTER));  break; 
                
            }
        }
    }
    catch(std::exception & e){
        
    }
}