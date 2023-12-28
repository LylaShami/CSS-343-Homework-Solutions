
#include "store.h"
#include <algorithm>
#include <iostream>

using namespace std;

// Default Constructor for Store
Store::Store() {}
// Destructor for Store Class
Store::~Store() {

  for (Movie *movie : moviesC) {
    delete movie;
  }

  for (Movie *movie : moviesD) {
    delete movie;
  }

  for (Movie *movie : moviesF) {
    delete movie;
  }
}

// Function to add a movie to the corresponding mediaType list
void Store::addMovieToList(Movie *movie, char genreType) {
  // Check the mediaType typeOfGenre  and add the movie to the appropriate list
  if (genreType == 'F') {
    // If the mediaType is 'F' (for Fantasy), add the movie to the Fantasy mediaType
    // list
    moviesF.push_back(movie);
  } else if (genreType == 'D') {
    // If the mediaType is 'D' (for Drama), add the movie to the Drama mediaType list
    moviesD.push_back(movie);
  } else if (genreType == 'C') {
    // If the mediaType is 'C' (for Comedy), add the movie to the Comedy mediaType list
    moviesC.push_back(movie);
  }
}

// Function to build a list of customers based on input from a file stream
void Store::buildCustomerList(ifstream &customers) {
  // Check if the file stream is open
  if (!customers.is_open()) {
    cout << "Error, can't open Customer File.☠" << endl;
    return;
  }

  string line;
  // Read each line from the file
  while (getline(customers, line)) {
    istringstream parsingThrough(line);
    int ID;
    string last;
    string first;

    // Attempt to extract customer information from the line
    if (parsingThrough >> ID >> last >> first) {
      // Check if the extracted information is valid
      if (ID != 0 && !first.empty() && !last.empty()) {
        // Create a new Customer object and insert it into the list of customers
        Customer *customerInfo = new Customer(ID, last, first);
        listOfCustomers.insert(customerInfo);
      } else {
        cout << "Invalid! Wrong Customer Entry☠:  " << line << endl;
      }
    } else {
      cout << "Error✘ Trouble Parsing for Customer:  " << line << endl;
    }
  }

  // Close the file stream
  customers.close();
}

// returns int getter funcion to get number of Customer
int Store::getNumOfCustomers() { return listOfCustomers.size(); }
// this function will help find customer by ID

string Store::findByCustomerID(int id) {
  // Search for Customer object with the given id
  Customer *search = listOfCustomers.getIdentification(id);

  // Check if the customer with the given id is found
  if (search != nullptr) {
    string firstName = search->getFirstName();
    string lastName = search->getLastName();

    // Return the full name of the person with the given id
    return firstName + " " + lastName;
  } else {
    // Return not found message for invalid ID
    return "The person with the given id is not found: Invalid ID";
  }
}

// Bool  function that take  id of customer to remove customer
bool Store::removeByCustomerID(int id) {
  // Search for Customer object with the given id
  Customer *search = listOfCustomers.getIdentification(id);

  // Check if the customer with the given id is found
  if (search != nullptr) {
    // Remove the customer from the list
    listOfCustomers.remove(id);

    // Delete the search pointer to avoid memory leaks
    delete search;

    // Return true for successful deletion
    return true;
  } else {
    // Return false if the customer with the given ID is not found
    return false;
  }
}

// function to add customer with their info
bool Store::addCustomer(int id, string firstName, string lastName) {
  // Search for Customer object with the given ID
  Customer *search = listOfCustomers.getIdentification(id);

  // Check if a customer with the given ID already exists
  if (search == nullptr) {
    // Create a new Customer object with the provided information
    Customer *customerToAdd = new Customer(id, firstName, lastName);

    // Add the new customer to the list
    listOfCustomers.insert(customerToAdd);

    // Return true for successful addition
    return true;
  } else {
    // Return false if a customer with the same ID already exists
    return false;
  }
}

bool Store::updateMovieInventory(int stockChange, Movie *movie) {
  // Ensure the movie pointer is valid
  if (!movie) {
    cout << "Invalid Movie☢" << endl;
    return false;
  }

  // Get the current movieStock of the movie
  int currentStock = movie->getNumOfMovies();

  // Calculate the new movieStock after applying the movieStock change
  int newMovieStock = currentStock + stockChange;

  // Check if the new movieStock is less than 0
  if (newMovieStock < 0) {
    cout << movie->getMovieTitle() << " Movie Not Available in Stock™" << endl;
    return false;
  }

  // Update the movieStock value
  movie->setNumOfMovies(newMovieStock);

  return true;
}

