#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"lexer.h"
#include "parser.h"
#include "hashset.h"


void main(int argc,char *argv[]){
    // char *source = "+- */";
    // char *source =  "IF+-123 foo*THEN/";
    // Lexer *lexer = initLexer(source);
    // char c;
    // while ((c = (int)nextChar(lexer))!=-1)
    // {
    //     printf("%c\n",c);
    // }

    FILE *inputfile = fopen("input.txt","r");
    if(inputfile == NULL){
         fprintf(stderr, "Error: Could not open source file.\n");
        exit(1);
    } 

    fseek(inputfile,0,SEEK_END);
    long file_size = ftell(inputfile);
    fseek(inputfile,0,SEEK_SET);

    char *source = malloc(file_size + 1);
    if(source == NULL){
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(inputfile);
        exit(1);
    }
    fread(source,1,file_size,inputfile);
    source[file_size] = '\0';
    fclose(inputfile);
    
    Lexer *lexer = initLexer(source);
    Parser *parser = initParser(lexer);
    program(parser);
    // Token *token;
    // while((token = getToken(lexer))->type !=EOFL){
    //     printf("%s %d\n", token->tokenText,token->type);
        
    //     nextChar(lexer);
    //     // printf("%c",lexer->currChar);
    // }
    

}