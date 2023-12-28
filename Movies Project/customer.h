#ifndef CUSTOMER_H
#define CUSTOMER_H
#define MAXLOG 1000

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Customer {
public:
  // Default constructor for Customer
  Customer();

  // Destructor for Customer
  ~Customer();

  // Parameterized constructor for Customer
  Customer(int id, string firstName, string lastName);

  // Getter for retrieving the first name of the customer
  string getFirstName() const;

  // Setter for setting the first name of the customer
  void setFirstName(string firstname);

  // Getter for retrieving the customer's ID
  int getID() const;

  // Setter for setting the customer's ID
  void setID();

  // Getter for retrieving the last name of the customer
  string getLastName() const;

  // Setter for setting the last name of the customer
  void setLastName(string lastName);

  // Record a transaction for the customer
  void recordTransaction(string point, string operation);

  // Display the transaction history of the customer
  void displayTransaction();

  // Getter for retrieving the total number of transactions for the customer
  int getNumberOfTransactions() const;

  // Setter for setting the total number of transactions for the customer
  void setNumberOfTransactions();

  // Check if a movie is borrowed by the customer and update the transaction history
  bool borrowedMovie(string action, string movieInfo);

private:
  // Map to store movies available for the customer
  map<int, string> availableForCustomer;

  // Customer's ID
  int ID;

  // Total number of transactions for the customer
  int transactionsInTotal;

  // Customer's first name
  string firstName;

  // Customer's last name
  string lastName;

  // Customer's transaction history array
  string customerTransactionHistory[MAXLOG][3];
};
#endif