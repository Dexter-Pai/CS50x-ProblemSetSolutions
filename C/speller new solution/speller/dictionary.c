// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int pointer;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char processed_word[LENGTH + 1];
    int word_count = strlen(word);
    // processed to lowercase
    for (int i = 0; i < LENGTH + 1; i++)
    {
        processed_word[i] = word[i];
        if (word[i - 1] == '\0')
        {
            break;
        }
    }

    // if (processed_word[0] == 'a' || processed_word[0] == 'i')
    // {
    //     return true;
    // }
    if ((processed_word[0] == 'a' || processed_word[0] == 'i' ||
         processed_word[0] == 'A' || processed_word[0] == 'I') && processed_word[1] == '\0')
    {
        return true;
    }

    //start comparing here

    //where to start looking hash
    unsigned int hash_value = hash(word);

    //node to compare
    node *cmp = table[hash_value];
    while (cmp != 0)
    {
        // int i =strcmp(processed_word, cmp->word);
        if (strcasecmp(processed_word, cmp->word) == 0)
        {
            return true;
        }
        else
        {
            cmp = cmp->next;
        }
    }
    //make temp pointer
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file
    int loaded_size = 0;
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }

    // initializing all the nodes in table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // initializin containers
    node *node_previous = malloc(sizeof(node));
    if (node_previous == NULL)
    {
        return false;
    }
    char c = '\0';
    node *old_node = node_previous;


    //scanning
    while (fscanf(d, "%s", node_previous->word) != EOF)
    {
        if (c != node_previous->word[0])
        {
            old_node->next = NULL;
            c = tolower(node_previous->word[0]);
        }

        //determine hash
        unsigned int hash_value = hash(node_previous->word);

        //if table doesn't have that index yet, start pointing
        if (table[hash_value] == NULL)
        {
            node_previous->next = NULL;
            table[hash_value] = node_previous;
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                return false;
            }
            table[hash_value]->next = new_node;
            old_node = node_previous;
            node_previous = new_node;
            loaded_size++;
        }

        //if table already have the index
        else
        {
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                return false;
            }
            old_node = node_previous;
            node_previous->next = new_node;
            node_previous = new_node;
            loaded_size++;
        }
    }
    node_previous = NULL;
    // free(node_previous);
    // free(new_node);
    pointer = loaded_size;
    fclose(d);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return pointer;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
//     // TODO
    for (int i = 0; i < N; i ++)
    {
        // node* point = malloc(sizeof(node));
        node *tmp = table[i];
        while (tmp != NULL)
        {
            node *point = tmp;
            tmp = tmp->next;
            free(point);
        }
    }
    return true;

}
// }

// bool compare(char* a, char* b)
// {
//     for (int i = 0; i < LENGTH + 1; i++)
//     {
//         if (a[i] != b[i])
//         {
//             return false;
//         }
//     }
//     return true;
// }