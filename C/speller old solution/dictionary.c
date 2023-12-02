// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
unsigned int loaded_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char processed_word[LENGTH + 1];

    //processed to lowercase
    for(int i = 0; i < LENGTH + 1; i++)
    {
        processed_word[i] = tolower(word[i]);
    }

    if (processed_word[0] == 'a' || processed_word[0] == 'i')
    {
        return true;
    }

    //start comparing here

    //where to start looking hash
     unsigned int hash_value = hash(processed_word);

     //node to compare
     node* cmp = table[hash_value];
     while(cmp != NULL)
     {
        int i =strcmp(processed_word, cmp->word);
        if (strcmp(processed_word, cmp->word) == 0)
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
    char c = word[0];
    c = tolower(c);

    return c - 'a';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file
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
    node * old_node = node_previous;


    //scanning
    while(fscanf(d, "%s", node_previous->word) != EOF)
    {
        if (c != node_previous->word[0])
        {
            old_node->next = NULL;
            c = tolower(node_previous->word[0]);
        }

        //determine hash
        unsigned int hash_value = hash(node_previous->word);

        //if table doesn't have that index yet, start pointing
        if(table[hash_value] == NULL)
        {
            node_previous->next = NULL;
            table[hash_value] = node_previous;
            node *new_node = malloc(sizeof(node));
            if(new_node == NULL)
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
    fclose(d);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size()
{
        return loaded_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i ++)
    {
        // node* point = malloc(sizeof(node));
        node* tmp = table[i];
        while (tmp != NULL)
        {
            node *point = tmp;
            tmp = tmp->next;
            free(point);
        //     free(next);
        //     next = point->next;
        }

    }
    return true;

}



    //     while (fread(&c, sizeof(char), 1, dict) != -1)
    // {
    //     // fread(&c, sizeof(char), 1, dict));
    //     printf("%c\n", c);
    // }

            // if (c != '\0') // && counter = 0
            // {

            //     dict_word->word[counter] = c;
            //     counter++;
            // }
            // else if (c == '\0')
            // {
            //     dict_word->word[counter] = c;
            //     counter = 0;
            // }

// bool load(const char *dictionary)
// {
//     // TODO
//     for (int i = 0; i < N; i++)
//     {
//         table[i] = malloc(sizeof(node));
//     }

//     char c = '\0';
//     FILE *dict = fopen(dictionary, "r");

//     //declare base case
//     if (dict == NULL)
//     {
//         return false;
//     }

//     //reading
//     int counter = 0;
//     node *dict_word = NULL;
//     bool is_first_node = true;
//     node *tmp = NULL;
//     // char first_index = '\0';
//     char first_word = '\0';
//     char first_word_after_enter = 'a';
//     bool after_enter = false;
//     while ((c = fgetc(dict)) != EOF)
//     {
//         if(after_enter)
//         {
//             first_word_after_enter = c;
//             after_enter = false;
//         }


//         if(first_word != first_word_after_enter) // && (c >= 'a' && c <='z')
//         {
//             is_first_node = true;
//             if(is_first_node)
//             {
//                 dict_word = malloc(sizeof(node));
//                 table[((int)c) - 97] = dict_word;
//                 dict_word->word[counter] = c;
//                 is_first_node = false;
//                 first_word = first_word_after_enter;
//                 counter++;
//             }
//         }
//         else
//         {
//             if(is_first_node)
//             {
//                 dict_word = malloc(sizeof(node));
//                 table[((int)c) - 97] = dict_word;
//                 dict_word->word[counter] = c;
//                 is_first_node = false;
//                 counter++;
//             }
//             else
//             {
//                 if(counter == 0)
//                 {
//                     tmp = dict_word;
//                     dict_word = malloc(sizeof(node));
//                     tmp->next = dict_word;
//                     dict_word->word[counter] = c;
//                     counter++;
//                 }
//                 else
//                 {
//                     if (c != '\n') // && counter = 0
//                     {

//                         dict_word->word[counter] = c;
//                         counter++;
//                     }
//                     else if (c == '\n')
//                     {
//                         dict_word->word[counter] = c;
//                         counter = 0;
//                         after_enter = true;
//                     }
//                 }
//             }
//         }
//     }

//     return true;
// }

//     node *tmp = malloc(sizeof(node));
//     tmp = table[hash];
//     for (int i = 1; i < word_count; i++)
//     {
//         if (processed_word[i] < tmp->word[i])
//         {
//             return false;
//         }
//         if (i < word_count)
//         {
//             if(processed_word[i] == tmp->word[i])
//             {
//                 // i++;
//                 if (tmp->word[i+1] == '\n')
//                 {
//                     return true;
//                 }

//             }
//             else if (tmp->next == NULL)
//             {
//                 return false;
//             }
//             else
//             {
//                 tmp = tmp->next;
//                 i = 0;
//             }
//         }
//         else if (i == word_count)
//         {
//             if (tmp->word[i+1] == '\n')
//             {
//                 return true;
//             }
//         }