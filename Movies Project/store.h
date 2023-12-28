#ifndef STORE_H
#define STORE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include <vector>
#include <string>

#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "hashtable.h"
#include "movie.h"

using namespace std;

class Store {
public:
  // Default constructor: Initializes the store and sets up movie lists and customer hashtable
  Store();

  // Destructor: Cleans up resources, including movie lists and customer hashtable
  ~Store();

  // Sorts a vector of movies based on the provided comparison function
  void sortMoviesByCriteria(vector<Movie*>& movies, function<bool(Movie*, Movie*)> compareFunction);
  

  // Adds a movie to the appropriate mediaType list (classic, comedy, or drama)
  void addMovieToList(Movie* movie, char genreType);

  // Builds the movie lists from the input file stream
  void buildListForMovie(ifstream &movies);

  // Builds the customer hashtable from the input file stream
  void buildCustomerList(ifstream &customers);

  // Returns the number of customers in the store
  int getNumOfCustomers();

  // Finds and returns a string representation of a customer by their ID
  string findByCustomerID(int id);

  // Removes a customer from the store by their ID
  bool removeByCustomerID(int id);

  // Adds a new customer to the store
  bool addCustomer(int id, string firstName, string lastName);

  // Updates the information of an existing customer in the store
  bool updateCustomerInfo(int id, string firstName, string lastName);

  // Prints details for all customers in the store
  void printAllCustomer();

  // Sorts movies and performs commands based on the input string command
  bool sortingMoviesAndCommands(string command);

  // Sorts movies and performs commands from an input file stream
  bool sortingMoviesAndCommandsFile(ifstream &commands);

  // Displays the rental history of a customer based on their ID
  bool showCustomerHistory(int id);

  // Finds the index of a substring in a string at a specified position
  int subStringAt(string str, int index, char sign);

private:
  // Updates the inventory of a movie by changing its stock
  bool updateMovieInventory(int stockChange, Movie *movie);

  HashTable listOfCustomers;   // Hashtable to store customer information
  vector<Movie *> moviesC;     // List of classic movies
  vector<Movie *> moviesD;     // List of drama movies
  vector<Movie *> moviesF;     // List of comedy movies
};

#endif // STORE_H
