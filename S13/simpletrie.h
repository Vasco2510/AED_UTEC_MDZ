#include <iostream>
#include "trie.h"

using namespace std;

const unsigned ALPHA_SIZE = 26; // tamanio del alfabeto de letras minusculas

class TrieSimple : public Trie
{
private:
    struct TrieNode
    {
        // opcion 1:   TrieNode **children;
        // opcion 2:   list<pair<char, TrieNode*>> children;
        // opcion 3:   map<pair<char, TrieNode*>> children;
        TrieNode **children;
        bool endWord; // indica si es final de una palabra
        int count;

        TrieNode()
        {
            children = new TrieNode *[ALPHA_SIZE];
            for (size_t i = 0; i < ALPHA_SIZE; i++)
                children[i] = nullptr;
            endWord = false;
            count = 0;
        }
        ~TrieNode()
        {
            delete[] children;
        }
    };

    TrieNode *root;

public:
    TrieSimple() : root(nullptr) {}

    void insert(string key)
    {
        if (root == nullptr)
            root = new TrieNode();
        int index = 0;
        TrieNode *node = root;
        // recorrer caracter por caracter del key a insertar
        for (size_t i = 0; i < key.size(); i++)
        {
            index = key[i] - 'a';
            if (node->children[index] == nullptr)
            {
                node->children[index] = new TrieNode();
                node->count = node->count + 1;
            }
            node = node->children[index];
        }
        // indicar fin de la palabra
        node->endWord = true;
    }

    bool search(string key)
    {
        if (root == nullptr)
            return false;
        int index = 0;
        TrieNode *node = root;
        for (size_t i = 0; i < key.size(); i++)
        {
            index = key[i] - 'a';
            if (node->children[index] == nullptr)
                return false;
            node = node->children[index];
        }
        return node->endWord;
    }

    void remove(string key)
    {
        if (root != nullptr)
            remove(root, key, 0);
    }

    bool remove(TrieNode *&node, string key, int i)
    {
        bool encontrado = false;
        if (i == key.size())
        {
            encontrado = node->endWord;
            node->endWord = false;
        }
        else
        {
            int index = key[i] - 'a';
            if (node->children[index] != nullptr)
            {
                encontrado = remove(node->children[index], key, i + 1);
                if (encontrado && node->children[index]->count == 0)
                {
                    delete node->children[index];
                    node->children[index] = nullptr;
                    node->count = node->count - 1;
                }
            }
        }
        return encontrado;
    }

    // imprimir ordenado linea por linea
    string toString(string sep)
    {
        return toString(root, sep, "");
    }

private:
    string toString(TrieNode *node, string sep, string prefix)
    {
        if (root == nullptr)
            return "";
        string result = "";
        if (node->endWord)
            result += prefix + sep;
        for (int i = 0; i < ALPHA_SIZE; i++)
        {
            if (node->children[i] != nullptr)
                result += toString(node->children[i], sep, prefix + char('a' + i));
        }
        return result;
    }
};
