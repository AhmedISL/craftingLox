#include "Scanner.hpp"
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <exception>
#include <variant>

Scanner::Scanner(std::shared_ptr<std::string> inputCode, std::shared_ptr<TokenFactory> tokenFactory)
                                        :m_inputCode(std::move(inputCode)),m_tokenFactory(tokenFactory)
{
    std::cout << "initializing Scanner" << std::endl;
    tokenFactory->registerToken("(", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("(",lineNumber, TokenType::LBRACKET);});
    tokenFactory->registerToken(")", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("(",lineNumber, TokenType::LBRACKET);});
    tokenFactory->registerToken("[", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("[",lineNumber, TokenType::LSQUAREBRACKET);});
    tokenFactory->registerToken("]", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("]",lineNumber, TokenType::RSQUAREBRACKET);});
    tokenFactory->registerToken("{", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("{",lineNumber, TokenType::LCURLYBRACKET);});
    tokenFactory->registerToken("}", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("}",lineNumber, TokenType::RCURLYBRACKET);});
    tokenFactory->registerToken("<", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("<",lineNumber, TokenType::LANGLEBRACKET);});
    tokenFactory->registerToken(">", [this](int lineNumber,std::string text){return m_tokenFactory->getToken(">",lineNumber, TokenType::RANGLEBRACKET);});
    tokenFactory->registerToken("+", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("+",lineNumber, TokenType::ADD);});
    tokenFactory->registerToken("-", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("-",lineNumber, TokenType::SUB);});
    tokenFactory->registerToken("=", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("=",lineNumber, TokenType::ASSIGNMENT);});
    tokenFactory->registerToken("!", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("!",lineNumber, TokenType::NOT);});
    tokenFactory->registerToken(";", [this](int lineNumber,std::string text){return m_tokenFactory->getToken(";",lineNumber, TokenType::SEMICOLON);});
    tokenFactory->registerToken("~", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("~",lineNumber, TokenType::CMPL);});
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
                addToken(m_tokenFactory->createToken(num_text, m_line,TokenType::NUMBER));
                /*Continue to start new  token*/
                continue;
            }
            char c = advance();
            switch (c) {
                case '-': 
                    if (match('=')) {
                        addToken(m_tokenFactory->createToken("-=", m_line,TokenType::SUBEQ));
                    }
                    else if(match('-')){
                        addToken(m_tokenFactory->createToken("--", m_line,TokenType::DEC));
                    }
                    else if (match('>')) {
                        addToken(m_tokenFactory->createToken("->", m_line,TokenType::ARROW));
                    }
                    else {
                        addToken(m_tokenFactory->createToken("-", m_line,TokenType::SUB)); 
                    }
                    break;
                case '+': 
                    if (match('=')){
                        addToken(m_tokenFactory->createToken("+=", m_line,TokenType::ADDEQ));
                    }
                    else if (match('+')){
                        addToken(m_tokenFactory->createToken("++", m_line,TokenType::INC));
                    }
                    else {
                        addToken(m_tokenFactory->createToken("+", m_line,TokenType::ADD));
                        }
                    break;
                case '*': 
                    if (match('=')){
                        addToken(m_tokenFactory->createToken("*=", m_line,TokenType::MULEQ));
                    }
                    else {
                        addToken(m_tokenFactory->createToken("*", m_line,TokenType::MUL));
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
                case '^':
                    if (match('=')) {
                        addToken(m_tokenFactory->createToken("^=", m_line, TokenType::XOREQ));
                    }
                    else{
                        addToken(m_tokenFactory->createToken("^", m_line,TokenType::XOR));
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

                case '<':
                    if (match('=')){
                        addToken(m_tokenFactory->createToken("<=", m_line,TokenType::LESSEQUAL));
                    }
                    else if(match('<')){
                        addToken(m_tokenFactory->createToken("<<", m_line,TokenType::SHIFTLEFT));
                    }
                    else{
                        addToken(m_tokenFactory->createToken("<", m_line,TokenType::LESSTHAN));
                    }
                    break;
                case '>':
                    if (match('=')){
                        addToken(m_tokenFactory->createToken(">=", m_line, TokenType::GREATEREQUAL));
                    }
                    else if(match('>')){
                        addToken(m_tokenFactory->createToken(">>", m_line,TokenType::SHIFTRIGHT));
                    }
                    else {
                        addToken(m_tokenFactory->createToken(">", m_line, TokenType::GREATERTHAN));
                    }
                    break;

                case '=':
                    if(match('=')) {
                        addToken(m_tokenFactory->createToken("==", m_line, TokenType::EQ));
                    } else {
                        addToken(m_tokenFactory->createToken("=", m_line, TokenType::ASSIGNMENT));
                    }
                    break;

                case ':':
                    if (match(':')) {
                        addToken(m_tokenFactory->createToken("::", m_line, TokenType::SCOOPRESOLUTION));
                    }
                    else{
                        addToken(m_tokenFactory->createToken(":", m_line,TokenType::COLON));
                    }
                    break;
                /*QUESTION CONFUSED ABOUT THE * HOW TO CLARIFY IF POINTER OR MULTIPLICATION*/
                // case '*':
                //     if (peekNext() == '=')
                //     addToken(m_tokenFactory->createToken(s, 0,TokenType::POINTER));  break; 
                default:
                    if(isAlphaNumeric()){
                        std::string s = getIdentifier();
                        isBuiltInIdentifier(s);
                    }
                    else{
                        std::string s_c(1,c);
                        /*dummy value for token type as it is already registed by its read type*/
                        addToken(m_tokenFactory->createToken(s_c, m_line));
                    }
                //most probably new var or built in identifier need to be regestered ?
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
    else if (lexem == "float") {
        type = TokenType::FLOAT;
        // m_tokenFactory->registerToken("float", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("float",lineNumber, TokenType::FLOAT);});
    }
    else if (lexem == "char") {
        type = TokenType::CHAR;
        // m_tokenFactory->registerToken("char", [this](int lineNumber,std::string text){return m_tokenFactory->getToken("char",lineNumber, TokenType::CHAR);});
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
    else if(lexem == "uniion"){
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
        // return false;
        type = TokenType::IDENTIFIER;
        isBuiltIn = false;
    }
    addToken(m_tokenFactory->createToken(lexem, m_line, type));
    return isBuiltIn;
}