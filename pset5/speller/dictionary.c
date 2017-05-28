/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "trie.h"
#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    TrieNode *current_node = &trie_root;
    while (*word != '\0')
    {

        int c = tolower(*word);

        if (isalpha(c))
            c = c - 'a' + 1;

        if (c == '\'')
            c = c - '\'';

        if (current_node->nodes[c] == NULL)
        {
            return false;
        }
        else
        {
            current_node = current_node->nodes[c];
        }

        word++;
    }

    if (current_node->is_word == true)
        return true;
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open file by the filename that is passed in
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    TrieNode *current_node;

    // iterate through all characters in the dictionary file
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        current_node = &trie_root;

        while (isalpha(c) || c == '\'')
        {
            if (isalpha(c))
                c = c - 'a' + 1;

            if (c == '\'')
                c = c - '\'';

            printf("at char: %d\n", c);

            // path does not exist yet
            if (current_node->nodes[c] == NULL)
            {
                // dynamically allocate another node at index c of current node
                TrieNode *new_node = malloc(sizeof(TrieNode));
                if (new_node == NULL)
                {
                    printf("Could not create a new node");
                    return false;
                }

                new_node->is_word = false;

                for (int i = 0; i < 27; i++)
                {
                    new_node->nodes[i] = NULL;
                }

                current_node->nodes[c] = new_node;
                
                // debug purposes
                printf("Created new node\n");
            }

            // traverse through that path
            current_node = current_node->nodes[c];

            c = fgetc(fp);
        }

        printf("reached end of word\n");
        current_node->is_word = true;
    }

    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    if ()
}
