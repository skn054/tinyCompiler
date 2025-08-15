#include<stdio.h>
#include<stdlib.h>
#include"lexer.h"


void main(){
    // char *source = "+- */";
    char *source =  "+- */ >>= = !=";
    Lexer *lexer = initLexer(source);
    // char c;
    // while ((c = (int)nextChar(lexer))!=-1)
    // {
    //     printf("%c\n",c);
    // }
    Token *token;
    while((token = getToken(lexer))->type !=EOFL){
        printf("%s %d\n", token->tokenText,token->type);
        
        nextChar(lexer);
    }
    

}