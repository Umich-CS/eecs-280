/* Interfaces_and_Invariants.cpp
 * 
 * Example of an abstract base class representing a set of integers.
 * There are two implementations: sorted and unsorted
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2013-05-30
 */

#include <iostream> //cout, endl
#include <cassert>  //assert
#include <string>   //needed for factory function
using namespace std;


////////////////////////////////////////////////////////////////////////////////
class IntSet {
  // OVERVIEW: interface for a mutable set of ints with bounded size  
public:

  //REQUIRES: set is not full
  //MODIFIES: this
  //EFFECTS: set=set+{v}
  virtual void insert(int v) = 0;

  //REQUIRES: v is in set
  //MODIFIES: this
  //EFFECTS: set=set-{v}
  virtual void remove(int v) = 0;

  //EFFECTS: returns true if v is in set,
  //false otherwise
  virtual bool query(int v) const = 0;

  //EFFECTS: returns |set|
  virtual int size() const = 0;

  //EFFECTS: prints set
  virtual void print() const = 0;

  //maximum size of a set
  static const int ELTS_CAPACITY = 100;
};


////////////////////////////////////////////////////////////////////////////////
class IntSetUnsorted : public IntSet {
  // OVERVIEW: mutable set of ints with bounded size, unsorted order
public:

  //EFFECTS: creates a zero-size IntSetUnsorted
  IntSetUnsorted();

  //REQUIRES: set is not full
  //MODIFIES: this
  //EFFECTS: set=set+{v}
  virtual void insert(int v);

  //REQUIRES: v is in set
  //MODIFIES: this
  //EFFECTS: set=set-{v}
  virtual void remove(int v);

  //EFFECTS: returns true if v is in set,
  //false otherwise
  virtual bool query(int v) const;

  //EFFECTS: returns |set|
  virtual int size() const;

  //EFFECTS: prints set
  virtual void print() const;

private:
  //Represent a set of size N as an sorted set of integers, with no 
  //duplicates, stored in the first N slots of the array
  int elts[ELTS_CAPACITY];

  //Number of elements currently in the set
  int elts_size;

  //EFFECTS: returns the index of v if it exists in the set, ELTS_CAPACITY otherwise
  int indexOf(int v) const;

  //EFFECTS: returns true if representation invariant holds
  bool check_invariant() const;
};


////////////////////////////////////////////////////////////////////////////////
class IntSetSorted : public IntSet {
  // OVERVIEW: mutable set of ints with bounded size, in sorted order
 public:

  //EFFECTS: creates a zero-size IntSetSorted
  IntSetSorted();

  //REQUIRES: set is not full
  //MODIFIES: this
  //EFFECTS: set=set+{v}
  virtual void insert(int v);

  //REQUIRES: v is in set
  //MODIFIES: this
  //EFFECTS: set=set-{v}
  virtual void remove(int v);

  //EFFECTS: returns true if v is in set,
  //false otherwise
  virtual bool query(int v) const;

  //EFFECTS: returns |set|
  virtual int size() const;

  //EFFECTS: prints set
  virtual void print() const;

private:
  //Represent a set of size N as an sorted set of integers, with no 
  //duplicates, stored in the first N slots of the array
  int elts[ELTS_CAPACITY];

  //Number of elements currently in the set
  int elts_size;

  //EFFECTS: returns the index of v if it exists in the set, ELTS_CAPACITY otherwise
  int indexOf(int v) const;

  //EFFECTS: returns true if representation invariant holds
  bool check_invariant() const;
};


////////////////////////////////////////////////////////////////////////////////
// IntSetUnsorted Implementation

IntSetUnsorted::IntSetUnsorted()
  : elts_size(0) {
  assert(check_invariant());
}


void IntSetUnsorted::insert(int v) {
  assert(check_invariant());
  assert(elts_size < ELTS_CAPACITY); //REQUIRES set is not full
  if (query(v)) return;
  elts[elts_size++] = v;
  assert(check_invariant());
}


void IntSetUnsorted::remove(int v) {
  assert(check_invariant());
  int victim = indexOf(v);
  if (victim == ELTS_CAPACITY) return;//not found
  elts[victim] = elts[--elts_size];
  assert(check_invariant());
}


int IntSetUnsorted::size() const {
  assert(check_invariant());
  return elts_size;
}


int IntSetUnsorted::indexOf(int v) const {
  assert(check_invariant());
  for (int i = 0; i < elts_size; ++i) {
    if (elts[i] == v) return i;
  }
  return ELTS_CAPACITY;
}


bool IntSetUnsorted::query(int v) const {
  assert(check_invariant());
  return (indexOf(v) != ELTS_CAPACITY);
}


void IntSetUnsorted::print() const {
  assert(check_invariant());
  cout << "{ ";
  for (int i=0; i<elts_size; ++i)
    cout << elts[i] << " ";
  cout << "} "<< endl;
  assert(check_invariant());
}

bool IntSetUnsorted::check_invariant() const {
  for (int i=0; i<elts_size; ++i) {
    for (int j=i+1; j<elts_size; ++j) {
      if (elts[i] == elts[j]) return false;
    }
  }
  return true;
}


////////////////////////////////////////////////////////////////////////////////
// IntSetSorted Implementation
IntSetSorted::IntSetSorted()
  : elts_size(0) {
  assert(check_invariant());
}


void IntSetSorted::insert(int v) {
  assert(check_invariant());
  assert(elts_size < ELTS_CAPACITY); //REQUIRES set is not full

  if (indexOf(v) != ELTS_CAPACITY) return; //already there
  int cand = elts_size-1; //largest element

  while ((cand >= 0) && elts[cand] > v) {
    elts[cand+1] = elts[cand];
    --cand;
  }

  //Now, cand points to the left of the "gap".
  elts[cand+1] = v;
  ++elts_size; //repair invariant

  assert(check_invariant());
}


void IntSetSorted::remove(int v) {
  assert(check_invariant());

  int gap = indexOf(v);

  if (gap == ELTS_CAPACITY) return; //not found
  --elts_size; //one less element

  while (gap < elts_size) {
    //there are elts to our right
    elts[gap] = elts[gap+1];
    ++gap;
  }

  assert(check_invariant());
}


int IntSetSorted::size() const {
  assert(check_invariant());
  return elts_size;
}


int IntSetSorted::indexOf(int v) const {
  assert(check_invariant());
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


bool IntSetSorted::query(int v) const {
  assert(check_invariant());
  return (indexOf(v) != ELTS_CAPACITY);
}


void IntSetSorted::print() const {
  assert(check_invariant());
  cout << "{ ";
  for (int i=0; i<elts_size; ++i)
    cout << elts[i] << " ";
  cout << "} "<< endl;
}


bool IntSetSorted::check_invariant() const {
  for (int i=0; i<elts_size-1; ++i) {
    if (elts[i] >= elts[i+1]) {
      return false;
    }
  }
  return true;
}


////////////////////////////////////////////////////////////////////////////////
// IntSet factory function

// Dirty global variable trick.  We'll fix this when we learn about dynamic
//  memory.
static IntSetSorted g_iss;
static IntSetUnsorted g_isu;

//EFFECTS: returns a pointer to an IntSet
IntSet * IntSet_factory() {
  //return &g_iss; //could use the sorted version instead, and would still work!
  return &g_isu;
}


////////////////////////////////////////////////////////////////////////////////
int main () {
  IntSet *is = IntSet_factory();
  is->insert(7);
  is->insert(4);
  is->insert(7);
  is->print();
  is->remove(7);
  is->print();
}
