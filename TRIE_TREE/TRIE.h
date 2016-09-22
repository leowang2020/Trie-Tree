#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int trieVal_t;
typedef struct trieNode 
{
    char key;
    trieVal_t value;
    struct trieNode *next;
    struct trieNode *prev;
    struct trieNode *children;
    struct trieNode *parent; 
} trieNode_t;
 
void TrieCreate(trieNode_t **root);
trieNode_t* TrieSearch(trieNode_t *root, const char *key);
void TrieAdd(trieNode_t **root, char *key, int data);
void TrieRemove(trieNode_t **root, char *key);
trieNode_t* WordMatch(trieNode_t *root, const char *key);
char* makeNewKeyAddaLetter(const char *key, char letter, int j);
char* makeNewKeyEraseaLetter(const char *key, int j);
void TrieDestroy( trieNode_t* root );