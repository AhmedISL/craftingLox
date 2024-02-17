#include "Scanner.hpp"
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <exception>
#include <variant>

Scanner::Scanner(std::unique_ptr<std::string> inputCode, std::shared_ptr<TokenFactory> tokenFactory)
                                        :m_inputCode(std::move(inputCode)),m_tokenFactory(tokenFactory)
{
    std::cout << "initializing Scanner" << std::endl;
    tokenFactory->registerToken("(", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("(",lineNumber, TokenType::LBRACKET);});
    tokenFactory->registerToken(")", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("(",lineNumber, TokenType::LBRACKET);});
    tokenFactory->registerToken("[", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("[",lineNumber, TokenType::LSQUAREBRACKET);});
    tokenFactory->registerToken("]", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("]",lineNumber, TokenType::RSQUAREBRACKET);});
    tokenFactory->registerToken("{", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("{",lineNumber, TokenType::LCURLYBRACKET);});
    tokenFactory->registerToken("}", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("}",lineNumber, TokenType::RCURLYBRACKET);});
    tokenFactory->registerToken("<", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("<",lineNumber, TokenType::LANGLEBRACKET);});
    tokenFactory->registerToken(">", [this](int lineNumber,std::string text){return m_tokenFactory->createToken(">",lineNumber, TokenType::RANGLEBRACKET);});
    tokenFactory->registerToken("+", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("+",lineNumber, TokenType::ADD);});
    tokenFactory->registerToken("-", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("-",lineNumber, TokenType::SUB);});
    tokenFactory->registerToken("=", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("=",lineNumber, TokenType::ASSIGNMENT);});
    tokenFactory->registerToken("!", [this](int lineNumber,std::string text){return m_tokenFactory->createToken("!",lineNumber, TokenType::NOT);});
    tokenFactory->registerToken(";", [this](int lineNumber,std::string text){return m_tokenFactory->createToken(";",lineNumber, TokenType::SEMICOLON);});
    // m_inputCode->substr(m_startIndex,m_currentIndex);
}

char Scanner::advance(){
    return  (*m_inputCode)[m_currentIndex++];
}

char Scanner::peek() const{
    return  (*m_inputCode)[m_currentIndex ];
}

char Scanner::peekNext() const{
    return  (*m_inputCode) [m_currentIndex +1];
}

bool Scanner::match(char expectedChar){
    if (isAtEnd()) {
        return false;
    }
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

std::string  Scanner::getIdentifier(){
    while (isAlphaNumeric() && !isAtEnd()){
        advance();
    }
    return  m_inputCode->substr(m_startIndex,m_currentIndex-1); //
}


bool Scanner::isWhiteSpace(){
    char c =  peek();
    switch (c)
    {
    case '\r':
    case ' ':
    case '\t':
        return true;
        break;
    case '\n':
    // Skip the newline character and continue to next line.
        m_line++;
        return true;
     default:
         return false;
    }
}

void Scanner::skipWhitSpace(){
    while(isWhiteSpace())
        advance();
}

bool Scanner::isAlphaNumeric(){
    return ( isAlpha() || isDigit());
}

std::string Scanner::getString(){
    while (peek() != '"' && !isAtEnd()) {
        advance();
    }
    return m_inputCode->substr(m_startIndex,m_currentIndex-1);
}

void Scanner::scanTokens(){
    try{
        if(m_inputCode == nullptr || m_inputCode->length() == 0){
            throw  "Input code cannot be empty";
        }
        
        while(!isAtEnd()){
            m_startIndex = m_currentIndex;
            // std::string s;
            TokenType t;
            //Skip white space characters.
            skipWhitSpace();
            char c = advance();
            switch (c) {
                case '-': 
                    if (match('=')) {
                        addToken(m_tokenFactory->createToken("-=", m_line,TokenType::SUBEQ));
                    }
                    else {
                        addToken(m_tokenFactory->createToken("-", m_line,TokenType::SUB)); 
                    }
                    break;
                case '+': 
                    if (match('=')){
                        addToken(m_tokenFactory->createToken("+=", m_line,TokenType::ADDEQ));
                    }
                    else{
                        addToken(m_tokenFactory->createToken("+", m_line,TokenType::ADD));
                    }
                    break;
                /*indicating string*/
                case '"':
                    addToken(m_tokenFactory->createToken(getString(), m_line,TokenType::STRING));
                    break;
                case '|':
                    if (match('|')){
                        addToken(m_tokenFactory->createToken("||", m_line,TokenType::OR));
                    }
                    else if (match('=')) {
                        addToken(m_tokenFactory->createToken("|=", m_line, TokenType::OREQ));
                    }
                    else{
                    addToken(m_tokenFactory->createToken("|", m_line,TokenType::BITOR));
                    }
                    break;
                case '&':
                    if (match('&')){
                        addToken(m_tokenFactory->createToken("&&", m_line,TokenType::AND));
                    }
                    else if (match('=')) {
                        addToken(m_tokenFactory->createToken("&=", m_line, TokenType::ANDEQ));
                    }
                    else{
                    addToken(m_tokenFactory->createToken("&", m_line,TokenType::BITAND));
                    }
                    break;
                case '/':
                    if (match('/')){
                        //skip the comment
                        while (!isAtEnd() && peek() != '\n'){
                            advance();
                        }
                    }else if (match('*')){
                        //skip the multiline comment
                        bool isMultiLine = true;
                        while(!isAtEnd()) {
                            if (peek() == '*' && peekNext() ==  '/'){
                                isMultiLine = false;
                                advance();
                                advance();
                                break;
                            }
                            advance();
                        }
                        if (isMultiLine){
                            std::stringstream ss;
                            ss << "Unclosed multi-line comment." << std::to_string(m_line);
                            throw ss.str();
                        }
                    }else{
                        addToken(m_tokenFactory->createToken("/", m_line,TokenType::DIV));
                    }
                    break;

                /*QUESTION CONFUSED ABOUT THE * HOW TO CLARIFY IF POINTER OR MULTIPLICATION*/
                // case '*':
                //     if (peekNext() == '=')
                //     addToken(m_tokenFactory->createToken(s, 0,TokenType::POINTER));  break; 
                default:
                //most probably new var or built in identifier need to be regestered ?
                break;
                
            }
        }
    }
    catch(std::exception & e){
        std::cout << "failed to scan input source code" << e.what()<<std::endl;
    }
}