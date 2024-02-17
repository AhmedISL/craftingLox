#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include "Token.hpp"
#include <map>
#include <unordered_map>

#ifndef TOKENFACTORY_HPP__
#define TOKENFACTORY_HPP__

class  TokenFactory {
    public:
    TokenFactory() = default;
    ~TokenFactory() = default;
    static void registerToken(std::string lexem, std::function<std::shared_ptr<Token> (int,std::string)> cbk);
    static void unregisterToken(std::string lexem);
    //add literal value
    static std::shared_ptr<Token> createToken(std::string lexem, int lineNo, TokenType type);
    private:
    static std::unordered_map<std::string, std::function<std::shared_ptr<Token>(int, std::string)>> m_TokenMap;
    
};

#endif