#include "trie.h"

Trie::Trie() : root(new TrieNode) {};

Trie::Trie(const std::vector<std::string> words) : root(new TrieNode) {
  insertList(words);
};

bool Trie::insert(const std::string& word) {
  TrieNode* curr = root;

  for(size_t ndx = 0; ndx < word.size(); ++ndx) {
    TrieNode* nxt = curr->children[TrieNode::ord(word[ndx])];
    if ( nxt == nullptr ) {
      nxt = new TrieNode;
    }
    curr = nxt;
  }

  bool inserted = !curr->terminal;
  curr->terminal = true;
  return inserted;
}

unsigned Trie::insertList(const std::vector<std::string>& words) {
  unsigned count = 0;
  for(const std::string& word: words) {
    count += insert(word); 
  }

  return count;
}

bool Trie::search(const std::string& word) {
  TrieNode* curr = root;

  for(size_t ndx = 0; ndx < word.size(); ++ndx) {
    TrieNode* nxt = curr->children[TrieNode::ord(word[ndx])];
    if ( nxt == nullptr ) {
      return false;
    }
    curr = nxt;
  }

  return curr->terminal;
}

bool Trie::searchPrefix(const std::string& word) {
  TrieNode* curr = root;

  for(size_t ndx = 0; ndx < word.size(); ++ndx) {
    TrieNode* nxt = curr->children[TrieNode::ord(word[ndx])];
    if ( nxt == nullptr ) {
      return false;
    }
    curr = nxt;
  }

  return true; 
}

Trie::~Trie() {
  delete root;
}

Trie::Trie(const Trie& rhs): root(nullptr) {
  *root = *rhs.root;
};

Trie& Trie::operator=(const Trie& rhs) {
  if ( this == &rhs ) return * this;

  delete root;
  *root = *rhs.root;

  return *this;
}

Trie::Trie(Trie&& rhs): root(rhs.root) {
  rhs.root = nullptr;
}

Trie& Trie::operator=(Trie&& rhs) {
  if ( this == &rhs ) return *this;

  root = rhs.root;

  rhs.root = nullptr;
  
  return *this;
}













