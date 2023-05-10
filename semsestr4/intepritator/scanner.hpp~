#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iostream>

#include "lexem.hpp"
#include "ident.hpp"


//==================  class Scanner  ==================//
 
class Scanner
{
    enum state { H, IDENT, NUM, ISNUM, ISCOM, COM, ENDCOM, ALE, DELIM, NEQ, STR, SIGN };
    state CS;

    TablIdent& TID;
    FILE *fp;
    int c;
    char buf [ 256 ];
    int buf_top;
         
    void clear ();
    void add ();       
    void gc();

    void reset();

public:
    Scanner(FILE *program, TablIdent& tid);

    Lex *getLex ();
};

#endif
