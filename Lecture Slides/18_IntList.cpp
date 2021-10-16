/* IntList.cpp
 *
 * Singly-linked, double-ended list implementation
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2015-03-26 created
 */

#include <cassert>
#include <iostream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// IntList declaration
class IntList {
  //OVERVIEW: a singly-linked list
 public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the first element in the list
  int & front() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the last element in the list
  int & back() const;

  //MODIFIES: this
  //EFFECTS:  inserts datum into the front of the list
  void push_front(int datum);

  //MODIFIES: this
  //EFFECTS:  inserts datum into the back of the list
  void push_back(int datum);

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //EFFECTS: prints the list to stdout
  void print() const;

  //default constructor and Big Three
  IntList();
  IntList(const IntList &l);
  ~IntList();
  IntList & operator=(const IntList &rhs);

private:
  //a private type
  struct Node {
    Node *next;
    int datum;
  };

  //MODIFIES: this
  //EFFECTS:  copies all nodes from other list to this list
  void push_all(const IntList &other);

  //MODIFIES: this
  //EFFECTS:  removes all nodes
  void pop_all();

  Node *front_ptr; //pointer to the first Node in the list, 0 for empty list
  Node *back_ptr;  //pointer to the last Node in the list, 0 for empty list
};


////////////////////////////////////////////////////////////////////////////////
// IntList implementation
bool IntList::empty() const {
  return front_ptr == 0;
}

int & IntList::front() const {
  assert(!empty());
  return front_ptr->datum;
}

int & IntList::back() const {
  assert(!empty());
  return back_ptr->datum;
}

void IntList::push_front(int datum) {
  cout << "FIXME: push_front(): do something with 'back_ptr'\n";
  Node *p = new Node;
  p->datum = datum;
  p->next = front_ptr;
  front_ptr = p;
}

void IntList::push_back(int datum) {
  Node *p = new Node;
  p->datum = datum;
  p->next = 0;
  if (empty()) {
    front_ptr = back_ptr = p;
  } else {
    assert(back_ptr);
    back_ptr->next = p;
    back_ptr = p;
  }
}

void IntList::pop_front() {
  cout << "FIXME: pop_front(): do something with 'back_ptr'\n";
  assert(!empty());
  Node *victim = front_ptr;
  front_ptr = front_ptr->next;
  delete victim; victim=0;
}

void IntList::pop_all() {
  while (!empty()) {
    pop_front();
  }
}

void IntList::push_all(const IntList &other) {
  for (Node *p=other.front_ptr; p != 0; p=p->next) {
    push_back(p->datum);
  }
}

IntList::IntList()
  : front_ptr(0), back_ptr(0) {}

IntList::~IntList() {
  pop_all();
}

IntList::IntList(const IntList &other)
  : front_ptr(0), back_ptr(0) {
  push_all(other);
}

IntList & IntList::operator= (const IntList &rhs) {
  if (this == &rhs) return *this;
  pop_all();
  push_all(rhs);
  return *this;
}

void IntList::print() const {
  for (Node *i=front_ptr; i != 0; i=i->next) {
    cout << i->datum << " ";
  }
  cout << "\n";
}


////////////////////////////////////////////////////////////////////////////////
int main() {
  IntList l;
  l.push_front(1);
  l.print();
  l.push_front(2);
  l.print();
  l.push_front(3);
  l.print();
  cout << l.front() << endl;
  l.pop_front();
  l.print();
  l.pop_front();
  l.print();
  l.pop_front();
  l.print();
  if (l.empty()) cout << "empty!\n";
  return 0;
}

/* output
FIXME: push_front(): do something with 'back_ptr'
1 
FIXME: push_front(): do something with 'back_ptr'
2 1 
FIXME: push_front(): do something with 'back_ptr'
3 2 1 
3
FIXME: pop_front(): do something with 'back_ptr'
2 1 
FIXME: pop_front(): do something with 'back_ptr'
1 
FIXME: pop_front(): do something with 'back_ptr'

empty!
*/
