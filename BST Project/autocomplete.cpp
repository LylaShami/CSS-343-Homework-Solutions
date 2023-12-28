#include "autocomplete.h"
#include "bstmap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void testBSTAll();

// Function to read data from a file and populate a data structure called
// 'phrases'.
void Autocomplete::readFile(const string &fileName) {
  // Open the file with the given 'fileName'.
  ifstream ifs(fileName);
  // Check if the file exists or can be opened.
  if (!ifs) {
    cerr << "file does not exist" << endl;
    cout << "Please check spelling and re-enter file name" << endl;
  }
  int entryNumber;
  string lineFromFile;
  
  // Read the first lineFromFile from the file, which contains the total number
  // of entries.
  getline(ifs, lineFromFile);
  istringstream parser(lineFromFile);
  parser >> entryNumber;

  // Loop through each entry in the file.
  for (int i = 0; i < entryNumber; i++) {
    // Read the weight from the file (an integer).
    getline(ifs, lineFromFile, '\t');
    istringstream parser(lineFromFile);
    int weight;
    parser >> weight;
    // Read the key (a phrase) from the file.
    string key;
    getline(ifs, key, '\n');
    // Add the phrase and its weight to the 'phrases' data structure.
    phrases[key] = weight;
  }
  // Close the file.
  ifs.close();
  // Rebalance the 'phrases' data structure.
  phrases.rebalance();
  // Uncommenting the next lineFromFile would print the contents of 'phrases'.
  // cout << phrases << endl;
}

// Function to compare and sort pairs of key-value data by their values
// (weights).
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// Function to find and return autocomplete suggestions based on a given prefix.
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  // Retrieve a vector of key-value pairs from the 'phrases' data structure that
  // match the 'prefix'.
  vector<BSTMap::value_type> v = phrases.getAll(prefix);
  // Sort the vector of key-value pairs by their values (weights).
  sort(v.begin(), v.end(), sortByWeight);
  // Return the sorted vector of autocomplete suggestions.
  return v;
}
