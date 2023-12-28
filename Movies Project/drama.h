#ifndef DRAMA_H_
#define DRAMA_H_

#include "movie.h"
#include <string>
#include <vector>

class Drama : public Movie {
public:
  // Function to split a string into parts using a specified delimiter
  vector<string> splitString(const string &str, char delimiter = ',');

  // Default constructor for Drama
  Drama();

  // Parameterized constructor for Drama, takes a string representation of a movie
  Drama(const string &line);

  // Parameterized constructor for Drama
  Drama(int movieStock, string name, string movieTitle, int releaseDate, char movieType,
        char mediaType);

  // Destructor for Drama
  virtual ~Drama();

  // Overridden less than operator for Drama movies
  virtual bool operator<(const Movie &other) const;

  // Overridden greater than operator for Drama movies
  virtual bool operator>(const Movie &other) const;

  // Overridden equality operator for Drama movies
  virtual bool operator==(const Movie &other) const;

  // Overridden inequality operator for Drama movies
  virtual bool operator!=(const Movie &other) const;
};

#endif
