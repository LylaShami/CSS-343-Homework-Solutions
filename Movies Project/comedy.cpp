#include "comedy.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Default constructor for Comedy
Comedy::Comedy() {
  // Initialize member variables with default values
  setNumOfMovies(0);
  setNameOfDirector("");
  setMovieTitle("");
  setNameOfActorAndReleaseDate("");
  setReleaseYear(0);
  setMovieType(' ');
  setMediaType(' ');
}

// Function to split a string into a vector of strings using a delimiter
vector<string> Comedy::splitString(const string &str, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(str);
  // Loop to extract tokens from the string using the specified delimiter
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// Constructor that takes a string for parsing movie information
Comedy::Comedy(const string &line) {
  // Split the input line into parts using a comma as a delimiter
  vector<string> parts = splitString(line, ',');

  // Check if there are enough parts to create a Comedy movie
  if (parts.size() >= 5) {
    movieType = parts[0][0];
    movieStock = stoi(parts[1]);
    directorName = parts[2];
    movieTitle = parts[3];
    setReleaseYear(stoi(parts[4]));
  }
}

// Parameterized constructor for Comedy
Comedy::Comedy(int movieStock, string name, string movieTitle, int releaseDate, char movieType,
               char mediaType) {
  // Set the member variables with the provided values
  this->movieStock = movieStock;
  this->directorName = name;
  this->movieTitle = movieTitle;
  this->releaseYear = releaseDate;
  this->movieType = movieType;
  this->mediaType = mediaType;
}

// Destructor for Comedy
Comedy::~Comedy() {}

// Overloaded less than operator for comparing Comedy movies based on movieTitle
bool Comedy::operator<(const Movie &other) const {
  return movieTitle < other.getMovieTitle();
}

// Overloaded greater than operator for comparing Comedy movies based on movieTitle
bool Comedy::operator>(const Movie &other) const {
  return movieTitle > other.getMovieTitle();
}

// Overloaded equality operator for comparing Comedy movies based on movieTitle
bool Comedy::operator==(const Movie &other) const {
  return movieTitle == other.getMovieTitle();
}

// Overloaded inequality operator for comparing Comedy movies based on movieTitle
bool Comedy::operator!=(const Movie &other) const {
  return movieTitle != other.getMovieTitle();
}
