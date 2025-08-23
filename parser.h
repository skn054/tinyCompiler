#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include <stdbool.h> // for bool types

typedef struct{

    Lexer *lexer;
    Token *current_token;
    Token *next_token;

}Parser;


bool checkToken(Parser *parser,TokenType token);

Parser* initParser(Lexer *lexer);

Token* nextToken(Parser *parser);

void match(Parser *parser,TokenType token);
 
bool checkPeek(Parser *parser,TokenType type);

void program(Parser* parser);

void statement(Parser* parser);

void parser_nl(Parser *parser);

char* token_type_to_string(TokenType type);

void expression(Parser* parser);

#endif
