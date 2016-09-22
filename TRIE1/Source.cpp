#include <stdio.h> 
#include <stdlib.h> 
#include <string> 
#include <ctype.h> 
#include <conio.h> 
#include <iostream> 
 
using namespace std; 
 
#define NR 27 // the American alphabet(26 letters) plus blank. 
typedef char var_type; // the key is a set of characters 
 
typedef struct trie_node{ 
 bool NotLeaf; // indicates if the trie_node struct is a leaf or an intern node 
 trie_node *pChildren[NR]; // a list of pointers corresponding to the used alphabet 
 var_type word[20]; // the string stored in node 
}node; 
 
 
//function for creating a leaf node 
trie_node *NewLeaf(char keyWord[20]) 
{ 
 trie_node *t_node; 
 int count; 
 
 //allocating the necessary memory 
 t_node = (trie_node *)malloc(sizeof(trie_node)); 
 
 for(count = 0; count < 27; count++) //the terminal nodes don't have children 
 t_node->pChildren[count] = NULL; 
 t_node->NotLeaf = false; // the node is a leaf 
 strcpy(t_node->word,keyWord); //store in the structure(node->word) the string 
 
 return t_node; 
} 
 //function for creating a intern node 
trie_node *NewIntern() 
{ 
 trie_node *t_node; 
 int count; 
 
 //allocating the necessary memory 
 t_node = (trie_node *)malloc(sizeof(trie_node)); 
 
 for(count = 0; count < 27; count++) // initial the intern node don't have children 
 t_node->pChildren[count] = NULL; 
 t_node->NotLeaf = true; //it isn't a leaf 
 t_node->word[0] = 0; //so we store the null string in node 
 
 return t_node; 
} 
 
//function performs a search in the TRIE when a string or key is passed. 
void Find(trie_node *trie, char keyWord[20]) 
{ 
 trie_node *next, *index, *data; 
 int count; 
 
 next = trie; //start searching from the trie root 
 
 if(next == NULL) //trie is empty 
 { 
 cout << "Word not found in trie !!!!" << endl ; 
 exit(1); 
 } 
 else 
 index = next;// index - the current node from trie 
 
 count = 0; // start searching for the first letter of the word(index of letter in word is 0) 
 while((index->NotLeaf == true) && (count < strlen(keyWord)) && (index->pChildren[keyWord[count]-
'a'] != NULL)) 
 { 
 next = index->pChildren[keyWord[count]-'a']; 
 index = next; 
 count ++ ; 
 } 
 
 if(next == NULL) 
 cout << "Word not found in trie !!!!" << endl; 
 else 
 { 
 data = next; 
 //the string is in a leaf 
 if(!strcmp(data->word,keyWord)) 
 cout << "Key exists --- Word found in trie !!!!" << endl; 
 else//the string is in the blank pointer(prefix for others words stored in trie) 
 if((data->pChildren[26]) && !strcmp(data->pChildren[26]->word,keyWord)) 
 cout << "Key exists --- Word found in trie !!!!" << endl ; 
 else 
 cout << "Word not found in trie !!!!" << endl ; 
 } } 
 
