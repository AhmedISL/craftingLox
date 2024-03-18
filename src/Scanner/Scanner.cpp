#include "Scanner.hpp"
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <exception>
#include <variant>

Scanner::Scanner(std::shared_ptr<std::string> inputCode)
                                        :m_inputCode(inputCode)
{
    std::cout << "initializing Scanner" << std::endl;
    TokenFactory::registerToken(TokenType::LBRACKET, [this](int lineNumber,std::string text){return std::make_unique<Token>("(",lineNumber, TokenType::LBRACKET,text);});
    TokenFactory::registerToken(TokenType::RBRACKET, [this](int lineNumber,std::string text){return std::make_unique<Token>("(",lineNumber, TokenType::LBRACKET,text);});
    TokenFactory::registerToken(TokenType::LSQUAREBRACKET, [this](int lineNumber,std::string text){return std::make_unique<Token>("[",lineNumber, TokenType::LSQUAREBRACKET,text);});
    TokenFactory::registerToken(TokenType::RSQUAREBRACKET, [this](int lineNumber,std::string text){return std::make_unique<Token>("]",lineNumber, TokenType::RSQUAREBRACKET,text);});
    TokenFactory::registerToken(TokenType::LCURLYBRACKET, [this](int lineNumber,std::string text){return std::make_unique<Token>("{",lineNumber, TokenType::LCURLYBRACKET,text);});
    TokenFactory::registerToken(TokenType::RCURLYBRACKET, [this](int lineNumber,std::string text){return std::make_unique<Token>("}",lineNumber, TokenType::RCURLYBRACKET,text);});
    TokenFactory::registerToken(TokenType::LANGLEBRACKET, [this](int lineNumber,std::string text){return std::make_unique<Token>("<",lineNumber, TokenType::LANGLEBRACKET,text);});
    TokenFactory::registerToken(TokenType::RANGLEBRACKET, [this](int lineNumber,std::string text){return std::make_unique<Token>(">",lineNumber, TokenType::RANGLEBRACKET,text);});
    TokenFactory::registerToken(TokenType::ADD, [this](int lineNumber,std::string text){return std::make_unique<Token>("+",lineNumber, TokenType::ADD,text);});
    TokenFactory::registerToken(TokenType::SUB, [this](int lineNumber,std::string text){return std::make_unique<Token>("-",lineNumber, TokenType::SUB,text);});
    TokenFactory::registerToken(TokenType::ASSIGNMENT, [this](int lineNumber,std::string text){return std::make_unique<Token>("=",lineNumber, TokenType::ASSIGNMENT,text);});
    TokenFactory::registerToken(TokenType::EQ, [this](int lineNumber,std::string text){return std::make_unique<Token>("==",lineNumber, TokenType::EQ,text);});
    TokenFactory::registerToken(TokenType::NOT, [this](int lineNumber,std::string text){return std::make_unique<Token>("!",lineNumber, TokenType::NOT,text);});
    TokenFactory::registerToken(TokenType::SEMICOLON, [this](int lineNumber,std::string text){return std::make_unique<Token>(";",lineNumber, TokenType::SEMICOLON,text);});
    TokenFactory::registerToken(TokenType::CMPL, [this](int lineNumber,std::string text){return std::make_unique<Token>("~",lineNumber, TokenType::CMPL,text);});
    TokenFactory::registerToken(TokenType::SUBEQ, [this](int lineNumber,std::string text){return std::make_unique<Token>("-=",lineNumber, TokenType::SUBEQ,text);});
    TokenFactory::registerToken(TokenType::SUBEQ, [this](int lineNumber,std::string text){return std::make_unique<Token>("--",lineNumber, TokenType::SUBEQ,text);});
    TokenFactory::registerToken(TokenType::ARROW, [this](int lineNumber,std::string text){return std::make_unique<Token>("->",lineNumber, TokenType::ARROW, text);});
    TokenFactory::registerToken(TokenType::DOT, [this](int lineNumber,std::string text){return std::make_unique<Token>(".",lineNumber, TokenType::DOT, text);});
    TokenFactory::registerToken(TokenType::ADDEQ, [this](int lineNumber,std::string text){return std::make_unique<Token>("+=",lineNumber, TokenType::ADDEQ, text);});
    TokenFactory::registerToken(TokenType::INC, [this](int lineNumber,std::string text){return std::make_unique<Token>("++",lineNumber, TokenType::INC, text);});
    TokenFactory::registerToken(TokenType::MUL, [this](int lineNumber,std::string text){return std::make_unique<Token>("*",lineNumber, TokenType::MUL, text);});
    TokenFactory::registerToken(TokenType::MULEQ, [this](int lineNumber,std::string text){return std::make_unique<Token>("*=",lineNumber, TokenType::MULEQ, text);});
    TokenFactory::registerToken(TokenType::BITOR, [this](int lineNumber,std::string text){return std::make_unique<Token>("|",lineNumber, TokenType::BITOR, text);});
    TokenFactory::registerToken(TokenType::OREQ, [this](int lineNumber,std::string text){return std::make_unique<Token>("|=",lineNumber, TokenType::OREQ, text);});
    TokenFactory::registerToken(TokenType::OR, [this](int lineNumber,std::string text){return std::make_unique<Token>("||",lineNumber, TokenType::OR, text);});
    TokenFactory::registerToken(TokenType::BITAND, [this](int lineNumber,std::string text){return std::make_unique<Token>("&",lineNumber, TokenType::BITAND, text);});
    TokenFactory::registerToken(TokenType::ANDEQ, [this](int lineNumber,std::string text){return std::make_unique<Token>("&=",lineNumber, TokenType::ANDEQ, text);});
    TokenFactory::registerToken(TokenType::AND, [this](int lineNumber,std::string text){return std::make_unique<Token>("&&",lineNumber, TokenType::AND, text);});
    TokenFactory::registerToken(TokenType::DIV, [this](int lineNumber,std::string text){return std::make_unique<Token>("/",lineNumber, TokenType::DIV, text);});
    TokenFactory::registerToken(TokenType::XOR, [this](int lineNumber,std::string text){return std::make_unique<Token>("^",lineNumber, TokenType::XOR, text);});
    TokenFactory::registerToken(TokenType::XOREQ, [this](int lineNumber,std::string text){return std::make_unique<Token>("^=",lineNumber, TokenType::XOREQ, text);});
    TokenFactory::registerToken(TokenType::LESSTHAN, [this](int lineNumber,std::string text){return std::make_unique<Token>("<",lineNumber, TokenType::LESSTHAN, text);});
    TokenFactory::registerToken(TokenType::LESSEQUAL, [this](int lineNumber,std::string text){return std::make_unique<Token>("<=",lineNumber, TokenType::LESSEQUAL, text);});
    TokenFactory::registerToken(TokenType::GREATERTHAN, [this](int lineNumber,std::string text){return std::make_unique<Token>(">",lineNumber, TokenType::GREATERTHAN, text);});
    TokenFactory::registerToken(TokenType::GREATEREQUAL, [this](int lineNumber,std::string text){return std::make_unique<Token>(">=",lineNumber, TokenType::GREATEREQUAL, text);});
    TokenFactory::registerToken(TokenType::COLON, [this](int lineNumber,std::string text){return std::make_unique<Token>(":",lineNumber, TokenType::COLON, text);});
    TokenFactory::registerToken(TokenType::COMMA, [this](int lineNumber,std::string text){return std::make_unique<Token>(",",lineNumber, TokenType::COMMA, text);});
    TokenFactory::registerToken(TokenType::ARROW, [this](int lineNumber,std::string text){return std::make_unique<Token>("->",lineNumber, TokenType::ARROW, text);});
    TokenFactory::registerToken(TokenType::TERNARY, [this](int lineNumber,std::string text){return std::make_unique<Token>("?",lineNumber, TokenType::TERNARY,text);});
    /*convert number text  to number value*/
    TokenFactory::registerToken(TokenType::NUMBER, [this](int lineNumber,std::string text){return std::make_unique<Token>(text,lineNumber, TokenType::LESSEQUAL, stoi(text));});
    TokenFactory::registerToken(TokenType::TEXT, [this](int lineNumber,std::string text){return std::make_unique<Token>("text",lineNumber, TokenType::TEXT,text);});
    TokenFactory::registerToken(TokenType::IDENTIFIER, [this](int lineNumber,std::string text){return std::make_unique<Token>(text,lineNumber, TokenType::IDENTIFIER,text);});
    TokenFactory::registerToken(TokenType::STRING, [this](int lineNumber,std::string text){return std::make_unique<Token>(text,lineNumber, TokenType::STRING, text);});
    TokenFactory::registerToken(TokenType::INT, [this](int lineNumber,std::string text){return std::make_unique<Token>("int",lineNumber, TokenType::INT,text);});
    TokenFactory::registerToken(TokenType::VOID, [this](int lineNumber,std::string text){return std::make_unique<Token>("void",lineNumber, TokenType::VOID,text);});
    TokenFactory::registerToken(TokenType::BOOL, [this](int lineNumber,std::string text){return std::make_unique<Token>("bool",lineNumber, TokenType::BOOL,text);});
    TokenFactory::registerToken(TokenType::CHAR, [this](int lineNumber,std::string text){return std::make_unique<Token>("char",lineNumber, TokenType::CHAR,text);});
    TokenFactory::registerToken(TokenType::FLOAT, [this](int lineNumber,std::string text){return std::make_unique<Token>("float",lineNumber, TokenType::FLOAT,stof(text));});
    TokenFactory::registerToken(TokenType::IF, [this](int lineNumber,std::string text){return std::make_unique<Token>("if",lineNumber, TokenType::IF,text);});
    TokenFactory::registerToken(TokenType::ELSE, [this](int lineNumber,std::string text){return std::make_unique<Token>("else",lineNumber, TokenType::ELSE,text);});
    TokenFactory::registerToken(TokenType::ELSEIF, [this](int lineNumber,std::string text){return std::make_unique<Token>("else if",lineNumber, TokenType::ELSEIF,text);});
    TokenFactory::registerToken(TokenType::SWITCH, [this](int lineNumber,std::string text){return std::make_unique<Token>("switch",lineNumber, TokenType::SWITCH,text);});
    TokenFactory::registerToken(TokenType::CASE, [this](int lineNumber,std::string text){return std::make_unique<Token>("case",lineNumber, TokenType::CASE,text);});
    TokenFactory::registerToken(TokenType::BREAK, [this](int lineNumber,std::string text){return std::make_unique<Token>("break",lineNumber, TokenType::BREAK,text);});
    TokenFactory::registerToken(TokenType::DEFAULT, [this](int lineNumber,std::string text){return std::make_unique<Token>("default",lineNumber, TokenType::DEFAULT,text);});
    TokenFactory::registerToken(TokenType::CLASS, [this](int lineNumber,std::string text){return std::make_unique<Token>("class",lineNumber, TokenType::CLASS,text);});
    TokenFactory::registerToken(TokenType::PRIVATE, [this](int lineNumber,std::string text){return std::make_unique<Token>("private",lineNumber, TokenType::PRIVATE,text);});
    TokenFactory::registerToken(TokenType::PUBLIC, [this](int lineNumber,std::string text){return std::make_unique<Token>("public",lineNumber, TokenType::PUBLIC,text);});
    TokenFactory::registerToken(TokenType::PROTECTED, [this](int lineNumber,std::string text){return std::make_unique<Token>("protected",lineNumber, TokenType::PROTECTED,text);});
    TokenFactory::registerToken(TokenType::VIRTUAL, [this](int lineNumber,std::string text){return std::make_unique<Token>("virtual",lineNumber, TokenType::VIRTUAL,text);});
    TokenFactory::registerToken(TokenType::OVERRIDE, [this](int lineNumber,std::string text){return std::make_unique<Token>("override",lineNumber, TokenType::OVERRIDE,text);});
    TokenFactory::registerToken(TokenType::FINAL, [this](int lineNumber,std::string text){return std::make_unique<Token>("final",lineNumber, TokenType::FINAL,text);});
    TokenFactory::registerToken(TokenType::DELETE, [this](int lineNumber,std::string text){return std::make_unique<Token>("delete",lineNumber, TokenType::DELETE,text);});
    TokenFactory::registerToken(TokenType::TRY, [this](int lineNumber,std::string text){return std::make_unique<Token>("try",lineNumber, TokenType::TRY,text);});
    TokenFactory::registerToken(TokenType::THROW, [this](int lineNumber,std::string text){return std::make_unique<Token>("throw",lineNumber, TokenType::THROW,text);});
    TokenFactory::registerToken(TokenType::CATCH, [this](int lineNumber,std::string text){return std::make_unique<Token>("catch",lineNumber, TokenType::CATCH,text);});
    TokenFactory::registerToken(TokenType::ENUM, [this](int lineNumber,std::string text){return std::make_unique<Token>("enum",lineNumber, TokenType::ENUM,text);});
    TokenFactory::registerToken(TokenType::UNION, [this](int lineNumber,std::string text){return std::make_unique<Token>("union",lineNumber, TokenType::UNION,text);});
    TokenFactory::registerToken(TokenType::STRUCT, [this](int lineNumber,std::string text){return std::make_unique<Token>("struct",lineNumber, TokenType::STRUCT,text);});
}

