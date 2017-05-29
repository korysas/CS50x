/**
 * Trie structure consists of nodes.
 *
 * Each node can points to any letter in the alphabet,
 * and each node holds the letters traversed in
 * order to arrive at this node.
 */
#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct TrieNode
{
    bool is_word;
    struct TrieNode *nodes[27];
}
TrieNode;

#endif // TRIE_H