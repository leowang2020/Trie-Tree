#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TRIE.h"

trieNode_t *TrieCreateNode(char key, int data)
{
	trieNode_t *node = NULL;
	node = (trieNode_t *)malloc(sizeof(trieNode_t));
 
	if(NULL == node)
	{
		printf("Malloc failed\n");
		return node;
	}
 
	node->key = key;
	node->next = NULL;
	node->children = NULL;
	node->value = data;
	node->parent= NULL;
	node->prev= NULL;
	return node;
}

void TrieCreate(trieNode_t **root)
{
	*root = TrieCreateNode('\0', 0xffffffff);
}
 
void TrieAdd(trieNode_t **root, char *key, int data)
{
	trieNode_t *pTrav = NULL;
 
	if(NULL == *root)
	{
		printf("NULL tree\n");
		return;
	}

	#ifdef _DEBUG
	printf("\nInserting key %s: \n",key);
	#endif

	pTrav = (*root)->children; 
	
	if(pTrav == NULL)
	{
		/*First Node*/
		for(pTrav = *root; *key; pTrav = pTrav->children)
		{
			pTrav->children = TrieCreateNode(*key, 0xffffffff);
			pTrav->children->parent = pTrav;
			#ifdef _DEBUG
			printf("Inserting: [%c]\n",pTrav->children->key);
			#endif
			key++;
		}
 
		pTrav->children = TrieCreateNode('\0', data);
		pTrav->children->parent = pTrav;
		#ifdef _DEBUG
		printf("Inserting: [%c]\n",pTrav->children->key);
		#endif
		return;
	}
 
	if(TrieSearch(pTrav, key))
	{
		printf("Duplicate!\n");
		return;
	}
 
	while(*key != '\0')
	{
		if(*key == pTrav->key)
		{
			key++;
			#ifdef _DEBUG
			printf("Traversing child: [%c]\n",pTrav->children->key);
			#endif
			pTrav = pTrav->children;
		}
		else
			break;
	}
 
	while(pTrav->next)
	{
		if(*key == pTrav->next->key)
		{
			key++;
			TrieAdd(&(pTrav->next), key, data);
			return;
		}
		pTrav = pTrav->next;
	}
 
	if(*key)
	{
		pTrav->next = TrieCreateNode(*key, 0xffffffff);
	}
	else
	{
		pTrav->next = TrieCreateNode(*key, data);
	}
 
	pTrav->next->parent = pTrav->parent;
	pTrav->next->prev = pTrav;
 
	#ifdef _DEBUG
	printf("Inserting [%c] as neighbour of [%c] \n",pTrav->next->key, pTrav->key);
	#endif
 
	if(!(*key))
		return;
 
	key++;
 
	for(pTrav = pTrav->next; *key; pTrav = pTrav->children)
	{
		pTrav->children = TrieCreateNode(*key, 0xffffffff);
		pTrav->children->parent = pTrav;
		#ifdef _DEBUG
		printf("Inserting: [%c]\n",pTrav->children->key);
		#endif
		key++;
	}
 
	pTrav->children = TrieCreateNode('\0', data);
	pTrav->children->parent = pTrav;
	#ifdef _DEBUG
	printf("Inserting: [%c]\n",pTrav->children->key);
	#endif
	return;
}
 
trieNode_t* TrieSearch(trieNode_t *root, const char *key)
{
	trieNode_t *level = root;
	trieNode_t *pPtr = NULL;
 
	int lvl=0;
	while(1)
	{
		trieNode_t *found = NULL;
		trieNode_t *curr;
 
		for (curr = level; curr != NULL; curr = curr->next)
		{
			if (curr->key == *key)
			{
				found = curr;
				lvl++;
				break;
			}
		}
 
		if (found == NULL)
			return NULL;
 
		if (*key == '\0')
		{
			pPtr = curr;
			return pPtr;
		}
 
		level = found->children;
		key++;
	}
}
 