//function for inserting a string into the trie 
trie_node *Insert(trie_node *trie, char keyWord[20]) 
{ 
 trie_node *next, *index, *parent; 
 trie_node *new_leaf, *data, *new_index; 
 trie_node *oldChildren, *newWord, *intern; 
 
 int inWordIndex, prefixLenght, lenght = strlen(keyWord); 
 
 next = trie; 
 if(next == NULL) //trie empty 
 { 
 trie = NewIntern(); 
 new_leaf = NewLeaf(keyWord); 
 trie->pChildren[keyWord[0]-'a'] = new_leaf; 
 
 return trie; 
 } 
 else 
 index = next; 
 
 inWordIndex = 0; 
 while((inWordIndex < lenght) &&(index->NotLeaf == true)&&(index->pChildren[keyWord[inWordIndex]-'a'] != NULL)) 
 { 
 parent = next; 
 next = index->pChildren[keyWord[inWordIndex]-'a']; 
 index = next; 
 
 inWordIndex++; 
 } 
 
 
 if((inWordIndex < lenght) && (index->pChildren[keyWord[inWordIndex]-'a'] == NULL) && (index->NotLeaf == true)) 
 { 
 new_index = NewLeaf(keyWord); 
 index->pChildren[keyWord[inWordIndex]-'a'] = new_index; 
 
 return trie; 
 } 
 else 
 data=next; 
 
 if(!strcmp(data->word,keyWord)) 
 cout << "Word already exists in trie !!!" << endl; 
 else 
 { 
 oldChildren = parent->pChildren[keyWord[inWordIndex-1]-'a']; 
 newWord = NewLeaf(keyWord); 
 
 prefixLenght= strlen(keyWord); 
 if(data->word[0] != '\0') 
 if(strlen(data->word) < prefixLenght)  prefixLenght = strlen(data->word); 
 } 
 
 bool createIntern = false; 
 while((inWordIndex <= prefixLenght)&&(((data->word[0] != '\0' )&& (data->word[inWordIndex-1] == 
keyWord[inWordIndex-1])) || (data->word[0] == '\0'))) 
 { 
 intern = NewIntern(); 
 parent->pChildren[keyWord[inWordIndex-1]-'a'] = intern; 
 parent->NotLeaf = true; 
 parent = intern; 
 inWordIndex++; 
 
 createIntern = true; 
 } 
 if(createIntern) 
 inWordIndex--; 
 
 if((inWordIndex != prefixLenght) || ((inWordIndex == prefixLenght)&&(strlen(keyWord) == strlen(data->word))))
 { 
 parent->pChildren[data->word[inWordIndex]-'a'] = oldChildren; 
 parent->pChildren[keyWord[inWordIndex]-'a'] = newWord; 
 } 
 else 
 if(data->word[0] != '\0')// doar un cuv care il are ca prefix pe keyWord sau invers 
 if(strlen(data->word) <= prefixLenght) 
 { 
 parent->pChildren[26] = oldChildren; 
 parent->pChildren[keyWord[prefixLenght]-'a'] = newWord; 
 } 
 else 
 { 
 parent->pChildren[26] = newWord; 
 parent->pChildren[data->word[prefixLenght]-'a'] = oldChildren; 
 } 
 else// 2 sau mai multe cuv care au acelasi prefix 
 { 
 for (int count = 0 ; count < 27;count++) 
 parent->pChildren[count] = oldChildren->pChildren[count]; 
 parent->pChildren[26] = newWord; 
 } 
 
 return trie; 
} 
 
//function for displaying the words stored in the trie 
void DisplayTrie(trie_node *trie, int nivel) 
{ 
 int count; 
 
 if(trie) 
 { 
 if (trie->NotLeaf != true) // if trie_node is a leaf(a word is stored in) 
 { // display the string at his level 
 for (count = 0; count <= nivel; count++)  cout << " "; 
 cout << trie->word << endl; 
 } 
 // display all the words stored through trie children 
 for (count = 26; count >= 0; count--) 
 DisplayTrie(trie->pChildren[count], nivel + 4); 
 } 
 
} 
 
int main() 
{ 
 trie_node *trie; 
 char UserInputWord[20], cont_insert=' '; 
 int option = 0; //stores the user's input(the chosen option) 
 
 trie = NULL; 
 
label_menu: 
 while( option != 5) 
 { 
 //display menu 
 cout << endl << " Menu: " << endl; 
 cout << "___________________________________________" << endl; 
 cout << " 1. Create tree\n 2. Insert node\n 3. Search for node\n 4. Display tree\n 5. Exit\n"; 
 
 //get user input 
 cout << "\n\n\nInput choice: "; 
 cin >> option; 
 
 
 switch (option) 
 { 
 case 1: //Create tree 
 while(cont_insert != 'n') 
 { 
 // get user input string 
 cout << endl << "Insert word :"; 
 cin >> UserInputWord; 
 
 trie = Insert(trie,UserInputWord); 
 
 cout << "\n Continue ? <y/n>"; 
 cont_insert = getchar(); 
 } 
 
 break; 
 case 2: //Insert node 
 cout << endl << "Insert word :"; 
 cin >> UserInputWord; 
 
 Insert(trie,UserInputWord); 
 
 break; 
 case 3: //Search for node 
 cout << endl << "Searched word :";  cin >> UserInputWord; 
 
 Find(trie,UserInputWord); 
 
 break; 
 case 4: //Display tree 
 DisplayTrie(trie,0); 
 
 break; 
 case 5: //Exit 
 break; 
 default: 
 cout << "Choose from the displayed options (1-5) !!!"; 
 goto label_menu; 
 }//end switch 
 }//end while 
 
 system("PAUSE"); 
 return 0; 
} 
