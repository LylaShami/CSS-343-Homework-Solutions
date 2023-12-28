#ifndef HashTable_H
#define HashTable_H

#define MAXTABLESIZE 10

#include <iostream>
#include <vector>
using namespace std;

#include "customer.h"

class HashTable {
public:
  // Constructor: Initializes the hash table with nullptrs
  HashTable();

  // Destructor: Deallocates memory for all nodes and customer objects in the hash table
  ~HashTable();

  // Insert a customer into the hash table
  bool insert(Customer *customer);

  // Display all customer information in the hash table
  void showAllCustomerInfo();

  // Get customer information by ID from the hash table
  Customer *getIdentification(int id);

  // Get the total number of customers in the hash table
  int size() const;

  // Remove a customer by ID from the hash table
  bool remove(const int id);

  // Retrieve all customer information from the hash table
  vector<Customer *> retrieveAllCustomerInfo();

private:
  // Hash function: Maps customer ID to an index in the hash table
  int hashFunction(int id);

  // Node structure to store customer information and create a linked list
  struct Node {
    int id;
    Customer *customer;
    Node *next;

    // Node constructor: Initializes the node with customer information
    Node(int id, Customer *customer)
        : id(id), customer(customer), next(nullptr) {}
  };

  vector<Node *> tableOfCustomers;  // Array of linked lists to store customers

};

#endif