// function to update customer'stream info
bool Store::updateCustomerInfo(int id, string firstName, string lastName) {
  // Retrieve the pointer to the Customer object with the given ID
  Customer *customerToUpdate = listOfCustomers.getIdentification(id);

  // Check if a customer with the given ID is found
  if (customerToUpdate != nullptr) {
    // Update the first and last names of the customer
    customerToUpdate->setFirstName(firstName);
    customerToUpdate->setLastName(lastName);

    // Return true for successful update
    return true;
  } else {
    // Return false if no customer with the given ID is found
    return false;
  }
}

bool Store::sortingMoviesAndCommandsFile(ifstream &commands) {
  string line;
  // loop continues as long as there are lines in file it gets the line
  while (getline(commands, line)) {
    // calls excute commandSign on line which execute commandSign according to
    // commandSign input in the line
    sortingMoviesAndCommands(line);
  }
  // return false if no lines
  return false;
}

// Function to find the position of the 'index'-th occurrence of 'sign' in the
// string 'str' Returns the position of the character immediately after the
// 'index'-th occurrence of 'sign'
int Store::subStringAt(string str, int index, char sign) {
  int count = 0;             // Counter for the number of occurrences found
  int dependentPosition = 0; // Position of the character immediately after the
                             // 'index'-th occurrence

  // Iterate through each character in the string
  for (int i = 0; i < str.length(); i++) {
    // Check if the current character is the target 'sign'
    if (str[i] == sign) {
      count++; // Increment the occurrence count
    }

    // Check if the required 'index'-th occurrence is reached
    if (count == index) {
      dependentPosition = i; // Set the position to the current index
    }
  }

  // Return the position of the character immediately after the 'index'-th
  // occurrence of 'sign'
  return (dependentPosition + 1);
}
// this function displays customerTransactionHistory of all transaction of
// customer
bool Store::showCustomerHistory(int id) {
  // pointer to customer object called customer
  Customer *customer;
  // retrieves customer object from customer list based on id given and stores
  // it into temporary customer pointer

  customer = listOfCustomers.getIdentification(id);
  if (customer == 0) {

    delete customer;
  }
  // edge case: if customer'stream number of transaction are 0
  if (customer->getNumberOfTransactions() == 0) {
    // prints error
    cout << "There is no customer Transaction History for: "
         << customer->getFirstName() << " " << customer->getLastName() << endl;
    return false;
  } else
    // else returns summary of all transactions of customer
    cout << "Summary Transactions for Customer" << endl;

  customer->displayTransaction();
  return true;
}

// Function to print information for all customers in the store
void Store::printAllCustomer() {
  // Iterate through each customer in the list of customers
  for (const auto &customer : listOfCustomers.retrieveAllCustomerInfo()) {
    // Print customer information, including ID and full name
    cout << "\t"
         << "Customer ID: " << customer->getID() << " Full Name: "
         << " " << customer->getFirstName() << " " << customer->getLastName()
         << endl;
  }
}

void Store::sortMoviesByCriteria(
    vector<Movie *> &movies, function<bool(Movie *, Movie *)> compareFunction) {
  sort(movies.begin(), movies.end(), compareFunction);
}

