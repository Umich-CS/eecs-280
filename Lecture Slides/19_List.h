#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * Templated, singly-linked, double-ended list implementation
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2015-03-31
 */

#include <cassert>  //assert
#include <iostream> //cout
// NOTE: don't add "using namespace std;" in a .h file.  It pollutes the global
// namespace for every program that includes this file.


////////////////////////////////////////////////////////////////////////////////
// List declaration
template <typename T>
class List {
  //OVERVIEW: a singly-linked list
 public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the first element in the list
  T & front() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the last element in the list
  T & back() const;

  //MODIFIES: this
  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //MODIFIES: this
  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //EFFECTS: prints the list to stdout
  void print() const;

  //default constructor and Big Three
  List();
  List(const List &other);
  ~List();
  List & operator=(const List &rhs);

private:
  //a private type
  struct Node {
    Node *next;
    T datum;
  };

  //MODIFIES: this
  //EFFECTS:  copies all nodes from l to this
  void push_all(const List &other);

  //MODIFIES: this
  //EFFECTS:  removes all nodes
  void pop_all();

  Node *front_ptr; //pointer to the first Node in the list, 0 for empty list
  Node *back_ptr;  //pointer to the last Node in the list, 0 for empty list
};


////////////////////////////////////////////////////////////////////////////////
// List implementation

template <typename T>
bool List<T>::empty() const {
  return front_ptr == 0;
}

template <typename T>
T & List<T>::front() const {
  assert(!empty());
  return front_ptr->datum;
}

template <typename T>
T & List<T>::back() const {
  assert(!empty());
  return back_ptr->datum;
}

template <typename T>
void List<T>::push_front(const T &datum) {
  std::cout << "FIXME: push_front(): do something with 'back_ptr'\n";
  Node *p = new Node;
  p->datum = datum;
  p->next = front_ptr;
  front_ptr = p;
}

template <typename T>
void List<T>::push_back(const T &datum) {
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

template <typename T>
void List<T>::pop_front() {
  std::cout << "FIXME: pop_front(): do something with 'back_ptr'\n";
  assert(!empty());
  Node *victim = front_ptr;
  front_ptr = front_ptr->next;
  delete victim; victim=0;
}

template <typename T>
void List<T>::pop_all() {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
void List<T>::push_all(const List &other) {
  for (Node *p=other.front_ptr; p!=0; p=p->next) {
    push_back(p->datum);
  }
}

template <typename T>
List<T>::List()
  : front_ptr(0), back_ptr(0) {}

template <typename T>
List<T>::~List() {
  pop_all();
}

template <typename T>
List<T>::List(const List &other)
  : front_ptr(0), back_ptr(0) {
  push_all(other);
}

template <typename T>
List<T> & List<T>::operator= (const List &rhs) {
  if (this == &rhs) return *this;
  pop_all();
  push_all(rhs);
  return *this;
}

template <typename T>
void List<T>::print() const {
  for (Node *i=front_ptr; i != 0; i=i->next) {
    std::cout << i->datum << " ";
  }
}

#endif
