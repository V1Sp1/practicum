#ifndef LEX_HPP
#define LEX_HPP

enum type_of_lex {
    LEX_NULL,
    LEX_PROGRAM,
    LEX_INT,
    LEX_STRING,
    LEX_IF,
    LEX_ELSE,
    LEX_WHILE,
    LEX_READ,
    LEX_WRITE,
    LEX_AND,
    LEX_NOT,
    LEX_OR,
    /*DELIMETERS*/
    LEX_LPAREN,
    LEX_RPAREN,
    LEX_LBRACE,
    LEX_RBRACE,
    LEC_COMMA,
    LEX_SEMICOLON,
    LEX_ASSIGN,
    LEX_PLUS,
    LEX_MINUS,
    LEX_TIMES,
    LEX_SLASH,
    LEX_LSS,
    LES_GTR,
    LEX_LEQ,
    LEX_GEQ,
    LEX_EQ,
    LEX_NEQ,
    /*CONSTANT*/
    LEX_NUM,
    LEX_STR,
    /*IDENTIFIER*/
    LEX_ID,
    LEX_FIN
};

union Value {
    char *str;
    int num;
    Value(int n = 0);
    Value(char *s);
};

//==================  class Lex  ==================//
 
class Lex
{
  type_of_lex type;
  static const char *lexis[];
  Value val;
public:
    Lex(type_of_lex t = LEX_NULL, Value v = (int) 0);
    
    const char *getLexis();
    type_of_lex  getType();
    Value getValue(); 
    
    static type_of_lex getKeyword(const char *str);
    static type_of_lex getDelim(const char *str);
    
    ~Lex();
};

#endif
