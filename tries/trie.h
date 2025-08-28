#include "trienode.h"
#include <string>
#include <vector>

class TrieNode;

class Trie {
  TrieNode* root;

  public:
    // Construct empty Trie
    Trie();

    // Construct Trie from a list of words
    Trie(const std::vector<std::string>);

    //=====================================================
    // RULE OF 5
    // ====================================================

    
    // Copy constructor
    Trie(const Trie&);
    
    // Assignment operator
    Trie& operator=(const Trie&);

    // Move constructor
    Trie(Trie&&);

    // Move assignment operator
    Trie& operator=(Trie&&);

    // Destructor
    ~Trie();

    // ===================================================
    
    bool insert(const std::string&);
    
    unsigned insertList(const std::vector<std::string>&);

    bool search(const std::string&);

    bool searchPrefix(const std::string&);
};