void Scanner::addToken(std::unique_ptr<Token> token){
    m_Tokens.push_back(std::move(token));
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

std::string Scanner::getNumber(){
    while (isDigit() && !isAtEnd()) {
        advance();
    }
    if(peek() == '.' && peekNext() >= '0' && peekNext() <= '9'){
        advance();
    }
    while (isDigit() && !isAtEnd()) {
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
            //Skip white space characters.
            skipWhitSpace();
            m_startIndex = m_currentIndex;
            TokenType t;
            std::string num_text = getNumber();
            //current token is number
            if(m_currentIndex != m_startIndex){
                //how to save the number Token statically ?
                addToken(TokenFactory::getToken(num_text, m_line, TokenType::NUMBER));
                /*Continue to start new  token*/
                continue;
            }
            char c = advance();
            switch (c) {
                case '-': 
                    if (match('=')) {
                        addToken(TokenFactory::getToken("-=", m_line, TokenType::SUBEQ));
                    }
                    else if(match('-')){
                        addToken(TokenFactory::getToken("--", m_line, TokenType::DEC));
                    }
                    else if (match('>')) {
                        addToken(TokenFactory::getToken("->", m_line, TokenType::ARROW));
                    }
                    else {
                        addToken(TokenFactory::getToken("-", m_line, TokenType::SUB));
                    }
                    break;
                case '+': 
                    if (match('=')){
                        addToken(TokenFactory::getToken("+=", m_line, TokenType::ADDEQ));
                    }
                    else if (match('+')){
                        addToken(TokenFactory::getToken("++", m_line, TokenType::INC));
                    }
                    else {
                        addToken(TokenFactory::getToken("+", m_line, TokenType::ADD));
                        }
                    break;
                case '*': 
                    if (match('=')){
                        addToken(TokenFactory::getToken("*=", m_line, TokenType::MULEQ));
                    }
                    else {
                        if (m_Tokens.back()->getTokenType() == TokenType::NUMBER || m_Tokens.back()->getTokenType() == TokenType::ASSIGNMENT \
                                    || m_Tokens.back()->getTokenType() == TokenType::IDENTIFIER) {
                            addToken(TokenFactory::getToken("*", m_line, TokenType::MUL));
                        }
                        else{
                            addToken(TokenFactory::getToken("*", m_line, TokenType::POINTER));
                        }
                        
                    }
                    break;
                /*indicating string*/
                case '"':
                    addToken(TokenFactory::getToken(getString(), m_line, TokenType::TEXT));
                    break;
                case '|':
                    if (match('|')){
                        addToken(TokenFactory::getToken("||", m_line, TokenType::OR));
                    }
                    else if (match('=')) {
                        addToken(TokenFactory::getToken("|=", m_line, TokenType::OREQ));
                    }
                    else{
                        addToken(TokenFactory::getToken("|", m_line, TokenType::BITOR));
                    }
                    break;
                case '&':
                    if (match('&')){
                        addToken(TokenFactory::getToken("&&", m_line, TokenType::AND));
                    }
                    else if (match('=')) {
                        addToken(TokenFactory::getToken("&=", m_line, TokenType::ANDEQ));
                    }
                    else{
                        addToken(TokenFactory::getToken("&", m_line, TokenType::BITAND));
                    }
                    break;
                case '^':
                    if (match('=')) {
                        addToken(TokenFactory::getToken("^=", m_line, TokenType::XOREQ));
                    }
                    else{
                        addToken(TokenFactory::getToken("^", m_line, TokenType::XOR));
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
                        addToken(TokenFactory::getToken("/", m_line, TokenType::DIV));
                    }
                    break;

                case '<':
                    if (match('=')){
                        addToken(TokenFactory::getToken("<=", m_line, TokenType::LESSEQUAL));
                    }
                    else if(match('<')){
                        addToken(TokenFactory::getToken("<<", m_line, TokenType::SHIFTLEFT));
                    }
                    else{
                        addToken(TokenFactory::getToken("<", m_line, TokenType::LESSTHAN));
                    }
                    break;
                case '>':
                    if (match('=')){
                        addToken(TokenFactory::getToken(">=", m_line, TokenType::GREATEREQUAL));
                    }
                    else if(match('>')){
                        addToken(TokenFactory::getToken(">>", m_line, TokenType::SHIFTRIGHT));
                    }
                    else {
                        addToken(TokenFactory::getToken(">", m_line, TokenType::GREATERTHAN));
                    }
                    break;

                case '=':
                    if(match('=')) {
                        addToken(TokenFactory::getToken("==", m_line, TokenType::EQ));
                    } else {
                        addToken(TokenFactory::getToken("=", m_line, TokenType::ASSIGNMENT));
                    }
                    break;

                case ':':
                    if (match(':')) {
                        addToken(TokenFactory::getToken("::", m_line, TokenType::SCOOPRESOLUTION));
                    }
                    else{
                        addToken(TokenFactory::getToken(":", m_line, TokenType::COLON));
                    }
                    break;
                case '?':
                    addToken(TokenFactory::getToken("?", m_line, TokenType::TERNARY));
                    break;
                default:
                    if(isAlphaNumeric()){
                        std::string s = getIdentifier();
                        bool isCatched = isBuiltInIdentifier(s);
                        if (!isCatched) {
                            throw  "Undefined identifier";
                        }
                    }
                break;
                
            }
        }
    }
    catch(std::exception & e){
        std::cout << "failed to scan input source code" << e.what()<<std::endl;
    }
}

