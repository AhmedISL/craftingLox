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
    static void registerToken(std::string lexem, std::function<void (std::string, TokenType)> cbk);
    static void unregisterToken(std::string lexem);
    static std::shared_ptr<Token> createToken(std::string lexem, int lineNo, TokenType type);
    private:
    static std::unordered_map<std::string, std::function<std::shared_ptr<Token>(std::string,TokenType)>> m_TokenMap;
    // std::function<std::shared_ptr<Token>(int line)>  isOrOperator = 
    //                                                         [](int lineNo){
    //                                                             std::shared_ptr<Token> t_ptr = std::make_shared<Token>(TokenType::OR, lineNo,"||","||");
    //                                                             return t_ptr;
    //                                                         };
    
};

#endif