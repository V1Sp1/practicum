#ifndef IDENT_HPP
#define IDENT_HPP


//==================  class Ident  ==================//
 
class Ident
{
    char *name;
    bool declare;
    type_of_lex  type;
    bool assign;
    Value val;
public:
    Ident();

    char *getName();
    void putName(const char *n);
    bool getDeclare();
    void putDeclare();

    type_of_lex getType();
    void putType(type_of_lex t);

    bool getAssign();
    void putAssign();

    Value getValue();
    void putValue(Value v);
};


//==================  class TablIdent  ==================//
 
class TablIdent
{
    Ident *p;
    int size;
    int top;
public:
    TablIdent(int max_size);
    ~TablIdent();
    Ident& operator[]( int k );
    int put(const char *buf);
};

#endif
