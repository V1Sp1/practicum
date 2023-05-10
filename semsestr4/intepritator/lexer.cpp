#include <iostream>

#include "lex.hpp"
#include "ident.hpp"
#include "scanner.hpp"

using namespace std;

int main()
{
    type_of_lex type;
    Lex *lexem;
    TablIdent TID(128);
    Scanner scan(stdin ,TID);
    try {
        while(true){
            lexem = scan.getLex();
            type = lexem->getType();
            cout << "Type of lexem: " << type << " ";
            if (type == LEX_FIN) {
                delete lexem;
                break;
            } else if (type == LEX_NUM){
                cout << "value: " << (lexem->getValue()).num << endl;
            } else if (type == LEX_STR){
                cout << "value: " << (lexem->getValue()).str << endl;
            } else if (type == LEX_ID){
                cout << "identifier name: " << TID[(lexem->getValue()).num].getName() << endl;
            } else {
                cout << "keyword name: " << lexem->getLexis() << endl;
            }
            delete lexem;
        }
    } catch (const char *err){
        cout << err << endl;
    }
    return 0;
}
