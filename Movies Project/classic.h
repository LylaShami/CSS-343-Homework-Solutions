#ifndef CLASSIC_H_
#define CLASSIC_H_

#include "movie.h"  // Include the necessary header for Movie class
#include <string>
#include <vector>

using namespace std;

class Classic : public Movie {
public:
  // Default constructor
  Classic();

  // Constructor that takes a string for parsing movie information
  Classic(const string &line);

  // Parameterized constructor
  Classic(int movieStock, string name, string movieTitle, string actorNameAndReleaseDate,
          int release, char movieType, char mediaType);

  // Function to split a string into a vector of strings using a delimiter
  static vector<string> splitString(const string& str, char delimiter = ',');

  // Destructor
  virtual ~Classic();

  // Setter for the name of the actor and release date
  void setNameOfActorAndReleaseDate(string actorNameAndReleaseDate);

  // Getter for the name of the actor and release date
  string getNameOfActorAndReleaseDate();

  // Overloaded less than operator for comparing Classic movies
  bool operator<(Classic &other) const;

  // Overloaded greater than operator for comparing Classic movies
  bool operator>(Classic &other) const;

  // Overloaded equality operator for comparing Classic movies
  bool operator==(Classic &other) const;

  // Overloaded inequality operator for comparing Classic movies
  bool operator!=(Classic &other) const;
};

#endif
