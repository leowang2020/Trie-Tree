#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TRIE.h"
 
int main()
{
    trieNode_t *root;
    printf("Trie Example\n");
     
    /*Create a trie*/
    TrieCreate(&root);
     
    TrieAdd(&root, "god", 1);
    TrieAdd(&root, "leo", 2);
    TrieAdd(&root, "sherry", 3);
	TrieAdd(&root, "tracy", 4);
    TrieAdd(&root, "annie", 5);
    TrieAdd(&root, "godzilla", 6);
    TrieAdd(&root, "tea", 7);
    TrieAdd(&root, "coffee", 8);
    TrieAdd(&root, "banana", 9);
    TrieAdd(&root, "apple", 10);
    TrieAdd(&root, "orange", 11);
    TrieAdd(&root, "kiwi", 12);
    TrieAdd(&root, "cherry", 13);
	TrieAdd(&root, "vacation", 14);
	TrieAdd(&root, "harass", 15);
	TrieAdd(&root, "recommend", 16);
	TrieAdd(&root, "vacuum", 17);
	TrieAdd(&root, "embarrass", 18);
	TrieAdd(&root, "experience", 19);
	TrieAdd(&root, "hierarchy", 20);
	TrieAdd(&root, "immediate", 21);
	TrieAdd(&root, "apparent", 22);
    TrieAdd(&root, "leonardo", 23);
	TrieAdd(&root, "accidentally", 24);
	TrieAdd(&root, "receive", 25);
	TrieAdd(&root, "weird", 26);
	TrieAdd(&root, "judgement", 27);
	TrieAdd(&root, "parallel", 28);
	TrieAdd(&root, "ridiculous", 29);
	TrieAdd(&root, "success", 30);
	trieNode_t* pSearchResult = TrieSearch(root->children, "andrew");

	char wordToSearch[50];
	while (strcmp(wordToSearch, "end") != 0)
	{
		printf("Please enter your word: ");
		scanf("%s", wordToSearch);

		pSearchResult = TrieSearch(root->children, wordToSearch);
		bool bFound;
		if (pSearchResult == NULL)
		{
			bFound = false;
			pSearchResult = WordMatch(root->children, wordToSearch);
		}
		else
			bFound = true;

		if (pSearchResult != NULL)
		{
			char * newWord = (char *)malloc(strlen(wordToSearch) + 10); 
			/*
			void * memset ( void * ptr, int value, size_t num );
			Fill block of memory
			Sets the first num bytes of the block of memory pointed by ptr to the specified value (interpreted as an unsigned char).
			*/

			memset(newWord, 0, strlen(wordToSearch) + 10);
			int i = strlen(wordToSearch)+5;
			trieNode_t* pCurr = pSearchResult;
			while ((pCurr->parent != NULL) && (pCurr->parent->key != '\0'))
			{
				i--;
				newWord[i] = pCurr->parent->key;
				pCurr = pCurr->parent;
			}
			if (bFound)
				printf("\n[%s] found.\ \n\n\n", wordToSearch);
			else
				printf("\n[%s] not found.\nDid you mean [%s]? \n\n\n", wordToSearch, newWord+i);

			free(newWord);
		}
		else
			printf("\n[%s] is not found. Please try again.\n\n", wordToSearch);
	}

    /*Destroy the trie*/
    TrieDestroy(root);
	system("pause");
}