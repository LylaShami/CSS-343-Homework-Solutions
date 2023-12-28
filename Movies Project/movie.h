#ifndef MOVIES_H_
#define MOVIES_H_

#include <iostream>
#include <string>
using namespace std;

class Movie {
  friend ostream &operator<<(ostream &out, const Movie & movie);

public:
  // Default constructor: Initializes movie attributes to default values
  Movie();

  // Parameterized constructor: Initializes movie attributes with provided values
  Movie(int movieStock, string name, string movieTitle, int releaseDate,
        char movieType, char mediaType);

  // Borrow a movie: Decreases the stock of available movies
  void borrowMovie();

  // Virtual destructor: Allows derived classes to override and clean up resources
  virtual ~Movie();

  // Get the number of movies borrowed by customers
  int getNumberOfMoviesBorrowed() const;

  // Set the number of movies borrowed
  void setNumberOfMoviesBorrowed(int movieStock);

  // Get the media type (e.g., DVD) of the movie
  char getMediaType() const;

  // Set the media type of the movie
  void setMediaType(char mediaType);

  // Get the title of the movie
  string getMovieTitle() const;

  // Set the title of the movie (static method shared among all instances)
  static void setMovieTitle(string movieTitle);

  // Get the current stock of available movies
  int getNumOfMovies() const;

  // Set the stock of available movies
  void setNumOfMovies(int movieStock);

  // Get the type of the movie (e.g., comedy, drama)
  char getMovieType() const;

  // Set the type of the movie
  void setMovieType(char movieType);

  // Get the name of the movie director
  string getNameOfDirector() const;

  // Set the name of the movie director
  void setNameOfDirector(string firstName);

  // Get the release year of the movie
  int getReleaseYear() const;

  // Set the release year of the movie (static method shared among all instances)
  static void setReleaseYear(int releaseYear);

  // Virtual function to get the name of the actor and release date
  virtual string getNameOfActorAndReleaseDate() const;

  // Virtual function to set the name of the actor and release date
  virtual void setNameOfActorAndReleaseDate(string actorAndReleaseYear);

protected:
 // Number of movies available for borrowing
  int remainingMovies;      
   // Number of movies currently borrowed by customers
  int numberOfMoviesBorrowed;   
   // Original stock of movies (before any borrowings) 
  int oldMovieStock;             
   // Actor's name and release date for specific movie types
  string actorNameAndReleaseDate;
   // Number of movies borrowed (for bookkeeping)
  int borrowedMovies;      
  // Name of the movie director      
  string directorName;     
    // Type of the movie (e.g., comedy, drama)       
  char movieType;  
    // Title of the movie             
  string movieTitle;     
    // Media type of the movie (e.g., DVD)       
  char mediaType;
   // Release year of the movie              
  int releaseYear;               
  // Current stock of available movies
  int movieStock;                 
};

#endif
