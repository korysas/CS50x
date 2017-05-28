/**
 * Trie structure consists of nodes.
 *
 * Each node can points to any letter in the alphabet,
 * and each node holds the letters traversed in
 * order to arrive at this node.
 */

typedef struct TrieNode
{
    bool is_word;
    struct TrieNode *nodes[27];
}
TrieNode;

TrieNode trie_root = { .is_word = false, .nodes = { NULL } };