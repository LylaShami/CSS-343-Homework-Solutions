#include "customer.h"
#include <sstream>

// Default constructor for Customer
Customer::Customer() {
  ID = 0;
  firstName = "";
  lastName = "";
  transactionsInTotal = 0;
}

// Destructor for Customer
Customer::~Customer() {}

// Parameterized constructor for Customer
Customer::Customer(int id, string firstName, string lastName) {
    this->ID = id;

    if (!lastName.empty()) {
        this->lastName = lastName;
    }
    
    this->firstName = firstName;
    transactionsInTotal = 0;
}


// Getter for retrieving the first name of the customer
string Customer::getFirstName() const { return firstName; }

// Setter for setting the first name of the customer
void Customer::setFirstName(string firstname) { this->firstName = firstname; }

// Check if a movie is borrowed by the customer and update the transaction history
bool Customer::borrowedMovie(string action, string movieInfo) {
  if (transactionsInTotal == 0) {
    return false;
  }

  for (int i = transactionsInTotal - 1; i >= 0; i--) {
    if (customerTransactionHistory[i][1] == action &&
        customerTransactionHistory[i][0] == movieInfo) {
      return true;
    }
  }
  return false;
}

// Getter for retrieving the customer's ID
int Customer::getID() const { return ID; }

// Getter for retrieving the last name of the customer
string Customer::getLastName() const { return lastName; }

// Setter for setting the last name of the customer
void Customer::setLastName(string lastName) { this->lastName = lastName; }

// Record a transaction for the customer
void Customer::recordTransaction(string point, string operation) {
  customerTransactionHistory[transactionsInTotal][0] = point;
  customerTransactionHistory[transactionsInTotal][1] = operation;
  customerTransactionHistory[transactionsInTotal][2] = "";
  transactionsInTotal++;
  if (transactionsInTotal == 0) {
    cout << "    "
         << "No Recorded Transactions for Customer✎" << endl;
  }
}

// Getter for retrieving the total number of transactions for the customer
int Customer::getNumberOfTransactions() const { return transactionsInTotal; }

// Display the transaction history of the customer
void Customer::displayTransaction() {
  cout << "✉Transaction History for:  " << getFirstName()
       << " " << getLastName() << endl;
  int transactionNumber = 0;
  for (int i = 0; i < transactionsInTotal; i++) {
    cout << ++transactionNumber  << ". " << customerTransactionHistory[i][2] << " "
         << customerTransactionHistory[i][0] << " "
         << customerTransactionHistory[i][1] << endl;
  }
}
