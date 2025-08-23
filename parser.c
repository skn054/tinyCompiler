#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "lexer.h"
#include "parser.h"


Parser* initParser(Lexer *lexer){
    Parser *parser = malloc(sizeof(Parser));
    if(parser == NULL){
        perror("Memory allocation failed for Parser"); exit(EXIT_FAILURE); 
    }
    parser->lexer = lexer;
    parser->current_token = NULL;
    parser->next_token = NULL;
    nextToken(parser);
    nextToken(parser);
    return parser;
}

Token* nextToken(Parser *parser){

    parser->current_token = parser->next_token;
    parser->next_token = getToken(parser->lexer);

}

bool checkToken(Parser *parser,TokenType tokenType){
    return parser->current_token->type == tokenType;
}

void match(Parser *parser,TokenType tokenType){
    if(!checkToken(parser,tokenType)){
        char error_message[100]; // Adjust size if needed
        snprintf(error_message, sizeof(error_message), "Expected %s, got %s", token_type_to_string(tokenType), token_type_to_string(parser->current_token->type));
    }
    nextToken(parser);
}

char* token_type_to_string(TokenType type){

    switch (type)
    {
    case EOFL:
        return "EOFL";
    case NEWLINE: return "NEWLINE";
        case NUMBER: return "NUMBER";
        case IDENT: return "IDENT";
        case STRING: return "STRING";
        case LABEL: return "LABEL";
        case GOTO: return "GOTO";
        case PRINT: return "PRINT";
        case INPUT: return "INPUT";
        case LET: return "LET";
        case IF: return "IF";
        case THEN: return "THEN";
        case ENDIF: return "ENDIF";
        case WHILE: return "WHILE";
        case REPEAT: return "REPEAT";
        case ENDWHILE: return "ENDWHILE";
        case EQ: return "=";
        case PLUS: return "+";
        case MINUS: return "-";
        case ASTERISK: return "*";
        case SLASH: return "/";
        case EQEQ: return "==";
        case NOTEQ: return "!=";
        case LT: return "<";
        case LTEQ: return "<=";
        case GT: return ">";
        case GTEQ: return ">=";
        default: return "UNKNOWN_TOKEN_TYPE";
    
    
    }

}

bool checkPeek(Parser *parser,TokenType tokenType){
     return parser->next_token->type == tokenType;
}


void program(Parser *parser){
    printf("PROGRAM");
     while (checkToken(parser, NEWLINE)) {
        nextToken(parser);
    }
    while (!checkToken(parser,EOFL))
    {
        statement(parser);
    }
    
}

void parser_nl(Parser *parser){

    match(parser,NEWLINE);
    while(checkToken(parser,NEWLINE)){
        nextToken(parser);
    }
}

void statement(Parser *parser){
    printf("STATEMENT");
    if(checkToken(parser,PRINT)){
        nextToken(parser);

        if(checkToken(parser,STRING)){
            nextToken(parser);
        }else{
            expression(parser);
        }

        parser_nl(parser);
    }
}

void expression(Parser *parser){

}


