/* Container.cpp
 * 
 * Example of an abstract data type representing a set of integers
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2013-05-30
 */

#include <iostream> //cout, endl
#include <cassert>  //assert
using namespace std;


class IntSet {
  // OVERVIEW: mutable set of ints with bounded size
 public:

  //EFFECTS: creates a zero-size IntSet
  IntSet();

  //REQUIRES: set is not full
  //MODIFIES: this
  //EFFECTS: set=set+{v}
  void insert(int v);

  //REQUIRES: v is in set
  //MODIFIES: this
  //EFFECTS: set=set-{v}
  void remove(int v);

  //EFFECTS: returns true if v is in set,
  //false otherwise
  bool query(int v) const;

  //EFFECTS: returns |set|
  int size() const;

  //EFFECTS: prints set
  void print() const;

  //maximum size of a set
  static const int ELTS_CAPACITY = 100;

private:
  //Represent a set of size N as an sorted set of integers, with no 
  //duplicates, stored in the first N slots of the array
  int elts[ELTS_CAPACITY];

  //Number of elements currently in the set
  int elts_size;

  //EFFECTS: returns the index of v if it exists in the set, ELTS_CAPACITY otherwise
  int indexOf(int v) const;
};


////////////////////////////////////////////////////////////////////////////////
//ADT definition (member function implementations)
IntSet::IntSet()
  : elts_size(0) {}


void IntSet::insert(int v) {
  assert(elts_size < ELTS_CAPACITY); //REQUIRES set is not full

  if (query(v)) return; //already there
  int cand = elts_size-1; //largest element

  while ((cand >= 0) && elts[cand] > v) {
    elts[cand+1] = elts[cand];
    --cand;
  }

  //Now, cand points to the left of the "gap".
  elts[cand+1] = v;
  ++elts_size; //repair invariant
}


void IntSet::remove(int v) {
  int gap = indexOf(v);

  if (gap == ELTS_CAPACITY) return; //not found
  --elts_size; //one less element

  while (gap < elts_size) {
    //there are elts to our right
    elts[gap] = elts[gap+1];
    ++gap;
  }
}


int IntSet::size() const {
  return elts_size;
}


int IntSet::indexOf(int v) const {
  int left = 0;
  int right = elts_size-1;

  while (right >= left) {
    int elts_size = right - left + 1;
    int middle = left + elts_size/2;
    if (elts[middle] == v)
      return middle;
    else if (elts[middle] < v)
      left = middle+1;
    else
      right = middle-1;
  }

  return ELTS_CAPACITY;
}


bool IntSet::query(int v) const {
  return (indexOf(v) != ELTS_CAPACITY);
}


void IntSet::print() const {
  cout << "{ ";
  for (int i=0; i<elts_size; ++i)
    cout << elts[i] << " ";
  cout << "} "<< endl;
}


////////////////////////////////////////////////////////////////////////////////
int main () {
  IntSet is;
  is.insert(7);
  is.insert(4);
  is.insert(7);
  is.print();
  is.remove(7);
  is.print();
}
