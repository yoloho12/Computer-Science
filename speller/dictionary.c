#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
 
 
#include "dictionary.h"
 
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
 
//word count for size
int word_count = 0;
 
// Number of buckets in hash table
const unsigned int N = 26;
 
// Hash table
node *table[N];
 
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char w[46];
    for (int i = 0; i < strlen(word) + 1; i++)
    {
        w[i] = tolower(word[i]);
    }
    int index = hash(w);
    for (node *tmp = table[index]; tmp->next != NULL; tmp = tmp->next)
    {
        //   printf("%s \t & %s \n",w,tmp->next->word);
        if (strcasecmp(w, tmp->next->word) == 0)
        {
            return true;
        }
    }
    return  false;
}
 
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char *bucket_keys = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 26 ; i++)
    {
        if (word[0] == bucket_keys[i])
        {
            return i;
        }
    }
    return 26;
}
 
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char w[100];
    unsigned int index;
    // open dictionary and import data to hashTable
    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        //
        table[i]->next = NULL;
        if (table[i] == NULL)
        {
            return 1;
        }
    }
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        while (fscanf(file, "%s", w) != EOF)
        {
            index = hash(w);
            // printf(" best index is _%i for word :%s\n ", index, w);
 
            if (table[index]->next == NULL)
            {
                node *n = malloc(sizeof(node));
                if (n == NULL)
                {
                    return 1;
                }
                n->next = NULL;
                strcpy(n-> word, w);
                table[index]->next = n;
                // printf("stroed!\n");
 
            }
            else
            {
                node *n = malloc(sizeof(node));
                if (n == NULL)
                {
                    return false;
                }
                strcpy(n -> word, w);
                n -> next = table[index] -> next;
                table[index] -> next = n;
                // printf("stroed!\n");
            }
            word_count++;
        }
        fclose(file);
        return true;
    }
 
    return false;
}
 
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}
 
// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (table[i]->next != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
        free(table[i]);
    }
 
 
    return true;
}