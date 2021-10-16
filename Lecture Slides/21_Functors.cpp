/* Functors.cpp
 *
 * Example of Functor creation and use
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * Created: 2013-12-04
 * Updated: 2015-04-08
 */

#include "20_List_with_Iterator.h"
#include <iostream>
using namespace std;


class GreaterN {
  //OVERVIEW: functor returns true if input is greater than limit
  int limit;
public:
  GreaterN(int limit_in) : limit(limit_in) {}
  bool operator() (int n) { return n > limit; }
};

class LessN {
  //OVERVIEW: functor returns true if input is less than limit
  int limit;
public:
  LessN(int limit_in) : limit(limit_in) {}
  bool operator() (int n) { return n < limit; }
};

class InRange {
  //OVERVIEW: functor returns true if input is within a range
  int min, max;
public:
  InRange(int min_in, int max_in)
  : min(min_in), max(max_in) {}

  bool operator() (int n) { return (min <= n) && (n <= max); }
};

//EFFECTS: returns true if pred() returns true for any of the elements in l
template <class Predicate>
bool any_of(const List<int> &l, Predicate pred) {
  for(List<int>::Iterator i=l.begin(); i!=l.end(); ++i)
    if (pred(*i)) return true;

  return false;
}

int main() {
  List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  GreaterN g6(6);
  cout << "any_of(l, g6) = " << any_of(l, g6) << endl;


  // functor version
  LessN is_solid(32);
  InRange is_liquid(33, 211);
  GreaterN is_gas(212);
  int temp = 96;
  cout << "is_solid " << is_solid(temp) << endl;
  cout << "is_liquid " << is_liquid(temp) << endl;
  cout << "is_gas " << is_gas(temp) << endl;
}
