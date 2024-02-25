#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include "Token.hpp"
#include <map>
#include <unordered_map>

#ifndef TOKENFACTORY_HPP__
#define TOKENFACTORY_HPP__

typedef std::function<std::unique_ptr<Token>(int,std::string)> tokenCallback;

class  TokenFactory {
    public:
    TokenFactory() = default;
    ~TokenFactory() = default;
    static void registerToken(std::string lexem, tokenCallback cbk);
    static void unregisterToken(std::string lexem);
    //add literal value
    static std::unique_ptr<Token> createToken(std::string lexem, int lineNo, TokenType type = TokenType::UNKNOWN);
    static std::unique_ptr<Token> getToken(std::string,int,TokenType);
    private:
    static std::unordered_map<std::string, tokenCallback> m_TokenMap;
    
};

#endif