#ifndef LEXER_H
#define LEXER_H


typedef enum {
    EOFL = -1,
	NEWLINE = 0,
	NUMBER = 1,
	IDENT = 2,
	STRING = 3,
	LABEL = 101,
	GOTO = 102,
	PRINT = 103,
	INPUT = 104,
	LET = 105,
	IF = 106,
	THEN = 107,
	ENDIF = 108,
	WHILE = 109,
	REPEAT = 110,
	ENDWHILE = 111,
	EQ = 201,
	PLUS = 202,
	MINUS = 203,
	ASTERISK = 204,
	SLASH = 205,
	EQEQ = 206,
	NOTEQ = 207,
	LT = 208,
	LTEQ = 209,
	GT = 210,
	GTEQ = 211

}TokenType;


typedef struct {
    char *tokenText;
    TokenType type;
}Token;


typedef struct {
    char *source;
    int currPosition;
    char currChar;
   

}Lexer;

char peek(Lexer *lexer);

TokenType checkIfkeyWord(char *text);

Lexer* initLexer(char *source);

void skipWhiteSpaces(Lexer *lexer);

void skipComments(Lexer *lexer);

char nextChar(Lexer *lexer);

Token* createToken(char *tokenText,TokenType type);
Token* getToken(Lexer *lexer);

void lexer_abort(char *message);


#endif