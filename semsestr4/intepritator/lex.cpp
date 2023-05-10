#include <string.h>
#include <iostream>

#include "lex.hpp"

Value::Value(int n)
{
    str = NULL;
    num = n;
}

Value::Value(char *s)
{
    num = 0;
    str = s;
}


const char *Lex::lexis[] = {
    "",
    "program",
    "int",
    "string",
    "if",
    "else",
    "while",
    "read",
    "write",
    "and",
    "not",
    "or",
    /*DELIMETERS*/
    "(",
    ")",
    "{",
    "}",
    ",",
    ";",
    "=",
    "+",
    "-",
    "*",
    "/",
    "<",
    ">",
    "<=",
    ">=",
    "==",
    "!="
};

const char *Lex::getLexis()
{
    return lexis[type];
}

type_of_lex Lex::getType()
{
    return type;
}

Value Lex::getValue()
{
    return val;
}

Lex::Lex(type_of_lex t, Value v)
{
    type = t;
    if (type == LEX_STR){
        val = new char[strlen(v.str) + 1];
        strcpy(val.str, v.str);
    } else {
        val = v;
    }
}

Lex::~Lex()
{
    if (type == LEX_STR)
        delete [] val.str;
}

type_of_lex Lex::getKeyword(const char *str)
{
    for (int i = LEX_NULL; i <= LEX_OR; ++i){
        if (!strcmp(str, lexis[i]))
            return static_cast<type_of_lex>(i);
    }
    return LEX_NULL;
}

type_of_lex Lex::getDelim(const char *str)
{
    for (int i = LEX_LPAREN; i <= LEX_NEQ; ++i){
        if (!strcmp(str, lexis[i]))
            return static_cast<type_of_lex>(i);
    }
    return LEX_NULL;
}
