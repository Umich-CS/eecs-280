/* IntSet.cpp
 * 
 * Abstract data type representing a set of integers
 * Dynamically sized and includes Big 3 (destructor, copy constructor and
 * overload assignment operator
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2013-11-07
 */

#include <iostream> //cout, endl
#include <cassert>  //assert
using namespace std;


class IntSet {
  // OVERVIEW: mutable set of ints
 public:

  //EFFECTS:  constructor creates an IntSet with specified capacity
  //REQUIRES: capacity > 0
  IntSet(int capacity = ELTS_CAPACITY_DEFAULT);

  //EFFECTS: copy constructor creates an IntSet that is a (deep) copy of other
  IntSet(const IntSet &other);

  //EFFECTS: destroys this IntSet
  ~IntSet();

  //EFFECTS: assignment operator does a deep copy
  IntSet & operator= (const IntSet &rhs);

  //MODIFIES: this
  //EFFECTS: set=set+{v}
  void insert(int v);

  //REQUIRES: v is in set
  //MODIFIES: this
  //EFFECTS: set=set-{v}
  void remove(int v);

  //EFFECTS: returns true if v is in set, false otherwise
  bool query(int v) const;

  //EFFECTS: returns |set|
  int size() const;

  //EFFECTS: prints set
  void print() const;

private:
  //Represent a set of size N as an sorted set of integers, with no 
  //duplicates, stored in the first N slots of the array
  int *elts; // pointer to dynamic array

  //Number of elements currently in the set
  int elts_size;

  //Maximum capacity of current array
  int elts_capacity;

  //Default capacity of array
  static const int ELTS_CAPACITY_DEFAULT = 100;

  //EFFECTS: returns the index of v if it exists in the set, ELTS_CAPACITY_DEFAULT otherwise
  int indexOf(int v) const;

  //EFFECTS   enlarges the elts arrays, preserving contents
  //MODIFIES: this
  void grow();
};


////////////////////////////////////////////////////////////////////////////////
//ADT definition (member function implementations)

IntSet::IntSet(int capacity)
  : elts_size(0), elts_capacity(capacity) {
  assert(capacity > 0);
  elts = new int[capacity];
}


IntSet::IntSet(const IntSet &other) {
  elts = new int[other.elts_capacity];
  elts_size = other.elts_size;
  elts_capacity = other.elts_capacity;

  for (int i = 0; i < other.elts_size; ++i) {
    elts[i] = other.elts[i];
  }
}


IntSet & IntSet::operator= (const IntSet &rhs) {
  if (this == &rhs) return *this; //check for self assignment
  delete[] elts; //remove all

  //initialize member variables
  elts = new int[rhs.elts_capacity];
  elts_size = rhs.elts_size;
  elts_capacity = rhs.elts_capacity;

  //copy from the rhs
  for (int i = 0; i < rhs.elts_size; ++i)
    elts[i] = rhs.elts[i];

  return *this;
}

IntSet::~IntSet() {
  delete[] elts;
}


void IntSet::insert(int v) {
  if (elts_size == elts_capacity) grow();
  if (query(v)) return;
  elts[elts_size++] = v;
}


void IntSet::remove(int v) {
  int victim = indexOf(v);
  if (victim == ELTS_CAPACITY_DEFAULT) return;//not found
  elts[victim] = elts[--elts_size];
}


int IntSet::size() const {
  return elts_size;
}


int IntSet::indexOf(int v) const {
  for (int i = 0; i < elts_size; ++i) {
    if (elts[i] == v) return i;
  }
  return ELTS_CAPACITY_DEFAULT;
}

bool IntSet::query(int v) const {
  return (indexOf(v) != ELTS_CAPACITY_DEFAULT);
}


void IntSet::print() const {
  cout << "{ ";
  for (int i=0; i<elts_size; ++i) cout << elts[i] << " ";
  cout << "} "<< endl;
}


void IntSet::grow() {
  int *tmp = new int[elts_capacity + 1];
  for (int i = 0; i < elts_size; ++i) {
    tmp[i] = elts[i];
  }
  delete [] elts;
  elts = tmp;
  elts_capacity += 1;
}


////////////////////////////////////////////////////////////////////////////////
int main () {
  IntSet is1(1);
  is1.insert(42);
  is1.print();

  IntSet is2;
  is2 = is1;
  is2.insert(43);

  is2.print();
}
