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
    printf("PROGRAM\n");
     while (checkToken(parser, NEWLINE)) {
        nextToken(parser);
    }
    while (!checkToken(parser,EOFL))
    {
        statement(parser);
        // printf("Token after statement is: %s\n", token_type_to_string(parser->current_token->type));
    }
    
}

void parser_nl(Parser *parser){
    printf("NEWLINE\n");
    match(parser,NEWLINE);
    while(checkToken(parser,NEWLINE)){
        nextToken(parser);
    }
}

void parser_abort(Parser *parser, const char *message) {
            fprintf(stderr, "Parsing Error: %s. Got token type %s with text '%s'\n", 
            message, 
            token_type_to_string(parser->current_token->type),
            parser->current_token->tokenText);
    exit(EXIT_FAILURE);
}

void statement(Parser *parser){
    printf("STATEMENT\n");
    if(checkToken(parser,PRINT)){
        printf("STATEMENT-PRINT\n");
        nextToken(parser);

        if(checkToken(parser,STRING)){
            nextToken(parser);
        }else{
            expression(parser);
        }       
    }
    else if(checkToken(parser,IF)){
        printf("STATEMENT-IF\n");
        nextToken(parser);
        comparison(parser);
        
        match(parser,THEN);
        parser_nl(parser);

        while (!checkToken(parser,ENDIF))
        {
            statement(parser);
        }
        
        match(parser,ENDIF);
        
    }
    else if(checkToken(parser,WHILE)){
        printf("STATEMENT-WHILE\n");
        nextToken(parser);
        
        comparison(parser);

        match(parser,REPEAT);
        parser_nl(parser);

        while (!checkToken(parser,ENDWHILE))
        {
            statement(parser);
        }

        match(parser,ENDWHILE);
        
    }
    else if(checkToken(parser,LABEL)){
        printf("STATEMENT-LABEL\n");
        nextToken(parser);
        match(parser,IDENT);

    }
     else if(checkToken(parser,GOTO)){
        printf("STATEMENT-GOTO\n");
        nextToken(parser);
        match(parser,IDENT);
        
    }
    else if(checkToken(parser,INPUT)){
        printf("STATEMENT-INPUT\n");
        nextToken(parser);
        match(parser,IDENT);
        
    }
    else if(checkToken(parser,LET)){
        printf("STATEMENT-LET\n");
        nextToken(parser);
        match(parser,IDENT);
        match(parser,EQ);
        expression(parser);     
    }

    else{
        parser_abort(parser, "Invalid statement");
    }

    parser_nl(parser);
}



void comparison(Parser *parser){

    printf("comparison");
    expression(parser);
    
    if(isComparisonOperator(parser)){
        nextToken(parser);
        expression(parser);
    }else{
        char error_message[100];
        snprintf(error_message, sizeof(error_message), "Expected comparison operator at: : %s", parser->current_token->tokenText);
        parser_abort(parser,error_message);
        
    }

    while(isComparisonOperator(parser)){
        nextToken(parser);
        expression(parser);
    }

}

void expression(Parser *parser){
    printf("EXPRESSION\n");
    term(parser);

    while (checkToken(parser,MINUS)|| checkToken(parser,PLUS))
    {   nextToken(parser);
        term(parser);
    }
    
}

void term(Parser *parser){
    printf("TERM\n");
    unary(parser);
    while(checkToken(parser,SLASH)|| checkToken(parser,ASTERISK)){
        nextToken(parser);
        unary(parser);
    }
}

void unary(Parser *parser){
    printf("UNARY\n");
    if(checkToken(parser,PLUS)|| checkToken(parser,MINUS)){
        nextToken(parser);
        
    }
    primary(parser);

}

void primary(Parser *parser){
    printf("PRIMARY %s \n", parser->current_token->tokenText);
    if(checkToken(parser,NUMBER)|| checkToken(parser,IDENT)){
        nextToken(parser);
    }else{
        char error_message[100];
        snprintf(error_message, sizeof(error_message), "Unexpected token at: %s", parser->lexer->currPosition);
        parser_abort(parser,error_message);
    }
}

bool isComparisonOperator(Parser *parser){
    
    if(checkToken(parser,EQEQ)|| checkToken(parser,NOTEQ)|| checkToken(parser,GT)|| checkToken(parser,GTEQ)||checkToken(parser,LT)|| checkToken(parser,LTEQ)){
        return true;

    }
    return false;
}


