#include "movie.h"


// Default constructor for Movie class
Movie::Movie() {
  // Initialize member variables with default values
  setNumOfMovies(0);
  setNameOfDirector("");
  setMovieTitle("");
  setNameOfActorAndReleaseDate("");
  setReleaseYear(0);
  setMovieType(' ');
  oldMovieStock = 0;
}

// Parameterized constructor for Movie class
Movie::Movie(int movieStock, string name, string movieTitle, int releaseDate, char movieType, char mediaType) {
  // Set member variables using provided arguments
  this->movieStock = movieStock;
  this->directorName = name;
  this->movieTitle = movieTitle;
  this->releaseYear = releaseDate;
  this->movieType = movieType;
  this->mediaType = mediaType;
  this->oldMovieStock = movieStock;
}

// Destructor for Movie class
Movie::~Movie() {
  // No dynamic memory to deallocate, so empty destructor
}

// Function to borrow a movie
void Movie::borrowMovie() {
  // Check if there are available copies of the movie
  if (movieStock > 0) {
    // Decrement the available movie stock
    movieStock--;
  } else {
    // Print a message if no copies are available
    cout << "That Movie is not available, that movie is out of stock:( Sorry!)" << endl;
  }
}

// getter function to get director first name
string Movie::getNameOfDirector() const { return directorName; }

/// setter function to set director first name
void Movie::setNameOfDirector(string firstName) { directorName = firstName; }

// function to get all number of movies in the store set
int Movie::getNumOfMovies() const { return movieStock; }

// function to set number of movies in store
void Movie::setNumOfMovies(int movieStock) { this->movieStock = movieStock; }

// returns char  getter function for getting movieType of movie in store set

char Movie::getMovieType() const { return movieType; }

// function to set movieType of movie
void Movie::setMovieType(char movieType) { movieType = movieType; }

// function to get Actor and releaseDate information
string Movie::getNameOfActorAndReleaseDate() const {
  return actorNameAndReleaseDate;
}

// function to set Actor and releaseDate information
void Movie::setNameOfActorAndReleaseDate(string actorAndReleaseYear) {
  actorNameAndReleaseDate = actorAndReleaseYear;
}

// function to get mediaType of movie
char Movie::getMediaType() const { return mediaType; }

// function to set mediaType of movie
void Movie::setMediaType(char mediaType) { mediaType = mediaType; }

// getter function to  get movieTitle of movie
string Movie::getMovieTitle() const { return movieTitle; }

// setter function to set movieTitle of movie
void Movie::setMovieTitle(string movieTitle) { movieTitle = movieTitle; }

// getter function to get releaseDate year
int Movie::getReleaseYear() const { return releaseYear; }

// setter function to set releaseDate year
void Movie::setReleaseYear(int releaseYear) { releaseYear = releaseYear; }

// ostream to help print movie movieTitle
ostream &operator<<(ostream &out, const Movie &movie) {
  out << movie.getMovieTitle() << endl;
  return out;
}