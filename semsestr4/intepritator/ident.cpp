#include <iostream>
#include <string.h>

#include "ident.hpp"


//==================  class Ident  ==================// 

Ident::Ident() 
{
    declare = false;
    assign = false;
}

char *Ident::getName()
{
    return name;
}

void Ident::putName(const char *n)
{
    name = new char [ strlen(n)+1];
    strcpy(name,n);
}



bool Ident::getDeclare()
{
    return declare;
}

void Ident::putDeclare()
{
    declare = true;
}

type_of_lex Ident::getType()
{
    return type;
}

void Ident::putType(type_of_lex t)
{
    type = t;
}

bool Ident::getAssign()
{
    return assign;
}

void Ident::putAssign()
{
    assign = true;
}

Value Ident::getValue()
{
    return val;
}

void Ident::putValue(Value v)
{
    val = v;
}


//==================  class TablIdent  ==================//

TablIdent::TablIdent(int max_size)
{
    p = new Ident[size = max_size];
    top = 1;
}

TablIdent::~TablIdent() { delete [] p; }
    
Ident& TablIdent::operator[]( int k ) { return p[k]; }



int TablIdent::put ( const char *buf )
{
  for ( int j = 1; j < top; j++ )
    if (!strcmp (buf, p[j].getName()))
      return j;
  p[top].putName(buf);
  ++top;
  return top-1;
}
 