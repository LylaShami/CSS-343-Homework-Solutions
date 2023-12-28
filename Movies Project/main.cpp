/**
 * Driver for starting movie store tests
 */

#include "customer.h"
#include "store.h"
#include <iostream>

using namespace std;

int main() {
  // forward declaration, implementation in store_test.cpp
  void testAll();
  cout << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥Starting Storetest.cpp"
       << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥" << endl;
  testAll();
  cout << "Done." << endl;
  cout << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥"
       << endl;

Store myStore;

// Open and build the movie list
ifstream movies("data4movies.txt");
if (!movies) {
    cout << "File could not be opened." << endl;
    system("pause");
    return -1;
}
myStore.buildListForMovie(movies);

// Open and build the customer list
ifstream customers("data4customers.txt");
if (!customers) {
    cout << "File could not be opened." << endl;
    system("pause");
    return -1;
}
myStore.buildCustomerList(customers);
cout << "Testings data4customers.txt" << endl;
cout << "❅❅❅❅❅❅❅❅❅❅❅❅Customer Information"
     << "❅❅❅❅❅❅❅❅❅❅❅❅" << endl;
myStore.printAllCustomer();

// Open and process the commands
ifstream commands("data4commands.txt");
if (!commands) {
    cout << "File could not be opened." << endl;
    system("pause");
    return -1;
}
cout << "Testings data4commands.txt" << endl;
myStore.sortingMoviesAndCommandsFile(commands);

return 0;


}
