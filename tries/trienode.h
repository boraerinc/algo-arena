// Change this based on your domain.
// 26 is enough to represent lowercasse or uppercase words
const unsigned NUM_CHARS = 26;

class TrieNode { 
public:
  bool terminal; 
  TrieNode** children;

  static unsigned ord(char);
  
  TrieNode(); 
  
  ~TrieNode();

  TrieNode& operator=(const TrieNode&);

  TrieNode(const TrieNode&);

  TrieNode& operator=(TrieNode&&);

  TrieNode(TrieNode&&);
};
