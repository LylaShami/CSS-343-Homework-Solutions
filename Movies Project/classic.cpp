#include "classic.h"
#include <sstream>
#include <string>
#include <vector>


using namespace std;

// Function to split a string into a vector of strings using a delimiter
vector<string> Classic::splitString(const string& str, char delimiter)  {
  vector<string> tokens;
  istringstream tokenStream(str);
  string token;
  // Loop to extract tokens from the string using the specified delimiter
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// Default constructor for Classic
Classic::Classic() {
  setNumOfMovies(0);
  setNameOfDirector("");
  setMovieTitle("");
  setNameOfActorAndReleaseDate("");
  setReleaseYear(0);
  setMovieType(' ');
  setMediaType(' ');
}

// Constructor that takes a string for parsing movie information
Classic::Classic(const string &line) {
  // Split the input line into parts using a comma as a delimiter
  vector<string> parts = splitString(line, ',');

  // Check if there are enough parts to create a Classic movie
  if (parts.size() >= 5) {
    movieType = parts[0][0];
    movieStock = stoi(parts[1]);
    directorName = parts[2];
    movieTitle = parts[3];
    actorNameAndReleaseDate = parts[4];
  } 
}

// Parameterized constructor for Classic
Classic::Classic(int movieStock, string name, string movieTitle, string actorNameAndReleaseDate,
                 int releaseDate, char movieType, char mediaType) {
  // Set the member variables with the provided values
  this->movieStock = movieStock;
  this->directorName = name;
  this->movieTitle = movieTitle;
  this->actorNameAndReleaseDate = actorNameAndReleaseDate;
  this->releaseYear = releaseDate;
  this->movieType = movieType;
  this->mediaType = mediaType;
}

// Destructor for Classic
Classic::~Classic() {}

// Setter for the name of the actor and release date
void Classic::setNameOfActorAndReleaseDate(string actorNameAndReleaseDate) {
  actorNameAndReleaseDate = actorNameAndReleaseDate;
}

// Getter for the name of the actor and release date
string Classic::getNameOfActorAndReleaseDate() { return actorNameAndReleaseDate; }

// Overloaded less than operator for comparing Classic movies based on actorNameAndReleaseDate
bool Classic::operator<(Classic &other) const {
  return actorNameAndReleaseDate < other.getNameOfActorAndReleaseDate();
}

// Overloaded greater than operator for comparing Classic movies based on actorNameAndReleaseDate
bool Classic::operator>(Classic &other) const {
  return actorNameAndReleaseDate > other.getNameOfActorAndReleaseDate();
}

// Overloaded equality operator for comparing Classic movies based on actorNameAndReleaseDate
bool Classic::operator==(Classic &other) const {
  return actorNameAndReleaseDate == other.getNameOfActorAndReleaseDate();
}

// Overloaded inequality operator for comparing Classic movies based on actorNameAndReleaseDate
bool Classic::operator!=(Classic &other) const {
  return actorNameAndReleaseDate != other.getNameOfActorAndReleaseDate();
}