// function to execute all commandSign takes in the commandSign line as
// parameter
bool Store::sortingMoviesAndCommands(string commandSign) {
  // if first index of commandSign line if 'I'
  if (commandSign[0] == 'I') {
    sortMoviesByCriteria(moviesF, [](Movie *a, Movie *b) {
      if (a->getMovieTitle() != b->getMovieTitle()) {
        return a->getMovieTitle() < b->getMovieTitle();
      } else {
        return a->getReleaseYear() < b->getReleaseYear();
      }
    });

    // Sort the Drama movies by Director, then movieTitle
    sortMoviesByCriteria(moviesD, [](Movie *a, Movie *b) {
      if (a->getNameOfDirector() != b->getNameOfDirector()) {
        return a->getNameOfDirector() < b->getNameOfDirector();
      } else {
        return a->getMovieTitle() < b->getMovieTitle();
      }
    });

    // Sort the Classic movies by Release date, then Major actor
    sortMoviesByCriteria(moviesC, [](Movie *a, Movie *b) {
      if (a->getReleaseYear() != b->getReleaseYear()) {
        return a->getReleaseYear() < b->getReleaseYear();
      } else {
        return a->getNameOfActorAndReleaseDate() <
               b->getNameOfActorAndReleaseDate();
      }
    });

  // Display inventory list of all items in the store
cout << "★★★★★★★★★★★★★★★★Inventory List of all Items in Store★★★★★★★★★★★★★★★★" << endl;

// Display genres for Comedy, Drama, and Classic movies
cout << "\n ♛♛♛♛♛Genre'stream(Media typeOfGenre ) For Comedy, Drama and Classic Movies♛♛♛♛♛" << endl;

// Display Comedy movies
cout << "Comedy";
for (Movie *movieF : moviesF) {
    // Display movie details: media type, movie type, number of movies, director, title, and release year
    cout << "\t" << movieF->getMediaType() << " " << movieF->getMovieType() << " " << movieF->getNumOfMovies()
         << " " << movieF->getNameOfDirector() << " " << movieF->getMovieTitle() << " " << movieF->getReleaseYear() << endl;
}

// Display Drama movies
cout << "Drama" << endl;
for (Movie *movieD : moviesD) {
    // Display movie details: media type, movie type, number of movies, director, title, and release year
    cout << "\t" << movieD->getMediaType() << " " << movieD->getMovieType() << " " << movieD->getNumOfMovies()
         << " " << movieD->getNameOfDirector() << " " << movieD->getMovieTitle() << " " << movieD->getReleaseYear() << endl;
}

// Display Classic movies
cout << "Classic" << endl;
for (Movie *movieC : moviesC) {
    // Display movie details: media type, movie type, number of movies, director, title, and actor/release date
    cout << "\t" << movieC->getMediaType() << " " << movieC->getMovieType() << " " << movieC->getNumOfMovies()
         << " " << movieC->getNameOfDirector() << " " << movieC->getMovieTitle() << " " << movieC->getNameOfActorAndReleaseDate() << endl;
}

// Display borrowed and remaining movies for each media type (Genre)
cout << "\n✯✯✯✯✯✯✯✯✯Borrowed and Remaining Movies for Each mediaType (Media typeOfGenre )✯✯✯✯✯✯✯✯✯✯ " << endl;

// Display total borrowed and remaining movies for Comedy
cout << "\n✿ Total Borrowed Movies and Remaining Movies for Comedy✿" << endl;
for (Movie *movieF : moviesF) {
    ifstream inFile("data4movies.txt");
    if (!inFile) {
        cout << "Failed to open the file.✘ Please Try again" << endl;
        return false;
    }

    string line;
    getline(inFile, line);

    istringstream issued(line);
    char character;
    int dependingNumber;

    string characterOfStrings;
    getline(issued, characterOfStrings, ',');
    istringstream(characterOfStrings) >> character;

    string numberOfStrings;
    getline(issued, numberOfStrings);
    istringstream(numberOfStrings) >> dependingNumber;

    inFile.close();

    // Display movie title, director, release year, borrowed movies, and remaining movies
    cout << movieF->getMovieTitle() << "(" << movieF->getNameOfDirector() << ", " << movieF->getReleaseYear() << ") "
         << " Borrowed Movies: " << dependingNumber - movieF->getNumOfMovies() << "\n"
         << " The amount of Movies Remaining: " << movieF->getNumOfMovies() << endl;
}

// Display total borrowed and remaining movies for Drama
cout << "\n☂ Total Borrowed Movies and Remaining Movies for Drama☂" << endl;
for (Movie *movieD : moviesD) {
    ifstream inFile("data4movies.txt");
    if (!inFile) {
        cout << "Failed to open the file.✘ Please Try Again " << endl;
        return false;
    }

    string line;
    getline(inFile, line);

    istringstream issued(line);
    char character;
    int dependingNumber;

    string characterOfStrings;
    getline(issued, characterOfStrings, ',');
    istringstream(characterOfStrings) >> character;
    string numberOfStrings;
    getline(issued, numberOfStrings);
    istringstream(numberOfStrings) >> dependingNumber;

    inFile.close();

    // Display movie title, borrowed movies, and remaining movies for Drama
    cout << movieD->getMovieTitle() << "Borrowed Movies: " << dependingNumber - movieD->getNumOfMovies() << "\n"
         << "The amount of Movies Remaining: " << movieD->getNumOfMovies() << endl;
}

// Display total borrowed and remaining movies for Classic
cout << "\n✪ Total Borrowed Movies and Remaining Movies for Classic✪" << endl;
for (Movie *movieC : moviesC) {
    ifstream inFile("data4movies.txt");
    if (!inFile) {
        cout << "Failed to open the file.✘ Please Try Again" << endl;
        return false;
    }

    string line;
    getline(inFile, line);

    istringstream issued(line);
    char character;
    int dependingNumber;

    string characterOfStrings;
    getline(issued, characterOfStrings, ',');
    istringstream(characterOfStrings) >> character;

    string numberOfStrings;
    getline(issued, numberOfStrings);
    istringstream(numberOfStrings) >> dependingNumber;

    inFile.close(); // Close the input file

    // Display movie title, actor/release date, borrowed movies, and remaining movies for Classic
    cout << movieC->getMovieTitle() << "(" << movieC->getNameOfActorAndReleaseDate() << ")"
         << "Borrowed Movies: " << dependingNumber - movieC->getNumOfMovies() << "\n"
         << "The amount of Movies Remaining: " << movieC->getNumOfMovies() << endl;
}

  } else if (commandSign[0] == 'H') {
    // Extracting typeOfGenre and ID from the commandSign using stringstream
    stringstream stream(commandSign);
    string typeOfGenre;
    string ID;

    stream >> typeOfGenre >> ID;

    // Converting ID to an integer
    int id = atoi(ID.c_str());

    // Calling the showCustomerHistory function with the extracted ID
    showCustomerHistory(id);
  }

  else if (commandSign[0] == 'B' || commandSign[0] == 'R') {
    // Declare variables to store information extracted from the commandSign
    string typeOfGenre;
    string actionDependent;
    int ID;
    char mediaType;
    // Create a stringstream to extract information from the commandSign
    stringstream stream;
    stream << commandSign;
    stream >> actionDependent;
    stream >> ID;
    stream >> typeOfGenre;
    stream >> mediaType;
    // Retrieve the customer object based on the extracted ID
    Customer *customer = listOfCustomers.getIdentification(ID);
    // Check if the customer with the specified ID exists
    if (customer == nullptr) {
      cout << "There is No Customer with this ID✎ " << ID << endl;
      return false; // Return false as the operation cannot proceed without a
                    // valid customer
    }

    if (mediaType == 'F') {
      // Extract the positions of the relevant substrings in the commandSign
      int firstPosition = subStringAt(commandSign, 3, ' ');
      int secondPosition = subStringAt(commandSign, 0, ',');

      // Extract the movie title using substr based on the positions
      string movieTitle =
          commandSign.substr(firstPosition, (secondPosition - firstPosition));
      // Extract information substring
      string info = commandSign.substr(0);

      // Iterate through the moviesF vector to find the matching movieTitle
      for (int i = 0; i < moviesF.size(); i++) {
        if (moviesF[i]->getMovieTitle() == movieTitle) {

          if (commandSign[0] == 'B') {
            // Record the transaction and update movie inventory for borrowing
            customer->recordTransaction(commandSign, "Borrowed♾️");

            updateMovieInventory(-1, moviesF[i]);

            return true;
          }
          // Check if the command is for returning
          if (commandSign[0] == 'R') {
            // Check if the customer is not nullptr

            if (customer != nullptr) {
              // Record the transaction and update movie inventory for returning

              customer->recordTransaction(commandSign, "Returned☮");
              updateMovieInventory(1, moviesF[i]);

              return true;
            } 
            
              cout << "Customer not found✘" << endl;
            
          }
        }
      }
      // If the movieTitle is not found in the moviesF vector

      cout << "Movie:" << movieTitle << "is not found✪: " << commandSign
           << "Transaction failed✄" << endl;
    }
    if (mediaType == 'D') {

      int firstPosition = subStringAt(commandSign, 3, ' ');
      int secondPosition = subStringAt(commandSign, 0, ',');
      string direction =
          commandSign.substr(firstPosition, (secondPosition - firstPosition));

      firstPosition = subStringAt(commandSign, 0, ',');
      secondPosition = subStringAt(commandSign, 1, ',');
      string movieTitle = commandSign.substr(
          firstPosition + 1, (secondPosition - firstPosition) - 1);
      // check every movies
      for (int i = 0; i < moviesD.size(); i++) {

        if (moviesD[i]->getMovieTitle() == movieTitle) {
          // if the command sign is 'C'
          if (commandSign[0] == 'B') {
            customer->recordTransaction(commandSign, "Borrowed♾️");

            updateMovieInventory(-1, moviesD[i]);

            return true;
          }
          // if the command sign is 'R'
          if (commandSign[0] == 'R') {

            // and if customer is not nullptr
            if (customer != nullptr) {

              // record transaction as returned
              customer->recordTransaction(commandSign, "Returned☮");
              //and update movie inventory for returning
              updateMovieInventory(1, moviesD[i]);

              return true;
            } else {
              cout << "Customer not found✘" << endl;
            }
          }
        }
      }
      cout << "Movie:" << movieTitle << "is not found✪:" << commandSign
           << "Transaction failed✄" << endl;
    }

    // Check if the mediaType is 'C'
    if (mediaType == 'C') {
      // Extract the positions of the relevant substrings in the commandSign
      int firstPosition = subStringAt(commandSign, 3, ' ');
      int secondPosition = subStringAt(commandSign, 5, ' ');

      // Extract the release year using substr based on the positions
      string ownYear =
          commandSign.substr(firstPosition, (secondPosition - firstPosition));

      // Reset positions to extract actor's name
      firstPosition = subStringAt(commandSign, 5, ' ');
      secondPosition = commandSign.length();

      // Extract the actor's name using substr based on the new positions
      string actionDependent = commandSign.substr(
          firstPosition + 1, (secondPosition - firstPosition) - 1);

      // Check every movie in the moviesC vector
      for (int i = 0; i < moviesC.size(); i++) {
        // If the actor's name and release year match
        if (moviesC[i]->getNameOfActorAndReleaseDate() ==
            (" " + actionDependent + ownYear)) {
          // Check if the command is for borrowing
          if (commandSign[0] == 'B') {
            // Check if the customer is not nullptr
            if (customer != nullptr) {
              // Record the transaction and update movie inventory for borrowing
              customer->recordTransaction(commandSign, "Borrowed♾️");
              updateMovieInventory(-1, moviesC[i]);
              return true;
            } else {
              cout << "Customer not found✘" << endl;
            }
          }

          // Check if the command is for returning

          if (commandSign[0] == 'R') {
            // Check if the customer is not nullptr

            if (customer != nullptr) {
              // Record the transaction and update movie inventory for returning

              customer->recordTransaction(commandSign, "Returned☮");
              updateMovieInventory(1, moviesC[i]);

              return true;
            } else {
              cout << "Movie:" << actionDependent
                   << "is not found✪: " << commandSign << "Transaction failed✄"
                   << endl;
            }
          }
        }
      }
      // If the actor's name and release year are not found in the moviesC
      // vector

      cout << commandSign << "not found" << endl;
    }

  }

  else {
    // If the mediaType is not 'C', print an error message

    cout << "Invalid Command✘ Please Try Again." << commandSign[0] << endl;
    return false;
  }
  // If the command is successfully processed, return true
  return true;
}

