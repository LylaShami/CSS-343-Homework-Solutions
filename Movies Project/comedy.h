#ifndef COMEDY_H_
#define COMEDY_H_

#include "movie.h"  // Include the necessary header for the Movie class
#include <string>
#include <vector>


class Comedy : public Movie {
public:
  // Function to split a string into a vector of strings using a delimiter
 static  vector<string> splitString(const string &str, char delimiter = ',') ;

  // Default constructor for Comedy
  Comedy();

  // Constructor that takes a string for parsing movie information
  Comedy(const string &line);

  // Parameterized constructor for Comedy
  Comedy(int movieStock, string name, string movieTitle, int releaseDate, char movieType,
         char mediaType);

  // Destructor for Comedy
  virtual ~Comedy();

  // Overloaded less than operator for comparing Comedy movies
  virtual bool operator<(const Movie &other) const;

  // Overloaded greater than operator for comparing Comedy movies
  virtual bool operator>(const Movie &other) const;

  // Overloaded equality operator for comparing Comedy movies
  virtual bool operator==(const Movie &other) const;

  // Overloaded inequality operator for comparing Comedy movies
  virtual bool operator!=(const Movie &other) const;
};

#endif
