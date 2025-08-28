#ifndef HASH_SET
#define HASH_SET

#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#define SIZE 251

typedef struct{

    char *value;
    Node* next;

}Node;

typedef struct{

    Node* values[SIZE];
    

}Set;


Set* create_set();
long getHash(char *value);
Node *createNode(char *value);
bool lookup(Set* hashset,  char *value);
void insert(Set* hashset, char *value);
bool search(Set* hashset,char *value);
void free_hash_table(Set* hashset);
long getHash(char *value);





#endif