# Self-Evaluation

## Name(s): Lyla Shami 

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes/No
Yes 
- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: ENTER_NUMBER
5
- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: full
History: full
Borrow: full
Return: full


Q: -1 for each compilation warning, min -3: ENTER_NUMBER

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: ENTER_NUMBER
0

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: ENTER_NUMBER
0

- Check under *4. clang-format does not find any formatting issues*


Q: -2 for any detected memory leak: ENTER_NUMBER
0
- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: ENTER_NUMBER


- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): ENTER_NUMBER
0
- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: in the store.cpp under the sorting movies and commands method

invalid movie type: in store.cpp in update movie inventory method

invalid customer ID: in store.cpp under get Number of customers
 
invalid movie: in store.cpp under the buildlist for movie method

factory classes: classic.cpp, classic.cpp and drama.cpp are all in the project

hashtable: The hashtable class is in the project, and the hashtable for this project was storing the customer information such as the id, and first name and last name of customer to the hashtable.

container used for comedy movies: a vector in store.cpp

function for sorting comedy movies: All the sorting for the each genre is being done in the store class. 

function where comedy movies are sorted: sorting movies and commands funtion in store.cpp 

functions called when retrieving a comedy movie based on title and year: I used the vector so under the moviesC which is for comedy you call the getMovieTitle, and get releasedate and year. under store.cpp

functions called for retrieving and printing customer history: its under the customer class under the getname and setname and id showing transaction history. 

container used for customer history: a vector under store.cpp 

functions called when borrowing a movie: borrowed movie funciton under customer class

explain borrowing a movie that does not exist: if the customer tries to buy it, it shows up as a movie that does not exist

explain borrowing a movie that has 0 stock: it tells the customer that the movie is unavailable because it is out of stock

explain returning a movie that customer has not checked out: It explains to customer that the movie being returned has not yet been checked out.

any static_cast or dynamic_cast used: no


Q: Total points: ADD_ALL_POINTS (max 25)
24