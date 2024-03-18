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
    TokenFactory() = delete;
    ~TokenFactory() = default;
    static void registerToken(TokenType type, tokenCallback cbk);
    static void unregisterToken(TokenType type);
    static std::unique_ptr<Token> getToken(std::string,int,TokenType);
    private:
    static std::unordered_map<TokenType, tokenCallback> m_TokenMap;
    
};

#endif