#include "drama.h"
#include <sstream>

// Default constructor for Drama class
Drama::Drama() {
  setNumOfMovies(0);
  setNameOfDirector("");
  setMovieTitle("");
  setNameOfActorAndReleaseDate("");
  setReleaseYear(0);
  setMovieType(' ');
  setMediaType(' ');
}

// Helper function to split a string based on a delimiter
vector<string> Drama::splitString(const string &str, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(str);
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// Constructor that initializes Drama object using a string line
Drama::Drama(const string &line) {
  // Split the input line into parts based on commas
  vector<string> parts = splitString(line, ',');

  // If there are at least 5 parts, extract and set relevant information
  if (parts.size() >= 5) {
    movieType = parts[0][0];
    movieStock = stoi(parts[1]);
    directorName = parts[2];
    movieTitle = parts[3];
    releaseYear = stoi(parts[4]);
  }
}

// Parameterized constructor for Drama class
Drama::Drama(int movieStock, string name, string movieTitle, int releaseDate, char movieType, char mediaType) {
  // Set member variables using provided arguments
  movieStock = movieStock;
  directorName = name;
  movieTitle = movieTitle;
  releaseYear = releaseDate;
  movieType = movieType;
  mediaType = mediaType;
}

// Destructor for Drama class
Drama::~Drama() {}

// Overloaded less-than operator for Drama class based on director's name
bool Drama::operator<(const Movie &other) const {
  return directorName < other.getNameOfDirector();
}

// Overloaded greater-than operator for Drama class based on director's name
bool Drama::operator>(const Movie &other) const {
  return directorName > other.getNameOfDirector();
}

// Overloaded equality operator for Drama class based on director's name
bool Drama::operator==(const Movie &other) const {
  return directorName == other.getNameOfDirector();
}

// Overloaded inequality operator for Drama class based on director's name
bool Drama::operator!=(const Movie &other) const {
  return directorName != other.getNameOfDirector();
}
