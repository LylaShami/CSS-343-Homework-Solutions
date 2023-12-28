// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// BST class
// Creates a BST to store values
// Uses Node which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BSTMAP_H
#define BSTMAP_H

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class BSTMap {

  // display BST tree in a human-readable format
  // comment out printSideways or printVertical
  friend ostream &operator<<(ostream &out, const BSTMap &bst);

public:
  using key_type = string;
  using mapped_type = uint64_t;
  using value_type = pair<key_type, mapped_type>;

  // constructor, empty tree
  BSTMap() = default;

  // copy constructor
  BSTMap(const BSTMap &bst);

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (uses same helper as rebalance)
  explicit BSTMap(const vector<value_type> &v);

  // destructor
  virtual ~BSTMap();

  // move not allowed
  BSTMap(BSTMap &&other) = delete;

  // assignment not allowed
  BSTMap &operator=(const BSTMap &other) = delete;

  // move assignment not allowed
  BSTMap &operator=(BSTMap &&other) = delete;

  // true if no nodes in BST
  static bool empty();

  // Number of nodes in BST
  int size() const;

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int height() const;

  // delete all nodes in tree
  void clear();

  // true if item is in BST
  bool contains(const key_type &key) const;

  // same as contains, but returns 1 or 0
  // compatibility with std::map
  size_t count(const key_type &k) const;

  // If k matches the key returns a reference to its value
  // If k does not match any key, inserts a new element
  // with that key and returns a reference to its mapped value.
  mapped_type &operator[](const key_type &k);

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inorder(void visit(const value_type &item)) const;

  // preorder traversal: root-left-right
  void preorder(void visit(const value_type &item)) const;

  // postorder traversal: left-right-root
  void postorder(void visit(const value_type &item)) const;

  // balance the BST by saving all nodes to a vector inorder
  // and then recreating the BST from the vector
  void rebalance();

  // returns true if item successfully erased - BONUS
  bool erase(const key_type &k);

  // given a prefix string, return all values that match
  // the prefix. Traverses both branches of the tree once
  // a value matching the prefix is found.
  vector<value_type> getAll(const key_type &k) const;

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BSTMap &other) const;

  // not == to each other
  bool operator!=(const BSTMap &other) const;

private:
  // Node for BST
  struct Node {
    // key-value pair
    value_type data;
    // children
    struct Node *left;
    struct Node *right;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // print Node
  friend ostream &operator<<(ostream &out, const Node &n);

  // root of the tree
  Node *root{nullptr};
  // create a deep copy of a subtree starting from a given root node.
  Node *copySubtree(Node *root);
  // function to create a new node with the given key-value pair data.
  static Node *createNode(const value_type &item);
  // Function to count the number of nodes in the tree rooted at 'node'
  void clearTree(Node *node);
  // Function to count the number of nodes in the tree rooted at 'node'.
  int countNodes(Node *node) const;
  // Function to insert a key-value pair into the tree, or update the value if
  // the key already exists.
  mapped_type &insert(const value_type &item);
  // Function to build a tree from a vector of key-value pairs within a
  // specified range.
  Node *buildTree(const vector<value_type> &v, int firstIndex, int lastIndex);
  // Function to retrieve values that match a given key and store them in a
  // vector.
  void retrieveMatchingValues(vector<value_type> &v, Node *root,
                              const key_type &k) const;

  // Function to count the occurrences of a specific key in the tree.
  size_t countHelper(Node *node, const string &k) const;
  // Function to traverse the tree in an inorder (left-root-right) manner,
  // applying a given visit function.
  void inorderRecursive(Node *node, void visit(const value_type &item)) const;
  // Function to traverse the tree in a preorder (root-left-right) manner,
  // applying a given visit function.
  void preorderHelper(Node *n, void visit(const value_type &item)) const;
  // Function to traverse the tree in a postorder (left-right-root) manner,
  // applying a given visit function.
  void postorderHelper(Node *n, void visit(const value_type &item)) const;
  // Function to perform an inorder traversal for the purpose of tree
  // rebalancing.
  void inorderForRebalance(Node *n, vector<value_type> &v) const;
  // Function to build a balanced tree from a sorted vector of key-value pairs.
  Node *buildBalancedTree(const vector<value_type> &v, int left, int right);
  // Function to compare the structure of two trees rooted at 'node1' and
  // 'node2'.
  bool compareTrees(Node *node1, Node *node2) const;
  // Static function to find the leftmost node in a subtree rooted at
  // 'currentNode'.
  static Node *findLeftmostNode(Node *currentNode);
  // Function to erase a node with the specified key from the tree.
  bool eraseNode(Node *current, Node *parent, const key_type &k);

  // print tree sideways with root on left
  static ostream &printSideways(ostream &out, const Node *curr, int level = 0);

  // helper for printVertical
  static ostream &centeredPrint(ostream &out, int space, const string &str,
                                char fillChar = ' ');

  // print tree with the root at top
  static ostream &printTreeLevel(ostream &out, queue<const Node *> &q,
                                 int width, int depth, int maxDepth);

  // helper function for displaying tree sideways, works recursively
  static ostream &printVertical(ostream &out, Node *curr);

  // height of a Node, nullptr is 0, root is 1, static, no access to 'this'
  // helper function to height(), used by printVertical
  int getHeight(const Node *n) const;
};
#endif