#include "trienode.h"
#include <cstddef>

TrieNode::TrieNode() : terminal(false), children(new TrieNode*[NUM_CHARS]) {};

TrieNode::~TrieNode() {
  delete[] children;  
}

TrieNode::TrieNode(const TrieNode& rhs) : terminal(rhs.terminal), children(new TrieNode*[NUM_CHARS]) {
  for(size_t ndx = 0; ndx < NUM_CHARS; ++ndx) {
      children[ndx] = rhs.children[ndx];
  } 
}

TrieNode& TrieNode::operator=(const TrieNode& rhs)  {
  // Step 0:  Self-assigment check
  if(this == &rhs) return *this;

  // Step 1: Free up space
  delete[] children;

  //Step 2: Copy over members
  terminal = rhs.terminal;
  for(size_t ndx = 0; ndx < NUM_CHARS; ++ndx) {
      children[ndx] = rhs.children[ndx];
  }

  // Step 3: return self
  return *this;
}

TrieNode::TrieNode(TrieNode&& rhs) :terminal(rhs.terminal), children(rhs.children) {
  rhs.children = nullptr; 
}

TrieNode& TrieNode::operator=(TrieNode&& rhs)  {
  if(this == &rhs) return *this;

  children = rhs.children;
  terminal = rhs.terminal;
  
  rhs.children = nullptr; 
  
  return * this;
}

unsigned TrieNode::ord(char c) {
  return c - 'a';
}
