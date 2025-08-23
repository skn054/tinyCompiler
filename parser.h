
#include "lexer.h"

typedef struct{

    Lexer *lexer;
    Token *current_token;
    Token *next_token;

}Parser;


bool checkToken(Parser *parser,TokenType token);

Parser* initParser(Lexer *lexer);

Token nextToken(Parser *parser);

void match(Parser *parser,TokenType token);
 


bool checkPeek(Parser *parser,TokenType type);
