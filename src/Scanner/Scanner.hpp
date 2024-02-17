#ifndef SCANNER_HPP__
#define SCANNER_HPP__

#include "iostream"
#include "vector"
#include <string>
#include <vector>
#include "../Factories/Token.hpp"
#include "../Factories/TokenFactory.hpp"
#include <memory>

class Scanner{
    public:
    Scanner(std::unique_ptr<std::string> inputCode,std::shared_ptr<TokenFactory> tokenFactory);
    void scanTokens();
    bool match(char expectedChar);
    char peek() const;
    char peekNext() const;
    char advance();
    void addToken(std::shared_ptr<Token>  token);
    bool isAtEnd();
    bool isAlpha() const;
    bool isDigit() const;
    bool isWhiteSpace();
    void skipWhitSpace();
    bool isAlphaNumeric();
    std::string getIdentifier();
    int getNumber();
    std::string getString();
    private:
    std::shared_ptr<TokenFactory> m_tokenFactory;
    std::vector<Token> m_Tokens;
    int m_startIndex{0};
    int m_currentIndex{0};
    int m_line{1}; //with every new line increament this value to keep track of  line number
    static int m_currentLineNumber;
    std::unique_ptr<std::string> m_inputCode;
};


#endif