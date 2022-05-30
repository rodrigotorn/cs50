// Implements a dictionary's functionality
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
#define N 10000

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{   int n = strlen(word);
    char lower_word[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[n] = '\0';

    int index = hash(lower_word);
    node *tmp = table[index];
    
    while (tmp != NULL && strncmp(tmp->word, lower_word, LENGTH) != 0)
    {
        tmp = tmp->next;
    }
    if (tmp != NULL){
        if (strncmp(tmp->word, lower_word, LENGTH) == 0)
            return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char* word) {
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

bool insert_word(const char *word)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Could not store the word.\n");
        return false;
    }
    strcpy(n->word, word);
    int index = hash(word);
    n->next = table[index];
    table[index] = n;
    return true;
}

void init_table()
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    init_table();
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != -1) 
    {
        if (insert_word(word) == false)
        {
            return false;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int word_count = 0;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *tmp = table[i];
            while (tmp != NULL)
            {
                tmp = tmp->next;
                word_count++;
            }
        }
    }
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    if (size() > 0)
    {
        node* tmp;
        node* crawler;

        for(int i = 0; i < N; i++)
        {   
            if (table[i] != NULL)
            {
                crawler = table[i];
                while (crawler != NULL)
                {
                    tmp = crawler->next;
                    free(crawler);
                    crawler = tmp;
                }
                tmp = crawler;
                free(tmp);
            }
        }
        return true;
    }
    return false;    
}


void print_table()
{
    printf("Start\n");
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t", i);
            node *tmp = table[i];
            while (tmp != NULL)
            {
                printf("%s - ", tmp->word);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End\n");
}


// int main(int argc, char* argv[])
// {
//     init_table();
//     char const* const fileName = argv[1];
//     load(fileName);

//     printf("%i\n", size());
//     unload();
// }
