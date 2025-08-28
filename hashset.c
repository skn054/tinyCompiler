#include<stdio.h>
#include<string.h>

#include "hashset.h"

Set* create_set(){
    Set *hashset =(Set *)malloc(sizeof(Set));
    if(hashset == NULL){
        return NULL;
    }


    for(int i=0;i<SIZE;i++){
        hashset->values[i] = NULL;
    }

    return hashset;

}

long getHash(char *value){
    long hash = 0;
    for(int i=0;value[i]!='\0';i++){
        hash = hash*31 + value[i];
    }
    return labs(hash % SIZE);
}

Node *createNode(char *value){
    Node *node = malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->value = strdup(value);
    if (node->value == NULL) { // Check if strdup failed
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

bool lookup(Set* hashset,  char *value){
    long hash_index = getHash(value);
    Node *temp;
    temp = hashset->values[hash_index];
        // travese the list tp find element
    while(temp!=NULL){
        if(strcmp(temp->value,value)==0){
                return true;
        }
        temp = temp->next;
            
    }
    return false;
        
    
}

void insert(Set* hashset, char *value){

    if(lookup(hashset,value)){
        return;
    }

    long hash_index = getHash(value);
    Node *node = createNode(value);
    if(node == NULL) return;
    
    node->next = hashset->values[hash_index];
    hashset->values[hash_index] = node;
    


}

bool search(Set* hashset,char *value){
    
      return lookup(hashset,value);
}


void free_hash_table(Set* hashset){

    for(int i=0;i<SIZE;i++){
        Node *temp = hashset->values[i];
        while(temp!=NULL){
            Node *t = temp;
            temp = t->next;
            free(t->value);
            
            free(t);
        }
    }

    free(hashset);

}