// Function to build movie lists based on input from a file stream
void Store::buildListForMovie(ifstream &movies) {
  // Check if the file stream is open
  if (!movies.is_open()) {
    cout << "Error opening movie file" << endl;
    return;
  }

  string line;
  // Read each line from the file
  while (getline(movies, line)) {
    istringstream parsingThrough(line);
    string mediaType;
    // Extract mediaType from the line
    if (getline(parsingThrough, mediaType, ',')) {
      // Check if the mediaType is valid (F, D, or C)
      if (mediaType == "F" || mediaType == "D" || mediaType == "C") {
        string movieStock;
        string director;
        string movieTitle;
        string year;

        // Extract movie details from the line
        if (getline(parsingThrough, movieStock, ',') &&
            getline(parsingThrough, director, ',') &&
            getline(parsingThrough, movieTitle, ',') &&
            getline(parsingThrough, year, ',')) {

          // Check for invalid movie entries (empty fields)
          if (movieStock.empty() || director.empty() || movieTitle.empty() ||
              year.empty()) {
            cout << "Invalid movie entry: " << line << endl;
            continue;
          }

          Movie *movie = nullptr;

          // Create a movie object based on the mediaType
          if (mediaType == "F") {
            // Fantasy movie
            movie = new Movie(stoi(movieStock), director, movieTitle,
                              stoi(year), 'D', 'F');
          } else if (mediaType == "D") {
            // Drama movie
            movie = new Movie(stoi(movieStock), director, movieTitle,
                              stoi(year), 'D', 'D');
          } else if (mediaType == "C") {
            // Classic movie
            size_t spaceForPosition = year.find_last_of(' ');
            string actorsName = year.substr(0, spaceForPosition);
            string stringForYear = year.substr(spaceForPosition + 1);
            int releaseYear = stoi(stringForYear);

            movie = new Classic(stoi(movieStock), director, movieTitle,
                                actorsName + " " + to_string(releaseYear),
                                releaseYear, 'D', 'C');
          }

          // Add the movie to the appropriate mediaType list
          if (movie) {
            addMovieToList(movie, mediaType[0]);
          } else {
            cout << "Invalid mediaType typeOfGenre : " << mediaType << endl;
          }
        } else {
          cout << "Invalid movie entry: " << line << endl;
        }
      } else {
        cout << "Invalid mediaType typeOfGenre : " << mediaType << endl;
      }
    }
  }

  // Close the file stream
  movies.close();
}
