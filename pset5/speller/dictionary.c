/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "trie.h"
#include "dictionary.h"

// global root
TrieNode *trie_root;
// = { .is_word = false, .nodes = { NULL } };

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    TrieNode *current_node = trie_root;
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
    // define trie_root
    trie_root = malloc(sizeof(TrieNode));
    if (trie_root == NULL)
    {
        printf("Could not create trie root node");
        return false;
    }
    
    trie_root->is_word = false;

    for (int i = 0; i < 27; i++)
    {
        trie_root->nodes[i] = NULL;
    }

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
        current_node = trie_root;

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

    fclose(fp);

    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    int size = 0;
    _size(&size, trie_root);

    return size;
}

/**
 * private helper function that recursively traverses trie
 * and determines the valid words in the trie
 */
void _size(int *size, TrieNode *node)
{
    if (node->is_word == true)
    {
        *size += 1;
    }

    for (int i = 0; i < 27; i++)
    {
        if (node->nodes[i] != NULL)
        {
            _size(size, node->nodes[i]);
        }
    }

    return;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    return _unload(trie_root);
}

/**
 * private helper function that recursively implements unload
 * to free any memory alloacted via malloc
 */
bool _unload(TrieNode *node)
{
    for (int i = 0; i < 27; i++)
    {
        if (node->nodes[i] != NULL)
        {
            _unload(node->nodes[i]);
        }
    }

    printf("free node\n");
    free(node);
    return true;
}
