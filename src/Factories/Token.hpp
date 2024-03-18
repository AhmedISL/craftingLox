

#ifndef TOKEN_HPP__
#define TOKEN_HPP__

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>
#include "../common/TokenType.hpp"

using litralOptions = std::variant<std::monostate, int, std::string, long, float, double, bool>;

class  Token {
    public:
    Token() = delete;
    Token(std::string lexem, int line, TokenType type, litralOptions litral);
    TokenType getTokenType();

    private:
    TokenType m_type;
    int m_line;
    std::string m_lexem;
    litralOptions m_litral;
};

#endif