bool Scanner::isBuiltInIdentifier(std::string lexem){
    TokenType type;
    std::string text;
    bool isBuiltIn = true;
    if(lexem =="int"){
        type = TokenType::INT;
        // m_tokenFactory->registerToken("int", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("int",lineNumber, TokenType::INT);});
    }
    else if(lexem=="void"){
        type = TokenType::VOID;
        // m_tokenFactory->registerToken("void", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("void",lineNumber, TokenType::VOID);});
    }
    else if(lexem == "string"){
        type = TokenType::STRING;
    }
    else if (lexem == "float") {
        type = TokenType::FLOAT;
        // m_tokenFactory->registerToken("float", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("float",lineNumber, TokenType::FLOAT);});
    }
    else if (lexem == "char") {
        type = TokenType::CHAR;
        // m_tokenFactory->registerToken("char", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("char",lineNumber, TokenType::CHAR);});
    }
    else if (lexem == "if") {
        type = TokenType::IF;
    }
    else if (lexem == "else") {
        /*confusion: is  else if should be handled as a single token or 2 separate  tokens? */
        skipWhitSpace();
        if(isAlphaNumeric()){
            std::string  ident = getIdentifier();
            if (ident == "if") {
                type = TokenType::ELSEIF;
                lexem = "else if";
                // m_tokenFactory->registerToken("else if", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("else if",lineNumber, TokenType::ELSEIF);});
            }
        }
        else{
            type = TokenType::ELSE;
            // m_tokenFactory->registerToken("else", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("else",lineNumber, TokenType::ELSE);});
        }
    }
    else if(lexem == "switch"){
        type = TokenType::SWITCH;
        // m_tokenFactory->registerToken("switch", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("switch",lineNumber, TokenType::SWITCH);});
    }
    else if(lexem == "case"){
        type = TokenType::CASE;
        // m_tokenFactory->registerToken("case", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("case",lineNumber, TokenType::CASE);});
    }
    else if(lexem == "default"){
        type = TokenType::DEFAULT;
        // m_tokenFactory->registerToken("default", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("default",lineNumber, TokenType::DEFAULT);});
    }
    else if (lexem == "break") {
        type = TokenType::BREAK;
    }
    else if (lexem == "class") {
        type = TokenType::CLASS;
        // m_tokenFactory->registerToken("class", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("class", lineNumber, TokenType::CLASS);});
    }
    else if(lexem == "private"){
        type = TokenType::PRIVATE;
        // m_tokenFactory->registerToken("private", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("private", lineNumber, TokenType::PRIVATE);});
    }
    else if(lexem == "public"){
        type = TokenType::PUBLIC;
        // m_tokenFactory->registerToken("public", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("public", lineNumber, TokenType::PUBLIC);});
    }
    else if(lexem == "protected"){
        type = TokenType::PROTECTED;
        // m_tokenFactory->registerToken("protected", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("protected", lineNumber, TokenType::PROTECTED);});
    }
    else if(lexem == "virtual"){
        type = TokenType::VIRTUAL;
        // m_tokenFactory->registerToken("virtual", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("virtual", lineNumber, TokenType::VIRTUAL);});
    }
    else if(lexem == "override"){
        type = TokenType::OVERRIDE;
        // m_tokenFactory->registerToken("override", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("override", lineNumber, TokenType::OVERRIDE);});
    }
    else if(lexem == "final"){
        type = TokenType::FINAL;
        // m_tokenFactory->registerToken("final", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("final", lineNumber, TokenType::FINAL);});
    }
    else if(lexem == "delete"){
        type = TokenType::DELETE;
        // m_tokenFactory->registerToken("delete", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("delete", lineNumber, TokenType::DELETE);});
    }
    else if(lexem == "try"){
        type = TokenType::TRY;
        // m_tokenFactory->registerToken("try", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("try", lineNumber, TokenType::TRY);});
    }
    else if(lexem == "throw"){
        type = TokenType::THROW;
        // m_tokenFactory->registerToken("throw", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("throw", lineNumber, TokenType::THROW);});
    }
    else if(lexem == "catch"){
        type = TokenType::CATCH;
        // m_tokenFactory->registerToken("catch", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("catch", lineNumber, TokenType::CATCH);});
    }
    else if(lexem == "union"){
        type = TokenType::UNION;
        // m_tokenFactory->registerToken("catch", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("catch", lineNumber, TokenType::CATCH);});
    }
    else if(lexem == "struct"){
        type = TokenType::STRUCT;
        // m_tokenFactory->registerToken("catch", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("catch", lineNumber, TokenType::CATCH);});
    }
    else if (lexem == "enum") {
        type  = TokenType::ENUM;
    }
    else{
        type = TokenType::IDENTIFIER;
        isBuiltIn = false;
    }
    addToken(TokenFactory::getToken(lexem, m_line, type));
    return isBuiltIn;
}