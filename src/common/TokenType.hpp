#include <cstdint>
#include <iostream>
#include <map>

enum class TokenType :  uint8_t 
{
    /*data types*/
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    BOOL,
    STRING,
    AUTO,
    NUMBER,
    /*CONTAINERS*/
    STRUCT,         //struct
    UNION,          //union
    ENUM,           //enum
    VECTOR,         //vector<>
    MAP,             //map<K,V>
    QUEUE,          //queue<>
    STACK,          //stack<>
    /*Variables*/
    IDENTIFIER,
    /*Operations*/
    ADD,            //+
    SUB,            //-
    MUL,            //*
    DIV,            ///< Division >
    AND,            //&&
    OR,             //||
    NOT,            //!
    EQ,             //==
    GREATERTHAN,    //>
    LESSTHAN,       //<
    GREATEREQUAL,   //>=
    LESSEQUAL,      //<=
    NEQ,            //!=
    ASSIGNMENT,     //=
    INC,            //++
    DEC,            //--
    SHIFTLEFT,      //<<
    SHIFTRIGHT,     //>>
    ADDEQ,          //+=
    SUBEQ,          //-=
    MULEQ,          //*=
    /*BIT OPERTATORS*/
    BITAND,         //&
    BITOR,          //|
    XOR,            //^
    CMPL,           //~
    ANDEQ,          //&=
    OREQ,           //|=
    XOREQ,          //^=
    /*built_in IDENTIFIERS*/
    IF,
    ELSE,
    ELSEIF,
    DO,
    SWITCH,
    CASE,
    RETURN,
    BREAK,
    FOR,
    WHILE,
    VOID,
    CONTINUE,
    /*scoops*/
    LBRACKET,       //(
    RBRACKET,       //)
    LCURLYBRACKET,  //{
    RCURLYBRACKET,  //}
    LSQUAREBRACKET, //[
    RSQUAREBRACKET, //]
    LANGLEBRACKET,  //<
    RANGLEBRACKET,  //>
    COLON,          //: {member initializer list, inheritance, looping using iterators}
    SCOOPRESOLUTION,//::
    SEMICOLON,      //;
    COMMA,          //,
    QUOTE,          //"
    // POINTER,        //*       ->shouldn't be handled in scanning phase
    DOT,            //.
    ARROW,          //->
    /*MACRO*/
    HASH,           //#
    /*DEFINITIONS*/
    DEFINE,
    USING,
    INCLUDE,
    TYPEDEF,
    NAMESPACE,
    CLASS,
    PRIVATE,
    PROTECTED,
    PUBLIC,
    VIRTUAL,
    OVERRIDE,
    FINAL,
    DELETE,
    DEFAULT,
    TRY,
    THROW,
    CATCH,
    NULL_PTR,
    UNKNOWN
};