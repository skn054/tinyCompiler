#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "lexer.h"

Lexer * initLexer(char *source){

    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->currPosition = -1;
    lexer->currChar = ' ';
    nextChar(lexer);  /// intialize currChar 
    return lexer;

}

int getsourceLength(char *source){
    return strlen(source);
}

char nextChar(Lexer *lexer){
    lexer->currPosition++;
    lexer->currChar = lexer->currPosition >=getsourceLength(lexer->source) ? '\0' : lexer->source[lexer->currPosition];

}

Token* createToken(char *tokenText,TokenType type){
    Token *token = malloc(sizeof(Token));
    token->tokenText = strdup(tokenText);
    token->type = type;
    return token;
}



Token* getToken(Lexer *lexer){
        skipWhiteSpaces(lexer);
        skipComments(lexer);
        char text = lexer->currChar;
        Token *token = NULL;

        if(text == '+'){
            token = createToken("+",PLUS);
        }
        else if(text == '-'){
            token = createToken("-",MINUS);
        }
        else if(text == '*'){
            token = createToken("*",ASTERISK);
        }
        else if(text == '/'){
            token = createToken("/",SLASH);
        }
        else if (text == '\n')
        {
           token = createToken("\'\'n",NEWLINE);
        }
        else if(text == '\0'){
            token = createToken("\0",EOFL);
        }
        else if (text == '=')
        {
           if(peek(lexer) == '='){
                char currText[3] = {lexer->currChar,peek(lexer),'\0'};
                nextChar(lexer);
                createToken(currText,EQEQ);
           }else{
            createToken("=",EQ);
           }
        }
        else if(text == '>'){
            if(peek(lexer) == '='){
                char currText[3] = {lexer->currChar,peek(lexer),'\0'};
                nextChar(lexer);
                createToken(currText,GTEQ);
           }else{
            createToken(">",GT);
           }
        }
        else if(text == '<'){
            if(peek(lexer) == '='){
                char currText[3] = {lexer->currChar,peek(lexer),'\0'};
                nextChar(lexer);
                createToken(currText,LTEQ);
           }else{
            createToken("<",LT);
           }
        }
        else if(text == '!'){
            if(peek(lexer) == '='){
                char currText[3] = {lexer->currChar,peek(lexer),'\0'};
                nextChar(lexer);
                createToken(currText,NOTEQ);
           }else{
                lexer_abort("Expected !=, got !");
           }
        }
        else if(isdigit(lexer->currChar)){
            int startPos = lexer->currPosition;
            nextChar(lexer);
            while(isdigit(lexer->currChar)){
                nextChar(lexer);
            }
            if(lexer->currChar == '.'){
                nextChar(lexer);
                if(!isdigit(lexer->currChar)){
                    //error
                    lexer_abort( "Illegal character in number");
                }
                while(isdigit(lexer->currChar)){
                    nextChar(lexer);
                }
            }
             int strLen = lexer->currPosition - startPos;
            char *strText = (char *)malloc(strLen + 1);
            if(!strText){
                lexer_abort("Memory allocation failed"); 
            }
            strncpy(strText,lexer->source + startPos, strLen);
            strText[strLen] = '\0';
            token = createToken(strText,NUMBER);
            free(strText);

        }
        else if(isalpha(lexer->currChar)){
            int startPos = lexer->currPosition;
            nextChar(lexer);
            while(isalnum(lexer->currChar)){
                nextChar(lexer);
            }
            int strLen = lexer->currPosition - startPos;
            char *strText = (char *)malloc(strLen + 1);
            if(!strText){
                lexer_abort("Memory allocation failed"); 
            }
            strncpy(strText,lexer->source + startPos, strLen);
            strText[strLen] = '\0';
            
            TokenType tokenType =  checkIfkeyWord(strText);
            createToken(strText,tokenType);
           
            free(strText);
        }
        else if(text == '"'){

            
            nextChar(lexer);
            int startPos = lexer->currPosition;
            while(lexer->currChar != '"'){
                //Error handling
                if(lexer->currChar == '\r' || lexer->currChar == '\n' || lexer->currChar == '\t' || lexer->currChar == '\\' || lexer->currChar == '%'){
                   lexer_abort( "Illegal character in string.");

                }
                nextChar(lexer);
            }
            int strLen = lexer->currPosition - startPos;
            char *strText = (char *)malloc(strLen + 1);
            if(!strText){
                lexer_abort("Memory allocation failed"); 
            }
            strncpy(strText,lexer->source + startPos, strLen);
            strText[strLen] = '\0';
            token = createToken(strText,STRING);
            free(strText);

        }
        else{
            lexer_abort("invalid symbol");
        }
        
      
}

TokenType checkIfkeyWord(char* text){
    const char *keywords[] = {
        "LABEL", "GOTO", "PRINT", "INPUT", "LET", "IF", "THEN", "ENDIF",
        "WHILE", "REPEAT", "ENDWHILE"
    };
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(text, keywords[i]) == 0) {
            return LABEL + i;
        }
    }
    return IDENT; 
}

void lexer_abort(char *message){
    fprintf(stderr, "Lexing Error: %s\n", message);
    exit(EXIT_FAILURE);
}

char peek(Lexer *lexer){
    int len = getsourceLength(lexer->source);
     if(lexer->currPosition + 1 >= len){
        return '\0';
    }else{
        return lexer->source[lexer->currPosition+1];
    }
    
}

void skipWhiteSpaces(Lexer *lexer){
    
    while(lexer->currChar == ' '|| lexer->currChar == '\t' || lexer->currChar == '\r'){
        nextChar(lexer);
    }
}

void skipComments(Lexer *lexer){
    if(lexer->currChar == '#'){
        while(lexer->currChar!='\n' && lexer->currChar!='\0'){
            nextChar(lexer);
        }
    }
}