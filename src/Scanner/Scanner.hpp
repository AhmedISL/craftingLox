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
    Scanner(std::shared_ptr<std::string> inputCode,std::shared_ptr<TokenFactory> tokenFactory);
    void scanTokens();
    private:
    bool match(char expectedChar);
    char peek() const;
    char peekNext() const;
    char advance();
    void addToken(std::unique_ptr<Token>  token);
    bool isAtEnd();
    bool isAlpha() const;
    bool isDigit() const;
    bool isWhiteSpace();
    void skipWhitSpace();
    bool isAlphaNumeric();
    std::string getIdentifier();
    std::string getNumber();
    std::string getString();
    // add function to check if the indentifier is a built in identifier or not
    bool isBuiltInIdentifier(std::string);
    std::shared_ptr<TokenFactory> m_tokenFactory;
    std::vector<std::unique_ptr<Token>> m_Tokens;
    int m_startIndex{0};
    int m_currentIndex{0};
    int m_line{1}; //with every new line increament this value to keep track of  line number
    static int m_currentLineNumber;
    std::shared_ptr<std::string> m_inputCode;
};


#endif