void TrieRemove(trieNode_t **root, char *key)
{
	trieNode_t *tPtr = NULL;
	trieNode_t *tmp = NULL;
 
	if(NULL == *root || NULL == key)
		return;
 
	tPtr = TrieSearch((*root)->children, key);
 
	if(NULL == tPtr)
	{
		printf("Key [%s] not found in trie\n", key);
		return;
	}
 
	#ifdef _DEBUG
	printf("Deleting key [%s] from trie\n", key);
	#endif
 
	while(1)
	{
		if( tPtr->prev && tPtr->next)
		{
			tmp = tPtr;
			tPtr->next->prev = tPtr->prev;
			tPtr->prev->next = tPtr->next;
			#ifdef _DEBUG
			printf("Deleted [%c] \n", tmp->key);
			#endif
			free(tmp);
			break;
		}
		else if(tPtr->prev && !(tPtr->next))
		{
			tmp = tPtr;
			tPtr->prev->next = NULL;
			#ifdef _DEBUG
			printf("Deleted [%c] \n", tmp->key);
			#endif
			free(tmp);
			break;
		}
		else if(!(tPtr->prev) && tPtr->next)
		{
			tmp = tPtr;
			tPtr->parent->children = tPtr->next;
			#ifdef _DEBUG
			printf("Deleted [%c] \n", tmp->key);
			#endif
			free(tmp);
			break;
		}
		else
		{
			tmp = tPtr;
			tPtr = tPtr->parent;
			tPtr->children = NULL;
			#ifdef _DEBUG
			printf("Deleted [%c] \n", tmp->key);
			#endif
			free(tmp);
		}
	}
 
	#ifdef _DEBUG
	printf("Deleted key [%s] from trie\n", key);
	#endif
}

trieNode_t* WordMatch(trieNode_t *root, const char *key)
{
	if (root == NULL)
		return NULL;

	trieNode_t *found = TrieSearch(root, key);
	if (found != NULL) // found it
		return found;
 
	int len = strlen(key);
	for (int j=len; j>0; j--)
	{
		for (int i=0; i<26; i++)
		{
			if (key[j-1] == (97 + i)) // 97 is ascii code for letter 'a'
				continue;
			char* newKey = (char*)malloc(len + 1);
			strcpy(newKey, key);
			newKey[j-1] = 97 + i; 
			found = TrieSearch(root, newKey);
			free(newKey);
			if (found != NULL)
				return found;
		}
	}

	return NULL;
}
 

void TrieDestroy( trieNode_t* root )
{
	trieNode_t *tPtr = root;
	trieNode_t *tmp = root;
 
	while(tPtr)
	{
		while(tPtr->children)
			tPtr = tPtr->children;
 
		if( tPtr->prev && tPtr->next)
		{
			tmp = tPtr;
			tPtr->next->prev = tPtr->prev;
			tPtr->prev->next = tPtr->next;
			#ifdef _DEBUG
			printf("Deleted [%c] \n", tmp->key);
			#endif
			free(tmp);
		}
		else if(tPtr->prev && !(tPtr->next))
		{
			tmp = tPtr;
			tPtr->prev->next = NULL;
			#ifdef _DEBUG
			printf("Deleted [%c] \n", tmp->key);
			#endif
			free(tmp);
		}
		else if(!(tPtr->prev) && tPtr->next)
		{
			tmp = tPtr;
			tPtr->parent->children = tPtr->next;
			tPtr->next->prev = NULL;
			tPtr = tPtr->next;
			#ifdef _DEBUG
			printf("Deleted [%c] \n", tmp->key);
			#endif
			free(tmp);
		}
		else
		{
			tmp = tPtr;
			if(tPtr->parent == NULL)
			{
			/*Root*/
			free(tmp);
			return;
		}
		tPtr = tPtr->parent;
		tPtr->children = NULL;
		#ifdef _DEBUG
		printf("Deleted [%c] \n", tmp->key);
		#endif
		free(tmp);
	}
	}
}