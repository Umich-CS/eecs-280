/* Exceptions.cpp
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * Created: 2013-12-02
 * Modified: 2015-04-09
 */

#include <iostream>
using namespace std;

//Exception types
class NegativeError {};
class InputError {};

//REQUIRES: n >= 0
//EFFECTS: returns n!
int factorial (int n) {
  if (n<0) throw NegativeError();
  int result = 1;
  while (n > 0) {
    result *= n;
    n -= 1;
  }
  return result;
}

//EFFECTS: returns n choose k, throws an exception for negative input
int combination(int n, int k) {
  return factorial(n) / (factorial(k) * factorial(n-k));
}


////////////////////////////////////////////////////////////////////////////////
int main() {

  cout << "Enter commands like this \"factorial 3\" or \"combination 4 2\"" << endl;

  string f; //function
  int n; //number
  while (cin >> f >> n) {

    try {
      if (f == "factorial") {
        cout << factorial(n) << endl;
      } else if (f == "combination") {
        int k;
        cin >> k;
        cout << combination(n, k) << endl;
      } else {
        throw InputError();
      }

    } catch (NegativeError) {
      cout << "try again with a positive number" << endl;
    } catch (...) {
      cout << "try again" <<endl;
    }//try-catch

  }//while

}//main
