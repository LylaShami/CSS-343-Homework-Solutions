#include "hashtable.h"
#include <iomanip>

HashTable::HashTable() {
    // Constructor: Initialize the hash table with nullptrs
    for (int i = 0; i < MAXTABLESIZE; ++i) {
        tableOfCustomers.push_back(nullptr);
    }
}

int HashTable::hashFunction(int id) {
    // Hash function: Maps customer ID to an index in the hash table
    return (id % MAXTABLESIZE);
}

std::vector<Customer *> HashTable::retrieveAllCustomerInfo() {
  // Retrieve all customer information from the hash table
  std::vector<Customer *> customerList;
  for (int i = 0; i < MAXTABLESIZE; i++) {
    Node *current = tableOfCustomers[i];
    while (current != nullptr) {
      customerList.push_back(current->customer);
      current = current->next;
    }
  }
  return customerList;
}

bool HashTable::insert(Customer* customer) {
  // Insert a customer into the hash table
  int id = customer->getID();
  int index = hashFunction(id);
  Node* nodeToAdd = new Node(id, customer);

  if (tableOfCustomers[index] == nullptr) {
    tableOfCustomers[index] = nodeToAdd;
  } else {
    Node* current = tableOfCustomers[index];

    // Check for duplicate customer ID
    while (current != nullptr) {
      if (current->id == id) {
        delete nodeToAdd;
        return false;  // Duplicate customer ID
      }
      current = current->next;
    }

    // Append the new customer to the end of the linked list
    current = tableOfCustomers[index];
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = nodeToAdd;
  }

  return true;
}

HashTable::~HashTable() {
  // Destructor: Deallocate memory for all nodes and customer objects in the hash table
  for (int i = 0; i < tableOfCustomers.size(); i++) {
    Node *current = tableOfCustomers[i];
    while (current != nullptr) {
      Node *next = current->next;
      delete current->customer;
      delete current;
      current = next;
    }
  }
}

Customer *HashTable::getIdentification(const int id) {
  // Get customer information by ID from the hash table
  int index = hashFunction(id);

  Node *current = tableOfCustomers[index];

  while (current != nullptr) {
    if (current->id == id) {
      return current->customer;
    }
    current = current->next;
  }

  return nullptr;  // Customer not found
}

int HashTable::size() const {
    // Get the total number of customers in the hash table
    int size = 0;

    for (const auto& current : tableOfCustomers) {
        Node* currentNode = current;

        while (currentNode != nullptr) {
            size++;
            currentNode = currentNode->next;
        }
    }

    return size;
}

bool HashTable::remove(const int id) {
    // Remove a customer by ID from the hash table
    int index = hashFunction(id);
    Node* current = tableOfCustomers[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->id == id) {
            if (prev == nullptr) {
                tableOfCustomers[index] = current->next;
            } else {
                prev->next = current->next;
            }

            delete current;
            return true;  // Customer removed successfully
        }

        prev = current;
        current = current->next;
    }

    return false;  // Customer not found
}

void HashTable::showAllCustomerInfo() {
  // Display all customer information in the hash table
  for (int i = 0; i < MAXTABLESIZE; i++) {
    Node *current = tableOfCustomers[i];
    if (current != nullptr) {
      cout << "[" << setw(2) << setfill('0') << i << "] => ";

      while (current != nullptr) {
        string fullName = current->customer->getFirstName() + " " +
                          current->customer->getLastName();
        cout << "[" << current->id << " " << fullName << "] ";
        current = current->next;
      }

      cout << "\n";
    }
  }
}
