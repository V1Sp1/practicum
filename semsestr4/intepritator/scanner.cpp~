#include <iostream>
#include <ctype.h>
#include <string.h>

#include "scanner.hpp"


//==================  class Scanner  ==================//
 
void Scanner::clear()
{
    buf_top = 0;
    for (int j = 0; j < 256; ++j)
        buf[j] = '\0';
}

void Scanner::reset()
{
    CS = H;
    clear();
}

Scanner::Scanner(FILE *program, TablIdent& tid)
    : CS(H), TID(tid), fp(program), c('\0'), buf_top(0)
{
    clear();
    gc();
}

void Scanner::add()
{
    if (buf_top >= 255)
        throw "Command is to long\n";
    buf[buf_top] = c;
    ++buf_top;
}
                 
void Scanner::gc()
{
    c = fgetc (fp);
}

Lex *Scanner::getLex () 
{
    int d = 0;
    int tmp;
    type_of_lex type;
    bool isNeg = false;

    while(true){
        switch(CS){
            case H:
                if (c == EOF) 
                    return new Lex(LEX_FIN);
                else if ( c==' ' || c == '\n' || c== '\r' || c == '\t' ){
                    gc();
                } else if ( isdigit(c) ){
                    d = c - '0';
                    gc();
                    CS = NUM;
                } else if (isalpha(c)){
                    clear();
                    add();
                    gc();
                    CS = IDENT;
                } else if ( c== '"' ){
                    clear();
                    gc();
                    CS = STR;
                } else if ( c== '=' || c== '<' || c== '>' ){ 
                    clear(); 
                    add(); 
                    gc(); 
                    CS = ALE; 
                } else if (c == '!'){
                    clear();
                    add();
                    gc();
                    CS = NEQ;
                } else if (c == '/'){
                    clear();
                    add();
                    gc();
                    CS = ISCOM;
                } else if ((c == '+') || (c == '-')){
                    clear();
                    add();
                    isNeg = (c == '-');
                    gc();
                    CS = ISNUM;
                } else{
                    clear();
                    add();
                    CS = DELIM;
                }
                break;
            case SIGN:
                if (isalpha(c) || isdigit(c)){
                    CS = DELIM;
                }
                CS = H;
                break;
            case IDENT:
                if (isalpha(c) || isdigit(c)){
                    add(); 
                    gc();
                } else {
                    tmp = c;
                    c = '\0';
                    add();
                    c = tmp;
                    CS = SIGN;
                    type = Lex::getKeyword(buf);
                    if (type != LEX_NULL){
                        return new Lex(type);
                    } else {
                        d = TID.put(buf);
                        return new Lex(LEX_ID, d);
                    }
                }
                break;
            case NUM:
                if (isdigit(c)){
                    if (isNeg)
                        d = d * 10 - (c - '0');
                    else
                        d = d * 10 + (c - '0');
                    gc();
                } else {
                    CS = SIGN;
                    return new Lex(LEX_NUM, d);
                }
                break;
            case ISNUM:
                if (isdigit(c)){
                    if (isNeg)
                        d = -(c - '0');
                    else
                        d = c - '0';
                    gc();
                    CS = NUM;
                } else {
                    tmp = c;
                    c = '\0';
                    add();
                    c = tmp;
                    CS = H;
                    type = Lex::getDelim(buf);
                    return new Lex(type);
                }
                break;
            case STR:
                if (c == EOF){
                    throw "expected \" in string\n";
                } else if (c == '"'){
                    c = '\0';
                    add();
                    CS = H;
                    gc();
                    return new Lex(LEX_STR, buf);
                } else {
                    add();
                    gc();
                }
                break;
            case ISCOM:
                if (c == '*'){ 
                CS = COM;
                } else {
                    CS = H;
                    return new Lex(LEX_SLASH);
                }
                break;
            case COM:
                if ( c == EOF ){
                    CS = H;
                    throw "expected \" in string\n";
                } else if (c == '*'){
                    gc();
                    CS = ENDCOM;
                } else {
                    gc();
                }
                break;
            case ENDCOM:
                if (c == '/')
                    CS = H;
                else {
                    CS = COM;
                }
                gc();
                break;
            case ALE:
                if ( c == '='){
                    add();
                    gc();
                }
                tmp = c;
                c = '\0';
                add();
                c = tmp;
                CS = H;
                type = Lex::getDelim(buf);
                return new Lex(type);   
            case NEQ:
                if (c == '='){
                    gc();
                    CS = H;
                    return new Lex(LEX_NEQ);
                } else {
                    throw "expected !=\n";
                }
                break;
            case DELIM:
                tmp = c;
                c = '\0';
                add();
                c = tmp;
                type = Lex::getDelim(buf);
                if (type != LEX_NULL){
                    if (type == LEX_RPAREN) {
                    CS = SIGN;
                    } else
                        CS = H;
                    gc();
                    return new Lex(type);
                } else {
                    throw "Not such symbols in Delimiters!\n";
                }
                break;
        }//end switch
    }
    throw "Undefined symbol\n";
}
